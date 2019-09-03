cmake_minimum_required(VERSION 3.0.0)

project(UserInterface)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5RemoteObjects)

message(STATUS "Start repc source...")
execute_process(COMMAND ${REPC_EXE} -i rep -o source
                        "${PROJECT_SOURCE_DIR}\\Interface.rep" "${PROJECT_SOURCE_DIR}\\Interface_source.h"
                WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
                RESULT_VARIABLE rep_result
                ERROR_VARIABLE rep_error
                OUTPUT_VARIABLE rep_ver)

if(ret_result EQUAL "1")
    message("Start repc source...FAIL")
    message(rep_error)
else()
    message("Start repc source...DONE")
endif()

message(STATUS "Start repc source...")
execute_process(COMMAND ${REPC_EXE} -i rep -o replica
                        "${PROJECT_SOURCE_DIR}\\Interface.rep" "${PROJECT_SOURCE_DIR}\\Interface_replica.h"
                WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
                RESULT_VARIABLE rep_result
                ERROR_VARIABLE rep_error)

if(ret_result EQUAL "1")
    message("Start repc replica...FAIL")
    message(rep_error)
else()
    message("Start repc replica...DONE")
endif()

message(STATUS "Start repc source...")
execute_process(COMMAND ${REPC_EXE} -i rep -o source
                        "${PROJECT_SOURCE_DIR}\\CommandRepresent.rep" "${PROJECT_SOURCE_DIR}\\CommandRepresent_source.h"
                WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
                RESULT_VARIABLE rep_result
                ERROR_VARIABLE rep_error
                OUTPUT_VARIABLE rep_ver)

if(ret_result EQUAL "1")
    message("Start repc source...FAIL")
    message(rep_error)
else()
    message("Start repc source...DONE")
endif()

message(STATUS "Start repc source...")
execute_process(COMMAND ${REPC_EXE} -i rep -o replica
                        "${PROJECT_SOURCE_DIR}\\CommandRepresent.rep" "${PROJECT_SOURCE_DIR}\\CommandRepresent_replica.h"
                WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
                RESULT_VARIABLE rep_result
                ERROR_VARIABLE rep_error)

if(ret_result EQUAL "1")
    message("Start repc replica...FAIL")
    message(rep_error)
else()
    message("Start repc replica...DONE")
endif()

set(SOURCES
    InterfaceBase.cpp
    LocalInterface.cpp
    RemoteInterface.cpp
    Interface_source.h
    Interface_replica.h
    Command.cpp
    CommandRepresent_source.h
    CommandRepresent_replica.h
    ServiceRepresent.cpp
    ServiceBase.cpp
    )

add_library(${PROJECT_NAME} STATIC ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${SUPPORT_DIR})

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::RemoteObjects Support)

