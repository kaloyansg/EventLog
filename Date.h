#pragma once
class Date
{
public:
	Date()
	{
		day = 1;
		month = Month::Jan;
		year = 2024;
	}

	Date(unsigned day, unsigned month, unsigned year)
	{
		if (month > 12)
			throw "Invalid month";
		if (day > 31)
			throw "Invalid day";
		if (year < 2024)
			throw "Invalid year";

		this->day = day;
		this->year = year;
		this->month = static_cast<Month>(month);
	}

	unsigned getDay() const
	{
		return day;
	}

	unsigned getMonth() const
	{
		return static_cast<unsigned>(month);
	}

	unsigned getYear() const
	{
		return year;
	}

private:
	enum class Month
	{
		Jan,
		Feb,
		Mar,
		Apr,
		May,
		Jun,
		Jul,
		Aug,
		Sep,
		Oct,
		Nov,
		Dec
	};

	unsigned day;
	Month month;
	unsigned year;
};