#pragma once
#include <iostream>
#include <string>
#include <cmath>	//для функции fabs (модуль разности) и pow (возведение в степень - для побитового сдвига)

#define EXP 1048576 //2^20 - для побитового сдвига
#define EXP1 1024	//2^10 - для побитового сдвига

//реализуем полином на базе циклического списка с головой
class Polynomial //: public List<double>
{
protected:	//реализуем внутреннюю структуру - моном (одночлен) на базе звена
	struct Monomial //:public Node
	{
		double coeff;	//вещественный коэфиициент монома
		int degree;	//степени у трёх зависимых переменных монома: x, y, z. Допустимые показатели - от 0 до 1023, хранятся с помощью побитового сдвига
		Monomial* next;

		Monomial() { coeff = 0; degree = 0; next = NULL; }	//поле next переопределяется в конструкторе списка и при создании новых звеньев в списке
		Monomial(double _coeff, int _degree) { coeff = _coeff; degree = _degree; next = NULL; }
		Monomial(const Monomial& to_copy) { coeff = to_copy.coeff; degree = to_copy.degree; next = NULL; }
		~Monomial() {}
		Monomial& operator*=(const Monomial& input)
		{
			if (degree / EXP + input.degree / EXP > 1023 || degree % EXP / EXP1 + input.degree % EXP / EXP1 > 1023 || degree % EXP1 + input.degree % EXP1 > 1023)
				throw "Degree greater than the maximum allowable";	//проверка, чтобы не было переполнения степеней. 
			//Иначе алгоритм хранения трёх показателей степеней трёх переменных в одном поле int перестанет работать
			else
			{
				coeff *= input.coeff;	//коэффициенты перемножаются
				degree += input.degree;	//а показатели складываются
				return *this;
			}
		}
		Monomial operator*(const Monomial& input)
		{
			Monomial tmp(*this);
			tmp *= input;
			return  tmp;
		}
		bool operator==(const Monomial& Mon)
		{
			return (fabs(coeff - Mon.coeff) < 1e-10 && degree == Mon.degree) ? true : false;	//если коэффициенты до некоторой степени точности равны 
		}		//и степени при этом равны, возвращаем true. Иначе false
	};
protected:
	Monomial* head;
	int count;	//число мономов
	Monomial* translator(std::string&);	//для считывания строки и создания звеньев полинома
	void insert(Monomial*);		//для вставки очередного монома в полином с сохранением упорядоченности
public:
		Polynomial()	//конструктор по умолчанию
	{
		head = new Monomial(0, -1);	//только создаём голову. Заносим на всякий случай значение коэффициента 0, а степени -1. В дальнейшем можно будет идентифицировать ошибку, если случайно обратимся к голове
		head->next = head;
		count = 0;
	}
	Polynomial(std::string input_data)		//конструктор с параметром
	{
		head = new Monomial(0, -1);	//создали голову
		head->next = head;
		count = 0;
		
		while (input_data.size() > 0)		//записываем мономы сразу в упорядоченном виде
		{
			Monomial* tmp = translator(input_data);	//Так как вначале проверка на длину строки, транслятор должен отработать корректно
			insert(tmp);
		}
	}
	Polynomial(const Polynomial& to_copy)	//конструктор копирования. Так как полином всегда поддерживается упорядоченным, копировать можно просто все звенья подряд, 
	{				//и новый полином тоже будет упорядоченным
		head = new Monomial(0, -1); head->next = head;
		Monomial *tmp1 = head, *tmp2 = to_copy.head->next;
		while (tmp2 != to_copy.head)
		{
			Monomial* curr = new Monomial(tmp2->coeff, tmp2->degree);
			tmp1->next = curr; 
			curr->next = head;
			tmp1 = tmp1->next;
			tmp2 = tmp2->next;
		}
		count = to_copy.count;
	}
	~Polynomial()
	{
		//или через итератор - пример далее, функция clear
		Monomial* p = head->next, * tmp;
		while (p != head)
		{
			tmp = p->next;
			delete p;
			p = tmp;
		}
		delete head;
	}
	void Print();	//распечатка полинома
	Polynomial& operator+=(const Polynomial&);
	Polynomial operator+(const Polynomial&);
	Polynomial& operator-=(const Polynomial&);
	Polynomial operator-(const Polynomial&);
	Polynomial& operator+=(const Monomial&);
	Polynomial& operator*=(const Polynomial&);
	Polynomial operator*(const Polynomial&);
	Polynomial& operator*=(const double&);
	Polynomial operator*(const double&);
	bool operator==(const Polynomial&) const;	//константный метод - не меняет поля класса
	bool operator!=(const Polynomial&) const;
	Polynomial& operator=(const Polynomial& to_copy)
	{
		Monomial* tmp1 = head, * tmp2 = to_copy.head->next;
		head->next = head;
		while (tmp2 != to_copy.head)
		{
			Monomial* curr = new Monomial(tmp2->coeff, tmp2->degree);
			tmp1->next = curr;
			curr->next = head;
			tmp1 = tmp1->next;
			tmp2 = tmp2->next;
		}
		count = to_copy.count;
		/*
		Polynomial k = Pol;	//сделали копию полинома
		/*Polynomial* tmp = &k;
		delete this;
		return *tmp;*/
		//if (this) delete this; <----------- это неправильно! Удалять не нужно! Всё удалится автоматически при выходе из функции 
		//*this = k;
		return *this;
	}
	bool search(const Monomial&);		//проверка наличия такого монома с такими коэффициентами в полиноме
	bool empty() { return (head->next == head); }	//проверка на пустоту		//или return (count==0)
	Monomial front();	//возвращает первый моном (сразу за головой)
	void clear();	//очистка списка (останется только голова)
	int GetCount() { return count; }	//возвращает количество элементов (звеньев) в списке
};
Polynomial::Monomial* Polynomial::translator(std::string &str)	//упрощённый транслятор. ПОСЛЕДОВАТЕЛЬНО СЧИТЫВАЕМ: коэффициент, если есть, степени x, y, z. Строка должна быть без пробелов
{
	if (str.size() == 0)
		return nullptr;	//если не вышли из функции, значит всё хорошо, хотя бы один символ в строке есть, продолжаем
//для единообразности обработки строки, вставим в начало знак (+ или -). Возможные варианты начала строки: +, -, цифра, переменная x,y,z. В первых двух случаях знак есть сразу. Во всех остальных нужно добавить вручную
	if (str[0] != '+' && str[0] != '-')	str.insert(0, "+");	
//теперь будет однотипная обработка: обязательно вначале идёт знак, потом коэффициент, если есть (если нет, то равен 1), потом переменные со степенями (если нет, степени равны нулю)

	Monomial* tmp = new Monomial();	//по умолчанию степень ноль, все биты - нули
	//if (str[0] == '+' || str[0] == '-')	- это условие всегда выполняется. Смотрим именно на символ на  первой позиции
	if (str[1] >= '0' && str[1] <= '9')
	{
		size_t LenghtTmpNumber;
		double TmpNumber;
		TmpNumber = std::stod(str, &LenghtTmpNumber);	//преобразование в число типа double будет с первой позиции! То есть будет учитываться знак
		tmp->coeff = TmpNumber;
		str.erase(0, LenghtTmpNumber);
	}	//если на первой позиции не число, а переменная, то коэффициент равен +1 или -1, в зависимости от знака на нулевой позиции. Один символ нужно удалить
	else if (str[0] == '+') { tmp->coeff = 1; str.erase(0, 1); }
	else { tmp->coeff = -1; str.erase(0, 1); }
	
	if (str[0] == 'x' || str[0] == 'х')	//второй вариант - кириллица, для любителей русского
	{
		int DegreeX = 1;	//если в строке написано x, то он всяко существует в 1 степени. Если затем идёт символ ^, то изменим значение показателя. Если нет, то степень так и останется первой
		if (str[1] == '^')
		{
			str.erase(0, 2);	//стираем два символа - x^
			size_t LenghtTmpNumber;
			DegreeX = std::stoi(str, &LenghtTmpNumber);
			str.erase(0, LenghtTmpNumber);
			if (DegreeX < 0) throw "Negative exponent x";	//т.к. мы работаем только с целыми неотрицательными показателями. Запись x^0 допустима
			if (DegreeX > 1023) throw "Too large exponent x";
		}	//после этого момента степень переменной x однозначно определена
		else str.erase(0, 1);	//иначе стираем только один символ x
		
		for (int i = 9; i >=0; i--)		//делаем побитовый сдвиг в поле degree. Занимаем десять позиций, с 29 по 20-ую, считая справа 
		{
			if (DegreeX / int(pow(2, i)) > 0)	//такое возможно только если целая часть от деления будет равна единице. Переводим в двоичный вид
			{
				tmp->degree += 1 << (i + 20);		//т.к. позиции с 29 по 20, прибавляем +20
				DegreeX -= pow(2, i);
			}
		}
	}
		//аналогично
	if (str[0] == 'y' || str[0] == 'у')	//второй вариант - кириллица
	{
		int DegreeY = 1;
		if (str[1] == '^')
		{
			str.erase(0, 2);	//стираем два символа - y^
			size_t LenghtTmpNumber;
			DegreeY = std::stoi(str, &LenghtTmpNumber);
			str.erase(0, LenghtTmpNumber);
			if (DegreeY < 0) throw "Negative exponent y";	
			if (DegreeY > 1023) throw "Too large exponent y";
		}	//после этого момента степень переменной y однозначно определена
		else str.erase(0, 1);	//иначе стираем только один символ y

		for (int i = 9; i >= 0; i--)		//делаем побитовый сдвиг в поле degree. Занимаем десять позиций, с 19 по 10-ую, считая справа 
		{
			if (DegreeY / int(pow(2, i)) > 0)	//такое возможно только если целая часть от деления будет равна единице. Переводим в двоичный вид
			{
				tmp->degree += 1 << (i + 10);		//т.к. позиции с 19 по 10, прибавляем +10
				DegreeY -= pow(2, i);
			}
		}
	}

	if (str[0] == 'z')
	{
		int DegreeZ = 1;
		if (str[1] == '^')
		{
			str.erase(0, 2);	//стираем два символа - z^
			size_t LenghtTmpNumber;
			DegreeZ = std::stoi(str, &LenghtTmpNumber);
			str.erase(0, LenghtTmpNumber);
			if (DegreeZ < 0) throw "Negative exponent z";
			if (DegreeZ > 1023) throw "Too large exponent z";
		}	//после этого момента степень переменной z однозначно определена
		else str.erase(0, 1);	//иначе стираем только один символ z

		for (int i = 9; i >= 0; i--)		//делаем побитовый сдвиг в поле degree. Занимаем десять позиций, с 9 по 0-ую, считая справа 
		{
			if (DegreeZ / int(pow(2, i)) > 0)	//такое возможно только если целая часть от деления будет равна единице. Переводим в двоичный вид
			{
				tmp->degree += 1 << i;		//т.к. позиции с 9 по 0, ничего не прибавляем 
				DegreeZ -= pow(2, i);
			}
		}
	}
	return tmp;
}

