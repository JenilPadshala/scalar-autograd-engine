cmake_minimum_required(VERSION 3.15)
project(ScalarAutogradEngine CXX)

# Setting C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_WARN_DEPRECATED OFF CACHE BOOL "" FORCE)
# Location of include files
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Include)

# Fetch pybind11
include(FetchContent)
FetchContent_Declare(
    pybind11
    GIT_REPOSITORY https://github.com/pybind/pybind11.git
    GIT_TAG v2.13.1
)
FetchContent_MakeAvailable(pybind11)

pybind11_add_module(micrograd_cpp
    Source/Value.cpp
    Source/Function.cpp
    Source/Engine.cpp
    Source/Bindings.cpp
)

