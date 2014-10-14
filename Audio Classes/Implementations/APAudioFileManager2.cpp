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
    _formatManager = std::make_unique<AudioFormatManager>();
    _formatManager->registerBasicFormats();
}

APAudioFileManager::~APAudioFileManager()
{

}

void APAudioFileManager::loadFile(File fileToLoad)
{
    AudioFormatReader* formatReader = _formatManager->createReaderFor(fileToLoad);
    
    int numChannels = formatReader->numChannels;
    int numSamples = formatReader->lengthInSamples;
    
    auto file = std::make_unique<APAudioFile>();
    AudioSampleBuffer buffer;
    buffer.setSize(numChannels, numSamples);
    
    formatReader->read(&buffer, 0, numSamples, 0, true, true);
    file->setAudio(buffer);
    file->setFileName(fileToLoad.getFileName());
    file->setNumChannels(numChannels);
    file->setNumSamples(numSamples);
    
    _audioFiles.emplace_back(std::move(file));
    _filesLoaded++;
    
    delete formatReader;
}

void APAudioFileManager::loadFile(std::string fileToLoad)
{
    String newFile = fileToLoad;
    File file(File::getSpecialLocation(File::currentApplicationFile).getChildFile(newFile));
    
    std::cout<<file.getFullPathName()<<std::endl;
    
    AudioFormatReader* formatReader = _formatManager->createReaderFor(file);
    
    int numChannels = formatReader->numChannels;
    int numSamples = formatReader->lengthInSamples;
    
    auto audioFile = std::make_unique<APAudioFile>();
    AudioSampleBuffer buffer;
    buffer.setSize(numChannels, numSamples);
    
    formatReader->read(&buffer, 0, numSamples, 0, true, true);
    audioFile->setFileName(fileToLoad);
    audioFile->setNumChannels(numChannels);
    audioFile->setNumSamples(numSamples);
    audioFile->setAudio(buffer);
    
    _audioFiles.emplace_back(std::move(audioFile));
    _filesLoaded++;
    
    delete formatReader;
}

APAudioFile* APAudioFileManager::getFile(juce::String name)
{
    for(auto& file: _audioFiles)
    {
        if (file->getName() == name)
            return file.get();
    }

    return nullptr;
}

APAudioFile* APAudioFileManager::getFile(int index)
{
    return _audioFiles[index].get();
}

int APAudioFileManager::getNumberOfFiles()
{
    return _filesLoaded;
}

void APAudioFileManager::clearManager()
{
    _audioFiles.clear();
}

