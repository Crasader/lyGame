//
//  IObserver.h
//
//  ly-Game
//
//  Created by loveyur on 2016/12/14
//  Copyright 2016 loveyur. All rights reserved.
//
//

#ifndef __lyGame__IObserver_h
#define __lyGame__IObserver_h

class ISubject;

class IObserver
{
public:
    virtual void attach(ISubject* subject, const int observerId = 0) = 0;
    virtual void detach(ISubject* subject, const int observerId = 0) = 0;
    virtual void update(ISubject* subject, const int observerId, void* changedBy) = 0;
};

#endif
