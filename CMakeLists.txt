cmake_minimum_required(VERSION 3.15)
project(ScalarAutogradEngine CXX)

# Setting C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Location of include files
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Include)

# Group all source files together into the executable target
add_executable(scalar_autograd
Source/Value.cpp
Source/Function.cpp
Source/Engine.cpp
Source/Main.cpp
)


