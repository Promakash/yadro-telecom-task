#include "client.h"

Client::Client() = default;

Client::Client(std::string &name) : Name_(std::move(name)) {
}

std::string Client::GetName() const {
    return Name_;
}

void Client::SetName(const std::string &name) {
    Name_ = name;
}

Client::~Client() = default;
