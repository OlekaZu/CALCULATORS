#!/bin/bash

$BUILD_DIR_NAME="BuildProject"

cmake MyCalculator/CMakeLists.txt -B $BUILD_DIR_NAME
cmake --build $BUILD_DIR_NAME
open ./$BUILD_DIR_NAME/MyCalculator.app