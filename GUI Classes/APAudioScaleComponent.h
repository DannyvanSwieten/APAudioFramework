//
//  APAudioScaleComponent.h
//  FPTAnalyzer
//
//  Created by Danny van Swieten on 10/16/14.
//
//

#ifndef __FPTAnalyzer__APAudioScaleComponent__
#define __FPTAnalyzer__APAudioScaleComponent__

#include "../JuceLibraryCode/JuceHeader.h"

class APAudioScaleComponent: public Component
{
public:
    
    APAudioScaleComponent();
    ~APAudioScaleComponent();
    
    void resized() override final;
    void paint(Graphics& g) override final;
    void setValues(int max, int sampleRate);
    void setZoom(int zoom);
    
private:
    
    int _maxValue = 0;
    float _stepSize = 0;
    bool _hasAudio = 0;
    int _zoom = 1;
};

#endif /* defined(__FPTAnalyzer__APAudioScaleComponent__) */
