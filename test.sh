#!/bin/sh

# Limit tests to the debug flavor
FLAVOR=debug

BUILD_DIR=build/$FLAVOR

ninja_test_all() {
    for dir in $BUILD_DIR/*/ ; do
        ninja test -C $dir
    done
}

setup_and_ninja_and_test() {
    ./bld.sh $FLAVOR
    ninja_test_all
}

[ -d $BUILD_DIR ] && ninja_test_all || setup_and_ninja_and_test
