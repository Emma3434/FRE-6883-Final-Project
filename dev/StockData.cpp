
#include "StockData.h"
//#include "FetchData.h"
#include "Utils.h"
#include <iostream>

using namespace std;


StockData::StockData(string ticker_): ticker(ticker_)
{
	eps_surprise = 0;
	announce_day = "";	
}


void StockData::RetrieveData(int N, CalendarManager* calendar)
{
	string day0 = announce_day + "T16:00:00";
	//cout << "announce day: " << announce_day << endl;
	string startTime = (*calendar).PrevNDays(announce_day, N);
	string endTime = (*calendar).NextNDays(announce_day, N);

	//fetch_data(this, string startTime, string endTime);
}

void StockData::DisplayAttribute() const
{
	cout << "Ticker: " << ticker
		<< ", Announce Date: " << announce_day
		<< ", EPS Surprise: " << eps_surprise
		<< endl;
}
