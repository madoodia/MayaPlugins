# --------------------- #
# (C) 2020 madoodia.com #
# --------------------- #

# -----= Getting Inputs =---- #
ROOT=$1
FOLDER=$2
export FILE_NAME=$3
export TARGET_NAME=$(basename $ROOT)
# --------------------------- #

# ------= Include Envs =----- #
LINUX_DIR=$(dirname "$0")
. $LINUX_DIR/envVars.sh
# --------------------------- #

# --------- Common ---------- #
cd $ROOT
if test -d build; then
    rm -rf build
fi
if test -f "$TARGET_NAME"; then
    rm -rf $TARGET_NAME
fi
mkdir build
cd build

cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_PREFIX_PATH=$GTEST_LOCATION $ROOT/$FOLDER
cmake --build .

# ---= Workspace Project =--- #
# --------- Release --------- #
if [ "$FOLDER" = "." ]; then
    cp src/$TARGET_NAME $ROOT
fi
# --------------------------- #


# ----= Folder Project =----- #
# -----= File Project =------ #
# --------- Release --------- #
if [ "$FOLDER" != "." ]; then
    cp $TARGET_NAME $ROOT
fi
# --------------------------- #
