cmake_minimum_required(VERSION 3.2)
project(ear VERSION 0.0.0 DESCRIPTION "ear library")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(SRC
  src/core/task.cpp
  src/core/periodic_task.cpp
  src/core/aperiodic_task.cpp
  src/core/scheduler.cpp
  src/msg/messenger.cpp
  src/msg/publisher.cpp
  src/msg/subscriber.cpp 
  src/io/io_device.cpp
)

add_subdirectory(ext/spdlog ext/spdlog/build)
add_subdirectory(ext/nng ext/nng/build)

include_directories(ext/spdlog/include ext/nng/include src/util src/core src/io src/msg)
link_directories(ext/spdlog/build ext/nng/build)
link_libraries(spdlog nng)

add_library(${PROJECT_NAME} SHARED ${SRC})
set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
