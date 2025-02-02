

#pragma once

#include <vector>
#include <fstream>
#include "../domain/TrenchCoat.h"

using std::vector;
using std::ofstream;

class DataLoader {

private:

public:

    /**
     * Function that saves the coats from a vector in a file.
     * @param vector vector<TrenchCoat> - the vector which is saved
     */
    virtual void Save(vector<TrenchCoat> vector) {};
    /**
     * Function that opens the file in which the coats was saved.
     */
    virtual void Open() {};
    virtual ~DataLoader() = default;
};