
#include "MainEngine.h"

extern int fetch_data_list(vector<StockData*> stock_list);

void MainEngine::Initialize()
{
	// init calendar
	calendar.LoadData();

	// init stock list
	LoadStockData();
	stock_map = create_stock_map(stock_list);

}

void MainEngine::InitializeTest()
{
	// init calendar
	calendar.LoadData();

	// init stock list
	stock_list = load_stock_data(TEST_FILE, "Test");
	stock_map = create_stock_map(stock_list);

}

void MainEngine::LoadStockData()
{
	vector<StockData*> stock_list_miss = load_stock_data(MISS_FILE, "Miss");
	vector<StockData*> stock_list_meet = load_stock_data(MEET_FILE, "Meet");
	vector<StockData*> stock_list_beat = load_stock_data(BEAT_FILE, "Beat");

	cout << "stock list Miss size: " << stock_list_miss.size() << endl;
	cout << "stock list Meet size: " << stock_list_meet.size() << endl;
	cout << "stock list Beat size: " << stock_list_beat.size() << endl;

	stock_list = combine_stock_list(stock_list_miss, stock_list_meet, stock_list_beat);

	cout << "stock list size: " << stock_list.size() << endl;
}

void MainEngine::RetrieveDataSingleThread()
{

	cout << "start retrieve data (single-thread)..." << endl << endl;

	clock_t time1 = clock();

	for (auto iter : stock_list)  iter->RetrieveDataSetting(N, &calendar);

	fetch_data_list(stock_list);

	for (auto iter : stock_list)
	{
		cout << iter->ticker << endl;
		iter->RetrieveDataSanityCheck();
		iter->CalDailyReturns();
		//iter->DisplayData();
	}

	clock_t time2 = clock();
	double secs = (double)(time2 - time1) / CLOCKS_PER_SEC;
	cout << "run time : " << secs << " seconds" << endl;
}


void MainEngine::RetrieveDataMultiThread()
{
	cout << "start retrieve data (mutli-thread)..." << endl << endl;

	clock_t time1 = clock();
	time1 = clock();
	
	MYDATA* mydt = new MYDATA[stock_list.size()];
	for (int i = 0; i < stock_list.size(); i++) {
		mydt[i].sd = stock_list[i];
		mydt[i].calendar = calendar;
		mydt[i].N = N;
		mydt[i].size = stock_list.size();
	}
	
	thread t1(thread_producer, mydt);

	// create thread pool for retrieve data
	thread* consumer_threads = new thread[THREAD_NUM];
	for (int i = 0; i < THREAD_NUM; i++)
	{
		consumer_threads[i] = thread(thread_consumer);
	}
	
	for (int i = 0; i < THREAD_NUM; i++)
	{
		//consumer_threads[i].detach();
		consumer_threads[i].join();
	}

	t1.join();

	delete[] consumer_threads;
	delete[] mydt;

	//for (int i = 0; i < 4; i++)
	//{
	//	stock_list[i]->DisplayData();
	//}

	clock_t time2 = clock();
	double secs = (double)(time2 - time1) / CLOCKS_PER_SEC;
	cout << "run time : " << secs << " seconds" << endl;
}


void MainEngine::ClearAll()
{
	for (auto itr : stock_list)
	{
		delete itr;
		itr = NULL;
	};
}