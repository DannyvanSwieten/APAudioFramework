//
//  Buffer.h
//  GUI
//
//  Created by Danny van Swieten on 10/28/14.
//
//

#ifndef __GUI__Buffer__
#define __GUI__Buffer__

#include <vector>

template<typename T>

class Buffer
{
public:
    Buffer() = default;
    void resize(int numChannels, unsigned long numSamples)
    {
        _buffer.resize(numChannels);
        for(auto& channel: _buffer)
            channel.resize(numSamples);
    };
    
    std::vector<T> getChannel(int channel){return _buffer[channel];};
private:
    
    std::vector<std::vector<T>> _buffer;
};

#endif /* defined(__GUI__Buffer__) */
