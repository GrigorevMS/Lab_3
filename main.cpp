#pragma once
#include"TStack.h"
#include"TFormula.h"
#include<string>
using namespace std;
void StrToChar(string in, char out[]) {
	for (int i = 0; i < in.size(); i++) {
		out[i] = in[i];
	}
	out[in.size()] = 0;
}
int main() {
	/*TStack<int> stack(10);
	cout << stack.IsEmpty() << endl;
	cout << stack.IsFull() << endl;
	stack.Put(2);
	cout << stack.IsEmpty() << endl;
	cout << stack.IsFull() << endl;
	stack.Output();
	stack.Put(3);
	stack.Put(4);
	stack.Put(5);
	stack.Get();
	stack.Put(7);
	stack.Output();
	int a = stack.See();
	cout << a;
	stack.Output();*/
	bool next = true;
	int next_in;
	cout << "Enter 1 as 'YES' or 0 as 'NO'" << endl;
	do {
		string in;
		cout << endl << "Enter TFormula: ";
		cin >> in;
		cout << endl;

		char mas[255];
		StrToChar(in, mas);
		TFormula formula(mas);
		formula.Output();
		cout << "Mistakes: " << formula.FormulaChecker(1) << endl;
		formula.FormulaConverter();
		formula.Output();
		cout << endl << "The result is: " << formula.FormulaCalculator() << endl;

		cout << endl << "Do you want to continue?" << endl;
		cout << "Your answer --> ";
		cin >> next_in;
		if (next_in == 0)
			next = false;
	} while (next);
}