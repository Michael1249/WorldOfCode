cmake_minimum_required(VERSION 3.0.0)

project(Server VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

add_subdirectory(Game)
add_subdirectory(ServerUIComponent)

add_executable(${PROJECT_NAME} "main.cpp")

target_include_directories(${PROJECT_NAME} PUBLIC ${SUPPORT_DIR})
target_link_libraries(${PROJECT_NAME} Qt5::Core)
target_link_libraries(${PROJECT_NAME} Support)
