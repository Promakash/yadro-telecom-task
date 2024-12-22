#include "table.h"
#include <iostream>
#include "time_utils.h"

Table::Table(const unsigned int id, const unsigned int price)
    : ID_(id), Price_(price), IsBusy_(false), SessionStartTime_(0), TotalBusyTime_(0) {
}

unsigned int Table::GetID() const {
    return ID_;
}

void Table::SetPrice(const unsigned int price) {
    Price_ = price;
}

unsigned int Table::GetPrice() const {
    return Price_;
}

void Table::SetIsBusy(const bool is_busy) {
    IsBusy_ = is_busy;
}

bool Table::GetIsBusy() const {
    return IsBusy_;
}

unsigned int Table::GetSessionStartTime() const {
    return SessionStartTime_;
}

unsigned int Table::GetTotalBusyTime() const {
    return TotalBusyTime_;
}

void Table::SetNewOwnership(const unsigned int time) {
    SessionStartTime_ = time;
    IsBusy_ = true;
}

void Table::DispatchOwnership(const unsigned int time) {
    IsBusy_ = false;
    TotalBusyTime_ += time - SessionStartTime_;
}

void Table::PrintTotalRevenueByDay() {
    if (SessionStartTime_ == 0) {
        return;
    }

    unsigned int total_work_time = TotalBusyTime_ / 60;
    if (TotalBusyTime_ % 60 != 0) {
        total_work_time++;
    }
    unsigned int total_revenue = total_work_time * Price_;

    std::cout << ID_ << ' ' << total_revenue << ' ' << TimeUtils::TimeToString(TotalBusyTime_) << std::endl;
}
