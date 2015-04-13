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

class InputStream
{
public:
    InputStream();
    ~InputStream();
    
    void createInputStream(std::string path);
    void jumpToPosition(long long position);

    std::string fullFile();
    
    void readChars(char*, int numChars);
    
    std::string getLine();
    
    template <typename T>
    inline T readFundamentalType()
    {
        char buffer[sizeof(T)];
        
        _inputStream->read(buffer, sizeof(T));
        
        return *reinterpret_cast<T*>(buffer);
    }
    
    std::istream* returnStream(){return _inputStream;};
    std::size_t lookForString(std::string stringToLookFor);
    
private:
    
    std::string _fullFileString;
    std::filebuf _fileBuffer;
    std::istream* _inputStream;
    long long length = 0;
};

#endif /* defined(__GUI__APAudioFormatReader__) */
