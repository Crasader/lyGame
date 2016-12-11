//
//  lyJsonConverter.h
//  Json解析基类
//
//  Created by loveyur on 2016/12/07.
//
//

#ifndef __cocos2d_x_jc__lyJsonConverter__
#define __cocos2d_x_jc__lyJsonConverter__

#include "cocos2d.h"

USING_NS_CC;


#include "lyJsonData.h"
#include "lyJson.h"


class lyJsonConverter : public Ref
{
public:
    static lyJsonConverter * getInstance();
    
    char * strFrom(const ValueMap& dictionary);
    
    ValueMap dictionaryFrom(const char * str);
    ValueMap convertFileToDictionary(const char *jsonFile);
    ValueMap convertStringToDictionary(const char *jsonString);
    ValueMap convertJsonToDictionary(lyJson *json);
    
private:
    lyJson* convertDictionaryToJson(const ValueMap& dictionary);
    
    ValueVector convertJsonToArray(lyJson * json);
    
    lyJson* convertArrayToJson(ValueVector& array);
    
    lyJson * getObjJson(cocos2d::Value& obj);
    
    cocos2d::Value getJsonObj(lyJson * json);
};

#endif /* defined(__cocos2d_x_jc__lyJsonConverter__) */
