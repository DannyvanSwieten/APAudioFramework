//
//  APAudioSoundDescription.h
//  APAudioEngine
//
//  Created by Danny van Swieten on 13-05-14.
//  Copyright (c) 2014 Danny van Swieten. All rights reserved.
//

#ifndef __APAudioEngine__APAudioSoundDescription__
#define __APAudioEngine__APAudioSoundDescription__

#include "APAudioModule.h"

class APAudioSoundDescription
{
public:
    APAudioSoundDescription();
    
    virtual ~APAudioSoundDescription();
    
    virtual bool    listensToNote(ControlValue note) = 0;
    virtual bool    listensToChannel(ControlValue channel) = 0;
    
    void            setID(String ID);
    void            setRange(ControlValue min, ControlValue max);
    void            setLength(unsigned int length);
    
    inline ControlValue getMinNote(){return _minNote;};
    inline ControlValue getMaxNote(){return _maxNote;};
    inline ControlValue getChannel(){return _channel;};
    
private:
    
    String _ID;
    ControlValue _minNote;
    ControlValue _maxNote;
    ControlValue _channel;
};

#endif /* defined(__APAudioEngine__APAudioSoundDescription__) */
