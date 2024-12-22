#include "validator.h"
#include "time_utils.h"
#include <sstream>

Validator::Validator(unsigned int total_tables) : TotalTables_(total_tables) {
}

unsigned int Validator::GetTotalTables() const {
    return TotalTables_;
}

void Validator::SetTotalTables(unsigned int total_tables) {
    TotalTables_ = total_tables;
}

bool Validator::ValidateTableCount(const std::string &line) const {
    return std::regex_match(line, UIntValuePattern_);
}

bool Validator::ValidateWorkingHours(const std::string &line) const {
    std::istringstream stream(line);
    std::string start_time, end_time;
    if (!(stream >> start_time >> end_time)) {
        return false;
    }

    return TimeUtils::ConvertTimeToMinutes(start_time) < TimeUtils::ConvertTimeToMinutes(end_time);
}

bool Validator::ValidateEvent(const std::string &line, unsigned int last_event_time) const {
    if (!std::regex_match(line, EventPattern_)) {
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
        if (table_id > TotalTables_) {
            return false;
        }
    }

    return true;
}
