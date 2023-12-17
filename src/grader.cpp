// Written by Uglješa Lukešević and other contributors
// github.com/ukicomputers/grader
// Marked as Open Source Project

/*
    @author Uglješa Lukešević
    @file grader.cpp
    @brief An CPP library for grading CPP codes.
    Licensed under GNU GPL-3.0 License
*/

#include <grader.hpp>

grader::grader(string __code, configGrader __config)
{
    if(__config.compilation == "ndef") {
        throwRE(COMPILER_NOT_FOUND);
    }
}

grader::RE_TYPE grader::throwRE(RE_TYPE re)
{
    if(re == COMPILER_NOT_FOUND) {
        cerr << "Declared C++ (or C) compiler not found." << endl << endl;
        throw runtime_error("COMPILER_NOT_FOUND");
    } else if(re == CODE_NOT_FOUND) {
        cerr << "Declared C++ (or C) compilation code not found or acces is denied." << endl << endl;
        throw runtime_error("CODE_NOT_FOUND");
    } else if(re == USUAL_FAIL) {
        throw runtime_error("USUAL_FAIL");
    }

    return re;
}