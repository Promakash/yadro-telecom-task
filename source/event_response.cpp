#include "event_response.h"
#include "time_utils.h"
#include <sstream>
#include <unordered_map>

EventResponse::EventResponse() = default;

EventResponse::EventResponse(const Event& event, const EventResponseErrorCodes description, const EventID result_code)
    : Event_(event), Description_(description), ResultCode_(result_code) {}

std::string EventResponse::EventResponseCodeToString(EventResponseErrorCodes resp_code) const {
    static const std::unordered_map<EventResponseErrorCodes, std::string> description_map = {
        {EventResponseErrorCodes::ALREADY_AT_CLUB, "YouShallNotPass"},
        {EventResponseErrorCodes::NOT_WORKING_HOURS, "NotOpenYet"},
        {EventResponseErrorCodes::TABLE_IS_OCCUPIED, "PlaceIsBusy"},
        {EventResponseErrorCodes::CLIENT_NOT_AT_CLUB, "ClientUnknown"},
        {EventResponseErrorCodes::FREE_TABLES_EXIST, "ICanWaitNoLonger!"},
        {EventResponseErrorCodes::NOTHING, ""}
    };

    auto it = description_map.find(resp_code);
    return it != description_map.end() ? it->second : "";
}

std::string EventResponse::ToString() const {
    std::string event_str = Event_.ToString();

    if (ResultCode_ == EventID::ERROR) {
        std::ostringstream result;
        result << TimeUtils::TimeToString(Event_.GetTime()) << ' '
               << static_cast<unsigned int>(ResultCode_);

        if (Description_ != EventResponseErrorCodes::NOTHING) {
            result << ' ' << EventResponseCodeToString(Description_);
        }

        return event_str + '\n' + result.str();
    }

    return event_str;
}