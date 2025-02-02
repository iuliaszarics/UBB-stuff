#pragma once

#include "../repo/Repo.h"
#include "../domain/TrenchCoat.h"

class Services{

protected:

    Repo* _repo;

public:

    explicit Services(Repo* repo);

    Services();
    ~Services();
    vector<TrenchCoat> GetData();

};