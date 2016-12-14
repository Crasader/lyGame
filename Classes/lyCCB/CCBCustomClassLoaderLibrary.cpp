//
//  CCBCustomClassLoaderLibrary.cpp
//  client-vitamin
//
//  Created by 大久保 孝一郎 on 2014/06/26.
//
//

#include "CCBCustomClassLoaderLibrary.h"
#include "BaseNodeLoader.h"

#include "testLayer.h"
#include "loginLayer.h"
#include "loadingText.h"


static CCBCustomClassLoaderLibrary *s_CustomClassLoaderLibrary = nullptr;

CCBCustomClassLoaderLibrary::CCBCustomClassLoaderLibrary() {
    m_customClassEntry = {
        { "testLayer", testLayerLoader::loader()},
        //{ "loginTest", loginTestLoader::loader()}
        //{ "loginLayer", loginLayerLoader::loader()},
        //{ "loadingText", loadingTextLoader::loader()}
        
    };
}

CCBCustomClassLoaderLibrary::~CCBCustomClassLoaderLibrary() {
}

void CCBCustomClassLoaderLibrary::registerCustomClassLoader() {
    cocosbuilder::NodeLoaderLibrary *nodeLoaderLibrary = cocosbuilder::NodeLoaderLibrary::getInstance();
    
    for (int i=0; i<m_customClassEntry.size(); i++) {
        CCLOG("registerCustomClassLoader i=%d,layername=%s",i,m_customClassEntry[i].pClassName);
        nodeLoaderLibrary->registerNodeLoader(m_customClassEntry[i].pClassName, m_customClassEntry[i].pCCNodeLoader);
    }
}

void CCBCustomClassLoaderLibrary::unregisterCustomClassLoader() {
    cocosbuilder::NodeLoaderLibrary *nodeLoaderLibrary = cocosbuilder::NodeLoaderLibrary::getInstance();
    
    for (int i=0; i<m_customClassEntry.size(); i++) {
        nodeLoaderLibrary->unregisterNodeLoader(m_customClassEntry[i].pClassName);
    }
}

CCBCustomClassLoaderLibrary* CCBCustomClassLoaderLibrary::getInstance() {
    if(s_CustomClassLoaderLibrary == NULL) {
        s_CustomClassLoaderLibrary = new CCBCustomClassLoaderLibrary;
    }
    return s_CustomClassLoaderLibrary;
}

void CCBCustomClassLoaderLibrary::purgeSharedCustomClassLoaderLibrary() {
    CC_SAFE_DELETE(s_CustomClassLoaderLibrary);
}

void CCBCustomClassLoaderLibrary::changeRegisterCustomClassLoader(const char* className, cocosbuilder::NodeLoader* loader) {
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

