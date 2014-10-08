//
//  APAudioFileManager.h
//  APAudioEngine
//
//  Created by Danny van Swieten on 07-05-14.
//  Copyright (c) 2014 Danny van Swieten. All rights reserved.
//

#ifndef __APAudioEngine__APAudioFileManager__
#define __APAudioEngine__APAudioFileManager__

#include "APAudioProcessor.h"

struct AudioFile
{
    SampleBuffer    leftData;
    SampleBuffer    rightData;
    UInt64          numFrames;
    bool            isStereo;
    std::string     name;
};

class APAudioFileManager
{
public:
    
    APAudioFileManager();
    OSStatus getAvailableSoundFileLibraries();
    OSStatus getFileListForSoundFileLibrary(NSString* libraryName);
    OSStatus loadFile(NSString* fileName, NSString* libraryName);
    OSStatus setupMonoStreamFormat();
    OSStatus setupStereoStreamFormat();
    
    AudioFile* findFile(std::string fileName);
    
private:
    
    NSString*               soundFileLibrariesPathName;
    NSArray*                availableSoundFileLibraries;
    NSMutableArray*         soundFileLibraries;
    NSMutableArray*         audioFileList;

    AudioStreamBasicDescription     stereoStreamDescription;

    AudioStreamBasicDescription     monoStreamDescription;
    
    std::vector<AudioFile>               audioFiles;
};

#endif /* defined(__APAudioEngine__APAudioFileManager__) */
