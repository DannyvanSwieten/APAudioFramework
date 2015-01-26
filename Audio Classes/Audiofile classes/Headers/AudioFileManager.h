//
//  APAudioFileManager2.h
//  APAAnalyzer
//
//  Created by Danny van Swieten on 10/1/14.
//
//

#ifndef __APAAnalyzer__APAudioFileManager2__
#define __APAAnalyzer__APAudioFileManager2__

#include "WaveFormatReader.h"
#include <vector>
#include <memory>

namespace APAudio
{
    class AudioFileManager
    {
    public:
        AudioFileManager();
        ~AudioFileManager();
        
        void loadFile(AudioFile file);
        void loadFile(std::string path);
        void loadFiles(std::vector<std::string> paths);
        
        AudioFile& getFile(std::string name);
        AudioFile& getFile(long index);
        void clearManager();
        long getNumberOfFiles();
        
    private:
        
        std::vector<AudioFile> _audioFiles;
        AudioFile emptyFile;
        long _filesLoaded = 0;
    };
}

struct AppleAudioFileManager
{
    APAudio::AudioFileManager fileManager;
};

#endif /* defined(__APAAnalyzer__APAudioFileManager2__) */
