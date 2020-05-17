# --------------------- #
# (C) 2020 madoodia.com #
# --------------------- #

# DEV_LOCATION
export DEV_LOCATION=/mnt/hdd/madoodia/dev

# MADAPI_LOCATION
export MADAPI_LOCATION=$DEV_LOCATION/madAPI

# SDKS_LOCATION
export SDKS_LOCATION=/mnt/hdd/madoodia/sdks

# Qt5_DIR
export Qt5_DIR=$SDKS_LOCATION/Qt5/lib/cmake

# GTEST_LOCATION
export GTEST_LOCATION=$SDKS_LOCATION/googletest
export GTEST_BASE_LOCATION=$SDKS_LOCATION/repos/googletest

# GLEW_LOCATION
export GLEW_LOCATION=$SDKS_LOCATION/glew

# STB_LOCATION
export STB_LOCATION=$SDKS_LOCATION/stb

# OPENCL_LOCATION
export OPENCL_LOCATION=$SDKS_LOCATION/OpenCL

# MAYA DEVKIT_LOCATION
export DEVKIT_LOCATION=$SDKS_LOCATION/Maya_2019

# Adding Extra custom Definitions of the project
. $ROOT/extra.sh

