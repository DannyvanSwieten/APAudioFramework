//
//  APAudioFileManager.
//  APAudioEngine
//
//  Created by Danny van Swieten on 07-05-14.
//  Copyright (c) 2014 Danny van Swieten. All rights reserved.
//

#include "APAudioFileManager.h"

APAudioFileManager::APAudioFileManager()
{
    setupMonoStreamFormat();
    setupStereoStreamFormat();
    getAvailableSoundFileLibraries();

}

AudioFile* APAudioFileManager::findFile(std::string fileName)
{
    for(auto& file : audioFiles)
    {
        if (file.name == fileName)
        {
            return &file;
        }
    }
    
    return nullptr;
}

OSStatus APAudioFileManager::getAvailableSoundFileLibraries()
{
    OSStatus error = noErr;
    NSError* result;
    
    NSString *bundlePathName            = [[NSBundle mainBundle] bundlePath];
    NSString *dataPathName              = [bundlePathName stringByAppendingPathComponent:@"Audio"];
    
    availableSoundFileLibraries   = [[NSFileManager defaultManager] contentsOfDirectoryAtPath: dataPathName
                                                                                         error: &result];
    
    soundFileLibrariesPathName    = dataPathName;
    
    return error;
}

OSStatus APAudioFileManager::getFileListForSoundFileLibrary(NSString* libraryName)
{
    OSStatus error = noErr;
    NSError* result;
    
    NSString* libraryToLoad = [soundFileLibrariesPathName stringByAppendingPathComponent: libraryName];
    
    NSArray* list               = [[NSFileManager defaultManager] contentsOfDirectoryAtPath: libraryToLoad
                                                                                      error: &result];
    
    if (result)
        //NSLog(@"%@", [result description]);
        NSLog(@"Audio File Path: %@", libraryToLoad);
    
    NSLog(@"Files found: %lu", (unsigned long)[list count]);
    
    audioFileList = [[NSMutableArray alloc]init];
    
    for (int i = 0; i < [list count]; i++)
    {
        NSString* file = [list[i] stringByDeletingPathExtension];
        
        [audioFileList addObject: file];
        
        NSLog(@"File %d : %@", i, audioFileList[i]);
    }
    
    return error;
}

