#pragma once

//Сущность стола. Предоставляет функционал подсчета итоговой выручки, а так же считает время, проведенное клиентами за ним
class Table {
private:
  const unsigned int ID_;
  unsigned int Price_;
  bool IsBusy_;
  unsigned int SessionStartTime_;
  unsigned int TotalBusyTime_;

public:
  Table() = delete;

  Table(unsigned int id, unsigned int price);

  unsigned int GetID() const;

  void SetPrice(unsigned int price);

  unsigned int GetPrice() const;

  void SetIsBusy(bool is_busy);

  bool GetIsBusy() const;

  unsigned int GetSessionStartTime() const;

  unsigned int GetTotalBusyTime() const;

  //Задает нового владельца стола
  void SetNewOwnership(unsigned int time);

  //Освобождает стол, делая его доступным для клиентов. Просчитывает время, занятое клиентом
  void DispatchOwnership(unsigned int time);

  //Выводит данные о выручке за день
  void PrintTotalRevenueByDay();
};
