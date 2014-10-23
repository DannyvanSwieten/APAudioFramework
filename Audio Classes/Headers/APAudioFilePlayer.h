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
    
    float play();
    void setPlay();
    void setFile(APAudioFile* file);
private:
    
    APAudioFile* _file = nullptr;
    int _position = 0;
    bool _playing = 0;
};

#endif
