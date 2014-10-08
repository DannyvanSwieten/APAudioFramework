//
//  APAudioVoiceManager.
//  APAudioEngine
//
//  Created by Danny van Swieten on 07-05-14.
//  Copyright (c) 2014 Danny van Swieten. All rights reserved.
//

#include "APAudioVoiceManager.h"

APAudioVoiceManager::APAudioVoiceManager(APAudioMainFrame* mf, UInt channel): APAudioModule(mf)
{
    activeVoices = 0;
    this->channel = channel;
}

void APAudioVoiceManager::addSamplerVoice()
{
    APAudioVoice* newVoice = new APAudioSamplerVoice();
    voices.emplace_back(newVoice);
}

void APAudioVoiceManager::destroyAllVoices()
{
    voices.clear();
}

APAudioVoice* APAudioVoiceManager::findFreeVoice(APAudioSoundDescription* sound, ControlValue pitch)
{
    if (!voices.empty())
    {
        for(auto& voice : voices)
        {
            if (!voice->getIsPlaying() && voice->canPlaySound(sound))
            {
                return voice;
            }
        }
    }
    
    return nullptr;
}

void APAudioVoiceManager::addSound(APAudioSoundDescription *s)
{
    sounds.emplace_back(s);
}

void APAudioVoiceManager::noteOn(ControlValue pitch, ControlValue channel)
{
    for(auto& sound : sounds)
    {
        if (sound->listensToNote(pitch))
            startVoice(findFreeVoice(sound, pitch), sound, pitch, channel);
    }
}

void APAudioVoiceManager::noteOff(UInt ID)
{
    for(auto& voice : voices)
    {
        if (voice->getIsPlaying() && voice->getID() == ID)
        {
            voice->getEnvelope()->enterNextStage(APAudioEnvelope::EnvelopeState::RELEASE);
        }
    }
}

void APAudioVoiceManager::updatePitch(ControlValue pitch, ControlValue ID)
{
    for(auto& voice : voices)
    {
        if (voice->getIsPlaying() && voice->getID() == ID)
        {
            voice->setPitch(pitch);
        }
    }
}

void APAudioVoiceManager::startVoice(APAudioVoice *freeVoice, APAudioSoundDescription* sound, ControlValue pitch, ControlValue velocity)
{
    if (freeVoice != nullptr)
    {
        freeVoice->setIsPlaying(true);
        freeVoice->getEnvelope()->enterNextStage(APAudioEnvelope::EnvelopeState::ATTACK);
        freeVoice->setPitch(pitch);
        freeVoice->setID(velocity);
        freeVoice->setSound(sound);
        activeVoices++;
    }
    else if(freeVoice == nullptr)
    {
        if (sound == dynamic_cast<APAudioSampleSound*>(sound))
        {
            freeVoice = new APAudioSamplerVoice();
        }
        
        freeVoice->setIsPlaying(true);
        freeVoice->getEnvelope()->enterNextStage(APAudioEnvelope::EnvelopeState::ATTACK);
        freeVoice->setPitch(pitch);
        freeVoice->setID(velocity);
        freeVoice->setSound(sound);
        voices.emplace_back(freeVoice);
        activeVoices++;
    }
}

UInt APAudioVoiceManager::getActiveVoices()
{
    return activeVoices;
}

void APAudioVoiceManager::calculateBuffer()
{
    for(auto i = 0; i < getBufferSize(); i++)
    {
        outputBuffer[i] = 0.0;
    }
    
    for (auto& voice : voices)
    {
        if (voice->getIsPlaying())
        {
            voice->renderNextBlock(outputBuffer,
                                   0,
                                   getBufferSize(),
                                   channel);
        }
    }
    
    if (activeVoices == 0)
    {
        if(!voices.empty())
            voices.clear();
        
        for(auto i = 0; i < getBufferSize(); i++)
        {
            outputBuffer[i] = 0.0;
        }
    }
}