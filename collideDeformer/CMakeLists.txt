# --------------------- #
# (C) 2020 madoodia.com #
# --------------------- #



cmake_minimum_required(VERSION 3.3)

# include the project setting file
include($ENV{DEVKIT_LOCATION}/cmake/pluginEntry.cmake)

project($ENV{TARGET_NAME} CXX)

SET(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)


# set SOURCE_FILES
set(SOURCE_FILES
   main.cpp
   collideDeformer.cpp
)

# set linking libraries
set(LIBRARIES
     OpenMaya
     OpenMayaAnim
     Foundation
)

# Build plugin
build_plugin()
