#pragma once
#include "MiniCppUnit.hpp"
#include "RleData.h"
#include <iostream>
#include <iomanip>

// Helper functions
bool buffersAreSame(const char* expected, const char* actual, size_t size);
void runCompressionTest(char* test, size_t testSize,
	char* expected, size_t expectedSize);
void runDecompressionTest(char* test, size_t testSize,
	char* expected, size_t expectedSize);

// IMPORTANT NOTE --
// The tests all use "sizeof" to find the size of the input
// buffer. However, remember that this only works because the
// character arrays are statically allocated.
// If you just have a pointer to a C-style string, "sizeof"
// will return the size of the pointer type (either 4 or 8).
class CompressionTests : public TestFixture<CompressionTests>
{
public:
	TEST_FIXTURE_DESCRIBE(CompressionTests, "Testing Compression...")
	{
		TEST_CASE_DESCRIBE(testBasicPositiveRuns, "Basic positive runs test");
        
        TEST_CASE_DESCRIBE(testLongPositiveRun, "Long positive run test");
        TEST_CASE_DESCRIBE(testLongNegativeRun, "Long negative run test");
        
        TEST_CASE_DESCRIBE(testAlternateRun1, "Alternate run test 1");
        TEST_CASE_DESCRIBE(testAlternateRun2, "Alternate run test 2");
        TEST_CASE_DESCRIBE(testAlternateRun3, "Alternate run test 3");
        TEST_CASE_DESCRIBE(testAlternateRun4, "Alternate run test 4");
        TEST_CASE_DESCRIBE(testAlternateRun5, "Alternate run test 5");
        TEST_CASE_DESCRIBE(testAlternateRun6, "Alternate run test 6");
        
        TEST_CASE_DESCRIBE(testGreaterMaxRun1, "Greater than max run test 1");
        TEST_CASE_DESCRIBE(testGreaterMaxRun2, "Greater than max run test 2");
        TEST_CASE_DESCRIBE(testGreaterMaxRun2_1, "Greater than max run test 2_1");
        TEST_CASE_DESCRIBE(testGreaterMaxRun2_2, "Greater than max run test 2_2");
        TEST_CASE_DESCRIBE(testGreaterMaxRun2_3, "Greater than max run test 2_3");
        TEST_CASE_DESCRIBE(testGreaterMaxRun3, "Greater than max run test 3");
        TEST_CASE_DESCRIBE(testGreaterMaxRun4, "Greater than max run test 4");
        TEST_CASE_DESCRIBE(testGreaterMaxRun5, "Greater than max run test 5");
	}
	
	void testBasicPositiveRuns()
	{
		char test[] = "aaabbbcccdddaaabbbcccdddaaabbbcccdddaaabbbc"
			"ccdddaaabbbcccdddaaabbbcccdddaaabbbcccdddaaabbbcccddd";
		char expected[] = "\x03" "a" "\x03" "b" "\x03" "c" "\x03" "d"
			"\x03" "a" "\x03" "b" "\x03" "c" "\x03" "d"
			"\x03" "a" "\x03" "b" "\x03" "c" "\x03" "d"
			"\x03" "a" "\x03" "b" "\x03" "c" "\x03" "d"
			"\x03" "a" "\x03" "b" "\x03" "c" "\x03" "d"
			"\x03" "a" "\x03" "b" "\x03" "c" "\x03" "d"
			"\x03" "a" "\x03" "b" "\x03" "c" "\x03" "d"
			"\x03" "a" "\x03" "b" "\x03" "c" "\x03" "d";
		
		runCompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
	}
    
    void testLongPositiveRun()
    {
        char test[] = "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa";
        char expected[] = "\x064" "a";
        
        runCompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
    }
    
    void testLongNegativeRun()
    {
        char test[] = "abcdefghijklmnopqrstuvwxyz";
        char expected[] = "\x0E6" "abcdefghijklmnopqrstuvwxyz";
        
        runCompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
    }
    
