#pragma once
#include "MojaLista.h"
class test
{
public:
	static bool test_push_back()
	{
		auto lista = new MojaLista<int>();
		lista->push_back(10);
		lista->push_back(100);
		lista->push_back(1000);

		vector <int> exp{ 10,100,1000 };
		auto real = lista->to_vec();
		return exp == real;
	};
	static bool test_erase_from_empty()
	{
		auto lista = new MojaLista<int>();
		auto wynik = lista->erase(10);
		return wynik == false;
	};
	static bool test_erase_from_one_element_list()
	{
		auto lista = new MojaLista<int>();
		lista->push_back(5);
		auto wynik = lista->erase(5);
		return wynik == true;
	};
	static bool test_erase_basic_case()
	{
		auto lista = new MojaLista<int>();
		lista->push_back(5);
		lista->push_back(50);
		lista->push_back(500);
		lista->erase(50);
		lista->erase(500);
		lista->erase(5);

		auto wynik = lista->to_vec();
		
		vector <int> exp{};

		return (exp == wynik);


	};
	static bool test_low_to_high_basic_case()
	{
		auto lista = new MojaLista<int>();
		lista->push_back(13);
		lista->push_back(8);
		lista->push_back(9);
		lista->low_to_high();

		vector <int> exp{ 8,9,13 };
		auto real = lista->to_vec();

		return exp == real;
	};
	static bool test_low_to_high_multiple_same_elements()
	{
		auto lista = new MojaLista<int>();
		lista->push_back(15);
		lista->push_back(6);
		lista->push_back(15);
		lista->push_back(8);
		lista->push_back(15);
		lista->low_to_high();

		vector <int> exp{ 6,8,15,15,15 };
		auto real = lista->to_vec();

		return exp == real;
	};
	static bool test_low_to_high_empty()
	{
		auto lista = new MojaLista<int>();
		lista->low_to_high();

		vector <int> exp{ };
		auto real = lista->to_vec();

		return exp == real;
	};
	static bool test_low_to_high_only_one_element()
	{
		auto lista = new MojaLista<int>();
		lista->push_back(3);
		lista->low_to_high();

		vector <int> exp{ 3 };
		auto real = lista->to_vec();

		return exp == real;
	};
	static bool test_copy_constructor()
	{
		auto lista = MojaLista<int>();
		lista.push_back(5);
		lista.push_back(10);
		lista.push_back(15);

		auto lista1 = MojaLista<int>(lista);
		
		lista.erase(5);
		lista.erase(10);
		lista.erase(15);

		vector<int> exp{ 5,10,15 };
		auto real = lista1.to_vec();
		return exp == real;
	};
	static bool test_move_constructor()
	{
		auto lista = MojaLista<int>();
		lista.push_back(5);
		lista.push_back(10);
		lista.push_back(15);

		auto lista1 = MojaLista <int> (std::move(lista));

		vector<int> exp{ 5,10,15 };
		auto real = lista1.to_vec();

		return exp == real;

	};
	static void run_test()
	{
		cout << "wynik push_back: " << test_push_back() << endl;
		cout << "wynik erase from empty: " << test_erase_from_empty() << endl;
		cout << "wynik erase from one-element list: " << test_erase_from_one_element_list() << endl;
		cout << "wynik erase normal case: " << test_erase_basic_case() << endl;
		cout << "wynik low_to_high normal case: " << test_low_to_high_basic_case() << endl;
		cout << "wynik low_to_high multiple identic values: " << test_low_to_high_multiple_same_elements() << endl;
		cout << "wynik low_to_high empty: " << test_low_to_high_empty() << endl;
		cout << "wynik low_to_high one element: " << test_erase_from_one_element_list() << endl;
		cout << "wynik copy_constructor: " << test_copy_constructor() << endl;
		cout << "wynik move_constructor: " << test_move_constructor() << endl;
	};
};
	

