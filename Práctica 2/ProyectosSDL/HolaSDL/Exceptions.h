#pragma once
#include <exception>
#include <iostream>
using namespace std;

//ArkanoidError
class ArkanoidError : public logic_error {
public:
	ArkanoidError(const string& message) : logic_error(message) {};
};

// SDL_Error
class SDL_Error : public ArkanoidError {
public:
	SDL_Error(const string& message) : ArkanoidError("SDL_ERROR: " + message) {};
	// SDL GetError, IMG GetError
};

// FileNotFoundError
class FileNotFoundError : public ArkanoidError {
public:
	FileNotFoundError(const string& message) : ArkanoidError("FileNotFoundError: " + message) {};
};

// FileFormatError
class FileFormatError : public ArkanoidError {
public:
	FileFormatError(const string& message) : ArkanoidError("FileFormatError: " + message) {};
};