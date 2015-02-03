//
//  VSTHost.cpp
//  VSTHost
//
//  Created by Danny van Swieten on 1/29/15.
//  Copyright (c) 2015 Danny van Swieten. All rights reserved.
//

#include "Vst.h"

extern "C"
{
    VstIntPtr VSTCALLBACK hostCallback(AEffect* effect,
                                       VstInt32 opcode,
                                       VstInt32 index,
                                       VstIntPtr value,
                                       void* ptr,
                                       float opt);
}

typedef AEffect *(*vstPluginFuncPtr)(audioMasterCallback host);
// Plugin's dispatcher function
typedef VstIntPtr (*dispatcherFuncPtr)(AEffect *effect, VstInt32 opCode, VstInt32 index, VstInt32 value, void *ptr, float opt);
// Plugin's getParameter() method
typedef float (*getParameterFuncPtr)(AEffect *effect, VstInt32 index);
// Plugin's setParameter() method
typedef void (*setParameterFuncPtr)(AEffect *effect, VstInt32 index, float value);
// Plugin's processEvents() method
typedef VstInt32 (*processEventsFuncPtr)(VstEvents *events);
// Plugin's process() method
typedef void (*processFuncPtr)(AEffect *effect, float **inputs, float **outputs, VstInt32 sampleFrames);

VstIntPtr VSTCALLBACK hostCallback(AEffect* effect,
                                   VstInt32 opcode,
                                   VstInt32 index,
                                   VstIntPtr value,
                                   void* ptr,
                                   float opt)
{
    switch(opcode)
    {
        case audioMasterVersion:
        {
            return 2400;
        }
            
        case audioMasterIdle:
        {
            effect->dispatcher(effect, effEditIdle, 0, 0, 0, 0);
            break;
        }
            
        case audioMasterGetVendorString:
        {
            effect->dispatcher(effect, effGetVendorString, 0, 0, ptr, 0);
            std::cout<<"Manufacturer: "<<(char*)ptr<<std::endl;
            break;
        }
            
        case audioMasterGetProductString:
        {
            effect->dispatcher(effect, effGetEffectName, 0, 0, ptr, 0.0f);;
            std::cout<<(char*)ptr<<std::endl;
            break;
        }
            
        case audioMasterGetVendorVersion:
        {
            std::cout<<"Version: "<<effect->dispatcher(effect, effGetVendorVersion, 0, 0, ptr, 0)<<std::endl;
            break;
        }
            
        default:
            std::cout<<"Plugin requested value of opcode: "<<opcode<<std::endl;
            break;
    }
    return 0;
}

Vst::Vst(std::string pathOnDisk)
{
    loadPlugin(pathOnDisk);
}

std::vector<std::string> Vst::getPluginList()
{
    std::vector<std::string> plugins;
    std::string path = "/Library/Audio/Plug-Ins/VST";
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir (path.c_str())) != NULL)
    {
        /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != NULL)
        {
            plugins.emplace_back(std::string(ent->d_name));
        }
        closedir (dir);
    }
    else
    {
        /* could not open directory */
        perror ("");
    }
    
    return plugins;
}

int Vst::loadPlugin(std::string pathOnDisk)
{
    int error = 0;
    
    plugin = nullptr;
    
    CFStringRef pluginPathReference = CFStringCreateWithCString(nullptr, pathOnDisk.c_str(), kCFStringEncodingASCII);
    CFURLRef bundleUrl = CFURLCreateWithFileSystemPath(kCFAllocatorDefault, pluginPathReference, kCFURLPOSIXPathStyle, true);
    
    if(bundleUrl == nullptr)
    {
        std::cout<<"Could't find reference to VST URL. It might not exist, or the path is wrong."<<std::endl;
        return -1;
    }
    
    CFBundleRef bundle = CFBundleCreate(kCFAllocatorDefault, bundleUrl);
    if(bundle == nullptr)
    {
        std::cout<<"Couldn't create VST Bundle reference. It might not be a VST, or corrupted"<<std::endl;
        CFRelease(bundleUrl);
        CFRelease(bundle);
        return -1;
    }
    
    VSTPlugin = (vstPluginFuncPtr)CFBundleGetFunctionPointerForName(bundle, CFSTR("VSTPluginMain"));
    
    plugin = VSTPlugin(hostCallback);
    
    if(plugin == nullptr)
    {
        std::cout<<"Couldn't create VST Main Entry Point"<<std::endl;
        CFBundleUnloadExecutable(bundle);
        CFRelease(bundle);
        return -1;
    }
    
    CFRelease(pluginPathReference);
    CFRelease(bundleUrl);
    
    error = configureCallbacks();
    error = startPlugin();
    
    return error;
}

int Vst::configureCallbacks()
{
    if(plugin->magic != kEffectMagic)
    {
        std::cout<<"Plugin's magic number is bad"<<std::endl;
        return -1;
    }
    
    setParameter = plugin->setParameter = (setParameterFuncPtr)plugin->setParameter;
    getParameter = plugin->getParameter = (getParameterFuncPtr)plugin->getParameter;
    process = plugin->processReplacing = (processFuncPtr)plugin->processReplacing;
    dispatcher = (dispatcherFuncPtr)plugin->dispatcher;
    
    return 0;
}

int Vst::startPlugin()
{
    int error = 0;
    
    dispatcher(plugin, effOpen, 0, 0, NULL, 0.0f);
    char name[64];
    dispatcher(plugin, effGetEffectName, 0, 0, name, 0.0f);
    std::cout<<"Product Name: "<<name<<std::endl;
    std::cout<<"Number of Programs: "<<plugin->numPrograms<<std::endl;
    std::cout<<"Number of input Channels: "<<plugin->numInputs<<std::endl;
    std::cout<<"Number of output Channels: "<<plugin->numOutputs<<std::endl;
    std::cout<<"Number of Parameters: "<<plugin->numParams<<std::endl;
    
    
    // Set some default properties
    float sampleRate = 44100.0f;
    dispatcher(plugin, effSetSampleRate, 0, 0, NULL, sampleRate);
    int blocksize = 512;
    dispatcher(plugin, effSetBlockSize, 0, blocksize, NULL, 0.0f);
    
    return error;
}