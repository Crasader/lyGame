//
//  lyCSVReader.h
//  csv配置文件读取类，
//  ly-Game
//
//  Created by loveyur on 2016/12/24
//  Copyright 2016 loveyur. All rights reserved.
//
//

#ifndef __lyGame__lyCSVReader__
#define __lyGame__lyCSVReader__

#include "lyInclude.h"


#define MAP_LINE std::map<std::string, std::string>          //key为首行字符串, value为此列字符串
#define MAP_CONTENT std::map<int, MAP_LINE>                  //key为code, value为一行map
#define VEC_MAP  std::vector<std::pair<std::string, int>>


class lyCSVReader
{
public:
    lyCSVReader();
    ~lyCSVReader();

    static lyCSVReader* getInstance();
    //解析csv. fileName.csv文件名,
    void parse(const char *fileName);
    
    //获取内容map. filename:文件名
    const MAP_CONTENT* getContentMap(std::string filename);
    //获取一行map.filename:文件名， code一行code
    const MAP_LINE* getLineMap(std::string filename, int code);
    //获取表数据的行数map.filename:文件名
    int getLineCountMap(std::string filename);
    //获取某行某列的值
    const std::string getByCode(std::string filename, int code, const std::string &key);
private:
    //读取csv的一行.line:一行的内容
    void readCSVLine(const char *line, int index);
    
    VEC_MAP m_firstVector;                                          //第一行的vector
    MAP_CONTENT m_contentMap;                                       //内容map
    std::map<std::string, MAP_CONTENT> m_fileMap;                   //文件map
};


#endif /* defined(__lyGame__lyCSVReader__) */
