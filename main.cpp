#include <string>
#include <iostream>
#include "enums.hpp"
#include "generated_maps.hpp"

int main() {
    Color c = GREEN;
    Direction d = WEST;

    std::cout << "Color: " << ColorToString[c] << std::endl;
    std::cout << "Direction: " << DirectionToString[d - 1] << std::endl;

    // Reverse lookup
    std::string input = "BLUE";
    Color c2 = StringToColor[input];
    std::cout << "Reverse lookup (\"BLUE\") = Enum value: " << c2 << " = " << ColorToString[c2] << std::endl;

    return 0;
}

