//
//  FastWavelet.cpp
//  DFT
//
//  Created by Danny van Swieten on 9/22/14.
//  Copyright (c) 2014 Danny van Swieten. All rights reserved.
//

#include "FastWavelet.h"

FastWavelet::FastWavelet()
{
    
}

void FastWavelet::process(float* input ,unsigned int N, int direction)
{
    if(direction)
        forward(input, N);
    else
        backward(input, N);
}

void FastWavelet::forward(float *input, unsigned int N)
{
    float a;
    float c;
    int i;
    int j;
    int k;
    int l;
    int m;
    
    
    i = 1;
    j = 2;
    m = N;
    
    for (l = N-1;  l >= 0;  l--)
    {
        printf ("l = %d \n", l);
        m /= 2;
        
        for (k = 0;  k < m;  k++)
        {
            a = (input[j*k] + input[j*k+i]) / 2.0;
            c = (input[j*k] - input[j*k+i]) / 2.0;
            input[j*k] = a;
            input[j*k+i] = c;
        }
        
        i *= 2;
        j *= 2;
    }
    std::vector<float> result;
    for(auto sample = 0; sample < N; sample++)
    {
        result.emplace_back(input[sample]);
    }
    _result.emplace_back(result);
}

void FastWavelet::backward(float *input, unsigned int N)
{
    float a0;
    float a1;
    int i;
    int j;
    int k;
    int l;
    int m;
    
    
    i = N>>1;
    j = 2*i;
    m = 1;
    
    for (l = 1;  l <= N;  l++)
    {
        printf ("l = %d \n", l);
        
        for (k = 0;  k < m;  k++)
        {
            a0 = input[j*k] + input[j*k+i];
            a1 = input[j*k] - input[j*k+i];
            input[j*k] = a0;
            input[j*k+i] = a1;
        }
        
        i /= 2;
        j /= 2;
        m *= 2;
    }
}