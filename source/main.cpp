#include "club.h"
#include <iostream>

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        std::cout << "Not enough arguments" << std::endl;
        return 1;
    }
    std::string file_path = argv[1];
    try {
        Club club_manager(file_path);
        club_manager.StartServing();
    }
    catch (const std::exception& e) {
        std::cout << "Unxpected exception was caught" << e.what() << std::endl;
    }

    return 0;
}