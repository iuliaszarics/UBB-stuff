

#pragma once

#include <string>

class Validator {

public:
    /**
     * Function that validates the size of a coat.
     * @param size String - the size to be validated
     * @return -, if the size is valid, an error message otherwise
     * @raises "Size must be a number" - if the size is not valid (not a number)
     */
    static void ValidateSize(const std::string& size);
    /**
     * Function that validates the price of a coat.
     * @param price String - the price to be validated
     * @return -, if the price is valid, an error message otherwise
     * @raises "Price must be a number" - if the price is not valid
     */
    static void ValidatePrice(const std::string& price);
    /**
     * Function that validates the quantity of a coat.
     * @param quantity String - the quantity to be validated
     * @return -, if the quantity is valid, an error message otherwise
     * @raises "Quantity must be a number" - if the quantity is not valid (not a number)
     */
    static void ValidateQuantity(const std::string& quantity);
    /**
     * Function that validates the colour of a coat.
     * @param colour String - the colour to be validated
     * @return -, if the colour is valid, an error message otherwise
     * @raises "Colour must not be empty" - if the colour is not valid (empty string)
     */
    static void ValidateColour(const std::string& colour);
    /**
     * Function that validates the photo of a coat.
     * @param photo String - the photo to be validated
     * @return -, if the photo is valid, an error message otherwise
     * @raises "Photo must not be empty" - if the photo is not valid (empty string)
     */
    static void ValidatePhoto(const std::string& photo);


};