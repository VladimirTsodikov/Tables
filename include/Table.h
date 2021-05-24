#pragma once
#include "Polynomial.h"	//чтобы назначить в качестве типа по умолчанию
#include <iostream>
#include <vector> //для собственно самой таблицы - это вектор пар ключ-значение
#include <algorithm> //для функции сортировки и lower_bound и find
#include <list>	//для метода цепочек в хэш-таблицах

#define LoadFactor 0.75		//коэффициент загруженности таблицы: отнношение числа записей в таблице size к числу ячеек в векторе data.size()
#define KoefForStock 1.3	//коэффициент с запасом - для конструктора копирования и resize


template <class ValType>
class Table	{
public:
	virtual void insert(size_t key, const ValType& value_to_ins) = 0;	//производит вставку элемента с соответствующим ключом в таблицу. Если такой ключ в таблице уже есть, выбрасываем исключение
	virtual void erase(size_t key) = 0;	//удаляет из таблицы строку с соответствующим ключом. Если такого ключа в таблице нет, ничего не происходит
	virtual std::pair<size_t, ValType> find (size_t key) = 0;	//возвращает строку - пару из ключа и значения, если в таблице будет найден ключ key
	
	virtual size_t GetSize() = 0;
	virtual void clear() = 0;
	virtual bool empty() = 0;
	virtual void Print() = 0;
};

template <class ValType, class CellType = std::pair <size_t, ValType> >	//celltype - тип ячейки. Создаём вектор пар из ключа и значения valtype
class ArrayTable : public Table<ValType> {
protected: 
	std::vector<CellType> data;	//вектор по умолчанию пуст
	size_t size = 0;
public:
	ArrayTable() {}

	ArrayTable(const ArrayTable& to_copy) {
		data = to_copy.data;
		size = to_copy.size;
	}

	size_t GetSize() override {	//слово override необязательное вспомогательное, чтобы подчеркнуть, что это полиморфная, то есть переопределённая функция
		return size;
	}

	void clear() override {
		data.clear();
		size = 0;
	}

	bool empty() override {
		return (size == 0);
	}

	void Print() override {		//неупорядоченный вывод - печать будет сгруппирована по значениям хэша (то есть по спискам поочерёдно
		if (empty()) std::cout << "Table is empty\n";
		else {
			std::cout << "Key:" << '\t' << '|' << '\t' << "Value:" << '\t' << '\t' << "Table's size is " << GetSize() << '\n';
			for (auto x : data)
				std::cout << x.first << '\t' << '|' << '\t' << x.second << '\n';
		}
	}

//	template <ValType> friend class HashTable;	//для того, чтобы конструктор копирования у хэш-функций мог обратиться к полям вектора
};

template <class ValType = Polynomial>
class UnorderedTable : public ArrayTable<ValType> {
public:
	UnorderedTable() : ArrayTable() {}
	UnorderedTable(const ArrayTable& to_copy) : ArrayTable(to_copy) {}	//делаем конструктор копирования от общего класса "Таблицы на массиве", потому что и упор., и неупор. скопированный вектор будут нам подходить. 
													//В случае с Упорядоченными массивами конструктор копирования будет сложнее, поскольку в результате копии неупорядоченного массива мы должны получить всё равно упорядоченный
	void insert(size_t key, const ValType& value_to_ins) override {
		for (auto& x : data) {				//проверяем, есть ли в таблице запись с таким ключом. Если будет выброшено исключение, функция не продолжит работу
			if (x.first == key)
				throw "Insert failed: record with the same key already exists in the table";
		}
		data.push_back(std::make_pair(key, value_to_ins));	//если дошли до сюда, значит, всё в порядке. Добавляем всегда в конец, т.к. неупоряд.
		size++;
	}

	void erase(size_t key) override {
		bool isElem = false;
		for (auto& x : data) {	//ищем во всём векторе. Ключ в таблице либо существует в ЕДИНСТВЕННОМ экземпляре, либо не существует
			if (x.first == key)
			{
				x.first = data[size - 1].first;	//если мы нашли элемент с таким ключом, меняем эту пару местами с последней парой, и последнюю пару удаляем из вектора
				x.second = data[size - 1].second;		//или кратно x=data[size-1];
				data.pop_back();
				size--;
				isElem = true;
				break;
			}
		}
		if (!isElem) throw "The deletion did not happen: a record with such a key does not exist in the table";
	}

