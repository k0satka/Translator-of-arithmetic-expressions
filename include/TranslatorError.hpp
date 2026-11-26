#pragma once

#include <stdexcept>
#include <string>

class TranslatorError : public std::runtime_error {
private:
    std::string stage_;
    size_t position_;

public:
    TranslatorError(const std::string& stage, const std::string& message, size_t position): std::runtime_error(message), stage_(stage), position_(position) {};

    const std::string& stage() const noexcept {
        return stage_;
    };

    size_t position() const noexcept {
        return position_;
    };
};

class LexicalError : public TranslatorError {
public:
    LexicalError(const std::string& message, std::size_t position) : TranslatorError("LexicalError", message, position) {};
};

class SyntaxError : public TranslatorError {
public:
    SyntaxError(const std::string& message, size_t position) : TranslatorError("SyntaxError", message, position) {};
};

class EvaluatorError : public TranslatorError {
public:
    EvaluatorError(const std::string& message, size_t position) : TranslatorError("EvaluatorError", message, position) {};
};

class PostfixError : public TranslatorError {
public:
    PostfixError(const std::string& message, size_t position) : TranslatorError("PostfixError", message, position) {};
};