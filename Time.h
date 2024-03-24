#pragma once
class Time
{
public:
	Time()
	{
		hours = 0;
		minutes = 0;
	}

	Time(unsigned hours, unsigned minutes)
	{
		if (hours > 24)
			throw "Invalid hour";
		if (minutes > 59)
			throw "Invalid minutes";

		this->hours = hours % 24;
		this->minutes = minutes;
	}

	unsigned getHour() const
	{
		return hours;
	}

	unsigned getMinutes() const
	{
		return minutes;
	}

private:
	unsigned hours;
	unsigned minutes;
};

