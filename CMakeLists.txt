cmake_minimum_required(VERSION 3.25.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_BINARY_DIR bin)
set(CMAKE_SOURCE_DIR src)

set(NAME hashlang)
project(${NAME} VERSION 1.0)

file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_executable(${NAME} ${SRC_FILES})
target_include_directories(${NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)
