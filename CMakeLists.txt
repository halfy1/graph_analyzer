cmake_minimum_required(VERSION 3.10)
project(OrdTreeChecker)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}/src)

set(SOURCES
    src/main.cpp
    src/Graph.cpp
    src/OrdTreeChecker.cpp
)

set(HEADERS
    src/Graph.h
    src/OrdTreeChecker.h
)

add_executable(ordtree_checker ${SOURCES} ${HEADERS})

file(COPY ${CMAKE_SOURCE_DIR}/tests/ DESTINATION ${CMAKE_BINARY_DIR}/tests/)