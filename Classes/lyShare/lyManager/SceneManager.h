//
//  SceneManager.h
//  CoreAppFramework
//
//  Created by Shinji Hiramatsu on 2014/05/24.
//  Copyright 2014 GCREST,Inc. All rights reserved.
//

#ifndef __CoreAppFramework__SceneManager__
#define __CoreAppFramework__SceneManager__

#include "ISceneManager.h"
#include "cocos2d.h"


// Sceneの管理を行うクラスです。
class SceneManager  : public cocos2d::Ref, public ISceneManager
{
public:
    // コンストラクタ
    SceneManager();
    // デストラクタ
    virtual ~SceneManager();
    
    // 初期化
    virtual bool init();
    
    // 次のSceneに遷移
    virtual bool nextScene();
    
    // 前のSceneに遷移
    virtual bool previousScene();
    
    // 指定されたSceneクラスを生成し、画面に表示しているSceneと入れ替えます。
    virtual cocos2d::Scene* runWithScene(const SceneID sid, SceneParameter* params = nullptr);

    // 指定されたSceneクラスを生成し、画面に表示しているSceneと入れ替えます。
    virtual cocos2d::Scene* changeScene(const SceneID sid, SceneParameter* params = nullptr);
    
    // 指定されたSceneクラスを生成し、pushします
    cocos2d::Scene* pushScene(SceneID sid, SceneParameter* params);

    // SceneのPopをします
    void popScene();

    // 指定したSceneクラスを生成します。
    // Sceneの生成のみを行い、画面上のSceneの入れ替えは行わない。
    virtual cocos2d::Scene* createScene(const SceneID sid, SceneParameter* params = nullptr);
    
    // 指定したSceneのTopレイヤーを作成します。
    virtual cocos2d::Layer* createTopLayer(const SceneID sid, SceneParameter* params = nullptr);
    
};

#endif /* defined(__CoreAppFramework__SceneManager__) */
