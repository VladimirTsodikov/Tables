#pragma once
#include "Polynomial.h"	//чтобы назначить в качестве типа по умолчанию
#include <iostream>
#include <vector> //для собственно самой таблицы - это вектор пар ключ-значение

template <class ValType = Polynomial>
class Table
{
public:
	virtual void insert(size_t key, const ValType& value_to_ins) = 0;	//производит вставку элемента с соответствующим ключом в таблицу. Если такой ключ уже есть, ...
	virtual void erase(size_t key) = 0;	//удаляет из таблицы строку с соответствующим ключом. Если такого ключа в таблице нет, ничего не происходит
	virtual std::pair<size_t, ValType> find (size_t key) = 0;	//возвращает строку - пару из ключа и значения, если в таблице будет найден ключ key
	
	virtual size_t GetSize() = 0;
	virtual void clear() = 0;
	virtual bool empty() = 0;
};

template <class ValType, class CellType = std::pair <size_t, ValType> >	//celltype - тип ячейки. Создаём вектор пар из ключа и значения valtype
class ArrayTable : public Table<ValType>
{
protected: 
	std::vector<CellType> data = 0;
	size_t size = 0;
public:
	ArrayTable() {
		data = 0;
		size = 0;
	}

	ArrayTable(const ArrayTable& to_copy) {
		data = to_copy.data;
		size = to_copy.size;
	}

};
template <class ValType>
class UnorderedTable : public ArrayTable<ValType>
{

};