//
//  APAudioFormatReader.h
//  GUI
//
//  Created by Danny van Swieten on 10/28/14.
//
//

#ifndef __GUI__APAudioFormatReader__
#define __GUI__APAudioFormatReader__

#include <string>
#include <fstream>
#include <iostream>
#include <memory>
#include <cstdio>

class APAudioInputStream
{
public:
    APAudioInputStream();
    ~APAudioInputStream();
    
    void createInputStream(std::string path);
    void jumpToPosition(long long position);
    
    long long currentPosition();
    long long size();
    std::string fullFile();
    
    void readBytes(char* result, int numOfBytes);
    char readByte();
    short readShort();
    int readInt16();
    short readUInt16();
    int readInt32();
    
    std::size_t lookForString(std::string stringToLookFor);
    
private:
    
    std::string _fullFileString;
    FILE* file = NULL;
    long long length = 0;
};

#endif /* defined(__GUI__APAudioFormatReader__) */
