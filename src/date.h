#pragma once

#include <iostream>
#include <iomanip>

using namespace std;

class Date {
public:
	Date(const int& y, const int& m, const int& d) :
		Year(y),
		Month(m),
		Day(d) {
	}
	int GetYear() const;
	int GetMonth() const;
	int GetDay() const;
private:
	const int Year;
	const int Month;
	const int Day;
};

Date ParseDate(istream& is);

bool operator<(const Date& left, const Date& right);
bool operator>(const Date& left, const Date& right);
bool operator==(const Date& left, const Date& right);
bool operator!=(const Date& left, const Date& right);
bool operator<=(const Date& left, const Date& right);
bool operator>=(const Date& left, const Date& right);

ostream& operator<<(ostream& stream, const Date& date);
