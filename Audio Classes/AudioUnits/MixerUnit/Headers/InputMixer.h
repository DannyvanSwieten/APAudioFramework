//
//  InputMixer.h
//  VSTHost
//
//  Created by Danny van Swieten on 1/31/15.
//  Copyright (c) 2015 Danny van Swieten. All rights reserved.
//

#ifndef __VSTHost__InputMixer__
#define __VSTHost__InputMixer__

#include <vector>
#include "Channel.h"
#include "OutputChannel.h"
#include <mutex>

class InputMixer
{
public:
    
    InputMixer();
    void feedInput(float** input, unsigned int numChannels, unsigned int numFrames);
    void addChannel(std::unique_ptr<Channel> channel);
    void disConnect(Channel* c);
    std::vector<std::unique_ptr<Channel>>& getChannels(){return channels;};
    AudioUnit* getOutputChannel(){return outputChannel.get();};
private:
    
    std::unique_ptr<OutputChannel> outputChannel;
    std::vector<std::unique_ptr<Channel>> channels;
};

#endif /* defined(__VSTHost__InputMixer__) */
