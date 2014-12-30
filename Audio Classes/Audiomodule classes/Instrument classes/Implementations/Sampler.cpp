//
//  Sampler.cpp
//  FuChair
//
//  Created by Danny van Swieten on 10/7/14.
//
//

#include "Sampler.h"

namespace APAudio
{
    namespace Audio
    {

        Sampler::Sampler(Mainframe* mainFrame ,AudioFileManager* fileManager): AudioModule(mainFrame)
        {
            _fileManager = fileManager;
        }

        void Sampler::onNoteOn(int noteOn, float velocity, int channel, bool repeat)
        {
            for(auto& description: _fileDescriptions)
                if(description.listensToNote(noteOn) && description.listensToChannel(channel))
                {
                    SamplerVoice* voice = findFreeVoice();
                    
                    if(voice == nullptr)
                    {
                        voice = new SamplerVoice();
                        voice->setFileToPlay(&_fileManager->getFile(description.getID()));
                        voice->setNote(noteOn);
                        voice->play(repeat);
                        _activeVoices.emplace_back(voice);
                        _numVoicesActive++;
                    }
                    else
                    {
                        voice->setFileToPlay(&_fileManager->getFile(description.getID()));
                        voice->setNote(noteOn);
                        voice->play(repeat);
                    }
                }
        }

        void Sampler::onNoteOn(std::string file, float velocity, int channel, bool repeat)
        {
            for(auto& description: _fileDescriptions)
                if(description.getID() == file)
                {
                    SamplerVoice* voice = findFreeVoice();
        //            SamplerVoice* voice = new SamplerVoice();
                    
                    if(voice == nullptr)
                    {
                        voice = new SamplerVoice();
                        voice->setFileToPlay(&_fileManager->getFile(description.getID()));
                        voice->play(repeat);
                        _activeVoices.emplace_back(voice);
                        _numVoicesActive++;
                    }
                    else
                    {
                        voice->setFileToPlay(&_fileManager->getFile(description.getID()));
                        voice->play(repeat);
                        voice->setPosition();
                    }
                }
        }

        void Sampler::onNoteOff(std::string file)
        {
            for(auto& activeVoice: _activeVoices)
                if(activeVoice->getPlayingFile()->getName() == file && activeVoice->isPlaying())
                {
                    activeVoice->stop();
                    _numVoicesActive--;
                }
        }

        Sampler::~Sampler()
        {
            
        }

        SamplerVoice* Sampler::findFreeVoice()
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
            SoundDescription description;
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

        void Sampler::setSpeed(float speed)
        {
            for(auto& voice: _activeVoices)
                voice->setSpeed(speed);
        }

        void Sampler::setSpeed(std::string file,float speed)
        {
            for(auto& voice: _activeVoices)
                if(voice->getPlayingFile()->getName()==file)
                    voice->setSpeed(speed);
        }

        void Sampler::setVoiceAmplitude(int note, float amp)
        {
            for(auto& voice: _activeVoices)
                if (voice->getNote() == note)
                    voice->setAmplitude(amp);
        }
    }
}