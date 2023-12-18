# Written by Uglješa Lukešević and other contributors
# github.com/ukicomputers/grader
# Marked as Open Source Project

# @brief Build script for develop and installation

rm -rf build_lib
mkdir build_lib
cd build_lib
cmake ../lib
make -j$(nproc --all)
sudo make install