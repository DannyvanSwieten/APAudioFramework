//
//  Input.cpp
//  DAW
//
//  Created by Danny van Swieten on 4/9/15.
//
//

#include "Input.h"

Input::Input()
{
    listenToChannel(0);
}

void Input::calculateSample()
{
    output = inputBuffer[counter];
    counter++;
    if(counter > getBufferSize())
        counter = 0;
}

void Input::calculateBuffer()
{
    
}

void Input::listenToChannel(unsigned int channel_)
{
    channel = channel_;
}