OSStatus APAudioFileManager::loadFile(NSString* fileName, NSString* libraryName)
{
    OSStatus error = noErr;
    UInt16 fileIndex = 0;
    
    AudioFile fileObject = {};
    
    for (int files = 0 ; files < [audioFileList count]; files++)
    {
        NSString* string1 = [audioFileList objectAtIndex:files];
        
        if (![string1 compare: fileName])
        {
            fileIndex = files;
        }
    }
    
    NSString* libraryPath = [soundFileLibrariesPathName stringByAppendingPathComponent:libraryName];
    
    NSURL* file                 = [[NSBundle bundleWithPath: libraryPath]
                                   URLForResource:[audioFileList objectAtIndex:fileIndex]
                                   withExtension:@"wav"];
    
    NSString *fileString        = [file absoluteString];
    NSLog(@"Loading file: %@ ...", fileString);
    
    CFURLRef audioUrl = (__bridge CFURLRef)(file);
    
    ExtAudioFileRef audioFile   = 0;
    error                       = ExtAudioFileOpenURL (audioUrl,
                                                       &audioFile);
    
    if (error != noErr ||  audioFile == NULL)
        NSLog(@"Unable to open audio file with error code: %d", (int)error);
    
    UInt64 totalFramesInFile        = 0;   // total number of frames will be stored in this
    UInt32 frameLengthPropertySize  = sizeof (totalFramesInFile); //The size of one frame will be stored in this.
    // The product of the two will be the size of the total length of the file in frames.
    
    error =    ExtAudioFileGetProperty (audioFile,
                                        kExtAudioFileProperty_FileLengthFrames,
                                        &frameLengthPropertySize,
                                        &totalFramesInFile);
    
    if (error != noErr)
        NSLog(@"Unable to get total number of frames for audio file with error code: %d", (int)error);
    fileObject.name         = [fileName UTF8String];
    fileObject.numFrames    = (UInt64)totalFramesInFile;
    
    AudioStreamBasicDescription audioFileFormat = {0};
    UInt32 formatPropertySize = sizeof (audioFileFormat);
    
    error  =    ExtAudioFileGetProperty (audioFile,
                                         kExtAudioFileProperty_FileDataFormat,
                                         &formatPropertySize,
                                         &audioFileFormat);
    
    if (error != noErr)
        NSLog(@"Unable to get audio stream description for audio file with error code: %d", (int)error);
    
    UInt8 channelCount = audioFileFormat.mChannelsPerFrame;
    AudioStreamBasicDescription importFormat = {0};
    
    if (channelCount == 2)
    {
        fileObject.isStereo = YES;
        importFormat = stereoStreamDescription;
        
        fileObject.leftData   = (SampleBuffer)calloc(fileObject.numFrames, sizeof(Sample));
        fileObject.rightData  = (SampleBuffer)calloc(fileObject.numFrames, sizeof(Sample));
    }
    else
    {
        fileObject.isStereo = NO;
        importFormat = monoStreamDescription;
        
        fileObject.leftData   = (SampleBuffer)calloc(fileObject.numFrames, sizeof(Sample));
    }
    
    error  =    ExtAudioFileSetProperty (audioFile,
                                         kExtAudioFileProperty_ClientDataFormat,
                                         sizeof (importFormat),
                                         &importFormat);
    
    if (error != noErr)
        NSLog(@"Unable to set audio stream description for audio file with error code: %d", (int)error);
    
    // Allocate memory for the buffer list struct according to the number of
    //    channels it represents.
    
    AudioBufferList *bufferList;
    
    bufferList = (AudioBufferList *) malloc (sizeof (AudioBufferList) + sizeof (AudioBuffer) * (channelCount));
    
    if (NULL == bufferList)
    {
        NSLog (@"*** malloc failure for allocating bufferList memory");
        return -1;
    }
    
    // initialize the mBuffers member to 0
    AudioBuffer emptyBuffer = {0};
    
    if (channelCount)
    {
        for (int channel = 0; channel < channelCount; channel++)
        {
            bufferList->mBuffers[channel] = emptyBuffer;
            
            // initialize the mNumberBuffers member
            bufferList->mNumberBuffers = channelCount;
            
            // set up the AudioBuffer structs in the buffer list
            bufferList->mBuffers[0].mNumberChannels  = 1;
            bufferList->mBuffers[0].mDataByteSize    = (UInt32)totalFramesInFile * sizeof (Sample);
            bufferList->mBuffers[0].mData            = fileObject.leftData;
            
            if (2 == channelCount)
            {
                bufferList->mBuffers[1].mNumberChannels  = 1;
                bufferList->mBuffers[1].mDataByteSize    = (UInt32)totalFramesInFile * sizeof (Sample);
                bufferList->mBuffers[1].mData            = fileObject.rightData;
            }
        }
        
        UInt32 numberOfPacketsToRead = (UInt32)totalFramesInFile;
        
        error = ExtAudioFileRead (audioFile,
                                  &numberOfPacketsToRead,
                                  bufferList);
        
        if (error != noErr)
            NSLog(@"Unable to read samples from audio file with error code: %d", (int)error);
        
        // Dispose of the extended audio file object, which also
        //    closes the associated file.
        //ExtAudioFileDispose (audioFile);
        
        audioFiles.emplace_back(fileObject) ;
    }
    else
    {
        free(bufferList);
    }
    return error;
}

OSStatus APAudioFileManager::setupStereoStreamFormat()
{
    OSStatus result = noErr;
    
    NSLog(@"Configure stereo stream format...");
    
    UInt32 sampleSize = sizeof(Float32);
    
    stereoStreamDescription.mChannelsPerFrame  = 2;
    stereoStreamDescription.mBitsPerChannel    = 8 * sampleSize;
    stereoStreamDescription.mBytesPerFrame     = sampleSize;
    stereoStreamDescription.mBytesPerPacket    = sampleSize;
    stereoStreamDescription.mFramesPerPacket   = 1;
    stereoStreamDescription.mFormatID          = kAudioFormatLinearPCM;
    stereoStreamDescription.mFormatFlags       = kAudioFormatFlagsNativeFloatPacked | kAudioFormatFlagIsNonInterleaved;
    stereoStreamDescription.mSampleRate        = 44100;
    stereoStreamDescription.mReserved          = 0;
    
    NSLog(@"Done!");
    
    
    
    return result;
}

OSStatus APAudioFileManager::setupMonoStreamFormat()
{
    OSStatus result = noErr;
    
    NSLog(@"Configure mono stream format...");
    
    UInt32 sampleSize = sizeof(Float32);
    
    monoStreamDescription.mChannelsPerFrame    = 1;
    monoStreamDescription.mBitsPerChannel      = 8 * sampleSize;
    monoStreamDescription.mBytesPerFrame       = sampleSize;
    monoStreamDescription.mBytesPerPacket      = sampleSize;
    monoStreamDescription.mFramesPerPacket     = 1;
    monoStreamDescription.mFormatID            = kAudioFormatLinearPCM;
    monoStreamDescription.mFormatFlags         = kAudioFormatFlagsNativeFloatPacked | kAudioFormatFlagIsNonInterleaved;
    monoStreamDescription.mSampleRate          = 44100;
    monoStreamDescription.mReserved            = 0;
    
    NSLog(@"Done!");
    
    return result;
}