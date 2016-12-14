//
//  PositionUtil.h
//
//  ly-Game
//
//  Created by loveyur on 2016/12/14
//  Copyright 2016 loveyur. All rights reserved.
//
//

#ifndef Donut_PositionUtil_h
#define Donut_PositionUtil_h

#include "cocos2d.h"

namespace PositionUtil {
    
    /**
     * 全体からみて自分の位置的な？
     */
    static cocos2d::Vec2 getRootPosition(cocos2d::Node *node)
    {
        cocos2d::Vec2 totalPos = cocos2d::Vec2::ZERO;
        auto parent = node->getParent();
        while (parent != nullptr)
        {
            cocos2d::Vec2 parentPos = parent->getPosition();
            totalPos.x += parentPos.x;
            totalPos.y += parentPos.y;
            parent = parent->getParent();
        }
        return cocos2d::Vec2(totalPos.x + node->getPosition().x, totalPos.y + node->getPosition().y);
    }
    
}

#endif