void Polynomial::insert(Monomial* to_ins)	//вставляем САМО ЗВЕНО! НЕ ЕГО КОПИЮ! НЕ CONST!
{
	Monomial *first = head, *second = head->next;
	while (second->degree > to_ins->degree)	//степень монома от 0 до 1023*1023*1023, а у головы степень -1. Поэтому мы точно остановимся
	{
		first = first->next;
		second = second->next;
	}
	if (second->degree == to_ins->degree)	//если уже существует звено с такими показателями переменных
	{
		second->coeff += to_ins->coeff;
		delete to_ins;
		if (second->coeff <1e-10)	//удаляем звено, если коэффициент стал равен нулю
		{
			first->next = second->next;
			delete second;
			count--;
		}
	}
	else //значит звена с такими показателями переменных ещё не было
	{
		first->next = to_ins;
		to_ins->next = second;
		count++;
	}
}

void Polynomial::Print()
{
	if (count == 0) { std::cout << 0; }
	else 
	{
		Monomial* tmp = head->next;
		bool flg = true;	//проверка на первый вход в цикл - чтобы не выводить знак, если коэффициент положительный
		while (tmp != head)
		{
			if (flg == true)
			{
				if (tmp->coeff > 0)
					if (fabs(tmp->coeff - 1) > 1e-10) std::cout << tmp->coeff;	//если коэффициент не равен равен единице, выводим его на экран. В противном случае ничего не делаем 
				if (tmp->coeff < 0)
					if (fabs(tmp->coeff + 1) > 1e10) std::cout << tmp->coeff;	//если коэффициент не равен равен -1, выводим его на экран. В противном случае выводим только минус
					else std::cout << '-';
				flg = false;	//отработали все случаи первого звена, больше вариантов нет. Остальные звенья обрабатываются иначе
			}
			else
			{
				if (tmp->coeff > 0)
				{
					std::cout << '+';
					if (fabs(tmp->coeff - 1) > 1e-10) std::cout << tmp->coeff;	//если коэффициент не равен 1, выводим знак плюс и сам коэффициент. Иначе только плюс
				}
				if (tmp->coeff<0)
					fabs(tmp->coeff + 1) < 1e-10 ? std::cout << '-' : std::cout << tmp->coeff;	//если коэффициент равен минус единице, нужно вывести только вывести знак. Иначе - нужно вывести всё число
			}

			/*
			if (flg == true && tmp->coeff > 0 && tmp->coeff != 1) { std::cout << tmp->coeff; flg = false; }
			else if (flg == false)
				if (tmp->coeff > 0)
				{
					std::cout << '+';
					if (tmp->coeff != 1) std::cout << tmp->coeff;
				}
			if (tmp->coeff < 0)
			{
				if (tmp->coeff == -1) std::cout << '-';
				else std::cout << tmp->coeff;
				flg = false;		//если зашли в эту ветку, выводить коэффициент без знака больше не придётся
			}
			*/
			if (tmp->degree / EXP > 1)	std::cout << "x^" << tmp->degree / EXP;
			if (tmp->degree / EXP == 1) std::cout << 'x';	//если равно нулю - ничего не выводим
			if (tmp->degree % EXP / EXP1 > 1)	std::cout << "y^" << tmp->degree % EXP / EXP1;
			if (tmp->degree % EXP / EXP1 == 1) std::cout << 'y';
			if (tmp->degree % EXP1 > 1)	std::cout << "z^" << tmp->degree % EXP1;
			if (tmp->degree % EXP1 == 1) std::cout << 'z';
			tmp = tmp->next;
		}

	}
}
/*
Polynomial& Polynomial::operator+=(const Polynomial& Pol)
{
	Monomial* tmp = Pol.head->next;
	while (tmp != Pol.head)
	{
		Monomial* to_ins = new Monomial(tmp->coeff, tmp->degree);	//сделали копию звена. Затем либо включили его в наш список, либо удалили, если звено с такими коэффициентами уже было
		this->insert(to_ins);
		tmp = tmp->next;
	}
	return *this;
}*/

