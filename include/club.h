#pragma once

#include "client.h"
#include "string"
#include "table.h"
#include "event_handler.h"
#include "event_response.h"
#include "time_utils.h"

#include <queue>
#include <unordered_map>

class Club {
private:
 std::unordered_map<unsigned int, Client> ClientsByID_;
 std::unordered_map<std::string, unsigned int> ClientsIDsByName_;
 std::unordered_map<unsigned int, unsigned int> Clients_Tables_;

 std::queue<unsigned int> ClientsQueueByID_;
 std::vector<Table> TablesVec_;

 EventHandler Handler_;

 unsigned int StartTime_;
 unsigned int EndTime_;

 unsigned int MaxTables_;
 unsigned int FreeTables_;

 unsigned int CurrentID_ = 1;

 void SetupClubParameters() {
  std::vector<unsigned int> parameters = Handler_.ReadClubParameters();
  MaxTables_ = parameters[0];
  FreeTables_ = MaxTables_;

  StartTime_ = parameters[1];
  EndTime_ = parameters[2];

  for (int i = MaxTables_; i >= 0; i--) {
   TablesVec_.emplace_back(MaxTables_ - i + 1, parameters[3]);
  }
 }

 EventResponse AddClient(const Event &event) {
  if (ClientsIDsByName_.count(event.GetUsername())) {
   return {event, EventResponseErrorCodes::ALREADY_AT_CLUB, EventID::ERROR};
  }

  if (event.GetTime() < StartTime_ || event.GetTime() >= EndTime_) {
   return {event, EventResponseErrorCodes::NOT_WORKING_HOURS, EventID::ERROR};
  }

  Client new_client(event.GetUsername());
  ClientsIDsByName_[new_client.GetName()] = CurrentID_;
  ClientsByID_[CurrentID_] = new_client;
  CurrentID_++;

  return {event, EventResponseErrorCodes::NOTHING, event.GetID()};
 }

 std::vector<EventResponse> SitClient(const Event &event) {
  std::vector<EventResponse> responses;

  auto client_id_ptr = ClientsIDsByName_.find(event.GetUsername());

  if (client_id_ptr == ClientsIDsByName_.end()) {
   responses.emplace_back(event, EventResponseErrorCodes::CLIENT_NOT_AT_CLUB, EventID::ERROR);
   return std::move(responses);
  }

  unsigned int client_id = client_id_ptr->second;
  unsigned int table_id = event.GetTableID();

  if (TablesVec_[table_id - 1].GetIsBusy()) {
   responses.emplace_back(event, EventResponseErrorCodes::TABLE_IS_OCCUPIED, EventID::ERROR);
   return std::move(responses);
  }

  auto table_id_ptr = Clients_Tables_.find(client_id);

  if (table_id_ptr != Clients_Tables_.end()) {
   const unsigned int current_table_id = table_id_ptr->second;
   TablesVec_[current_table_id - 1].DispatchOwnership(event.GetTime());
   Clients_Tables_.erase(client_id);
   responses.emplace_back(event, EventResponseErrorCodes::NOTHING, event.GetID());

   Event new_event(event);
   new_event.SetTableID(current_table_id);

   std::pair <bool, Event> operation_result = GetClientFromQueue(event);
   if (operation_result.first) {
    responses.emplace_back(operation_result.second, EventResponseErrorCodes::NOTHING, operation_result.second.GetID());
   }
  }
  else {
   responses.emplace_back(event, EventResponseErrorCodes::NOTHING, event.GetID());
  }

  TablesVec_[table_id - 1].SetNewOwnership(event.GetTime());
  Clients_Tables_[client_id] = table_id;

  ClientsByID_[client_id].SetStatus(ClientStatus::PLAYING);

  return std::move(responses);
 }

 EventResponse PutClientInQueue(const Event &event) {
  if (Clients_Tables_.size() < MaxTables_) {
   return {event, EventResponseErrorCodes::FREE_TABLES_EXIST, EventID::ERROR};
  }

  auto client_id_ptr = ClientsIDsByName_.find(event.GetUsername());
  if (client_id_ptr == ClientsIDsByName_.end()) {
   return {event, EventResponseErrorCodes::CLIENT_NOT_AT_CLUB, EventID::ERROR};
  }

  unsigned int client_id = client_id_ptr->second;

  if (ClientsQueueByID_.size() >= MaxTables_) {
   ClientsIDsByName_.erase(event.GetUsername());
   ClientsIDsByName_.erase(client_id_ptr);
   return {event, EventResponseErrorCodes::NOTHING, EventID::LEAVE_AT_CLOSING};
  }

  ClientsQueueByID_.push(client_id);
  return {event, EventResponseErrorCodes::NOTHING, event.GetID()};
 }

