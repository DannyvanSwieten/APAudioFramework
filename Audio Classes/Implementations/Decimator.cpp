//
//  DecimatorModule.cpp
//  Engine
//
//  Created by Danny van Swieten on 10-05-14.
//  Copyright (c) 2014 Danny van Swieten. All rights reserved.
//

#include "Decimator.h"

namespace APAudio
{
    namespace Audio
    {
        
        Decimator::Decimator(Mainframe* mf): AudioModule(mf)
        {
            outputSample = 0;
            bitRate = getSampleRate();
            step = getSampleRate()/ bitRate;
        }

        void Decimator::calculateBuffer()
        {
            for (auto& input : inputList)
            {
                SampleBuffer inputBuffer = input->outputBuffer.data();
                UInt i = 0;
                while (i < getBufferSize())
                {
                    outputSample = inputBuffer[i];
                    
                    for (int j = 0; j < step && i < getBufferSize(); j++)
                    {
                        outputBuffer[i] = outputSample;
                        i++;
                    }
                }
            }
        }
    }
}