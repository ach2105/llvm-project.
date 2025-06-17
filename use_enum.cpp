#include <iostream>

extern const char* __nameof_Color[];

int main() {
    std::cout << "Enum name for value 0: " << __nameof_Color[0] << "\n";
    std::cout << "Enum name for value 1: " << __nameof_Color[1] << "\n";
    std::cout << "Enum name for value 2: " << __nameof_Color[2] << "\n";
    return 0;
}
