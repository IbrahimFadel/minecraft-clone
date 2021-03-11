cmake_minimum_required(VERSION 3.7...3.18)
project(minecraft)

SET(CPP_COMPILE_FLAGS "")
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(SRC_FILES
    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/window.cpp
    ${SRC_DIR}/shader.cpp
    ${SRC_DIR}/texture.cpp
    ${SRC_DIR}/camera.cpp

    ${SRC_DIR}/terrain/block.cpp
    ${SRC_DIR}/terrain/chunk.cpp
    ${SRC_DIR}/terrain/world.cpp

    ${SRC_DIR}/rendering/vbo.cpp
    ${SRC_DIR}/rendering/vao.cpp
)

# add_library(noise 
#     ${CMAKE_CURRENT_SOURCE_DIR}/lib/noise/noise1234.cpp
#     ${CMAKE_CURRENT_SOURCE_DIR}/lib/noise/noise1234.h
# )

# add_library(fastNoiseLite
#     ${CMAKE_CURRENT_SOURCE_DIR}/lib/FastNoiseLite/FastNoiseLite.h
# )

# add_library(fastNoise 
#     ${CMAKE_CURRENT_SOURCE_DIR}/lib/FastNoiseSIMD/FastNoiseSIMD/FastNoiseSIMD.cpp
#     ${CMAKE_CURRENT_SOURCE_DIR}/lib/FastNoiseSIMD/FastNoiseSIMD/FastNoiseSIMD_sse41.cpp
#     ${CMAKE_CURRENT_SOURCE_DIR}/lib/FastNoiseSIMD/FastNoiseSIMD/FastNoiseSIMD_sse2.cpp
#     ${CMAKE_CURRENT_SOURCE_DIR}/lib/FastNoiseSIMD/FastNoiseSIMD/FastNoiseSIMD_neon.cpp
#     ${CMAKE_CURRENT_SOURCE_DIR}/lib/FastNoiseSIMD/FastNoiseSIMD/FastNoiseSIMD_internal.cpp
#     ${CMAKE_CURRENT_SOURCE_DIR}/lib/FastNoiseSIMD/FastNoiseSIMD/FastNoiseSIMD_avx512.cpp
# )

# set_target_properties(fastNoise PROPERTIES COMPILE_FLAGS "-std=c++11")


# set_property(SOURCE
#     ${CMAKE_CURRENT_SOURCE_DIR}/lib/FastNoiseSIMD/FastNoiseSIMD/FastNoiseSIMD_sse41.cpp
#     PROPERTY COMPILE_FLAGS -msse4.1
# )
# set_property(SOURCE
#     ${CMAKE_CURRENT_SOURCE_DIR}/lib/FastNoiseSIMD/FastNoiseSIMD/FastNoiseSIMD_sse2.cpp
#     PROPERTY COMPILE_FLAGS -msse2
# )
# set_property(SOURCE
# ${CMAKE_CURRENT_SOURCE_DIR}/lib/FastNoiseSIMD/FastNoiseSIMD/FastNoiseSIMD_avx512.cpp
# PROPERTY COMPILE_FLAGS -mavx512f
# )


add_executable(minecraft ${SRC_FILES})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/stb)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/FastNoiseLite)
# include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/FastNoiseSIMD/FastNoiseSIMD)

target_link_libraries(minecraft glfw pthread GLEW GLU GL rt Xrandr Xxf86vm Xi Xinerama X11)

target_compile_options(minecraft PRIVATE "${CPP_COMPILE_FLAGS}")