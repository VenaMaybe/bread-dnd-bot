cmake_minimum_required(VERSION 3.16)
project(breadDnDBot)

# Need C++20 for coroutines
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Manually find them smh cuz findpackage is cringe
include_directories(/usr/local/include)
link_directories(/usr/local/lib)

# Automatically collect all source and header files
file(GLOB_RECURSE SRC_FILES "src/*.cpp")
file(GLOB_RECURSE HEADER_FILES "include/*.hpp")

# Find the python interpreter and libraries
find_package(Python3 COMPONENTS Interpreter Development REQUIRED)

# For now just compile main.cpp
add_executable(breadDnDBot ${SRC_FILES} ${HEADER_FILES})

# Include additional directories if needed / makes #includes relative to include/
target_include_directories(breadDnDBot PRIVATE include)

# Link DPP
# target_link_libraries(breadDnDBot dpp)

# Link against the Python libraries
target_link_libraries(breadDnDBot PRIVATE dpp Python3::Python)
