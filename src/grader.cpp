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
    if (__config.compiler == "ndef")
    {
        throwRE(COMPILER_NOT_FOUND);
        return;
    }

    // Currently adjusted for G++, NEEDS MORE VERSION CLARIFICATION TEST
    string test = __config.compiler + " --version";

    if (system(test.c_str()) == -1)
    {
        throwRE(COMPILER_NOT_FOUND);
        return;
    }

    if (!filesystem::exists(__code))
    {
        throwRE(CODE_NOT_FOUND);
        return;
    }

    code = __code;
    config = __config;
}

grader::RE_TYPE grader::throwRE(RE_TYPE re)
{
    if (re == COMPILER_NOT_FOUND)
    {
        cerr << "Declared C++ (or C) compiler not found." << endl
             << endl;
        throw runtime_error("COMPILER_NOT_FOUND");
    }
    else if (re == CODE_NOT_FOUND)
    {
        cerr << "Declared C++ (or C) compilation code not found or acces is denied." << endl
             << endl;
        throw runtime_error("CODE_NOT_FOUND");
    }
    else if (re == USUAL_FAIL)
    {
        throw runtime_error("USUAL_FAIL");
    }

    return re;
}

grader::TEST_RESULT grader::compile()
{
    string command = config.compiler + " " + config.arguments;

    size_t arg = command.find("{filename}");

    if (arg != string::npos)
    {
        command.replace(arg, 10, code);
    }

    arg = command.find("{outfile}");

    if (arg != string::npos)
    {
        command.replace(arg, 9, code);
    }

    int compile_result = system(command.c_str());

    if (compile_result == -1)
    {
        return COMPILE_ERROR;
    }
}