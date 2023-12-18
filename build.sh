# Written by Uglješa Lukešević and other contributors
# github.com/ukicomputers/grader
# Marked as Open Source Project

# @brief Build script for develop and installation

rm -rf build
mkdir build
cd build
cmake ..
make -j$(nproc --all)
#sudo make install