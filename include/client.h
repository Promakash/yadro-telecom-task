#pragma once

#include <string>

//Сущность клиент, с сеттерами и геттерами

class Client {
private:
  std::string Name_;

public:
  Client();

  explicit Client(std::string &name);

  std::string GetName() const;

  void SetName(const std::string &name);

  ~Client();
};
