#pragma once

#include <string>

enum class ClientStatus {
  AT_CLUB = 1,
  WAITING = 2,
  PLAYING = 3
};

class Client {
private:
  std::string Name_;
  ClientStatus Status_;

public:
  Client();

  explicit Client(std::string &name);

  std::string GetName() const;

  void SetName(const std::string &name);

  void SetStatus(ClientStatus status);

  ClientStatus GetStatus() const;

  ~Client();
};
