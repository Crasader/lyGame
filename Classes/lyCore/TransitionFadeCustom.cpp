//
//  TransitionFadeCustom.cpp
//  client-vitamin
//
//  Created by 竹田 篤史 on 2014/11/04.
//
//

#include "TransitionFadeCustom.h"

USING_NS_CC;

static const unsigned int kSceneFade = 0xFADEFADE;

static float SRC_SCALE = 12.0f;
static float SHRINK1_DURATION = 0.4f;
static float DST_SCALE1 = 0.6f;
static float HOP_DURATION = 0.3f;
static float DST_SCALE2 = 0.8f;
static float SHRINK2_DURATION = 0.1f;
static float EXPAND_DURATION = 0.8f;
static float LAST_DELAY = 0.05f;

// custom onEnter
void TransitionSceneCustom::onEnter()
{
    Scene::onEnter();
    
    // disable events while transitions
    _eventDispatcher->setEnabled(false);
    
    // outScene should not receive the onEnter callback
    // only the onExitTransitionDidStart
    _outScene->onExitTransitionDidStart();
}

// custom onExit
void TransitionSceneCustom::onExit()
{
    Scene::onExit();
    
    _eventDispatcher->setEnabled(true);

    // _inScene should not receive the onEnter callback
    // only the onEnterTransitionDidFinish
    // _inScene->onEnter();
    _inScene->onEnterTransitionDidFinish();
}

void TransitionSceneCustom::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    Scene::draw(renderer, transform, flags);
    
    if( _isInSceneOnTop ) {
        if (_outScene) {
            _outScene->visit(renderer, transform, flags);
        }
        if (_inScene) {
            _inScene->visit(renderer, transform, flags);
        }
    } else {
        if (_inScene) {
            _inScene->visit(renderer, transform, flags);
        }
        if (_outScene) {
            _outScene->visit(renderer, transform, flags);
        }
    }
}

// custom cleanup
void TransitionSceneCustom::cleanup()
{
    Scene::cleanup();
}

void TransitionSceneCustom::setNewScene(float dt)
{
    CC_UNUSED_PARAM(dt);
    
    this->unschedule(schedule_selector(TransitionSceneCustom::setNewScene));
    
    // Before replacing, save the "send cleanup to scene"
    Director *director = Director::getInstance();
    
    director->replaceScene(_inScene);
}

TransitionFadeCustom::TransitionFadeCustom()
: _exitWithMask(false)
, _enterWithMask(false)
, _layerColor(nullptr)
, _mask(nullptr)
, _changeSceneCallback(nullptr)
{
}
TransitionFadeCustom::~TransitionFadeCustom()
{
}

TransitionFadeCustom* TransitionFadeCustom::create(float duration, Scene *scene, const Color3B& color, bool exitWithMask /* = false */, bool enterWithMask /* = false */)
{
    TransitionFadeCustom * transition = new TransitionFadeCustom();
    transition->initWithDuration(duration, scene, color, exitWithMask, enterWithMask);
    transition->autorelease();
    return transition;
}

TransitionFadeCustom* TransitionFadeCustom::create(float duration, Scene* scene, bool exitWithMask /* = false */, bool enterWithMask)
{
    return TransitionFadeCustom::create(duration, scene, Color3B::BLACK, exitWithMask, enterWithMask);
}

bool TransitionFadeCustom::initWithDuration(float duration, Scene *scene, const Color3B& color, bool exitWithMask /* = false */, bool enterWithMask)
{
    if (TransitionScene::initWithDuration(duration, scene))
    {
        _color.r = color.r;
        _color.g = color.g;
        _color.b = color.b;
        _color.a = 0;
        
        _exitWithMask = exitWithMask;
        _enterWithMask = enterWithMask;
    }
    return true;
}

bool TransitionFadeCustom::initWithDuration(float t, Scene *scene, bool exitWithMask /* = false */, bool enterWithMask /* = false */)
{
    this->initWithDuration(t, scene, Color3B::BLACK, exitWithMask, enterWithMask);
    return true;
}

