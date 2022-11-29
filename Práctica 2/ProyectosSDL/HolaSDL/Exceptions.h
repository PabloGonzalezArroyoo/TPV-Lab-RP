#pragma once
#include <exception>
#include <iostream>
using namespace std;

//ArkanoidError
class ArkanoidError : public logic_error {
public:
	explicit ArkanoidError(const string& message);
	virtual const char* what() const throw();
};