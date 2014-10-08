//
//  Utility.h
//  DFT
//
//  Created by Danny van Swieten on 9/18/14.
//  Copyright (c) 2014 Danny van Swieten. All rights reserved.
//

#ifndef DFT_Utility_h
#define DFT_Utility_h

#include <math.h>
#include <algorithm>

enum WindowType
{
    HANNING,
    HAMMING,
    BLACKMAN
};

static inline void createWindow(WindowType t, float* output, unsigned int N)
{
    switch (t) {
        case HANNING:
            for (auto i = 0; i < N; i++)
            {
                output[i] = 0.5 * (1 - cos((2*M_PI * i) / N));
            }
            break;
            
        default:
            break;
    }
}

static inline float phaseWrap(float x, float d)
{
    // Optimize this ###
    float d2 = 2*d;
    float y = fmod(x, d2);
    
    return (y>d) ? (y-d2) : ((y<-d) ? (y+d2) : (y));
}

static inline void normalize(float* input, int size)
{
    float max = 0.0;
    
    for(auto i = 0; i < size; i++)
        max = std::max(max, input[i]);
    
    for(auto i = 0; i < size; i++)
        if(input[i] != 0.0)
            input[i] /= max;
}

#endif