void TransitionFadeCustom :: onEnter()
{
    TransitionSceneCustom::onEnter();

    if (_exitWithMask || _enterWithMask)
    {
        _layerColor = LayerColor::create(_color);

        _mask = Sprite::create("images/effect/efe_00171_masktest.png");
        auto visibleSize = Director::getInstance()->getVisibleSize();
        _mask->setPosition(visibleSize.width * 0.5f, visibleSize.height * 0.5f);
        _mask->setScale(SRC_SCALE);
        
        auto clip = ClippingNode::create();
        clip->setAlphaThreshold(0.01f);
        clip->setStencil(_mask);
        clip->setInverted(true);
        clip->addChild(_layerColor);
        
        addChild(clip, 2, kSceneFade);
    }
    else
    {
        _layerColor = LayerColor::create(_color);
        addChild(_layerColor, 2, kSceneFade);
    }

    _inScene->setVisible(false);
    
    startExitSceneEffect();
}

void TransitionFadeCustom::onExit()
{
    TransitionSceneCustom::onExit();
    this->removeChildByTag(kSceneFade, false);
}

void TransitionFadeCustom::startExitSceneEffect()
{
    if (_exitWithMask)
    {
        _layerColor->setOpacity(255);
        
        auto exitEffect = Sequence::create(
            ScaleTo::create(SHRINK1_DURATION, DST_SCALE1),
            EaseCubicActionOut::create(ScaleTo::create(HOP_DURATION, DST_SCALE2)),
            ScaleTo::create(SHRINK2_DURATION, 0.0f),
            DelayTime::create(LAST_DELAY),
            CallFunc::create([this](){
                changeScene();
            }),
            nullptr
        );
        _mask->runAction(exitEffect);
    }
    else
    {
        if (_mask) _mask->setVisible(false);
        _layerColor->setOpacity(0);

        auto exitEffect = Sequence::create(
            FadeIn::create(_duration/2),
            CallFunc::create([this](){
                changeScene();
            }),
            nullptr
        );

        _layerColor->runAction(exitEffect);
    }
}

void TransitionFadeCustom::changeScene()
{
    // enable events while transitions
    // _eventDispatcher->setEnabled(true);
    _outScene->onExit();
    _outScene->cleanup();
    _outScene->setVisible(false);
    _outScene->setPosition(Point(0,0));
    _outScene->setScale(1.0f);
    _outScene->setRotation(0.0f);
    _outScene->setAdditionalTransform(nullptr);
    CC_SAFE_RELEASE_NULL(_outScene);
    
    if (_changeSceneCallback) {
        _changeSceneCallback();
    }
    
    _inScene->setVisible(true);
    _inScene->setPosition(Point(0,0));
    _inScene->setScale(1.0f);
    _inScene->setRotation(0.0f);
    _inScene->setAdditionalTransform(nullptr);
    _inScene->onEnter();
    
    startEnterSceneEffect();
}

void TransitionFadeCustom::startEnterSceneEffect()
{
    if (_enterWithMask)
    {
        _mask->setVisible(true);
        _mask->setScale(0.0f);
        _layerColor->setOpacity(255);

        auto seq = Sequence::create(
            ScaleTo::create(0.0f, 0.0f),
            EaseCubicActionInOut::create(ScaleTo::create(EXPAND_DURATION, SRC_SCALE)),
            DelayTime::create(0.02f),
            CallFunc::create([this]{
                //[self schedule:@selector(setNewScene:) interval:0];
                this->schedule(schedule_selector(TransitionSceneCustom::setNewScene), 0);
            }),
            nullptr
        );
        _mask->runAction(seq);
    }
    else
    {
        if (_mask) _mask->setVisible(false);
        _layerColor->setOpacity(255);

        auto seq = Sequence::create(
            FadeOut::create(_duration/2),
            CallFunc::create([this]{
                //[self schedule:@selector(setNewScene:) interval:0];
                this->schedule(schedule_selector(TransitionSceneCustom::setNewScene), 0);
            }),
           nullptr
           );
        _layerColor->runAction(seq);
    }
}

