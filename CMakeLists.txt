cmake_minimum_required(VERSION 3.16)
project(ZYEngine)

set(CMAKE_CXX_STANDARD 14)

find_library(GLEW_LIB glew)
if (NOT GLEW_LIB)
    message(FATAL_ERROR "glew not found")
endif()

find_library(OPENGL_LIB opengl3)
if (NOT OPENGL_LIB)
    message(FATAL_ERROR "opengl3 not found")
endif()

find_library(SDL2 SDL2)
if (NOT SDL2)
    message(FATAL_ERROR "SDL2 not found")
endif()

find_library(TTF_SDL
        NAMES SDL2_ttf
        HINTS "/Library/Frameworks/SDL2_ttf.framework")
if (NOT TTF_SDL)
    message(FATAL_ERROR "SDL2_TTF not found")
endif()

find_library(IMAGE_SDL SDL2_image)
if (NOT IMAGE_SDL)
    message(FATAL_ERROR "SDL2_IMAGE not found")
endif()

find_library(MIXER_SDL SDL2_mixer)
if (NOT MIXER_SDL)
    message(FATAL_ERROR "SDL2_mixer not found")
endif()

find_library(OPENGL OpenGL)
if (NOT OPENGL)
    message(FATAL_ERROR "OPENGL not found")
endif()

find_library(COCOA Cocoa)
if (NOT COCOA)
    message(FATAL_ERROR "COCOA not found")
endif()

find_library(COREVID CoreVideo)
if (NOT COREVID)
    message(FATAL_ERROR "CoreVideo not found")
endif()

find_library(IOKIT_LIB IOKit)
if (NOT IOKIT_LIB)
    message(FATAL_ERROR "IOKit not found")
endif()

set(IMGUI_DIR libs/imgui/)
include_directories(${IMGUI_DIR} ${IMGUI_DIR}/examples)

include_directories(libs/glm/)

add_executable(ZYEngine src/main.cpp
        ${IMGUI_DIR}/examples/imgui_impl_sdl.cpp
        ${IMGUI_DIR}/examples/imgui_impl_opengl3.cpp
        ${IMGUI_DIR}/imgui.cpp
        ${IMGUI_DIR}/imgui_draw.cpp
        ${IMGUI_DIR}/imgui_demo.cpp
        ${IMGUI_DIR}/imgui_widgets.cpp
        src/Engine.cpp
        src/Engine.h
        src/Constants.h
        src/Game/Game.cpp
        src/Game/Game.h src/Game/EntityManager.cpp src/Game/EntityManager.h src/Game/Entity.cpp src/Game/Entity.h src/Game/Component.h src/Game/Components/SpriteComponent.h src/EntityWindow.cpp src/EntityWindow.h src/Game/AssetManager.cpp src/Game/AssetManager.h src/Game/TextureManager.cpp src/Game/TextureManager.h)
message(${OPENGL})

target_link_libraries(ZYEngine ${GLEW_LIB} ${OPENGL_LIB})
target_include_directories(ZYEngine PRIVATE /usr/local/include/GL)

target_link_libraries(ZYEngine ${OPENGL} ${COCOA} ${COREVID})
target_include_directories(ZYEngine PRIVATE ${OPENGL}/Headers)

target_link_libraries(ZYEngine ${SDL2})
target_include_directories(ZYEngine PRIVATE ${SDL2}/Headers)

target_link_libraries(ZYEngine ${IMAGE_SDL})
target_include_directories(ZYEngine PRIVATE ${IMAGE_SDL}/Headers)

target_link_libraries(ZYEngine ${TTF_SDL})
target_include_directories(ZYEngine PRIVATE ${TTF_SDL}/Headers)

target_link_libraries(ZYEngine ${MIXER_SDL})
target_include_directories(ZYEngine PRIVATE ${MIXER_SDL}/Headers)