#!/bin/bash
case "$1" in
    "build") vendor/premake/bin/Linux/premake5 gmake2 ${@:2};;
    *) vendor/premake/bin/Linux/premake5 ${@:1};;
esac