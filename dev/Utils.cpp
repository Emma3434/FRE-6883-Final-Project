
#include "Utils.h"

mutex display_data_mutex;
mutex queue_not_empty_mutex;
deque<MyData> q;
condition_variable cond;


vector<StockData*> load_stock_data(string filename, string group)
{
	// load data from local grouped EPS files.
	// initiliaze StockData instances using data.

	//cout << filename << endl;
	ifstream inFile(filename, ios::in);
	string line;

	vector<StockData*> stock_list;

	while (getline(inFile, line))
	{
		//cout << line << endl;

		StockData* stock = new StockData();
		stock->SetGroup(group);

		stock->SetTicker(line.substr(0, line.find_first_of(',')));

		stock->SetEPSSurprisePercent(stod(line.substr(line.find_last_of(',') + 1)));
		line.erase(line.find_last_of(','));

		stock->SetEPSSurprise(stod(line.substr(line.find_last_of(',') + 1)));
		line.erase(line.find_last_of(','));

		stock->SetActualEPS(stod(line.substr(line.find_last_of(',') + 1)));
		line.erase(line.find_last_of(','));

		stock->SetEstimateEPS(stod(line.substr(line.find_last_of(',') + 1)));
		line.erase(line.find_last_of(','));

		stock->SetPeriodEnd(line.substr(line.find_last_of(',') + 1));
		line.erase(line.find_last_of(','));

		stock->SetAnnounceDay(line.substr(line.find_last_of(',') + 1));

		//stock.ShowAttribute();
		stock_list.push_back(stock);
	}

	return stock_list;
}

vector<StockData*> combine_stock_list(vector<StockData*> stock_list_miss, vector<StockData*> stock_list_meet, vector<StockData*> stock_list_beat)
{
	// combine stock instances from three groups

	vector<StockData*> stock_list;
	for (auto iter : stock_list_miss)
	{
		stock_list.push_back(iter);
	}
	
	for (auto iter : stock_list_meet)
	{
		stock_list.push_back(iter);
	}

	for (auto iter : stock_list_beat)
	{
		stock_list.push_back(iter);
	}

	return stock_list;
}

std::map<string, StockData*> create_stock_map(vector<StockData*> stock_list)
{
	std::map<string, StockData*> stock_map;
	for (auto iter : stock_list)
	{
		stock_map[iter->GetTicker()] = iter;
	}
	return stock_map;
}

void thread_task(MyData md)
{
	md.sd->RetrieveData(md.N, &md.calendar);
}

void thread_producer(MYDATA* md)
{
	int count = md->size;
	for (int i = 0; i < count; i++)
	{			
		unique_lock<mutex> unique(queue_not_empty_mutex);
		q.push_front(md[i]);

		this_thread::sleep_for(500ms);
		unique.unlock();
		cout << "producer a value: " << md[i].sd->ticker << endl;
		cond.notify_all();
	}

	// poison pill to terminate consumers
	MYDATA pill = md[0];
	pill.size = 0;

	unique_lock<mutex> unique(queue_not_empty_mutex);
	q.push_front(pill);
	unique.unlock();
	cout << "producer a pill" << endl;
	cond.notify_all();
	this_thread::sleep_for(chrono::seconds(10));
}

int thread_consumer()
{
	MYDATA mydt;
	while (1)
	{
		unique_lock<mutex> unique(queue_not_empty_mutex);
		while (q.empty())
			cond.wait(unique);
		mydt = q.back();
		if (mydt.size == 0)
		{
			// receive poison pill: finish all tasks, terminate current thread
			cout << "thread receive poison pill" << endl;
			unique.unlock();
			return 0;
		}
		q.pop_back();
		unique.unlock();

		cout << mydt.sd->ticker << " retrieve data" << endl;

		// multiprocess tasks
		mydt.sd->RetrieveData(mydt.N, &mydt.calendar);
		mydt.sd->CalDailyReturns();
	}
}

bool cmp(pair<StockData*, double> a, pair<StockData*, double> b) 
{
	return a.second < b.second;
}

map<string, vector<StockData*>> bootstrapping(vector<StockData*> stock_list)
{
	int bootstrap_num = BOOTSTRAP_NUM;
	default_random_engine random(time(NULL));
	std::uniform_real_distribution<double> dist(0.0, 1.0);

	vector< pair<StockData*, double> > vec;
	for (int i = 0; i < stock_list.size()-1; i++)
	{
		vec.push_back(pair<StockData*, double>(stock_list[i], dist(random)));
	}

	sort(vec.begin(), vec.end(), cmp);	

	// Beat
	vector<StockData*> beat_result;
	for (auto iter : vec)
	{
		if ((iter.first->group == "Beat") && (iter.first->fetch_success))
		{
			beat_result.push_back(iter.first);
			if (beat_result.size() == bootstrap_num) break;
		}
	}

	// Meet
	vector<StockData*> meet_result;
	for (auto iter : vec)
	{
		if ((iter.first->group == "Meet") && (iter.first->fetch_success))
		{
			meet_result.push_back(iter.first);
			if (meet_result.size() == bootstrap_num) break;
		}
	}

	// Miss
	vector<StockData*> miss_result;
	for (auto iter : vec)
	{
		if ((iter.first->group == "Miss") && (iter.first->fetch_success))
		{
			miss_result.push_back(iter.first);
			if (miss_result.size() == bootstrap_num) break;
		}
	}

	map<string, vector<StockData*>> bootstrap_result;
	bootstrap_result["Beat"] = beat_result;
	bootstrap_result["Meet"] = meet_result;
	bootstrap_result["Miss"] = miss_result;

	return bootstrap_result;
}