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


#define MAP_ONE_LINE std::map<std::string, std::string>          //key为首行字符串, value为此列字符串
#define MAP_MUTI_LINE std::map<int, MAP_ONE_LINE>                  //key为code, value为一行map
#define VEC_COLUMN_NAME  std::vector<std::pair<std::string, int>>


class lyCSVReader
{
public:
    lyCSVReader();
    ~lyCSVReader();

    static lyCSVReader* getInstance();
    //解析csv
    void Parse(std::string strCSVPath);
    //获取某CSV表的行数
    int getLineNum(std::string strCSVPath);
    //获取某行某列的值
    const std::string getValue(std::string strCSVPath, int nRowId, const std::string &strColumn);
    

    //获取内容map
    const MAP_MUTI_LINE* getOneFile(std::string strCSVPath);
    //获取某一行value
    const MAP_ONE_LINE* getOneLine(std::string strCSVPath, int code);
    
    

private:
    //读取csv的一行
    void readCSVLine(const char *line, int index);

    
private:
    VEC_COLUMN_NAME m_VectorColumnName;                                          //第一行的vector
    MAP_MUTI_LINE m_mapOneFile;                                       //内容map
    std::map<std::string, MAP_MUTI_LINE> m_mapMutiFile;                   //文件map
};


#endif /* defined(__lyGame__lyCSVReader__) */
