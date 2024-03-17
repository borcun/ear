cmake_minimum_required(VERSION 3.2)
project(face-task-test)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(SRC main.cpp)

link_directories(../../src/build/ ../../ext/spdlog/build ../../ext/nng/build)
include_directories(../../src/core ../../src/ioss ../../src/psss ../../src/tss ../../src/pcss ../../ext/spdlog/include ../../ext/nng/include)

link_libraries(face spdlog nng)
add_executable(${PROJECT_NAME} ${SRC})
