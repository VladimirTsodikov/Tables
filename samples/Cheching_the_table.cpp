#pragma once
#include <iostream>
#include "Polynomial.h"
#include <string>
#include <cmath>	

int main()
{
	Polynomial s("2.5+x");
	Polynomial k("-5y+12x^2z^25-5z+4");
	Polynomial m("x+1.23+1.29-0.02+yz^1-yz");
	bool a= (s==k);
	m = s*k;
	k *= k;
	//k.clear();
	//k = s;
	s *= 4;
	k.Print();
	//std::cout<<a;
	/*int degree = 0;
	int DegreeX = 0;
	for (int i = 9; i >= 0; i--)		//������ ��������� ����� � ���� degree. �������� ������ �������, � 29 �� 20-��, ������ ������ 
		if (DegreeX / pow(2, i) > 0)	//����� �������� ������ ���� ����� ����� �� ������� ����� ����� �������. ��������� � �������� ���
		{
			degree += 1 << i+1;
			DegreeX -= pow(2, i);
		}
	std::cout << degree;
	
	
	size_t LenghtTmpNumber;
	double TmpNumber;							//� �� ������ ������ ������� ������ LenghtTmpNumber ���������(����), ��� LenghtTmpNumber - ����� "������������" �����
	TmpNumber = std::stod("+12", &LenghtTmpNumber);
	std::cout << TmpNumber << LenghtTmpNumber;
	List<> a(2);
	a.Print(); std::cout << std::endl;
	a.insert(5, 2);
	a.Print(); std::cout << std::endl;
	a.erase(1);
	a.Print(); std::cout << std::endl;
	a.erase(1);
	a.Print(); std::cout << a.empty() << std::endl;

	List<> b(3);
	b.insert(4);
	b.insert(5);



	std::cout << b.search(5) << std::endl;
	b.clear();
	std::cout << b.empty();
	std::cout << b.search(2) << std::endl;

	List<>c;
	c.insert(2);
	c.Print();*/
}