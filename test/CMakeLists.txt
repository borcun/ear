cmake_minimum_required(VERSION 3.2)
project(face_test)

include_directories(../third_party/googletest/googletest/include ../face/core ../face/ioss)
link_directories(../third_party/googletest/build/lib ../face/build)

link_libraries(gtest face)
add_executable(${PROJECT_NAME} face_test.cpp)