    void testAlternateRun1()
    {
        char test[] = "aaabbcdefg";
        char expected[] = "\x03" "a" "\x02" "b" "\xFB" "cdefg";
        
        runCompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
    }
    
    void testAlternateRun2()
    {
        char test[] = "aaabbcdefgaaa";
        char expected[] = "\x03" "a" "\x02" "b" "\xFB" "cdefg" "\x03" "a";
        
        runCompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
    }
    
    void testAlternateRun3()
    {
        char test[] = "abcdeffffb";
        char expected[] = "\xFB" "abcde" "\x04" "f" "\x01" "b";
        
        runCompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
    }
    
    void testAlternateRun4()
    {
        char test[] = "abcdeffffbb";
        char expected[] = "\xFB" "abcde" "\x04" "f" "\x02" "b";
        
        runCompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
    }

    void testAlternateRun5()
    {
        char test[] = "aabaaa";
        char expected[] = "\x02" "a" "\x01" "b" "\x03" "a";
        
        runCompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
    }
    
    void testAlternateRun6()
    {
        char test[] = "abbaaa";
        char expected[] = "\x01" "a" "\x02" "b" "\x03" "a";
        
        runCompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
    }
    
    void testGreaterMaxRun1()
    {
        char test[] = "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa";
        char expected[] = "\x7F" "a" "\x49" "a";
        
        runCompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
    }
    
    void testGreaterMaxRun2()
    {
        char test[] = "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaa"
            "abcde";
        char expected[] = "\x7F" "a" "\xFB" "abcde";
        
        runCompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
    }
    
    void testGreaterMaxRun2_1()
    {
        char test[] = "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaa"
            "aabc";
        char expected[] = "\x7F" "a" "\x02" "a" "\xfe" "bc";
        
        runCompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
    }
    
    void testGreaterMaxRun2_2()
    {
        char test[] = "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaa"
            "aabaa";
        char expected[] = "\x7F" "a" "\x02" "a" "\x01" "b" "\x02" "a";
        
        runCompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
    }

    void testGreaterMaxRun2_3()
    {
        char test[] = "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaa"
            "b";
        char expected[] = "\x7F" "a" "\x01" "b";
        
        runCompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
    }
    
    void testGreaterMaxRun3()
    {
        char test[] = "abcabcabcabc"
            "abcabcabcabc"
            "abcabcabcabc"
            "abcabcabcabc"
            "abcabcabcabc"
            "abcabcabcabc"
            "abcabcabcabc"
            "abcabcabcabc"
            "abcabcabcabc"
            "abcabcabcabc"
            "abcabcaaaa";
        char expected[] = "\x81" "abcabcabcabc"
            "abcabcabcabc"
            "abcabcabcabc"
            "abcabcabcabc"
            "abcabcabcabc"
            "abcabcabcabc"
            "abcabcabcabc"
            "abcabcabcabc"
            "abcabcabcabc"
            "abcabcabcabc"
            "abcabca"
            "\x03" "a";
        
        runCompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
    }
    
    void testGreaterMaxRun4()
    {
        char test[] = "abcabcabcabc"
            "abcabcabcabc"
            "abcabcabcabc"
            "abcabcabcabc"
            "abcabcabcabc"
            "abcabcabcabc"
            "abcabcabcabc"
            "abcabcabcabc"
            "abcabcabcabc"
            "abcabcabcabc"
            "abcabcaabcde";
        char expected[] = "\x81" "abcabcabcabc"
            "abcabcabcabc"
            "abcabcabcabc"
            "abcabcabcabc"
            "abcabcabcabc"
            "abcabcabcabc"
            "abcabcabcabc"
            "abcabcabcabc"
            "abcabcabcabc"
            "abcabcabcabc"
            "abcabca"
            "\xFB" "abcde";
        
        runCompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
    }
    
