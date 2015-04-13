//
//  ExternalAudioObject.h
//  DAW
//
//  Created by Danny van Swieten on 4/13/15.
//
//

#ifndef __DAW__ExternalAudioObject__
#define __DAW__ExternalAudioObject__

#include "AudioObject.h"
#include <dlfcn.h>
#include <functional>
#include <iostream>

class ExternalAudioObject
{
public:
    ExternalAudioObject(std::string path);
    std::unique_ptr<AudioObject> getExternal();
    
private:
    
    std::unique_ptr<AudioObject> external;
    std::function<AudioObject*()> create;
};
#endif /* defined(__DAW__ExternalAudioObject__) */
