#pragma once

#include "event.h"
#include "validator.h"
#include "event_response.h"
#include <fstream>
#include <string>
#include <vector>

class EventHandler {
private:
  std::ifstream FileStream_;
  Validator DataValidator_;

  void ReloadFileStream();

public:
  explicit EventHandler(const std::string &file_path);

  bool CheckFile();

  std::vector<unsigned int> ReadClubParameters();

  std::pair<bool, Event> ReadEventFromFile();

  void HandleResult(const EventResponse &resp) const;

  ~EventHandler();
};
