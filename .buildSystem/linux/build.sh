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
if [ -d build ] && [ "$NEED_BUILD" = 0 ]; then
    rm -rf build
fi
if [ ! -d "build" ]; then
    mkdir build
fi

if [ -f "$TARGET_NAME.$OUTPUT_FILE_EXTENSION" ]; then
    rm -rf $TARGET_NAME.$OUTPUT_FILE_EXTENSION
fi

cd build

cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH=$EXTRA_PREFIX_PATH $ROOT/$FOLDER
cmake --build .

# ---= Workspace Project =--- #
# --------- Release --------- #
if [ "$FOLDER" = "." ]; then
    cp src/$TARGET_NAME.$OUTPUT_FILE_EXTENSION $ROOT
fi
# --------------------------- #


# ----= Folder Project =----- #
# -----= File Project =------ #
# --------- Release --------- #
if [ "$FOLDER" != "." ]; then
    cp $TARGET_NAME.$OUTPUT_FILE_EXTENSION $ROOT
fi
# --------------------------- #

# ---= Running EXE File =---- #
cd $ROOT
if [ -f $ROOT/$TARGET_NAME.$OUTPUT_FILE_EXTENSION ]; then
    ./$TARGET_NAME.$OUTPUT_FILE_EXTENSION
    # ./$TARGET_NAME.$OUTPUT_FILE_EXTENSION --gtest_output="xml:./$TARGET_NAME.xml"
fi

# --------------------------- #
