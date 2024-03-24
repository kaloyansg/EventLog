#pragma once
#include "Event.h"
#include "Date.h"
#include "Time.h"

class EventLog
{
public:
	EventLog()
	{
		events = new Event[1];
		capacity = 1;
		size = 0;
	}

	~EventLog()
	{
		delete[] events;
		events = nullptr;
	}

	void resize()
	{
		if (size < capacity)
			return;

		Event* tempEvents = new Event[capacity * 2];
		for (size_t i = 0; i < size; ++i)
		{
			tempEvents[i] = events[i];
		}

		delete[] events;
		events = tempEvents;
		capacity *= 2;
	}

	void addEvent(const Event& event)
	{
		resize();
		events[size] = event;
		++size;
	}

	void print() const
	{
		for (size_t i = 0; i < size; ++i)
		{
			std::cout << events[i] << std::endl;
		}
	}

	void saveAsText(std::ofstream& file) const
	{
		for (size_t i = 0; i < size; ++i)
		{
			events[i].saveAsText(file);
			file << '\n';
		}
	}

	void getFromText(std::ifstream& file)
	{
		Event tempEvent;
		tempEvent.getFromText(file);
		while (!file.eof())
		{
			this->addEvent(tempEvent);
			file.ignore(); //for the \n
			tempEvent.getFromText(file);
		}
	}

	void saveAsBin(std::ofstream& file) const
	{
		for (size_t i = 0; i < size; ++i)
		{
			events[i].saveAsBin(file);
		}
	}

	void getFromBin(std::ifstream& file)
	{
		Event tempEvent;
		tempEvent.getFromBin(file);
		while (!file.eof())
		{
			this->addEvent(tempEvent);
			tempEvent.getFromBin(file);
		}
	}

private:
	Event* events;
	unsigned size;
	unsigned capacity;
};

