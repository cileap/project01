cmake_minimum_required(VERSION 3.16)
project(LibraryMap LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/bin)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(LibraryMap WIN32 main.cpp widget.h widget.cpp widget.ui)

target_link_libraries(LibraryMap PRIVATE Qt6::Widgets)