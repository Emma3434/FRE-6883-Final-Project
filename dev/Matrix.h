#pragma once
#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <cmath>
#include <iostream>
#include "Vector.h"
#include "StockData.h"
using namespace std;

class Matrix
{
public:
	vector<Vector> data;
	Matrix(vector<StockData> stock_list)
	{
		for (auto iter : stock_list)
		{
			data.push_back(iter.abnormal_return);
		}
	};
	void append(Vector& V);
	Vector sum();
	Vector mean();
	Vector std();
};



#endif
