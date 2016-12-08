//
//  Observer.cpp
//  CoreAppFramework
//
//  Created by Shinji Hiramatsu on 2014/05/24.
//  Copyright 2014 GCREST,Inc. All rights reserved.
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

