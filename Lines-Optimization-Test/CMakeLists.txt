cmake_minimum_required(VERSION 3.20)

project(Software-Renderer)

set(EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)

include_directories(include/)

add_executable(${PROJECT_NAME} src/main.cpp)

add_library(renderer STATIC src/renderer.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3 renderer)