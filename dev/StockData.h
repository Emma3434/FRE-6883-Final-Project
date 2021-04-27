
#ifndef StockData_H
#define StockData_H

#include <string>
#include "FetchData.h"

using namespace std;

class StockData
{
public:
	string ticker;
	string announce_day;
	double eps_surprise;
	struct MemoryStruct data;

	StockData(string ticker_);
	~StockData();

	void SetAnnounceDay(string announce_day_);
	void SetAnnounceDay(double eps_surprise_);

private:

};

#endif