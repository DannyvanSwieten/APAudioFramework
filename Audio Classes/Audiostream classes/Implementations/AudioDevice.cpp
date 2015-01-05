//
//  AudioDevice.cpp
//  GUI
//
//  Created by Danny van Swieten on 10/28/14.
//
//

#include "AudioDevice.h"

#ifndef IOS

static int callback(const void *inputBuffer,
                    void *outputBuffer,
                    unsigned long framesPerBuffer,
                    const PaStreamCallbackTimeInfo* timeInfo,
                    PaStreamCallbackFlags statusFlags,
                    void *userData )
{
    AudioProcessor* audioDevice = (AudioProcessor*)userData;
    float** output = (float**)outputBuffer;

    audioDevice->render(output, output, framesPerBuffer);
    
    return 0;
}

static int callbackByLambda(const void *inputBuffer,
                            void *outputBuffer,
                            unsigned long framesPerBuffer,
                            const PaStreamCallbackTimeInfo* timeInfo,
                            PaStreamCallbackFlags statusFlags,
                            void *userData)
{
    AudioDevice* audioDevice = (AudioDevice*)userData;
    float** output = (float**)outputBuffer;
    float** input = (float**)inputBuffer;
    
    audioDevice->getLambda()(input, output, framesPerBuffer);
    
    return 0;
}

AudioDevice::AudioDevice()
{
    err = Pa_Initialize();
        if( err != paNoError)
            std::cout<<"Couldn't initialize portaudio"<<std::endl;;
    
    outputParameters.device = Pa_GetDefaultOutputDevice();
    
    if (outputParameters.device == paNoDevice)
    {
        std::cout<<"Error: No default output device."<<std::endl;
    }
    
    outputParameters.channelCount = 2;       /* stereo output */
    outputParameters.sampleFormat = paNonInterleaved | paFloat32; /* 32 bit floating point output */
    outputParameters.suggestedLatency = Pa_GetDeviceInfo( outputParameters.device )->defaultLowOutputLatency;
    outputParameters.hostApiSpecificStreamInfo = NULL;
}

void AudioDevice::listDevices()
{
    auto numDevices = Pa_GetDeviceCount();
    
    for(auto i = 0; i < numDevices; i++)
    {
        auto info = Pa_GetDeviceInfo(i);
        if (info)
        {
            connectedHardware.emplace_back(info);
            std::cout<<info->name<<std::endl;
            std::cout<<"Default Samplerate: "<<info->defaultSampleRate<<std::endl;
            std::cout<<"Maximum input channels: "<<info->maxInputChannels<<std::endl;
            std::cout<<"Maximum output channels: "<<info->maxInputChannels<<std::endl;
        }
    }
}

AudioDevice::~AudioDevice()
{
    if(stream)
        Pa_AbortStream(stream);
    
    Pa_Terminate();
}

void AudioDevice::addCallback(AudioProcessor *audioProcessor_)
{
    audioProcessor = audioProcessor_;
    
    if(stream)
    {
        Pa_StopStream(&stream);
        Pa_CloseStream(&stream);
    }
    
    err = Pa_OpenStream(&stream,
                        NULL,
                        &outputParameters,
                        sampleRate,
                        bufferSize,
                        paClipOff,
                        &callback,
                        audioProcessor);
    
    if( err != paNoError )
    {
        std::cout<<"Couldn't open stream"<<std::endl;
        std::cout<< "Error message: "<< Pa_GetErrorText( err )<<std::endl;
    }
    
    std::cout<< "Error message: "<< Pa_GetErrorText( err )<<std::endl;
    
    err = Pa_StartStream( stream );
    if( err != paNoError )
    {
        std::cout<<"Couldn't start stream"<<std::endl;
        std::cout<< "Error message: "<< Pa_GetErrorText( err )<<std::endl;
    }
}

