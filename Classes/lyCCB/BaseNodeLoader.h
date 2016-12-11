//
//  BaseNodeLoader.h
//  Donut
//
//  Created by 横道 晃司 on 2014/07/02.
//
//

#ifndef Donut_BaseNodeLoader_h
#define Donut_BaseNodeLoader_h

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
