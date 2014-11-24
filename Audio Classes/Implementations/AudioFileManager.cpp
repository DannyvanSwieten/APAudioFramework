//
//  AudioFileManager2.cpp
//  AAnalyzer
//
//  Created by Danny van Swieten on 10/1/14.
//
//

#include "AudioFileManager.h"

namespace APAudio
{
    namespace Audio
    {

        AudioFileManager::AudioFileManager()
        {

        }

        AudioFileManager::~AudioFileManager()
        {

        }

        void AudioFileManager::loadFile(std::string path)
        {
            WaveFormatReader reader;
            _audioFiles.emplace_back(reader.read(path, true, true));
            _filesLoaded++;
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

        AudioFile& AudioFileManager::getFile(int index)
        {
            if(index >= _audioFiles.size())
                return emptyFile;
            else
                return _audioFiles[index];
        }

        int AudioFileManager::getNumberOfFiles()
        {
            return _filesLoaded;
        }

        void AudioFileManager::clearManager()
        {
            _audioFiles.clear();
        }
    }
}
