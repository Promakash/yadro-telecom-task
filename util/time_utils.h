#pragma once

#include <string>
#include <sstream>

class TimeUtils {
  public:
    static unsigned int ConvertTimeToMinutes(const std::string& str_time) {
        unsigned int hours, minutes;
        char colon;
        std::istringstream stream(str_time);
        if (stream >> hours >> colon >> minutes) {
            return hours * 60 + minutes;
        }
        else {
            throw std::runtime_error("Invalid time format: " + str_time);
        }
    }

    static std::string TimeToString(const unsigned int time) {
        unsigned int hours = time / 60;
        unsigned int minutes = time % 60;

        std::ostringstream time_str;
        if (hours < 10) {
            time_str << '0';
        }
        time_str << hours << ':';
        if (minutes < 10) {
            time_str << '0';
        }
        time_str << minutes;

        return time_str.str();
    }

};