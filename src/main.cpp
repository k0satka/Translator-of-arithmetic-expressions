#include "Translator.hpp"
#include "TranslatorError.hpp"
#include <iostream>
#include <exception>

int main() {
    std::string str;

    std::cout << "Translator of arithmetic expressions.\n";
    std::cout << "Type 'exit' to quit.\n\n";

    while (true) {
        std::cout << ">>> ";

        if (!std::getline(std::cin, str)) break;

        if (str == "exit") break;

        if (str.empty()) continue;

        try {
            std::cout << Translator::translate(str) << '\n';
        }
        catch (const TranslatorError& e) {
            if (e.position() != std::string::npos) {
                std::cout << str << '\n' << std::string(e.position(), ' ') << '^' << '\n';
            }

            std::cout << e.stage() << ": " << e.what() << '\n';
        }
        catch (const std::exception& e) {
            std::cerr << e.what() << '\n';
        }
    }

    return 0;
}