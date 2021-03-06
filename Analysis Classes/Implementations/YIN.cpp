//
//  YINAnalyser.cpp
//  FPTAnalyzer
//
//  Created by Danny van Swieten on 10/2/14.
//
//

#include "YIN.h"

YIN::YIN()
{

}

void YIN::init(int N)
{
    _N = N;
    _tau.resize(N/2);
    _threshold = 0.1;
}

YIN::~YIN()
{
    if(_window)
        delete[] _window;
}

void YIN::normalizedDifference()
{
    _tau[0] = 1.0;
    float sum = 0;
    for (auto i = 1; i < _N/2; i+= _downSample)
    {
        sum += _tau[i];
        if(sum != 0.0)
            _tau[i] *= (float)i / sum;
        else
            _tau[i] *= (float)i;
    }
}

int YIN::absoluteThreshold()
{
    int i = 0;
    for (i = 2; i < _N/2; i+= _downSample)
    {
        if(_tau[i] < _threshold)
        {
            while(i + 1 < _N/2 && _tau[i + 1] < _tau[i])
            {
                i++;
            }
            
            _probability = 1.0 - _tau[i];
            break;
        }
    }
    
    if(_tau[i] >= _threshold || i == _N/2)
    {
        _probability = 0;
        i = -1;
    }
    
    return i;
}

float YIN::analyze(float *input)
{
    squaredDifference(input);
    normalizedDifference();
    int tau = absoluteThreshold();
    if(tau != -1)
        return 44100.0 / tau;
    else
        return tau;
}