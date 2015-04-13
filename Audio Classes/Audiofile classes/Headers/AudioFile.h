//
//  APAudioFile.h
//  APAAnalyzer
//
//  Created by Danny van Swieten on 10/1/14.
//
//

#ifndef __APAAnalyzer__APAudioFile__
#define __APAAnalyzer__APAudioFile__

#include <string>
#include "Buffer.h"

class AudioFile
{
public:
    
    ~AudioFile();
    void setAudio(Buffer<float> audio);
    void setNumChannels(int channels);
    void setNumSamples(long int samples);
    void setFileName(std::string name);
    void setSamplerate(int sampleRate);
    
    std::string getName();
    const float* getAudioChannel(int index);
    std::vector<float>& getAudioVector(int index);
    int getNumChannels();
    long int getNumSamples();
    int getSampleRate();
    
private:
    
    Buffer<float> _audio;
    std::string _fileName;
    int _numChannels = 0;
    long int _numSamples = 0;
    int _sampleRate = 0;
};

#endif /* defined(__APAAnalyzer__APAudioFile__) */
