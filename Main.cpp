// Main.cpp : Defines the entry point for the console application.
//

#include "RleTests.h"
#include "RleData.h"
#include <cstring>
#include <iostream>
#include <string>
#include <sstream>
#include "RLEFile.h"

void Part1Tests()
{
	TestFixtureFactory::theInstance().runTests();
}

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		// Just the tests
		Part1Tests();
	}
	else
	{
        std::string fileTest = argv[1];
        
        RleFile test;
        
        if(fileTest.substr(fileTest.length() - 3, fileTest.length()) == "rl1")
        {
            test.ExtractArchive(fileTest);
        }
        else
        {
            test.CreateArchive(fileTest);
        }
        
    }
    
    return 0;
}

