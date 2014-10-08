//
//  FastWavelet.h
//  DFT
//
//  Created by Danny van Swieten on 9/22/14.
//  Copyright (c) 2014 Danny van Swieten. All rights reserved.
//

#ifndef __DFT__FastWavelet__
#define __DFT__FastWavelet__

#include <math.h>
#include <vector>

class FastWavelet
{
public:
    FastWavelet();
    
    void process(float* input ,unsigned int N,  int direction);
    
private:
    int _N;
    std::vector<std::vector<float>> _result;
    void forward(float* input ,unsigned int N);
    void backward(float* input ,unsigned int N);
};

#endif /* defined(__DFT__FastWavelet__) */
