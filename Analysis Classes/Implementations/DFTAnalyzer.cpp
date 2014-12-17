//
//  DFTAnalyzer.cpp
//  DFT
//
//  Created by Danny van Swieten on 9/18/14.
//  Copyright (c) 2014 Danny van Swieten. All rights reserved.
//

#include "DFTAnalyzer.h"

using namespace std;

namespace APAudio
{
    namespace Analysis
    {

        DFTAnalyzer::DFTAnalyzer(unsigned int N, unsigned int overlap, WindowType t): AudioAnalyzer()
        {
            init(N, overlap, t);
        }

        DFTAnalyzer::~DFTAnalyzer()
        {
            
        }

        void DFTAnalyzer::init(unsigned int N, unsigned int overlap, WindowType t)
        {
            setN(N);
            setOverlap(overlap);
            setHopsize(1);
            _dft.init(N, overlap, N, t);
        }

        void DFTAnalyzer::readAndAnalyse(const float *input, long numberOfSamples)
        {
            unsigned long position = 0;
            float buffer[getWindowSize()];
            unsigned int windowSize = getWindowSize();
            unsigned int hopSize = getHopsize();
            
            _analysisResult.clear();
            
            while(numberOfSamples > 0)
            {
                for (auto i = 0; i < windowSize; i++)
                {
                    if(position < numberOfSamples - 1)
                        buffer[i] = input[position++];
                    else
                        buffer[i] = 0;
                }
                if (getOverlap() != 1)
                    position -= (windowSize - hopSize);

                numberOfSamples -= hopSize;
                _dft.calculateDFT(buffer);
                
                _analysisResult.emplace_back(_dft.getResult());
            }
        }

        void DFTAnalyzer::calculateAmplitudes()
        {
            getAmplitudes().clear();
            for(auto i = 0; i < _analysisResult.size(); i++)
            {
                vector<float> amplitudes;
                for (auto n = 0; n < _dft.getSize(); n++)
                    amplitudes.emplace_back( std::abs(_analysisResult[i][n])/((float)_dft.getSize()/2));
                
                normalize(amplitudes.data(), _dft.getSize());
                
                getAmplitudes().emplace_back(move(amplitudes));
            }
        }

        void DFTAnalyzer::generatePeakMap()
        {
            _peakMaps.clear();
            for(auto i = 0; i < getAmplitudes().size(); i++)
            {
                std::vector<int> peakMap;
                float* frame = getAmplitudes()[i].data();
                for(auto n = 1; n < _dft.getSize()-1;n++)
                {
                    if(frame[n] > frame[n-1] && frame[n] > frame[n+1])
                        peakMap.emplace_back(1);
                    else
                        peakMap.emplace_back(0);
                }
                
                _peakMaps.emplace_back(peakMap);
            }
        }

        void DFTAnalyzer::searchStableSinusoids()
        {
            for(auto i = 2; i < getAmplitudes().size(); i++)
            {
                int* frame = _peakMaps[i].data();
                int* frameDiv = _peakMaps[i-1].data();
                int* frameDiv2 = _peakMaps[i-2].data();
                for(auto n = 0; n < _dft.getSize();n++)
                {
                    if(frame[n] == 1 && frameDiv[n] == 1 && frameDiv2[n] == 1)
                        frame[n] = 1;
                    else
                        frame[n] = 0;
                }
            }
        }

        void DFTAnalyzer::calculatePhases()
        {
            for(auto i = 0; i < _analysisResult.size(); i++)
            {
                std::vector<float> phase;
                for(auto n = 0; n < _dft.getSize();n++)
                {
                    phase.emplace_back(std::arg(_analysisResult[i][n]));
                }
                getPhases().emplace_back(phase);
            }
            
            for(auto i = 1; i < _analysisResult.size(); i++)
            {
                for(auto n = 0; n < _dft.getSize();n++)
                {
                    while(getPhases()[i][n] - getPhases()[i-1][n] > M_PI)
                        getPhases()[i][n] -= 2*M_PI;
                    while(getPhases()[i][n] - getPhases()[i-1][n] < -M_PI)
                        getPhases()[i][n] += 2*M_PI;
                }
            }
        }

        void DFTAnalyzer::calculateLogSpectrum()
        {
            for(auto& amplitudes: getAmplitudes())
            {
                std::vector<float> logAmp;
                for (auto i = 0; i < _dft.getSize(); i++)
                {
                    amplitudes[i] = 20 * log10(amplitudes[i]);
                }
                normalize(amplitudes.data(), _dft.getSize());
            }
        }

        void DFTAnalyzer::calculateInstantFrequencies()
        {
            for(auto i = 1; i < getPhases().size(); i++)
            {
                std::vector<float> freq;
                for(auto j = 0; j < _dft.getSize(); j++)
                {
                    float wrappedPhaseDetermination = phaseWrap((getPhases()[i][j] - getPhases()[i-1][j]) - (getHopsize() * (_freqPerBin) * j), M_PI);
                    freq.emplace_back((_freqPerBin * j) + (wrappedPhaseDetermination/getHopsize()));
                }
                _trueFrequencies.emplace_back(freq);
            }
        }

        void DFTAnalyzer::calculateSpectralFlux()
        {
            for (auto i = 0; i < getAmplitudes().size()-2; i++)
            {
                float amplitude1 = 0;
                float amplitude2 = 0;
                float difference = 0;
                float result = 0;
                for (auto j = 0; j < _dft.getSize()/2; j++)
                {
                    amplitude1 = getAmplitudes()[i][j];
                    amplitude2 = getAmplitudes()[i + 1][j];
                    difference = amplitude2 - amplitude1;
                    
                    if(difference > 0)
                        result += difference;
                    else
                        result += 0;
                }
                
                _spectralFlux.emplace_back(result);
            }
            
            normalize(_spectralFlux.data(), _dft.getSize());
        }

        void DFTAnalyzer::inverse()
        {
            for(auto i = 0; i < getAmplitudes().size(); i++)
            {
                std::vector<std::complex<float>> _inverseVector;
                std::vector<float> _synthesisVector;
                _synthesisVector.resize(getWindowSize());
                
                for (auto j = 0; j < getWindowSize(); j++)
                {
                    _inverseVector.emplace_back(std::complex<float>(cos(getPhases()[i][j]), sin(getPhases()[i][j]))*getAmplitudes()[i][j]);
                }
                
                _dft.calculateIDFT(_synthesisVector, _inverseVector);
                _resynthesisMatrix.emplace_back(_synthesisVector);
            }
        }

        void DFTAnalyzer::calculatePitch()
        {
            
        }
    }
}