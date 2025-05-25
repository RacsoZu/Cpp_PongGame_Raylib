cmake_minimum_required(VERSION 3.11)
project(Pong_Game)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Change the output executable directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

# Dependencies
set(RAYLIB_VERSION 5.5)
find_package(raylib ${RAYLIB_VERSION} QUIET)
if (NOT raylib_FOUND)
    include(FetchContent)
    FetchContent_Declare(
            raylib
            DOWNLOAD_EXTRACT_TIMESTAMP OFF
            URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    )
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED)
        set(FETCH CONTENT_QUIET NO)
        FetchContent_MakeAvailable(raylib)
    endif()
endif()

# Source files in src/
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES}
        src/SoundManager.h
        src/GameState.h
        src/Ball.h
        src/Ball.cpp
        src/Paddle.h
        src/Paddle.cpp
        src/HumanPaddle.h
        src/HumanPaddle.cpp
        src/CpuPaddle.h
        src/CpuPaddle.cpp
        src/Button.h
        src/Button.cpp
        src/UIUtils.h
        src/UIUtils.cpp)
target_link_libraries(${PROJECT_NAME} raylib)
if (WIN32)
    set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE TRUE)
endif()

# Copy assets/ to output dir
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets)

# Web (Emscripten) config
if (${PLATFORM} STREQUAL "Web")
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -s ASYNCIFY -s GL_ENABLE_GET_PROC_ADDRESS=1")
endif()

# macOS specific
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()
