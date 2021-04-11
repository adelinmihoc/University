cmake_minimum_required(VERSION 3.16)
project(PriorityQueue)

set(CMAKE_CXX_STANDARD 17)

add_executable(PriorityQueue App.cpp ExtendedTest.h ExtendedTest.cpp ShortTest.h ShortTest.cpp PriorityQueue.cpp PriorityQueue.h)