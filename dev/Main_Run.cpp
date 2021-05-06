
#include "StockData.h"
#include "FetchData.h"
#include "MainEngine.h"
#include "CalendarManager.h"
#include "Utils.h"
#include "Constant.h"
#include "Vector.h"
#include <vector>
//#include <time.h>
#include <thread>
//#include <map>
#include "Matrix.h"

#include <iostream>
using namespace std;




int main()
{


	MainEngine me;

	me.SetN(30);

	me.Initialize();
	//me.InitializeTest();

	me.RetrieveDataSingleThread();
	//me.RetrieveDataMultiThread();





	me.ClearAll();




	// test bootstrapping
	// - 

	/*map<string, vector<StockData*>> bootstrap_result;
	for (int i = 0; i < 3; i++)
	{
		cout << "bootstrapping trial: " << i << endl;
		bootstrap_result = bootstrapping(stock_list);
		cout << "Beat length: " << bootstrap_result["Beat"].size() << endl;
		cout << "Meet length: " << bootstrap_result["Meet"].size() << endl;
		cout << "Miss length: " << bootstrap_result["Miss"].size() << endl;
		bootstrap_result["Beat"][0]->DisplayAttribute();
		bootstrap_result["Meet"][1]->DisplayAttribute();
		bootstrap_result["Miss"][2]->DisplayAttribute();
		cout << endl;
	}*/


}
