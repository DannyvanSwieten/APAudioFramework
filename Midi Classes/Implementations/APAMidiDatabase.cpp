/*
  ==============================================================================

    APAMidiDatabase.cpp
    Created: 3 Jul 2014 4:16:15pm
    Author:  Danny van Swieten

  ==============================================================================
*/

#include "APAMidiDatabase.h"

APAMidiDatabase::APAMidiDatabase()
{
    loader = new APAMidiLoader(16, 8);
}

APAMidiDatabase::~APAMidiDatabase()
{
    delete loader;
}

void APAMidiDatabase::load()
{
    FileChooser loadFile("Select midi data file",
                         File::getSpecialLocation(File::userHomeDirectory),
                         "*.txt");
    if(loadFile.browseForFileToOpen())
    {
        database.emplace_back(loader->loadData(loadFile.getResult()));
    }
}

void APAMidiDatabase::loadComposition()
{
    FileChooser loadFile("Select midi data file",
                         File::getSpecialLocation(File::userHomeDirectory),
                         "*.txt");
    if(loadFile.browseForFileToOpen())
    {
        composition = loader->loadData(loadFile.getResult());
    }
}