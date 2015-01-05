//
//  FFT.cpp
//  SpeechSynthesizer
//
//  Created by Danny van Swieten on 12/18/14.
//  Copyright (c) 2014 Danny van Swieten. All rights reserved.
//

#include "Spectrogram.h"

Spectrogram::Spectrogram()
{
    
}

Spectrogram::~Spectrogram()
{
    
}

void Spectrogram::init(long N)
{
    size = N;
    inputBuffer.resize(audiofft::AudioFFT::ComplexSize(size));
    real.resize(audiofft::AudioFFT::ComplexSize(size));
    imag.resize(audiofft::AudioFFT::ComplexSize(size));
    phaseFrame.resize(audiofft::AudioFFT::ComplexSize(size));
    amplitudeFrame.resize(audiofft::AudioFFT::ComplexSize(size));
    window.resize(size);
    createWindow(HANNING, window.data(), size);
}

void Spectrogram::createSpectrogram(AudioFile* file, long begin, long end, long overlap)
{
    
    auto analyzer = new audiofft::AudioFFT();
    analyzer->init(size);
    
    if(end > file->getNumSamples() || begin < 0)
        return;
    
    float* audio = file->getAudioVector(0).data();
    
    if(overlap == 0)overlap = 1;
    
    long hopsize = size / overlap;
    long numFrames = (end - begin) / hopsize;
    
    spectrogram.clear();
    phaseogram.clear();
    
    for(auto frame = 0; frame < numFrames; frame++)
    {
        int windowCounter = 0;
        
        long index = 0;
        float buffer[size];
        for(auto i = 0; i < size; i++)
        {
            index = (begin + i) + (frame * hopsize);
            if(index >= file->getNumSamples())
                buffer[i] = 0.0;
            else
                buffer[i] = audio[index] * window[windowCounter++];
        }
        
        memset(real.data(), 0, sizeof(float) * size/2);
        memset(imag.data(), 0, sizeof(float) * size/2);
        
        analyzer->fft(buffer, real.data(), imag.data());
        
        carToPol();
        spectrogram.emplace_back(amplitudeFrame);
        //phaseogram.emplace_back(phaseFrame);
    }
    
    delete analyzer;
}

void Spectrogram::carToPol()
{
    vec2polSSE(real.data(), imag.data(), amplitudeFrame.data(), phaseFrame.data(), size/2, false);
}

//void Spectrogram::calculateCepstrum()
//{
//    std::vector<float> logFFT;
//    logFFT.resize(size);
//    
//    for(auto i = 0; i < size; i++)
//    {
//        logFFT[i] = log(fabs(amplitudeFrame[i]));
//        if(isnan(logFFT[i])) logFFT[i] = -140;
//    }
//    
//    std::vector<float> buffer;
//    buffer.resize(size);
//    memset(imag.data(), 0, sizeof(float)*imag.size());
//    analyzer.ifft(buffer.data(), logFFT.data(), imag.data());
//    cepstrum.emplace_back(buffer);
//}