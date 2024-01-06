#!/usr/bin/env bash

mkdir -p temp
cd temp
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -G"Ninja" ..
cp compile_commands.json ..
cd ..
rm -rf temp
