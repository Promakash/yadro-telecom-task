#pragma once
#include <regex>
#include <string>
#include <sstream>
#include <iostream>
#include "time_utils.h"

class Validator {
private:
    std::regex UIntValuePattern{"^[1-9][0-9]*$"};
    std::regex TimePattern{"^[0-9]{2}:[0-9]{2} [0-9]{2}:[0-9]{2}$"};
    std::regex EventPattern{"^[0-9]{2}:[0-9]{2} [1-4] [a-zA-Z0-9_-]+ ?[0-9]*$"};
    unsigned int TotalTables;

public:
    Validator(unsigned int total_tables) : TotalTables(total_tables) {}

    unsigned int GetTotalTables() const {
        return TotalTables;
    }

    void SetTotalTables(const unsigned int total_tables) {
        TotalTables = total_tables;
    }

    bool ValidateTableCount(const std::string& line) const {
        return std::regex_match(line, UIntValuePattern);
    }

    bool ValidateWorkingHours(const std::string& line) const {
        std::istringstream stream(line);
        std::string start_time, end_time;
        if (!(stream >> start_time >> end_time)) {
            return false;
        }

        return TimeUtils::ConvertTimeToMinutes(start_time) < TimeUtils::ConvertTimeToMinutes(end_time);
    }

    bool ValidateEvent(const std::string& line, unsigned int last_event_time) const {
        if (!std::regex_match(line, EventPattern)) {
            return false;
        }

        std::istringstream event_stream(line);
        std::string event_time, event_id_str, event_body;
        unsigned int table_id = 0;

        if (!(event_stream >> event_time >> event_id_str >> event_body)) {
            return false;
        }

        unsigned int event_minutes = TimeUtils::ConvertTimeToMinutes(event_time);
        if (event_minutes < last_event_time) {
            return false;
        }

        if (event_stream >> table_id) {
            if (table_id > TotalTables) {
                return false;
            }
        }

        return true;
    }
};
