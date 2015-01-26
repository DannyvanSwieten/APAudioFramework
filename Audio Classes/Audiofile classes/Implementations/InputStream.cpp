//
//  FormatReader.cpp
//  GUI
//
//  Created by Danny van Swieten on 10/28/14.
//
//

#include "InputStream.h"

namespace APAudio
{

    InputStream::InputStream()
    {
        
    }
    
    InputStream::~InputStream()
    {
        if(_inputStream)
            delete _inputStream;
    }

    std::string InputStream::fullFile()
    {
        return _fullFileString;
    }
    
    void InputStream::readChars(char* character, int numChars)
    {
        _inputStream->read(character, numChars);
    }

    std::size_t InputStream::lookForString(std::string stringToLookFor)
    {
        return _fullFileString.find(stringToLookFor);
    }

    void InputStream::createInputStream(std::string path)
    {
        if (_fileBuffer.open (path, std::ios::in))
            _inputStream = new std::istream(&_fileBuffer);
    }
    
    std::string InputStream::getLine()
    {
        char buffer[256];
        if(_inputStream->getline(buffer, 256))
        {
            return std::string(buffer);
        }
        
        return std::string("-1");
    }
}