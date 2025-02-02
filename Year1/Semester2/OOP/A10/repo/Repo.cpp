

#include "../repo/Repo.h"
#include "../utils/Exceptions.h"
#include <iostream>
#include <QStandardItemModel>

void Repo::Add(const TrenchCoat &coat) {

    if(find(_data.begin(), _data.end(), coat) != _data.end())
        throw RepoException("The coat is already in the repo!");

    _data.push_back(coat);

}

TrenchCoat Repo::Delete(const TrenchCoat &coat) {

    auto iter = find(_data.begin(), _data.end(), coat);

    if(iter == _data.end())
        throw RepoException("The coat is not in the repo!");
    auto x = *iter;
    _data.erase(iter);

    return x;
}

TrenchCoat Repo::Update(const TrenchCoat &coat, const TrenchCoat &newCoat) {
    auto iter = find(_data.begin(), _data.end(), coat);

    if(iter == _data.end())
        throw RepoException("The coat is not in the repo!");

    auto x = *iter;
    *iter = newCoat;

    return x;
}

vector<TrenchCoat> Repo::GetData() const {
    return _data;
}

void Repo::Delete(int position) {
    auto iter = _data.begin() + position;

    if(iter == _data.end())
        throw RepoException("The coat is not in the repo!");

    _data.erase(iter);
}
