#include "validators.h"

TrenchExceptions::TrenchExceptions(std::vector<std::invalid_argument> errors)
{
    this->errors = errors;
}

TrenchExceptions::TrenchExceptions(std::string error)
{
    this->errors.push_back(std::invalid_argument(error));
}

void TrenchValidator::validateTrenchID(const std::string& idOfTrenchToBeValidated)
{
    int idOfTrenchToBeValidatedAsInteger;

    try
    {
       idOfTrenchToBeValidatedAsInteger = std::stoi(idOfTrenchToBeValidated);
    }
    catch (const std::exception& e)
    {
        throw std::invalid_argument("The year of release of the movie must be an integer!");
    }

    if (idOfTrenchToBeValidatedAsInteger < 0)
        throw std::invalid_argument("The year of release of the movie must be a positive integer!");
}

void TrenchValidator::validateTrenchSize(const std::string& sizeOfTrenchToBeValidated)
{
    if (sizeOfTrenchToBeValidated.empty())
        throw std::invalid_argument("The size of the trench cannot be empty!");
}

void TrenchValidator::validateTrenchColour(const std::string& colourOfTrenchToBeValidated)
{
    if (colourOfTrenchToBeValidated.empty())
        throw std::invalid_argument("The size of the trench cannot be empty!");
}

void TrenchValidator::validateTrenchQuantity(const std::string& quantityOfTrenchToBeValidated)
{
    int quantityOfTrenchToBeValidatedAsInteger;
    try
    {
        quantityOfTrenchToBeValidatedAsInteger = std::stoi(quantityOfTrenchToBeValidated);
    }
    catch (const std::exception& e)
    {
        throw std::invalid_argument("The number of likes of the movie must be an integer!");
    }
}

void TrenchValidator::validateTrenchPrice(const std::string& priceOfTrenchToBeValidated)
{
	int priceOfTrenchToBeValidatedAsInteger;
    try
    {
		priceOfTrenchToBeValidatedAsInteger = std::stoi(priceOfTrenchToBeValidated);
	}
    catch (const std::exception& e)
    {
		throw std::invalid_argument("The number of likes of the movie must be an integer!");
	}
}

void TrenchValidator::validateTrenchPhoto(const std::string& linkOfTrenchToBeValidated)
{
    const std::regex pattern("((http|https)://)(www.)?[a-zA-Z0-9@:%._\\+~#?&//=]{2,256}\\.[a-z]{2,6}\\b([-a-zA-Z0-9@:%._\\+~#?&//=]*)");

    if (!std::regex_match(linkOfTrenchToBeValidated, pattern))
        throw std::invalid_argument("Invalid trailer link");
}

void TrenchValidator::validateTrenchAll(const std::string& idOfTrenchToBeValidated, const std::string& sizeOfTrenchToBeValidated, const std::string& colourOfTrenchToBeValidated, const std::string& priceOfTrenchToBeValidated, const std::string& quantityOfTrenchToBeValidated)
{
	std::vector<std::invalid_argument> errors;

    try
    {
		validateTrenchID(idOfTrenchToBeValidated);
	}
    catch (const std::invalid_argument& e)
    {
		errors.push_back(e);
	}

    try
    {
		validateTrenchSize(sizeOfTrenchToBeValidated);
	}
    catch (const std::invalid_argument& e)
    {
		errors.push_back(e);
	}

    try
    {
		validateTrenchColour(colourOfTrenchToBeValidated);
	}
    catch (const std::invalid_argument& e)
    {
		errors.push_back(e);
	}

    try
    {
		validateTrenchPrice(priceOfTrenchToBeValidated);
	}
    catch (const std::invalid_argument& e)
    {
		errors.push_back(e);
	}

    try
    {
		validateTrenchQuantity(quantityOfTrenchToBeValidated);
	}
    catch (const std::invalid_argument& e)
    {
		errors.push_back(e);
	}

	if (errors.size() > 0)
		throw TrenchExceptions(errors);
}

std::vector<std::invalid_argument> TrenchExceptions::returnErrors()
{
    return this->errors;
}