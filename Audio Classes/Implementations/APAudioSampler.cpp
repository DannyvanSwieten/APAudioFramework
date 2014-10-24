//
//  APAudioSampler.cpp
//  FuChair
//
//  Created by Danny van Swieten on 10/7/14.
//
//

#include "APAudioSampler.h"

APAudioSampler::APAudioSampler(APAudioMainFrame* mainFrame ,APAudioFileManager* fileManager): APAudioModule(mainFrame)
{
    _fileManager = fileManager;
}

void APAudioSampler::onNoteOn(int noteOn, float velocity, int channel, bool repeat)
{
    for(auto& description: _fileDescriptions)
        if(description.listensToNote(noteOn) && description.listensToChannel(channel))
        {
            APAudioSamplerVoice* voice = findFreeVoice();
            
            if(voice == nullptr)
            {
                voice = new APAudioSamplerVoice();
                voice->setFileToPlay(_fileManager->getFile(description.getID()));
                voice->setNote(noteOn);
                voice->play(repeat);
                _activeVoices.emplace_back(voice);
                _numVoicesActive++;
            }
            else
            {
                voice->setFileToPlay(_fileManager->getFile(description.getID()));
                voice->setNote(noteOn);
                voice->play(repeat);
            }
        }
}

void APAudioSampler::onNoteOn(std::string file, float velocity, int channel, bool repeat)
{
    for(auto& description: _fileDescriptions)
        if(description.getID() == file)
        {
            APAudioSamplerVoice* voice = findFreeVoice();
            
            if(voice == nullptr)
            {
                voice = new APAudioSamplerVoice();
                voice->setFileToPlay(_fileManager->getFile(description.getID()));
                voice->play(repeat);
                _activeVoices.emplace_back(voice);
                _numVoicesActive++;
            }
            else
            {
                voice->setFileToPlay(_fileManager->getFile(description.getID()));
                voice->play(repeat);
            }
        }
}

APAudioSampler::~APAudioSampler()
{
    
}

APAudioSamplerVoice* APAudioSampler::findFreeVoice()
{
    for(auto& voice: _activeVoices)
    {
        if(!voice->isPlaying())
            return voice;
    }
    return nullptr;
}

void APAudioSampler::renderBlock(SampleBuffer output)
{
    memset(outputBuffer.data(), 0, sizeof(Sample)*getBufferSize());
    
    for(auto& voice: _activeVoices)
        if(voice->isPlaying())
            for(auto i = 0; i < getBufferSize(); i++)
                output[i] += voice->tick();
}

void APAudioSampler::loadFile(std::string fileToLoad, int noteToListenTo, int channelToListenTo)
{
    APAudioSoundDescription description;
    description.setNoteToListenTo(noteToListenTo);
    description.setID(fileToLoad);
    description.setChannelToListenTo(channelToListenTo);
    _fileDescriptions.emplace_back(description);
    _fileManager->loadFile(fileToLoad);
}

void APAudioSampler::calculateBuffer()
{
    renderBlock(outputBuffer.data());
}

void APAudioSampler::setSpeed(float speed)
{
    for(auto& voice: _activeVoices)
        voice->setSpeed(speed);
}

void APAudioSampler::setVoiceAmplitude(int note, float amp)
{
    for(auto& voice: _activeVoices)
        if (voice->getNote() == note)
            voice->setAmplitude(amp);
}