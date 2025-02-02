

#include "Operation.h"

class UndoServices {

private:

    vector<Operation*> history;
    int index;

public:

    UndoServices() = default;

    void Record(Operation *operation);
    void Undo();
    void Redo();

    ~UndoServices();
};


class UndoException : public exception {

private:
    string message;

public:

    explicit UndoException(string message){
        this->message = std::move(message);

    }

    const char *what() const noexcept override{
        return message.c_str();
    }

    ~UndoException() override = default;

};

