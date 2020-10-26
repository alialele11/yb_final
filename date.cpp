#include "date.h"
#include <iomanip>
using namespace std;
//определение класса ДАТА
Date :: Date(const int& year_input, const int& month_input, const int& day_input) {
        //проверяем месяц
        if (month_input < 1 || month_input > 12) {
            throw invalid_argument("Month value is invalid: " + to_string(month_input));
        }
        else {
            //проверяем день
            if (day_input < 1 || day_input > 31) {
                throw invalid_argument("Day value is invalid: " + to_string(day_input));
            }
            else {
                year = year_input;
                month = month_input;
                day = day_input;
            }
        }
    }
//определение метода получения года
int Date :: GetYear() const {
        return year;
}
//определение метода получения месяца
int Date :: GetMonth() const {
        return month;

}
//определение метода получения дня
int Date :: GetDay() const {
        return day;
}
//определение оператора 'меньше' 
bool operator<(const Date& lhs, const Date& rhs) {
    if (lhs.GetYear() == rhs.GetYear()) {
        if (lhs.GetMonth() == rhs.GetMonth()) {
            return lhs.GetDay() < rhs.GetDay();
        }
        else {
            return lhs.GetMonth() < rhs.GetMonth();
        }
    }
    else {
        return lhs.GetYear() < rhs.GetYear();
    }
}
//определение оператора меньше или равно
bool operator<=(const Date& lhs, const Date& rhs) {
    if (lhs.GetYear() == rhs.GetYear()) {
        if (lhs.GetMonth() == rhs.GetMonth()) {
            return lhs.GetDay() <= rhs.GetDay();
        }
        else {
            return lhs.GetMonth() < rhs.GetMonth();
        }
    }
    else {
        return lhs.GetYear() < rhs.GetYear();
    }
}
//определение оператора 'равно'
bool operator ==(const Date& r, const Date& s) {
    return r.GetYear() == s.GetYear() && r.GetMonth() == s.GetMonth() && r.GetDay() == s.GetDay();
}
bool operator !=(const Date& r, const Date& s) {
    return r.GetYear() != s.GetYear() || r.GetMonth() != s.GetMonth() || r.GetDay() != s.GetDay();
}
//определение оператора вывода в поток
ostream& operator <<(ostream& out, const Date& d) {
    out << setw(4) << setfill('0') << d.GetYear() << '-';
    out << setw(2) << setfill('0') << d.GetMonth() << '-';
    out << setw(2) << setfill('0') << d.GetDay();
    return out;
}
//определение функции считывания ДАТЫ
Date ParseDate(istream& in) {
    string line;
    in >> line;
    stringstream input(line);
    int year_input;
    int month_input;
    int day_input;
    if (input >> year_input && input.peek() == '-' && input.ignore(1) && input >> month_input && input.peek() == '-' && input.ignore(1) && input >> day_input && input.peek() == EOF) {
       Date d(year_input, month_input, day_input);
       return d;
    }
    //выбиваем исключение, если формат не корректный
    else {
        throw invalid_argument("Wrong date format: " + line);
    }
}
