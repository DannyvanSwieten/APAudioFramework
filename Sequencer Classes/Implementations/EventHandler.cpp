//
//  EventHandler.cpp
//  CharacterAnalyser
//
//  Created by Danny van Swieten on 08-05-14.
//  Copyright (c) 2014 Danny van Swieten. All rights reserved.
//

#include "EventHandler.h"

EventHandler::EventHandler()
{
    
}

void EventHandler::addHumanEvent(Event *event)
{
    humanEvents.push_back(event);
}

void EventHandler::addComputerEvent(Event *event)
{
    computerEvents.push_back(event);
}