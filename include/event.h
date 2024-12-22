#pragma once

#include <string>
#include <utility>
#include <sstream>
#include "time_utils.h"

enum class EventID {
    COME = 1,
    SIT = 2,
    WAIT = 3,
    LEAVE = 4,
    LEAVE_AT_CLOSING = 11,
    SIT_FROM_QUEUE = 12,
    ERROR = 13
};

class Event {
protected:
    EventID ID_;
    unsigned int Time_;
    std::string Username_;
    unsigned int TableID_;

public:
    Event() = default;

    Event(const EventID id, const unsigned int time, std::string username, const unsigned int table_id)
        : ID_(id)
          , Time_(time)
          , Username_(std::move(username))
          , TableID_(table_id){
    }

    Event(const Event& other)
        : ID_(other.ID_)
          , Time_(other.Time_)
          , Username_(other.Username_)
          , TableID_(other.TableID_) {
    }

    std::string ToString() const {
        std::ostringstream result;

        result << TimeUtils::TimeToString(Time_) << ' '
               << static_cast<int>(ID_) << ' '
               << Username_;
        if (TableID_ != 0) {
            result << ' ' << TableID_;
        }

        return result.str();
    }

    EventID GetID() const {
        return ID_;
    }

    void SetID(const EventID id) {
        ID_ = id;
    }

    unsigned int GetTime() const {
        return Time_;
    }

    void SetTime(const unsigned int time) {
        Time_ = time;
    }

    std::string GetUsername() const {
        return Username_;
    }

    void SetUsername(const std::string &username) {
        Username_ = username;
    }

    void SetTableID(const unsigned int table_id) {
        TableID_ = table_id;
    }

    unsigned int GetTableID() const {
        return TableID_;
    }
};
