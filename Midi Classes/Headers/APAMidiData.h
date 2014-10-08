/*
  ==============================================================================

    APAMidiData.h
    Created: 3 Jul 2014 3:54:02pm
    Author:  Danny van Swieten

  ==============================================================================
*/

#ifndef APAMIDIDATA_H_INCLUDED
#define APAMIDIDATA_H_INCLUDED

#include <vector>
#include "../JuceLibraryCode/JuceHeader.h"

class APAMidiData
{
public:
    
    using notes = std::vector<int>;
    
    String ID;
    
    std::vector<int>                intervals;
    std::vector<notes>              phraseIntervals;
    std::vector<notes>              measureIntervals;
    
private:
    

};


#endif  // APAMIDIDATA_H_INCLUDED
