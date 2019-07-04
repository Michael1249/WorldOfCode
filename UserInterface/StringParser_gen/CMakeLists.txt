cmake_minimum_required(VERSION 3.0.0)

project(StringParser_gen)

set(SOURCES
    stringparser.cpp
    )

#FILE(GLOB_RECURSE COMMAND_LIST "command_list.xml")
#FILE(GLOB_RECURSE GENERATOR "stringparser_generator.py")

add_library(${PROJECT_NAME} STATIC ${SOURCES})

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
    COMMAND python ${CMAKE_CURRENT_SOURCE_DIR}/stringparser_generator.py
    )
