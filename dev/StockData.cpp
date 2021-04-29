
#include "StockData.h"
#include "FetchData.h"
#include "Utils.h"
#include <iostream>
#include <iomanip>
#include <thread>

using namespace std;

extern mutex display_data_mutex;

extern int fetch_data(StockData* sd, string startTimeString, string endTimeString);

extern int fetch_benchmark(StockData* sd, string startTimeString, string endTimeString);

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

	int result = fetch_data(this, startTime, endTime);
	int result_benchmark = fetch_benchmark(this, startTime, endTime);

	display_data_mutex.lock();
	cout << "fetch sanity check..." << endl;
	cout << ticker << " expected length: " << 2*N+1 << ", received length: " << adjclose.size() << endl;
	cout << ticker << " benchmark expected length: " << 2 * N + 1 << ", received length: " << adjclose_benchmark.size() << endl << endl;
	display_data_mutex.unlock();
	// TODO: sanity stock dates matches benchmark dates
}

void StockData::DisplayAttribute() const
{
	cout << "Ticker: " << ticker
		<< ", Announce Date: " << announce_day
		<< ", EPS Surprise: " << eps_surprise
		<< endl;
}

void StockData::DisplayData() const
{

	display_data_mutex.lock();

	cout << std::setw(10);
	cout << setw(6) << "Ticker" << setw(15) << "Dates" << setw(15) << "Adjclose" << endl;
	for (int i = 0; i <= 4; i++)
	{
		cout << setw(6) << ticker << setw(15) << dates[i] << setw(15) << adjclose[i] << endl;
	}

	display_data_mutex.unlock();
}