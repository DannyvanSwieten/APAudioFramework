//
//  FFT.cpp
//  SpeechSynthesizer
//
//  Created by Danny van Swieten on 12/18/14.
//  Copyright (c) 2014 Danny van Swieten. All rights reserved.
//

#include "FFT.h"

FFT::FFT()
{
    
}

FFT::~FFT()
{
    
}

void FFT::init(int N)
{
    size = N;
    analyzer.init(size);
    inputBuffer.resize(audiofft::AudioFFT::ComplexSize(size));
    real.resize(audiofft::AudioFFT::ComplexSize(size));
    imag.resize(audiofft::AudioFFT::ComplexSize(size));
    phaseFrame.resize(audiofft::AudioFFT::ComplexSize(size));
    amplitudeFrame.resize(audiofft::AudioFFT::ComplexSize(size));
    window.resize(size);
    createWindow(HANNING, window.data(), size);
}

void FFT::analyze(APAudio::Audio::AudioFile* file, int begin, int end, int overlap)
{
    
    if(end > file->getNumSamples() || begin < 0)
        return;
    
    float* audio = file->getAudioVector(0).data();
    
    int hopsize = size / overlap;
    int numFrames = (end - begin) / hopsize;
    spectrogram.resize(numFrames);
    
    for(auto frame = 0; frame < numFrames; frame++)
    {
        int windowCounter = 0;
        
        for(auto i = 0; i < size; i++)
        {
            audio[i + (frame * hopsize)] *= window[windowCounter++];
        }
        
        memset(real.data(), 0, sizeof(float) * size/2);
        memset(imag.data(), 0, sizeof(float) * size/2);
        analyzer.fft(audio, real.data(), imag.data());
        carToPol();
        
        spectrogram[frame] = getAmplitude();
    }
}

void FFT::carToPol()
{
    vec2polSSE(real.data(), imag.data(), amplitudeFrame.data(), phaseFrame.data(), size/2, true);
}