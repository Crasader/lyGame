//
//  ObserverController.h
//
//  Created by loveyur on 2016/12/11.
//
//

#ifndef __CoreAppFramework__ObserverController__
#define __CoreAppFramework__ObserverController__

#include "ISubject.h"
#include "IObserver.h"
#include "cocos2d.h"

class ObserverController  : public IObserver
{
public:
    ObserverController(cocos2d::Node* obNode);
    virtual ~ObserverController();
    
    virtual void attach(ISubject* subject, const int observerId = 0) = 0;
    virtual void detach(ISubject* subject, const int observerId = 0) = 0;
    virtual void update(ISubject* subject, const int observerId, void* changedBy) = 0;
    
protected:
    cocos2d::Node*  _obsercerNode;
};

#endif /* defined(__CoreAppFramework__ObserverController__) */
