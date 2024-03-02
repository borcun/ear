cmake_minimum_required(VERSION 3.2)
project(face-test)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SRC eth_service.cpp main.cpp)

link_directories(../face/build/)
include_directories(../face/core ../face/ioss ../face/psss ../face/tss ../face/pcss)

link_libraries(face)
add_executable(${PROJECT_NAME} ${SRC})
