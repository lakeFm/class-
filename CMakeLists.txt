cmake_minimum_required(VERSION 3.17)
project(class++)
set(CMAKE_CXX_STANDARD 11)
include_directories(include)
file(GLOB SRC src/*.cpp)
add_executable(class++ main.cpp ${SRC})
install (TARGETS class++ DESTINATION bin)