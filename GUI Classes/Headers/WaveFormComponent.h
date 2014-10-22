//
//  WaveFormComponent.h
//  FPTAnalyzer
//
//  Created by Danny van Swieten on 9/30/14.
//
//

#ifndef __FPTAnalyzer__WaveFormComponent__
#define __FPTAnalyzer__WaveFormComponent__

#include "../JuceLibraryCode/JuceHeader.h"

#include "APAudioFileManager2.h"
#include "APAudioScaleComponent.h"

class WaveFormComponent: public Component
{
public:
    
    WaveFormComponent(APAudioFileManager* manager);
    ~WaveFormComponent();
    
    void resized()override;
    void paint(Graphics& g)override;
    void mouseUp (const MouseEvent& event)override;
    void mouseDown(const MouseEvent& event)override;
    
    void loadData(APAudioFile* file);
    void fillPath();
    
private:
    
    APAudioFile* _file = nullptr;
    Path _drawPath;
    APAudioFileManager* _fileManager = nullptr;
    int _step = 0;
    int _zoom = 1;
    
    std::unique_ptr<APAudioScaleComponent> _timeScale;
};


#endif /* defined(__FPTAnalyzer__WaveFormComponent__) */
