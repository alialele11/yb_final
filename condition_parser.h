#pragma once 
#include "node.h"
#include <memory>
#include <iostream>

using namespace std;
//объявление функции парсера условия с использованием "копии" Node
shared_ptr<Node> ParseCondition(istream& is);
//объявляем функцию теста для считывания 
void TestParseCondition();

