cmake_minimum_required(VERSION 3.6)
project(studyCppMailRuCource)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES task_1_2.cpp task_1_1.cpp main.cpp)
add_executable(studyCppMailRuCource ${SOURCE_FILES} main.cpp)