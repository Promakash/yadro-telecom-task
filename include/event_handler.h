#pragma once
#include <fstream>
#include <string>
#include <iostream>
#include <stdexcept>
#include <vector>
#include "event.h"
#include "validator.h"
#include "event_response.h"
#include "time_utils.h"

class EventHandler {
private:
  std::ifstream FileStream;
  Validator DataValidator;

  void ReopenFile() {
  }

public:
  EventHandler(const std::string &file_path)
    : FileStream(file_path)
      , DataValidator(0) {
    if (!FileStream.is_open()) {
      throw std::runtime_error("Error: Cannot open file: " + file_path);
    }
  }

  bool CheckFile() {
    std::string line;
    unsigned int line_number = 1;
    unsigned int last_event_time = 0;
    bool is_valid = true;

    while (std::getline(FileStream, line)) {
      switch (line_number) {
        case 1: {
          is_valid = DataValidator.ValidateTableCount(line);
          if (!is_valid) {
            break;
          }
          unsigned int table_count = std::stoul(line);
          DataValidator.SetTotalTables(table_count);
          break;
        }

        case 2: {
          is_valid = DataValidator.ValidateWorkingHours(line);
          break;
        }

        case 3: {
          is_valid = DataValidator.ValidateTableCount(line);
          break;
        }

        default: {
          const int time_length = 5;
          if (!DataValidator.ValidateEvent(line, last_event_time)) {
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

    FileStream.clear();
    FileStream.seekg(0, std::ios::beg);

    return is_valid;
  }

  std::vector<unsigned int> ReadClubParameters() {
    std::vector<unsigned int> parameters;
    std::string line;

    if (std::getline(FileStream, line)) {
      parameters.push_back(std::stoul(line));
    }

    if (std::getline(FileStream, line)) {
      std::istringstream stream(line);
      std::string start_time, end_time;

      if (stream >> start_time >> end_time) {
        parameters.push_back(TimeUtils::ConvertTimeToMinutes(start_time));
        parameters.push_back(TimeUtils::ConvertTimeToMinutes(end_time));
      } else {
        throw std::runtime_error("Can't read time");
      }
    }

    if (std::getline(FileStream, line)) {
      parameters.push_back(std::stoul(line));
    }

    return parameters;
  }

  std::pair<bool, Event> ReadEventFromFile() {
    std::string line;

    if (std::getline(FileStream, line)) {
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

  void HandleResult(const EventResponse &resp) {
    std::cout << resp.ToString() << std::endl;
  }

  ~EventHandler() {
    if (FileStream.is_open()) {
      FileStream.close();
    }
  }
};
