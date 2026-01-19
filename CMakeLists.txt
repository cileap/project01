cmake_minimum_required(VERSION 3.16)
project(LibraryMap LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/bin)

# 添加需要的 Qt 模块
find_package(Qt6 REQUIRED COMPONENTS
    Widgets
    Network
    Sql
)

# 收集所有源文件
file(GLOB_RECURSE SOURCES
    "*.cpp"
    "*.h"
    "*.ui"
)

add_executable(LibraryMap WIN32 ${SOURCES})

target_link_libraries(LibraryMap PRIVATE
    Qt6::Widgets
    Qt6::Network
    Qt6::Sql
)