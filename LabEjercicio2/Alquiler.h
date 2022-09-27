#pragma once

#include "Coche.h"
#include "Date.h"
#include <iostream>

class Alquiler
{
private:
	Coche* car;
	Date date;
	int days;
public:
	Alquiler();
	Alquiler(Coche* car, Date date, int days);
	Coche* getCoche();
	Date getDate();
	int getDays();
};

