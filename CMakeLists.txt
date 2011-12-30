cmake_minimum_required(VERSION 2.6)
project(Zorgster)
set(CMAKE_BUILD_TYPE Debug)

# Libs
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules"
    ${CMAKE_MODULE_PATH})
find_package(SFML 1.6 REQUIRED system window graphics network audio)
find_package(OpenGL)
find_package(GLUT)
find_package(Boost)

if(NOT SFML_FOUND)
    message(FATAL_ERROR "SFML not found!")
endif(NOT SFML_FOUND)

if(NOT OPENGL_FOUND)
    message(FATAL_ERROR "OpenGL not found!")
endif(NOT OPENGL_FOUND)

if(NOT GLUT_FOUND)
    message(FATAL_ERROR "GLUT not found!")
endif(NOT GLUT_FOUND)

if(NOT Boost_FOUND)
    message(FATAL_ERROR "Boost not found!")
endif(NOT Boost_FOUND)

# add executable
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})
set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)
set(DATA_DIR ${PROJECT_SOURCE_DIR}/data)
set(EXECUTABLE_NAME "Zorgster")

configure_file(
    "${PROJECT_SOURCE_DIR}/src/config.h.in"
    "${PROJECT_SOURCE_DIR}/src/config.h"
    )

include_directories(
    ${SRC_DIR}
    ${PROJECT_BINARY_DIR}
    ${SFML_INCLUDE_DIR}
    ${OPENGL_INCLUDE_DIR}
    ${GLUT_INCLUDE_DIR}
    ${Boost_INCLUDE_DIR}
    )

file(GLOB SOURCES ${SRC_DIR}/*.c ${SRC_DIR}/*.cpp)
file(GLOB HEADERS ${SRC_DIR}/*.h ${SRC_DIR}/*.hpp)
file(GLOB RESOURCES ${DATA_DIR}/*.png)
add_executable(${EXECUTABLE_NAME}
    ${HEADERS}
    ${SOURCES}
    ${RESOURCES}
    )

# link to libs
set(CORELIBS ${SFML_LIBRARIES} ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} )
target_link_libraries(${EXECUTABLE_NAME} ${CORELIBS})

# add some compiler flags
set(CMAKE_CXX_FLAGS "-g -Wall -Wextra -Weffc++")

message(STATUS
    ${Boost_INCLUDE_DIR}
    )
