
#include "../domain/TrenchCoat.h"
#include "../repo/Repo.h"
#include "Operation.h"

Operation::Operation(Repo *_repo, const TrenchCoat& _undoCoat, const TrenchCoat& _redoCoat) {
    repo = _repo;
    undoCoat = _undoCoat;
    redoCoat = _redoCoat;
}

AddOperation::AddOperation(Repo *repo, const TrenchCoat &_undoCoat, const TrenchCoat &_redoCoat)
: Operation(repo, _undoCoat, _redoCoat) {}

void AddOperation::Undo() {
    repo->Delete(undoCoat);
}

void AddOperation::Redo() {
    repo->Add(redoCoat);
}

DeleteOperation::DeleteOperation(Repo *repo, const TrenchCoat &_undoCoat, const TrenchCoat &_redoCoat)
: Operation(repo, _undoCoat, _redoCoat) {}

void DeleteOperation::Undo() {
    repo->Add(undoCoat);
}

void DeleteOperation::Redo() {
    repo->Delete(redoCoat);
}

UpdateOperation::UpdateOperation(Repo *repo, const TrenchCoat &_undoCoat, const TrenchCoat &_redoCoat)
: Operation(repo, _undoCoat, _redoCoat) {}

void UpdateOperation::Undo() {
    repo->Update(redoCoat, undoCoat);
}

void UpdateOperation::Redo() {
    repo->Update(undoCoat, redoCoat);
}



