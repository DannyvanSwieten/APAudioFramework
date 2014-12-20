//
//  FFT.h
//  SpeechSynthesizer
//
//  Created by Danny van Swieten on 12/18/14.
//  Copyright (c) 2014 Danny van Swieten. All rights reserved.
//

#ifndef __SpeechSynthesizer__FFT__
#define __SpeechSynthesizer__FFT__

#include "AudioFFT.h"
#include "Utility.h"
#include "SSEFunctions.h"

#include "AudioFile.h"

class FFT
{
public:
    FFT();
    ~FFT();
    
    void init(int N);
    void analyze(APAudio::Audio::AudioFile* file, int begin, int end, int overlap);
    void carToPol();
    
    inline std::vector<float>& getAmplitude(){return amplitudeFrame;};
    
private:
    
    int size = 0;
    int hopsize = 0;
    audiofft::AudioFFT analyzer;
    std::vector<float> inputBuffer;
    std::vector<float> window;
    std::vector<float> real;
    std::vector<float> imag;
    std::vector<float> amplitudeFrame;
    std::vector<float> phaseFrame;
    
    std::vector<std::vector<float>> spectrogram;
    std::vector<std::vector<float>> phaseogram;
};

#endif /* defined(__SpeechSynthesizer__FFT__) */
