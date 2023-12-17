// Written by Uglješa Lukešević and other contributors
// github.com/ukicomputers/grader
// Marked as Open Source Project

/*
    @author Uglješa Lukešević
    @file grader.hpp
    @brief An CPP library for grading CPP codes.
    Licensed under GNU GPL-3.0 License
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <filesystem>

#ifdef __linux__
#define COMPILER "g++"
#define ARGUMENTS "{filename} -O {outname}"
#else
#define COMPILER "ndef"
#define ARGUMENTS "ndef"
#endif

using namespace std;

class configGrader
{
public:
    int8_t timeLimit = 0;         // For TLE, defined in MS, 0 for the none
    int64_t memoryLimit = 0;      // For MLE, defined in KB, 0 for the none
    string io;                    // Test Pending Folder
    string compiler = COMPILER;   // Execution command for COMPILER
    string arguments = ARGUMENTS; // COMPILER executor, use {filename} for input CPP, use {outfile} for compile out
};

class grader
{
public:
    enum TEST_RESULT
    {
        COMPILE_ERROR,
        TEST_FAILED,
        MEMORY_LIMIT_EXCEEDED,
        TIME_LIMIT_EXCEEDED,
        TEST_PASSED
    };

    grader(string __code, configGrader __config);
    vector<TEST_RESULT> runTest();
    TEST_RESULT compile();

private:
    string code;
    configGrader config;

    enum RE_TYPE
    {
        COMPILER_NOT_FOUND,
        CODE_NOT_FOUND,
        USUAL_FAIL,
        IO_TESTS_NOT_FOUND
    };

    RE_TYPE throwRE(RE_TYPE re);
};