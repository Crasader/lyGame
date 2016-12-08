//
//  CCJSONConverter.cpp
//  cocos2d-x-jc
//
//  Created by LIN BOYU on 11/14/12.
//
//

#include "CCJSONConverter.h"
static CCJSONConverter *_sharedConverter;

CCJSONConverter * CCJSONConverter::getInstance()
{
    if (_sharedConverter == nullptr) {
        _sharedConverter = new CCJSONConverter();
    }
    
    return _sharedConverter;
}


 char * CCJSONConverter::strFrom(const cocos2d::ValueMap& dictionary)
 {
//     CCAssert(dictionary, "CCJSONConverter:can not convert a null pointer");
     
     // ValueMapからJSON文字列への変換
     cJSON * json = convertDictionaryToJson(dictionary);
     
     char* jsonString = cJSON_Print(json);
     cJSON_Delete(json);
     return jsonString;
 }


ValueMap CCJSONConverter::dictionaryFrom(const char *str)
{
    cJSON * json = cJSON_Parse(str);
    CCAssert(json && json->type==cJSON_Object, "CCJSONConverter:wrong json format");
    ValueMap dictionary = convertJsonToDictionary(json);
    cJSON_Delete(json);
    return dictionary;
}

ValueMap CCJSONConverter::convertJsonToDictionary(cJSON *json)
{
    ValueMap dictionary;
    if (json != nullptr) {
        cJSON * j = json->child;
        while (j) {
            Value obj = getJsonObj(j);
            dictionary.insert(std::make_pair(j->string, obj));
            j = j->next;
        }
    }
    return dictionary;
}


cJSON * CCJSONConverter::convertDictionaryToJson(const ValueMap& dictionary)
 {
     cJSON * json = cJSON_CreateObject();

     for (auto iter = dictionary.cbegin(); iter != dictionary.cend(); ++iter)
     {
         Value itemData = iter->second;
         cJSON * jsonItem = getObjJson(itemData);
         if (jsonItem != nullptr)
             cJSON_AddItemToObject(json, iter->first.c_str(), jsonItem);
     }

     return json;
 }


ValueVector CCJSONConverter::convertJsonToArray(cJSON * json)
{
    ValueVector array;
    int size = cJSON_GetArraySize(json);
    for (int i=0; i<size; i++) {
        cJSON * jsonItem = cJSON_GetArrayItem(json, i);
        Value objItem = getJsonObj(jsonItem);
        array.push_back(objItem);
    }
    
    return array;
}


 cJSON * CCJSONConverter::convertArrayToJson(ValueVector& array)
 {
     cJSON * json = cJSON_CreateArray();

     for (auto item : array)
     {
         cJSON * jsonItem = getObjJson(item);
         cJSON_AddItemToArray(json, jsonItem);
     }
     
     return json;
 }


cJSON * CCJSONConverter::getObjJson(Value& obj)
{
    cJSON * json = nullptr;
    
    if (obj.getType() == Value::Type::MAP)
    {
        ValueMap map = obj.asValueMap();
        json = convertDictionaryToJson(map);
    }
    else if(obj.getType() == Value::Type::VECTOR)
    {
        ValueVector array = obj.asValueVector();
        json = convertArrayToJson(array);
    }
    else if(obj.getType() == Value::Type::STRING)
    {
        std::string str = obj.asString();
        json = cJSON_CreateString(str.c_str());
    }
    else if(obj.getType() == Value::Type::INTEGER)
    {
        json = cJSON_CreateNumber(obj.asInt());
    }
    else if(obj.getType() == Value::Type::FLOAT || obj.getType() == Value::Type::DOUBLE)
    {
        json = cJSON_CreateNumber(obj.asDouble());
    }
    else if(obj.getType() == Value::Type::BOOLEAN)
    {
        bool flag = obj.asBool();
        if (flag)
            json = cJSON_CreateTrue();
        else
            json = cJSON_CreateFalse();
    }
    else if (obj.getType() == Value::Type::NONE)
    {
        json = cJSON_CreateNull();
//      log("CCJSONConverter encountered an unrecognized type");
    }
    else
    {
        json = nullptr;
    }
    
     return json;
 }


Value CCJSONConverter::getJsonObj(cJSON * json)
{
    switch (json->type) {
        case cJSON_Object:
        {
            ValueMap dictionary = convertJsonToDictionary(json);
            return Value(dictionary);
        }
        case cJSON_Array:
        {
            ValueVector array = convertJsonToArray(json);
            return Value(array);
        }
        case cJSON_String:
        {
            return Value(json->valuestring);
        }
        case cJSON_Number:
        {
            return Value(json->valuedouble);
        }
        case cJSON_True:
        {
            bool    flag = true;
            return Value(flag);
        }
        case cJSON_False:
        {
            bool    flag = false;
            return Value(flag);
        }
        case cJSON_NULL:
        {
            return Value();
        }
        default:
        {
            log("CCJSONConverter encountered an unrecognized type");
            return Value();
        }
    }
}
