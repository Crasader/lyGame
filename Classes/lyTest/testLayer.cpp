//
//  testLayer.cpp
//
//  ly-Game
//
//  Created by loveyur on 2016/12/14
//  Copyright 2016 loveyur. All rights reserved.
//
//

#include "testLayer.h"
#include "ApplicationManager.h"
#include "UISceneID.h"

#include "lyCSVReader.h"
#include "lyDefFunc.h"

#include "lyActionGroup.h"
#include "lyActionManager.h"
#include "lyPlistManager.h"
//#include "lyRole.h"


USING_NS_CC;
USING_NS_CC_EXT;


testLayer::testLayer()
: _isMoving(false)
, _nameLabel(nullptr)
,_myRole(nullptr)
{
}

testLayer::~testLayer()
{
    CC_SAFE_RELEASE_NULL(_nameLabel);
    CC_SAFE_RELEASE_NULL(_myRole);
}


void testLayer::completedAnimationSequenceNamed(const char *name)
{

}

void testLayer::onEnter()
{
    lyBaseLayer::onEnter();
}

void testLayer::onExit()
{
    lyBaseLayer::onExit();
}


bool testLayer::onAssignCCBMemberVariable(Ref *pTarget, const char *pMemberVariableName, Node *pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "_nameLabel", cocos2d::Label*, _nameLabel);
    //CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "_myRole", cocos2d::Node*, _myRole);
    
    //CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "_sprtest", cocos2d::Sprite *, _sprtest);
    return false;
}

cocos2d::extension::Control::Handler testLayer::onResolveCCBCCControlSelector(Ref* pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressCtrlButton", testLayer::onPressCtrlButton);
    return nullptr;
}
cocos2d::SEL_MenuHandler testLayer::onResolveCCBCCMenuItemSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onPressMenuButton", testLayer::onClickedMenuButton);
    return nullptr;
}

void testLayer::setSceneParameter(testLayerParameter *param)
{
    
}
bool testLayer::onTouchBegan(cocos2d::Touch* touches, cocos2d::Event* event)
{
    
    return true;
}

void testLayer::onTouchEnded(cocos2d::Touch* touches, cocos2d::Event* event)
{
  
}

void testLayer::onClickedMenuButton(cocos2d::Ref *sender)
{
    CCLOG("onClickedMenuButton");
    ApplicationManager::getInstance()->changeScene(SCENE_LOGIN);
}



void testLayer::onPressCtrlButton(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
    //CCLOG("onPressCtrlButton");
    //csv表格读取测试
    
    std::string strPath1 = lyTableValue("Table/Map.csv", 2, "MSPath");
    CCLOG("------------------------------");
    CCLOG("strPath1=%s",strPath1.c_str());
    
    std::string SprId = lyTableValue(strPath1, 0, "SprId");
    CCLOG("SprId=%s",SprId.c_str());
    
    int Line1 = lyTableLines("Table/Map.csv");
    CCLOG("Map Line1=%d",Line1);
    
    int Line2 = lyTableLines(strPath1);
    CCLOG("strPath1=%s,Line2=%d",strPath1.c_str(),Line2);
    
    
    lyPlistManager::getInstance()->loadRolePlist("Texture_Role_ant");
    /*
    lyActionGroup* pActGroup = lyActionGroup::Create();
    if ( pActGroup )
    {
        lyAction* pAction = lyAction::Create();
        if (pAction)
        {
            for ( unsigned char byIndex = 0; byIndex < 10; byIndex++ )
            {
                char szName[50];
                memset(szName, 0, sizeof(char)*50 );
                sprintf(szName, "Role/1/Stand/%03d.png",byIndex);
                pAction->AddFrame(szName);
            }
            pActGroup->AddAction(pAction, 0);
        }
        lyActionManager::GetInstance()->AddGroup(pActGroup, 1);
    }
    
    lyRole* pRole = lyRole::Create();
    if (_myRole && pRole) {
        
        pRole->setRoleId(0);
        pRole->setGroupId(0);
        pRole->SetPosition(100, 100);
        _myRole->addChild(pRole);
    }
    //*/
    
}

