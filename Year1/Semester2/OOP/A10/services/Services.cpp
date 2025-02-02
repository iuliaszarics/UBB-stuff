

#include "Services.h"

vector<TrenchCoat> Services::GetData() {
    return _repo->GetData();
}

Services::Services(Repo* repo) {

    _repo = repo;
}

Services::Services(){
    _repo = new Repo;
}

Services::~Services(){
    //delete _repo;
}

