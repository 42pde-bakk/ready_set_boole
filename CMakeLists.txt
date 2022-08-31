cmake_minimum_required(VERSION 3.22)
project(ready_set_boole)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(RPN_DIR Reverse_Polish_Notation/srcs)

set(SRC_FILES
        ${RPN_DIR}/RPN_Tree.cpp
        ${RPN_DIR}/RPN_Node.cpp
        ${RPN_DIR}/build_tree_from_string.cpp
        ${RPN_DIR}/utils.cpp
        ${RPN_DIR}/truth_table.cpp
        ${RPN_DIR}/TruthTable.cpp
)

include_directories(Reverse_Polish_Notation/include)

add_executable(ex00 ex00/main.cpp ex00/adder.cpp)
add_executable(ex01 ex01/main.cpp ex01/multiplier.cpp ex00/adder.cpp)
add_executable(ex02 ex02/gray_code.cpp)
add_executable(ex03 ex03/main.cpp ${SRC_FILES})
add_executable(ex04 ex04/main.cpp ${SRC_FILES})
add_executable(ex05 ex05/main.cpp ${SRC_FILES})
add_executable(ex06 ex06/main.cpp ${SRC_FILES})
add_executable(ex07 ex07/main.cpp ${SRC_FILES})
add_executable(ex08 ex08/main.cpp ${SRC_FILES})
add_executable(ex09 ex09/main.cpp ${SRC_FILES})
add_executable(ex10 ex10/main.cpp ${SRC_FILES})
add_executable(ex11 ex11/main.cpp ${SRC_FILES})
