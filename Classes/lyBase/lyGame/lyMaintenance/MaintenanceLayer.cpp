//
//  MaintenanceLayer.cpp
//  client-vitamin
//
//  Created by 井戸 大拙 on 2014/06/04.
//
//

#include "MaintenanceLayer.h"


void MaintenanceLayer::onEnter()
{
    VitaminCoreLayer::onEnter();
}

///CCBMemberVariableAssigner
bool MaintenanceLayer::onAssignCCBMemberVariable(cocos2d::Ref* pTarget, const char* pMemberVariableName, cocos2d::Node* pNode)
{
    return PartsBaseObj::onAssignCCBMemberVariable(pMemberVariableName, pNode);
}

cocos2d::extension::Control::Handler MaintenanceLayer::onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "btnEvent:",  MaintenanceLayer::btnEvent);
    return nullptr;
}

/**
 *  ボタンイベント
 */
void MaintenanceLayer::btnEvent(Ref* sender, cocos2d::extension::Control::EventType eventType)
{
    if(_isMovePage)
    {
        return;
    }
    
    cocos2d::extension::ControlButton* button = dynamic_cast<cocos2d::extension::ControlButton*>(sender);
    if(button)
    {
        if(eventType == cocos2d::extension::Control::EventType::TOUCH_UP_INSIDE ||
           eventType == cocos2d::extension::Control::EventType::TOUCH_UP_OUTSIDE)
        {
            
            if(!button->getName().compare("btn_detail"))
            {
                
            }
            else if(!button->getName().compare("btn_back"))
            {
                pressedBack(nullptr);
            }
        }
    }
}
//--

void MaintenanceLayer::pressedBack(Caption *sender)
{
    if(!_isMovePage)
    {
        _isMovePage = true;
        //ApplicationManager::getInstance()->changeScene(SCENE_APP_TOP);
    }
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
void MaintenanceLayer::keyBackClicked(cocos2d::Event* event)
{
    pressedBack(nullptr);
}
#endif


