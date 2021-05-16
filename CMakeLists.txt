cmake_minimum_required(VERSION 3.17)
project(class++)
set(CMAKE_CXX_STANDARD 11)

file(GLOB source  "src/*.cpp"  )
file(GLOB headers "include/*.h")

add_executable(class++ ${source} ${headers} main.cpp)
install (TARGETS class++ DESTINATION bin)