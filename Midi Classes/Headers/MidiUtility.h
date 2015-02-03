//
//  MidiUtility.h
//  SmartSampler
//
//  Created by Danny van Swieten on 1/9/15.
//
//

#ifndef __SmartSampler__MidiUtility__
#define __SmartSampler__MidiUtility__

#include <string>
#include <vector>

class MidiUtility
{
public:
    MidiUtility();
    
    int stringToMidi(std::string note);
    std::string midiToString(int note);
    
private:
    
    std::vector<std::string> noteNames;
    
};

#endif /* defined(__SmartSampler__MidiUtility__) */
