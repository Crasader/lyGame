//
//  lyJsonConverter.h
//  Json解析基类
//
//  Created by loveyur on 2016/12/07.
//
//

#ifndef __lyGame__lyJsonConverter__
#define __lyGame__lyJsonConverter__

#include "cocos2d.h"

USING_NS_CC;


#include "lyJsonData.h"
#include "lyJson.h"


class lyJsonConverter : public Ref
{
public:
    static lyJsonConverter * getInstance();
    
    char * getString(const ValueMap& dictionary);
    
    ValueMap GetDict(const char * str);
    
    ValueMap FileToDictionary(const char *jsonFile);
    
    ValueMap StringToDictionary(const char *jsonString);
    ValueMap JsonToDictionary(lyJson *json);
    
    
    lyJson* DictionaryToJson(const ValueMap& dictionary);
    
    ValueVector JsonToArray(lyJson * json);
    
    lyJson* ArrayToJson(ValueVector& array);
    
    lyJson * getObjJson(cocos2d::Value& obj);
    
    cocos2d::Value getJsonObj(lyJson * json);
};

#endif /* defined(__lyGame__lyJsonConverter__) */
