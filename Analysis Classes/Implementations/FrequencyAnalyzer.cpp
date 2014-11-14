//
//  FrequencyAnalyzer.cpp
//  APAAnalyzer
//
//  Created by Danny van Swieten on 10/2/14.
//
//

#include "FrequencyAnalyzer.h"

FrequencyAnalyzer::FrequencyAnalyzer()
{

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
            {
                buffer[i] = input[position++];
                _prevSample = buffer[i];
            }
            else
                buffer[i] = 0;
        }
        
        if(position < 0) return;
        
        numberOfSamples-= windowSize;
        _result.emplace_back(yin.analyze(buffer));
    }
}

void FrequencyAnalyzer::init(int N)
{
    _N = N;
    yin.init(N);
}