    void testGreaterMaxRun5()
    {
        char test[] = "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "\x00\x00";
        char expected[] = "\x7F" "a" "\x7B" "a" "\x02" "\x00";
        
        runCompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
    }
    
    
};

class DecompressionTests : public TestFixture<DecompressionTests>
{
public:
	TEST_FIXTURE_DESCRIBE(DecompressionTests, "Testing Decompression...")
	{
		TEST_CASE_DESCRIBE(testBasicPositiveRuns, "Basic positive run test for decompression");
		
        TEST_CASE_DESCRIBE(testRun1, "Test alternate run 1");
        TEST_CASE_DESCRIBE(testRun2, "Test alternate run 2");
        TEST_CASE_DESCRIBE(testRun3, "Test max run 1");
        TEST_CASE_DESCRIBE(testRun4, "Test max run 2");
        TEST_CASE_DESCRIBE(testRun5, "Test max run 3");

	}
	
	void testBasicPositiveRuns()
	{
		char test[] = "\x28" "x";
		char expected[] = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
		
		runDecompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
	}
    
    void testRun1()
    {
        char test[] = "\x03" "a" "\x02" "b" "\xFB" "cdefg";
        char expected[] = "aaabbcdefg";
        
        runDecompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
    }
    
    void testRun2()
    {
        char test[] = "\x03" "a" "\x02" "b" "\xFB" "cdefg" "\x03" "a";
        char expected[] = "aaabbcdefgaaa";
        
        runDecompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
    }
    
    void testRun3()
    {
        char test[] = "\x7F" "a" "\x49" "a";
        char expected[] = "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa";
        
        runDecompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
    }

    void testRun4()
    {
        char test[] = "\x7F" "a" "\xFB" "abcde";
        char expected[] = "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaaaaa"
            "aaaaaaa"
            "abcde";
        
        runDecompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
    }

    void testRun5()
    {
        char test[] = "\x81" "abcabcabcabc"
            "abcabcabcabc"
            "abcabcabcabc"
            "abcabcabcabc"
            "abcabcabcabc"
            "abcabcabcabc"
            "abcabcabcabc"
            "abcabcabcabc"
            "abcabcabcabc"
            "abcabcabcabc"
            "abcabca"
            "\x03" "a";
        char expected[] = "abcabcabcabc"
            "abcabcabcabc"
            "abcabcabcabc"
            "abcabcabcabc"
            "abcabcabcabc"
            "abcabcabcabc"
            "abcabcabcabc"
            "abcabcabcabc"
            "abcabcabcabc"
            "abcabcabcabc"
            "abcabcaaaa";
        
        runDecompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
    }


};

REGISTER_FIXTURE(CompressionTests);
REGISTER_FIXTURE(DecompressionTests);

bool buffersAreSame(const char* expected, const char* actual, size_t size)
{
	if (actual == nullptr)
	{
		std::cerr << std::endl << "Actual data is null." << std::endl;
		return false;
	}

	bool retVal = true;

	for (size_t i = 0; i < size; i++)
	{
		if (expected[i] != actual[i])
		{
			retVal = false;
			std::cerr << std::endl
				<< "Expected 0x" << std::hex << static_cast<unsigned>(expected[i])
				<< " at index " << std::dec << i << " but saw 0x"
				<< std::hex << static_cast<unsigned>(actual[i]) << std::endl;
			break;
		}
	}

	return retVal;
}

void runCompressionTest(char* test, size_t testSize, 
	char* expected, size_t expectedSize)
{
	RleData r;
	r.Compress(test, testSize);
	ASSERT_TEST_MESSAGE(buffersAreSame(expected, r.mData, expectedSize),
		"Buffer mismatch (see above for details)");
}

void runDecompressionTest(char* test, size_t testSize,
	char* expected, size_t expectedSize)
{
	RleData r;
	r.Decompress(test, testSize, expectedSize);
	ASSERT_TEST_MESSAGE(buffersAreSame(expected, r.mData, expectedSize),
		"Buffer mismatch (see above for details)");
}
