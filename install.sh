#!/bin/sh

# Limit install to release flavor.
FLAVOR=release

BUILD_DIR=build/$FLAVOR

install_project() {
    for dir in $BUILD_DIR/*/ ; do
        pushd $dir
        ninja install
        popd
    done
}

setup_and_ninja_and_install() {
    ./bld.sh $FLAVOR
    install_project
}

[ -d $BUILD_DIR ] && install_project || setup_and_ninja_and_install
