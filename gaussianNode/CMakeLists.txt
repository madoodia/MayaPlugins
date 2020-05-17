# --------------------- #
# (C) 2020 madoodia.com #
# --------------------- #

cmake_minimum_required(VERSION 3.3)
project($ENV{TARGET_NAME} CXX)

set(CMAKE_MODULE_PATH $ENV{ROOT}/maya_api/modules)

SET(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)


SET(CMAKE_AUTOMOC ON)
# SET(CMAKE_AUTOUIC ON)
# SET(CMAKE_AUTORCC ON)

set(MAYA_INCLUDE_DIR $ENV{MAYA_LOCATION}/include)

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

set(SOURCES 
    main.cpp
    gaussianNode.cpp
)

find_package(Maya REQUIRED)

include_directories(${MAYA_INCLUDE_DIR})
include_directories($ENV{MADAPI_LOCATION}/include)
link_directories(${MAYA_LIBRARY_DIR})
add_library(${PROJECT_NAME} SHARED ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${MAYA_LIBRARIES})

MAYA_PLUGIN(${PROJECT_NAME})
# install(TARGETS ${PROJECT_NAME} ${MAYA_TARGET_TYPE} DESTINATION plug-ins)
install(TARGETS ${PROJECT_NAME} ${MAYA_TARGET_TYPE} DESTINATION .)
