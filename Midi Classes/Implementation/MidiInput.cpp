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

MidiSession::MidiSession()
{
    error = Pm_Initialize();
    std::cout<<Pm_GetErrorText(error)<<std::endl;
}


std::vector<std::string> MidiSession::getDevices()
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

void MidiSession::openDevice(std::string device)
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
            
            midiThread = std::thread(&MidiSession::read, this);
            midiThread.detach();
            
            return;
        }
    }
}

void MidiSession::openOutputDevice(std::string device)
{
    auto numMidiInputs = Pm_CountDevices();
    auto devices = getDevices();
    
    for(auto i = 0; i < numMidiInputs; i++)
    {
        if(devices[i] == device)
        {
            if(!Pm_GetDeviceInfo(i)->opened)
                error = Pm_OpenOutput(&midiStream, i, nullptr, 3, nullptr, nullptr, 0);
            else
                std::cout<<"Device is already opened"<<std::endl;
            
            if(error != pmNoError)
            {
                std::cout<<"Trying to open device: "<<devices[i]<<std::endl;
                std::cout<<Pm_GetErrorText(error)<<std::endl;
                return;
            }
            
            midiThread = std::thread(&MidiSession::read, this);
            midiThread.detach();
            
            return;
        }
    }
}

void MidiSession::addListener(MidiListener *listener)
{
    listeners.emplace_back(listener);
}

void MidiSession::read()
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
                write(&events[i]);
                MidiEvent event;
                event.status = Pm_MessageStatus(events[i].message);
                event.note = Pm_MessageData1(events[i].message);
                event.velocity = Pm_MessageData2(events[i].message);
                event.timeStamp = events[i].timestamp;
                
                if(event.isNoteOff())
                {
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
    }
}