//
//  AudioSourceManager.h
//  SmartSampler
//
//  Created by Danny van Swieten on 1/9/15.
//
//

#ifndef __SmartSampler__AudioSourceManager__
#define __SmartSampler__AudioSourceManager__

#include <vector>
#include <string>
#include "AudioSourceDescription.h"
#include "InputStream.h"
#include "AudioFileManager.h"
#include "MidiUtility.h"
#include <memory>
#include "../JuceLibraryCode/JuceHeader.h"

class AudioSourcePackage
{
public:
    AudioSourcePackage();
    AudioSourcePackage(std::string id);
    void addSource(AudioSourceDescription source);
    std::vector<AudioSourceDescription>  getSources();
private:
    
    std::string ID;
    std::vector<AudioSourceDescription> audioSources;
};

class AudioSourceManager
{
public:
    AudioSourceManager(float sampleRate);
    void loadPackage(std::string pathOnDisk);
    std::vector<AudioSourceDescription> getAudioSources(int note, int velocity, int channel);
    AudioFileManager& getFileManager();
private:
    
    void parsePackage(var package);
    std::vector<std::string> swapNames(std::string pathOnDisk, std::vector<std::string> fileNames);
    AudioFileManager fileManager;
    std::vector<AudioSourcePackage> packages;
    float sampleRate;
};

#endif /* defined(__SmartSampler__AudioSourceManager__) */
