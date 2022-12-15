#pragma once
#include <exception>
#include <iostream>
using namespace std;

// ArkanoidError
class ArkanoidError : public logic_error {
public:
	ArkanoidError(const string& message) : logic_error(message) {};
};

// SDLError
class SDLError : public ArkanoidError {
public:
	SDLError(const string& message) : ArkanoidError("SDLError: " + message) {};
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