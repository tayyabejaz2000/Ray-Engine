#!/bin/bash
cd ../..
case "$1" in
    "build") vendor/premake/bin/premake5 gmake2 ${@:2};;
    *) vendor/premake/bin/premake5 ${@:1};;
esac