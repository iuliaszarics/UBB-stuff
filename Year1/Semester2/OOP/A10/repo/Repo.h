
#pragma once

#include "../domain/TrenchCoat.h"
#include <vector>
#include <algorithm>
#include <QAbstractItemModel>
#include "../utils/Exceptions.h"

using std::vector, std::find;


class Repo{

protected:
    vector<TrenchCoat> _data;

public:

    /**
    *  Function that adds a coat to the repo.
    * @param coat Coat - the coat to be added
    * @raises RepoException if the coat is already in the repo
    */
    virtual void Add(const TrenchCoat& coat);

    /**
     * Function that deletes a coat from the repo.
     * @param coat Coat - the coat to be deleted
     * @raises RepoException if the coat is not in the repo
     */
    virtual TrenchCoat Delete(const TrenchCoat& coat);

    virtual void Delete(int position);

    /**
     * Function that updates a coat from the repo.
     * @param coat Coat - the coat to be updated
     * @param newCoat Coat - the new coat
     * @raises RepoException if the coat is not in the repo
     */
    virtual TrenchCoat Update(const TrenchCoat& coat, const TrenchCoat& newCoat);

    /**
     * Function that returns the coats from the repo.
     * @return vector<TrenchCoat> - the coats from the repo.
     */
    vector<TrenchCoat> GetData() const;
};
