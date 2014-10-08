//
//  APSoundDescription.cpp
//  FuChair
//
//  Created by Danny van Swieten on 10/7/14.
//
//

#include "APSoundDescription.h"

APSoundDescription::APSoundDescription()
{
    
}

std::string APSoundDescription::getID()
{
    return _ID;
}

void APSoundDescription::setID(std::string ID)
{
    _ID = ID;
}

void APSoundDescription::setChannelToListenTo(int channel)
{
    _channelToListenTo = channel;
}

void APSoundDescription::setNoteToListenTo(int note)
{
    _noteToListenTo = note;
}

bool APSoundDescription::listensToChannel(int channel)
{
    if(channel == _channelToListenTo)
        return true;
    else
        return false;
}

bool APSoundDescription::listensToNote(int note)
{
    if(note == _noteToListenTo)
        return true;
    else
        return false;
}