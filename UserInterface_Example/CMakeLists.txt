cmake_minimum_required(VERSION 3.0.0)

project(Example VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5RemoteObjects)


add_executable(LocalInterface Local_main.cpp worker.cpp)

target_include_directories(LocalInterface PUBLIC ${SUPPORT_DIR} PUBLIC ${USERINTERFACE_DIR})
target_link_libraries(LocalInterface Qt5::Core Qt5::RemoteObjects Support UserInterface)

add_executable(RemoteInterface Remote_main.cpp worker.cpp)

target_include_directories(RemoteInterface PUBLIC ${SUPPORT_DIR} PUBLIC ${USERINTERFACE_DIR})
target_link_libraries(RemoteInterface Qt5::Core Qt5::RemoteObjects Support UserInterface)
