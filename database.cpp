#include "database.h"
#include <iostream>
#include <algorithm>
using namespace std;
//определяем функцию добавления события в базу
void Database :: Add(const Date& date, const string& event) {
    if(data_set[date].find(event) == data_set[date].end()){
       data_vec[date].push_back(event);
       data_set[date].insert(event);
    }
}
//определяем функцию удаления события по условию
int Database ::RemoveIf(function<bool(Date, string)> fun) {
    int len;
    int count = 0;
    vector<Date> unnecessary;
    for (auto it = data_vec.begin(); it != data_vec.end(); it++) {
        len = it->second.size();
        auto tem = stable_partition(it->second.begin(), it->second.end(), [it, fun](string ev){return !fun(it->first, ev);});
        for(auto temp = tem; temp != it->second.end(); ++temp){
        	data_set[it->first].erase(*temp);
        }
        it->second.erase(tem, it->second.end());
        count += len - it->second.size();
        if (it->second.size() == 0) {
            unnecessary.push_back(it->first);
        }
    }
    for (auto item : unnecessary) {
        data_vec.erase(item);
    }
    unnecessary.clear();
    return count;
}

vector<pair<Date, string>> Database :: FindIf(function<bool(Date, string)> fun) const {
    vector<pair<Date, string>> result;
    for (auto it = data_vec.begin(); it != data_vec.end(); ++it) {
        for (auto ti = it->second.begin(); ti != it->second.end(); ++ti) {
            if (fun(it->first, *ti)) {
                result.push_back(make_pair(it->first, *ti));
            }
        }
    }
    return result;
}
void Database :: Print(ostream& out) const {
    for (auto item : data_vec) {
        for (auto ev : item.second) {
            out << item.first << " " << ev << endl;
        }
    }
}
pair<Date, string> Database::Last(const Date& d) const{
    auto it = data_vec.lower_bound(d);
    if (data_vec.empty()) {
    	throw invalid_argument("");
    }
    if (it == data_vec.begin() && d < it->first) {
        throw invalid_argument("");
    }
    if (it == data_vec.end() || d < it->first) {
        it = prev(it);
    }
    vector<string> vec = it -> second;
    return make_pair(it->first, *prev(vec.end()));
}
ostream& operator <<(ostream& out, pair<Date, string> t) {
    out << t.first << " " << t.second;
    return out;
}
