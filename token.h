#pragma once
#include <sstream>
#include <vector>
#include <memory>
using namespace std;
//типы токенов
enum class TokenType {
	//отвечает за дату
	DATE,
	//отвечает за событие
	EVENT,
	//отвечает за то, что нужно найти/удалить событие или дату
	COLUMN,
	//отвечает за сложение и умножение условий
	LOGICAL_OP,
	//отвечает за логические операторы
	COMPARE_OP,
	//отвечают за скобки
	PAREN_LEFT,
	PAREN_RIGHT,
};
//объявляем класс Токен
struct Token {
	const string value;
	const TokenType type;
};
//объявляем функцию Tokenize
vector<Token> Tokenize(istream& cl);

