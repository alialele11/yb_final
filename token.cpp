#include "token.h"
#include <exception>
#include <vector>
using namespace std;

vector<Token> Tokenize(istream& cl) {
    vector<Token> tokens;
    char c;
    while (cl >> c) {
        //считываем дату из потока и добавляем соответствующий токен с типом ДАТА
        if (isdigit(c)) {
            string date(1, c);
            for (int i = 0; i < 3; ++i) {
                while (isdigit(cl.peek())) {
                    date += cl.get();
                }
                if (i < 2) {
                    date += cl.get(); // Consume '-'
                }
            }
            tokens.push_back({ date, TokenType::DATE });
        }
        //считываем событие и создаем соответствующий токен с типом СОБЫТИЕ
        else if (c == '"') {
            string event;
            getline(cl, event, '"');
            tokens.push_back({ event, TokenType::EVENT });
        }
        //если строка начинается со слова 'date', создаем токен с типом СТОЛБЕЦ и значением date
        else if (c == 'd') {
            if (cl.get() == 'a' && cl.get() == 't' && cl.get() == 'e') {
                tokens.push_back({ "date", TokenType::COLUMN });
            }
            //кидаем искючение при неправильном формате
            else {
                throw logic_error("Unknown token");
            }
        }
        //если строка начинается со слова 'event', создаем токен с типом СТОЛБЕЦ и значением event
        else if (c == 'e') {
            if (cl.get() == 'v' && cl.get() == 'e' && cl.get() == 'n' &&
                cl.get() == 't') {
                tokens.push_back({ "event", TokenType::COLUMN });
            }
            //кидаем искючение при неправильном формате
            else {
                throw logic_error("Unknown token");
            }
        }
        //если предполагаются сложение или умножение условий, считываем их в токены с соответствующими значениями и типом ЛОГИЧЕСКИЙ ОПЕРАТОР
        else if (c == 'A') {
            if (cl.get() == 'N' && cl.get() == 'D') {
                tokens.push_back({ "AND", TokenType::LOGICAL_OP });
            }
            else {
                throw logic_error("Unknown token");
            }
        }
        else if (c == 'O') {
            if (cl.get() == 'R') {
                tokens.push_back({ "OR", TokenType::LOGICAL_OP });
            }
            else {
                throw logic_error("Unknown token");
            }
        }
        //считываются в токены синтаксические дополнения, скобки
        else if (c == '(') {
            tokens.push_back({ "(", TokenType::PAREN_LEFT });
        }
        else if (c == ')') {
            tokens.push_back({ ")", TokenType::PAREN_RIGHT });
        }
        //если вводятся операторы (больше, меньше, равно, не равно), считываем их в токе с соответствующим значением и типом КОМПАЙР
        else if (c == '<') {
            if (cl.peek() == '=') {
                cl.get();
                tokens.push_back({ "<=", TokenType::COMPARE_OP });
            }
            else {
                tokens.push_back({ "<", TokenType::COMPARE_OP });
            }
        }
        else if (c == '>') {
            if (cl.peek() == '=') {
                cl.get();
                tokens.push_back({ ">=", TokenType::COMPARE_OP });
            }
            else {
                tokens.push_back({ ">", TokenType::COMPARE_OP });
            }
        }
        else if (c == '=') {
            if (cl.get() == '=') {
                tokens.push_back({ "==", TokenType::COMPARE_OP });
            }
            else {
                throw logic_error("Unknown token");
            }
        }
        else if (c == '!') {
            if (cl.get() == '=') {
                tokens.push_back({ "!=", TokenType::COMPARE_OP });
            }
            else {
                throw logic_error("Unknown token");
            }
        }
    }

    return tokens;
}
