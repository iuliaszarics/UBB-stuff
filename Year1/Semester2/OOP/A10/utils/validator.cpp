

#include <string>
#include <stdexcept>
#include "validator.h"
#include "utils.h"
#include "Exceptions.h"

void Validator::ValidateSize(const std::string& size) {

    if(!Utils::IsNumber(size))
        throw ValidatorException("Size must be a number");

}

void Validator::ValidatePrice(const std::string& price) {

    if(!Utils::IsNumber(price))
        throw ValidatorException("Price must be a number");
}

void Validator::ValidateQuantity(const std::string& quantity) {

    if(!Utils::IsNumber(quantity))
        throw ValidatorException("Quantity must be a number");
}

void Validator::ValidateColour(const std::string& colour) {

    if(colour.empty())
        throw ValidatorException("Colour must not be empty");
}

void Validator::ValidatePhoto(const std::string& photo) {

    if(photo.empty())
        throw std::invalid_argument("Photo must not be empty");
}