//
//  SummerObject.cpp
//  DAW
//
//  Created by Danny van Swieten on 2/2/15.
//
//

#include "SummerObject.h"

SummerObject::SummerObject(APAudio::Mainframe& mf_): APAudio::AudioObject(mf_)
{
    
}

void SummerObject::calculateBuffer()
{
    memset(outputBuffer.data(), 0, sizeof(float) * getBufferSize());
    
    if(inputList.size())
    {
        for(auto& input: inputList)
        {
            float* inputBuffer = input->outputBuffer.data();
            for(auto i = 0; i < getBufferSize(); i++)
            {
                outputBuffer[i] += inputBuffer[i];
            }
        }
    }
}