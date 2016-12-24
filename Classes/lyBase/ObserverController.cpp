//
//  ObserverController.cpp
//
//  ly-Game
//
//  Created by loveyur on 2016/12/14
//  Copyright 2016 loveyur. All rights reserved.
//
//

#include "ObserverController.h"
#include "cocos2d.h"

USING_NS_CC;

ObserverController::ObserverController(cocos2d::Node* obNode)   :
    _obsercerNode(obNode)
{
    
}

ObserverController::~ObserverController()
{
    
}


void ObserverController::attach(ISubject* subject, const int observerId)
{
    if (subject)
    {   // SubjectにこのObserverControllerをAttachする。
        subject->attachObserver(this, observerId);
    }
}

void ObserverController::detach(ISubject* subject, const int observerId)
{
    if (subject)
    {   // Subjectから、このObserverControllerをDetachする。
        subject->detachObserver(this, observerId);
    }
}

void ObserverController::update(ISubject* subject, const int observerId, void* changedBy)
{
    if (_obsercerNode)
    {   // ObserverNodeのUpdate処理
        
    }
}
