//
//  MidiUtility.cpp
//  SmartSampler
//
//  Created by Danny van Swieten on 1/9/15.
//
//

#include "MidiUtility.h"

MidiUtility::MidiUtility()
{
    noteNames.resize(128);
    for (auto octave = 0; octave < 10; octave++)
    {
        noteNames[0 + (octave * 12)] = "C" + std::to_string(octave);
        noteNames[1 + (octave * 12)] = "C#" + std::to_string(octave);
        noteNames[2 + (octave * 12)] = "D" + std::to_string(octave);
        noteNames[3 + (octave * 12)] = "D#" + std::to_string(octave);
        noteNames[4 + (octave * 12)] = "E" + std::to_string(octave);
        noteNames[5 + (octave * 12)] = "F" + std::to_string(octave);
        noteNames[6 + (octave * 12)] = "F#" + std::to_string(octave);
        noteNames[7 + (octave * 12)] = "G" + std::to_string(octave) ;
        noteNames[8 + (octave * 12)] = "G#" + std::to_string(octave);
        noteNames[9 + (octave * 12)] = "A" + std::to_string(octave);
        noteNames[10 + (octave * 12)] = "A#" + std::to_string(octave);
        noteNames[11 + (octave * 12)] = "B" + std::to_string(octave);
    }
}

int MidiUtility::stringToMidi(std::string note)
{
    for(auto i = 0; i < 128; i++)
        if(noteNames[i] == note)
            return i;
    
    return -1;
}

std::string MidiUtility::midiToString(int note)
{
    return std::string("");
}