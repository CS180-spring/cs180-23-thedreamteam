CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(CMAKE_CXX_STANDARD 14)

ADD_EXECUTABLE(exec
	 main.cpp
)

add_custom_target(clean
    COMMAND rm -rf ${CMAKE_BINARY_DIR}/a.out ${CMAKE_BINARY_DIR}/exec ${CMAKE_BINARY_DIR}/CMakeCache.txt ${CMAKE_BINARY_DIR}/Makefile ${CMAKE_BINARY_DIR}/cmake_install.cmake ${CMAKE_SOURCE_DIR}/CMakeFiles
)