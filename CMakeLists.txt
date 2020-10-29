cmake_minimum_required(VERSION 3.1)

project(project_geas VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# dependencies {{{

# GL/glew.h
#add_subdirectory(${PROJECT_SOURCE_DIR}/deps/glew/build/cmake)
#include_directories(${PROJECT_SOURCE_DIR}/deps/glew/include)
find_package(GLEW REQUIRED STATIC)

# GLFW/glfw3.h
#add_subdirectory(${PROJECT_SOURCE_DIR}/deps/glfw)
#include_directories(${PROJECT_SOURCE_DIR}/deps/glfw/include)
find_package(glfw3 REQUIRED STATIC)

# nlohmann::json module
set(JSON_BuildTests OFF CACHE INTERNAL "")
set(JSON_Install OFF CACHE INTERNAL "")
add_subdirectory(${PROJECT_SOURCE_DIR}/deps/json)

find_package(Threads REQUIRED)

# }}}

# TODO: when implementing custom renderers on a per OS basis
# https://gitlab.kitware.com/cmake/community/-/wikis/doc/tutorials/How-To-Write-Platform-Checks

# output executable
add_executable(geas)

file(GLOB_RECURSE GEAS_SOURCE
        src/*.cpp
        )
target_sources(geas PUBLIC ${GEAS_SOURCE})

target_link_libraries(geas ${GLEW_LIBRARIES} glfw3 ${GLFW_LIBRARIES} ${OPENGL_LIBRARIES} nlohmann_json::nlohmann_json ${CMAKE_THREAD_LIBS_INIT})

if(MSVC)
    target_compile_options(geas PRIVATE /W4 /WX)
else()
    target_compile_options(geas PRIVATE -Wall -Wextra -Werror -DGL_SILENCE_DEPRECIATION)
endif()