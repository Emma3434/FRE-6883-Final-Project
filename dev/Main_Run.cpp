
#include "StockData.h"
#include "FetchData.h"
#include "MainEngine.h"
#include "CalendarManager.h"
#include "Utils.h"
#include "Configure.h"
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
	me.Initialize();

	//me.SetN(30);
	//me.RetrieveDataSingleThread();
	////me.RetrieveDataMultiThread();
	//map<string, map<string, Vector>> result = me.RunResearch();
	////result["CAAR_mean"]["Beat"].display();
	//plot_caar(result["CAAR_mean"]);

	me.RunMenu();

	me.ClearAll();

}
