//============================================================================
// Name        : White_Final.cpp
// Author      : barsik.marsik.11@gmail.com
// Version     :
// Copyright   :
// Description :
//============================================================================
#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

class Date {
public:
	// Если значения месяца и дня не проходят проверку на валидность, то выбрасываются исключения
	Date(int new_year, int new_month, int new_day) {
		Year = new_year;
		if (new_month < 1 || new_month > 12) {
			throw logic_error("Month value is invalid: " + to_string(new_month));
		}
		Month = new_month;
		if (new_day < 1 || new_day > 31) {
			throw logic_error("Day value is invalid: " + to_string(new_day));
		}
		Day = new_day;
	}
	int GetYear() const { return Year; }
	int GetMonth() const { return Month; }
	int GetDay() const { return Day; }
private:
	int Year;
	int Month;
	int Day;
};

bool operator<(const Date& lhs, const Date& rhs) {
	if (lhs.GetYear() == rhs.GetYear()) {
		if (lhs.GetMonth() == rhs.GetMonth()) {
			return lhs.GetDay() < rhs.GetDay();
		} else {
			return lhs.GetMonth() < rhs.GetMonth();
		}
	} else {
		return lhs.GetYear() < rhs.GetYear();
	}
}
ostream& operator<<(ostream& stream, const Date& date) {
	stream << setw(4) << setfill('0') << date.GetYear() << "-" <<
			setw(2) << setfill('0') << date.GetMonth() << "-" <<
			setw(2) << setfill('0') << date.GetDay();
	return stream;
}
class Database {
public:
	void AddEvent(const Date& date, const string& event) {
		Storage[date].insert(event);
	}
	bool DeleteEvent(const Date& date, const string& event) {
		if (Storage.count(date) > 0 && Storage[date].count(event) > 0) {
			Storage[date].erase(event);
			return true;
		} else {
			return false;
		}
	}
	int  DeleteDate(const Date& date) {
		if (Storage.count(date) == 0) {
			return 0;
		} else {
			const int deleted_events = Storage[date].size();
			Storage.erase(date);
			return deleted_events;
		}
	}
	set<string> Find(const Date& date) const {
		if (Storage.count(date) > 0) {
			return Storage.at(date);
		} else {
			return {};
		}
	}
	void Print() const {
		for (const auto& item : Storage) {
			for (const auto& s_event : item.second) {
				cout << item.first << " " << s_event << endl;
			}
		}
	}
private:
	map<Date, set<string>> Storage;
};
Date ParseDate (const string& date) {
	istringstream date_stream(date);
	bool ok = true;

	int year;
	ok = ok && (date_stream >> year);
	ok = ok && (date_stream.peek() == '-');
	date_stream.ignore(1);

	int month;
	ok = ok && (date_stream >> month);
	ok = ok && (date_stream.peek() == '-');
	date_stream.ignore(1);

	int day;
	ok = ok && (date_stream >> day);
	ok = ok && date_stream.eof();

	if (!ok) {
		throw logic_error("Wrong date format: " + date);
	}
	return Date(year, month, day);
}

int main() {
	try {
		Database db;
		string command_line;
		while (getline(cin, command_line)) {
			// Считайте команды с потока ввода и обработайте каждую
			stringstream ss(command_line);
			string command;
			ss >> command;
			if (command == "Add"){
				string str_date, event;
				ss >> str_date >> event;
				const Date date = ParseDate(str_date);
				db.AddEvent(date, event);
			} else if (command == "Del") {
				string str_date;
				ss >> str_date;
				string event;
				if (!ss.eof()) {
					ss >> event;
				}
				const Date date = ParseDate (str_date);
				if (event.empty()) {
					cout << "Deleted " << db.DeleteDate(date) << " events" << endl;
				} else {
					if (db.DeleteEvent(date, event)) {
						cout << "Deleted successfully" << endl;
					} else {
						cout << "Event not found" << endl;
					}
				}
			} else if (command == "Find") {
				string str_date;
				ss >> str_date;
				const Date date = ParseDate(str_date);
				for (const string& event : db.Find(date)) {
					cout << event << endl;
				}
			} else if (command == "Print") {
				db.Print();
			} else if (!command.empty()){
				throw logic_error("Unknown command: " + command);
			}
		}
	} catch (exception& ex) {
		cout << ex.what() << endl;
	}
	return 0;
}
