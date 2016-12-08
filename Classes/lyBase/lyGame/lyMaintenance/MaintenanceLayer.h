//
//  MaintenanceLayer.h
//  client-vitamin
//
//  Created by 井戸 大拙 on 2014/06/04.
//
//

#ifndef __client_vitamin__MaintenanceLayer__
#define __client_vitamin__MaintenanceLayer__

#include "PartsBase.h"
#include "VitaminCoreLayer.h"

class MaintenanceLayer
: public VitaminCoreLayer
, public PartsBaseObj
{
public:
    CREATE_WITH_FORMAT_FUNC(MaintenanceLayer);
    
    MaintenanceLayer(){};
    virtual ~MaintenanceLayer(){};

    virtual void onEnter();

    virtual bool onAssignCCBMemberVariable(cocos2d::Ref* target, const char* memberVariableName, cocos2d::Node* node);

    virtual cocos2d::extension::Control::Handler onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char* pSelectorName);
    
    virtual void pressedBack(Caption *sender);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    virtual void keyBackClicked(cocos2d::Event* event);
#endif
    
private:
    
    virtual void btnEvent(Ref* sender, cocos2d::extension::Control::EventType eventType);
};


#endif /* defined(__client_vitamin__MaintenanceLayer__) */
