//
//  VSTHost.h
//  VSTHost
//
//  Created by Danny van Swieten on 1/29/15.
//  Copyright (c) 2015 Danny van Swieten. All rights reserved.
//

#ifndef __VSTHost__VSTHost__
#define __VSTHost__VSTHost__

#include <aeffectx.h>
#include <aeffect.h>
#include <functional>
#include <string>
#include <memory>
#include <Carbon/Carbon.h>
#include <iostream>
#include <vector>
#include <string>
#include <dirent.h>

class Vst
{
public:
    Vst(std::string pathOnDisk);
    static std::vector<std::string> getPluginList();
    int configureCallbacks();
    int startPlugin();
    
    AEffect* plugin;
    
    std::function<AEffect*(audioMasterCallback host)> VSTPlugin;
    std::function<VstIntPtr(AEffect* effect, VstInt32 opcode, VstInt32 index, VstInt32 value, void* ptr, float opt)> dispatcher;
    std::function<float(AEffect* effect, VstInt32 index)> getParameter;
    std::function<void(AEffect* effect, VstInt32 index, float value)> setParameter;
    std::function<VstInt32(VstEvents* events)> processEvents;
    std::function<void(AEffect* effect, float** inputs, float** outputs, VstInt32 numFrames)> process;
    
private:
    
    int loadPlugin(std::string pathOnDisk);
};

#endif /* defined(__VSTHost__VSTHost__) */
