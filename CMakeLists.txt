cmake_minimum_required(VERSION 3.7...3.18)
project(mcClone)

SET(CPP_COMPILE_FLAGS "-std=c++17")
set(CMAKE_INSTALL_PREFIX /usr/local/bin)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(SRC_FILES
    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/window.cpp
    ${SRC_DIR}/shader.cpp
    ${SRC_DIR}/texture.cpp
    ${SRC_DIR}/camera.cpp
    ${SRC_DIR}/player.cpp
    ${SRC_DIR}/entity.h

    ${SRC_DIR}/terrain/chunk.cpp
    ${SRC_DIR}/terrain/world.cpp

    ${SRC_DIR}/rendering/renderer.cpp
    ${SRC_DIR}/rendering/vbo.cpp
    ${SRC_DIR}/rendering/vao.cpp
)

add_executable(mcClone ${SRC_FILES})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/stb)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/FastNoiseLite)

target_link_libraries(mcClone glfw pthread GLEW GLU GL rt Xrandr Xxf86vm Xi Xinerama X11)

target_compile_options(mcClone PRIVATE "${CPP_COMPILE_FLAGS}")

install(TARGETS mcClone
    DESTINATION ${CMAKE_INSTALL_PREFIX}
)