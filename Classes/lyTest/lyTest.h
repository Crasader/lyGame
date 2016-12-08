//
//  lyTest.h
//  ly-client
//	测试类
//  Created by loveyur on 2016/11/10
//

#ifndef ly_lyTest_h_
#define ly_lyTest_h_

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "spritebuilder/SpriteBuilder.h"

#include "VitaminCoreLayer.h"

#include "PartsBase.h"


class lyTest
{
public:
    lyTest();
	~lyTest();
    
    static lyTest* GetInstance();
    void TestScene(cocos2d::Scene* main);
    void TestWebView();
    void TestSound();
    void TestCCB();
    
    void WebViewCallback(cocos2d::Ref* pSender);
    void SoundCallback(cocos2d::Ref* pSender);
    void CCBCallback(cocos2d::Ref* pSender);
    
    
private:
    static lyTest* m_plyTest;
    
    cocos2d::Scene* m_pMainScene;
};

#endif /* defined(ly_lyTest_h_) */
