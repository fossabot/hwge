#include <hwge/hwge.hpp>
#include <iostream>

void HWGE::init() {
    std::cout << "HWGE Version: " << HWGE::version() << std::endl;
}

std::string HWGE::version() {
    return HWGE_VERSION;
}