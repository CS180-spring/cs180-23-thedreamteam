CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(CMAKE_CXX_STANDARD 14)

ADD_EXECUTABLE(exec
	 main.cpp
	./src/collection.cpp
    ./src/document.cpp
)

