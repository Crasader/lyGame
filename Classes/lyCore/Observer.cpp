//
//  Observer.cpp
//
//  Created by loveyur on 2016/12/11.
//
//

#include "Observer.h"
#include "ISubject.h"

Observer::Observer()
{
}

Observer::~Observer()
{
}

void Observer::init(ISubject* target)
{
    base = target;
}

void Observer::clearSubject()
{
    base = 0;
}

void Observer::attach(ISubject* subject, const int observerId)
{
    if (subject)
    {
        subject->attachObserver(this, observerId);
    }
}

void Observer::detach(ISubject* subject, const int observerId)
{
    if (subject)
    {
        subject->detachObserver(this, observerId);
    }
}

void Observer::update(ISubject* subject, const int observerId, void* changedBy)
{
    if (base)
    {
        base->notify(observerId, changedBy);
    }
}

