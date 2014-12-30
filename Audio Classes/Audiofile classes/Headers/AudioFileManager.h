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
    namespace Audio
    {

        class AudioFileManager
        {
        public:
            AudioFileManager();
            ~AudioFileManager();
            
            void loadFile(AudioFile file);
            void loadFile(std::string path);
            
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
}

struct AppleAudioFileManager
{
    APAudio::Audio::AudioFileManager fileManager;
};

#endif /* defined(__APAAnalyzer__APAudioFileManager2__) */
