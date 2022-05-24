cmake_minimum_required(VERSION 3.22)
project(packy)

set(CMAKE_CXX_STANDARD 20)

set(SOURCES include/Entry.hpp include/EntryType.hpp include/Bundle.hpp src/Bundle.cpp)

add_library(packy_static STATIC ${SOURCES})
target_include_directories(packy_static PRIVATE "./include")
set_target_properties(packy_static PROPERTIES OUTPUT_NAME "packy")

add_library(packy_shared SHARED ${SOURCES})
target_include_directories(packy_shared PRIVATE "./include")
set_target_properties(packy_shared PROPERTIES OUTPUT_NAME "packy")