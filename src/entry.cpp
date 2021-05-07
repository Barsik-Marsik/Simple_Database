#include "entry.h"

#include <iostream>
#include<string>

using namespace std;

Date Entry::GetDate() const {
	return D;
}

string Entry::GetEvent() const {
	return Event;
}

ostream& operator<<(ostream& os, const Entry& entry) {
	os << entry.GetDate() << " " << entry.GetEvent();
	return os;
}

bool operator!=(const Entry& lh, const Entry& rh) {
	return lh.GetDate() != rh.GetDate() && lh.GetEvent() != rh.GetEvent();
}
