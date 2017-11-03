@echo off
mkdir build
cd build
cmake -G "MinGW Makefiles" -DUSE_GLFW ..
mingw32-make
cd ..