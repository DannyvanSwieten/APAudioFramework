//
//  APAudioSequencer.h
//  APA
//
//  Created by Danny van Swieten on 17-07-14.
//
//

#ifndef __APA__APAudioSequencer__
#define __APA__APAudioSequencer__

#include "../JuceLibraryCode/JuceHeader.h"
#include "APAEvent.h"
#include "APAScheduler.h"
#include <vector>

class APAudioSequencer
{
public:
    APAudioSequencer(APAScheduler* scheduler);
    virtual ~APAudioSequencer() = 0;
    
    void play();
    void stop();
    void pause();
    void update(unsigned int time);
    using EventFuntion = std::function<void()>;
    void addEvent(unsigned long int timeStamp, EventFuntion function);
    
private:
    
    APAScheduler* _scheduler;
    std::vector<APAEvent> _events;
    unsigned long int _currentTime;
    bool _stop;
    bool _pause;
    bool _play;
};
#endif /* defined(__APA__APAudioSequencer__) */
