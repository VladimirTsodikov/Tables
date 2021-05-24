#pragma once
#include <iostream>
#include "Table.h"
#include <string>
#include <cmath>	

size_t hash(size_t x) {
	x = ((x >> 16) ^ x) * 0x45d9f3b;
	x = ((x >> 16) ^ x) * 0x45d9f3b;
	x = (x >> 16) ^ x;
	return x % 100;
}

int main()
{
	HashTable<> a;
	Polynomial pol1("2x^3+4"), pol2("-7y^12+xy^3-xz^25+4"), pol3("98y^2z^4+7xz-2x");
	//std::cout << pol3;
	//for (int i=0; i<200; i++)
	//	a.insert(i, pol1); 

	a.insert(1262, pol3);
	a.insert(1734, pol2);

	HashTable<> b = a;

	a.Print();
	//OrderedTable<> b(a);
	a.erase(1262);
	a.Print();
	a.erase(1734);
	a.Print();

	b.Print();
	//b.Print();
//a.erase(2);
//
//a.print();
//a.erase(24);
//
//a.print();
//a.erase(1);
//a.print();
}