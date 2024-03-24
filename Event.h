#pragma once
#pragma warning (disable:4996)
#include <iostream>
#include <fstream>
#include "Time.h"
#include "Date.h"

class Event
{
public:
	Event() : date(1, 1, 2024), time(0, 0)
	{
		this->name = new char[strlen("Event") + 1];
		strcpy(name, "Event");
	}

	Event(const char* name, unsigned day, unsigned month, unsigned year, unsigned hour, unsigned minutes) :
		date(day, month, year), time(hour, minutes)
	{
		this->name = new char[strlen(name) + 1];
		strcpy(this->name, name);
	}

	Event(const Event& other) : date(other.date), time(other.time)
	{
		this->name = new char[strlen(other.name) + 1];
		strcpy(this->name, other.name);
	}

	Event& operator=(const Event& other)
	{
		if (this == &other)
			return *this;

		char* tempName = new char[strlen(other.name) + 1];
		strcpy(tempName, other.name);

		time = other.time;
		date = other.date;

		delete[] name;
		name = tempName;

		return *this;
	}

	~Event()
	{
		delete[] name;
		name = nullptr;
	}

	friend std::ostream& operator<<(std::ostream& os, const Event& event)
	{
		os << event.name << ": "
			<< event.date.getDay() << "/" << event.date.getMonth() << "/" << event.date.getYear() << "; "
			<< event.time.getHour() << ":" << event.time.getMinutes();
		return os;
	}

	void saveAsText(std::ofstream& file) const
	{
		file << *this;
	}

	void getFromText(std::ifstream& file)
	{
		size_t position = file.tellg();
		unsigned n = 0;
		char a = ' ';
		while (a != ':')
		{
			++n;
			file.get(a);
			if (!file)
				return;
		}
		file.seekg(position, std::ios::beg);

		char* tempName = new char[n];
		file.getline(tempName, n, ':');
		file.ignore();//for the space

		unsigned day, month, year, hour, minutes;
		file >> day;
		file.ignore();//for the /
		file >> month;
		file.ignore(); //for the /
		file >> year;
		file.ignore(); //for the ;
		file.ignore(); //for the space
		file >> hour;
		file.ignore(); //for the :
		file >> minutes;

		Event temp(tempName, day, month, year, hour, minutes);
		delete[] tempName;

		if (!file)
			return;

		*this = temp;
	}

	void saveAsBin(std::ofstream& file) const
	{
		size_t nameSize = strlen(name) + 1;
		file.write(reinterpret_cast<const char*>(&nameSize), sizeof(nameSize));
		file.write(name, nameSize);
		file.write(reinterpret_cast<const char*>(this), sizeof(Event));
	}

	void getFromBin(std::ifstream& file)
	{
		size_t nameSize = 0;
		file.read(reinterpret_cast<char*>(&nameSize), sizeof(name));
		char* tempName = new char[nameSize];
		file.read(tempName, nameSize);
		file.read(reinterpret_cast<char*>(this), sizeof(Event));
		name = tempName;
	}

private:
	char* name;
	Date date;
	Time time;
};

