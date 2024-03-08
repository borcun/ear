cmake_minimum_required(VERSION 3.2)
project(face VERSION 0.0.0 DESCRIPTION "face reference library")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SRC core/service.cpp
 ioss/ios.cpp
 psss/ps.cpp
 psss/ps_sched.cpp
 tss/ts.cpp
 pcss/pcs.cpp
)

include_directories(core ioss psss tss pcss)
add_library(${PROJECT_NAME} SHARED ${SRC})
set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
