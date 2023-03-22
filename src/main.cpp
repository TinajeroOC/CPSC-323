#include <iostream>
#include <string>
#include "compiler/compiler.h"

int main() {
    Compiler compiler;
    std::string sourceFileName;

    std::cout << "Input the source file name: ";
    std::cin >> sourceFileName;
    compiler.run(sourceFileName);

    return 0;
}