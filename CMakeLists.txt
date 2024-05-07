cmake_minimum_required(VERSION 3.10)
project(nielsen_function) 

# Set C++17 as the standard for the project
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add executable
add_executable(myProgram xdim_rstr_udf.cpp xdim_rstr_udf_test.cpp)