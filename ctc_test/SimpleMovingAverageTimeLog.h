#pragma once

#include <random>
#include "SimpleMovingAverage.h"
#include "log_duration.h"

namespace SMA {
    template<typename T>
    class TestSimpleMovingAverage {
    public:
        /*
         * Функция принимает на вход количество экспериментов
         * для тестирования, длину окна усреднения, длину входных данных для обработки (res_vec_size),
         * интервал возможных значений
         * */
        ::int64_t *
        CountMs(int samples, int window_size, int res_vec_size, int min_to_distribution, int max_to_distribution,
                RUNMODE runMode = SIMPLE);

    };

    template<typename T>
    ::int64_t *
    TestSimpleMovingAverage<T>::CountMs(int samples, int window_size, int res_vec_size, int min_to_distribution,
                                        int max_to_distribution, RUNMODE runMode) {
        {

            std::mt19937 rng(std::random_device{}());
            std::uniform_real_distribution<T> distribution(0.0, 30.0);
            auto *micros = new int64_t(0); // ALL SUM

            for (int j = 0; j < samples; ++j) {
                {
                    SMA::SimpleMovingAverage<T> average(window_size);
                    std::vector<T> result(res_vec_size);

                    LogDuration duration("Time spent", micros, runMode);

                    for (int i = 0; i < res_vec_size; ++i) {
                        double x = distribution(rng);
                        average.AddNumber(x);
                        result[i] = average.CalcMean();
                    }
                }
            }

            *micros /= static_cast<T>(samples);
            return micros;
        }
    }
} //namespace SMA