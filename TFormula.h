#pragma once
#include"TStack.h"
#include<string>
using namespace std;
const int MaxLength = 255; // ������������ ������ ������� ������
class TFormula {
public:
	char Formula[MaxLength]; // ������� ������
	char PostfixForm[MaxLength]; // ����������� ������
	int size; // ������ ������
	int p_size;
public:
	TFormula();
	TFormula(char form[]);
	void Change(int pos, int key); // ����� �� ������. 1: -(- = +, 2: +(- = -
	void Prepare(void); // ���������� ������ Formula � �������� ����� ���������, ������� � ������ Change
	int Rank(char sym); // ����������� �������������� ��������: 0 - (, 1 - ), 2 - + ��� -, 3 - * ��� /, 4 - ��������
	void Output(void);
	// �������� ����������______________________________________________________
	int FormulaChecker(/*char map[], int size_of_map, */int map_out_flag = 0);// �������� ������������
	int FormulaConverter(void); // ������� � ����������� �����
	double FormulaCalculator(void); // ���������� ����������
};

// ����� �� ������. 1: -(- = +, 2: +(- = -________________________
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

// ���������� ������ Formula � �������� ����� ���������, ������� � ������ Change
void TFormula::Prepare(void) {
	for (int i = 0; i < size - 2; i++) {
		if (Formula[i] == '-' && Formula[i+1] == '(' && Formula[i+2] == '-') {
			Change(i, 0);
		}
		else if (Formula[i] == '+' && Formula[i+1] == '(' && Formula[i+2] == '-') {
			Change(i, 1);
		}
	}
}

// ����������� �������������� ��������: 0 - (, 1 - ), 2 - + ��� -, 3 - * ��� /, 4 - ��������
int TFormula::Rank(char sym) {
	if (sym == '(') {
		return(0);
	}
	else if (sym == ')') {
		return(1);
	}
	else if (sym == '+' || sym == '-') {
		return(2);
	}
	else if (sym == '*' || sym == '/') {
		return(3);
	}
	else {
		return(4);
	}
}

void TFormula::Output(void) {
	cout << "Formula = [ ";
	for (int i = 0; i < size; i++)
		cout << Formula[i] << " ";
	cout << "]" << endl;
	cout << "PostfixForm = [ ";
	for (int i = 0; i < size; i++)
		cout << PostfixForm[i] << " ";
	cout << "]" << endl;
	cout << "size = " << size << endl;
}

// ����������� �� ���������_______________________________________
TFormula::TFormula() {
	size = MaxLength;
	for (int i = 0; i < MaxLength - 1; i++) {
		Formula[i] = '0';
	}
	Formula[MaxLength - 1] = 0;
	for (int i = 0; i < MaxLength - 1; i++) {
		PostfixForm[i] = '0';
	}
	PostfixForm[MaxLength - 1] = 0;
	p_size = 0;
}

// ����������� �����������________________________________________
TFormula::TFormula(char form[]) {
	int form_size = 0;
	while (form[form_size] != 0)
		form_size++;
	if (form_size > 0 && form_size <= 255) {
		size = form_size;
		for (int i = 0; i < form_size; i++) {
			Formula[i] = form[i];
		}
		Formula[form_size] = 0;
	}
	for (int i = 0; i < form_size; i++) {
		PostfixForm[i] = ' ';
	}
	PostfixForm[form_size] = 0;
	p_size = 0;
	Prepare();
}

