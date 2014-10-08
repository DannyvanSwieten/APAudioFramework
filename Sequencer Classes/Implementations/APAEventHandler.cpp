//
//  APAEventHandler.cpp
//  CharacterAnalyser
//
//  Created by Danny van Swieten on 08-05-14.
//  Copyright (c) 2014 Danny van Swieten. All rights reserved.
//

#include "APAEventHandler.h"

APAEventHandler::APAEventHandler()
{
    
}

void APAEventHandler::addHumanEvent(APAEvent *event)
{
    humanEvents.push_back(event);
}

void APAEventHandler::addComputerEvent(APAEvent *event)
{
    computerEvents.push_back(event);
}