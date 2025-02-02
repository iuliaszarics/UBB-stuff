

#pragma once

#include <exception>
#include <string>
#include <utility>

using std::string;
using std::exception;

class RepoException : public exception {

private:
    string _message;

public:

    explicit RepoException(string message) : _message(std::move(message)) {}

    const char *what() const noexcept override {
        return _message.c_str();
    }
};

class ValidatorException : public exception {

private:
    string _message;

public:

    explicit ValidatorException(string message) : _message(std::move(message)) {}

    const char *what() const noexcept override {
        return _message.c_str();
    }

};

class ServicesException : public exception {

private:
    string _message;

public:

    explicit ServicesException(string message) : _message(std::move(message)) {}

    const char *what() const noexcept override {
        return _message.c_str();
    }
};
