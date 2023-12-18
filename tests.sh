# Written by Uglješa Lukešević and other contributors
# github.com/ukicomputers/grader
# Marked as Open Source Project

# @brief Build script for building everything
# Uses sudo
# Used currently for github actions

rm -rf build_lib
# rm -rf build_demo

mkdir build_lib
# mkdir build_demo

cd build_lib

cmake ../lib
make -j$(nproc --all)
sudo make install

# cd ..
# cd build_demo

# cmake ../demo
# make -j$(nproc --all)

cd ..
cd demo
g++ -o main main.cpp