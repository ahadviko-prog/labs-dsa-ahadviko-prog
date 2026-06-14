cmake_minimum_required(VERSION 3.15)
project(AlgorithmPlayground CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Inform CMake about your header directories
include_directories(include)

# Define the custom header files so CLion recognizes them in the project targets
set(DSA_HEADERS
        include/doctest.h
        include/dsa/DynamicArray.hpp
        include/dsa/Stack.hpp
        include/dsa/Queue.hpp
        include/dsa/LinkedList.hpp
        include/dsa/BST.hpp
)

# 1. Target for Interactive Menu App
add_executable(project_run main.cpp ${DSA_HEADERS}
        include/dsa/Stack.hpp
        include/dsa/Queue.hpp
        include/dsa/LinkedList.hpp
        include/dsa/BST.hpp)

# 2. Target for Automated Unit Tests
add_executable(project_tests tests.cpp ${DSA_HEADERS})