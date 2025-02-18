cmake_minimum_required(VERSION 3.10)

project(Minesweeper)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

set(SOURCES
    src/board.cpp
    src/logger.cpp
    src/main.cpp
    src/minesweeper.cpp
)

add_executable(minesweeper ${SOURCES})

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_options(minesweeper PRIVATE -Wall -Wextra -Wpedantic)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(minesweeper PRIVATE /W4)
endif()

