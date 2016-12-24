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
#define lyTableValue(strCSVPath, nId, strKey)\
lyCSVReader::getInstance()->getValue(strCSVPath, nId, strKey)

//通过table取得数据条数
#define lyTableLines(strCSVPath)\
lyCSVReader::getInstance()->getLineNum(strCSVPath)






#endif /* __lyGame__lyFunc_h */
