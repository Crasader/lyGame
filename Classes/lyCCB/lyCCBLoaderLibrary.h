//
//  lyCCBLoaderLibrary.h
//
//  ly-Game
//
//  Created by loveyur on 2016/11/11
//  Copyright 2016 loveyur. All rights reserved.
//
//

#ifndef __lyGame__lyCCBLoaderLibrary__
#define __lyGame__lyCCBLoaderLibrary__

#include "cocosbuilder/CocosBuilder.h"


typedef struct {
    const char                *pClassName;       //! クラス名
    cocosbuilder::NodeLoader *pCCNodeLoader;    //! 登録するローダーのポインタ
} CustomClassEntry;

class lyCCBLoaderLibrary {
public:
    
    lyCCBLoaderLibrary();
    
    ~lyCCBLoaderLibrary();
    
    void registerCustomClassLoader();
    
    void unregisterCustomClassLoader();
    
    static lyCCBLoaderLibrary * getInstance();
    
    static void purgeSharedCustomClassLoaderLibrary();
    
    void changeRegisterCustomClassLoader(const char* className, cocosbuilder::NodeLoader* loader);
    
private:
    std::vector<CustomClassEntry> m_customClassEntry;
};


#endif /* defined(__lyGame__lyCCBLoaderLibrary__) */
