
#include "../services/AdminServices.h"
#include "../utils/utils.h"
#include "../services/Operation.h"

void AdminServices::Add(const string &inputSize, const string& inputColour, const string &inputPrice, const string &inputQuantity,
                        const string& inputPhotograph) {

    //Make a coat
    TrenchCoat coat = TrenchCoat(Utils::StringToNumber(inputSize), Utils::StringToNumber(inputPrice),
                                  Utils::StringToNumber(inputQuantity), inputColour, inputPhotograph);

    _repo->Add(coat);

    auto operation = new AddOperation(_repo, coat, coat);

    undoServices.Record(operation);
}

void AdminServices::Delete(const string &inputSize, const string& inputColour) {

    TrenchCoat coat = TrenchCoat(Utils::StringToNumber(inputSize),
                                 0, 0, inputColour, "");

    auto x = _repo->Delete(coat);

    auto operation = new DeleteOperation(_repo, x, x);
    undoServices.Record(operation);
}

void AdminServices::Update(const string &inputSize, const string& inputColour, const string &inputNewPrice,
                           const string &inputNewQuantity, const string& inputNewPhotograph) {

    TrenchCoat coat = TrenchCoat(Utils::StringToNumber(inputSize), 0, 0, inputColour, "");
    TrenchCoat newCoat = TrenchCoat(Utils::StringToNumber(inputSize), Utils::StringToNumber(inputNewPrice),
                                    Utils::StringToNumber(inputNewQuantity), inputColour, inputNewPhotograph);

    auto x = _repo->Update(coat, newCoat);

    auto operation = new UpdateOperation(_repo, x, newCoat);
    undoServices.Record(operation);

}

AdminServices::AdminServices(Repo* repo) : Services(repo) {
}

void AdminServices::Delete(int position) {
    _repo->Delete(position);
}


