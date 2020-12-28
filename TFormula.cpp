#pragma once
#include"TFormula.h"
#include"TStack.h"
#include<string>
#include<iostream>
using namespace std;

// вырез из строки. 1: -(- = +, 2: +(- = -________________________
void TFormula::Change(int pos, int key) {
	// key = 0: -(- = + | key = 1: +(- = -
	if (key == 0) {
		Formula[pos] = '+';
		Formula[pos + 1] = Formula[pos + 3];
		for (int i = pos + 2; i < size - 3; i++) {
			Formula[i] = Formula[i + 3];
		}
	}
	else if (key == 1) {
		Formula[pos] = '-';
		Formula[pos + 1] = Formula[pos + 3];
		for (int i = pos + 2; i < size - 3; i++) {
			Formula[i] = Formula[i + 3];
		}
	}
	size = size - 3;
	Formula[size] = 0;
}

// подготовка строки Formula к основной части алгоритма, принцип в методе Change
void TFormula::Prepare(void) {
	for (int i = 0; i < size; i++) {
		if (Formula[i] == '-' && Formula[i] == '(' && Formula[i] == '-') {
			Change(i, 0);
		}
		else if (Formula[i] == '+' && Formula[i] == '(' && Formula[i] == '-') {
			Change(i, 1);
		}
	}
}

// определения приоритетности операций: 0 - (, 1 - ), 2 - + или -, 3 - * или /, 4 - операнды
int TFormula::Rank(char sym) {
	if (sym == '(')
		return(0);
	else if (sym == ')')
		return(1);
	else if (sym == '+' || sym == '-')
		return(2);
	else if (sym == '*' || sym == '/')
		return(3);
	else
		return(4);
}

// констурктор по умолчанию_______________________________________
TFormula::TFormula() {
	size = 0;
}

// констурктор копирования________________________________________
TFormula::TFormula(char form[]) {
	if (size >= 0 && size <= 255) {
		int form_size = 0;
		while (form[form_size] != 0)
			form_size++;
		size = form_size;
		for (int i = 0; i < size; i++) {
			Formula[i] = form[i];
		}
	}
	else {
		throw - 1;
	}
}

// проверка правильности______________________________________________
int TFormula::FormulaChecker(char * map[], int * size_of_map, int map_out_flag) { 
	int kolvo_mis = 0; // количество ошибок в расстановке скобок в формуле
	int kolvo_brckts = 0; // количество скобок
	char map_of_num[255]; // представление формулы через номера скобок(+ - открывает, - - закрывает)
	char map_of_pairs[255][2]; // таблица соответствия открывающихся скобок с закрывающимися через их номера
	int size_of_map_of_pairs = 0; // размер map_of_pairs
	TStack<int> check(255); // стек для работы алгоритма
	for (int i = 0; i < size; i++) { // создание массива с информацией о типе скобок и их порядковых номерах в формуле
		if (Formula[i] == '(') {
			map_of_num[kolvo_brckts] = kolvo_brckts + 1;
			kolvo_brckts++;
		}
		else if (Formula[i] == ')') {
			map_of_num[kolvo_brckts] = (kolvo_brckts + 1) * (-1);
			kolvo_brckts++;
		}
	}
	for (int i = 0; i < kolvo_brckts; i++) { // обработка массива через стек, выявление ошибок, создание таблицы вывода
		if (map_of_num[i] > 0) {
			check.Put(map_of_num[i]);
		}
		else {
			if (check.IsEmpty()) {
				map_of_pairs[size_of_map_of_pairs][0] = -1;
				map_of_pairs[size_of_map_of_pairs][1] = map_of_num[i] * (-1);
				size_of_map_of_pairs++;
				kolvo_mis++;
			}
			else {
				int var = check.Get();
				map_of_pairs[size_of_map_of_pairs][0] = var;
				map_of_pairs[size_of_map_of_pairs][1] = map_of_num[i] * (-1);
				size_of_map_of_pairs++;
			}
		}
	}
	while (!check.IsEmpty()) { // опустошение остатков стека, выявление ошибок для открывающихся скобок
		int var = check.Get();
		map_of_pairs[size_of_map_of_pairs][0] = var;
		map_of_pairs[size_of_map_of_pairs][1] = -1;
		size_of_map_of_pairs++;
		kolvo_mis++;
	}
	for (int i = 0; i < size_of_map_of_pairs; i++) {
		map[i][0] = map_of_pairs[i][0];
		map[i][1] = map_of_pairs[i][1];
	}
	*size_of_map = size_of_map_of_pairs;
	if (map_out_flag == 1) {
		for (int i = 0; i < size_of_map_of_pairs; i++) {
			cout << "    " << map_of_pairs[i][0] << "    |    " << map_of_pairs[i][1] << endl;
		}
	}
	return kolvo_mis;
}

// перевод в постфиксную форму________________________________________
int TFormula::FormulaConverter(void) { 
	Prepare();
	TStack<char> stack(255);
	for (int i = 0; i < size; i++) {
		//if(Rank())
	}
	return 0;
}

// вычисление результата______________________________________________
double TFormula::FormulaCalculator(void) {
	return 0.0;
}