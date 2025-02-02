#include "Exceptions.h"

FileException::FileException(const std::string& message)
{
	this->message = message;
}

const char* FileException::what()
{
	return this->message.c_str();
}

RepositoryException::RepositoryException() : std::exception()
{
	this->message = "";
}

RepositoryException::RepositoryException(const std::string& message)
{
	this->message = message;
}

const char* RepositoryException::what()
{
	return this->message.c_str();
}

const char* DuplicateTrenchException::what()
{
	return "The trench is already in the repository!";
}

const char* InvalidPositionException::what()
{
	return "The position of the trench is invalid!";
}