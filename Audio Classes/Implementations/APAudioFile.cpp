//
//  APAudioFile.cpp
//  APAAnalyzer
//
//  Created by Danny van Swieten on 10/1/14.
//
//

#include "APAudioFile.h"

APAudioFile::~APAudioFile()
{
    
}

void APAudioFile::setAudio(AudioSampleBuffer buffer)
{
    _audio = buffer;
}

void APAudioFile::setSamplerate(int sampleRate)
{
    _sampleRate = sampleRate;
}

void APAudioFile::setNumChannels(int channels)
{
    _numChannels = channels;
}

void APAudioFile::setNumSamples(long int samples)
{
    _numSamples = samples;
};

void APAudioFile::setFileName(String name)
{
    _fileName = name;
}

String APAudioFile::getName()
{
    return _fileName;
}

const float* APAudioFile::getAudioChannel(int index)
{
    return _audio.getReadPointer(index);
}

int APAudioFile::getNumChannels()
{
    return _numChannels;
}

int APAudioFile::getSampleRate()
{
    return _sampleRate;
}

long int APAudioFile::getNumSamples()
{
    return _numSamples;
}