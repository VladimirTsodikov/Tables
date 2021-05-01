#pragma once
#include <iostream>
#include "Table.h"
#include <string>
#include <cmath>	

int main()
{
	UnorderedTable<> a;
	Polynomial pol1("2x^3+4"), pol2("-7y^12+xy^3-xz^25+4"), pol3("98y^2z^4+7xz-2x");
	//std::cout << pol3;
	a.insert(1, pol1); 
	a.insert(24, pol2);
	a.insert(2, pol3); 	

	OrderedTable<> b(a);
	
	b.Print();
//a.erase(2);
//
//a.print();
//a.erase(24);
//
//a.print();
//a.erase(1);
//a.print();
}