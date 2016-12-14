//
//  Subject.h
//
//  ly-Game
//
//  Created by loveyur on 2016/12/14
//  Copyright 2016 loveyur. All rights reserved.
//
//

#ifndef __CoreAppFramework__Subject__
#define __CoreAppFramework__Subject__

#include "ISubject.h"
#include <vector>

class IObserver;

class Subject : public ISubject
{
public:
    Subject();
    virtual ~Subject();
    
    // Attach an observer that uses regular attachment to this subject.
    virtual void attachObserver(IObserver* observer, const int observerId);
    
    // Detach an observer that uses regular attachment from this subject.
    virtual void detachObserver(IObserver* observer, const int observerId);
    
    // Notify observers that are attached to this subject via regular attachment.
    virtual void notify(const int observerId, void* changedBy = nullptr);
    
    // Check whether the observer is attached to this subject.
    virtual bool isAttached(IObserver* observer, const int observerId);
    
protected:
    std::vector<IObserver*>   fObservers;
};

#endif /* defined(__CoreAppFramework__Subject__) */
