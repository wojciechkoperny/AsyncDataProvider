#!/bin/bash

export CURRENT_DIR="$PWD"
export TOOLS_DIR=$CURRENT_DIR/tools
export CMAKE_ROOT=$TOOLS_DIR/cmake
export NINJA_ROOT=$TOOLS_DIR/ninja
export OUT_DIR=$CURRENT_DIR/build
export PATH=$PATH:$NINJA_ROOT
OPTION=""

mkdir -p $OUT_DIR 
if [ "$1" == "clean" ]; then
    echo Cleaning build...
    cd $OUT_DIR && rm -rf *
    exit
elif [ "$1" == "debug" ]; then
    echo debug build...
    OPTION="-DTESTBUILD=ON"

else
    echo normal build...
    OPTION="-DTESTBUILD=OFF"
fi

cd $OUT_DIR
$CMAKE_ROOT/bin/cmake -G "Ninja" $OPTION ..
$NINJA_ROOT/ninja -j 4

