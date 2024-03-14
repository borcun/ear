cmake_minimum_required(VERSION 3.2)
project(face VERSION 0.0.0 DESCRIPTION "face reference library")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

set(SRC
 core/service.cpp
 core/task.cpp
 core/scheduler.cpp
 ioss/ios.cpp
 psss/ps.cpp
 tss/gateway.cpp	
 tss/edge_service.cpp
 pcss/pcs.cpp
)

include_directories(../ext/spdlog/include ../ext/nng/include core ioss psss tss pcss)
link_directories(../ext/spdlog/build ../ext/nng/build)
link_libraries(spdlog nng)

add_library(${PROJECT_NAME} SHARED ${SRC})
set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
