//
//  ExternalAudioObject.cpp
//  DAW
//
//  Created by Danny van Swieten on 4/13/15.
//
//

#include "ExternalAudioObject.h"

ExternalAudioObject::ExternalAudioObject(std::string path)
{
    std::cout<<path<<std::endl;
    void* handle = dlopen(path.c_str(), RTLD_LAZY);
    if(!handle)
        std::cout<<"Failed loading external: "<<path<<" please check the name and if external is installed"<<std::endl;
    create = (ObjectBase* (*)())dlsym(handle, "create_object");
    if(!create)
        std::cout<<"Can't open creation function for external"<<std::endl;
    else
    {
        std::unique_ptr<ObjectBase> p(create());
        external = move(p);
        if(external)
            std::cout<<"Loading: "<<path<<" Succeeded"<<std::endl;
        else
            std::cout<<"Loading: "<<path<<" Failed"<<std::endl;
    }
}

std::unique_ptr<ObjectBase> ExternalAudioObject::getExternal()
{
    return move(external);
}