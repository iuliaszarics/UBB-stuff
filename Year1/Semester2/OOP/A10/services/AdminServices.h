

#pragma once

#include <QAbstractItemModel>
#include "Services.h"

#include "UndoServices.h"

class AdminServices : public Services{
private:
    UndoServices undoServices;

public:
    /**
     * Function that takes the input and adds to the repo a coat with the given attributes.
     * @param inputSize String - the size of the coat
     * @param inputColour String - the colour of the coat
     * @param inputPrice String - the price of the coat
     * @param inputQuantity String - the quantity of the coat
     * @param inputPhotograph String - the photograph of the coat
     * @raises RepoException if the coat is already in the repo
     */
    void Add(const string& inputSize, const string& inputColour,
             const string& inputPrice, const string& inputQuantity,
             const string& inputPhotograph);

    /**
     * Function that takes the input and removes from the repo a coat with the given attributes.
     * @param inputSize String - the size of the coat
     * @param inputColour String - the colour of the coat
     * @raises RepoException if the coat is not in the repo
     */
    void Delete(const string& inputSize, const string& inputColour);

    /**
     * Function that takes the input and updates in the repo a coat with the given attributes.
     * @param inputSize String - the size of the coat
     * @param inputColour String - the colour of the coat
     * @param inputNewPrice String - the new price of the coat
     * @param inputNewQuantity String - the new quantity of the coat
     * @param inputNewPhotograph String - the new photograph of the coat
     * @raises RepoException if the coat is not in the repo
     */
    void Update(const string& inputSize, const string& inputColour,
                const string& inputNewPrice, const string& inputNewQuantity,
                const string& inputNewPhotograph);

    void Delete(int position);
    void Undo(){undoServices.Undo();}
    void Redo(){undoServices.Redo();}

    TrenchCoat GetCoat(int position){return _repo->GetData()[position];}

    explicit AdminServices(Repo* repo);
    AdminServices() = default;

};
