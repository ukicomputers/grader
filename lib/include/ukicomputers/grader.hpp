// Written by Uglješa Lukešević and other contributors
// github.com/ukicomputers/grader
// Marked as Open Source Project

/*
    @author Uglješa Lukešević
    @file grader.hpp
    @brief An CPP library for grading executable IO/s.
    Licensed under GNU GPL-3.0 License
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <filesystem>

// For reading vector, automatically reallocates if size is more than defined
// Not need to worry, this is just memory allocation warmup
#define PRE_ALLOCATED_SIZE 4096

#ifdef __linux__
#define COMPILER "g++"
#define ARGUMENTS "-o {outname} {filename}"
#else
#define COMPILER "ndef"
#define ARGUMENTS "ndef"
#endif

using namespace std;

class configGrader
{
public:
    // TLE & MLE test still not published
    // int8_t timeLimit = 0;      // For TLE, defined in MS, 0 for the none
    // int64_t memoryLimit = 0;   // For MLE, defined in KB, 0 for the none

    filesystem::path io;          // Test Pending Folder
    string compiler = COMPILER;   // Execution command for COMPILER
    string arguments = ARGUMENTS; // COMPILER executor, use {filename} for input CPP, use {outfile} for compile out
                                  // If {outfile} not defined, executable name will be same as code name
                                  // If on Linux, arguments will be automatically chosen for g++ :)
};

class grader
{
public:
    enum TEST_RESULT
    {
        COMPILE_ERROR = 4,
        TEST_FAILED = 1,
        MEMORY_LIMIT_EXCEEDED = 2,
        TIME_LIMIT_EXCEEDED = 3,
        TEST_PASSED = 0,
        NAN = 5
    };

    grader(string __code, configGrader __config); // grader element
    vector<TEST_RESULT> runTest();                // Returns only element [0] with TEST_RESULT's COMPILE_ERROR, and breaks testing
    TEST_RESULT compile();                        // Used as private function, but you can use it if you want to recompile code

private:
    string code;
    configGrader config;

    enum RE_TYPE
    {
        COMPILER_NOT_FOUND = 4,
        CODE_NOT_FOUND = 1,
        USUAL_FAIL = 0,
        IO_TESTS_NOT_FOUND = 2,
        IO_TESTS_FAILED_CONFIGURATION = 3
    };

    RE_TYPE throwRE(RE_TYPE re);
};
