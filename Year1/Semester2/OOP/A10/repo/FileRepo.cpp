
#include <iostream>
#include "FileRepo.h"
#include "../utils/Exceptions.h"

FileRepo::FileRepo(const string &filename) : Repo() {

    _filepath = filename;
    LoadData();

}

void FileRepo::LoadData() {

    std::ifstream file(_filepath);

    if(!file.is_open())
        throw RepoException("Could not open the file");

    while(!file.eof()) {

        TrenchCoat coat;
        file >> coat;

        if(file.eof()) {
            break;
        }

        _data.push_back(coat);


    }

    file.close();
}

void FileRepo::SaveData() {

    std::ofstream file(_filepath);

    if(!file.is_open())
        throw RepoException("Could not open the file");

    for(const auto& coat : _data){
        file << coat<<'\n';
    }

    file.close();
}

void FileRepo::Add(const TrenchCoat &coat) {
    Repo::Add(coat);
    SaveData();

}

TrenchCoat FileRepo::Delete(const TrenchCoat &coat) {
   auto x = Repo::Delete(coat);
    SaveData();

    return  x;
}

TrenchCoat FileRepo::Update(const TrenchCoat &coat, const TrenchCoat &newCoat) {
    auto x = Repo::Update(coat, newCoat);
    SaveData();

    return x;

}

void FileRepo::Delete(int position) {
    Repo::Delete(position);
    SaveData();
}




