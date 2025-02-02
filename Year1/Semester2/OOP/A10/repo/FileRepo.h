
#pragma once


#include "Repo.h"
#include <fstream>
using std::string;
using std::ifstream;
using std::ofstream;

class FileRepo : public Repo{

private:
    string _filepath;

    void LoadData();
    void SaveData();

public:

    explicit FileRepo(const string& filename);

    void Add(const TrenchCoat& coat) override;
    TrenchCoat Delete(const TrenchCoat& coat) override;
    void Delete(int position) override;
    TrenchCoat Update(const TrenchCoat& coat, const TrenchCoat& newCoat) override;

};
