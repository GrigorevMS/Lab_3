#pragma once
#include<iostream>
using namespace std;
const int MaxMemSize = 25; //������ ������ ��-���������
template <class Type>
class TStack {
protected:
	Type* pMem; // ������ ���������
	int MemSize; // ������ ���������� ������
	int DataCount; // ���������� ���������
	int High; // ������ ������� �����
	virtual int GetNextIndex(int index);
public:
	TStack(int Size = MaxMemSize); // �����������
	TStack(const TStack& Copy); // ����������� �����������
	~TStack(); // ����������
	int IsEmpty(void) const; // �������� �������
	int IsFull(void) const; // �������� ������������
	void Put(const Type& Val); // �������� ��������
	virtual Type Get(void); // ������� ��������
	Type See(void);
	void Output(void);
};

template <typename Type>
TStack<Type>::TStack(int Size) {
	DataCount = 0;
	if (Size == 0) {
		Size = MaxMemSize;
	}
	MemSize = Size;
	pMem = new Type[MemSize];
	High = -1;
}
template<typename Type>
TStack<Type>::TStack(const TStack& Copy) {
	DataCount = Copy.DataCount;
	MemSize = Copy.MemSize;
	pMem = new Type[MemSize];
	for (int i = 0; i < DataCount; i++) {
		pMem[i] = Copy.pMem[i];
	}
}
template<typename Type>
TStack<Type>::~TStack() {
	delete[]pMem;
}
template<typename Type>
int TStack<Type>::GetNextIndex(int index) {
	return ++index;
}
template<typename Type>
int TStack<Type>::IsEmpty(void)const {
	return DataCount == 0;
}
template<typename Type>
int TStack<Type>::IsFull(void)const {
	return DataCount == MemSize;
}
template<typename Type>
void TStack<Type>::Put(const Type& Val) {
	High = GetNextIndex(High);
	pMem[High] = Val;
	DataCount++;
}
template<typename Type>
Type TStack<Type>::Get(void) {
	DataCount--;
	return pMem[High--];
}
template<typename Type>
Type TStack<Type>::See(void) {
	return pMem[High];
}
template<typename Type>
void TStack<Type>::Output(void) {
	cout  << endl << "[ ";
	for (int i = 0; i < DataCount; i++) {
		cout << pMem[i] << " ";
	}
	cout << "]" << endl;
	cout << "DataCount = " << DataCount << endl;
	cout << "High = " << High << endl;
}