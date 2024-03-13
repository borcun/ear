cmake_minimum_required(VERSION 3.2)
project(tss-test)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SRC main.cpp)

link_directories(../../src/build/ ../../ext/nng/build ../../ext/spdlog/build)
include_directories(../../ext/nng/include ../../ext/spdlog/include ../../src/core ../../src/ioss ../../src/psss ../../src/tss ../../src/pcss)

link_libraries(face spdlog nng)
add_executable(${PROJECT_NAME} ${SRC})
