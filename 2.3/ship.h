#ifndef SHIP_H
#define SHIP_H

#include <iomanip>
#include <iostream>
#include <string>

class Ship
{
private:
	int minute, hour, day, month, year;
	char origin;
	std::string UBI;

public:
	Ship(std::string, std::string, char, std::string);
	Ship();
	Ship(const Ship &);

	// Accessor methods
	int get_minute() const;
	int get_hour() const;
	int get_day() const;
	int get_month() const;
	int get_year() const;
	char get_origin() const;
	std::string get_UBI() const;

	void set_time(std::string);
	void set_date(std::string);
	void set_origin(char);
	void set_UBI(std::string);

	// Operator override
	bool operator<(const Ship &);
};

Ship::Ship(std::string date, std::string time, char origin_, std::string UBI_)
{
	day = (date[0] - '0') * 10 + (date[1] - '0');
	month = (date[3] - '0') * 10 + (date[4] - '0');
	year = (date[6] - '0') * 10 + (date[7] - '0');

	hour = (time[0] - '0') * 10 + time[1] - '0';
	minute = (time[3] - '0') * 10 + time[4] - '0';

	origin = origin_;
	UBI = UBI_;
}

Ship::Ship()
{
	day = 0;
	month = 0;
	year = 0;
	hour = 0;
	minute = 0;
	origin = '0';
	UBI = "";
}

Ship::Ship(const Ship &right)
{
	day = right.day;
	month = right.month;
	year = right.year;
	hour = right.hour;
	minute = right.minute;
	origin = right.origin;
	UBI = right.UBI;
}

int Ship::get_minute() const
{
	return minute;
}

int Ship::get_hour() const
{
	return hour;
}

int Ship::get_day() const
{
	return day;
}

int Ship::get_month() const
{
	return month;
}

int Ship::get_year() const
{
	return year;
}

char Ship::get_origin() const
{
	return origin;
}

std::string Ship::get_UBI() const
{
	return UBI;
}

bool Ship::operator<(const Ship &right)
{
	if (year != right.year)
		return year < right.get_year();

	if (month != right.month)
		return month < right.get_month();

	if (day != right.day)
		return day < right.get_day();

	if (hour != right.hour)
		return hour < right.get_hour();

	if (minute != right.minute)
		return minute < right.get_minute();

	return false;
}

void Ship::set_time(std::string time)
{
	hour = (time[0] - '0') * 10 + time[1] - '0';
	minute = (time[3] - '0') * 10 + time[4] - '0';
}

void Ship::set_date(std::string date)
{
	day = (date[0] - '0') * 10 + date[1] - '0';
	month = (date[3] - '0') * 10 + date[4] - '0';
	year = (date[6] - '0') * 10 + date[7] - '0';
}

std::ostream &operator<<(std::ostream &out, const Ship &barco)
{
	out << std::setfill('0');
	out << std::setw(2) << barco.get_day() << "-";
	out << std::setw(2) << barco.get_month() << "-";
	out << std::setw(2) << barco.get_year() << " ";
	out << std::setw(2) << barco.get_hour() << ":";
	out << std::setw(2) << barco.get_minute() << " ";
	out << barco.get_origin() << " " << barco.get_UBI();
	return out;
}

#endif