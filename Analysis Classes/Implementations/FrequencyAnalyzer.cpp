//
//  FrequencyAnalyzer.cpp
//  APAAnalyzer
//
//  Created by Danny van Swieten on 10/2/14.
//
//

#include "FrequencyAnalyzer.h"

FrequencyAnalyzer::FrequencyAnalyzer(int N)
{
    _N = N;
    yin.init(_N);
}
void FrequencyAnalyzer::readAndAnalyse(const float *input, long int numberOfSamples)
{
    long position = 0;
    float buffer[_N];
    unsigned int windowSize = _N;
    
    while(numberOfSamples > 0)
    {
        for (auto i = 0; i < windowSize; i++)
        {
            if(position < numberOfSamples)
                buffer[i] = input[position++];
            else
                buffer[i] = 0;
        }
        
        position -= (windowSize - 10);
        
        numberOfSamples -= 10;
        _result.emplace_back(yin.analyze(buffer));
    }
}