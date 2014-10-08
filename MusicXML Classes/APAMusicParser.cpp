//
//  APAMusicParser.cpp
//  APA
//
//  Created by Danny van Swieten on 22-05-14.
//
//

#include "APAMusicParser.h"

APAMusicParser::APAMusicParser()
{
    eventHandler = new APAEventHandler();
}

APAMusicParser::~APAMusicParser()
{
    delete mainXmlElement;
    delete eventHandler;
}

void APAMusicParser::loadMusicFile()
{
    FileChooser myChooser ("Please select the file you want to load...",
                           File::getSpecialLocation (File::userHomeDirectory),
                           "*.xml");
    
    if (myChooser.browseForFileToOpen())
    {
        XmlDocument sheetMusic(File(myChooser.getResult()));
        mainXmlElement = XmlDocument::parse(File(myChooser.getResult()));
    }
}

void APAMusicParser::checkForEvents()
{
    int numEvents = 0;
    forEachXmlChildElement (*mainXmlElement, e)
    {
        if(e->getTagName() == "part")
        {
            forEachXmlChildElement (*e, f)
            {
                if (f->getTagName() == "measure")
                {
                    forEachXmlChildElement (*f, g)
                    {
                        //std::cout<<g->getTagName()<<std::endl;
                        if(g->getTagName() == "note")
                        {
                            forEachXmlChildElement (*g, h)
                            {
                                //std::cout<<h->getTagName()<<std::endl;
                                if(h->getTagName() == "pitch")
                                {
                                    forEachXmlChildElement (*h, i)
                                    {
                                        numEvents++;
                                        if(i->getTagName() == "step")
                                        {
                                            APAEvent* event = new APAEvent();
                                            String value(i->getAllSubText());
                                            event->setPitch(value.toStdString());
                                            eventHandler->addComputerEvent(event);
                                        }
                                    
                                        std::cout<<i->getTagName()<<std::endl;
                                        std::cout<<i->getAllSubText()<<std::endl;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    std::cout<<numEvents<<std::endl;
}