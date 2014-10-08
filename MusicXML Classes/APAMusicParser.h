//
//  APAMusicParser.h
//  APA
//
//  Created by Danny van Swieten on 22-05-14.
//
//

#ifndef __APA__APAMusicParser__
#define __APA__APAMusicParser__

#include "../JuceLibraryCode/JuceHeader.h"

#include "APAEventHandler.h"
#include "APAEvent.h"

class APAMusicParser
{
public:
    
    APAMusicParser();
    ~APAMusicParser();
    
    void loadMusicFile();
    void checkForEvents();
    
private:
    
    XmlElement* mainXmlElement;
    APAEventHandler* eventHandler;
};

#endif /* defined(__APA__APAMusicParser__) */
