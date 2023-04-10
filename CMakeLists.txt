cmake_minimum_required(VERSION 3.22)
set(CMAKE_CXX_STANDARD 17)

project(graphics-engine)

file(GLOB_RECURSE SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)
add_executable(graphics-engine main.cpp ${SOURCE_FILES})
target_include_directories(graphics-engine PUBLIC include)

target_include_directories(graphics-engine PUBLIC include/glad)
target_include_directories(graphics-engine PUBLIC common/thirdparty/old/glm)

find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})

find_package(SDL2 REQUIRED)
target_link_libraries(graphics-engine ${OpenGL_LIBS} SDL2::SDL2)

