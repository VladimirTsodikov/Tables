#pragma once
#include <iostream>
#include "Table.h"
#include <string>
#include <cmath>	

int main()
{
	OrderedTable<int> a;
	a.insert(1, 35); 
	a.Print();
	a.erase(1);
	a.Print();
	a.insert(24, 5);
	a.insert(2, 34); 	


	a.Print();
	a.erase(2);

	a.Print();
	a.erase(24);

}