#include "node.h"
#include "date.h"
using namespace std;

bool EmptyNode :: Evaluate(const Date& date, const string& event) const {
	return true;
}
DateComparisonNode::DateComparisonNode(const Comparison& cm, const Date& date) : cm_(cm), date_(date){}
bool DateComparisonNode :: Evaluate(const Date& date, const string& event) const {
	if (cm_ == Comparison::Less) {
		if (date < date_) {
			return true;
		}
		else {
			return false;
		}
	}
	else if(cm_ == Comparison::LessOrEqual) {
		if (date <= date_) {
			return true;
		}
		else {
			return false;
		}
	}
	else if (cm_ == Comparison::Greater) {
		if (date_ < date) {
			return true;
		}
		else {
			return false;
		}
	}
	else if (cm_ == Comparison::GreaterOrEqual) {
		if (date_ <= date) {
			return true;
		}
		else {
			return false;
		}
	}
	else if (cm_ == Comparison::Equal) {
		if (date_ == date) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		if (date_ != date) {
			return true;
		}
		else {
			return false;
		}
	}
}
EventComparisonNode :: EventComparisonNode(const Comparison& cm, const string& event) : cm_(cm), event_(event){}
bool EventComparisonNode :: Evaluate(const Date& date, const string& event) const {
	if (cm_ == Comparison::Less) {
		if (event < event_) {
			return true;
		}
		else {
			return false;
		}
	}
	else if (cm_ == Comparison::LessOrEqual) {
		if (event <= event_) {
			return true;
		}
		else {
			return false;
		}
	}
	else if (cm_ == Comparison::Greater) {
		if (event_ < event) {
			return true;
		}
		else {
			return false;
		}
	}
	else if (cm_ == Comparison::GreaterOrEqual) {
		if (event_ <= event) {
			return true;
		}
		else {
			return false;
		}
	}
	else if (cm_ == Comparison::Equal) {
		if (event_ == event) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		if (event_ != event) {
			return true;
		}
		else {
			return false;
		}
	}
}
LogicalOperationNode :: LogicalOperationNode(const LogicalOperation& op, shared_ptr<Node> left, shared_ptr<Node> right) : op_(op), left_(left), right_(right){}
bool LogicalOperationNode::Evaluate(const Date& date, const string& event) const {
	bool result;
	if (op_ == LogicalOperation::And){
		result = left_->Evaluate(date, event) * right_->Evaluate(date, event);
	}
	if (op_ == LogicalOperation::Or) {
		result = left_->Evaluate(date, event) + right_->Evaluate(date, event);
	}
	return result;
}
