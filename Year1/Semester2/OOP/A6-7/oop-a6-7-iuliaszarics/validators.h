#pragma once
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include "domain.h"

class TrenchExceptions : public std::exception
{
private:
	std::vector<std::invalid_argument> errors;

public:
	TrenchExceptions(std::vector<std::invalid_argument> errors);
	TrenchExceptions(std::string error);
	std::vector<std::invalid_argument> returnErrors();
};

class TrenchValidator
{
public:
	static void validateTrenchID(const std::string&);
	static void validateTrenchSize(const std::string&);
	static void validateTrenchColour(const std::string&);
	static void validateTrenchPrice(const std::string&);
	static void validateTrenchQuantity(const std::string&);
	static void validateTrenchPhoto(const std::string&);
	static void validateTrenchAll(const std::string&, const std::string&, const std::string&, const std::string&, const std::string&);
};