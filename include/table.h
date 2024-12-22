#pragma once

#include <iostream>
#include "time_utils.h"

class Table {
private:
  const unsigned int ID_;
  unsigned int Price_;
  bool IsBusy_;
  unsigned int SessionStartTime_;
  unsigned int TotalBusyTime_;

public:
  Table() = delete;

  Table(const unsigned int id, const unsigned int price)
    : ID_(id)
      , Price_(price)
      , IsBusy_(false)
      , SessionStartTime_(0)
      , TotalBusyTime_(0) {
  }

  unsigned int GetID() const {
    return ID_;
  }

  void SetPrice(const unsigned int price) {
    Price_ = price;
  }

  unsigned int GetPrice() const {
    return Price_;
  }

  void SetIsBusy(const bool is_busy) {
    IsBusy_ = is_busy;
  }

  bool GetIsBusy() const {
    return IsBusy_;
  }

  unsigned int GetSessionStartTime() const {
    return SessionStartTime_;
  }

  unsigned int GetTotalBusyTime() const {
    return TotalBusyTime_;
  }

  void SetNewOwnership(const unsigned int time) {
    SessionStartTime_ = time;
    IsBusy_ = true;
  }

  void DispatchOwnership(const unsigned int time) {
    IsBusy_ = false;
    TotalBusyTime_ += time - SessionStartTime_;
  }

  void PrintTotalRevenueByDay() {
    if (SessionStartTime_ == 0) {
      return;
    }

    unsigned int total_work_time = TotalBusyTime_ / 60;
    if (TotalBusyTime_ % 60 != 0) {
      total_work_time++;
    }
    unsigned int total_revenue = total_work_time * Price_;

    std::cout << ID_ << ' ' << total_revenue <<  ' ' << TimeUtils::TimeToString(TotalBusyTime_) << std::endl;
  }
};
