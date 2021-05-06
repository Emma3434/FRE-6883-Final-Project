#ifndef MainEngine_H
#define MainEngine_H

#include "StockData.h"
#include "Utils.h"
#include "CalendarManager.h"
#include <time.h>

using namespace std;

class MainEngine
{
public:
	int N;
	CalendarManager calendar;
	vector<StockData*> stock_list;
	map<string, StockData*> stock_map;
	

	MainEngine(): N(30) { };
	MainEngine(int N_) : N(N_) { };

	void SetN(int N_) { N = N_; };

	void Initialize();
	void InitializeTest();

	void LoadStockData();
	void RetrieveDataSingleThread();
	void RetrieveDataMultiThread();

	void ClearAll();
};



#endif