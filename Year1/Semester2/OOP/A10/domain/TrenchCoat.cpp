

#include "TrenchCoat.h"
#include <iostream>

TrenchCoat::TrenchCoat() {

    _photo = "";
}

TrenchCoat::TrenchCoat(int size, int price, int quantity, std::string colour, std::string coat) {
    _size = size;
    _price = price;
    _quantity = quantity;
    _colour = colour;
    _photo = coat;
}

TrenchCoat::TrenchCoat(const TrenchCoat &coat) {
    _size = coat._size;
    _price = coat._price;
    _quantity = coat._quantity;
    _colour = coat._colour;
    _photo = coat._photo;
}


int TrenchCoat::GetPrice() const {
    return this->_price;
}

int TrenchCoat::GetQuantity() {
    return this->_quantity;
}

int TrenchCoat::GetSize() {
    return this->_size;
}

std::string TrenchCoat::GetColour() const {
    return this->_colour;
}

std::string TrenchCoat::GetPhoto() {
    return this->_photo;
}

//TrenchCoat &TrenchCoat::operator<<(std::ostream &os) {
//    std::cout<<":3";
//}

bool TrenchCoat::operator==(const TrenchCoat &other) {
    return this->_size == other._size && this->_colour == other._colour;
}

std::string TrenchCoat::ToString() const {
    return "Size: " + std::to_string(_size) + " Price: " + std::to_string(_price) + " Quantity: " + std::to_string(_quantity) + " Colour: " + _colour;
}

void TrenchCoat::SetQuantity(int quantity) {
    _quantity = quantity;
}

ostream &operator<<(ostream &os, const TrenchCoat &coat) {

    os<<coat._size<<" "<<coat._price<<" "<<coat._quantity<<" "<<coat._colour<<" "<<coat._photo;

    return os;
}

istream &operator>>(istream &is, TrenchCoat &coat) {

    is>>coat._size>>coat._price>>coat._quantity>>coat._colour>>coat._photo;

    return is;
}
