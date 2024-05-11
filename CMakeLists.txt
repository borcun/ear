cmake_minimum_required(VERSION 3.2)
project(ear VERSION 0.0.0 DESCRIPTION "embeded architecture reference (EAR) library")

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")
set(SPDLOG_DIR ext/spdlog)
set(INC_DIRS src/sched src/io src/comm)

include(src/sched/sched.cmake)
include(src/comm/comm.cmake)
include(src/io/io.cmake)

add_subdirectory(${SPDLOG_DIR}/ ${SPDLOG_DIR}/build)
include_directories(${SPDLOG_DIR}/include ${INC_DIRS})
link_directories(${SPDLOG_DIR}/build)
link_libraries(spdlog)

option(BUILD_EXAMPLES "Build ear examples" ON)

if (BUILD_EXAMPLES)
  add_subdirectory(example/pipeline)
  add_subdirectory(example/network)
endif (BUILD_EXAMPLES)
    
add_library(${PROJECT_NAME} SHARED ${IO_SRC} ${SCHED_SRC} ${COMM_SRC})
set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
