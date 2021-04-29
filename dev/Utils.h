#ifndef Utils_H
#define Utils_H
#include <string>
#include <vector>
#include <map>
#include <sstream> 
#include <fstream>
#include <iostream>
#include <mutex> 
#include "StockData.h"

using namespace std;

typedef struct MyData
{
	StockData* sd;
	CalendarManager calendar;
	int N;
}MYDATA;

//mutex display_data_mutex;

vector<StockData> load_stock_data(string filename, string group);

vector<StockData> combine_stock_list(vector<StockData> stock_list_miss, vector<StockData> stock_list_meet, vector<StockData> stock_list_beat);

map<string, StockData> create_stock_map(vector<StockData> stock_list);

void thread_task(MyData md);

#endif