#pragma once

#include <unordered_map>

#include "event.h"
#include "time_utils.h"

enum class EventResponseErrorCodes {
    ALREADY_AT_CLUB = 1,
    NOT_WORKING_HOURS = 2,
    TABLE_IS_OCCUPIED = 3,
    CLIENT_NOT_AT_CLUB = 4,
    FREE_TABLES_EXIST = 5,
    NOTHING = 6
  };

class EventResponse{
private:
    Event event_;
    EventResponseErrorCodes Description_;
    EventID ResultCode_;

    std::string EventResponseCodeToString(EventResponseErrorCodes resp_code) const {
        static const std::unordered_map<EventResponseErrorCodes, std::string> description_map = {
            {EventResponseErrorCodes::ALREADY_AT_CLUB, "YouShallNotPass"},
        {EventResponseErrorCodes::NOT_WORKING_HOURS, "NotOpenYet"},
        {EventResponseErrorCodes::TABLE_IS_OCCUPIED, "PlaceIsBusy"},
        {EventResponseErrorCodes::CLIENT_NOT_AT_CLUB, "ClientUnknown"},
        {EventResponseErrorCodes::FREE_TABLES_EXIST, "ICanWaitNoLonger!"},
        {EventResponseErrorCodes::NOTHING, ""}
        };

        return description_map.find(resp_code)->second;
    }

public:
    EventResponse() = default;

    EventResponse(const Event& event, const EventResponseErrorCodes description, const EventID result_code) : event_(event), Description_(description), ResultCode_(result_code) {};

    std::string ToString() const {
        std::string event_str = event_.ToString();

        if (ResultCode_ == EventID::ERROR) {
            std::ostringstream result;
            result << TimeUtils::TimeToString(event_.GetTime()) << ' '
                   << static_cast<unsigned int>(ResultCode_) << ' '
                   << event_.GetUsername();

            if (event_.GetTableID() != 0) {
                result << ' ' << event_.GetTableID();
            }

            if (Description_ != EventResponseErrorCodes::NOTHING) {
                result << ' ' << EventResponseCodeToString(Description_);
            }

            return event_str + '\n' + result.str();
        }

        return event_str;
    }

};