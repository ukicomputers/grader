# Written by Uglješa Lukešević and other contributors
# github.com/ukicomputers/grader
# Marked as Open Source Project

# @brief Build script for building everything
# Uses sudo
# USED ONLY FOR GITHUB ACTIONS

rm -rf build_lib
mkdir build_lib
cd build_lib

cmake ../lib
make -j$(nproc --all)
sudo make install

cd ..
cd demo

mkdir build
cd build
cmake ..
make -j$(nproc --all)
./grader-testcase