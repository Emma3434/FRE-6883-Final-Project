
#include "MainEngine.h"

extern int fetch_data_list_single(vector<StockData*> stock_list);

extern int fetch_data_list_single2(vector<StockData*> stock_list);

extern int fetch_data_list_multi(vector<StockData*> stock_list);


void MainEngine::Initialize()
{
	// init calendar
	calendar.LoadData();

	// init stock list
	LoadStockData();
	stock_map = create_stock_map(stock_list);

	// init groups
	groups.push_back("Beat");
	groups.push_back("Meet");
	groups.push_back("Miss");

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

	fetch_data_list_single(stock_list);

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
	cout << "start retrieve data (multi-thread)..." << endl << endl;

	clock_t time1 = clock();

	for (auto iter : stock_list)  iter->RetrieveDataSetting(N, &calendar);

	fetch_data_list_multi(stock_list);

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

map<string, map<string, Vector>> MainEngine::RunResearch()
{	
	map<string, vector<Vector>> AAR;
	map<string, vector<Vector>> CAAR;

	map<string, map<string, Vector>> result;

	for (int i = 0; i < RUN_BOOTSTRAP_NUM; i++)
	{
		// run bootstrap
		cout << "bootstrapping trial: " << i+1 << endl;
		map<string, vector<StockData*>> bootstrap_result = bootstrapping(stock_list, i);
		cout << bootstrap_result["Beat"][1]->ticker << endl;
		//cout << "bootstrapping finish" << endl;
		for (auto iter : groups)
		{
			AAR[iter].push_back(CalReturnForGroup(bootstrap_result[iter]));
			CAAR[iter].push_back(AAR[iter].back().cumsum());
		}

		//cout << "AAR CAAR finish" << endl;
	}

	// combine bootstrap results
	for (auto iter : groups)
	{
		Matrix AAR_mean(AAR[iter]);
		Matrix CAAR_mean(CAAR[iter]);
		//AAR_mean.display(); // check if random see valid
		result["AAR_mean"][iter] = Matrix(AAR[iter]).mean();
		result["CAAR_mean"][iter] = Matrix(CAAR[iter]).mean();
		result["AAR_std"][iter] = Matrix(AAR[iter]).std();
		result["CAAR_std"][iter] = Matrix(CAAR[iter]).std();
	}
	research_result = result;
	return result;
}

Vector MainEngine::CalReturnForGroup(vector<StockData*> stock_list)
{
	Matrix mat(stock_list);
	Vector AARt = mat.sum();
	return AARt;
}

void MainEngine::ClearAll()
{
	for (auto itr : stock_list)
	{
		delete itr;
		itr = NULL;
	};
}