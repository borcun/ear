cmake_minimum_required(VERSION 3.2)
project(pipeline-test)

include(src/pipeline.cmake)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wpedantic -std=c++11")

include_directories(
  ../../src/sched
  ../../src/iodev
  ../../src/comm
  ../../ext/spdlog/include
)

link_directories(
  ../../build/
  ../../build/ext/spdlog/build
)

link_libraries(spdlog ear)
add_executable(${PROJECT_NAME} ${PIPELINE_SRC})
