cmake_minimum_required (VERSION 2.8.9)
project(OptParser)

set(SOURCES "OptParser.cpp")

add_library(Kanedo_OptParser ${SOURCES})

add_executable(Kanedo_OptParser_Example "example.cpp")
target_link_libraries(Kanedo_OptParser_Example Kanedo_OptParser)