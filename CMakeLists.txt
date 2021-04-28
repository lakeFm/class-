cmake_minimum_required(VERSION 3.17)
project(class++)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON )
include_directories(include)
set(CMAKE_SOURCE_DIR src)

file(GLOB HEADERS "include/*.h")
file(GLOB SOURCE  "src/*.cpp")

add_executable(class++ ${HEADERS} ${SOURCE} main.cpp)