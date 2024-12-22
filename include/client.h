#pragma once

#include "string"

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
  Client() {
    Status_ = ClientStatus::AT_CLUB;
  }

  Client(const std::string& name) : Client() {
    Name_ = name;
  }

  std::string GetName() {
    return Name_;
  }

  void SetName(const std::string& name) {
    Name_ = name;
  }

  void SetStatus(const ClientStatus status) {
    Status_ = status;
  }

  ClientStatus GetStatus() const {
    return Status_;
  }

  ~Client() = default;
};
