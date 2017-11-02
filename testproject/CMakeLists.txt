cmake_minimum_required(VERSION 3.0)
project(hwge-testproject)

set(ALL_SOURCES
    src/main.cpp
)

add_executable(testproject
    ${ALL_SOURCES}
)

target_link_libraries(testproject
    hwge
)