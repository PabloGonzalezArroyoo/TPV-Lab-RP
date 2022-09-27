#pragma once

#include <iostream>

class Coche
{
private:
	int code;
	int price;
	std::string model;
public:
	Coche();
	Coche(int code, int price, std::string model);
	int getCode();
	int getPrice();
	std::string getModel();
};

