
#include "StockData.h"



StockData::StockData(string ticker_): ticker(ticker_)
{
	eps_surprise = 0;
	announce_day = "";	
}

StockData::~StockData()
{
}

void StockData::SetAnnounceDay(string announce_day_) 
{
	announce_day = announce_day;
}

void StockData::SetAnnounceDay(double eps_surprise_)
{
	eps_surprise = eps_surprise_;
}