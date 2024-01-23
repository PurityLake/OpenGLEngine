#!/usr/bin/env bash

mkdir -p build
cmake -S. -B ./build -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build ./build
