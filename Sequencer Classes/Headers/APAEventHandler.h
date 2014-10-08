//
//  APAEventHandler.h
//  CharacterAnalyser
//
//  Created by Danny van Swieten on 08-05-14.
//  Copyright (c) 2014 Danny van Swieten. All rights reserved.
//

#ifndef __CharacterAnalyser__APAEventHandler__
#define __CharacterAnalyser__APAEventHandler__

#include "APAEvent.h"
#include <vector>

class APAEventHandler
{
public:
    APAEventHandler();
    void addHumanEvent(APAEvent* event);
    void addComputerEvent(APAEvent* event);
    
private:
    
    std::vector<APAEvent*> humanEvents;
    std::vector<APAEvent*> computerEvents;
    
};

#endif /* defined(__CharacterAnalyser__APAEventHandler__) */
