#pragma once

#include <deque>
#include <stdexcept>

namespace SMA {

    template<typename T>
    class SimpleMovingAverage {
    public: // PUBLIC METHODS AND CTOR //

        explicit SimpleMovingAverage(int window_size);

        void AddNumber(T number);

        [[nodiscard]] double CalcMean() const;


    private: // PRIVATE DATA //

        std::deque<T> data_;
        int window_size_;
        T sum_;

    };

    // DEFINITIONS //

    template<typename T>
    double SimpleMovingAverage<T>::CalcMean() const {
        return (sum_ / static_cast<T>(window_size_));
    }

    template<typename T>
    void SimpleMovingAverage<T>::AddNumber(T number) {
        sum_ += number;
        data_.push_back(number);
        if (data_.size() > window_size_) {
            sum_ -= data_.front();
            data_.pop_back();
        }
    }

    template<typename T>
    SimpleMovingAverage<T>::SimpleMovingAverage(int window_size) {
        {
            if (window_size <= 0) {
                throw std::invalid_argument("Window size <= 0");
            } else {
                window_size_ = window_size;
            }
        }
    }
} //namespace SMA

