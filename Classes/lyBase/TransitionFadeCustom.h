//
//  TransitionFadeCustom.h
//  client-vitamin
//
//  Created by 竹田 篤史 on 2014/11/04.
//
//

#ifndef __lyGame__TransitionFadeCustom__
#define __lyGame__TransitionFadeCustom__

#include "cocos2d.h"

class TransitionSceneCustom : public cocos2d::TransitionScene
{
public:
    void setNewScene(float dt);
    void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags);
    void cleanup();

    virtual void onEnter();
    virtual void onExit();
};

/** @brief TransitionFade:
 Fade out the outgoing scene and then fade in the incoming scene.'''
 */
class CC_DLL TransitionFadeCustom : public TransitionSceneCustom
{
public:
    /** creates the transition with a duration and with an RGB color
     * Example: FadeTransition::create(2, scene, Color3B(255,0,0); // red color
     */
    static TransitionFadeCustom* create(float duration, cocos2d::Scene* scene, const cocos2d::Color3B& color, bool exitWithMask = false, bool enterWithMask = false);
    static TransitionFadeCustom* create(float duration, cocos2d::Scene* scene, bool exitWithMask = false, bool enterWithMask = false);
    
    /**
     * @js NA
     * @lua NA
     */
    virtual void onEnter() override;
    /**
     * @js NA
     * @lua NA
     */
    virtual void onExit() override;
    
CC_CONSTRUCTOR_ACCESS:
    TransitionFadeCustom();
    virtual ~TransitionFadeCustom();
    
    /** initializes the transition with a duration and with an RGB color */
    bool initWithDuration(float t, cocos2d::Scene* scene, const cocos2d::Color3B& color, bool exitWithMask = false, bool enterWithMask = false);
    bool initWithDuration(float t, cocos2d::Scene* scene, bool exitWithMask = false, bool enterWithMask = false);
    
public:
    void setChangeSceneCallback(const std::function<void()> &callback) {
        _changeSceneCallback = callback;
    }
    
protected:
    cocos2d::Color4B _color;
    bool _exitWithMask;
    bool _enterWithMask;
    cocos2d::LayerColor* _layerColor;
    cocos2d::Sprite *_mask;
    
private:
    CC_DISALLOW_COPY_AND_ASSIGN(TransitionFadeCustom);
    std::function<void()> _changeSceneCallback;

    void startExitSceneEffect();
    void startEnterSceneEffect();
    void changeScene();
};

#endif /* defined(__lyGame__TransitionFadeCustom__) */
