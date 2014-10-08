//
//  Sampler.cpp
//  FuChair
//
//  Created by Danny van Swieten on 10/7/14.
//
//

#include "APAudioSampler.h"

Sampler::Sampler(APAudioMainFrame* mainFrame ,APAudioFileManager* fileManager): APAudioModule(mainFrame)
{
    _fileManager = fileManager;
}

void Sampler::onNoteOn(int noteOn, float velocity, int channel)
{
    for(auto& description: _fileDescriptions)
        if(description.listensToNote(noteOn) && description.listensToChannel(channel))
        {
            APAudioSamplerVoice* voice = findFreeVoice();
            
            if(voice == nullptr)
            {
                voice = new APAudioSamplerVoice();
                voice->setFileToPlay(_fileManager->getFile(description.getID()));
                voice->play();
                _activeVoices.emplace_back(voice);
            }
            else
            {
                voice->setFileToPlay(_fileManager->getFile(description.getID()));
                voice->play();
            }
        }
}

Sampler::~Sampler()
{
    
}

APAudioSamplerVoice* Sampler::findFreeVoice()
{
    for(auto& voice: _activeVoices)
    {
        if(!voice->isPlaying())
            return voice;
    }
    return nullptr;
}

void Sampler::renderBlock(SampleBuffer output)
{
    memset(outputBuffer.data(), 0, sizeof(Sample)*getBufferSize());
    
    for(auto& voice: _activeVoices)
        if(voice->isPlaying())
            for(auto i = 0; i < getBufferSize(); i++)
                output[i] += voice->tick();
}

void Sampler::loadFile(std::string fileToLoad, int noteToListenTo, int channelToListenTo)
{
    APAudioSoundDescription description;
    description.setNoteToListenTo(noteToListenTo);
    description.setID(fileToLoad);
    description.setChannelToListenTo(channelToListenTo);
    _fileDescriptions.emplace_back(description);
    _fileManager->loadFile(fileToLoad);
}

void Sampler::calculateBuffer()
{
    renderBlock(outputBuffer.data());
}