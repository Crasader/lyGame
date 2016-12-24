//
//  lyFunc.h
//  lyGame
//	函数宏定义头文件
//  Created by loveyur on 2016/11/24
//

#ifndef __lyGame__lyFunc_h
#define __lyGame__lyFunc_h

#include "cocos2d.h"
#include "lyCSVReader.h"

using namespace cocos2d;
using namespace std;


//通过table取得数据
#define lyTableName(tName, nId, strKey)\
lyCSVReader::getInstance()->getByCode(string("Table/")+tName+".csv", nId, strKey)
//获得table
#define lyTablePath(tPath, nId, strKey)\
lyCSVReader::getInstance()->getByCode(tPath, nId, strKey)
//通过table取得数据条数
#define lyTableLineCount(tName)\
lyCSVReader::getInstance()->getLineCountMap(string("Table/")+tName+".csv")
//获得table数据条数
#define lyTablePathLineCount(tPath)\
lyCSVReader::getInstance()->getLineCountMap(tPath)






#endif /* __lyGame__lyFunc_h */