void AudioDevice::addCallback(std::function<void(float** input, float** output, long bufferSize)> callBack)
{
    callbackLambda = callBack;

    if(stream)
    {
        Pa_StopStream(&stream);
        Pa_CloseStream(&stream);
    }
    
    err = Pa_OpenStream(&stream,
                        NULL,
                        &outputParameters,
                        sampleRate,
                        bufferSize,
                        paClipOff,
                        &callbackByLambda,
                        this);
    
    if( err != paNoError )
    {
        std::cout<<"Couldn't open stream"<<std::endl;
        std::cout<< "Error message: "<< Pa_GetErrorText( err )<<std::endl;
    }
    
    err = Pa_StartStream( stream );
    
    if( err != paNoError )
    {
        std::cout<<"Couldn't start stream"<<std::endl;
        std::cout<< "Error message: "<< Pa_GetErrorText( err )<<std::endl;
    }
}

void AudioDevice::setSampleRate(long sampleRate)
{
    this->sampleRate = sampleRate;
    
    if(!stream)
        return;
    
    Pa_StopStream(&stream);
    Pa_CloseStream(&stream);
    
    err = Pa_OpenStream(&stream,
                        NULL,
                        &outputParameters,
                        sampleRate,
                        bufferSize,
                        paClipOff,
                        callbackLambda == nullptr ? &callbackByLambda : &callback,
                        this);
    
    if( err != paNoError )
    {
        std::cout<<"Couldn't open stream with that samplerate: "<<sampleRate<<std::endl;
        std::cout<< "Error message: "<< Pa_GetErrorText( err )<<std::endl;
    }
}

void AudioDevice::setBufferSize(long bufferSize)
{
    this->bufferSize = bufferSize;
    
    if(!stream)
        return;
    
    Pa_StopStream(&stream);
    Pa_CloseStream(&stream);
    
    err = Pa_OpenStream(&stream,
                        NULL,
                        &outputParameters,
                        sampleRate,
                        bufferSize,
                        paClipOff,
                        callbackLambda == nullptr ? &callbackByLambda : &callback,
                        this);
    
    if( err != paNoError )
    {
        std::cout<<"Couldn't open stream with that buffersize: "<<bufferSize<<std::endl;
        std::cout<< "Error message: "<< Pa_GetErrorText( err )<<std::endl;
    }
}

#else

static OSStatus inputRenderCallback(void* inRefCon,
                                    AudioUnitRenderActionFlags *ioActionFlags,
                                    const AudioTimeStamp *inTimeStamp,
                                    UInt32 inBusNumber,
                                    UInt32 inNumberFrames,
                                    AudioBufferList *ioData)
{
    OSStatus result = noErr;
    
    AudioDevice* thisDevice = (AudioDevice*)inRefCon;
    
    float** input = (float**) ioData->mBuffers[0].mData;
    float** output = (float**) ioData->mBuffers[0].mData;
    
    thisDevice->getLambda()(input, output, inNumberFrames);
    
    return result;
}

