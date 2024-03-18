#pragma once
#include <string>
#include <sstream>
#include <fstream>
#include "MojaLista.h"

using namespace std;

struct Athlete
{
	string name;
	int age;
	string country;
	double points;

	void add_points(double);
	Athlete();
	Athlete(string, int, string, double);
	bool operator==(const Athlete& rhs) const;
	bool operator==(const string& rhs) const;
	bool operator<(const Athlete& rhs) const;
	bool operator>(const Athlete& rhs) const;
};

class Athletes
{
	MojaLista<Athlete> athletes;
public:
	void read_from_file(string);
	MojaLista<Athlete>& get_athletes();
};


ostream& operator<<(ostream& os, const Athlete& skier)
{
	os << skier.name << " country: " << skier.country << " age: " << skier.age << " points: " << skier.points;
	return os;
}


inline void Athlete::add_points(double pts)
{
	this->points = points + pts;
}

inline Athlete::Athlete()
{

}
inline Athlete::Athlete(string name, int age, string country, double points)
{
	this->name = name;
	this->age = age;
	this->country = country;
	this->points = points;
}

bool Athlete::operator==(const Athlete& rhs) const
{
	return this->name == rhs.name;
}
	


inline bool Athlete::operator==(const string& rhs) const
{
	return this->name == rhs;
}

bool Athlete::operator<(const Athlete& rhs) const
{
	if (this->points > rhs.points)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool Athlete::operator>(const Athlete& rhs) const
{
	if (this->points > rhs.points)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Athletes::read_from_file(string sciezka)
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
			auto ath = Athlete();

			while (getline(ss, komorka, ','))
			{
				switch (licznik)
				{
				case 0:
					ath.name = komorka;
					break;
				case 1:
					ath.age = stoi(komorka);
					break;
				case 2:
					ath.country = komorka;
					break;
				case 3:
					ath.points = stod(komorka);
					break;
				}
				licznik++;
			}
			this->athletes.push_back(ath);
		}
	}
}

inline MojaLista<Athlete> &Athletes::get_athletes()
{
	return this->athletes;
}