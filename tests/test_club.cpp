#include <catch2/catch_test_macros.hpp>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include "club.h"

TEST_CASE("Valid data") {
    const std::string valid_file = std::string(TEST_DATA_DIR) + "/test_file.txt";
    const std::string expected_output_file = std::string(TEST_DATA_DIR) + "/expected_output.txt";
    const std::string actual_output_file = "actual_output.txt";

    std::ofstream output_file(actual_output_file);
    REQUIRE(output_file.is_open());

    std::streambuf* original_cout = std::cout.rdbuf();
    std::cout.rdbuf(output_file.rdbuf());

    Club club_manager(valid_file);
    club_manager.StartServing();

    std::cout.rdbuf(original_cout);
    output_file.close();

    std::ifstream actual_output(actual_output_file);
    std::ifstream expected_output(expected_output_file);
    REQUIRE(actual_output.is_open());
    REQUIRE(expected_output.is_open());

    std::stringstream actual_stream, expected_stream;
    actual_stream << actual_output.rdbuf();
    expected_stream << expected_output.rdbuf() << std::endl;

    REQUIRE(actual_stream.str() == expected_stream.str());

    actual_output.close();
    expected_output.close();
}
