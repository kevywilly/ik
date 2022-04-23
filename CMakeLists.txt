cmake_minimum_required(VERSION 3.22)
project(ik)

set(CMAKE_CXX_STANDARD 14)

add_executable(ik main.cpp src/ik/chain.h src/ik/utils.h src/ik/matrix.h src/ik/inverse.h)
