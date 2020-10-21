cmake_minimum_required(VERSION 3.1)

project(project_geas VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# GL/glew.h
add_subdirectory(${PROJECT_SOURCE_DIR}/modules/glew/build/cmake)
include_directories(${PROJECT_SOURCE_DIR}/modules/glew/include)

# GLFW/glfw3.h
add_subdirectory(${PROJECT_SOURCE_DIR}/modules/glfw)
include_directories(${PROJECT_SOURCE_DIR}/modules/glfw/include)

# nlohmann::json module
set(JSON_BuildTests OFF CACHE INTERNAL "")
set(JSON_Install OFF CACHE INTERNAL "")
add_subdirectory(${PROJECT_SOURCE_DIR}/modules/json)

# TODO: when implementing custom renderers on a per OS basis
# https://gitlab.kitware.com/cmake/community/-/wikis/doc/tutorials/How-To-Write-Platform-Checks

# output executable
add_executable(geas)

# linking woes :(
target_link_libraries(geas glfw glew nlohmann_json::nlohmann_json ${GLFW_LIBRARIES})

file(GLOB GEAS_SOURCE
        src/*.cpp
        src/**/*.cpp
        )
target_sources(geas PUBLIC ${GEAS_SOURCE})

if(MSVC)
    target_compile_options(geas PRIVATE /W4 /WX)
else()
    target_compile_options(geas PRIVATE -Wall -Wextra -pedantic -Werror -DGL_SILENCE_DEPRECIATION)
endif()