
#include "StockData.h"
#include "FetchData.h"
#include "CalendarManager.h"
#include "Utils.h"
#include "Constant.h"
#include <vector>
#include <time.h>
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






	// TODO: test retrievedata
	// - use CalendarManger to get previous/next date.
	// - fetch speed might be an issue. multithreading might help.
	// - fetch data not complete.

	cout << "--------------------------------------------" << endl;
	cout << "start test fetch data..." << endl << endl;

	int N = 40;
	clock_t time1 = clock();
	for (auto iter : stock_list) iter.RetrieveData(N, &calendar);
	clock_t time2 = clock();
	double secs = (double)(time2 - time1) / CLOCKS_PER_SEC;	// Count time
	cout << "run time : " << secs  << " seconds" << endl;
	




	// test create stock map
	// - finish

	cout << "--------------------------------------------" << endl;
	cout << "start test stock map..." << endl << endl;
	map<string, StockData> stock_map = create_stock_map(stock_list);
	cout << "stock mat size: " << stock_map.size() << endl;
	stock_map["AAPL"].DisplayAttribute();




	cout << "end" << endl;
}