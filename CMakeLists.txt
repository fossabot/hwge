cmake_minimum_required(VERSION 3.0)
project(hwge)

option(USE_GLFW "use glfw" ON)
option(USE_SDL "use sdl" OFF)

set(CMAKE_BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set(CMAKE_CXX_STANDARD 11)

file(STRINGS "version.txt" HWGE_VERSION)

add_definitions(
    -DTW_STATIC
    -DTW_NO_LIB_PRAGMA
    -DTW_NO_DIRECT3D
    -DGLEW_STATIC
    -D_CRT_SECURE_NO_WARNINGS
    -DHWGE_VERSION="${HWGE_VERSION}"
)

add_subdirectory(third_party)

include_directories(
    ${OPENGL_INCLUDE_DIR}
    third_party/glfw/include
    third_party/glew/include
    third_party/glm
    third_party/freeglut/include
    third_party/libpng
    third_party/freetype/include
    third_party/sdl2/include
    include/
)

set(ALL_LIBS
    ${OPENGL_gl_LIBRARY}
    glew
    freeglut_static
    png_static
    z
    freetype
)

if(WIN32)
    set(
        ${ALL_LIBS}
        mingw32
    )
endif()

if(USE_GLFW)
    add_definitions(-DHWGE_USE_GLFW)
    set(ALL_LIBS
        ${ALL_LIBS}
        glfw
    )
elseif(USE_SDL)
    add_definitions(-DHWGE_USE_SDL)
    set(ALL_LIBS
        ${ALL_LIBS}
        SDL2main
        SDL2-static
    )
endif()

aux_source_directory(src/ HWGE_SOURCES)
aux_source_directory(include/ HWGE_INCLUDES)

add_library(${PROJECT_NAME} STATIC
    ${HWGE_SOURCES}
    ${HWGE_INCLUDES}
)

target_link_libraries(${PROJECT_NAME}
    ${ALL_LIBS}
)

add_subdirectory(testproject)