Polynomial& Polynomial::operator+=(const Polynomial& Pol)//принцип основан на упорядоченности обоих полиномов и том, что моном с одинаковыми степенями может быть только один (без повторений)
{
	Monomial *prev1 = head, *curr1 = head->next, *curr2 = Pol.head->next;
	while (curr2 != Pol.head)
	{
		bool flg = true;
		if (curr2->degree > curr1->degree)
		{
			//Monomial* to_ins = new Monomial(*curr2);
			Monomial* to_ins = new Monomial(curr2->coeff, curr2->degree);
			prev1->next = to_ins;
			to_ins->next = curr1;
			prev1 = prev1->next;	//значение curr1 сохраняется, не двигается
			curr2 = curr2->next;	//сдвигаемся вперёд по вставляемому полиному, т.к. произошла вставка
			count++;
			flg = false;
		}
		else if (curr2->degree == curr1->degree)
		{
			curr1->coeff += curr2->coeff;
			curr2 = curr2->next;	//сдвигаемся вперёд по вставляемому полиному, т.к. произошла вставка
			if (curr1->coeff < 1e-10)	//если коэффициент стал равен нулю
			{
				curr1 = curr1->next;
				delete prev1->next; //удаляем звено, у которого коэффициент стал равен нулю (бывшее звено curr1)
				prev1->next = curr1;
				count--;
				flg = false;
			}
		}
		if (flg) { prev1 = prev1->next; curr1 = curr1->next; }//двигаем оба указателя в тек. полин. когда не произошло вставки (степень тек. монома была больше ИЛИ равная и итоговый коэф. не равен нулю)
	}
	return* this;
}

