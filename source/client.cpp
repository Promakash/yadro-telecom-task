#include "client.h"

Client::Client() : Status_(ClientStatus::AT_CLUB) {
}

Client::Client(std::string &name) : Name_(std::move(name)), Status_(ClientStatus::AT_CLUB) {
}

std::string Client::GetName() const {
    return Name_;
}

void Client::SetName(const std::string &name) {
    Name_ = name;
}

void Client::SetStatus(ClientStatus status) {
    Status_ = status;
}

ClientStatus Client::GetStatus() const {
    return Status_;
}

Client::~Client() = default;
