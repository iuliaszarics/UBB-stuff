#include "CSVDataLoader.h"

void CSVDataLoader::Save(vector<TrenchCoat> vector) {

    ofstream file("data.csv");

    for (auto& i : vector) {
        file << i.getTrenchSize() << "," << i.getTrenchPrice() << "," << i.getTrenchQuantity() << "," << i.getTrenchColour() << "," << i.getTrenchPhotographyLink() << "\n";
    }

    file.close();
}

void CSVDataLoader::Open() {
    system("start data.csv");
}