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
#include "lyFunc.h"

USING_NS_CC;
USING_NS_CC_EXT;


testLayer::testLayer()
: _isMoving(false)
, _nameLabel(nullptr)
{
}

testLayer::~testLayer()
{
    CC_SAFE_RELEASE_NULL(_nameLabel);
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
    lyCSVReader::getInstance()->parse("Table/Texture.csv");
   /*
    //通过table取得数据
    #define lyTable(tName, nId, strKey)\
    lyCSVReader::getInstance()->getByCode(string("Table/")+tName+".csv", nId, strKey)
    //获得table
    #define lyTablePath(tPath, nId, strKey)\
    lyCSVReader::getInstance()->getByCode(tPath, nId, strKey)
    //通过table取得数据条数
    #define lyTableLineCount(tName)\
    lyCSVReader::getInstance()->getLineCountMap(string("Table/")+tName+".csv")
    //获得table数据条数
    #define lyTablePathLineCount(tPath)\
    lyCSVReader::getInstance()->getLineCountMap(tPath)
    */
    
    
    std::string strPath1 = lyTableName("Map", 2, "MSPath");
    CCLOG("------------------------------");
    CCLOG("strPath1=%s",strPath1.c_str());
    
    std::string SprId = lyTablePath(strPath1, 0, "SprId");
    CCLOG("SprId=%s",SprId.c_str());
    
    int Line1 = lyTableLineCount("Map");
    CCLOG("Map Line1=%d",Line1);
    
    int Line2 = lyTablePathLineCount(strPath1);
    CCLOG("strPath1=%s,Line2=%d",strPath1.c_str(),Line2);
    
    
    
    
    
    
}

