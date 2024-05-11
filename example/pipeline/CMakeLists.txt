cmake_minimum_required(VERSION 3.2)
project(pipeline-test)

include(src/pipeline.cmake)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

link_directories(
  ../../build/
  ../../build/ext/spdlog/build
)

include_directories(
  ../../src/sched
  ../../src/io
  ../../src/comm
  ../../ext/spdlog/include
)

link_libraries(ear spdlog)
add_executable(${PROJECT_NAME} ${PIPELINE_SRC})
