#pragma once
#include "MojaLista.h"
#include "Athletes.h"
#include <string>

using namespace std;

class Disqualified
{
public:
	MojaLista<Athlete> dsq_athletes;
	void read_from_file(string);
};

void Disqualified::read_from_file(string sciezka)
{
	ifstream plik_wejsciowy;
	string line;
	plik_wejsciowy.open(sciezka);
	while (getline(plik_wejsciowy, line))
	{
		istringstream ss(line);
		auto ath = Athlete();
		ath.name = line;
		this->dsq_athletes.push_back(ath);
	}
}