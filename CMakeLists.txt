cmake_minimum_required(VERSION 3.22)
project(ready_set_boole)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(ex00 ex00/adder.cpp)
add_executable(ex01 ex01/multiplier.cpp)
add_executable(ex02 ex02/gray_code.cpp)
add_executable(ex03 ex03/boolean_evaluation.cpp ex03/RPN_Node.hpp ex03/RPN_Node.cpp ex03/utils.cpp)
add_executable(ex04 ex04/truth_table.cpp ex04/RPN_Node.hpp ex04/RPN_Node.cpp ex04/utils.cpp)
