cmake_minimum_required(VERSION 3.0.0)

project(WorldOfCode VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
find_package(Qt5Core)

include_directories(UserInterface)

add_executable(${PROJECT_NAME} "main.cpp")

add_subdirectory(UserInterface)
add_subdirectory(Client)
add_subdirectory(Server)

target_link_libraries(${PROJECT_NAME} Qt5::Core)
target_link_libraries(${PROJECT_NAME} UserInterface)

