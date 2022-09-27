#include "Coche.h"

Coche::Coche() : code(0), price(0), model("") {}

Coche::Coche(int code, int price, std::string model) : code(code), price(price), model(model) {}

int Coche::getCode() { return code; }

int Coche::getPrice() { return price; }

std::string Coche::getModel() { return model; }