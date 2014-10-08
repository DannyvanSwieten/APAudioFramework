/*
  ==============================================================================

    APAMidiDatabase.h
    Created: 3 Jul 2014 4:16:15pm
    Author:  Danny van Swieten

  ==============================================================================
*/

#ifndef APAMIDIDATABASE_H_INCLUDED
#define APAMIDIDATABASE_H_INCLUDED

#include "APAMidiData.h"
#include "APAMidiLoader.h"

class APAMidiDatabase
{
public:
    APAMidiDatabase();
    ~APAMidiDatabase();
    void load();
    void loadComposition();
    
    APAMidiData getData(){return composition;};
    
private:
    
    APAMidiData composition;
    APAMidiLoader* loader;
    std::vector<APAMidiData> database;
};



#endif  // APAMIDIDATABASE_H_INCLUDED
