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
    catch (const std::runtime_error& e) {
        std::cout << "Runtime exception was caught: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}