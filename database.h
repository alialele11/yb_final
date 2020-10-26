#pragma once
#include "date.h"
#include <map>
#include <set>
#include <vector>
#include <iomanip>
#include <functional>
using namespace std;
class Database {
public:
    void Add(const Date& date, const string& event);
    int RemoveIf(function<bool(Date, string)> fun); //???????????????????????????????
    vector<pair<Date, string>> FindIf(function<bool(Date, string)> fun) const; //????????????????????
    void Print(ostream& out) const;
    pair<Date, string> Last(const Date& d) const;
private:
    map<Date, set<string>> data_set;
    map<Date, vector<string>> data_vec;
};
ostream& operator <<(ostream& out, pair<Date, string> t);
