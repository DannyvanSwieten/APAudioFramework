//
//  Wavelet.cpp
//  FrameworkMaintenance
//
//  Created by Danny van Swieten on 12/11/14.
//  Copyright (c) 2014 Danny van Swieten. All rights reserved.
//

#include "Wavelet.h"

namespace APAudio
{
    namespace Analysis
    {
        Wavelet::Wavelet(int period, WindowType t)
        {
            real.resize(period);
            imag.resize(period);
            
            window.resize(period);
            
            this->period = period;
            
            createWindow(t, window.data(), period);
            
            for (auto i = 0; i < period; i++)
            {
                real[i] = sinf(2 * M_PI / period * i) * window[i];
                imag[i] = cosf(2 * M_PI / period * i) * window[i];
            }
        }
        
        Wavelet::~Wavelet()
        {
            
        }
    }
}