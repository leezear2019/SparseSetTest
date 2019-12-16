cmake_minimum_required(VERSION 3.15)
project(SparseSetTest)

set(CMAKE_CXX_STANDARD 17)

add_executable(SparseSetTest main.cpp Biset.cpp Biset.h BitSet64.hpp)