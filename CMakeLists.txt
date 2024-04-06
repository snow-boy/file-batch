cmake_minimum_required(VERSION 3.10)

project(file_batch_project LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/debug/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

file(GLOB_RECURSE SOURCES_LIST
    src/*.h
    src/*.cpp
)

add_executable(file_batch ${SOURCES_LIST})

find_package(Qt5 COMPONENTS Widgets Concurrent AxContainer REQUIRED)
find_package(everything_sdk REQUIRED)

target_link_libraries(file_batch 
    Qt5::Widgets
    Qt5::Concurrent
    Qt5::AxContainer
    everything_sdk  
)