#pragma once
#include <vector>
#include <fstream>
#include "domain.h"

using std::vector;
using std::ofstream;

class DataLoader {

private:

public:

    /**
     * Function that saves the data from a vector in a file.
     * @param vector vector<TrenchCoat> - the vector which is saved
     */
    virtual void Save(vector<TrenchCoat> vector) = 0;
    /**
     * Function that opens the file in which the data was saved.
     */
    virtual void Open() = 0;
    virtual ~DataLoader() = default;
};