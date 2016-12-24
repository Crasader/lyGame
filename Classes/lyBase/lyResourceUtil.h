//
//  lyResourceUtil.h
//
//  ly-Game
//
//  Created by loveyur on 2016/11/11
//  Copyright 2016 loveyur. All rights reserved.
//
//

#ifndef __lyGame__lyResourceUtil_h_
#define __lyGame__lyResourceUtil_h_

#include "cocos2d.h"

class lyResourceUtil
{
public:
    static std::vector<std::string> getResourceSearchPaths();
    static std::vector<std::string> getResourceResolutionOrder();
    
    //资源路径的获取
    static std::string getCardFacePlistPath(int64_t cardId, bool isZoom);
};

#endif /* defined(__lyGame__lyResourceUtil_h_) */
