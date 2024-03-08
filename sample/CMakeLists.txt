cmake_minimum_required(VERSION 3.2)
project(face-test)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SRC eth_service.cpp file_service.cpp serial_service.cpp gpio_service.cpp gps.cpp logger.cpp imu.cpp switch.cpp main.cpp)

link_directories(../src/build/)
include_directories(../src/core ../src/ioss ../src/psss ../src/tss ../src/pcss)

link_libraries(face)
add_executable(${PROJECT_NAME} ${SRC})
