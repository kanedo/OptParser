cmake_minimum_required (VERSION 3.1.3)
project(OptParser)

set(SOURCES "OptParser.cpp")

add_library(Kanedo_OptParser ${SOURCES})
set_property(TARGET Kanedo_OptParser PROPERTY CXX_STANDARD 11)
set(CXX_STANDARD_REQUIRED ON)
add_executable(Kanedo_OptParser_Example "example.cpp")
target_link_libraries(Kanedo_OptParser_Example Kanedo_OptParser)