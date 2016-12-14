//
//  lyResourceUtil.h
//
//  ly-Game
//
//  Created by loveyur on 2016/11/11
//  Copyright 2016 loveyur. All rights reserved.
//
//

#ifndef ly_lyResourceUtil_h_
#define ly_lyResourceUtil_h_

#include "cocos2d.h"

class lyResourceUtil
{
public:
    static std::vector<std::string> getResourceSearchPaths();
    static std::vector<std::string> getResourceResolutionOrder();
    
    
};

#endif /* defined(ly_lyResourceUtil_h_) */
