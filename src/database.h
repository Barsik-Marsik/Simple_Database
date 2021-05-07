#pragma once

#include "date.h"
#include "entry.h"

#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <set>
#include <vector>
#include <stdexcept>

using namespace std;

class Database {
public:
	void Add(const Date& date, const string& event);
	void Print(ostream& os) const;
	template<typename Predicate>
	int RemoveIf(Predicate predicate);
	template<typename Predicate>
	vector<Entry> FindIf(Predicate predicate) const;
	Entry Last(const Date& date) const;
private:
	map<Date, set<string>> DB_set;
	map<Date, vector<string>> DB_vector;
};

template<class Predicate>
int Database::RemoveIf(Predicate predicate){
	int N = 0;
	for(auto it_1 = DB_vector.begin(); it_1 != DB_vector.end();) {
		const auto date = it_1->first;
		auto begin_ = stable_partition(it_1->second.begin(),
				it_1->second.end(),[date = date, predicate](const string& event) {
			return predicate(date, event);
		});
		N += begin_ - it_1->second.begin();
		if(begin_ != it_1->second.end()) {
			for(auto it_2 = it_1->second.begin(); it_2 != begin_;) {
				DB_set[date].erase(*it_2);
				++it_2;
			}
			it_1->second.erase(it_1->second.begin(), begin_);
			++it_1;
		} else if(begin_ == it_1->second.end()) {
			DB_set.erase(date);
			DB_vector.erase(it_1++);
		} else {
			++it_1;
		}
//		++it_1;
	}
	return N;
}

template<class Predicate>
vector<Entry> Database::FindIf(Predicate predicate) const {
	vector<Entry> entries;
	int N = 0;
	for(auto it_1 = DB_vector.begin(); it_1 != DB_vector.end();) {
		const auto date = it_1->first;
		for(auto it_2 = it_1->second.begin(); it_2 != it_1->second.end();) {
			if(predicate(date, *it_2)) {
				entries.push_back({date, *it_2});
				N++;
			}
			++it_2;
		}
		++it_1;
	}
	return entries;
}
