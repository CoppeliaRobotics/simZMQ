cmake_minimum_required(VERSION 3.5)
project(simExtZMQ)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_MACOSX_RPATH 1)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 6.0.0)
    add_compile_options(-fpermissive)
endif()

if(WIN32)
    find_package(ZeroMQ CONFIG REQUIRED)
    set(ZMQ_INCLUDE_DIRS ${ZeroMQ_INCLUDE_DIR})
else()
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(ZMQ REQUIRED IMPORTED_TARGET libzmq)
endif()

find_path(ZMQ_H_DIR zmq.h PATHS ${ZMQ_INCLUDE_DIRS} REQUIRED)

find_package(Python3 REQUIRED COMPONENTS Interpreter)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/generated)
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/generated/zmq_constants.cpp
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/zmq_constants.py
    COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/zmq_constants.py
        ${CMAKE_CURRENT_BINARY_DIR}/generated/zmq_constants.cpp
        ${ZMQ_H_DIR}/zmq.h
)
add_custom_target(generate_const DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/generated/zmq_constants.cpp)

if(NOT LIBPLUGIN_DIR)
    if(DEFINED ENV{COPPELIASIM_ROOT_DIR})
        set(LIBPLUGIN_DIR $ENV{COPPELIASIM_ROOT_DIR}/programming/libPlugin)
    else()
        set(LIBPLUGIN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../libPlugin)
    endif()
endif()
list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules
    ${LIBPLUGIN_DIR}/cmake)
find_package(CoppeliaSim 4.1.0.0 REQUIRED)

include_directories(${CMAKE_CURRENT_BINARY_DIR}/generated)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external)

coppeliasim_generate_stubs(${CMAKE_CURRENT_BINARY_DIR}/generated XML_FILE ${CMAKE_CURRENT_SOURCE_DIR}/callbacks.xml LUA_FILE ${CMAKE_CURRENT_SOURCE_DIR}/simZMQ.lua)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.in ${CMAKE_CURRENT_BINARY_DIR}/config.h)

coppeliasim_add_plugin(simExtZMQ SOURCES plugin.cpp)
add_dependencies(simExtZMQ generate_const)
if(WIN32)
    target_link_libraries(simExtZMQ libzmq-static)
else()
    target_link_libraries(simExtZMQ PkgConfig::ZMQ)
endif()
