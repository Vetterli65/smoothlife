cmake_minimum_required(VERSION 3.0)

project(smoothlife LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(external/raylib)

set(SOURCE_FILES
    src/main.cpp
    src/scene.cpp
    src/raygui.cpp
)

set(HEADER_FILES
    src/scene.h
)

add_executable(smoothlife ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(smoothlife raylib)

target_include_directories(smoothlife PRIVATE external/raygui/src)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(smoothlife PRIVATE -Wall -Wextra)
endif()

if (UNIX)
    target_link_libraries(smoothlife pthread)
endif()
