#include "database.h"

#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <set>
#include <vector>

using namespace std;

void Database::Add(const Date& date, const string& event) {
	auto Pair = DB_set[date].insert(event);
	if(Pair.second) {
		DB_vector[date].push_back(event);
	}
}

void Database::Print(ostream& os) const {
	for(auto it_1 = DB_vector.begin(); it_1 != DB_vector.end();) {
		for(auto it_2 = it_1->second.begin(); it_2 != it_1->second.end();) {
			os << it_1->first << " " << *it_2 << endl;
			++it_2;
		}
		++it_1;
	}
}

Entry Database::Last(const Date& date) const {
	auto it = DB_vector.upper_bound(date);
	if(it == DB_vector.begin()) {
		throw invalid_argument("");
	}
	--it;
	Entry entry(it->first, it->second.back());
	return entry;
}
