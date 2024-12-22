#pragma once

#include <queue>
#include <unordered_map>
#include <vector>

#include "client.h"
#include "event.h"
#include "event_handler.h"
#include "event_response.h"
#include "table.h"

// Сущность клуб, реализующий логику управления клиентами
class Club {
private:
    //Вспомогательные контейнеры для эффективного поиска и удаления
    //Предоставляет связь типа ClientID - Client
    std::unordered_map<unsigned int, Client> ClientsByID_;
    //Предоставляет связь типа ClientName - ClientID
    std::unordered_map<std::string, unsigned int> ClientsIDsByName_;
    //Предоставляет связь типа ClientID - TableID (Vector index)
    std::unordered_map<unsigned int, unsigned int> Clients_Tables_;
    //Хранит ID клиентов вместо сущностей
    std::queue<unsigned int> ClientsQueueByID_;
    std::vector<Table> TablesVec_;

    EventHandler Handler_;

    // Время хранится в минутах
    unsigned int StartTime_;
    unsigned int EndTime_;
    unsigned int MaxTables_;
    unsigned int FreeTables_;
    unsigned int CurrentID_ = 1;

    void SetupClubParameters();

    //Функция обработки события с EventID = 1
    EventResponse AddClient(const Event &event);

    //Функция обработки события с EventID = 2
    std::vector<EventResponse> SitClient(const Event &event);

    //Функция обработки события с EventID = 3
    EventResponse PutClientInQueue(const Event &event);

    //Функция обработки события с EventID = 4
    std::vector<EventResponse> RemoveClient(const Event &event);

    //Возвращает пару <признак наличия клиентов в очереди, событие>. В случае false результат игнорируется программой
    std::pair<bool, Event> GetClientFromQueue(const Event &event);

    //Вызывается при окончании событий, выводит событие с EventID = 11
    std::vector<EventResponse> RemoveClientsAfterClosing();

    void CloseDay();

    //Функция очистки связей клиента с заданным столом
    void ReleaseTable(unsigned int client_id, unsigned int current_table_id, const Event &event,
                      std::vector<EventResponse> &responses);

    //Функция удаления клиента из контейнеров связей
    void RemoveClientFromClub(const std::string &username, unsigned int client_id);

public:
    Club() = delete;

    explicit Club(const std::string &file_path);

    void StartServing();
};
