//
//  CCBCustomClassLoaderLibrary.cpp
//  client-vitamin
//
//  Created by 大久保 孝一郎 on 2014/06/26.
//
//

#include "CCBCustomClassLoaderLibrary.h"

//#include "lyCCBBaseNodeLoader.h"
//#include "Caption.h"
//#include "MaintenanceLayer.h"

#include "spritebuilder/CCBSelectorResolver.h"
#include "spritebuilder/CCBMemberVariableAssigner.h"
#include "spritebuilder/CCBAnimationManager.h"
#include "spritebuilder/CCBReader.h"
#include "spritebuilder/CCNodeLoader.h"
#include "spritebuilder/CCNodeLoaderLibrary.h"
#include "CoreCCBNode.h"

#include "CCBCustomClassLoaderLibrary.h"
#include "spritebuilder/SpriteBuilder.h"
#include "BaseNodeLoader.h"
#include "PublisherLayer.h"


USING_NS_CC;
USING_NS_CC_EXT;
using namespace spritebuilder;


// インスタンス変数
static CCBCustomClassLoaderLibrary *s_CustomClassLoaderLibrary = nullptr;

// コンストラクタ
CCBCustomClassLoaderLibrary::CCBCustomClassLoaderLibrary()
{

    m_customClassEntry = {
        //{ "PublisherLayer", PublisherLayerLoader::loader()}

        //{ "MaintenanceLayer", lyCCBBaseNodeLoader<MaintenanceLayer>::loader()}
    };

}

// デストラクタ
CCBCustomClassLoaderLibrary::~CCBCustomClassLoaderLibrary() {
}

// カスタムクラス登録
void CCBCustomClassLoaderLibrary::registerCustomClassLoader() {
    
    //spritebuilder::NodeLoaderLibrary *nodeLoaderLibrary = spritebuilder::NodeLoaderLibrary::getInstance();
    for (int i=0; i<m_customClassEntry.size(); i++) {
        //nodeLoaderLibrary->registerNodeLoader(m_customClassEntry[i].pClassName, m_customClassEntry[i].pCCNodeLoader);
    }
}

// カスタムクラス登録解除
void CCBCustomClassLoaderLibrary::unregisterCustomClassLoader() {
    spritebuilder::NodeLoaderLibrary *nodeLoaderLibrary = spritebuilder::NodeLoaderLibrary::getInstance();
    
    for (int i=0; i<m_customClassEntry.size(); i++) {
        nodeLoaderLibrary->unregisterNodeLoader(m_customClassEntry[i].pClassName);
    }
}

// インスタンス取得
CCBCustomClassLoaderLibrary* CCBCustomClassLoaderLibrary::getInstance() {
    if(s_CustomClassLoaderLibrary == NULL) {
        s_CustomClassLoaderLibrary = new CCBCustomClassLoaderLibrary;
    }
    return s_CustomClassLoaderLibrary;
}

// インスタンス解放
void CCBCustomClassLoaderLibrary::purgeSharedCustomClassLoaderLibrary() {
    CC_SAFE_DELETE(s_CustomClassLoaderLibrary);
}

// 指定したカスタムクラスのローダー登録を変更
void CCBCustomClassLoaderLibrary::changeRegisterCustomClassLoader(const char* className, spritebuilder::NodeLoader* loader) {
    spritebuilder::NodeLoaderLibrary *nodeLoaderLibrary = spritebuilder::NodeLoaderLibrary::getInstance();
    
    for (int i=0; i<m_customClassEntry.size(); i++) {
        if (!strcmp(m_customClassEntry[i].pClassName, className)) {
            // 指定したクラス名の登録を解除
            nodeLoaderLibrary->unregisterNodeLoader(m_customClassEntry[i].pClassName);
            
            m_customClassEntry[i].pCCNodeLoader = loader;
            
            nodeLoaderLibrary->registerNodeLoader(m_customClassEntry[i].pClassName, m_customClassEntry[i].pCCNodeLoader);
            
            break;
        }
    }
}

