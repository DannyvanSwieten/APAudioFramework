//
//  AudioFile.cpp
//  AAnalyzer
//
//  Created by Danny van Swieten on 10/1/14.
//
//

#include "AudioFile.h"

namespace APAudio
{

    AudioFile::~AudioFile()
    {
        
    }

    void AudioFile::setAudio(Buffer<float> audio)
    {
        _audio = audio;
    }

    void AudioFile::setSamplerate(int sampleRate)
    {
        _sampleRate = sampleRate;
    }

    void AudioFile::setNumChannels(int channels)
    {
        _numChannels = channels;
    }

    void AudioFile::setNumSamples(long int samples)
    {
        _numSamples = samples;
    };

    void AudioFile::setFileName(std::string name)
    {
        _fileName = name;
    }

    std::string AudioFile::getName()
    {
        return _fileName;
    }

    const float* AudioFile::getAudioChannel(int index)
    {
        return _audio.getChannel(index).data();
    }

    std::vector<float>& AudioFile::getAudioVector(int index)
    {
        return _audio.getChannel(index);
    }

    int AudioFile::getNumChannels()
    {
        return _numChannels;
    }

    int AudioFile::getSampleRate()
    {
        return _sampleRate;
    }

    long int AudioFile::getNumSamples()
    {
        return _numSamples;
    }
}