	std::pair<size_t, ValType> find(size_t key) override {
		bool isElem = false;
		int i = 0;
		for ( ; i < size; i++) {	//ищем во всём векторе. Ключ в таблице либо существует в ЕДИНСТВЕННОМ экземпляре, либо не существует
			if (data[i].first == key)
			{
				isElem = true;
				break;
			}
		}
		if (!isElem) throw "The deletion did not happen: a record with such a key does not exist in the table";
		return data[i];	//если дошли до сюда, то пара с таким ключом в таблице действительно присутствует, исключение не сработает, и КОПИЮ этой пару мы и вернём
	}
};

template <class ValType = Polynomial>
class OrderedTable : public ArrayTable<ValType> {
public:
	OrderedTable() : ArrayTable() {}
	OrderedTable(const ArrayTable& to_copy) : ArrayTable(to_copy) {	//в этом случае недостаточно просто скопировать тот вектор значений, который есть в to_copy: если таблица, которую копируем, была неупорядоченная
		std::sort(data.begin(), data.end());	//а такое возможно, т.к. копия идёт от общего класса ArrayTable, к которому относятся и неупорядоченные таблицы, то скопированный вектор пар нужно ещё отсортировать!
	}	//используем стандартную сортировку, по умолчанию идёт по возрастанию. от начала массива (вектора) до элемента data[size-1] (то есть не включая правую границу. Сортировка по ключу! Одинаковых ключей быть не может! СОртировка по значению не нужна -> ПЕРЕГРУЖАТЬ БОЛЬШЕ И МЕНЬШЕ У ПОЛИНОМОВ НЕ ТРЕБУЕТСЯ!

	void insert(size_t key, const ValType& value_to_ins) override {
		for (auto& x : data) {				//проверяем, есть ли в таблице запись с таким ключом. Если будет выброшено исключение, функция не продолжит работу
			if (x.first == key)
				throw "Insert failed: record with the same key already exists in the table";
		}
		auto lower = lower_bound(data.begin(), data.end(), std::make_pair(key, value_to_ins));	//ищет позицию, в которой вставляемая пара будет не больше, чем следующая
		data.insert(lower, std::make_pair(key, value_to_ins));	//вставка на анйденную позицию
		size++;
	}

	void erase(size_t key) override {
		bool isElem = false;
		int i;
		for (i = 0; i < size; i++) {
			if (data[i].first == key) 
			{
				isElem = true;
				break;
			}
		}
		if (!isElem) throw "The deletion did not happen: a record with such a key does not exist in the table";
		for (; i < size - 1; i++)
			data[i] = data[i + 1];
		data.pop_back();	//на последнем месте всегда хранится "мусор" - или то же, что в предпоследней строке, или то, что от нас требовали удалить. Избавимся от этого с помощью pop_back
		size--;
	}

	std::pair<size_t, ValType> find(size_t key) override {
		//bool isElem = false;
		//int i = 0;
		//for (; i < size; i++) {	//ищем во всём векторе. Ключ в таблице либо существует в ЕДИНСТВЕННОМ экземпляре, либо не существует
		//	if (data[i].first == key)
		//	{
		//		isElem = true;		//выходим из цикла. Нашли
		//		break;
		//	}
		//	if (data[i].first > key)	//тоже выходим из цикла. Не нашли. Дальше искать смысла нет, т.к. упорядоченно по ключам
		//		break;
		//}
		//if (!isElem) throw "The deletion did not happen: a record with such a key does not exist in the table";
		//return data[i];	//если дошли до сюда, то пара с таким ключом в таблице действительно присутствует, исключение не сработает, и КОПИЮ этой пару мы и вернём
	
		int l = -1, r = size, m;
		while (l < r-1) {
			m = (l + r) / 2;
			if (data[m].first < key)
				l = m;
			else
				r = m;
		}
		if (data[r].first == key) return data[r];
		else throw "The deletion did not happen: a record with such a key does not exist in the table";
	}
};

template<class ValType = Polynomial>		//наследуем от виртуального класса Table. Хэш-таблицы всё-таки не таблицы на векторе, это другое и функции печати/копирования будут другими
class HashTable : public Table<ValType> {	//создаём таблицу (т.е. вектор) списков пар ключ-значение
protected:
	std::vector<std::list<std::pair<size_t, ValType>>> data;
	size_t size = 0;
private: 
	size_t HashF(size_t x, size_t size_table) {		//hash-function
		x = ((x >> 16) ^ x) * 0x45d9f3b;
		x = ((x >> 16) ^ x) * 0x45d9f3b;
		x = (x >> 16) ^ x;
		return x % size_table;
	}

