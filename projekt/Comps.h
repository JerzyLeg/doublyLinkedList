#pragma once
#include <string>
#include <sstream>
#include "MojaLista.h"
using namespace std;

struct Comp
{
	string event;
	string winner_name;
	bool operator==(const Comp& rhs) const;
};


class Comps
{
private:
	MojaLista<Comp> comps;
public:
	void read_from_file(string);
	MojaLista<Comp> get_comps();
	MojaLista<string> get_winners();
};

ostream& operator<<(ostream& os, const Comp& comp)
{
	os << "event: " << comp.event << "   winner: " << comp.winner_name;
	return os;
}
bool Comp::operator==(const Comp& rhs) const
{
		return this->event == rhs.event;
}

void Comps::read_from_file(string sciezka)
{
	ifstream plik_wejsciowy;
	string line;
	plik_wejsciowy.open(sciezka);

	if (plik_wejsciowy.is_open())
	{

		while (getline(plik_wejsciowy, line))
		{
			istringstream ss(line);
			string komorka;
			int licznik = 0;
			auto comp = Comp();

			while (getline(ss, komorka, ','))
			{
				switch (licznik)
				{
				case 0:
					comp.event = komorka;
					break;
				case 1:
					comp.winner_name = komorka;
					break;
				}
				licznik++;
			}
			this->comps.push_back(comp);
		}
	}
}

inline MojaLista<Comp> Comps::get_comps()
{
	return this->comps;
}

inline MojaLista<string> Comps::get_winners()
{
	auto tmp = comps.get_first();
	auto winners = MojaLista<string>();
	while(tmp)
	{
		winners.push_back(tmp->value.winner_name);
		tmp = tmp->next;
	}
	return winners;
}