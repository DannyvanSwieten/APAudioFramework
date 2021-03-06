//
//  YINAnalyser.h
//  FPTAnalyzer
//
//  Created by Danny van Swieten on 10/2/14.
//
//

#ifndef __FPTAnalyzer__YINAnalyser__
#define __FPTAnalyzer__YINAnalyser__

#include <vector>
#include "Utility.h"
#include <iostream>

class YIN
{
public:
    YIN();
    ~YIN();
    
    void init(int N);
    void process(float* audioData, int numSamples);
    float analyze(float* input);
private:
    
    inline void squaredDifference(float *input)
    {
        _tau.clear();
        float delta = 0;
        for (auto tau = 0; tau < _N/2; tau++)
        {
            _tau[tau] = 0;
            for (auto i = 0; i < _N/2; i+= _downSample)
            {
                delta = input[i] - input[i + tau];
                _tau[tau] += delta * delta;
            }
        }
    }

    void normalizedDifference();
    int absoluteThreshold();
    
    int _N = 0;
    std::vector<float> _tau;
    float _threshold = 0;
    float _probability = 0;
    float* _window = nullptr;
    int _downSample = 1;
};

#endif /* defined(__FPTAnalyzer__YINAnalyser__) */
