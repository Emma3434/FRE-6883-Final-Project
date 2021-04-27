
#include "Utils.h"


vector<StockData> load_stock_data(string filename, string group)
{
	// load data from local grouped EPS files.
	// initiliaze StockData instances using data.

	//cout << filename << endl;
	ifstream inFile(filename, ios::in);
	string line;

	vector<StockData> stock_list;

	while (getline(inFile, line))
	{
		//cout << line << endl;

		StockData stock;
		stock.SetGroup(group);

		stock.SetTicker(line.substr(0, line.find_first_of(',')));

		stock.SetEPSSurprisePercent(stod(line.substr(line.find_last_of(',') + 1)));
		line.erase(line.find_last_of(','));

		stock.SetEPSSurprise(stod(line.substr(line.find_last_of(',') + 1)));
		line.erase(line.find_last_of(','));

		stock.SetActualEPS(stod(line.substr(line.find_last_of(',') + 1)));
		line.erase(line.find_last_of(','));

		stock.SetEstimateEPS(stod(line.substr(line.find_last_of(',') + 1)));
		line.erase(line.find_last_of(','));

		stock.SetPeriodEnd(line.substr(line.find_last_of(',') + 1));
		line.erase(line.find_last_of(','));

		stock.SetAnnounceDay(line.substr(line.find_last_of(',') + 1));

		//stock.ShowAttribute();
		stock_list.push_back(stock);
	}

	return stock_list;
}

vector<StockData> combine_stock_list(vector<StockData> stock_list_miss, vector<StockData> stock_list_meet, vector<StockData> stock_list_beat)
{
	// combine stock instances from three groups

	vector<StockData> stock_list;
	for (auto iter : stock_list_miss)
	{
		stock_list.push_back(iter);
	}
	
	for (auto iter : stock_list_meet)
	{
		stock_list.push_back(iter);
	}

	for (auto iter : stock_list_beat)
	{
		stock_list.push_back(iter);
	}

	return stock_list;
}

std::map<string, StockData> create_stock_map(vector<StockData> stock_list)
{
	std::map<string, StockData> stock_map;
	for (auto iter : stock_list)
	{
		stock_map[iter.GetTicker()] = iter;
	}
	return stock_map;
}
