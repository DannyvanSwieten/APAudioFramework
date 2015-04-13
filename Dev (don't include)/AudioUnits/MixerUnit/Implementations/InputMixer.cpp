//
//  InputMixer.cpp
//  VSTHost
//
//  Created by Danny van Swieten on 1/31/15.
//  Copyright (c) 2015 Danny van Swieten. All rights reserved.
//

#include "InputMixer.h"

InputMixer::InputMixer()
{
    outputChannel = std::make_unique<OutputChannel>(1, 2);
}

void InputMixer::feedInput(float **input, unsigned int numChannels, unsigned int numFrames)
{
    for(auto& channel: channels)
        channel->feedInput(input, numChannels, numFrames);
    
}

void InputMixer::addChannel(std::unique_ptr<Channel> channel)
{
    outputChannel->connect(channel.get());
    channels.emplace_back(std::move(channel));
}

void InputMixer::disConnect(Channel* c)
{
//    auto it = channels.begin();
//    for(auto& channel: channels)
//    {
//        if(channel.get() == c)
//        {
//            outputChannel->disconnect(channel.get());
//            channels.erase(it);
//        }
//        
//        it++;
//    }
}