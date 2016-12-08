//
//  lyTest.h
//  ly-client
//
//  Created by loveyur on 2016/11/10
//

#include "lyTest.h"
#include "UIButton.h"
#include "lyWebView.h"
#include "lySoundManager.h"
#include "SimpleAudioEngine.h"
#include "platform/CCFileUtils.h"
#include "lyResourceUtil.h"
#include "ApplicationManager.h"

#include "CCBCustomClassLoaderLibrary.h"
#include "spritebuilder/CCBSelectorResolver.h"
#include "spritebuilder/CCBMemberVariableAssigner.h"
#include "spritebuilder/CCBAnimationManager.h"
#include "spritebuilder/CCBReader.h"
#include "spritebuilder/CCNodeLoader.h"
#include "spritebuilder/CCNodeLoaderLibrary.h"
#include "CoreCCBNode.h"


USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;



lyTest *lyTest::m_plyTest = NULL;


lyTest::lyTest()
:m_pMainScene(nullptr)
{
	// TODO: auto generated code
}

lyTest::~lyTest()
{
	// TODO: auto generated code
}

lyTest*  lyTest::GetInstance()
{
    if (m_plyTest == NULL)
    {
        m_plyTest = new lyTest();
    }
    
    return m_plyTest;
}

void lyTest::TestScene(cocos2d::Scene* main)
{
    m_pMainScene = main;
    //创建一个图片
    auto searchPaths = lyResourceUtil::getResourceSearchPaths();
    FileUtils::getInstance()->setSearchPaths(searchPaths);

    CCBCustomClassLoaderLibrary::getInstance()->registerCustomClassLoader();
    
    
    //VitaminSceneManager* sceneMgr = new VitaminSceneManager;
    //ApplicationManager::getInstance()->setSceneManager(sceneMgr);
    //VitaminCommandManager* cmdMgr = new VitaminCommandManager;
    //ApplicationManager::getInstance()->setCommandManager(cmdMgr);
    
    auto sprite = Sprite::create("HelloWorld.png");
    sprite->setPosition(Vec2(200, 200));
    m_pMainScene->addChild(sprite);

    //创建一个按钮，每次点击按钮都打开一个外链
    Button* btnTest = Button::create();
    btnTest->loadTextureNormal("HelloWorld.png");
    btnTest->loadTexturePressed("HelloWorld.png");
    btnTest->setPosition(Vec2(400, 200));
    btnTest->setZoomScale(0.4f);
    btnTest->setPressedActionEnabled(true);
    m_pMainScene->addChild(btnTest);
    btnTest->setOpacity(100);
   
    
    this->TestWebView();
    this->TestSound();
    this->TestCCB();
}
void lyTest::TestWebView()
{
	cocos2d::log("TestWebView");
    auto closeItem = MenuItemImage::create(
                                           "ui/zokusei_01.png",
                                           "ui/zokusei_02.png",
                                           CC_CALLBACK_1(lyTest::WebViewCallback, this));
    
    closeItem->setPosition(Vec2(100 ,100));
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    m_pMainScene->addChild(menu, 1);

}
void lyTest::TestSound()
{
	cocos2d::log("TestSound");
    auto closeItem = MenuItemImage::create(
                                           "ui/zokusei_02.png",
                                           "ui/zokusei_03.png",
                                           CC_CALLBACK_1(lyTest::SoundCallback, this));
    
    closeItem->setPosition(Vec2(200 ,100));
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    m_pMainScene->addChild(menu, 1);
}
void lyTest::TestCCB()
{
	cocos2d::log("TestCCB");
    auto closeItem = MenuItemImage::create(
                                           "ui/zokusei_03.png",
                                           "ui/zokusei_04.png",
                                           CC_CALLBACK_1(lyTest::CCBCallback, this));
    
    closeItem->setPosition(Vec2(300 ,100));
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    m_pMainScene->addChild(menu, 1);

}
void lyTest::WebViewCallback(Ref* pSender)
{
	cocos2d::log("WebViewCallback");
    lyWebView::openWebView("https://www.hao123.com/");
}
void lyTest::SoundCallback(Ref* pSender)
{
	cocos2d::log("SoundCallback");
    lySoundManager::getInstance()->playBGM("sounds/bgmusic", false);
}


void lyTest::CCBCallback(Ref* pSender)
{
    cocos2d::log("CCBCallback");
    /*
    //ApplicationManager::getInstance()->changeScene(SCENE_MAINTENANCE);
    CCBReader* pReader = new CCBReader(CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary());
    pReader->autorelease();
    //设置ccbi的目录
    pReader->setCCBRootPath("ccbi");
    
    //加载ccbi
    CCNode* pNode = pReader->readNodeGraphFromFile("MaintenanceLayer.ccbi",pOwner);
    return pNode;
* /
   
    spritebuilder::CCBReader * ccbReader = new spritebuilder::CCBReader(spritebuilder::NodeLoaderLibrary::getInstance());
    Node* node = ccbReader->readNodeGraphFromFile("ccbi/VitaminPurchaseLoading");
    node->setTag(999);
    m_pMainScene->addChild(node, INT_MAX);
    node->setVisible(true);
    
     spritebuilder::NodeLoaderLibrary * ccNodeLoaderLibrary = spritebuilder::NodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    spritebuilder::CCBReader * ccbReader = new spritebuilder::CCBReader(ccNodeLoaderLibrary);
    CCNode * node = ccbReader->readNodeGraphFromFile("ccbi/VitaminPurchaseLoading");
    m_pMainScene->addChild(node);
     //*/

}
