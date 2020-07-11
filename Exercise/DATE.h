#pragma once

#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int cntLeapYear(int year);

class Ngay 
{
private:
	
	int ngay, thang, nam;

public:
	Ngay();
	Ngay(int, int, int);
	Ngay(int);
	friend ostream& operator<< (ostream& os, Ngay x);
	friend Ngay operator+ (Ngay x, Ngay y);
	Ngay operator+(int x);
	Ngay operator-(int x);
	friend Ngay operator+(int x, Ngay y);
	friend Ngay operator-(int x, Ngay y);
	friend Ngay operator-(Ngay x, Ngay y);
	bool operator >(Ngay x);
	static int Date[];
};