Polynomial Polynomial::operator+(const Polynomial& Pol)
{
	Polynomial k(*this);
	k += Pol;
	return k;
}

Polynomial& Polynomial::operator+=(const Monomial& Mon)
{
	Monomial* tmp = new Monomial(Mon);	//создали копию звена. Нужно, т.к. insert вставляет само звено, то есть если оно было частью другого списка всё нарушится
	insert(tmp);
	return *this;
}

Polynomial& Polynomial::operator-=(const Polynomial& Pol)
{
	Polynomial tmp(Pol);
	tmp *= (-1);
	*this += tmp;
	return *this;
}

Polynomial Polynomial::operator-(const Polynomial& Pol)
{
	Polynomial tmp(*this);
	tmp -= Pol;
	return tmp;
}

Polynomial& Polynomial::operator*=(const Polynomial& Pol)
{
	Polynomial tmp;		//если наш полином или входной полином были пусты, отработает тоже всё правильно: вернётчся пустой список, состоящий из одной головы
	Monomial* tmp1 = Pol.head->next;
	while (tmp1 != Pol.head)
	{
		Monomial* tmp2 = head->next;
		while (tmp2 != head)
		{
			tmp += (*tmp1) * (*tmp2);	//собираем все мономы от произведений в одном новом полиноме
			tmp2 = tmp2->next;
		}
		tmp1 = tmp1->next;
	}
	*this = tmp;
	return *this;
}

