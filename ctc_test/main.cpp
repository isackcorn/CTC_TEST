#include "log_duration.h"
#include "SimpleMovingAverageTimeLog.h"
#include <iostream>


int main() {
    SMA::TestSimpleMovingAverage<double> test;
    auto countMs = test.CountMs(100, 128, 1'000'000, 0.0, 100.0, RUNMODE::SIMPLE);
    std::cout << "Average time: " << *countMs << " microseconds.";
}
