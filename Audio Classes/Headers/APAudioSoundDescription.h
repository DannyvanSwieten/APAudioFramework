//
//  APSoundDescription.h
//  FuChair
//
//  Created by Danny van Swieten on 10/7/14.
//
//

#ifndef __FuChair__APSoundDescription__
#define __FuChair__APSoundDescription__

#include <string>

class APAudioSoundDescription
{
public:
    
    APAudioSoundDescription();
    bool listensToNote(int note);
    bool listensToChannel(int channel);
    std::string getID();
    
    void setNoteToListenTo(int note);
    void setChannelToListenTo(int channel);
    void setID(std::string ID);
private:
    
    std::string _ID;
    int _noteToListenTo = 0;
    int _channelToListenTo = 0;
};

#endif /* defined(__FuChair__APSoundDescription__) */
