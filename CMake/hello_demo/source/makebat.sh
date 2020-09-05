#!/bin/sh 

ROOT_DIR=./..

echo $1 == 'clean'

if [ "$1" = "clean" ]; then
    if [ -e ${ROOT_DIR}/build ]; then
        rm -rf ${ROOT_DIR}/build
    fi
    exit 0
fi


if [ -e ${ROOT_DIR}/build ]; then
    rm -rf ${ROOT_DIR}/build
fi

sleep 3

echo "mkdir build"
mkdir ${ROOT_DIR}/build

cd ${ROOT_DIR}/build
cmake ${ROOT_DIR}/source
#cmake --build .

echo "make"
make -C ${ROOT_DIR}/build
