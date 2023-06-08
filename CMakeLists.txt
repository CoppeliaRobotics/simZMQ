cmake_minimum_required(VERSION 3.5)
project(simZMQ)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_MACOSX_RPATH 1)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 6.0.0)
    add_compile_options(-fpermissive)
endif()

if(NOT ZMQ_INCLUDE_DIRS OR NOT ZMQ_LIBRARIES)
    if(WIN32)
        find_package(ZeroMQ CONFIG REQUIRED)
        set(ZMQ_INCLUDE_DIRS ${ZeroMQ_INCLUDE_DIR})
        set(ZMQ_LIBRARIES libzmq-static)
    else()
        find_package(PkgConfig REQUIRED)
        pkg_check_modules(ZMQ REQUIRED IMPORTED_TARGET libzmq)
        set(ZMQ_LIBRARIES PkgConfig::ZMQ)
    endif()
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

if(NOT COPPELIASIM_INCLUDE_DIR)
    if(DEFINED ENV{COPPELIASIM_ROOT_DIR})
        set(COPPELIASIM_INCLUDE_DIR $ENV{COPPELIASIM_ROOT_DIR}/programming/include)
    else()
        set(COPPELIASIM_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../include)
    endif()
endif()
list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules
    ${COPPELIASIM_INCLUDE_DIR}/cmake)
find_package(CoppeliaSim 4.5.1.7 REQUIRED)

include_directories(${CMAKE_CURRENT_BINARY_DIR}/generated)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external)

coppeliasim_generate_stubs(${CMAKE_CURRENT_BINARY_DIR}/generated XML_FILE ${CMAKE_CURRENT_SOURCE_DIR}/callbacks.xml LUA_FILE ${CMAKE_CURRENT_SOURCE_DIR}/simZMQ.lua)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.in ${CMAKE_CURRENT_BINARY_DIR}/config.h)

coppeliasim_add_plugin(simZMQ SOURCES plugin.cpp)
add_dependencies(simZMQ generate_const)
target_link_libraries(simZMQ ${ZMQ_LIBRARIES})
