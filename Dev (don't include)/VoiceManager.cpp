//
//  VoiceManager.cpp
//  SmartSampler
//
//  Created by Danny van Swieten on 1/9/15.
//
//

#include "VoiceManager.h"

namespace APAudio
{
    VoiceManager::VoiceManager(): APAudio::AudioObject()
    {
        for (auto i = 0; i < 16; i++)
        {
            std::unique_ptr<Voice> voice = std::make_unique<Voice>();
            voices.emplace_back(std::move(voice));
        }
    }
    
    VoiceManager::VoiceManager(Mainframe& mainFrame):AudioObject(mainFrame)
    {
        for (auto i = 0; i < 16; i++)
        {
            std::unique_ptr<Voice> voice = std::make_unique<Voice>();
            voices.emplace_back(std::move(voice));
        }
    }
    
    VoiceManager::VoiceManager(Mainframe& mainFrame, AudioSourceManager* manager): AudioObject(mainFrame)
    {
        sourceManager = manager;
        for (auto i = 0; i < 16; i++)
        {
            std::unique_ptr<Voice> voice = std::make_unique<Voice>();
            voices.emplace_back(std::move(voice));
        }
    }
    
    void VoiceManager::noteOn(int note, int velocity, int channel)
    {
        for(auto& source: sourceManager->getAudioSources(note, velocity, channel))
        {
            Voice* voice = findFreeVoice();
            
            if(voice == nullptr)
            {
                voice = new Voice();
                extraVoices.emplace_back(std::move(voice));
            }
            
            auto filePlayer = new AudioFilePlayer();
            filePlayer->setFile(&sourceManager->getFileManager().getFile(source.info));
            filePlayer->setSampleRate(getSampleRate());
            
            voice->setSource(filePlayer);
            voice->playingNumber = note;
            voice->start();
            std::cout<<voices.size()<<std::endl;
            std::cout<<extraVoices.size()<<std::endl;
        }
    }
    
    void VoiceManager::noteOff(int note, int velocity, int channel)
    {
        for(auto& voice: voices)
        {
            if(note == voice->playingNumber && voice->isPlaying())
                voice->getEnvelope()->enterNextStage(APAudio::Envelope::EnvelopeState::RELEASE);
            
            for(auto& voice: extraVoices)
            {
                if(note == voice->playingNumber && voice->isPlaying())
                    voice->getEnvelope()->enterNextStage(APAudio::Envelope::EnvelopeState::RELEASE);
            }
        }
    }
    
    Voice* VoiceManager::findFreeVoice()
    {
        for(auto& voice: voices)
        {
            if (!voice->isPlaying())
                return voice.get();
        }
        
        for(auto& voice: extraVoices)
        {
            if (!voice->isPlaying())
                return voice.get();
        }
        
        return nullptr;
    }
    
    void VoiceManager::calculateBuffer()
    {
        memset(outputBuffer.data(), 0, sizeof(float) * getBufferSize());
        activeVoices = 0;
        for(auto& voice: voices)
        {
            if(voice->isPlaying())
            {
                activeVoices++;
                for(auto i = 0; i < getBufferSize(); i++)
                {
                    outputBuffer[i] += voice->play();
                }
            }
        }
        
        if(extraVoices.size())
        {
            activeExtraVoices = 0;
            for(auto& voice: extraVoices)
            {
                if(voice->isPlaying())
                {
                    activeExtraVoices++;
                    for(auto i = 0; i < getBufferSize(); i++)
                    {
                        outputBuffer[i] += voice->play();
                    }
                }
            }
            if(!activeExtraVoices)
                extraVoices.clear();
        }
    }
}