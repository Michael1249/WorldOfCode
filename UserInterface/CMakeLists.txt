cmake_minimum_required(VERSION 3.0.0)

project(UserInterface)

set(APP_SOURCE
    userinterface.cpp
    )

add_library(${PROJECT_NAME} STATIC ${APP_SOURCE})
