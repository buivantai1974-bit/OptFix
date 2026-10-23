include(${CMAKE_CURRENT_SOURCE_DIR}/../cmake/Geode.cmake)
cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 20)

project(OptFix)

add_library(${PROJECT_NAME} SHARED src/main.cpp)

target_link_libraries(${PROJECT_NAME} Geode::Geode)

setup_geode_mod(${PROJECT_NAME})
