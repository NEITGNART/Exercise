#include "DATE.h"
int cntLeapYear(int year) {
	int cnt(0);
	for (int i = 1; i < year; ++i) {
		if ((i % 4 == 0 && i % 100 != 0) || i % 400 == 0) {
			++cnt;
		}
	}
	return cnt;
}

int cntDayofYear(int day, int month, int year) {
	int cnt(0);
	for (int i = 0; i < month; ++i) {
		cnt += Ngay::Date[i];
	}
	cnt += cntLeapYear(year) + (day + year * 365);
	return cnt;
}

int Ngay::Date[] = { 31,28,31,30,31,30, 31, 31,30,31, 30,31 };
void setNgayThangNam(int& day, int& month, int& year) {
	day = abs(day); month = abs(month); year = abs(year);
	
	int reDay = day % 365;
	// reDay range from [1...365];

	int cnt = 0;
	// remainder must range from [1...365]
	while (reDay > 30) {
		reDay = reDay - Ngay::Date[cnt];
		++cnt;
	}
	day = reDay;
	
	month = month + cnt;
	if (month > 12) {
		year += month/12;
		month = month % 12;
	}
	int divDay = day / 365;
	
	year = year + divDay;
}

void setNgayThanhNgayThangNam(int &day, int &month ,int &year, int &ngay) {

	ngay = 0, month = 1, year = 1;
	int reDay = day % 365;
	int cnt = 0;
	// remainder must range from [1...365]
	while (reDay > 30) {
		reDay = reDay - Ngay::Date[cnt % 12];
		++cnt;
	}
	ngay += reDay;
	month += cnt;
	if (month > 12) {
		year += month / 12;
		month = month % 12;
	}
	int divDay = day / 365;

	year +=divDay;
	
}
Ngay::Ngay() {
	ngay = 1;
	thang = 1;
	nam = 1;
}
Ngay::Ngay(int ngay, int thang, int nam) {

	this->ngay = abs(ngay);
	setNgayThangNam(ngay, thang, nam);
	this->ngay = ngay;
	this->thang = thang;
	this->nam = nam;
}


Ngay::Ngay(int ngay) {

	// initialization day, month and year equal 1-1-1; 
	int day, month, year;
	setNgayThanhNgayThangNam(ngay, month, year, day);
	this->ngay = day;
	this->thang = month;
	this->nam = year;
}

ostream& operator<< (ostream& os, Ngay object) {
	os << object.ngay << ":" << object.thang << ":" << object.nam; // casting to ostringstream
	return os;
}

Ngay operator+(Ngay x, Ngay y) {
	Ngay z;
	int day = 0, month = 0, year = 0;
	day += (y.ngay + x.ngay);
	int dayOfMonth = Ngay::Date[ (y.thang+x.thang-1)%12 ];

	if (day > dayOfMonth) {
		day = day - dayOfMonth;
		month += 1;
	}
	month += y.thang + x.thang;
	if (month > 12) {
		year += (month / 12);
		month %= 12;
	}
	year += y.nam + x.nam;
	z.ngay = day; z.thang = month; z.nam = year;
	return z;
}

Ngay Ngay::operator+(int x) {
	
	int day, month, year;
	setNgayThanhNgayThangNam(x, month, year, day);
	int dayLeapYear = cntLeapYear(year);
	day -= dayLeapYear;
	Ngay y(day, month, year);
	return  y + (*this);
}

Ngay operator+(int x, Ngay y) {

	int day, month, year;
	setNgayThanhNgayThangNam(x, month, year, day);
	day--; month--; year--;
	int dayLeapYear = cntLeapYear(year);
	day -= dayLeapYear;
	Ngay z(day, month, year);
	return z + y;
}


void setNgayThanhNgayThangNam1(int& ngay,int& day, int& month, int& year) {
	year = 0; month = 0; day = 0;
	year += (ngay / 365);
	int i = 0; 
	int re = ngay % 365;
	while (re > 30) {
		re = re - Ngay::Date[i];
		++i;
	}
	month += i;
	day += re;
}

Ngay operator-(Ngay x, Ngay y) {
	Ngay z;
	int day(0), month(0), year(0);	
	int dayofX = cntDayofYear(x.ngay, x.thang, x.nam);
	int dayofY = cntDayofYear(y.ngay, y.thang, y.nam);
	day += dayofX - dayofY + cntLeapYear(x.nam) + cntLeapYear(y.nam);
	int temp;
	setNgayThanhNgayThangNam1(day,temp, month, year);
	temp -= cntLeapYear(year);
	z.ngay = temp; z.thang = month; z.nam = year;
	return z;
}


Ngay operator-(int x, Ngay y) {
	Ngay z;
	int day(0), month(0), year(0);
	day += cntDayofYear(y.ngay, y.thang, y.nam);
	day = (x - day);
	int tmp = 0;
	setNgayThanhNgayThangNam1(day, tmp, month, year);
	z.ngay = (tmp - cntLeapYear(year) +1); z.thang = month+1; z.nam = year+1;
	return z;
}	

bool Ngay::operator >(Ngay x) {
	if (nam > x.nam) return true;
	if (thang > x.thang) return true;
	if (ngay > x.ngay) return true;
	
	return false;
}
Ngay Ngay::operator-(int x) {
	Ngay z;
	int day(0), month(0), year(0);
	int sumOfDay = abs( cntDayofYear(ngay, thang, nam) - x );

	setNgayThanhNgayThangNam1(sumOfDay, day, month, year);
	z.ngay = day; z.thang = month + 1; z.nam = year + 1;
	return z;
}