AudioDevice::AudioDevice()
{
    AVAudioSession* session = [AVAudioSession sharedInstance];
    NSError* audioError;
    [session setCategory:AVAudioSessionCategoryPlayback error:&audioError];
    if(audioError)
        NSLog(@"%@", audioError.localizedDescription);
    
    sampleRate = 44100.0;
    [session setPreferredSampleRate:sampleRate error:&audioError];
    
    if(audioError)
        NSLog(@"%@", audioError.localizedDescription);
    
    [session setPreferredIOBufferDuration: 512.0/sampleRate error:&audioError];
    
    if(audioError)
        NSLog(@"%@", audioError.localizedDescription);
    
    [session setActive:YES error:&audioError];
    
    if(audioError)
        NSLog(@"%@", audioError.localizedDescription);
    
    size_t bytesPerSample = sizeof(SInt16);
    
    // setup stereo info
    stereoStreamFormat.mFormatID = kAudioFormatLinearPCM;;
    stereoStreamFormat.mFormatFlags = kAudioFormatFlagIsSignedInteger | kAudioFormatFlagIsPacked;;
    stereoStreamFormat.mBytesPerPacket = bytesPerSample;
    stereoStreamFormat.mFramesPerPacket = 1;
    stereoStreamFormat.mBytesPerFrame = bytesPerSample;
    stereoStreamFormat.mChannelsPerFrame = 2;
    stereoStreamFormat.mBitsPerChannel = 8 * bytesPerSample;
    stereoStreamFormat.mSampleRate = sampleRate;
    
#define kOutputBus 0
#define kInputBus 1
    
    // ...
    
    
    OSStatus status;
    
    // Describe audio component
    AudioComponentDescription desc;
    desc.componentType = kAudioUnitType_Output;
    desc.componentSubType = kAudioUnitSubType_RemoteIO;
    desc.componentFlags = 0;
    desc.componentFlagsMask = 0;
    desc.componentManufacturer = kAudioUnitManufacturer_Apple;
    
    // Get component
    AudioComponent inputComponent = AudioComponentFindNext(NULL, &desc);
    
    // Get audio units
    status = AudioComponentInstanceNew(inputComponent, &audioUnit);
    
    // Enable IO for recording
    UInt32 flag = 1;
    status = AudioUnitSetProperty(audioUnit,
                                  kAudioOutputUnitProperty_EnableIO,
                                  kAudioUnitScope_Input,
                                  kInputBus,
                                  &flag,
                                  sizeof(flag));
    
    // Enable IO for playback
    status = AudioUnitSetProperty(audioUnit,
                                  kAudioOutputUnitProperty_EnableIO,
                                  kAudioUnitScope_Output,
                                  kOutputBus,
                                  &flag,
                                  sizeof(flag));
    
    // Describe format
    
    stereoStreamFormat.mSampleRate			= 44100.00;
    stereoStreamFormat.mFormatID			= kAudioFormatLinearPCM;
    stereoStreamFormat.mFormatFlags         = kAudioFormatFlagIsSignedInteger | kAudioFormatFlagIsPacked;
    stereoStreamFormat.mFramesPerPacket     = 1;
    stereoStreamFormat.mChannelsPerFrame	= 1;
    stereoStreamFormat.mBitsPerChannel		= 16;
    stereoStreamFormat.mBytesPerPacket		= 2;
    stereoStreamFormat.mBytesPerFrame		= 2;
    
    // Apply format
    status = AudioUnitSetProperty(audioUnit,
                                  kAudioUnitProperty_StreamFormat,
                                  kAudioUnitScope_Output,
                                  kInputBus,
                                  &stereoStreamFormat,
                                  sizeof(stereoStreamFormat));

    status = AudioUnitSetProperty(audioUnit,
                                  kAudioUnitProperty_StreamFormat,
                                  kAudioUnitScope_Input,
                                  kOutputBus,
                                  &stereoStreamFormat,
                                  sizeof(stereoStreamFormat));
}

void AudioDevice::listDevices()
{

}

AudioDevice::~AudioDevice()
{

}

void AudioDevice::addCallback(AudioProcessor *audioProcessor_)
{
    audioProcessor = audioProcessor_;
    AURenderCallbackStruct callbackStruct;
    callbackStruct.inputProc = inputRenderCallback;
    callbackStruct.inputProcRefCon = this;
    OSStatus status = noErr;
    status = AudioUnitSetProperty(audioUnit,
                                  kAudioUnitProperty_SetRenderCallback,
                                  kAudioUnitScope_Global,
                                  kOutputBus,
                                  &callbackStruct,
                                  sizeof(callbackStruct));
    
    // Initialise
    status = AudioUnitInitialize(audioUnit);
    status = AudioOutputUnitStart(audioUnit);
}

void AudioDevice::addCallback(std::function<void(float** input, float** output, long bufferSize)> callBack)
{
    callbackLambda = callBack;
    
    AURenderCallbackStruct callbackStruct;
    callbackStruct.inputProc = inputRenderCallback;
    callbackStruct.inputProcRefCon = this;
    OSStatus status = noErr;
    status = AudioUnitSetProperty(audioUnit,
                                  kAudioUnitProperty_SetRenderCallback,
                                  kAudioUnitScope_Global,
                                  kOutputBus,
                                  &callbackStruct,
                                  sizeof(callbackStruct));
    
    // Initialise
    status = AudioUnitInitialize(audioUnit);
    status = AudioOutputUnitStart(audioUnit);
}

void AudioDevice::setSampleRate(long sampleRate)
{

}

void AudioDevice::setBufferSize(long bufferSize)
{

}

#endif