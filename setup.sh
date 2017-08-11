#!/bin/sh
FLAVOR=debug

opt=$1
case $opt in
  release) FLAVOR=release
esac

SRC_DIR=src
MESON_BLD_DIR=build/$FLAVOR

for dir in $SRC_DIR/*/ ; do
    dir=${dir#$SRC_DIR/}
    meson --buildtype $FLAVOR $MESON_BLD_DIR/$dir $SRC_DIR/$dir
done
