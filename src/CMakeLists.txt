cmake_minimum_required(VERSION 3.2)
project(face VERSION 0.0.0 DESCRIPTION "face reference library")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

set(SRC
 core/service.cpp
 core/task.cpp
 core/periodic_service.cpp
 core/aperiodic_service.cpp
 core/scheduler.cpp
 core/node.cpp
 ioss/ios.cpp
)

include_directories(../ext/spdlog/include ../ext/nng/include core ioss)
link_directories(../ext/spdlog/build ../ext/nng/build)
link_libraries(spdlog nng)

add_library(${PROJECT_NAME} SHARED ${SRC})
set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
