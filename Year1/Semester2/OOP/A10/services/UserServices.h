

#pragma once

#include "Services.h"
#include "../repo/FileRepo.h"
#include "../data_loader/DataLoader.h"

using std::stoi, std::copy_if;

class UserServices : public Services {

private:

    int _totalPrice{0};
    TrenchCoat _currentCoat;
    vector<TrenchCoat> _filteredCoats;
    vector<TrenchCoat> _shoppingBasket;

    DataLoader* _dataLoader;

public:

    //GETTERS

    int GetTotalPrice() const;

    TrenchCoat GetCurrentCoat() const;

    vector<TrenchCoat> GetShoppingBasket() const;

    /**
     * Function that filters the coats by size, or returns all the coats if the size is empty.
     * The filtered coats are stored in the _filteredCoats vector.
     * @param size String - the size of the coats
     */
    void FilterBySize(const std::string& size);

    /**
     * Function that gets the next coat from the filtered coats, or the first coat if the current coat is the last one.
     * The current coat is stored in the _currentCoat variable.
     */
    void NextCoat();

    /**
     * Function that adds the current coat to the shopping basket.
     */
    void AddCurrentCoat();

    /**
     * Function that opens the shopping basket saved by DataLoader.
     */
    void Open();

    explicit UserServices(Repo* repo, DataLoader* dataLoader);

    explicit UserServices(Repo* repo);

    UserServices();

    void SetDataLoader(DataLoader* dataLoader);

    ~UserServices();

    void InitCSVLoader();

    void InitHTMLLoader();
};