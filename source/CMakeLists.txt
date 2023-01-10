# CMakeList.txt : CMake project for RaycastNative, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

find_package(SDL2 REQUIRED)

# Add source to this project's executable.
add_executable (${PROJECT_NAME} "main.c" "constants.h")

target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2 SDL2::SDL2main)

# TODO: Add tests and install targets if needed.
