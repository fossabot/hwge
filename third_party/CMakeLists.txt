add_definitions(
    -DTW_STATIC
    -DTW_NO_LIB_PRAGMA
    -DTW_NO_DIRECT3D
    -DGLEW_STATIC
    -D_CRT_SECURE_NO_WARNINGS
    -DASSIMP_BUILD_BOOST_WORKAROUND
)

find_package(OpenGL REQUIRED)

include_directories(${OPENGL_INCLUDE_DIR})

# SDL2
#set(SDL_DYNAMIC_API 0)
#set(SDL_JOYSTICK OFF CACHE BOOL "" FORCE) # Atleast for now SDL2 will not have joystick support
#set(SDL_HAPTIC OFF CACHE BOOL "" FORCE) # Atleast for now SDL2 will not have joystick support
#set(SDL_SHARED OFF CACHE BOOL "" FORCE)
add_subdirectory(sdl2)
include_directories(sdl2/include)

# GLFW
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(glfw)

include_directories(glfw/include)

set(GLFW_LIBS
    ${GLFW_LIBRARIES}
)

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set(GLFW_LIBS
        ${GLFW_LIBS}
        -lGL -lGLU -lXrandr -lXext -lX11 -lrt
        ${CMAKE_DL_LIBS}
    )
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(GLFW_LIBS
        ${GLFW_LIBS}
        ${CMAKE_DL_LIBS}
    )
endif()

# GLEW
include_directories(glew/include)

set(GLEW_SOURCES
    glew/src/glew.c
)

add_library(glew STATIC
    ${GLEW_SOURCES}
)

target_link_libraries(glew
    ${OPENGL_gl_LIBRARY}
)

# FreeGLUT
set(FREEGLUT_BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(FREEGLUT_BUILD_STATIC_LIBS ON CACHE BOOL "" FORCE)
set(FREEGLUT_BUILD_DEMOS OFF CACHE BOOL "" FORCE)

add_subdirectory(freeglut)

include_directories(freeglut/include)

# libpng
set(PNG_SHARED OFF CACHE BOOL "" FORCE)
set(PNG_BUILD_ZLIB ON CACHE BOOL "" FORCE)

add_subdirectory(libpng)

include_directories(libpng)

# freetype
add_subdirectory(freetype)

include_directories(freetype/include)