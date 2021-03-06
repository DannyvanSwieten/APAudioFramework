//
//  AudioFileManager2.cpp
//  AAnalyzer
//
//  Created by Danny van Swieten on 10/1/14.
//
//

#include "AudioFileManager.h"

AudioFileManager::AudioFileManager()
{

}

AudioFileManager::~AudioFileManager()
{

}

void AudioFileManager::loadFile(std::string path)
{
    auto namePos = path.find_last_of("/")+1;
    auto fileName = path.substr(namePos);
    for(auto& file: _audioFiles)
    {
        if(file.getName() == fileName)
            return;
    }
    
    WaveFormatReader reader;
    _audioFiles.emplace_back(reader.read(path, true, true));
    _filesLoaded++;
}

void AudioFileManager::loadFiles(std::vector<std::string> paths)
{
    for(auto path: paths)
        loadFile(path);
}

AudioFile& AudioFileManager::getFile(std::string name)
{
    for(auto& file: _audioFiles)
    {
        if (file.getName() == name)
            return file;
    }
    return emptyFile;
}

AudioFile& AudioFileManager::getFile(long index)
{
    if(index >= _audioFiles.size())
        return emptyFile;
    else
        return _audioFiles[index];
}

long AudioFileManager::getNumberOfFiles()
{
    return _filesLoaded;
}

void AudioFileManager::clearManager()
{
    _audioFiles.clear();
}
