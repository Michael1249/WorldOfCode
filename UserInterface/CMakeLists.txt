cmake_minimum_required(VERSION 3.0.0)

project(UserInterface)

set(SOURCES
    userinterface.cpp
    commandparser.cpp
    command.cpp
    )

include_directories(StringParser_gen)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

add_subdirectory(StringParser_gen)

target_link_libraries(${PROJECT_NAME} StringParser_gen)
