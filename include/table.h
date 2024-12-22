#pragma once

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

  void SetNewOwnership(unsigned int time);

  void DispatchOwnership(unsigned int time);

  void PrintTotalRevenueByDay();
};
