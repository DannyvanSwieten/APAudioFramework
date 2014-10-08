//
//  APAudioFileManager2.cpp
//  APAAnalyzer
//
//  Created by Danny van Swieten on 10/1/14.
//
//

#include "APAudioFileManager2.h"

APAudioFileManager::APAudioFileManager()
{
    formatManager = new AudioFormatManager();
    formatManager->registerBasicFormats();
}

APAudioFileManager::~APAudioFileManager()
{

}

void APAudioFileManager::loadFile(File fileToLoad)
{
    AudioFormatReader* formatReader = formatManager->createReaderFor(fileToLoad);
    
    int numChannels = formatReader->numChannels;
    int numSamples = formatReader->lengthInSamples;
    
    APAudioFile* file = new APAudioFile();
    AudioSampleBuffer buffer;
    buffer.setSize(numChannels, numSamples);
    
    formatReader->read(&buffer, 0, numSamples, 0, true, true);
    file->setAudio(buffer);
    file->setFileName(fileToLoad.getFileName());
    file->setNumChannels(numChannels);
    file->setNumSamples(numSamples);
    
    _audioFiles.emplace_back(file);
    _filesLoaded++;
    
//    delete formatReader;
}

void APAudioFileManager::loadFile(std::string fileToLoad)
{
    String newFile = fileToLoad;
    File file(File::getSpecialLocation(File::currentApplicationFile).getChildFile(newFile));
    
    std::cout<<file.getFullPathName()<<std::endl;
    
    AudioFormatReader* formatReader = formatManager->createReaderFor(file);
    
    int numChannels = formatReader->numChannels;
    int numSamples = formatReader->lengthInSamples;
    
    APAudioFile* audioFile = new APAudioFile;
    AudioSampleBuffer buffer;
    buffer.setSize(numChannels, numSamples);
    
    formatReader->read(&buffer, 0, numSamples, 0, true, true);
    audioFile->setFileName(fileToLoad);
    audioFile->setNumChannels(numChannels);
    audioFile->setNumSamples(numSamples);
    audioFile->setAudio(buffer);
    
    _audioFiles.emplace_back(audioFile);
    _filesLoaded++;
    
//    delete formatReader;
}

APAudioFile* APAudioFileManager::getFile(juce::String name)
{
    for(auto& file: _audioFiles)
    {
        if (file->getName() == name)
            return file;
    }

    return nullptr;
}

APAudioFile* APAudioFileManager::getFile(int index)
{
    return _audioFiles[index];
}

int APAudioFileManager::getNumberOfFiles()
{
    return _filesLoaded;
}

void APAudioFileManager::clearManager()
{
    _audioFiles.clear();
}

