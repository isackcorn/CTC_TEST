cmake_minimum_required(VERSION 3.26)
project(CTC_TEST)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=undefined")

add_executable(sources main.cpp
        log_duration.h
        SimpleMovingAverage.h
        SimpleMovingAverageTimeLog.h)
