
#include "StockData.h"
#include "FetchData.h"
#include "CalendarManager.h"
#include "Utils.h"
#include "Constant.h"
#include <vector>
#include <time.h>
#include <thread>
//#include <map>

#include <iostream>
using namespace std;




int main()
{

	//vector<StockData> stock_list = load_stock_data(TEST_FILE, "Test");



	// test CalendarManager
	// - finish

	cout << "--------------------------------------------" << endl;
	cout << "start test CalendarManager..." << endl << endl;
	CalendarManager calendar;
	calendar.LoadData();
	cout << calendar.PrevNDays("2018-12-14", 3) << endl;
	cout << calendar.NextNDays("2021-04-19", 3) << endl;
	cout << calendar.NextNDays("2021-04-19", 10) << endl;




	// test load data
	// - finish
	cout << "--------------------------------------------" << endl;
	cout << "start test load_stock_dta..." << endl << endl;
	vector<StockData> stock_list_miss = load_stock_data(MISS_FILE, "Miss");
	vector<StockData> stock_list_meet = load_stock_data(MEET_FILE, "Meet");
	vector<StockData> stock_list_beat = load_stock_data(BEAT_FILE, "Beat");

	cout << "stock list Miss size£º " << stock_list_miss.size() << endl;
	cout << "stock list Meet size£º " << stock_list_meet.size() << endl;
	cout << "stock list Beat size£º " << stock_list_beat.size() << endl;

	vector<StockData> stock_list = combine_stock_list(stock_list_miss, stock_list_meet, stock_list_beat);
	
	cout << "stock list size£º " << stock_list.size() << endl;






	// test retrievedata
	// - use CalendarManger to get previous/next date.
	// - fetch speed might be an issue. multithreading might help.
	// - fetch data complete.

	//cout << "--------------------------------------------" << endl;
	//cout << "start test fetch data..." << endl << endl;

	//int N = 50;

	//clock_t time1 = clock();
	//for (auto iter : stock_list)
	//{
	//	cout << iter.ticker << endl;
	//	iter.RetrieveData(N, &calendar);
	//	iter.CalDailyReturns();
	//	iter.DisplayData();
	//}
	//clock_t time2 = clock();
	//double secs = (double)(time2 - time1) / CLOCKS_PER_SEC;	
	//cout << "run time : " << secs  << " seconds" << endl;
	




	// test retrievedata using multithreading
	// - fetch speed might be an issue.multithreading might help.
	// - producer-consumer model

	//cout << "--------------------------------------------" << endl;
	//cout << "start test fetch data..." << endl << endl;

	//time1 = clock();
	//
	//MYDATA* mydt = new MYDATA[stock_list.size()];
	//for (int i = 0; i < stock_list.size(); i++) {
	//	mydt[i].sd = &stock_list[i];
	//	mydt[i].calendar = calendar;
	//	mydt[i].N = N;
	//	mydt[i].size = stock_list.size();
	//}
	//
	//thread t1(thread_producer, mydt);

	//// create thread pool for retrieve data
	//int thread_num = 10;
	//thread* consumer_threads = new thread[thread_num];
	//for (int i = 0; i < thread_num; i++)
	//{
	//	consumer_threads[i] = thread(thread_consumer);
	//}
	//
	//for (int i = 0; i < thread_num; i++)
	//{
	//	consumer_threads[i].detach();
	//	//consumer_threads[i].join();
	//}

	//t1.join();

	//delete[] consumer_threads;
	//delete[] mydt;

	//for (int i = 0; i < 4; i++)
	//{
	//	stock_list[i].DisplayData();
	//}

	//time2 = clock();
	//secs = (double)(time2 - time1) / CLOCKS_PER_SEC;	
	//cout << "run time : " << secs << " seconds" << endl;


	// test create stock map
	// - finish

	/*cout << "--------------------------------------------" << endl;
	cout << "start test stock map..." << endl << endl;
	map<string, StockData> stock_map = create_stock_map(stock_list);
	cout << "stock mat size: " << stock_map.size() << endl;
	stock_map["PWR"].DisplayAttribute();*/




	// test bootstrapping
	// - 

	map<string, vector<StockData>> bootstrap_result;
	for (int i = 0; i < 3; i++)
	{
		cout << "bootstrapping trial: " << i << endl;
		bootstrap_result = bootstrapping(stock_list);
		cout << "Beat length: " << bootstrap_result["Beat"].size() << endl;
		cout << "Meet length: " << bootstrap_result["Meet"].size() << endl;
		cout << "Miss length: " << bootstrap_result["Miss"].size() << endl;
		bootstrap_result["Beat"][0].DisplayAttribute();
		bootstrap_result["Meet"][1].DisplayAttribute();
		bootstrap_result["Miss"][2].DisplayAttribute();
		cout << endl;
	}
	
	
	
	//test vector class
	//-
	cout << "--------------------------------------------" << endl;
	cout << "start test VectorClass..." << endl << endl;
	vector<double> data = { 100,101,102,103,104 };
	vector<double> data2 = { 99,100,101,102,103 };
    Vector adjclose(data);
	Vector adjclose2(data2);
	Vector adjclose3(data);
	cout << "Original vector adjclose" << " ";
	for (int i = 0; i < adjclose.size(); i++)
	{
		cout << adjclose[i] << " ";
	}
	cout << endl;
	cout << "Test adjclose.size() " << adjclose.size() << endl;
	adjclose.push_back(105);
	cout << "After push_back(105) ";
	for (int i = 0; i < adjclose.size(); i++)
	{
		cout << adjclose[i]<<" ";
	}
	cout << endl;
	cout << "adjclose.back()" << adjclose.back() << endl;
	Vector pctchange = adjclose.pct_change();
	cout << "After pct_change() ";
	for (int i = 0; i < pctchange.size(); i++)
	{
		cout << pctchange[i]<<" ";
	}
	cout << endl;
	cout << "Calculate sum of adjreturn " << pctchange.sum() << endl;
	cout << "Calculate cumsum of adjreturn ";
	for (int i = 0; i < pctchange.cumsum().size(); i++)
	{
		cout << pctchange.cumsum()[i] << " ";
	}
	cout << endl;
	
	Vector diff = adjclose3 - adjclose2;
	Vector sum = adjclose3 + adjclose2;

	cout << "Sum of data 3 and 2 ";
	for (int i = 0; i < sum.size(); i++)
	{
		cout << sum[i] <<" ";
	}
	cout << endl;
	cout << "Difference of data 3 and 2 ";
	for (int i = 0; i < diff.size(); i++)
	{
		cout << diff.data[i] <<" ";
	}
	cout << endl;

	cout << "end" << endl;
}
