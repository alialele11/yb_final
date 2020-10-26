#pragma once
#include <iostream>
#include "date.h"
#include <memory>
using namespace std;

enum class Comparison {
    Less,
    LessOrEqual,
    Greater,
    GreaterOrEqual,
    Equal,
    NotEqual,
};

enum class LogicalOperation {
    Or,
    And,
};

class Node {
public:
virtual bool Evaluate(const Date& date, const string& event) const = 0;
};
class EmptyNode : public Node {
    bool Evaluate(const Date& date, const string& event) const override;
};
class DateComparisonNode : public Node {
public:
    DateComparisonNode(const Comparison& cm, const Date& date);
    bool Evaluate(const Date& date, const string& event) const override;
private:
    const Comparison cm_;
    const Date date_;
};
class EventComparisonNode : public Node {
public:
    EventComparisonNode(const Comparison& cm, const string& event);
    bool Evaluate(const Date& date, const string& event) const override;
private:
    const Comparison cm_;
    const string event_;
};
class LogicalOperationNode : public Node {
    public:
        LogicalOperationNode(const LogicalOperation& op, shared_ptr<Node> left, shared_ptr<Node> right);
        bool Evaluate(const Date& date, const string& event) const override;
    private:
    const LogicalOperation op_;
    shared_ptr<Node> left_;
    shared_ptr<Node> right_;
};
