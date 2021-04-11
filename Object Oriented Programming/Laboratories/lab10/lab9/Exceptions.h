#pragma once

#include <exception>
#include <iostream>
#include <string>
#include <utility>


class RepositoryError : public std::exception {
private:
    const char* message;
public:
    explicit RepositoryError(const char* msg) {
        this->message = msg;
    }

    [[nodiscard]] const char * what() const noexcept override {
        return message;
    }
};


class ControllerError : public std::exception {
private:
    const char* message;
public:
    explicit ControllerError(const char* msg) {
        this->message = msg;
    }
    [[nodiscard]] const char * what() const noexcept override {
        return message;
    }
};


class UIError : public std::exception {
private:
    const char* message;
public:
    explicit UIError(const char* msg) {
        this->message = msg;
    }
    [[nodiscard]] const char * what() const noexcept override {
        return message;
    }
};


class FileError : public std::exception {
private:
    const char* message;
public:
    explicit FileError(const char* msg) {
        this->message = msg;
    }
    [[nodiscard]] const char * what() const noexcept override {
        return message;
    }
};


class ValidationError : public std::exception {
private:
    const char* message;
public:
    explicit ValidationError(const char* msg) {
        this->message = msg;
    }
    [[nodiscard]] const char * what() const noexcept override {
        return message;
    }
};