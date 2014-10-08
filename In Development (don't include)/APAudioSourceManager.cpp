    //
//  APAudioSourceManager.cpp
//  APA
//
//  Created by Danny van Swieten on 13-07-14.
//
//

#include "APAudioSourceManager.h"

APAudioSourceManager::APAudioSourceManager()
{
    formatManager.registerBasicFormats();
}

APAudioSourceManager::~APAudioSourceManager()
{
    
}

APAudioSoundDescription* APAudioSourceManager::loadFile()
{
    FileChooser loadFile("Select audio file",
                         File::getSpecialLocation(File::userHomeDirectory),
                         "*.wav");
    APAudioSoundDescription* desc = new APAudioSampleSound();
    
    if(loadFile.browseForFileToOpen())
    {
        File audioFile = loadFile.getResult();
        formatReader = formatManager.createReaderFor(audioFile);
        AudioSampleBuffer buffer;
        buffer.setSize(2, formatReader->lengthInSamples);
        formatReader->read(&buffer, 0, formatReader->lengthInSamples, 0, 1, 1);
        desc->setData(buffer);
        desc->setRange(36, 88);
        desc->setID(audioFile.getFileName());
        desc->setLength(formatReader->lengthInSamples);
    }
    
    return desc;
}