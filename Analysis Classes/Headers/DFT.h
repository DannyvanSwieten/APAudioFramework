//
//  DFT.h
//  DFT
//
//  Created by Danny van Swieten on 9/11/14.
//  Copyright (c) 2014 Danny van Swieten. All rights reserved.
//
/*
 This is a class that calculates the Discrete Fourier Transform (DFT) of a signal.
 This is NOT a Fast Fourier Transform, because it is created only to analyse signals for acedamic purposes and not to be used for real time processes.
 It is a very straight forward aproach represented as a matrix vector multiplication. (Matrix N*K where K == N, multiplied by a vector of size N).
 Scaling is handled by the algorithm so Inverse Fourier Transorm gives a perfect reconstruction of the original signal if and only if the phases are left unchanged.
 For use:   1 - create DFT object.
            2 - call init method.
            3 - call calculateDFT method.
*/

#ifndef __DFT__DFT__
#define __DFT__DFT__

#include <vector>
#include <complex>
#include "Utility.h"

class DFT
{
public:
    DFT();
    ~DFT();
    unsigned int getSize(){return _N;};
    std::vector<std::complex<float>> getResult(){return _DFTResult;};
    void init(unsigned int N, WindowType t);
    void calculateDFT(float* input);
    void calculateIDFT(float* input);
    void createWindow(WindowType t);
    
private:
    
    void calculateTwiddleFactors();
    
    unsigned int  _N;
    std::vector<std::complex<float>> _DFTBuffer;
    std::vector<std::complex<float>> _DFTResult;
    std::vector<std::vector<std::complex<float>>> _twiddleFactors;
    std::vector<std::vector<std::complex<float>>> _inverseTwiddleFactors;
    float* _window = nullptr;
};

#endif /* defined(__DFT__DFT__) */
