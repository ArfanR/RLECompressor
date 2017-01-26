#include "RleData.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

void RleData::Compress(const char* input, size_t inSize)
{
    // reset members
    delete[] mData;
    mSize = 0;
    
    // dynamically allocate array
    mData = new char[2 * inSize];
    
    int count_repeats = 1; // positive run counts
    int count_uniques = 1; // negative run counts
    size_t max = MaxRunSize()-1; // max count
    
    for (size_t i = 0; i < inSize-1; i++)
    {
        // two equal values
        if (*(input+i) == *(input+i+1))
        {
            count_repeats++;
            i++;
            // count length of positive run
            for(size_t j = i; j < inSize-1; j++)
            {
                if (*(input+j) != *(input+j+1) || ((j % max) == 0))
                {
                    break;
                }
                count_repeats++;
            }
        
            // fill in mData with the positive run count/characters
            if (count_repeats >= 1)
            {
                mData[mSize] = count_repeats;
                mData[mSize+1] = *(input+i);
                mSize += 2;
            }
            
            // update counter
            i += (count_repeats-2);
            count_repeats = 1;
            
            // case of middle single value
            if (*(input+i+1) != *(input+i+2) && *(input+i+2) == *(input+i+3))
            {
                mData[mSize] = 1;
                mData[mSize+1] = *(input+i+1);
                mSize += 2;
                i++;
            }
                
            // case of last single value
            if (i == inSize-2)
            {
                mData[mSize] = 1;
                mData[mSize+1] = *(input+i+1);
                mSize += 2;
            }
        }
        
        // two unequal values
        else if (*(input+i) != *(input+i+1))
        {
            if (i == 0 && *(input+i+1) == *(input+i+2))
            {
                mData[mSize] = 1;
                mData[mSize+1] = *(input+i);
                mSize += 2;
            }
            else
            {
                size_t start = i;
                count_uniques++;
                i++;
                
                // count length of negative run
                for(; i < inSize-1; i++)
                {
                    if (*(input+i) == *(input+i+1))
                    {
                        count_uniques -= 1;
                        i--;
                        break;
                    }
                    
                    count_uniques++;
                    
                    // exceed max count
                    if (count_uniques % 127 == 0) {
                        i++;
                        break;
                    }
                    
                }
                
                if (count_uniques > 1)
                {
                    // fill in mData with negative run count
                    mData[mSize] = count_uniques*-1;
                    mSize++;
                    // fill in mData with characters
                    for (; start <= i; start++)
                    {
                        mData[mSize] = input[start];
                        mSize++;
                    }
                }
                
                // update counter
                count_uniques = 1;
                
                // case of last single value
                if (i == inSize-2)
                {
                    mData[mSize] = 1;
                    mData[mSize+1] = *(input+i+1);
                    mSize += 2;
                }
            }
        }
        
    }
}

void RleData::Decompress(const char* input, size_t inSize, size_t outSize)
{
    // reset members
    delete[] mData;
    mSize = 0;
    
    // allocate memory
    mData = new char[outSize];
    
    for (size_t i = 0; i < inSize; i++)
    {
        int count = static_cast<int>(*(input+i)); // cast run count to int
        // positive count
        if (count > 0)
        {
            for (int j = 0; j < count; j++)
            {
                mData[mSize] = *(input+i+1);
                mSize++;
            }
            i++;
        }
        // negative count
        else
        {
            count *= -1; // normalize count
            for (int j = 0; j < count; j++)
            {
                mData[mSize] = *(input+i+j+1);
                mSize++;
            }
            i += count;
        }
        
    }
}

std::ostream& operator<< (std::ostream& stream, const RleData& rhs)
{
	for (int i = 0; i < rhs.mSize; i++)
	{
		stream << rhs.mData[i];
	}
	return stream;
}
