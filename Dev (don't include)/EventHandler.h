//
//  APAEventHandler.h
//  CharacterAnalyser
//
//  Created by Danny van Swieten on 08-05-14.
//  Copyright (c) 2014 Danny van Swieten. All rights reserved.
//

#ifndef __CharacterAnalyser__APAEventHandler__
#define __CharacterAnalyser__APAEventHandler__

#include "Event.h"
#include <vector>

class EventHandler
{
public:
    EventHandler();
    void addHumanEvent(Event* event);
    void addComputerEvent(Event* event);
    
private:
    
    std::vector<Event*> humanEvents;
    std::vector<Event*> computerEvents;
    
};

#endif /* defined(__CharacterAnalyser__APAEventHandler__) */
