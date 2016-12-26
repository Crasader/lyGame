//
//  lyCCBNodeBaseLoader.h
//
//  ly-Game
//
//  Created by loveyur on 2016/11/11
//  Copyright 2016 loveyur. All rights reserved.
//
//

#ifndef __lyGame__lyCCBNodeBaseLoader_h
#define __lyGame__lyCCBNodeBaseLoader_h

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "cocosbuilder/CocosBuilder.h"

template<class T>
class lyCCBNodeBaseLoader : public cocosbuilder::NodeLoader
{
public:
    static lyCCBNodeBaseLoader<T> * loader() {
        lyCCBNodeBaseLoader<T> * ptr = new lyCCBNodeBaseLoader<T>();
        if(ptr != NULL) {
            ptr->autorelease();
            return ptr;
        }
        CC_SAFE_DELETE(ptr);
        return NULL;
    }
protected:
    virtual T * createNode(cocos2d::Node * pParent, cocosbuilder::CCBReader * pCCBReader) {
        return T::create();
    }
};

#endif
