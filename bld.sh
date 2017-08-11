#!/bin/sh
FLAVOR=debug

opt=$1
case $opt in
  release) FLAVOR=release
esac

BUILD_DIR=build/$FLAVOR

ninja_all() {
    for dir in $BUILD_DIR/*/ ; do
        ninja -C $dir
    done
}

setup_and_ninja() {
    ./setup.sh $FLAVOR
    ninja_all
}

[ -d $BUILD_DIR ] && ninja_all || setup_and_ninja
