cmake_minimum_required(VERSION 3.10)
project(GraphAnalyzer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O2")
endif()

set(SOURCES
    src/main.cpp
    src/Graph.cpp
    src/GraphAnalyzer.cpp
    src/FileHandler.cpp
)

add_executable(graph_analyzer ${SOURCES})

target_include_directories(graph_analyzer PRIVATE src)

if(WIN32)
    target_link_libraries(graph_analyzer stdc++fs)
endif()