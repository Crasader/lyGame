//
//  Observer.h
//
//  Created by loveyur on 2016/12/11.
//
//

#ifndef __CoreAppFramework__Observer__
#define __CoreAppFramework__Observer__

#include "IObserver.h"

class ISubject;

class Observer    : public IObserver
{
public:
    Observer();
    virtual ~Observer();
    virtual void init(ISubject* target);
    virtual void clearSubject();
    virtual void attach(ISubject* subject, const int observerId = 0);
    virtual void detach(ISubject* subject, const int observerId = 0);
    virtual void update(ISubject* subject, const int observerId, void* changedBy);
    
public:
    ISubject*   base;
};

#endif /* defined(__CoreAppFramework__Observer__) */
