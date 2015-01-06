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

static inline void int16ToFloat(SInt16* intBuffer, float* floatBuffer, size_t size)
{
    for(auto i = 0; i < size; i++)
    {
        floatBuffer[i] = (float)intBuffer[i] / 32768.0f;
    }
}

static inline void floatToInt16(float* floatBuffer, SInt16* intBuffer, size_t size)
{
    for(auto i = 0; i < size; i++)
    {
        intBuffer[i] = (SInt16)floatBuffer[i] * 32767;
    }
}

static inline float scale(float oldValue, float oldMin, float oldMax, float newMin, float newMax)
{
    float newValue = (((oldValue - oldMin) * (newMax - newMin)) / (oldMax - oldMin)) + newMin;
    return newValue;
}

static inline void createWindow(WindowType t, float* output, unsigned long N)
{
    switch (t) {
        case HANNING:
            for (auto i = 0; i < N; i++)
            {
                output[i] = 0.5 * (1 - cos((2*M_PI * i) / N));
            }
            break;
            
        case BLACKMAN:
        {
            float a0=0.35875, a1=0.48829, a2=0.14128, a3=0.01168;
            
            for (auto i = 0; i < N; i++)
            {
                output[i] = a0-a1*cos(2*M_PI/N-1)+a2*cos(4*M_PI/N-1)-a3*cos(6*M_PI/N-1);
            }
        }
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
        max = std::max(fabs(max), fabs(input[i]));
    
    for(auto i = 0; i < size; i++)
        if(input[i] != 0.0)
            input[i] /= max;
        else
            input[i] = 0;
}

#endif
