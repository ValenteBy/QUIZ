cmake_minimum_required(VERSION 3.22.1)

project(QuizLockoutLocal LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


add_executable(main src/main.cpp src/ConfigSem.cpp src/classes/Client.cpp src/classes/Serve.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
