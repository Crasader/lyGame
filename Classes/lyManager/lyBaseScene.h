//
//  lyBaseScene
//
//  Created by loveyur on 2016/12/07.
//
#ifndef __CoreAppFramework__SceneManager__
#define __CoreAppFramework__SceneManager__

#include "ISceneInterfaces.h"
#include "cocos2d.h"

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

#endif /* defined(__CoreAppFramework__SceneManager__) */
