#pragma once
#ifndef VECTORCLASS_H
#define VECTORCLASS_H

#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

class Vector
{
public:
	vector<double> data;
	Vector() {};
	Vector(vector<double> data_) :data(data_) {};
	~Vector() {};
	int size();
	void push_back(const double& val);
	double back();
	Vector pct_change();
	double sum();
	Vector cumsum();

	Vector operator-(Vector& a)
	{
		int d = a.size();
		vector<double> V(d);
		for (int i = 0; i < d; i++)
		{
			V[i] = data[i] - a[i];
		};
		return Vector(V);
	};
	Vector operator+(Vector& a)
	{
		int d = a.size();
		vector<double> V(d);
		for (int i = 0; i < d; i++)
		{
			V[i] = data[i] + a[i];
		};
		return Vector(V);
	};

	double operator[](int const idx)
	{
		return data[idx];
	};

};


#endif 