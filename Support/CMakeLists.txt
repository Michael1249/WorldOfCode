cmake_minimum_required(VERSION 3.0.0)

project(Support)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

set(SOURCES
    delegate.h
    )

add_library(${PROJECT_NAME} STATIC ${SOURCES})


target_link_libraries(${PROJECT_NAME} Qt5::Core)

