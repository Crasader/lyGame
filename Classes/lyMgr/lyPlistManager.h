//
//  lyPlistManager.h
//  lyGame
//
//  Created by loveyur on 2016/12/24
//  Copyright 2016 loveyur. All rights reserved.
//
//

#ifndef __lyGame__lyPlistManager__
#define __lyGame__lyPlistManager__

#include "lyInclude.h"

class lyPlistManager
{
public:
    lyPlistManager();
    ~lyPlistManager();
    
    static lyPlistManager* getInstance();
    
    void loadMapPlist(std::string textureName);
    void loadRolePlist(std::string textureName);
    void loadActionPlist(std::string texPath);
    void loadTexturePlist(std::string textureName);
    
    
};


#endif /* defined(__lyGame__lyPlistManager__) */
