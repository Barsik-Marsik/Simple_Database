#include "node.h"

#include <iostream>
#include <memory>

using namespace std;

//EmptyNode Evaluate definition
bool EmptyNode::Evaluate(const Date& date, const string& event) const {
	return true;
}

//DateComparisonNode Evaluate definition
bool DateComparisonNode::Evaluate(const Date& date, const string& event) const {
	if(_cmp == Comparison::Less) {
		return date < _date;
	} else if(_cmp == Comparison::LessOrEqual) {
		return date <= _date;
	} else if(_cmp == Comparison::Greater) {
		return date > _date;
	} else if(_cmp == Comparison::GreaterOrEqual) {
		return date >= _date;
	} else if(_cmp == Comparison::Equal) {
		return date == _date;
	} else {
		return date != _date;
	}
}
//EventComparisonNode Evaluate definition
bool EventComparisonNode::Evaluate(const Date& date, const string& event) const {
	if(_cmp == Comparison::Less) {
		return event < _event;
	} else if(_cmp == Comparison::LessOrEqual) {
		return event <= _event;
	} else if(_cmp == Comparison::Greater) {
		return event > _event;
	} else if(_cmp == Comparison::GreaterOrEqual) {
		return event >= _event;
	} else if(_cmp == Comparison::Equal) {
		return event == _event;
	} else {
		return event != _event;
	}
}

//LogicalOperationNode Evaluate definition
bool LogicalOperationNode::Evaluate(const Date& date, const string& event) const {
	if(_Op == LogicalOperation::And) {
		return _left->Evaluate(date, event) && _right->Evaluate(date, event);
	} else {
		return _left->Evaluate(date, event) || _right->Evaluate(date, event);
	}
}
