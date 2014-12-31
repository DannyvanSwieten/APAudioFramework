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
    float** output = (float**)outputBuffer;

    audioDevice->render(output, output, framesPerBuffer);
    
    return 0;
}

static int callbackByLambda(const void *inputBuffer, void *outputBuffer,
                          unsigned long framesPerBuffer,
                          const PaStreamCallbackTimeInfo* timeInfo,
                          PaStreamCallbackFlags statusFlags,
                          void *userData )
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