//
//  WaveFormatReader.cpp
//  GUI
//
//  Created by Danny van Swieten on 10/28/14.
//
//

#include "WaveFormatReader.h"

namespace APAudio
{
    namespace Audio
    {

        WaveFormatReader::WaveFormatReader()
        {
            
        }

        AudioFile WaveFormatReader::read(std::string path, bool useLeft, bool useRight)
        {
            
            _inputStream.createInputStream(path);
            
            AudioFile file;
            auto position = path.find_last_of("/");
            std::string fileName = path.substr(position+1, path.length()-position);
            file.setFileName(fileName);
            
            char chunkID[4];
            chunkID[4] = '\0';
            char format[4];
            format[4] = '\0';
            char subChunkID[4];
            subChunkID[4] = '\0';
            char subChunkID2[4];
            subChunkID2[4] = '\0';
            
            _inputStream.readChars(chunkID, 4);
            std::cout<<(chunkID)<<std::endl;
            
            auto chunkSize = _inputStream.readFundamentalType<uint32_t>();
            
            _inputStream.readChars(format, 4);
            std::cout<<(format)<<std::endl;
            
            _inputStream.readChars(subChunkID, 4);
            std::cout<<(subChunkID)<<std::endl;
            
            auto formatLength = _inputStream.readFundamentalType<uint32_t>();
            
            auto formatTag = _inputStream.readFundamentalType<short>();
            
            auto channels = _inputStream.readFundamentalType<short>();
            
            file.setNumChannels(channels);
            
            auto sampleRate = _inputStream.readFundamentalType<uint32_t>();
            
            file.setSamplerate(sampleRate);
            
            auto byteRate = _inputStream.readFundamentalType<uint32_t>();
            
            auto blockAlignment = _inputStream.readFundamentalType<short>();
            
            auto bitRate = _inputStream.readFundamentalType<short>();
            
            _inputStream.readChars(subChunkID2, 4);
            
            auto dataSize = _inputStream.readFundamentalType<uint32_t>();
            
            file.setNumSamples(dataSize);
            
            if(useLeft)
            {
                std::vector<float> dataLeft;
                for(auto sample = 0; sample < dataSize / channels; sample += channels)
                {
                    dataLeft.emplace_back((float)_inputStream.readFundamentalType<int16_t>() / INT16_MAX);
                }
                _data.getBuffer().emplace_back(std::move(dataLeft));
            }
            if(useRight && channels == 2)
            {
                std::vector<float> dataRight;
                
                for(auto sample = 0; sample < dataSize / channels; sample += channels)
                {
                    dataRight.emplace_back((float)_inputStream.readFundamentalType<int16_t>() / INT16_MAX);
                }
                _data.getBuffer().emplace_back(std::move(dataRight));
            }
            
            file.setAudio(_data);
            
            return std::move(file);
        }
    }
}