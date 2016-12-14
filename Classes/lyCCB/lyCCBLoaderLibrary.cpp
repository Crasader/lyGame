//
//  lyCCBLoaderLibrary.cpp
//
//  ly-Game
//
//  Created by loveyur on 2016/11/11
//  Copyright 2016 loveyur. All rights reserved.
//
//

#include "lyCCBLoaderLibrary.h"
#include "BaseNodeLoader.h"

#include "testLayer.h"
#include "loginLayer.h"
#include "loadingText.h"


static lyCCBLoaderLibrary *s_CustomClassLoaderLibrary = nullptr;

lyCCBLoaderLibrary::lyCCBLoaderLibrary() {
    m_customClassEntry = {
        { "testLayer", testLayerLoader::loader()},
        //{ "loginTest", loginTestLoader::loader()}
        //{ "loginLayer", loginLayerLoader::loader()},
        //{ "loadingText", loadingTextLoader::loader()}
        
    };
}

lyCCBLoaderLibrary::~lyCCBLoaderLibrary() {
}

void lyCCBLoaderLibrary::registerCustomClassLoader() {
    cocosbuilder::NodeLoaderLibrary *nodeLoaderLibrary = cocosbuilder::NodeLoaderLibrary::getInstance();
    
    for (int i=0; i<m_customClassEntry.size(); i++) {
        CCLOG("registerCustomClassLoader i=%d,layername=%s",i,m_customClassEntry[i].pClassName);
        nodeLoaderLibrary->registerNodeLoader(m_customClassEntry[i].pClassName, m_customClassEntry[i].pCCNodeLoader);
    }
}

void lyCCBLoaderLibrary::unregisterCustomClassLoader() {
    cocosbuilder::NodeLoaderLibrary *nodeLoaderLibrary = cocosbuilder::NodeLoaderLibrary::getInstance();
    
    for (int i=0; i<m_customClassEntry.size(); i++) {
        nodeLoaderLibrary->unregisterNodeLoader(m_customClassEntry[i].pClassName);
    }
}

lyCCBLoaderLibrary* lyCCBLoaderLibrary::getInstance() {
    if(s_CustomClassLoaderLibrary == NULL) {
        s_CustomClassLoaderLibrary = new lyCCBLoaderLibrary;
    }
    return s_CustomClassLoaderLibrary;
}

void lyCCBLoaderLibrary::purgeSharedCustomClassLoaderLibrary() {
    CC_SAFE_DELETE(s_CustomClassLoaderLibrary);
}

void lyCCBLoaderLibrary::changeRegisterCustomClassLoader(const char* className, cocosbuilder::NodeLoader* loader) {
    cocosbuilder::NodeLoaderLibrary *nodeLoaderLibrary = cocosbuilder::NodeLoaderLibrary::getInstance();
    for (int i=0; i<m_customClassEntry.size(); i++) {
        if (!strcmp(m_customClassEntry[i].pClassName, className)) {
            nodeLoaderLibrary->unregisterNodeLoader(m_customClassEntry[i].pClassName);
            
            m_customClassEntry[i].pCCNodeLoader = loader;
            
            nodeLoaderLibrary->registerNodeLoader(m_customClassEntry[i].pClassName, m_customClassEntry[i].pCCNodeLoader);
            
            break;
        }
    }
}

