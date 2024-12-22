#include "event.h"
#include "time_utils.h"
#include <sstream>

Event::Event() = default;

Event::Event(const EventID id, const unsigned int time, std::string username, const unsigned int table_id)
    : ID_(id)
      , Time_(time)
      , Username_(std::move(username))
      , TableID_(table_id) {
}

Event::Event(const Event &other) = default;

std::string Event::ToString() const {
    std::ostringstream result;

    result << TimeUtils::TimeToString(Time_) << ' '
            << static_cast<int>(ID_) << ' '
            << Username_;
    if (TableID_ != 0) {
        result << ' ' << TableID_;
    }

    return result.str();
}

EventID Event::GetID() const {
    return ID_;
}

void Event::SetID(const EventID id) {
    ID_ = id;
}

unsigned int Event::GetTime() const {
    return Time_;
}

void Event::SetTime(const unsigned int time) {
    Time_ = time;
}

std::string Event::GetUsername() const {
    return Username_;
}

void Event::SetUsername(const std::string &username) {
    Username_ = username;
}

void Event::SetTableID(const unsigned int table_id) {
    TableID_ = table_id;
}

unsigned int Event::GetTableID() const {
    return TableID_;
}
