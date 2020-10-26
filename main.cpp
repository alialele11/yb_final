#include "date.h"
#include "database.h"
#include "condition_parser.h"
#include "node.h"
#include "test_runner.h"
#include <iostream>
#include <stdexcept>

using namespace std;

//считываем событие
string ParseEvent(istream& is) {
    // Реализуйте эту функцию
    string event;
    getline(is,event);
    auto first = event.find_first_not_of(" ");
    event.erase(0, first);
    return event;
}

//юнит-тесты
void TestAll();

int main() {
    //запуск юнит-тестов
    TestAll();
    //заводим базу данных
    Database db;

    for (string line; getline(cin, line); ) {
        istringstream is(line);
        string command;
        is >> command;
        //команда == добавить
        if (command == "Add") {
            //считываем дату
            const auto date = ParseDate(is);
            //считываем событие
            const auto event = ParseEvent(is);
            db.Add(date, event);
        }
        //команда == напечатать
        else if (command == "Print") {
            db.Print(cout);
        }
        //команда == удалить
        else if (command == "Del") {
            //считываем условие
            auto condition = ParseCondition(is);
            //лямбда-функция для заданого условия
            auto predicate = [condition](const Date& date, const string& event) {
                return condition->Evaluate(date, event);
            }; 
            //считаем количество удалееных файлов
            int count = db.RemoveIf(predicate);
            cout << "Removed " << count << " entries" << endl;
        }
        // команда == найти
        else if (command == "Find") {
            //считываем условие
            auto condition = ParseCondition(is);
            //лямбда-функция для данного условия
            auto predicate = [condition](const Date& date, const string& event) {
                return condition->Evaluate(date, event);
            };
            //считываем в вектор элементы бд удовлетворящие условию и выводим их и количество
            const auto entries = db.FindIf(predicate);
            for (const auto& entry : entries) {
                cout << entry << endl;
            }
            cout << "Found " << entries.size() << " entries" << endl;
        }
        //оманда равна == вывести последний предыдущий
        else if (command == "Last") {
            // выводим запись с последним событием, случившимся не позже данной даты
            try {
                cout << db.Last(ParseDate(is)) << endl;
            }
            catch (invalid_argument&) {
                cout << "No entries" << endl;
            }
        }
        //пустая команда
        else if (command.empty()) {
            continue;
        }
        //некорректная команда, исключение
        else {
            throw logic_error("Unknown command: " + command);
        }
    }

    return 0;
}
//тестируем корректность считывания события
void TestParseEvent() {
    {
        istringstream is("event");
        AssertEqual(ParseEvent(is), "event", "Parse event without leading spaces");
    }
    {
        istringstream is("   sport event ");
        AssertEqual(ParseEvent(is), "sport event ", "Parse event with leading spaces");
    }
    {
        istringstream is("  first event  \n  second event");
        vector<string> events;
        events.push_back(ParseEvent(is));
        events.push_back(ParseEvent(is));
        AssertEqual(events, vector<string>{"first event  ", "second event"}, "Parse multiple events");
    }
}
//доп юнит-тесты
void TestAll() {
    TestRunner tr;
    tr.RunTest(TestParseEvent, "TestParseEvent");
    tr.RunTest(TestParseCondition, "TestParseCondition");

}
