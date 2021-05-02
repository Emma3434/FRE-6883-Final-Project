
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
	fetch_success = false;

	// clear dates and adjclose vectors
	vector <string>().swap(dates);
	vector <double>().swap(adjclose);
	vector <string>().swap(dates_benchmark);
	vector <double>().swap(adjclose_benchmark);


	string day0 = announce_day + "T16:00:00";
	//cout << "announce day: " << announce_day << endl;
	string startTime = (*calendar).PrevNDays(announce_day, N);
	string endTime = (*calendar).NextNDays(announce_day, N);

	int result = fetch_data(this, startTime, endTime);
	int result_benchmark = fetch_benchmark(this, startTime, endTime);

	//display_data_mutex.lock();
	cout << "fetch: sanity check..." << endl;
	cout << "fetch: " << ticker << " expected length: " << 2*N+1 << ", received length: " << adjclose.size() << endl;
	cout << "fetch: " << ticker << " benchmark expected length: " << 2 * N + 1 << ", received length: " << adjclose_benchmark.size() << endl;
	//display_data_mutex.unlock();

	if ((2 * N + 1 == adjclose.size()) && (adjclose.size() == adjclose_benchmark.size()))
	{
		// sanity check for fetch data
		// eg: ADT no historical data on Yahoo finance
		cout << "fetch: sanity check succeed" << endl << endl;
		fetch_success = true;
	}
	else 
	{
		cout << "fetch: sanity check fail" << endl << endl;
	}

}

void StockData::CalDailyReturns()
{
	// clear returns
	vector <double>().swap(adjreturn);
	vector <double>().swap(cum_adjreturn);
	vector <double>().swap(adjreturn_benchmark);
	vector <double>().swap(cum_adjreturn_benchmark);
	vector <double>().swap(abnormal_return);

	// zero return for first day
	adjreturn.push_back(0);
	cum_adjreturn.push_back(0);
	adjreturn_benchmark.push_back(0);
	cum_adjreturn_benchmark.push_back(0);
	abnormal_return.push_back(0);

	for (int i = 1; i < (adjclose.size()-1); i++)
	{
		adjreturn.push_back(adjclose[i] / adjclose[i-1] - 1);
		cum_adjreturn.push_back(cum_adjreturn.back() + adjreturn.back());
		adjreturn_benchmark.push_back(adjclose_benchmark[i] / adjclose_benchmark[i - 1] - 1);
		cum_adjreturn_benchmark.push_back(cum_adjreturn_benchmark.back() + adjreturn_benchmark.back());
		abnormal_return.push_back(adjreturn.back() - adjreturn_benchmark.back());
	}
}

void StockData::DisplayAttribute() const
{
	cout << "Ticker: " << ticker
		<< ", Announce Date: " << announce_day
		<< ", EPS Surprise: " << eps_surprise
		<< ", Group: " << group
		<< endl;
}

void StockData::DisplayData() const
{
	//display_data_mutex.lock();

	cout << std::setw(10);
	cout << setw(6) << "Ticker" 
		<< setw(15) << "Dates" 
		<< setw(15) << "Adjclose" 
		<< setw(15) << "Adjreturn" 
		<< setw(15) << "Cumadjreturn"
		<< setw(15) << "Benchmarkreturn"
		<< setw(15) << "Abnormalreturn"
		<< endl;
	
	if (adjclose.size() > 4)
	{
		for (int i = 0; i <= 4; i++)
		{
			cout << setw(6) << ticker 
				<< setw(15) << dates[i] 
				<< setw(15) << adjclose[i] 
				<< setw(15) << adjreturn[i] 
				<< setw(15) << cum_adjreturn[i]
				<< setw(15) << adjreturn_benchmark[i]
				<< setw(15) << abnormal_return[i]
				<< endl;
		}
	}
	cout << endl;

	//display_data_mutex.unlock();
}