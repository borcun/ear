cmake_minimum_required(VERSION 3.2)
project(network-test)

include(src/network.cmake)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(
  ../../src/sched
  ../../src/io
  ../../src/comm
  ../../ext/spdlog/include
)

link_directories(
  ../../build/
  ../../build/ext/spdlog/build
)

link_libraries(spdlog ear)
add_executable(${PROJECT_NAME} ${NETWORK_SRC})
