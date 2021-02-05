#!/usr/bin/env bash

OUT_DIR=build
BUILD_TYPE=Release

mkdir -p $OUT_DIR 
if [ "$1" == "clean" ]; then
    echo Cleaning build...
    cd $OUT_DIR && rm -rf *
    exit
elif [ "$1" == "debug" ]; then
    echo debug build...
    BUILD_TYPE=Debug

else
    echo normal build...
fi

cd $OUT_DIR
cmake -G "Ninja" -DCMAKE_BUILD_TYPE=${BUILD_TYPE} ..
ninja -j $(nproc)

