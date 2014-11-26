//
//  AudioDevice.cpp
//  GUI
//
//  Created by Danny van Swieten on 10/28/14.
//
//

#include "AudioDevice.h"

static int callback(const void *inputBuffer, void *outputBuffer,
                          unsigned long framesPerBuffer,
                          const PaStreamCallbackTimeInfo* timeInfo,
                          PaStreamCallbackFlags statusFlags,
                          void *userData )
{
    AudioProcessor* audioDevice = (AudioProcessor*)userData;
    
    float* output = (float*)outputBuffer;
    audioDevice->render(output, output, framesPerBuffer);
    
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
    outputParameters.sampleFormat = paFloat32; /* 32 bit floating point output */
    outputParameters.suggestedLatency = Pa_GetDeviceInfo( outputParameters.device )->defaultLowOutputLatency;
    outputParameters.hostApiSpecificStreamInfo = NULL;
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
                        44100.0,
                        512,
                        paClipOff,
                        &callback,
                        audioProcessor);
    
    if( err != paNoError )
        std::cout<<"Couldn't open stream"<<std::endl;
    
    std::cout<< "Error message: "<< Pa_GetErrorText( err )<<std::endl;
    
    err = Pa_StartStream( stream );
    if( err != paNoError )
        std::cout<<"Couldn't start stream"<<std::endl;
    
    std::cout<< "Error message: "<< Pa_GetErrorText( err )<<std::endl;
}

void AudioDevice::addCallback(std::function<void(float* input, float* output)> callback)
{
    
}