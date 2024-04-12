cmake_minimum_required(VERSION 3.2)
project(pipeline-test)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

set(SRC serial_device.cpp gps.cpp dcu.cpp main.cpp)

link_directories(../../src/build/ ../../ext/spdlog/build ../../ext/nng/build)
include_directories(../../src/util ../../src/core ../../src/io ../../src/msg ../../ext/spdlog/include ../../ext/nng/include)

link_libraries(ear spdlog nng)
add_executable(${PROJECT_NAME} ${SRC})
