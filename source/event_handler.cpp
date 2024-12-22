#include "event_handler.h"
#include "time_utils.h"
#include <iostream>
#include <sstream>
#include <stdexcept>

void EventHandler::ReloadFileStream() {
    FileStream_.clear();
    FileStream_.seekg(0, std::ios::beg);
}

EventHandler::EventHandler(const std::string &file_path)
    : FileStream_(file_path), DataValidator_(0) {
    if (!FileStream_.is_open()) {
        throw std::runtime_error("Error: Cannot open file: " + file_path);
    }
}

bool EventHandler::CheckFile() {
    std::string line;
    unsigned int line_number = 1;
    unsigned int last_event_time = 0;
    bool is_valid = true;

    while (std::getline(FileStream_, line)) {
        switch (line_number) {
            case 1: {
                is_valid = DataValidator_.ValidateTableCount(line);
                if (!is_valid) {
                    break;
                }
                unsigned int table_count = std::stoul(line);
                DataValidator_.SetTotalTables(table_count);
                break;
            }

            case 2: {
                is_valid = DataValidator_.ValidateWorkingHours(line);
                break;
            }

            case 3: {
                is_valid = DataValidator_.ValidateTableCount(line);
                break;
            }

            default: {
                constexpr int time_length = 5;
                if (!DataValidator_.ValidateEvent(line, last_event_time)) {
                    is_valid = false;
                    break;
                }
                last_event_time = TimeUtils::ConvertTimeToMinutes(line.substr(0, time_length));
                break;
            }
        }

        if (!is_valid) {
            std::cerr << "Invalid format at line " << line_number << ": " << line << std::endl;
            break;
        }

        ++line_number;
    }

    ReloadFileStream();
    return is_valid;
}

std::vector<unsigned int> EventHandler::ReadClubParameters() {
    std::vector<unsigned int> parameters;
    std::string line;

    if (std::getline(FileStream_, line)) {
        parameters.push_back(std::stoul(line));
    }

    if (std::getline(FileStream_, line)) {
        std::istringstream stream(line);
        std::string start_time, end_time;

        if (stream >> start_time >> end_time) {
            parameters.push_back(TimeUtils::ConvertTimeToMinutes(start_time));
            parameters.push_back(TimeUtils::ConvertTimeToMinutes(end_time));
        } else {
            throw std::runtime_error("Can't read time");
        }
    }

    if (std::getline(FileStream_, line)) {
        parameters.push_back(std::stoul(line));
    }

    return parameters;
}

std::pair<bool, Event> EventHandler::ReadEventFromFile() {
    std::string line;

    if (std::getline(FileStream_, line)) {
        std::istringstream event_stream(line);
        std::string event_time, username;
        unsigned int event_id = 0, table_id = 0;

        event_stream >> event_time >> event_id >> username;
        unsigned int event_minutes = TimeUtils::ConvertTimeToMinutes(event_time);

        if (event_stream >> table_id) {
            return {true, Event(static_cast<EventID>(event_id), event_minutes, username, table_id)};
        }

        return {true, Event(static_cast<EventID>(event_id), event_minutes, username, 0)};
    }

    return {false, Event{}};
}

void EventHandler::HandleResult(const EventResponse &resp) const{
    std::cout << resp.ToString() << std::endl;
}

EventHandler::~EventHandler() {
    if (FileStream_.is_open()) {
        FileStream_.close();
    }
}
