# --------------------- #
# (C) 2020 madoodia.com #
# --------------------- #



cmake_minimum_required(VERSION 3.3)

# include the project setting file
include($ENV{DEVKIT_LOCATION}/cmake/pluginEntry.cmake)

project($ENV{TARGET_NAME} CXX)

SET(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

#set .mel file list
set(MEL_FILES 
    AEgaussianTemplate.mel
)

# set SOURCE_FILES
set(SOURCE_FILES
   main.cpp
   gaussianNode.cpp
   ${MEL_FILES}
)

# set linking libraries
set(LIBRARIES
     OpenMaya
     Foundation
)

# Build plugin
build_plugin()
