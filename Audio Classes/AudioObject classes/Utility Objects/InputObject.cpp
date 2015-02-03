//
//  InputObject.cpp
//  VSTHost
//
//  Created by Danny van Swieten on 2/1/15.
//  Copyright (c) 2015 Danny van Swieten. All rights reserved.
//

#include "InputObject.h"

InputObject::InputObject(APAudio::Mainframe& mf_): APAudio::AudioObject(mf_)
{
    
}

void InputObject::feed(float *input)
{
    this->input = input;
}

void InputObject::enableInput()
{
    inputEnabled = true;
}

void InputObject::disableInput()
{
    inputEnabled = false;
}

void InputObject::calculateBuffer()
{
    if(inputEnabled)
        memcpy(outputBuffer.data(), input, getBufferSize() * sizeof(float));
    else
        memset(outputBuffer.data(), 0, getBufferSize() * sizeof(float));
}