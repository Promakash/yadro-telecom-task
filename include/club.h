#pragma once

#include <queue>
#include <unordered_map>
#include <vector>

#include "client.h"
#include "event.h"
#include "event_handler.h"
#include "event_response.h"
#include "table.h"

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

 void SetupClubParameters();

 EventResponse AddClient(const Event &event);

 std::vector<EventResponse> SitClient(const Event &event);

 EventResponse PutClientInQueue(const Event &event);

 std::vector<EventResponse> RemoveClient(const Event &event);

 std::pair<bool, Event> GetClientFromQueue(const Event &event);

 std::vector<EventResponse> RemoveClientsAfterClosing();

 void CloseDay();

public:
 Club() = delete;

 explicit Club(const std::string &file_path);

 void StartServing();
};
