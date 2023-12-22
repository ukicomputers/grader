# Written by Uglješa Lukešević and other contributors
# github.com/ukicomputers/grader
# Marked as Open Source Project

# @brief Build script for building everything
# Uses sudo
# USED ONLY FOR GITHUB ACTIONS

cd lib
rm -rf build
mkdir build
cd build

cmake ..
make -j$(nproc --all)
sudo make install

cd ..
cd ..
cd demo

rm -rf build
mkdir build
cd build

cmake ..
make -j$(nproc --all)
./grader-testcase