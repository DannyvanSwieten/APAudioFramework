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

class WaveFormComponent: public Component
{
public:
    
    WaveFormComponent(APAudioFileManager* manager);
    ~WaveFormComponent();
    
    void resized()override;
    void paint(Graphics& g)override;
    void mouseUp (const MouseEvent& event)override;
    void mouseDown(const MouseEvent& event)override;
    
private:
    
   APAudioFileManager* _fileManager;
};


#endif /* defined(__FPTAnalyzer__WaveFormComponent__) */
