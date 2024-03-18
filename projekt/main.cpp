// projekt_lista_dwukierunkowa.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "MojaLista.h"
#include "Test.h"
#include <sstream>
#include "Athletes.h"
#include "Comps.h"
#include "Disqualified.h"
#include <list>

using namespace std;


void points_update(Athletes& athletes,Comps& comps)
{
	auto winner_names = comps.get_winners();
	auto tmp = winner_names.get_first();

	while (tmp)
	{
		auto ath = Athlete();
		ath.name = tmp->value;
		auto ptr = athletes.get_athletes().find(ath);
		if (ptr)
		{
			ptr->value.add_points(100);
		}
		tmp = tmp->next;
	}
}

void dsq_update(Athletes& athletes, Disqualified& dsq_ath)
{
	auto dsq = dsq_ath.dsq_athletes.get_first();
	while (dsq)
	{
		auto ath = Athlete();
		ath.name = dsq->value.name;
		auto ptr = athletes.get_athletes().find(ath);
		if (ptr)
		{
			athletes.get_athletes().erase(ath);
		}
		dsq = dsq->next;
	}
}

void rank_update(Athletes& athletes)
{
	athletes.get_athletes().high_to_low();
}

int main()
{

	auto athletes = Athletes();
	athletes.read_from_file("skiers.txt");
	cout << "World cup skiers: " << endl;
	athletes.get_athletes().displayFront();

	cout << endl;

	auto comps = Comps();
	comps.read_from_file("comps.txt");
	cout << "World cup events and winners: " << endl;
	comps.get_comps().displayFront();

	cout << endl;


	points_update(athletes, comps);
	cout << "Skiers with updates points: " << endl;
	athletes.get_athletes().displayFront();

	cout << endl;

	rank_update(athletes);
	cout << "World cup ranking: " << endl;
	athletes.get_athletes().displayFront();

	cout << endl;

	auto dsq = Disqualified();
	dsq.read_from_file("dsq.txt");
	dsq_update(athletes, dsq);
	cout << "World cup ranking after dsq some athletes: " << endl;
	athletes.get_athletes().displayFront();
	

	/*test::run_test();*/
}