// �������� ������������______________________________________________
int TFormula::FormulaChecker(/*char map[], int size_of_map,*/ int map_out_flag) {
	
	int kolvo_mis = 0; // ���������� ������ � ����������� ������ � �������
	int kolvo_brckts = 0; // ���������� ������
	int map_of_num[255]; // ������������� ������� ����� ������ ������(+ - ���������, - - ���������)
	int map_of_pairs[255][2]; // ������� ������������ ������������� ������ � �������������� ����� �� ������
	int size_of_map_of_pairs = 0; // ������ map_of_pairs

	TStack<int> check(255); // ���� ��� ������ ���������
	for (int i = 0; i < size; i++) { // �������� ������� � ����������� � ���� ������ � �� ���������� ������� � �������
		if (Formula[i] == '(') {
			map_of_num[kolvo_brckts] = kolvo_brckts + 1;
			kolvo_brckts++;
		}
		else if (Formula[i] == ')') {
			map_of_num[kolvo_brckts] = (kolvo_brckts + 1) * (-1);
			kolvo_brckts++;
		}
	}

	for (int i = 0; i < kolvo_brckts; i++) { // ��������� ������� ����� ����, ��������� ������, �������� ������� ������
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

	while (!check.IsEmpty()) { // ����������� �������� �����, ��������� ������ ��� ������������� ������
		int var = check.Get();
		map_of_pairs[size_of_map_of_pairs][0] = var;
		map_of_pairs[size_of_map_of_pairs][1] = -1;
		size_of_map_of_pairs++;
		kolvo_mis++;
	}
	/*for (int i = 0; i < size_of_map_of_pairs; i++) {
		map[i][0] = map_of_pairs[i][0];
		map[i][1] = map_of_pairs[i][1];
	}
	size_of_map = size_of_map_of_pairs;*/
	if (map_out_flag == 1) {
		for (int i = 0; i < size_of_map_of_pairs; i++) {
			cout << "    " << map_of_pairs[i][0] << "    |    " << map_of_pairs[i][1] << endl;
		}
	}
	return kolvo_mis;
}

// ������� � ����������� �����________________________________________
int TFormula::FormulaConverter(void) {
	if (FormulaChecker(0) == 0) {
		TStack<char> stack(255);
		int post_size = 0;
		for (int i = 0; i < size; i++) {
			if (Rank(Formula[i]) == 4) {
				PostfixForm[post_size] = Formula[i];
				post_size++;
			}
			else {
				if (Rank(Formula[i])==0) {
					stack.Put('(');
				}
				else if (stack.IsEmpty() || ((Rank(Formula[i]) == 2 || Rank(Formula[i]) == 3) && (Rank(Formula[i]) > Rank(stack.See())))) {
					stack.Put(Formula[i]);
				}
				else if (!stack.IsEmpty() && (Rank(Formula[i]) == 2 || Rank(Formula[i]) == 3) && (Rank(Formula[i]) <= Rank(stack.See()))) {
					while ((Rank(stack.See() >= Rank(Formula[i]))) && !stack.IsEmpty()) {
						PostfixForm[post_size] = stack.See();
						post_size++;
						stack.Get();
					}
					stack.Put(Formula[i]);
				}
				else if (Rank(Formula[i]) == 1) {
					while (stack.See() != '(') {
						PostfixForm[post_size] = stack.See();
						post_size++;
						stack.Get();
					}
					stack.Get();
				}
			}
			/*cout << endl;
			stack.Output();
			cout << "PostfixForm = " << PostfixForm;
			cout << endl;*/
		}
		while (!stack.IsEmpty()) {
			PostfixForm[post_size] = stack.See();
			post_size++;
			stack.Get();
		}
		p_size = post_size;
		return 1;
	}
	cout << endl << "Formula contains mistakes. There is no way to produce necessary steps" << endl;
	return 0;
}

// ���������� ����������______________________________________________
double TFormula::FormulaCalculator(void) {
	TStack<double> stack(255);
	bool flag = false;
	if (FormulaChecker(0) == 0) {
		for (int i = 0; i < p_size; i++) {
			if (Rank(PostfixForm[i]) == 4) {
				stack.Put(PostfixForm[i] - 48);
			}
			else {
				double b = stack.See();
				stack.Get();
				double a = stack.See();
				stack.Get();
				double result;
				if (PostfixForm[i] == '+')
					result = a + b;
				else if (PostfixForm[i] == '-')
					result = a - b;
				else if (PostfixForm[i] == '*')
					result = a * b;
				else {
					if (b == 0) {
						flag = true;
						i = p_size;
						break;
					}
					else
						result = a / b;
				}
				stack.Put(result);
			}
			/*cout << endl;
			stack.Output();
			cout << endl;*/
		}
	}
	else {
		cout << "No way to calculate because of mistakes" << endl;
		return 0;
	}
	double answer = 0;
	if (flag) {
		cout << endl << "No way to calculate because of division by zero" << endl;
		return 0;
	}
	else {
		answer = stack.See();
		return answer;
	}
}