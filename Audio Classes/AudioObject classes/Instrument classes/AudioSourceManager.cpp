//
//  AudioSourceManager.cpp
//  SmartSampler
//
//  Created by Danny van Swieten on 1/9/15.
//
//

#include "AudioSourceManager.h"

namespace APAudio
{
    
    //==================AudioSourcePackage=========================
    AudioSourcePackage::AudioSourcePackage()
    {
        
    }
    
    AudioSourcePackage::AudioSourcePackage(std::string id)
    {
        ID = id;
    }
    
    void AudioSourcePackage::addSource(AudioSourceDescription source)
    {
        audioSources.emplace_back(source);
    }
    
    std::vector<AudioSourceDescription> AudioSourcePackage::getSources()
    {
        return audioSources;
    }
    
    AudioSourceManager::AudioSourceManager(float samplerate)
    {
        sampleRate = samplerate;
    }
    
    void AudioSourceManager::parsePackage(juce::var package)
    {
        std::cout<<"HEADER:"<<std::endl<<std::endl;
        var id = package[Identifier("id")];
        std::cout<<"Package ID: "<<id.toString()<<std::endl;
        
        AudioSourcePackage audioSourcePackage(id.toString().toStdString());
        
        var type = package[Identifier("type")];
        std::cout<<"Package Type: "<<type.toString()<<std::endl;
        var groups = package[Identifier("groups")];
        
        std::cout<<"Number of Groups: "<<groups.size()<<std::endl<<std::endl;
        
        for(auto group = 0; group < groups.size(); group++)
        {
            auto currentGroup = groups[group];
            auto groupName = currentGroup[Identifier("name")].toString();
            std::cout<<"Group: "<<groupName<<std::endl;
            auto layer = currentGroup[Identifier("layer")];
            std::cout<<"Layer: "<<layer[0].toString()<<" - "<<layer[1].toString()<<std::endl<<std::endl;
            
            std::cout<<"    SOURCES:"<<std::endl;
            auto samples = currentGroup[Identifier("samples")];
            
            for(auto sample = 0; sample < samples.size(); sample++)
            {
                auto currentSampleObject = samples[sample];
                auto currentSample = currentSampleObject[Identifier("sample")];
                auto currentSampleName = currentSample[Identifier("name")].toString();
                std::cout<<"    Sample: "<<currentSampleName<<std::endl;
                AudioSourceDescription description;
                description.ID = "Fileplayer";
                description.info = currentSampleName.toStdString();
                description.velocity.setMinValue(layer[0]);
                description.velocity.setMaxValue(layer[1]);
                
                var zone = currentSample[Identifier("zone")];
                
                description.note.setMinValue(zone[0]);
                description.note.setMaxValue(zone[0]);
                
                description.channel.setMinValue(0);
                description.channel.setMaxValue(16);
                description.channel.setValue(0);
                
                audioSourcePackage.addSource(description);
            }
            std::cout<<std::endl;
        }
        std::cout<<std::endl;
        
        packages.emplace_back(audioSourcePackage);
    }
    
    void AudioSourceManager::loadPackage(std::string pathOnDisk)
    {
        auto parse = JSON::parse(File(pathOnDisk));
        
        var package = parse[Identifier("package")];
        parsePackage(parse);
        
        std::vector<std::string> sampleNames;
        
        for(auto& package: packages)
        {
            for(auto& source: package.getSources())
            {
                sampleNames.emplace_back(source.info);
            }
        }

        auto files = swapNames(pathOnDisk, sampleNames);
        fileManager.loadFiles(files);
    }
    
    std::vector<AudioSourceDescription> AudioSourceManager::getAudioSources(int note, int velocity, int channel)
    {
        std::vector<AudioSourceDescription> listeningSources;
        
        for(auto package: packages)
        {
            for (auto source: package.getSources())
            {
                if (source.check(note, velocity, channel))
                {
                    listeningSources.emplace_back(source);
                }
            }
        }
        return std::move(listeningSources);
    }
    
    std::vector<std::string> AudioSourceManager::swapNames(std::string pathOnDisk, std::vector<std::string> fileNames)
    {
        auto pos = pathOnDisk.find_last_of("/");
        pathOnDisk.resize(pos + 1);
        std::string pathWithoutExtension = pathOnDisk;
        
        std::vector<std::string> absolutePaths;
        
        for(auto& file: fileNames)
            absolutePaths.emplace_back(pathWithoutExtension + "Samples/" + file);
        
        return std::move(absolutePaths);
    }
    
    AudioFileManager& AudioSourceManager::getFileManager()
    {
        return fileManager;
    }
}