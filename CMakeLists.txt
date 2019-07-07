cmake_minimum_required(VERSION 3.0.0)

project(WorldOfCode VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
find_package(Qt5Core)

get_filename_component(SUPPORT_DIR Support ABSOLUTE)

add_subdirectory(Support)
add_subdirectory(Client)
add_subdirectory(Server)
add_subdirectory(UserInterface)

add_executable(${PROJECT_NAME} "main.cpp")

target_link_libraries(${PROJECT_NAME}
    Qt5::Core
    UserInterface
    )

