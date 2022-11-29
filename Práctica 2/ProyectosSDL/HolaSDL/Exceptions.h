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

// SDL_Error
class SDL_Error : public ArkanoidError {
	// SDL GetError, IMG GetError y TTF GetError
};

// FileNotFoundError
class FileNotFoundError : public ArkanoidError {

};

// FileFormatError
class FileFormatError : public ArkanoidError {

};