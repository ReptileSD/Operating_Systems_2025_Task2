cmake_minimum_required(VERSION 3.10)

project(ProcessManager)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_library(process_manager STATIC
    src/process_manager.cpp
)

add_executable(test_program tests/main.cpp)

target_link_libraries(test_program process_manager)
