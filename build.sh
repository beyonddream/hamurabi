#!/bin/bash

set -e

BUILD_DIR=build

function build_hamurabi() {

        if [ ! -d "${BUILD_DIR}" ]; then
            echo "Making build dir"
            mkdir -p ${BUILD_DIR}

        fi

        echo "Changing to build dir"
        pushd ${BUILD_DIR}

        if [ ! -f "Makefile" ]; then
            echo "Configuring app"
            cmake $@ ..
        fi


        PROCESSORS=`sysctl -n hw.ncpu`
        make --no-print-directory -j$(($PROCESSORS * 2))

        popd
}

# run
if [ "$1" = "r" ]
then
    if [ ! -f "${BUILD_DIR}/hamurabi" ]; then
        build_hamurabi "$@"
    fi
    pushd ${BUILD_DIR}
    ./hamurabi
    popd
elif [ "$1" = "t" ]
then
    pushd ${BUILD_DIR}
    ctest -j8
    popd
else
    build_hamurabi "$@"
fi
