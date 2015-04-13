//
//  AudioUnit.h
//  VSTHost
//
//  Created by Danny van Swieten on 2/1/15.
//  Copyright (c) 2015 Danny van Swieten. All rights reserved.
//

#ifndef __VSTHost__AudioUnit__
#define __VSTHost__AudioUnit__

#include "Unit.h"
#include "Sum.h"

class AudioUnit: public Unit
{
public:
    AudioUnit(int sampleRate, int bufferSize, unsigned int numInlets_, unsigned int numChannels_);
    void connect(AudioUnit* unit, unsigned int inlet);
    virtual AudioObject* getOutputObject(unsigned int channel) = 0;
    void disconnect(AudioUnit* unit, unsigned int inlet);
    
    unsigned int getNumChannels();
    unsigned int getNumInlets();
    
    struct Inlet
    {
        // All the connected units
        std::vector<AudioUnit*> units;
        
        // A mixer for each channel
        std::vector<std::unique_ptr<Sum>> mixers;
    };
    
private:
    
    unsigned int numInlets = 0;
    unsigned int numChannels = 0;
    
protected:
    std::vector<std::unique_ptr<Inlet>> inlets;
    std::vector<AudioUnit*> connections;
};

#endif /* defined(__VSTHost__AudioUnit__) */
