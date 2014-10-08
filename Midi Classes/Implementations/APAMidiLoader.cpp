/*
  ==============================================================================

    APAMidiLoader.cpp
    Created: 26 Jun 2014 5:27:41pm
    Author:  Danny van Swieten

  ==============================================================================
*/

#include "APAMidiLoader.h"

APAMidiLoader::APAMidiLoader()
{
    measureSize = 0;
    phraseSize  = 0;
}

APAMidiLoader::APAMidiLoader(unsigned int measureSize, unsigned int phraseSize)
{
    this->measureSize   = measureSize;
    this->phraseSize    = phraseSize * measureSize;
}

void APAMidiLoader::setMeasureSize(unsigned int measureSize)
{
    this->measureSize   = measureSize;
}

void APAMidiLoader::setPhraseSize(unsigned int phraseSize)
{
    this->phraseSize    = phraseSize;
}

APAMidiData APAMidiLoader::loadData(juce::File dataFile)
{
    APAMidiData dataToLoad;
    
    if(measureSize == 0 || phraseSize == 0)
        return dataToLoad;
    
    dataFile.readLines(midiData);
    
    for (auto i = 0; i < midiData.size(); i+= phraseSize)
    {
        StringArray phrase;
        for (auto j = 0; j < phraseSize; j++)
        {
            if (j + i >= midiData.size())
                break;
            else
                phrase.add(midiData.getReference(i + j));
        }
        phrases.emplace_back(phrase);
    }
    
    for (auto i = 0; i < midiData.size(); i+= measureSize)
    {
        StringArray measure;
        for (auto j = 0; j < measureSize; j++)
        {
            if (j + i >= midiData.size())
                break;
            else
                measure.add(midiData.getReference(i + j));
        }
        measures.emplace_back(measure);
    }

    calculateIntervals();
    
    dataToLoad.intervals        = this->intervals;
    dataToLoad.phraseIntervals  = this->phraseIntervals;
    dataToLoad.measureIntervals = this->measureIntervals;
    dataToLoad.ID               = dataFile.getFileName();
    
    intervals.clear();
    phraseIntervals.clear();
    measureIntervals.clear();
    phrases.clear();
    measures.clear();
    midiData.clear();
    
    return dataToLoad;
}

void APAMidiLoader::calculateIntervals()
{
    for (auto i = 0; i < midiData.size()-1; i++)
    {
        auto interval1 = atoi(midiData.getReference(i).getCharPointer());
        auto interval2 = atoi(midiData.getReference(i+1).getCharPointer());
        
        if(interval2 == 0) break;
        
        intervals.emplace_back(interval2 - interval1);
    }
    
    phraseIntervals.resize(phrases.size());
    
    int counter = 0;
    for (auto i = 0; i < intervals.size(); i+= phraseSize)
    {
        for(auto j = 0; j < phraseSize; j++)
        {
            if (i + j >= intervals.size())
            {
                break;
            }
            else
            {
                phraseIntervals[counter].emplace_back(intervals[i + j]);
            }
        }
        counter++;
    }
    
    measureIntervals.resize(measures.size());
    counter = 0;
    
    for (auto i = 0; i < intervals.size(); i+= measureSize)
    {
        for(auto j = 0; j < measureSize; j++)
        {
            if (i + j >= intervals.size())
            {
                break;
            }
            else
            {
                measureIntervals[counter].emplace_back(intervals[i + j]);
            }
        }
        counter++;
    }
}