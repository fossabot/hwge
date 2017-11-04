@echo off
mkdir build
cd build
cmake -G "MinGW Makefiles" -DUSE_GLFW=ON -DUSE_SDL=OFF ..
mingw32-make
cd ..