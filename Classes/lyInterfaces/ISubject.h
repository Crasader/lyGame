//
//  ISubject.h
//
//  ly-Game
//
//  Created by loveyur on 2016/12/14
//  Copyright 2016 loveyur. All rights reserved.
//
//

#ifndef __CoreAppFramework__ISubject_h
#define __CoreAppFramework__ISubject_h

class IObserver;

class ISubject
{
public:
    // Attach an observer that uses regular attachment to this subject.
    virtual void attachObserver(IObserver* observer, const int observerId = 0) = 0;
    
    // Detach an observer that uses regular attachment from this subject.
    virtual void detachObserver(IObserver* observer, const int observerId = 0) = 0;
    
    // Notify observers that are attached to this subject via regular attachment.
    virtual void notify(const int observerId, void* changedBy = 0) = 0;
    
    // Check whether the observer is attached to this subject.
    virtual bool isAttached(IObserver* observer, const int observerId) = 0;
};


#endif
