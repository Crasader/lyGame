//
//  lyCSVReader.cpp
//  ly-Game
//
//  Created by loveyur on 2016/12/34
//  Copyright 2016 loveyur. All rights reserved.
//
//

#include "lyCSVReader.h"
#include "cocos2d.h"

USING_NS_CC;

static lyCSVReader* _pInstanceCSVReader = nullptr;

lyCSVReader::lyCSVReader()
{
    m_firstVector.clear();
    m_contentMap.clear();
    m_fileMap.clear();
}

lyCSVReader::~lyCSVReader()
{
}


lyCSVReader* lyCSVReader::getInstance()
{
    if (!_pInstanceCSVReader)
    {
        _pInstanceCSVReader = new lyCSVReader();
    }
    return _pInstanceCSVReader;
}
const MAP_CONTENT* lyCSVReader::getFile(std::string strCSVPath)
{
    //如果表数据不在内存中，解析表数据
    if(m_fileMap.find(strCSVPath) == m_fileMap.end())
    {
        this->Parse(strCSVPath.c_str());
    }
    //获得表数据
    if(m_fileMap.find(strCSVPath) != m_fileMap.end())
    {
        return &(m_fileMap.find(strCSVPath)->second);
    }
    return nullptr;
}
const MAP_LINE* lyCSVReader::getOneLine(std::string strCSVPath, int code)
{
    const MAP_CONTENT* content = getFile(strCSVPath);
    if(content && content->find(code) != content->end())
    {
        return &(content->find(code)->second);
    }
    return nullptr;
}
int lyCSVReader::getLineNum(std::string strCSVPath)
{
    const MAP_CONTENT* content = getFile(strCSVPath);
    if(content)
    {
        return (int)content->size();
    }
    return 0;
}
const std::string lyCSVReader::getValue(std::string strCSVPath, int nRowId, const std::string &strColumn)
{
    const MAP_LINE* line = getOneLine(strCSVPath, nRowId);
    if(line && line->find(strColumn) != line->end())
    {
        return line->find(strColumn)->second;
    }
    return "";
}
void lyCSVReader::Parse(std::string strCSVPath)
{
    m_contentMap.clear();       //首先进行清理
    
    if(!FileUtils::getInstance()->isFileExist(strCSVPath))
    {
        CCLOG("CSV file %s is not exist!!", strCSVPath.c_str());
        return;
    }
    unsigned long size = 0;
    std::string strData = FileUtils::getInstance()->getStringFromFile(strCSVPath);
    const char* data = strData.c_str();
    
    char line[32768];   //一行最多字节数
    const char *src = data;
    if (size == 0) size = strData.size();
    
    char *pl = line;        //指向line数组的指针
    int index = 0;
    bool skip = false;  //若一行为空，skip则标记为true
    
    while (data - src < size)
    {
        //读取到一行的末尾
        if (*data == '\n' && !skip)
        {
            *pl = '\0';
            readCSVLine(line, index);
            ++index;
            pl = line;
        }
        else if (*data == '\r')
        {}
        else
        {
            //任何一个字段能留空
            if (*data == '"')
                skip = !skip;
            
            *pl = *data;
            ++pl;
        }
        ++data;
    }
    *pl = '\0';
    
    //添加到map
    m_fileMap.insert(std::map<std::string, MAP_CONTENT>::value_type(strCSVPath, m_contentMap));
}

void lyCSVReader::readCSVLine(const char *line, int index)
{
    char value[32768];  //一行最多字节数
    if (*line == '\0')
        return;
    
    char *pv[32];
    char *tv = value;
    bool skip = false;
    int count = 0;
    
    *tv = '\0';
    pv[count++] = tv;
    
    while (*line != '\0')
    {
        if (*line == ',' && !skip)
        {
            *tv = '\0';
            ++tv;
            pv[count++] = tv;
        }
        else if (*line == '"')
        {
            skip = !skip;
        }
        else
        {
            *tv = *line;
            ++tv;
        }
        ++line;
    }
    *tv = '\0';
    
    //临时数组
    std::vector<std::pair<std::string, int>> tVector;
    for (int i=0; i<count; ++i)
    {
        tVector.push_back(std::pair<std::string, int>(pv[i], i));
    }
    //第一行作为key
    if(index == 2)
    {
        m_firstVector = tVector;
    }
    //第2行为注释
    else if(index > 4)
    {
        //一行的map
        std::map<string, string> tmp;
        for (int i = 0; i < m_firstVector.size(); i++)
        {
            tmp.insert(std::map<string, string>::value_type(m_firstVector[i].first, tVector[i].first));
        }
        m_contentMap.insert(std::map<int, MAP_LINE>::value_type(atoi(tVector[0].first.c_str()), tmp));
    }
}

