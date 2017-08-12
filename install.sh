#!/bin/sh

# Limit install to release flavor.
FLAVOR=release

BUILD_DIR=build/$FLAVOR

PROJECT_NAME=adder

install_project() {
    cd $BUILD_DIR/$PROJECT_NAME
    ninja install
}

setup_and_ninja_and_install() {
    ./bld.sh $FLAVOR
    install_project
}

[ -d $BUILD_DIR ] && install_project || setup_and_ninja_and_install
