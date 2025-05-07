#include <iostream>
#include "engine/dwn_engine.hpp"
int main() {
    DwnEngine engine("dwn_engine", 800, 600);
    engine.initialize();
    engine.run();

    
    
    std::cout << "Hello, World!" << std::endl;
    return 0;
}