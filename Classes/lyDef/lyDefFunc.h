//
//  lyDefFunc.h
//  lyGame
//	函数宏定义头文件
//  Created by loveyur on 2016/11/24
//

#ifndef __lyGame__lyDefFunc__
#define __lyGame__lyDefFunc__

#include "cocos2d.h"
#include "lyCSVReader.h"
#include "lySoundID.h"
#include "lySoundManager.h"
//#include "lyMemoryPool.h"

using namespace cocos2d;
using namespace std;


//通过table取得数据
#define lyTableValue(strCSVPath, nId, strKey)   lyCSVReader::getInstance()->getValue(strCSVPath, nId, strKey)

//通过table取得数据条数
#define lyTableLines(strCSVPath)    lyCSVReader::getInstance()->getLineNum(strCSVPath)



#define playBgm(soundId)                lySoundManager::getInstance()->playBGM(soundId)
#define playLimitedBgm(soundId,param)   lySoundManager::getInstance()->playLimitedBGM(soundId,param)
#define stopBgm()                       lySoundManager::getInstance()->stopBGMNoWait()
#define playSe(soundId)                 lySoundManager::getInstance()->playSE(soundId)
#define playVoice(soundId)              lySoundManager::getInstance()->playVOICE(soundId)
#define playSeWithPitch(soundId, pitch)        lySoundManager::getInstance()->playSE(soundId, false, pitch)
#define stopVoice()                     lySoundManager::getInstance()->stopVOICENoWait()
#define stopSe()                        lySoundManager::getInstance()->stopSENoWait()


/*
#define CREATE_FUNC_POOL(__TYPE__) \
static __TYPE__* create()\
{\
__TYPE__ *pRet = lyMemoryPool<__TYPE__>::getInstance()->MemMalloc(); \
return pRet; \
}
*/
#endif /* __lyGame__lyDefFunc__ */
