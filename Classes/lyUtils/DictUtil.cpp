//
//  DictUtil.cpp
//  CoreAppFramework
//
//  Created by Shinji Hiramatsu on 2014/05/24.
//  Copyright 2014 GCREST,Inc. All rights reserved.
//

#include "DictUtil.h"
#include "CCJSONConverter.h"
#include "cocos2d.h"
#include <typeinfo>

USING_NS_CC;

cocos2d::ValueMap DictUtil::cstrToDictionary(const char* chrs)
{
    ValueMap dict = CCJSONConverter::getInstance()->dictionaryFrom(chrs);
    
    return dict;
}


bool DictUtil::hasDataForKey(const cocos2d::ValueMap& dict, const std::string& keyId)
{
    bool hasKey = false;
    if (dict.size() > 0 && dict.find(keyId) != dict.end())
    {
        hasKey = true;
    }
    return hasKey;
}

std::string DictUtil::asString(const cocos2d::ValueMap& dict, const std::string& keyId)
{
    std::string    str;
    if (dict.size() > 0 && dict.find(keyId) != dict.end())
    {
        str = dict.at(keyId).asString();
    }
    return str;
}

int DictUtil::asInt(const cocos2d::ValueMap& dict, const std::string& keyId)
{
    int    value = 0;
    if (dict.size() > 0 && dict.find(keyId) != dict.end())
    {
        value = dict.at(keyId).asInt();
    }
    return value;
}

float DictUtil::asFloat(const cocos2d::ValueMap& dict, const std::string& keyId)
{
    float    value = 0;
    if (dict.size() > 0 && dict.find(keyId) != dict.end())
    {
        value = dict.at(keyId).asFloat();
    }
    return value;
}

bool DictUtil::asBool(const cocos2d::ValueMap& dict, const std::string& keyId)
{
    bool    value = false;
    if (dict.size() > 0 && dict.find(keyId) != dict.end())
    {
        value = dict.at(keyId).asBool();
    }
    return value;
}


