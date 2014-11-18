//
//  APAudioFormatReader.cpp
//  GUI
//
//  Created by Danny van Swieten on 10/28/14.
//
//

#include "APAudioInputStream.h"

APAudioInputStream::APAudioInputStream()
{
    
}

APAudioInputStream::~APAudioInputStream()
{
    fclose(file);
}

void APAudioInputStream::jumpToPosition(long long position)
{
    if(position > length)
    {
        std::cout<<"Position further than file length"<<std::endl;
        return;
    }
    
    fseek(file, position, SEEK_SET);
}

void APAudioInputStream::readBytes(char* result, int numOfBytes)
{
    fread(&result, sizeof(char), numOfBytes, file);
}

char APAudioInputStream::readByte()
{
    char result;
    fread(&result, sizeof(char), 1, file);
    return result;
}

short APAudioInputStream::readShort()
{
    short result;
    fread(&result, sizeof(short), 1, file);
    return result;
}

int APAudioInputStream::readInt16()
{
    int result;
    fread(&result, sizeof(char), 2, file);
    return result;
}

unsigned int APAudioInputStream::readUInt16()
{
    unsigned int result;
    fread(&result, sizeof(char), 2, file);
    return result;
}

int APAudioInputStream::readInt32()
{
    int result;
    fread(&result, sizeof(char), 4, file);
    return result;
}

long long APAudioInputStream::currentPosition()
{
    return ftell(file);
}

std::string APAudioInputStream::fullFile()
{
    return _fullFileString;
}

long long APAudioInputStream::size()
{
    return length;
}

std::size_t APAudioInputStream::lookForString(std::string stringToLookFor)
{
    return _fullFileString.find(stringToLookFor);
}

void APAudioInputStream::createInputStream(std::string path)
{
    file = fopen(path.c_str(), "rb");
    
    if (file)
    {
        // get length of file:
        fseek(file, 0, SEEK_END);
        length = ftell(file);
        fseek(file, 0, SEEK_SET);
        
        char* chars = new char[length];
        fread(chars, sizeof(char), length/2, file);
        _fullFileString = chars;
        delete [] chars;
    }
}