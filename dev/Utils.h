#ifndef Utils_H
#define Utils_H
#include <string>
#include <vector>
#include <map>
#include <sstream> 
#include <fstream>
#include <iostream>
#include "StockData.h"

using namespace std;

vector<StockData> load_stock_data(string filename, string group);

vector<StockData> combine_stock_list(vector<StockData> stock_list_miss, vector<StockData> stock_list_meet, vector<StockData> stock_list_beat);

map<string, StockData> create_stock_map(vector<StockData> stock_list);



#endif
