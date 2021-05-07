#pragma once

#include "date.h"

#include <iostream>
#include<string>

using namespace std;

class Entry {
public:
	Entry(const Date& d, const string& s) :
		D(d),
		Event(s) {
	}
	Date GetDate() const;
	string GetEvent() const;
private:
	const Date D;
	const string Event;
};

ostream& operator<<(ostream& os, const Entry& entry);
bool operator!=(const Entry& lh, const Entry& rh);
