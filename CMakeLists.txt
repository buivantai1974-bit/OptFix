cmake_minimum_required(VERSION 3.21)
project(OptFix)

add_library(${PROJECT_NAME} SHARED src/main.cpp)
target_link_libraries(${PROJECT_NAME} Geode::Geode)
