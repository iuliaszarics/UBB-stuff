
#include "../domain/TrenchCoat.h"
#include "../repo/Repo.h"

class Operation {

protected:

    TrenchCoat undoCoat, redoCoat;
    Repo* repo;

public:

    Operation(Repo* _repo, const TrenchCoat& _undoCoat, const TrenchCoat& _redoCoat);

    virtual void Undo() = 0;
    virtual void Redo() = 0;

    virtual ~Operation() = default;
};

class AddOperation : public Operation {

public:
    AddOperation(Repo *repo, const TrenchCoat &_undoCoat, const TrenchCoat &_redoCoat);

    void Undo() override;
    void Redo() override;

    ~AddOperation() override = default;
};

class DeleteOperation : public Operation {

public:
    DeleteOperation(Repo *repo, const TrenchCoat &_undoCoat, const TrenchCoat &_redoCoat);

    void Undo() override;
    void Redo() override;

    ~DeleteOperation() override = default;
};

class UpdateOperation : public Operation {

public:
    UpdateOperation(Repo *repo, const TrenchCoat &_undoCoat, const TrenchCoat &_redoCoat);

    void Undo() override;
    void Redo() override;

    ~UpdateOperation() override = default;
};


