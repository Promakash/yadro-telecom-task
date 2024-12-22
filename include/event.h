#pragma once

#include <string>

//Перечисление всех ID событий, которые могут быть
enum class EventID {
    COME = 1,
    SIT = 2,
    WAIT = 3,
    LEAVE = 4,
    LEAVE_AT_CLOSING = 11,
    SIT_FROM_QUEUE = 12,
    ERROR = 13
};

// Сущность событие, хранит в себе информацию об исходящих событиях
class Event {
protected:
    EventID ID_;
    unsigned int Time_;
    std::string Username_;
    unsigned int TableID_;

public:
    Event();

    Event(EventID id, unsigned int time, std::string username, unsigned int table_id);

    Event(const Event &other);

    std::string ToString() const;

    EventID GetID() const;

    void SetID(EventID id);

    unsigned int GetTime() const;

    void SetTime(unsigned int time);

    std::string GetUsername() const;

    void SetUsername(const std::string &username);

    void SetTableID(unsigned int table_id);

    unsigned int GetTableID() const;
};
