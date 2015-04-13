//
//  AudioSourceDescription.cpp
//  SmartSampler
//
//  Created by Danny van Swieten on 1/8/15.
//
//

#include "AudioSourceDescription.h"

AudioSourceDescription::AudioSourceDescription()
{
    
}

AudioSourceDescription::~AudioSourceDescription()
{
    
}

AudioSourceDescription::AudioSourceDescription(std::string type, std::string info, int note, int velocity, int channel)
{
    this->note = note;
    this->velocity = velocity;
    this->channel = channel;
    
    ID = type;
    this->info = info;
}

bool AudioSourceDescription::check(int note, int velocity, int channel)
{
    int sum = listensToVelocity(velocity) + listensToNote(note) + listensToChannel(channel);
    if(sum == 3)
        return true;
    else
        return false;
}

bool AudioSourceDescription::listensToChannel(int channel)
{
    if(this->channel.getValue() == channel)return true;
    else return false;
}

bool AudioSourceDescription::listensToNote(int note)
{
    if(note >= this->note.getMinValue() && note <= this->note.getMaxValue())return true;
    else return false;
}

bool AudioSourceDescription::listensToVelocity(int velocity)
{
    if(velocity >= this->velocity.getMinValue() && velocity < this->velocity.getMaxValue())return true;
    else return false;
}