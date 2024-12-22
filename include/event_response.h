#pragma once

#include "event.h"
#include <string>

enum class EventResponseErrorCodes {
    ALREADY_AT_CLUB = 1,
    NOT_WORKING_HOURS = 2,
    TABLE_IS_OCCUPIED = 3,
    CLIENT_NOT_AT_CLUB = 4,
    FREE_TABLES_EXIST = 5,
    NOTHING = 6
};

class EventResponse {
private:
    Event Event_;
    EventResponseErrorCodes Description_;
    EventID ResultCode_;

    std::string EventResponseCodeToString(EventResponseErrorCodes resp_code) const;

public:
    EventResponse();

    EventResponse(const Event &event, EventResponseErrorCodes description, EventID result_code);

    std::string ToString() const;
};
