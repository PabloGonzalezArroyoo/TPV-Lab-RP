#include "Alquiler.h"

Alquiler::Alquiler() : car(), date(), days() {}

Alquiler::Alquiler(Coche* car, Date date, int days) : car(car), date(date), days(days) {}

Coche* Alquiler::getCoche() { return car; }

Date Alquiler::getDate() { return date; }

int Alquiler::getDays() { return days; }