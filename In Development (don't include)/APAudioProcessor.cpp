//
//  APAudioProcessorCPP.cpp
//  APAudioEngine
//
//  Created by Danny van Swieten on 07-05-14.
//  Copyright (c) 2014 Danny van Swieten. All rights reserved.
//

#include "APAudioProcessorCPP.h"

OSStatus outputRenderCallback(void *							inRefCon,
                              AudioUnitRenderActionFlags *      ioActionFlags,
                              const AudioTimeStamp *			inTimeStamp,
                              UInt32							inBusNumber,
                              UInt32							inNumberFrames,
                              AudioBufferList *                 ioData)
{
    OSStatus result = 0;
    
    APAudioProcessorCPP* processor = (APAudioProcessorCPP*)inRefCon;
    processor->process(inNumberFrames, ioData);
    return result;
}

APAudioProcessorCPP::APAudioProcessorCPP()
{
    audioIsRunning = false;
    
    assert(!setupAudioSession());
    assert(!setupMonoStreamFormat());
    assert(!setupStereoStreamFormat());
    assert(!setupProcessor());
    assert(!setupAudioUnits());
}

OSStatus APAudioProcessorCPP::setupAudioSession()
{
    OSStatus error = noErr;
    
    std::cout<<"Set up audio session..."<<std::endl;
    
#if defined ( USING_IOS )
    
    // Set the audio session active
    NSError *err = nil;
    if (![[AVAudioSession sharedInstance] setActive:YES error:&err])
    {
        NSLog(@"Couldn't activate audio session: %@", err);
    }
    AVAudioSession* audioSession    = [AVAudioSession sharedInstance];
    
    graphSampleRate = 44100;
    [audioSession setPreferredSampleRate: graphSampleRate error: &err];
    
    if (error)
    {
        NSLog(@"Could'nt set preferred samplerate: 44100");
    }
    
    [audioSession setCategory: AVAudioSessionCategoryPlayAndRecord error: &err];
    
    [audioSession setActive: YES error: &err];
    graphSampleRate = [audioSession sampleRate];
    sampleSize = 512;
    
    bufferSize = ((sampleSize)/graphSampleRate);
    
    [audioSession setPreferredIOBufferDuration: bufferSize error:&err];
    if (error)
    {
        NSLog(@"Could'nt set preferred buffer size: %d", sampleSize);
    }
    
    bufferSize = [audioSession preferredIOBufferDuration];
    numInputChannels = [audioSession inputNumberOfChannels];
    numOutputChannels = [audioSession outputNumberOfChannels];
    
    NSLog(@"Done... Everything OK :)");
    NSLog(@"Number of input channels: %ld", (long)numInputChannels);
    NSLog(@"Number of output channels: %ld", (long)numOutputChannels);
    NSLog(@"Samplerate: %f", graphSampleRate);
    NSLog(@"BufferSize: %f", bufferSize * graphSampleRate);
    
#elif defined (USING_OSX)
    
    graphSampleRate = 44100;
    sampleSize = 512;
    bufferSize = (sampleSize/graphSampleRate);
    
#endif
    return error;
}

OSStatus APAudioProcessorCPP::setupProcessor()
{
    OSStatus result = noErr;
    
#if defined (USING_IOS)
    
    NSLog(@"Initializing audio processing graph...");
    
    NewAUGraph(&processingGraph);
    if (result != noErr)
        NSLog(@"Couldn't make processing graph. Error code: %d", (int)result);
    else
        NSLog(@"Done!");
    
    NSLog(@"Set up input/output unit...");
    IOComponentDescription.componentType          = kAudioUnitType_Output;
    IOComponentDescription.componentSubType       = kAudioUnitSubType_RemoteIO;
    IOComponentDescription.componentManufacturer  = kAudioUnitManufacturer_Apple;
    IOComponentDescription.componentFlags         = 0;
    IOComponentDescription.componentFlagsMask     = 0;
    NSLog(@"Done!");
    
    NSLog(@"Set up multi-channel mixer unit...");
    mixerComponentDescription.componentType          = kAudioUnitType_Mixer;
    mixerComponentDescription.componentSubType       = kAudioUnitSubType_MultiChannelMixer;
    mixerComponentDescription.componentManufacturer  = kAudioUnitManufacturer_Apple;
    mixerComponentDescription.componentFlags         = 0;
    mixerComponentDescription.componentFlagsMask     = 0;
    NSLog(@"Done!");
    
    NSLog(@"Adding nodes to the processing graph...");
    NSLog(@"Input/output node:");
    
    
    //-------------------------------------------------------
    result =    AUGraphAddNode(processingGraph,
                               &IOComponentDescription,
                               &IONode);
    if (result != noErr)
        NSLog(@"Failed adding Input/Output node with error code: %d", (int)result);
    else
        NSLog(@"Done!");
    
    NSLog(@"Mixer node:");
    
    //-------------------------------------------------------
    result =    AUGraphAddNode(processingGraph,
                               &mixerComponentDescription,
                               &mixerNode);
    if (result != noErr)
        NSLog(@"Failed adding multi-channel mixer with error code: %d", (int)result);
    else
        NSLog(@"Done!");
    
#elif defined (USING_OSX)
    
    NSLog(@"Set up input/output unit...");
    IOComponentDescription.componentType          = kAudioUnitType_Output;
    IOComponentDescription.componentSubType       = kAudioUnitSubType_DefaultOutput;
    IOComponentDescription.componentManufacturer  = kAudioUnitManufacturer_Apple;
    NSLog(@"Done!");
    
    AudioComponent component = AudioComponentFindNext(NULL, &IOComponentDescription);
    
    if (component == NULL)
    {
        NSLog(@"can't get output unit based on given description");
    }
    
    result = AudioComponentInstanceNew(component, &IOUnit);
    
    if (result != noErr)
    {
        NSLog(@"Can't open component voor output");
    }
    
#endif
    
    return result;
}

OSStatus APAudioProcessorCPP::setupAudioUnits()
{
    OSStatus result = noErr;
    
#if defined (USING_IOS)
    
    NSLog(@"Open processingGraph to instantiate audio units");
    
    result = AUGraphOpen(processingGraph);
    
    if (result != noErr)
    {
        NSLog(@"Couldn't open processing graph. Error code: %d", (int)result);
        return result;
    }
    else
        NSLog(@"Done!");
    
    NSLog(@"Configuring audio units...");
    
    result = AUGraphNodeInfo(processingGraph, mixerNode, nil, &mixerUnit);
    
    if (result != noErr)
    {
        NSLog(@"Failed to get multi-channel mixer unit. Error code: %d", (int)result);
        return result;
    }
    
    result = AUGraphNodeInfo(processingGraph, IONode, nil, &IOUnit);
    
    if (result != noErr)
    {
        NSLog(@"Failed to get input/output unit. Error code: %d", (int)result);
        return result;
    }
    
    NSLog(@"Connecting the output of the mixer to the input of the input/output unit");
    
    result = AUGraphConnectNodeInput(processingGraph, mixerNode, 0, IONode, 0);
    
    if (result != noErr)
    {
        NSLog(@"Failed connecting the output of the mixer to the input of the input/output unit. Error code: %d", (int)result);
        return result;
    }
    else
        NSLog(@"Done!");
    
    NSLog(@"Setting the amount of busses in the multi-channel mixer");
    
    UInt32 numBusses = 1;
    
    result = AudioUnitSetProperty(mixerUnit, kAudioUnitProperty_ElementCount, kAudioUnitScope_Input, 0, &numBusses, sizeof(numBusses));
    
    if (result != noErr)
    {
        NSLog(@"Failed to set number of busses in multi-channel mixer unit. Error code: %d", (int)result);
        return result;
    }
    else
        NSLog(@"Done!");
    
    UInt32 maxFrames = 4096*2;
    
    NSLog(@"Setting the maximum amount of frames per callback in the multi-channel mixer to %d", (unsigned int)maxFrames);
    
    result = AudioUnitSetProperty(mixerUnit, kAudioUnitProperty_MaximumFramesPerSlice, kAudioUnitScope_Global, 0, &maxFrames, sizeof(maxFrames));
    
    if (result != noErr)
    {
        NSLog(@"Failed to set maximum of frames per callback in multi-channel mixer unit. Error code: %d", (int)result);
        return result;
    }
    else
        NSLog(@"Done!");
    
    for (int i = 0; i < numBusses; i++)
    {
        result = AudioUnitSetProperty(mixerUnit, kAudioUnitProperty_StreamFormat, kAudioUnitScope_Input, i, &stereoStreamDescription, sizeof(stereoStreamDescription));
        
        if (result != noErr)
        {
            NSLog(@"Could not set input format for mixer unit bus: %d",i);
        }
        
        result = AudioUnitSetProperty(mixerUnit, kAudioUnitProperty_StreamFormat, kAudioUnitScope_Output, i, &stereoStreamDescription, sizeof(stereoStreamDescription));
        
        if (result != noErr)
        {
            NSLog(@"Could not set output format for mixer unit bus: %d",i);
        }
    }
    
    NSLog(@"Set samplerate of mixer unit");
    
    result = AudioUnitSetProperty (mixerUnit, kAudioUnitProperty_SampleRate, kAudioUnitScope_Output, 0, &graphSampleRate, sizeof (graphSampleRate));
    
    if (result != noErr) {
        NSLog(@"Failed to set mixer unit samplerate");
    }
    
    NSLog(@"Initializing audio processing graph");
    
    result = AUGraphInitialize(processingGraph);
    
    if (result != noErr)
    {
        NSLog(@"Failed to initialize audio processing graph Error code: %d", (int)result);
        return result;
    }
    else
        NSLog(@"Done!");
    
    AURenderCallbackStruct callbackStruct;
    callbackStruct.inputProc        = outputRenderCallback;
    callbackStruct.inputProcRefCon  = (void*)this;
    
    result = AudioUnitSetProperty(IOUnit,
                                  kAudioUnitProperty_SetRenderCallback,
                                  kAudioUnitScope_Input,
                                  0,
                                  &callbackStruct,
                                  sizeof(callbackStruct));
    
    
#elif defined (USING_OSX)
    
    AURenderCallbackStruct callbackStruct;
    callbackStruct.inputProc        = outputRenderCallback;
    callbackStruct.inputProcRefCon  = (void*)this;
    
    result = AudioUnitSetProperty(IOUnit,
                                  kAudioUnitProperty_SetRenderCallback,
                                  kAudioUnitScope_Input,
                                  0,
                                  &callbackStruct,
                                  sizeof(callbackStruct));
    if (result != noErr)
    {
        NSLog(@"Failed to set audio callback at output unit");
    }
    
    result = AudioUnitInitialize(IOUnit);
    
    if (result != noErr)
    {
        NSLog(@"Failed to initialize output unit");
    }
    
#endif
    
    return result;
}

OSStatus APAudioProcessorCPP::startProcessor()
{
    OSStatus result = noErr;
    
    NSLog(@"Trying to start audio pull...");
#if defined (USING_IOS)
    if (!audioIsRunning)
    {
        result = AUGraphStart(processingGraph);
        
        if (result != noErr)
        {
            NSLog(@"Failed. Error code: %d", (int)result);
        }
        else
        {
            audioIsRunning = YES;
            NSLog(@"Succes!");
        }
    }
    result = AudioUnitSetParameter (mixerUnit, kMultiChannelMixerParam_Enable, kAudioUnitScope_Input, 1, YES, 0);
    
    if (result != noErr)
        NSLog(@"set volume input error: %d", (int)result);
    
    result = AudioUnitSetParameter(mixerUnit, kMultiChannelMixerParam_Volume, kAudioUnitScope_Input, 0, 1.0, 0);
    if (result != noErr)
        NSLog(@"set volume input error");
    
#elif defined (USING_OSX)
    if (!audioIsRunning)
    {
        result = AudioOutputUnitStart(IOUnit);
        if (result != noErr)
            NSLog(@"Unable to start output unit");
    }
    
    audioIsRunning = true;
    
#endif
    return result;
}

OSStatus APAudioProcessorCPP::setupMonoStreamFormat()
{
    OSStatus result = noErr;
    
    NSLog(@"Configure mono stream format...");
    
    UInt32 sampleSize = sizeof(Float32);
    
    monoStreamDescription.mChannelsPerFrame    = 1;
    monoStreamDescription.mBitsPerChannel      = 8 * sampleSize;
    monoStreamDescription.mBytesPerFrame       = sampleSize;
    monoStreamDescription.mBytesPerPacket      = sampleSize;
    monoStreamDescription.mFramesPerPacket     = 1;
    monoStreamDescription.mFormatID            = kAudioFormatLinearPCM;
    monoStreamDescription.mFormatFlags         = kAudioFormatFlagsNativeFloatPacked | kAudioFormatFlagIsNonInterleaved;
    monoStreamDescription.mSampleRate          = graphSampleRate;
    monoStreamDescription.mReserved            = 0;
    
    printASBD(monoStreamDescription);
    
    NSLog(@"Done!");
    
    return result;

}

OSStatus APAudioProcessorCPP::setupStereoStreamFormat()
{
    OSStatus result = noErr;
    
    NSLog(@"Configure stereo stream format...");
    
    UInt32 sampleSize = sizeof(Float32);
    
    stereoStreamDescription.mChannelsPerFrame  = 2;
    stereoStreamDescription.mBitsPerChannel    = 8 * sampleSize;
    stereoStreamDescription.mBytesPerFrame     = sampleSize;
    stereoStreamDescription.mBytesPerPacket    = sampleSize;
    stereoStreamDescription.mFramesPerPacket   = 1;
    stereoStreamDescription.mFormatID          = kAudioFormatLinearPCM;
    stereoStreamDescription.mFormatFlags       = kAudioFormatFlagsNativeFloatPacked | kAudioFormatFlagIsNonInterleaved;
    stereoStreamDescription.mSampleRate        = graphSampleRate;
    stereoStreamDescription.mReserved          = 0;
    
    printASBD(stereoStreamDescription);
    
    NSLog(@"Done!");
    
    return result;
}

void APAudioProcessorCPP::printASBD(AudioStreamBasicDescription asbd)
{
    char formatIDString[5];
    UInt32 formatID = CFSwapInt32HostToBig (asbd.mFormatID);
    bcopy (&formatID, formatIDString, 4);
    formatIDString[4] = '\0';
    
    NSLog (@"  Sample Rate:         %10.0f",  asbd.mSampleRate);
    NSLog (@"  Format ID:           %10s",    formatIDString);
    NSLog (@"  Format Flags:        %10X",    (unsigned int)asbd.mFormatFlags);
    NSLog (@"  Bytes per Packet:    %10d",    (unsigned int)asbd.mBytesPerPacket);
    NSLog (@"  Frames per Packet:   %10d",    (unsigned int)asbd.mFramesPerPacket);
    NSLog (@"  Bytes per Frame:     %10d",    (unsigned int)asbd.mBytesPerFrame);
    NSLog (@"  Channels per Frame:  %10d",    (unsigned int)asbd.mChannelsPerFrame);
    NSLog (@"  Bits per Channel:    %10d",    (unsigned int)asbd.mBitsPerChannel);
}