Polynomial Polynomial::operator*(const Polynomial& Pol)
{
	Polynomial tmp(*this);
	tmp *= Pol;
	return tmp;
}

Polynomial& Polynomial::operator*=(const double& to_mult)
{
	Monomial* tmp = head->next;
	while (tmp != head)
	{
		tmp->coeff *= to_mult;
		tmp = tmp->next;
	}
	return *this;
}

Polynomial Polynomial::operator*(const double& to_mult)
{
	Polynomial tmp(*this);
	tmp *= to_mult;
	return tmp;
}

bool Polynomial::operator==(const Polynomial& Pol) const
{
	if (count != Pol.count) return false;
	bool equal = true;
	Monomial *tmp1 = head->next, *tmp2 = Pol.head->next;
	while (tmp1!=head)	//на tmp2 условие не нужно, т.к. количество звеньев в полиноме одинаково
	{	//т.к. полином поддерживается в упорядоченном состоянии, то можем идти просто последовательно от начала и до конца и сравнивать. Если когда-то звенья оказались не равны, то полиномы тоже не равны
		if (*tmp1==*tmp2) 
		{
			tmp1 = tmp1->next;
			tmp2 = tmp2->next;
		}
		else
		{
			equal = false;
			break;
		}
	}
	return equal;
}

bool Polynomial:: operator!=(const Polynomial& Pol) const
{
	return !(*this == Pol);
}

bool Polynomial::search(const Monomial& Mon)
{
	bool flg = false;
	Monomial* tmp = head->next;
	while (tmp != head)
	{
		if (*tmp == Mon) { flg = true; break; }
		else tmp = tmp->next;
	}
	return flg;
}

Polynomial::Monomial Polynomial::front()
{
	if (!empty())
	{
		Monomial* tmp = new Monomial(*head->next);	//делаем копию следующего за головой монома - с максимальной степенью
		return *tmp;
	}
	else throw "Polynomial is empty";
}

void Polynomial::clear()
{
	while (head->next != head)
	{
		Monomial* tmp = head->next;
		head->next = head->next->next;
		delete tmp;
	}
	count = 0;
}