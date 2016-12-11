//
//  lyResourceUtil.cpp
//  ly-client
//  UI控件基类
//  Created by loveyur on 2016/11/11
//


#include "lyResourceUtil.h"

std::vector<std::string> lyResourceUtil::getResourceSearchPaths()
{
    std::vector<std::string> searchPath;
    searchPath.push_back("Published-iOS");
    searchPath.push_back("res");
    searchPath.push_back("ui");
    searchPath.push_back("images");
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    searchPath.push_back("sounds/ios");
#else
    searchPath.push_back("sounds/android");
#endif
    return searchPath;
    
}
