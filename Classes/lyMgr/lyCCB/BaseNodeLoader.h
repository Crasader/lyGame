//
//  BaseNodeLoader.h
//
//  ly-Game
//
//  Created by loveyur on 2016/11/11
//  Copyright 2016 loveyur. All rights reserved.
//
//

#ifndef __lyGame__BaseNodeLoader_h
#define __lyGame__BaseNodeLoader_h

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "cocosbuilder/CocosBuilder.h"

template<class T>
class BaseNodeLoader : public cocosbuilder::NodeLoader
{
public:
    static BaseNodeLoader<T> * loader() {
        BaseNodeLoader<T> * ptr = new BaseNodeLoader<T>();
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
