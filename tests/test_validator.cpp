#include <catch2/catch_test_macros.hpp>
#include "event_handler.h"

TEST_CASE("EventHandler::CheckFile - Valid data") {
    const std::string valid_file = std::string(TEST_DATA_DIR) + "/test_file.txt";
    EventHandler handler(valid_file);
    REQUIRE(handler.CheckFile() == true);
}

TEST_CASE("EventHandler::CheckFile - No club parameters") {
    const std::string no_club_parameters_file = std::string(TEST_DATA_DIR) + "/test_no_club_parameters.txt";
    EventHandler handler(no_club_parameters_file);
    REQUIRE(handler.CheckFile() == false);
}

TEST_CASE("EventHandler::CheckFile - Broken Time Format") {
    const std::string invalid_time_format_file = std::string(TEST_DATA_DIR) + "/test_invalid_time_format.txt";
    EventHandler handler(invalid_time_format_file);
    REQUIRE(handler.CheckFile() == false);
}

TEST_CASE("EventHandler::CheckFile - Reversed TimeStamps") {
    const std::string reversed_timestamps_file = std::string(TEST_DATA_DIR) + "/test_reversed_timestamps.txt";
    EventHandler handler(reversed_timestamps_file);
    REQUIRE(handler.CheckFile() == false);
}

TEST_CASE("EventHandler::CheckFile - Non existing eventIDs") {
    const std::string non_existing_eventID_file = std::string(TEST_DATA_DIR) + "/non_existing_eventID.txt";
    EventHandler handler(non_existing_eventID_file);
    REQUIRE(handler.CheckFile() == false);
}
