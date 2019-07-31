cmake_minimum_required(VERSION 3.0.0)

project(Client)

set(SOURCES
    #client.cpp
    )

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${SUPPORT_DIR})
#target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Network)
