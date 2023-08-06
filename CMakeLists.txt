# CMakeList.txt : CMake project for BUDe, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.10)

project ("BUDe")

# Add source to this project's executable.
add_executable (BUDe "BUDe.cpp" "BUDe.h")

set(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_STANDARD_REQUIRED True)

# TODO: Add tests and install targets if needed.
