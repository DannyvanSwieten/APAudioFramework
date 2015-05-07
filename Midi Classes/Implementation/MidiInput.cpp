//
//  MidiInput.cpp
//  VSTHost
//
//  Created by Danny van Swieten on 1/30/15.
//  Copyright (c) 2015 Danny van Swieten. All rights reserved.
//

#include "MidiInput.h"

void MidiListener::addBuffer(MidiBuffer buffer)
{
    std::cout<<"Listener recieved midi event buffer!"<<std::endl;
    buffers.emplace_back(buffer);
}

MidiInput::MidiInput()
{
    error = Pm_Initialize();
    std::cout<<Pm_GetErrorText(error)<<std::endl;
}


std::vector<std::string> MidiInput::getDevices()
{
    auto numMidiInputs = Pm_CountDevices();
    std::vector<std::string> devices;
    for (auto input = 0; input < numMidiInputs; input++)
    {
        std::string device = Pm_GetDeviceInfo(input)->name;
        devices.emplace_back(device);
    }
    return devices;
}

void MidiInput::openDevice(std::string device)
{
    auto numMidiInputs = Pm_CountDevices();
    auto devices = getDevices();
    
    for(auto i = 0; i < numMidiInputs; i++)
    {
        if(devices[i] == device)
        {
            if(!Pm_GetDeviceInfo(i)->opened)
                error = Pm_OpenInput(&midiStream, i, nullptr, 3, nullptr, nullptr);
            else
                std::cout<<"Device is already opened"<<std::endl;
            
            if(error != pmNoError)
            {
                std::cout<<"Trying to open device: "<<devices[i]<<std::endl;
                std::cout<<Pm_GetErrorText(error)<<std::endl;
                return;
            }
            
            midiThread = std::thread(&MidiInput::read, this);
            midiThread.detach();
            
            return;
        }
    }
}

void MidiInput::addListener(MidiListener *listener)
{
    listeners.emplace_back(listener);
}

void MidiInput::read()
{
    while(active)
    {
        auto available = Pm_Poll(midiStream);
        
        if(available)
        {
            numEvents = Pm_Read(midiStream, events, 1);
            buffer.events.resize(numEvents);
            
            for(auto i = 0; i < numEvents; i++)
            {
                MidiEvent event;
                event.status = Pm_MessageStatus(events[i].message);
                event.note = Pm_MessageData1(events[i].message);
                event.velocity = Pm_MessageData2(events[i].message);
                event.timeStamp = events[i].timestamp;
                
                if(event.isNoteOff())
                {
                    write(&events[i]);
                    event.channel = event.status - 127;
                }
                
                if(event.isNoteOn())
                    event.channel = event.status - 143;
                
                if (event.isPolyAftertouch())
                    event.channel = event.status = 159;
                
                buffer.events[i] = event;
            }
            
            for(auto& listener: listeners)
                listener->addBuffer(buffer);
        }
        
        std::chrono::milliseconds dura(5);
        std::this_thread::sleep_for(dura);
    }
}