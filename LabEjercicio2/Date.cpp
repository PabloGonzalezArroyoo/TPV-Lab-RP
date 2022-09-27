
#include "Date.h"
#include <iostream>

using namespace std;


Date::Date(int d,int m,int y) {
	day = d;
	month = m;
	year = y;
	if (!correctDate()) throw "Invalid date";
}

Date::Date(const Date& date){
	day = date.day;
	month = date.month;
	year = date.year;
}

void Date::operator++(){
	// Asumimos que no hay años bisiestos
	day++;
	if (day > daysInMonth(month)){
		day = 1;
		month++;
		if (month > 12){
			month = 1;
			year++;
		}
	}
}

void Date::operator+=(int n){
	for (int i = 0; i < n; i++)
		operator++();
}

bool Date::operator<(const Date& date) const{
	return (year < date.year ||
	       (year == date.year && (month < date.month || (month == date.month && day < date.day))));
}


int Date::diff(const Date& date) const{
	return (calculateValue() - date.calculateValue());
}

void Date::print() const {
	cout << day << "/" << month << "/" << year;
}


// Private operations

int Date::calculateValue() const{
	// Asumimos que no hay años bisiestos
	int v = 0;
	v += 365 * (year - 1);
	int m = month - 1;
	for (; m > 0; m--)
		v += daysInMonth(m);
	v += day;
	return v;
}

int Date::daysInMonth(int m) const {
	// Asumimos que no hay años bisiestos
	int numDays = 0;
	switch (m) {
		case 1:case 3:case 5:case 7:case 8:case 10:case 12:
			numDays = 31;
			break;
		case 4:case 6:case 9:case 11:
			numDays = 30;
			break;
		case 2:
			numDays = 28;
			break;
		default:
			numDays = 0;
	}
	return numDays;
}

bool Date::correctDate() const {
	bool correct;
	if ((year <= 0) || (month < 1) || (month > 12) || (day < 1) || (day > daysInMonth(month)))
		correct = false;
	else
		correct = true;
	return correct;
}

istream& operator>>(istream& in, Date& d){
	char c;
	in >> d.day >> c >> d.month >> c >> d.year;
	return in;
}

ostream& operator<<(ostream& out, const Date& d){
	out << d.day << "/" << d.month << "/" << d.year;
	return out;
}
