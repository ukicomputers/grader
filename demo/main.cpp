// Written by Uglješa Lukešević and other contributors
// github.com/ukicomputers/grader
// Marked as Open Source Project

/*
    @author Uglješa Lukešević
    @file main.cpp
    @brief An CPP testcase.
    Licensed under GNU GPL-3.0 License
*/

#include <ukicomputers/grader.hpp>
#include <iostream>

using namespace std;

int main()
{
    // Make the configuration
    configGrader config;
    config.io = "../io";

    grader grader("../test.cpp", config);
    auto out = grader.runTest();

    if (out[0] == grader::COMPILE_ERROR)
    {
        cerr << "COMPILE_ERROR" << endl;
        return (-1);
    }

    int i = 0;
    for (auto it : out)
    {
        if (it == grader::TEST_PASSED)
        {
            cout << "Test " << i << " passed!";
        }
        else
        {
            cout << "Test " << i << " failed!";
        }
    }

    return 0;
}