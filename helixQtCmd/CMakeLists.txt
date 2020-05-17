# --------------------- #
# (C) 2020 madoodia.com #
# --------------------- #



cmake_minimum_required(VERSION 3.3)

# include the project setting file
include($ENV{DEVKIT_LOCATION}/cmake/pluginEntry.cmake)

project($ENV{TARGET_NAME} CXX)

SET(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# set SOURCE_FILES
set(SOURCE_FILES
   helixQtCmd.cpp
)

# set linking libraries
set(LIBRARIES
     OpenMaya
     Foundation
)

# Build plugin
build_plugin()

find_package(Qt5 COMPONENTS Core Widgets Gui REQUIRED)
target_link_libraries($ENV{TARGET_NAME} Qt5::Core Qt5::Widgets Qt5::Gui)