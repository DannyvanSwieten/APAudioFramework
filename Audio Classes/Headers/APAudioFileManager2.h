//
//  APAudioFileManager2.h
//  APAAnalyzer
//
//  Created by Danny van Swieten on 10/1/14.
//
//

#ifndef __APAAnalyzer__APAudioFileManager2__
#define __APAAnalyzer__APAudioFileManager2__

#include "APAudioFile.h"
#include <vector>
#include <memory>

class APAudioFileManager
{
public:
    APAudioFileManager();
    ~APAudioFileManager();
    
    void loadFile(APAudioFile file);
    void loadFile(File fileToLoad);
    void loadFile(std::string fileToLoad);
    void loadFiles();
    
    APAudioFile* getFile(std::string name);
    APAudioFile* getFile(int index);
    void clearManager();
    int getNumberOfFiles();
    
private:
    
    std::vector<std::unique_ptr<APAudioFile>> _audioFiles;
    std::unique_ptr<AudioFormatManager> _formatManager;
    int _filesLoaded = 0;
};

#endif /* defined(__APAAnalyzer__APAudioFileManager2__) */
