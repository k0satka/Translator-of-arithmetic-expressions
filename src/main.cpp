#include "Translator.hpp"
#include <iostream>
#include <exception>
#include <windows.h>

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
        catch (const std::exception& e) {
            std::cerr << e.what() << '\n';
        }
    }

    return 0;
}