cmake_minimum_required(VERSION 3.0.0)

project(UserInterface)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5RemoteObjects)

set(SOURCES
    Interface.cpp
    Interface_source.h
    CommandParser.cpp
    Command.cpp
    StdCommands.cpp
    UITest.cpp
    )

add_library(${PROJECT_NAME} STATIC ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${SUPPORT_DIR})

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::RemoteObjects Support)

