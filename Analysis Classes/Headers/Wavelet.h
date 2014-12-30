//
//  Wavelet.h
//  FrameworkMaintenance
//
//  Created by Danny van Swieten on 12/11/14.
//  Copyright (c) 2014 Danny van Swieten. All rights reserved.
//

#ifndef __FrameworkMaintenance__Wavelet__
#define __FrameworkMaintenance__Wavelet__

#include "Utility.h"
#include <vector>

namespace APAudio
{
    namespace Analysis
    {
        class Wavelet
        {
        public:
            Wavelet(int period, WindowType t);
            ~Wavelet();
            
            std::vector<float> operator* (const std::vector<float> data)
            {
                float sum1 = 0;
                float sum2 = 0;
                
                std::vector<float> amplitudes;
                
                for(auto i = 0; i < data.size(); i += period)
                {
                    for (auto j = 0; j < period; j++)
                    {
                        sum1 += data[i + j] * real[j];
                        sum2 += data[i + j] * imag[j];
                    }
                    
                    amplitudes.emplace_back(sqrtf((sum1 * sum1) + (sum2 * sum2)));
                }
            
                return std::move(amplitudes);
            }
            
        private:
            
            int period = 0;
            
            std::vector<float> real;
            std::vector<float> imag;
            std::vector<float> window;
        };
    }
}

#endif /* defined(__FrameworkMaintenance__Wavelet__) */
