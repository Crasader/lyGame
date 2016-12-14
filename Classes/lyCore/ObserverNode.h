//
//  ObserverNode.h
//  client-vitamin
//
//  Created by Shinji Hiramatsu on 2014/05/24.
//  Copyright 2014 GCREST,Inc. All rights reserved.
//
//

#ifndef __client_vitamin__ObserverNode__
#define __client_vitamin__ObserverNode__

#include "IObserver.h"
#include "cocos2d.h"

class Subject;

class ObserverNode    : public cocos2d::Node, public IObserver
{
public:
    ObserverNode();
    virtual ~ObserverNode();
    
    virtual void attach(ISubject* subject, const int observerId = 0);
    virtual void detach(ISubject* subject, const int observerId = 0);
    virtual void update(ISubject* subject, const int observerId, void* changedBy) = 0;
    
    // Set up visible position
    virtual void setNodePosition(cocos2d::Node* node, cocos2d::Point pos);
    // Get current display ratio
    virtual float getDispRatio();
    // Get current display ratio
    virtual float getResolution(bool isHigh=true);
    // Get current widnows size
    virtual cocos2d::Size getWinSize();
};


#endif /* defined(__client_vitamin__ObserverNode__) */
