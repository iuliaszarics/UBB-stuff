

#include <stdexcept>
#include <iostream>
#include "UserServices.h"
#include "../utils/Exceptions.h"
#include "../data_loader/CSVDataLoader.h"
#include "../data_loader/HTMLDataLoader.h"


int UserServices::GetTotalPrice() const {
    return _totalPrice;
}

TrenchCoat UserServices::GetCurrentCoat() const {
    return _currentCoat;
}

vector<TrenchCoat> UserServices::GetShoppingBasket() const {
    return _shoppingBasket;
}

void UserServices::FilterBySize(const std::string &size) {
    _filteredCoats.clear();

    auto vector = _repo->GetData();

    // If the size is empty, get the whole vector
    if(size.empty()){
        _filteredCoats = vector;

        if(_filteredCoats.empty())
            throw ServicesException("No coats with the given size!");

        _currentCoat = _filteredCoats.front();
        return;
    }

    int sizeInt = stoi(size);

    // Use copy_if to put in the _filteredCoats only the coats with
    // the size equal to sizeInt

    copy_if(vector.begin(), vector.end(), back_inserter(_filteredCoats), [sizeInt](TrenchCoat coat){
        return coat.GetSize() == sizeInt;
    });

    if(_filteredCoats.empty())
        throw ServicesException("No coats with the given size!");

    _currentCoat = _filteredCoats.front();
}

void UserServices::NextCoat() {

    if(_currentCoat == _filteredCoats.back())
        _currentCoat = _filteredCoats.front();
    else
        _currentCoat = _filteredCoats[std::find(_filteredCoats.begin(), _filteredCoats.end(), _currentCoat) - _filteredCoats.begin() + 1];
}

void UserServices::AddCurrentCoat() {

    unsigned int index = find(_shoppingBasket.begin(), _shoppingBasket.end(), _currentCoat) - _shoppingBasket.begin();

    // The coat is already in the shopping basket
    if(index != _shoppingBasket.size())
    {
        if(_shoppingBasket[index].GetQuantity() >= _currentCoat.GetQuantity())
            throw ServicesException("The coat is out of stock!");
        _totalPrice += _currentCoat.GetPrice();
        _shoppingBasket[index].SetQuantity(_shoppingBasket[index].GetQuantity() + 1);
        _dataLoader->Save(_shoppingBasket);
    }
    else{
        TrenchCoat aux(_currentCoat);
        aux.SetQuantity(1);
        _totalPrice += _currentCoat.GetPrice();
        _shoppingBasket.push_back(aux);
        _dataLoader->Save(_shoppingBasket);
    }
}

void UserServices::Open() {
    _dataLoader->Open();
}

UserServices::UserServices(Repo* repo, DataLoader* dataLoader) : Services(repo) {
    _dataLoader = dataLoader;
    _dataLoader->Save(_shoppingBasket);
}

UserServices::UserServices(Repo *repo) : Services(repo){
}

UserServices::~UserServices() {

    delete _dataLoader;
}

UserServices::UserServices() {}


void UserServices::InitCSVLoader() {
    _dataLoader = new CSVDataLoader();
    _dataLoader->Save(_shoppingBasket);
}

void UserServices::InitHTMLLoader() {
    _dataLoader = new HTMLDataLoader();
    _dataLoader->Save(_shoppingBasket);
}
