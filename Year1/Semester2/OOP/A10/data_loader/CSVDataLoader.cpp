

#include "../data_loader/CSVDataLoader.h"
#include "../domain/TrenchCoat.h"

void CSVDataLoader::Save(vector<TrenchCoat> vector) {

    ofstream file("coats.csv");

    for(auto& i : vector) {
        file << i.GetSize() << "," << i.GetPrice() << "," << i.GetQuantity() << "," << i.GetColour() << "," << i.GetPhoto() << "\n";
    }

    file.close();
}

void CSVDataLoader::Open() {
    system("start coats.csv");
}