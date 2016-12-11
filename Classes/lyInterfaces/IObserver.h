//
//  IObserver.h
//  CoreAppFramework
//
//  Created by Shinji Hiramatsu on 2014/05/24.
//  Copyright 2014 GCREST,Inc. All rights reserved.
//

#ifndef __CoreAppFramework__IObserver_h
#define __CoreAppFramework__IObserver_h

class ISubject;

class IObserver
{
public:
    virtual void attach(ISubject* subject, const int observerId = 0) = 0;
    virtual void detach(ISubject* subject, const int observerId = 0) = 0;
    virtual void update(ISubject* subject, const int observerId, void* changedBy) = 0;
};

#endif
