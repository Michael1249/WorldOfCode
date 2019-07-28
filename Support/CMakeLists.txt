cmake_minimum_required(VERSION 3.0.0)

project(Support)

set(SOURCES
    delegate.h
    qiostream.cpp
    config.h
    )

add_library(${PROJECT_NAME} STATIC ${SOURCES})


target_link_libraries(${PROJECT_NAME} Qt5::Core)

