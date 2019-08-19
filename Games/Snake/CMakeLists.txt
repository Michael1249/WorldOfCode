cmake_minimum_required(VERSION 3.0.0)

project(Snake VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5RemoteObjects)

set(SOURCES
    main.cpp
    Interface_replica.h
    )

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${SUPPORT_DIR})
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::RemoteObjects Support)
