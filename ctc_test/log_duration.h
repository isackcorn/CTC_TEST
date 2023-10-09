#pragma once

#include <chrono>
#include <iostream>
#include <string_view>

enum RUNMODE {
    SIMPLE,
    DETAILED
};

/*
 * Идея класса в создании временной метки начала жизни объекта в конструкторе
 * и возвращение/вывод разности между этой меткой и текущим временем в деструкторе.
 * Для подсчёта суммарного времени (при наборе испытаний) время суммируется в специальной переменной,
 * полученной по указателю.
 */

class LogDuration {
public:

    using Clock = std::chrono::steady_clock;

    LogDuration(std::string_view id, ::int64_t *millis, RUNMODE runMode = SIMPLE, std::ostream &dst_stream = std::cerr)
            : id_(id), dst_stream_(dst_stream),
              us_sum_ptr(millis), runMode_(runMode) {
    }

    ~LogDuration() {
        using namespace std::chrono;
        using namespace std::literals;

        const auto end_time = Clock::now();
        const auto dur = end_time - start_time_;
        if (runMode_ == DETAILED) {
            (dst_stream_ << id_ << ": "sv << duration_cast<microseconds>(dur).count() << " us"sv
                         << std::endl); // Вывод в микросекундах
        }
        *us_sum_ptr += static_cast<int>(duration_cast<microseconds>(dur).count());
    }

private:
    const std::string id_;
    const Clock::time_point start_time_ = Clock::now();
    std::ostream &dst_stream_;
    ::int64_t *us_sum_ptr;
    RUNMODE runMode_;
};