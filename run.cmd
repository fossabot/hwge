@echo off
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
mingw32-make
cd ..
cd testproject
..\bin\testproject.exe
cd ..