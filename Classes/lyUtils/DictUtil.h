//
//  DictUtil.h
//
//  ly-Game
//
//  Created by loveyur on 2016/12/14
//  Copyright 2016 loveyur. All rights reserved.
//
//

#ifndef __lyGame__DictUtil__
#define __lyGame__DictUtil__

#include "cocos2d.h"

class DictUtil
{
public:
    static cocos2d::ValueMap cstrToDictionary(const char* chrs);
    
    static bool hasDataForKey(const cocos2d::ValueMap& dict, const std::string& keyId);
    static std::string asString(const cocos2d::ValueMap& dict, const std::string& keyId);
    static int asInt(const cocos2d::ValueMap& dict, const std::string& keyId);
    static float asFloat(const cocos2d::ValueMap& dict, const std::string& keyId);
    static bool asBool(const cocos2d::ValueMap& dict, const std::string& keyId);
};

#endif /* defined(__lyGame__DictUtil__) */
