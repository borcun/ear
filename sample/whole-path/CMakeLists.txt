cmake_minimum_required(VERSION 3.2)
project(face-pipeline-test)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SRC serial_service.cpp gps.cpp positioning.cpp main.cpp)

link_directories(../../src/build/ ../../ext/spdlog/build)
include_directories(../../src/core ../../src/ioss ../../src/psss ../../src/tss ../../src/pcss ../../ext/spdlog/include)

link_libraries(face spdlog)
add_executable(${PROJECT_NAME} ${SRC})
