@echo off
mkdir temp
cd temp
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -G"Ninja" ..
copy compile_commands.json ..
cd ..
rmdir /s /q temp
