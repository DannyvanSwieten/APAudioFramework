//
//  Input.cpp
//  DAW
//
//  Created by Danny van Swieten on 4/9/15.
//
//

#include "Input.h"
#include "DawAudioProcessor.h"

Input::Input(DawAudioProcessor* processor_)
{
    processor = processor_;
    listenToChannel(0);
}

void Input::process()
{
//    memcpy(output.data(), processor->getInputChannel(channel), sizeof(float) * getBufferSize());
}

void Input::listenToChannel(unsigned int channel_)
{
    channel = channel_;
}
