#pragma once

#include "date.h"
#include "comparison.h"

#include <iostream>
#include <memory>

using namespace std;

class Node {
public:
	Node(){};
	virtual ~Node(){};
	virtual bool Evaluate(const Date& date, const string& event) const = 0;
};

class EmptyNode : public Node {
public:
	EmptyNode(){};
	bool Evaluate(const Date& date, const string& event) const override;
};

class DateComparisonNode : public Node {
public:
	DateComparisonNode(const Comparison& cmp, const Date& date) :
		_cmp(cmp),
		_date(date) {
	}
	bool Evaluate(const Date& date, const string& event) const override;
private:
	const Comparison _cmp;
	const Date _date;
};

class EventComparisonNode : public Node {
public:
	EventComparisonNode(const Comparison& cmp, const string& event) :
		_cmp(cmp),
		_event(event) {
	}
	bool Evaluate(const Date& date, const string& event) const override;
private:
	const Comparison _cmp;
	const string _event;
};

class LogicalOperationNode : public Node {
public:
	LogicalOperationNode(const LogicalOperation& op,
			const shared_ptr<Node>& left,
			const shared_ptr<Node>& right) :
				_Op(op), _left(left), _right(right) {
	}
	bool Evaluate(const Date& date, const string& event) const override;
private:
	const LogicalOperation _Op;
	const shared_ptr<Node> _left;
	const shared_ptr<Node> _right;
};
