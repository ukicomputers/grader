// Written by Uglješa Lukešević and other contributors
// github.com/ukicomputers/grader
// Marked as Open Source Project

/*
    @author Uglješa Lukešević
    @file grader.cpp
    @brief An CPP library for grading executable IO/s.
    Licensed under GNU GPL-3.0 License
*/

#include "ukicomputers/grader.hpp"

grader::grader(string __code, configGrader __config)
{
    if (__config.compiler == "ndef")
    {
        throwRE(COMPILER_NOT_FOUND);
        return;
    }

    // Currently adjusted for G++, only test does compiler works
    // NEEDS CONFIGURATION FOR OTHER COMPILERS
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
    else if (re == IO_TESTS_NOT_FOUND)
    {
        cerr << "Declared directory for IO tests does not have tests, or does not have .in or .out with same filename." << endl
             << endl;
        throw runtime_error("IO_TESTS_NOT_FOUND");
    }

    return re;
}

grader::TEST_RESULT grader::compile()
{
    filesystem::path exCommand = code;
    string command = config.compiler + " " + config.arguments;

    size_t arg = command.find("{filename}");

    if (arg != string::npos)
    {
        command.replace(arg, 10, code);
    }

    code = exCommand.stem().string();
    arg = command.find("{outname}");

    if (arg != string::npos)
    {
#ifdef __linux__
        command.replace(arg, 9, code);
#elif _WIN32
        command.replace(arg, 9, code + ".exe");
#endif
    }

    int compile_result = system(command.c_str());

    if (compile_result == -1)
    {
        return COMPILE_ERROR;
    }
}

vector<grader::TEST_RESULT> grader::runTest()
{
    vector<TEST_RESULT> tests;

    if (compile() == COMPILE_ERROR)
    {
        return {COMPILE_ERROR};
    }

    for (const auto &file : filesystem::directory_iterator(config.io))
    {
        if (file.is_regular_file())
        {
            filesystem::path fileName = file.path().stem();
            filesystem::path requiredFilePath = fileName;
            requiredFilePath += ".in";

            // Imagine that in and out with same name exists
            if (filesystem::exists(requiredFilePath))
            {
                // Prepare IO tests
                string inputFilePath = fileName;
                inputFilePath += ".in";

                filesystem::path outFilePath = fileName;
                outFilePath += ".out";

                if (!filesystem::exists(outFilePath))
                {
                    throwRE(IO_TESTS_NOT_FOUND);
                }

// Execute the program
#ifdef __linux__
                string executeProgram = "./" + code + " < " + inputFilePath;
#elif _WIN32
                string executeProgram = "./" + code + ".exe" + " < " + inputFilePath;
#endif

                FILE *program = popen(executeProgram.c_str(), "r");
                if (!program)
                {
                    tests.push_back(TEST_FAILED);
                    continue;
                }

                ostringstream outStream;
                vector<char> buffer(PRE_ALLOCATED_SIZE);

                while (fgets(buffer.data(), static_cast<int>(buffer.size()), program) != nullptr)
                {
                    outStream << buffer.data();
                }

                fclose(program);
                auto OUTPUT = outStream.str();

                ifstream eOutStream(outFilePath);
                ostringstream eOutBuffer;
                eOutBuffer << eOutStream.rdbuf();

                if (OUTPUT == eOutBuffer.str())
                {
                    tests.push_back(TEST_PASSED);
                }
                else
                {
                    tests.push_back(TEST_FAILED);
                }
            }
            else
            {
                throwRE(IO_TESTS_NOT_FOUND);
            }
        }

        return tests;
    }
}