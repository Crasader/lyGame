//
//  Subject.cpp
//
//  ly-Game
//
//  Created by loveyur on 2016/12/14
//  Copyright 2016 loveyur. All rights reserved.
//
//

#include "Subject.h"
#include "IObserver.h"
#include <vector>


Subject::Subject()
{
    
}

Subject::~Subject()
{
    fObservers.clear();
}

// Attach an observer that uses regular attachment to this subject.
void Subject::attachObserver(IObserver* observer, const int observerId)
{
    bool    found = false;
    std::vector<IObserver *>::iterator iter = fObservers.begin();
    while (iter != fObservers.end())
    {
        IObserver*  target = *iter;
        if (target == observer)
        {
            found = true;
            break;
        }
        iter++;
    }
    
    if (!found)
        fObservers.push_back(observer);
}

// Detach an observer that uses regular attachment from this subject.
void Subject::detachObserver(IObserver* observer, const int observerId)
{
    std::vector<IObserver *>::iterator iter = fObservers.begin();
    while (iter != fObservers.end())
    {
        IObserver*  target = *iter;
        if (target == observer)
        {
            iter = fObservers.erase( iter );
            break;
        }
        iter++;
    }
    
}

// Notify observers that are attached to this subject via regular attachment.
void Subject::notify(const int observerId, void* changedBy)
{
    std::vector<IObserver *>::iterator iter = fObservers.begin();
    while (iter != fObservers.end())
    {
        IObserver*  target = *iter;
        if (target)
        {
            target->update(this, observerId, changedBy);
        }
        iter++;
    }
    
}

// Check whether the observer is attached to this subject.
bool Subject::isAttached(IObserver* observer, const int observerId)
{
    bool    found = false;
    std::vector<IObserver *>::iterator iter = fObservers.begin();
    while (iter != fObservers.end())
    {
        if (*iter == observer)
        {
            found = true;
            break;
        }
        iter++;
    }
    return found;
}

