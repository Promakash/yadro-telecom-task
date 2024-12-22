#pragma once

#include <regex>
#include <string>

class Validator {
private:
    std::regex UIntValuePattern_{"^[1-9][0-9]*$"};
    std::regex TimePattern_{"^[0-9]{2}:[0-9]{2} [0-9]{2}:[0-9]{2}$"};
    std::regex EventPattern_{"^[0-9]{2}:[0-9]{2} [1-4] [a-zA-Z0-9_-]+ ?[1-9][0-9]*$"};
    unsigned int TotalTables_;

public:
    explicit Validator(unsigned int total_tables);

    unsigned int GetTotalTables() const;

    void SetTotalTables(unsigned int total_tables);

    bool ValidateTableCount(const std::string &line) const;

    bool ValidateWorkingHours(const std::string &line) const;

    bool ValidateEvent(const std::string &line, unsigned int last_event_time) const;
};
