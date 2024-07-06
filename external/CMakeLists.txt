add_subdirectory(raylib)

add_library(raygui STATIC raygui/src/raygui.h)

target_link_libraries(raygui raylib)
