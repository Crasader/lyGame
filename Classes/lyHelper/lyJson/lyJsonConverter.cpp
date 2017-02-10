//
//  lyJsonConverter.cpp
//  Json解析基类
//
//  Created by loveyur on 2016/12/07.
//
//

#include "lyJsonConverter.h"
#include "cocos2d.h"

static lyJsonConverter *_sharedConverter;

lyJsonConverter * lyJsonConverter::getInstance()
{
    if (_sharedConverter == nullptr) {
        _sharedConverter = new lyJsonConverter();
    }
    
    return _sharedConverter;
}


 char * lyJsonConverter::getString(const cocos2d::ValueMap& dictionary)
 {
//     CCAssert(dictionary, "lyJsonConverter:can not convert a null pointer");
     
     lyJson * json = DictionaryToJson(dictionary);
     
     char* jsonString = lyJson_Print(json);
     lyJson_Delete(json);
     return jsonString;
 }


ValueMap lyJsonConverter::GetDict(const char *str)
{
    lyJson * json = lyJson_Parse(str);
    CCAssert(json && json->type==lyJson_Object, "lyJsonConverter:wrong json format");
    ValueMap dictionary = JsonToDictionary(json);
    lyJson_Delete(json);
    return dictionary;
}
ValueMap lyJsonConverter::StringToDictionary(const char *jsonString)
{
    ValueMap dictRet;
    lyJson* json = lyJson_Parse(jsonString);
    if (json)
    {
        if (json->type==lyJson_Object)
        {
            dictRet = lyJsonConverter::getInstance()->JsonToDictionary(json);
            cocos2d::log("jsonString=%s",jsonString);
            lyJson_Delete(json);
        }
        else
        {
            cocos2d::log("stringToJson:json type isn't lyJson_Object");
        }
    }
    return dictRet;
}
ValueMap lyJsonConverter::FileToDictionary(const char *jsonFile)
{
    ValueMap dictRet;
    if (FileUtils::getInstance()->isFileExist(jsonFile))
    {
        dictRet = StringToDictionary(FileUtils::getInstance()->getStringFromFile(jsonFile).c_str());
    }
    return dictRet;
}

ValueMap lyJsonConverter::JsonToDictionary(lyJson *json)
{
    ValueMap dictionary;
    if (json != nullptr) {
        lyJson * j = json->child;
        while (j) {
            Value obj = getJsonObj(j);
            dictionary.insert(std::make_pair(j->string, obj));
            j = j->next;
        }
    }
    return dictionary;
}


lyJson * lyJsonConverter::DictionaryToJson(const ValueMap& dictionary)
 {
     lyJson * json = lyJson_CreateObject();

     for (auto iter = dictionary.cbegin(); iter != dictionary.cend(); ++iter)
     {
         Value itemData = iter->second;
         lyJson * jsonItem = getObjJson(itemData);
         if (jsonItem != nullptr)
             lyJson_AddItemToObject(json, iter->first.c_str(), jsonItem);
     }

     return json;
 }


ValueVector lyJsonConverter::JsonToArray(lyJson * json)
{
    ValueVector array;
    int size = lyJson_GetArraySize(json);
    for (int i=0; i<size; i++) {
        lyJson * jsonItem = lyJson_GetArrayItem(json, i);
        Value objItem = getJsonObj(jsonItem);
        array.push_back(objItem);
    }
    
    return array;
}


 lyJson * lyJsonConverter::ArrayToJson(ValueVector& array)
 {
     lyJson * json = lyJson_CreateArray();

     for (auto item : array)
     {
         lyJson * jsonItem = getObjJson(item);
         lyJson_AddItemToArray(json, jsonItem);
     }
     
     return json;
 }


lyJson * lyJsonConverter::getObjJson(cocos2d::Value& obj)
{
    lyJson * json = nullptr;
    
    if (obj.getType() == Value::Type::MAP)
    {
        ValueMap map = obj.asValueMap();
        json = DictionaryToJson(map);
    }
    else if(obj.getType() == Value::Type::VECTOR)
    {
        ValueVector array = obj.asValueVector();
        json = ArrayToJson(array);
    }
    else if(obj.getType() == Value::Type::STRING)
    {
        std::string str = obj.asString();
        json = lyJson_CreateString(str.c_str());
    }
    else if(obj.getType() == Value::Type::INTEGER)
    {
        json = lyJson_CreateNumber(obj.asInt());
    }
    else if(obj.getType() == Value::Type::FLOAT || obj.getType() == Value::Type::DOUBLE)
    {
        json = lyJson_CreateNumber(obj.asDouble());
    }
    else if(obj.getType() == Value::Type::BOOLEAN)
    {
        bool flag = obj.asBool();
        if (flag)
            json = lyJson_CreateTrue();
        else
            json = lyJson_CreateFalse();
    }
    else if (obj.getType() == Value::Type::NONE)
    {
        json = lyJson_CreateNull();
//      log("lyJsonConverter encountered an unrecognized type");
    }
    else
    {
        json = nullptr;
    }
    
     return json;
 }


cocos2d::Value lyJsonConverter::getJsonObj(lyJson * json)
{
    switch (json->type) {
        case lyJson_Object:
        {
            ValueMap dictionary = JsonToDictionary(json);
            return Value(dictionary);
        }
        case lyJson_Array:
        {
            ValueVector array = JsonToArray(json);
            return Value(array);
        }
        case lyJson_String:
        {
            return Value(json->valuestring);
        }
        case lyJson_Number:
        {
            return Value(json->valuedouble);
        }
        case lyJson_True:
        {
            bool    flag = true;
            return Value(flag);
        }
        case lyJson_False:
        {
            bool    flag = false;
            return Value(flag);
        }
        case lyJson_NULL:
        {
            return Value();
        }
        default:
        {
            log("lyJsonConverter encountered an unrecognized type");
            return Value();
        }
    }
}
