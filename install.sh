# Written by Uglješa Lukešević and other contributors
# github.com/ukicomputers/grader
# Marked as Open Source Project

# @brief Build script for develop and installation
# Install ONLY FOR Linux (also supports Windows distribution, but not with this script)

cd lib
rm -rf build
mkdir build
cd build
cmake ..
make -j$(nproc --all)
sudo make install