cmake_minimum_required(VERSION 3.16)
project(SortedMultiMapSLLA)

set(CMAKE_CXX_STANDARD 14)

add_executable(SortedMultiMapSLLA App.cpp SortedMultiMap.cpp SortedMultiMap.h SMMIterator.cpp SMMIterator.h ShortTest.cpp ShortTest.h ExtendedTest.cpp ExtendedTest.h)