 std::vector<EventResponse> RemoveClient(const Event &event) {
  std::vector<EventResponse> responses;
  auto client_id_ptr = ClientsIDsByName_.find(event.GetUsername());
  if (client_id_ptr == ClientsIDsByName_.end()) {
   responses.emplace_back(event, EventResponseErrorCodes::CLIENT_NOT_AT_CLUB, EventID::ERROR);
   return std::move(responses);
  }

  unsigned int client_id = client_id_ptr->second;

  auto table_id_ptr = Clients_Tables_.find(client_id);

  if (table_id_ptr != Clients_Tables_.end()) {
   const unsigned int current_table_id = table_id_ptr->second;
   TablesVec_[current_table_id - 1].DispatchOwnership(event.GetTime());
   Clients_Tables_.erase(client_id);
   ClientsIDsByName_.erase(event.GetUsername());
   ClientsByID_.erase(client_id);
   responses.emplace_back(event, EventResponseErrorCodes::NOTHING, event.GetID());

   Event new_event(event);
   new_event.SetTableID(current_table_id);

   std::pair <bool, Event> operation_result = GetClientFromQueue(new_event);
   if (operation_result.first) {
    responses.emplace_back(operation_result.second, EventResponseErrorCodes::NOTHING, operation_result.second.GetID());
   }
  }
  else {
   ClientsIDsByName_.erase(event.GetUsername());
   ClientsByID_.erase(client_id);
   responses.emplace_back(event, EventResponseErrorCodes::NOTHING, event.GetID());
  }

  return std::move(responses);
 }

 std::pair<bool, Event> GetClientFromQueue(const Event &event) {
  if (ClientsQueueByID_.empty()) {
   return {false, event};
  }

  unsigned int table_id = event.GetTableID();
  unsigned int user_id = ClientsQueueByID_.front();
  ClientsQueueByID_.pop();

  auto client_ptr = ClientsByID_.find(user_id);
  std::string username = client_ptr->second.GetName();

  client_ptr->second.SetStatus(ClientStatus::PLAYING);
  TablesVec_[table_id-1].SetNewOwnership(event.GetTime());
  Clients_Tables_[user_id] = table_id;

  Event response_event {EventID::SIT_FROM_QUEUE, event.GetTime(), std::move(username), table_id};
  return {true, std::move(response_event)};
 }

 std::vector<EventResponse> RemoveClientsAfterClosing() {
  std::vector<EventResponse> responses;
  for (auto &it : ClientsIDsByName_) {
   std::string name = it.first;
   Event event{EventID::LEAVE_AT_CLOSING, EndTime_, std::move(name), 0};
   responses.emplace_back(event, EventResponseErrorCodes::NOTHING, EventID::LEAVE_AT_CLOSING);
  }
  return std::move(responses);
 }

 void CloseDay() {
  std::vector <EventResponse> last_clients = RemoveClientsAfterClosing();
  for (auto &resp : last_clients) {
   Handler_.HandleResult(resp);
  }

  std::cout << TimeUtils::TimeToString(EndTime_) << std::endl;

  for (auto &table : TablesVec_) {
   if (table.GetIsBusy()) {
    table.DispatchOwnership(EndTime_);
   }
   table.PrintTotalRevenueByDay();
  }
 }

public:
 Club() = delete;

 Club(const std::string &file_path) : Handler_(file_path) {
 }

 void StartServing() {
  if (!Handler_.CheckFile()) {
   return;
  }

  SetupClubParameters();

  std::cout << TimeUtils::TimeToString(StartTime_) << std::endl;

  while (true) {
   std::pair<bool, Event> parse_result = Handler_.ReadEventFromFile();
   if (!parse_result.first) {
    break;
   }

   Event event = parse_result.second;
   std::vector<EventResponse> responses;

   switch (event.GetID()) {
    case EventID::COME:{
     responses.push_back(AddClient(event));
     break;
    }
    case EventID::SIT: {
     responses = std::move(SitClient(event));
     break;
    }
    case EventID::WAIT: {
     responses.push_back(PutClientInQueue(event));
     break;
    }
    case EventID::LEAVE: {
     responses = std::move(RemoveClient(event));
     break;
    }
    default: {
     throw std::runtime_error("Unknown event type");
    }
   }
   for (auto &resp : responses) {
    Handler_.HandleResult(resp);
   }
  }

  CloseDay();

 }
};