	void resize() {	//если количество записей в таблице стало большим, то таблица замедаляется, то нужно увеличить размер вектора. Хэши будут пересчитаны
		std::vector<std::list<std::pair<size_t, ValType>>> tmp((int)(data.size() * KoefForStock));	//увеличиваем размер вектора в 1.3 раза. При этом сейчас число записей во всей таблице не превышает 0.75 от числа её ячеек
			for (int i = 0; i < data.size(); i++)	//рассматриваем каждую ячейку вектора и каждое звено списка
				for (auto it = data[i].begin(); it != data[i].end(); ++it)
					tmp[HashF(it->first, tmp.size())].push_front(std::make_pair(it->first, it->second));
		data.clear();
		data = tmp;
	}

public:
	HashTable() {		//создаём заранее таблицу побольше, чтобы resize не потребовался дольше
		data = std::vector<std::list<std::pair<size_t, ValType>>>(100);
		size = 0;
	}
	/*HashTable(const ArrayTable<ValType>& to_copy) {	//копирование таблиц на массиве (упор/неупор)		не нужно проверять единственность ключа: если уже была таблица, то в ней всё верно. Поэтому просто идём по массиву и вычисляя хэш вставляем в новую
		data = std::vector<std::list<std::pair<size_t, ValType>>>((int)(to_copy.size * KoefForStock));
		for (auto it = to_copy.data.begin(); it != to_copy.data.end(); ++it)
			data[HashF(it->first, data.size())].push_front(std::make_pair(it->first, it->second));
		size = to_copy.size;
	}*/
	HashTable(const HashTable<ValType>& to_copy) {	//копирование хэш-таблиц. Будем считать, что то, что копируем, составлено корректно. Размер при копировании и хэш-значения ключей будут теми же
		data = to_copy.data;
		size = to_copy.size;
	}

	void insert(size_t key, const ValType& to_ins) override {		//проверка наличия за O(N/m) в среднем, вставка за O(1)
		if ((double)(size) / (double)(data.size()) > LoadFactor) resize();	//если нужно, делаем перепаковку

		size_t hash = HashF(key, data.size());		//вычислили хэш, затем идём в ячейку вектора по этому хэшу и ищем в соответствующем списке
		std::list<std::pair<size_t, ValType>>::iterator it;
		for (it=data[hash].begin(); it != data[hash].end(); ++it)
			if (it->first == key) throw "Insert failed: record with the same key already exists in the table";
		data[hash].push_front(std::make_pair(key, to_ins));	//иначе всё хорошо, вставляем в список в начало
		size++;
	}

	void erase(size_t key) override {
		size_t hash = HashF(key, data.size());
		std::list<std::pair<size_t, ValType>>::iterator it;
		for (it = data[hash].begin(); it != data[hash].end(); ++it)
			if (it->first == key) break;
		if (it == data[hash].end())	throw "The deletion did not happen: a record with such a key does not exist in the table";	//если долши до конца списка и элемент с таким ключом найден не был
		data[hash].erase(it);
		size--;
	}

	std::pair<size_t, ValType> find(size_t key) override {
		size_t hash = HashF(key, data.size());
		std::list<std::pair<size_t, ValType>>::iterator it;
		for (it = data[hash].begin(); it != data[hash].end(); ++it)
			if (it->first == key) break;
		if (it == data[hash].end()) throw "The deletion did not happen: a record with such a key does not exist in the table";
		return std::make_pair(it->first, it->second);
	}

	size_t GetSize() override { return size; }
	size_t VectorSize() { return data.size(); }

	void clear() override {
		data.clear();
		data = std::vector<std::list<std::pair<size_t, ValType>>>(100);	//чтобы не было проблем, когда снова начнём заполнять таблицу. Уже есть заготовка, чтобы вставлять нвоые элементы
		size = 0;
	}
	
	bool empty() override { return (size == 0); }

	void Print() override {
		if (empty()) std::cout << "Table is empty\n";
		else {
			std::cout << "Key:" << '\t' << '|' << '\t' << "Value:" << '\t' << '\t' << "Table's size is " << GetSize() << '\n';
			for (int i = 0; i < data.size(); i++)	//рассматриваем каждую ячейку вектора и каждое звено списка
				for (auto it = data[i].begin(); it != data[i].end(); ++it)
					std::cout << it->first << '\t' << '|' << '\t' << it->second << '\n';
		}
	}
};