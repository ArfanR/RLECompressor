#include "RLEFile.h"
#include "RleData.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include "FileSystem.h"

void RleFile::CreateArchive(const std::string& source)
{
    // Requires <fstream>
    std::ifstream::pos_type size;
    char* memblock;
    
    // Open the file for input, in binary mode, and start ATE (at the end)
    std::ifstream file (source, std::ios::in|std::ios::binary|std::ios::ate);
    
    if (file.is_open())
    {
        size = file.tellg(); // Save the size of the file
        memblock = new char [static_cast<unsigned int>(size)];
        file.seekg (0, std::ios::beg); // Seek back to start of file
        file.read (memblock, size);
        file.close();
        // File data has now been loaded into memblock array
    
        // Compress the data
        mData.Compress(memblock, static_cast<unsigned int>(size));
        
        // Make sure to clean up!
        delete[] memblock;
    }
    
    // Status message of percentage compressed
    double compressed = 100 * (static_cast<double>(size) - mData.mSize) / (static_cast<double>(size));
    std::cout << "File compressed was down to " << compressed << "%." << std::endl;
        
    // Output filename
    std::string filename = source + ".rl1";
        
    // Store header information
    char file_sig[] = "R" "L" "E" "\x01";
    strcpy(mHeader.sig, file_sig);
    mHeader.fileSize = static_cast<int>(size);
    mHeader.fileNameLength = static_cast<unsigned char>(source.length());
    mHeader.fileName = source;
        
    // Open the file for output, in binary mode, and overwrite an existing file
    std::ofstream arc(filename, std::ios::out|std::ios::binary|std::ios::trunc);
    if (arc.is_open())
    {
        arc.write(mHeader.sig, 4);
        arc.write(reinterpret_cast<char*>(&(mHeader.fileSize)), 4);
        arc.write(reinterpret_cast<char*>(&(mHeader.fileNameLength)), 1);
        arc.write(mHeader.fileName.c_str(), mHeader.fileNameLength);
        arc.write(mData.mData, mData.mSize);
    }
        
}

void RleFile::ExtractArchive(const std::string& source)
{
    // Requires <fstream>
    std::ifstream::pos_type size;
    char* memblock;
    
    // Open the file for input, in binary mode, and start ATE (at the end)
    std::ifstream file (source, std::ios::in|std::ios::binary|std::ios::ate);
   
    if (file.is_open())
    {
        size = file.tellg(); // Save the size of the file
        memblock = new char [static_cast<unsigned int>(size)];
        file.seekg (0, std::ios::beg); // Seek back to start of file
        file.read (memblock, size);
        file.close();
        // File data has now been loaded into memblock array
        
        // Fill in file signature
        for (int i = 0; i < 4; i++)
        {
            mHeader.sig[i] = memblock[i];
        }
        
        // Signature check
        if (!std::strcmp(mHeader.sig, "RLE1"))
        {
            std::cout << "File has invalid signature" << std::endl;
            exit(1);
        }
        // Decompress file
        else
        {
            mHeader.fileSize = *(reinterpret_cast<int*>(&memblock[4]));
            mHeader.fileNameLength = *(reinterpret_cast<int*>(&memblock[8]));
            
            for(int i = 0; i < static_cast<unsigned int>(mHeader.fileNameLength); i++)
            {
                mHeader.fileName += memblock[i+9];
            }
            
            // File data has now been loaded into memblock array
            mData.Decompress(memblock + 9 + mHeader.fileNameLength, static_cast<unsigned int>(size) - 9 - mHeader.fileNameLength, mHeader.fileSize);
        }
        
        // Make sure to clean up!
        delete[] memblock;
    }
    
    std::ofstream arc(mHeader.fileName, std::ios::out | std::ios::binary | std::ios::trunc);
    if (arc.is_open())
    {
        arc.write(mData.mData, mData.mSize);
    }

    std::cout << "File was fully decompressed." << std::endl;
        
        
}
