cmake_minimum_required(VERSION 3.2)
project(ear VERSION 0.0.0 DESCRIPTION "ear library")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

set(SRC
 core/task.cpp
 core/periodic_task.cpp
 core/aperiodic_task.cpp
 core/scheduler.cpp
 msg/messenger.cpp
 msg/publisher.cpp
 msg/subscriber.cpp 
 io/io_device.cpp
)

include_directories(../ext/spdlog/include ../ext/nng/include core ioss)
link_directories(../ext/spdlog/build ../ext/nng/build)
link_libraries(spdlog nng)

add_library(${PROJECT_NAME} SHARED ${SRC})
set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
