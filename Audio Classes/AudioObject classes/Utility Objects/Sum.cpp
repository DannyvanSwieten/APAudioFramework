//
//  Add.cpp
//  AudioEnvironment
//
//  Created by Danny van Swieten on 3/19/15.
//  Copyright (c) 2015 Danny van Swieten. All rights reserved.
//

#include "Sum.h"

Sum::Sum(): AudioObject()
{
    auto main = Parameter<float>(-5, 5, 0, false, "Main");

    createInlet("Main", 99);
}

void Sum::calculateSample()
{
    output = 0;
    
    for(auto& connection: inlets["Main"]->connections)
    {
        input += connection->output;
    }
    output = input;
}

void Sum::calculateBuffer()
{
    
}