#pragma once

#include <string>

using std::string;
using std::istream;
using std::ostream;

class TrenchCoat
{
private:

    int _size,_price,_quantity;
    std::string _colour,_photo;
public:

    TrenchCoat();

    TrenchCoat(int size, int price, int quantity,
               std::string colour, std::string coat);

    TrenchCoat(const TrenchCoat& coat);


    int GetSize();

    int GetPrice() const;

    int GetQuantity();

    std::string GetColour() const;

    std::string GetPhoto();

    bool operator==(const TrenchCoat& other);

    std::string ToString() const;

    void SetQuantity(int quantity);

    friend ostream& operator<<(ostream& os, const TrenchCoat& coat);

    friend istream& operator>>(istream& os, TrenchCoat& coat);

};