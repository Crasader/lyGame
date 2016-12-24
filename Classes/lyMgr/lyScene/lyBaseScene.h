//
//  lyBaseScene
//
//  ly-Game
//
//  Created by loveyur on 2016/12/14
//  Copyright 2016 loveyur. All rights reserved.
//
//

#ifndef __lyGame__SceneManager__
#define __lyGame__SceneManager__

#include "ISceneInterfaces.h"
#include "lyInclude.h"

class lyBaseScene  : public cocos2d::Ref, public ISceneInterfaces
{
public:
    lyBaseScene();
    virtual ~lyBaseScene();
    
    virtual bool init();
    
    virtual bool nextScene();
    
    virtual bool previousScene();
    
    virtual cocos2d::Scene* runWithScene(const SceneID sid, SceneParameter* params = nullptr);

    virtual cocos2d::Scene* changeScene(const SceneID sid, SceneParameter* params = nullptr);
    
    cocos2d::Scene* pushScene(SceneID sid, SceneParameter* params);

    void popScene();

    virtual cocos2d::Scene* createScene(const SceneID sid, SceneParameter* params = nullptr);
    
    virtual cocos2d::Layer* createTopLayer(const SceneID sid, SceneParameter* params = nullptr);
    
};

#endif /* defined(__lyGame__SceneManager__) */
