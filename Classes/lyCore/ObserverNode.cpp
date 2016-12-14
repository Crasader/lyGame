//
//  ObserverNode.cpp
//  client-vitamin
//
//  Created by Shinji Hiramatsu on 2014/05/24.
//  Copyright 2014 GCREST,Inc. All rights reserved.
//
//

#include "ObserverNode.h"
#include "ISubject.h"
#include "cocos2d.h"

#include "lyCommon.h"

USING_NS_CC;


ObserverNode::ObserverNode()
{
    
}

ObserverNode::~ObserverNode()
{
    
}

void ObserverNode::attach(ISubject* subject, const int observerId)
{
    if (subject)
    {
        subject->attachObserver(this, observerId);
    }
}

void ObserverNode::detach(ISubject* subject, const int observerId)
{
    if (subject)
    {
        subject->detachObserver(this, observerId);
    }
}

void ObserverNode::update(ISubject* subject, const int observerId, void* changedBy)
{
}

// Setup visible position
void ObserverNode::setNodePosition(cocos2d::Node* node, cocos2d::Point pos)
{
    node->setPosition(pos);
}

float ObserverNode::getDispRatio()
{
    Size size = Director::getInstance()->getWinSize();
    float ratio = size.width / DEFAULT_WIDTH;
    return ratio;
}

float ObserverNode::getResolution(bool isHigh)
{
    Size size = Director::getInstance()->getWinSize() * CCDirector::getInstance()->getContentScaleFactor();
    float  baseWidth = isHigh? DEFAULT_WIDTH: DEFAULT_LOW_WIDTH;
    return (size.width / baseWidth);
}


// Get current widnows size
cocos2d::Size ObserverNode::getWinSize()
{
    Size size = Director::getInstance()->getWinSize();
    return size;
}



