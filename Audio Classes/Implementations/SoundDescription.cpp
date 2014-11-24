//
//  SoundDescription.cpp
//  FuChair
//
//  Created by Danny van Swieten on 10/7/14.
//
//

#include "SoundDescription.h"
namespace APAudio
{
    namespace Audio
    {

        SoundDescription::SoundDescription()
        {
            
        }

        std::string SoundDescription::getID()
        {
            return _ID;
        }

        void SoundDescription::setID(std::string ID)
        {
            _ID = ID;
        }

        void SoundDescription::setChannelToListenTo(int channel)
        {
            _channelToListenTo = channel;
        }

        void SoundDescription::setNoteToListenTo(int note)
        {
            _noteToListenTo = note;
        }

        bool SoundDescription::listensToChannel(int channel)
        {
            if(channel == _channelToListenTo)
                return true;
            else
                return false;
        }

        bool SoundDescription::listensToNote(int note)
        {
            if(note == _noteToListenTo)
                return true;
            else
                return false;
        }

    }
}