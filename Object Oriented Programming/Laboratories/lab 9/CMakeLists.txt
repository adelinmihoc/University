cmake_minimum_required(VERSION 3.15)
project(FirstTry)

set(CMAKE_CXX_STANDARD 20)

add_executable(FirstTry main.cpp UserInterface.cpp UserInterface.h Controller.cpp Controller.h Domain.cpp Domain.h DynamicArray.h Iterator.cpp Iterator.h Repository.cpp Repository.h Tests.cpp Tests.h UserFile.cpp UserFile.h Exceptions.h Validators.h AdminFile.cpp AdminFile.h)