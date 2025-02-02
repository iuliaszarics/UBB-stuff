
#include "UndoServices.h"

void UndoServices::Record(Operation *operation) {

    // add to the beginning of the vector

    history.insert(history.begin(), operation);
}

void UndoServices::Undo() {

    if(index == history.size())
        throw UndoException("No more undos!");

    history[index]->Undo();
    index++;
}

void UndoServices::Redo() {

    if(!index)
        throw UndoException("No more redos!");

    index--;
    history[index]->Redo();
}

UndoServices::~UndoServices() {

    for(auto & operation : history)
        delete operation;

}
