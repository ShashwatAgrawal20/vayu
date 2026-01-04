cmake_minimum_required(VERSION 3.20)

project(vayu C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(TARGET_NAME vayu)

find_package(PkgConfig REQUIRED)
pkg_check_modules(DEPS REQUIRED IMPORTED_TARGET wlroots-0.20 wayland-server xkbcommon)

file(GLOB_RECURSE SRC_FILES "src/*.c")

add_executable(${TARGET_NAME} ${SRC_FILES})
target_compile_options(${TARGET_NAME} PRIVATE -Wall -Wextra -pedantic)
target_compile_definitions(${TARGET_NAME} PRIVATE -DWLR_USE_UNSTABLE)

target_include_directories(${TARGET_NAME} PRIVATE include)
target_link_libraries(${TARGET_NAME} PRIVATE
    PkgConfig::DEPS
)
