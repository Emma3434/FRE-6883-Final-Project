
#ifndef FetchData_H
#define FetchData_H

#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <locale>
#include <iomanip>
#include <fstream>

#include "StockData.h"
//#include "curl.h"
#include "curl/curl.h"



struct MemoryStruct {
	char* memory;
	size_t size;
};


//int write_data(void* ptr, int size, int nmemb, FILE* stream)
//{
//	size_t written;
//	written = fwrite(ptr, size, nmemb, stream);
//	return written;
//}


//void* myrealloc(void* ptr, size_t size)
//{
//	/* There might be a realloc() out there that doesn't like reallocting
//	NULL pointers, so we take care of it here */
//	if (ptr)
//		return realloc(ptr, size);
//	else
//		return malloc(size);
//}
//
//int write_data2(void* ptr, size_t size, size_t nmemb, void* data)
//{
//	size_t realsize = size * nmemb;
//	struct MemoryStruct* mem = (struct MemoryStruct*)data;
//	mem->memory = (char*)myrealloc(mem->memory, mem->size + realsize + 1);
//	if (mem->memory) {
//		memcpy(&(mem->memory[mem->size]), ptr, realsize);
//		mem->size += realsize;
//		mem->memory[mem->size] = 0;
//	}
//	return  realsize;
//}
//
//string getTimeinSeconds(string Time)
//{
//	std::tm t = { 0 };
//	std::istringstream ssTime(Time);
//	char time[100];
//	memset(time, 0, 100);
//	if (ssTime >> std::get_time(&t, "%Y-%m-%dT%H:%M:%S"))
//	{
//		cout << std::put_time(&t, "%c %Z") << "\n" << std::mktime(&t) << "\n";
//		sprintf(time, "%lld", mktime(&t));
//		return string(time);
//	}
//	else
//	{
//		cout << "Parse failed \n";
//		return "";
//	}
//}

//int fetch_data(StockData* sd, string startTime, string endTime)
//{
//	//string startTime = getTimeinSeconds("2021-01-01T16:00:00");
//	//string endTime = getTimeinSeconds("2021-12-31T16:00:00");
//	string symbol = sd->ticker;
//
//	struct MemoryStruct data;
//	data.memory = NULL;
//	data.size = 0;
//	FILE* fp1;
//	const char resultfilename[FILENAME_MAX] = "Results.txt";
//
//	// declaration of a pointer to an curl object
//	CURL* handle;
//
//	// result of the whole process
//	CURLcode result;
//	// set up the program environment that libcurl needs
//	curl_global_init(CURL_GLOBAL_ALL);
//
//	// curl_easy_init() returns a CURL easy handle
//	handle = curl_easy_init();
//
//	// if everything's all right with the easy handle...
//	if (handle)
//	{
//		string sCookies, sCrumb;
//		fp1 = fopen(resultfilename, "w");
//
//		string urlA = "https://query1.finance.yahoo.com/v7/finance/download/";
//
//		string urlB = "?period1=";
//		string urlC = "&period2=";
//		string urlD = "&interval=1d&events=history";
//		string url = urlA + symbol + urlB + startTime + urlC + endTime;
//		const char* cURL = url.c_str();
//		curl_easy_setopt(handle, CURLOPT_URL, cURL);
//
//
//		fprintf(fp1, "%s\n", symbol.c_str());
//		curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data);
//		curl_easy_setopt(handle, CURLOPT_WRITEDATA, fp1);
//		result = curl_easy_perform(handle);
//
//		fprintf(fp1, "%c", '\n');
//		// Check for errors */
//		if (result != CURLE_OK)
//		{
//			// if errors have occurred, tell us what is wrong with 'result'
//			fprintf(stderr, "curl_easy_perform() failed: % s\n", curl_easy_strerror(result));
//			return 1;
//		}
//
//
//		curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data2);
//		curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void*)&data);
//		result = curl_easy_perform(handle);
//		if (result != CURLE_OK)
//		{
//			// if errors have occurred, tell us what is wrong with 'result'
//			fprintf(stderr, "curl_easy_perform() failed: % s\n", curl_easy_strerror(result));
//			return 1;
//		}
//
//
//		stringstream sData;
//		sData.str(data.memory);
//		string sValue, sDate;
//		double dValue = 0;
//		string line;
//		getline(sData, line);
//		//cout << symbol << endl;
//		while (getline(sData, line)) {
//			sDate = line.substr(0, line.find_first_of(',')); // get Date column
//			line.erase(line.find_last_of(',')); // 
//			sValue = line.substr(line.find_last_of(',') + 1); // get Adj Close column
//			dValue = strtod(sValue.c_str(), NULL); // str to double, for Adj Close column
//			cout << sDate << " " << std::fixed << setprecision(6) << dValue << endl;
//		}
//
//		fclose(fp1);
//		free(data.memory);
//		data.size = 0;
//
//		//sd->data = data;
//	}
//	else
//	{
//		fprintf(stderr, "Curl init failed!\n");
//		return 1;
//	}
//
//	// cleanup since you've used curl_easy_init
//	curl_easy_cleanup(handle);
//	// release resources acquired by curl_global_init()
//	curl_global_cleanup();
//
//	return 0;
//}
#endif