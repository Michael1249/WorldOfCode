cmake_minimum_required(VERSION 3.0.0)

project(WorldOfCode VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Qt5Core REQUIRED)

find_program(REPC_EXE repc REQUIRED)
if(NOT REPC_EXE)
    message(FATAL_ERROR "REPC not found!")
endif()


get_filename_component(SUPPORT_DIR Support ABSOLUTE)
get_filename_component(USERINTERFACE_DIR UserInterface ABSOLUTE)

add_subdirectory(Support)
add_subdirectory(Games)
add_subdirectory(Client)
add_subdirectory(Server)
add_subdirectory(UserInterface)
add_subdirectory(UserInterface_Example)


add_executable(${PROJECT_NAME} "main.cpp")

target_link_libraries(${PROJECT_NAME}
    Qt5::Core
    UserInterface
    Server
    )

