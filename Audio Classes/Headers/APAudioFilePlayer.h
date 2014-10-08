//
//  APAudioStreamPlayer.h
//  FuChair
//
//  Created by Danny van Swieten on 10/7/14.
//
//

#ifndef FuChair_APAudioStreamPlayer_h
#define FuChair_APAudioStreamPlayer_h

#include "APAudioFile.h"

class APAudioFilePlayer
{
public:
    
    APAudioFilePlayer();
    ~APAudioFilePlayer();
    
    float play(APAudioFile* file, int channel, float speed);
    
private:
    
    int _position;
};

#endif
