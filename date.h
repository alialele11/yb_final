#pragma once
#include <exception>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;
//объявление класса ДАТА
//включает день, месяц, год
class Date {
public:
    Date(const int& year_input, const int& month_input, const int& day_input);
    int GetYear() const;
    int GetMonth() const;
    int GetDay() const;
private:
    int year;
    int month;
    int day;
};
//объявление переопределения операторов для ДАТЫ равенства и сравнения
bool operator<(const Date& lhs, const Date& rhs);
bool operator ==(const Date& r, const Date& s);
bool operator !=(const Date& r, const Date& s);
bool operator<=(const Date& lhs, const Date& rhs);
//объявление переопределения опреатора вывода в поток
ostream& operator <<(ostream& out, const Date& d);
//объявление функции считывания даты
Date ParseDate(istream& in);
