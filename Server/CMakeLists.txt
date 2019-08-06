cmake_minimum_required(VERSION 3.0.0)

project(Server)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

add_subdirectory(GameCore)

set(SOURCES
    Server.cpp
    )

add_library(${PROJECT_NAME} STATIC ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${SUPPORT_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC ${USERINTERFACE_DIR})

target_link_libraries(${PROJECT_NAME} Qt5::Core)
target_link_libraries(${PROJECT_NAME} Support)
target_link_libraries(${PROJECT_NAME} UserInterface)
