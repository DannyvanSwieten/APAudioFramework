//
//  MidiInput.h
//  VSTHost
//
//  Created by Danny van Swieten on 1/30/15.
//  Copyright (c) 2015 Danny van Swieten. All rights reserved.
//

#ifndef __VSTHost__MidiInput__
#define __VSTHost__MidiInput__

#include "portmidi.h"
#include "porttime.h"
#include <iostream>
#include <vector>
#include <thread>
#include <string>

class MidiEvent
{
public:
    int status;
    int note;
    int velocity;
    int channel;
    int timeStamp;
    
    bool isNoteOn(){return status >= 144 && status < 160;};
    bool isNoteOff(){return status >= 128 && status < 144;}
    bool isPolyAftertouch(){return status >= 160 && status < 176;};
    bool isPitchBend(){return status >= 224 && status < 240;};
};

class MidiBuffer
{
public:
    std::vector<MidiEvent> events;
};

class MidiListener
{
public:
    void addBuffer(MidiBuffer buffer);
    
private:
    
    std::vector<MidiBuffer> buffers;
};

class MidiInput
{
public:
    MidiInput();
    static std::vector<std::string> getDevices();
    void openDevice(std::string device);
    void read();
    virtual void write(PmEvent* event){};
    
    void addListener(MidiListener* listener);
    PortMidiStream* getCurrentStream(){return midiStream;};
    
    PmEvent events[6];
    int numEvents = 0;
private:
    
    std::vector<MidiListener*> listeners;
    std::thread midiThread;
    
    bool active = true;
    MidiBuffer buffer;
    PmError error;
    PortMidiStream* midiStream;
};


#endif /* defined(__VSTHost__MidiInput__) */
