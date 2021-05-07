#include "date.h"

#include <iostream>
#include <vector>

using namespace std;

// Date methods definition
int Date::GetYear() const {
	return Year;
}
int Date::GetMonth() const {
	return Month;
}
int Date::GetDay() const {
	return Day;
}

Date ParseDate(istream& is) {
	int year, month, day;
	is >> year;
	is.ignore(1);
	is >> month;
	is.ignore(1);
	is >> day;
	is.ignore(1);
	Date date(year, month, day);
	return date;
}

bool operator<(const Date& left, const Date& right) {
	return vector<int>{left.GetYear(), left.GetMonth(), left.GetDay()} <
			vector<int>{right.GetYear(), right.GetMonth(), right.GetDay()};
}

bool operator>(const Date& left, const Date& right) {
	return vector<int>{left.GetYear(), left.GetMonth(), left.GetDay()} >
			vector<int>{right.GetYear(), right.GetMonth(), right.GetDay()};
}

bool operator==(const Date& left, const Date& right) {
	return vector<int>{left.GetYear(), left.GetMonth(), left.GetDay()} ==
			vector<int>{right.GetYear(), right.GetMonth(), right.GetDay()};
}

bool operator!=(const Date& left, const Date& right) {
	return vector<int>{left.GetYear(), left.GetMonth(), left.GetDay()} !=
			vector<int>{right.GetYear(), right.GetMonth(), right.GetDay()};
}

bool operator<=(const Date& left, const Date& right) {
	return vector<int>{left.GetYear(), left.GetMonth(), left.GetDay()} <=
			vector<int>{right.GetYear(), right.GetMonth(), right.GetDay()};
}

bool operator>=(const Date& left, const Date& right) {
	return vector<int>{left.GetYear(), left.GetMonth(), left.GetDay()} >=
			vector<int>{right.GetYear(), right.GetMonth(), right.GetDay()};
}

ostream& operator<<(ostream& stream, const Date& date) {
	stream << setw(4) << setfill('0') << date.GetYear() <<
			'-' << setw(2) << setfill('0') << date.GetMonth() <<
			'-' << setw(2) << setfill('0') << date.GetDay();
	return stream;
}
