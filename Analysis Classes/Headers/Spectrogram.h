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

class Spectrogram
{
public:
    Spectrogram();
    ~Spectrogram();
    
    void init(long N);
    void createSpectrogram(AudioFile* file, long begin, long end, long overlap);
//    void calculateCepstrum();
    void carToPol();
    
    inline std::vector<float>& getAmplitude(){return amplitudeFrame;};
    inline std::vector<float>& getPhase(){return phaseFrame;};
    inline std::vector<std::vector<float>>& getSpectroGram(){return spectrogram;};
    inline std::vector<std::vector<float>>& getCepstrum(){return cepstrum;};
    
private:
    
    long size = 0;
    long hopsize = 0;
    std::vector<float> inputBuffer;
    std::vector<float> window;
    std::vector<float> real;
    std::vector<float> imag;
    std::vector<float> amplitudeFrame;
    std::vector<float> phaseFrame;
    
    std::vector<std::vector<float>> spectrogram;
    std::vector<std::vector<float>> phaseogram;
    
    std::vector<std::vector<float>> cepstrum;
};

#endif /* defined(__SpeechSynthesizer__FFT__) */
