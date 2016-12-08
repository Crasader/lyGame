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
    searchPath.push_back("Resources");
    searchPath.push_back("Resources/Published-iOS");
    searchPath.push_back("Resources/sounds");
    return searchPath;
    
}
