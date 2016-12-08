//
//  DictUtil.h
//  CoreAppFramework
//
//  Created by Shinji Hiramatsu on 2014/05/24.
//  Copyright 2014 GCREST,Inc. All rights reserved.
//

#ifndef __CoreAppFramework__DictUtil__
#define __CoreAppFramework__DictUtil__

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

#endif /* defined(__CoreAppFramework__DictUtil__) */
