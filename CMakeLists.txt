cmake_minimum_required(VERSION 3.17)
project(class++)
set(CMAKE_CXX_STANDARD 11)

add_executable(class++ main.cpp Variable.cpp Variable.h Constructor.cpp Constructor.h FunGenerator.cpp FunGenerator.h ClassGen.cpp ClassGen.h)
install (TARGETS class++ DESTINATION bin)