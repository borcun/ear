cmake_minimum_required(VERSION 3.2)
project(ear VERSION 0.0.0 DESCRIPTION "ear library")

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SRC
  src/sched/itask.cpp
  src/sched/task.cpp
  src/sched/scheduler.cpp
  src/comm/endpoint.cpp
  src/comm/listener.cpp
  src/comm/transmitter.cpp
  src/comm/network_manager.cpp 
  src/io/device.cpp
)

add_subdirectory(ext/spdlog ext/spdlog/build)
include_directories(ext/spdlog/include src/sched src/io src/comm)
link_directories(ext/spdlog/build)
link_libraries(spdlog)

option(BUILD_SAMPLES "Build ear samples" ON)

if (BUILD_SAMPLES)
  add_subdirectory(sample/pipeline)
  add_subdirectory(sample/network)
endif (BUILD_SAMPLES)
    
add_library(${PROJECT_NAME} SHARED ${SRC})
set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
