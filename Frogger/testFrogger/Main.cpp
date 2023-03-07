#include "Program.h"
#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    try {
        Application app;
        app.run();
    }
    catch (std::exception& e) {
        std::cout <<  e.what() << std::endl;
    }
}