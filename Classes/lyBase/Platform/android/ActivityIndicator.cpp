
#include "ActivityIndicator.h"
#include "JavaClassNameKey.h"
#include "cocos2d.h"
#include "platform/android/jni/JniHelper.h"
#include <jni.h>

USING_NS_CC;

//インジケータースタート
void ActivityIndicator::startAnimating()
{
    JniMethodInfo m;
    if (JniHelper::getStaticMethodInfo(m, CLASS_NAME_PROGRESS, "startAnimating", "()V"))
    {
            m.env->CallStaticVoidMethod(m.classID, m.methodID);
            m.env->DeleteLocalRef(m.classID);
    }
#ifdef DEBUG
    CCLOG("ActivityIndicator::startAnimating() end");
#endif
}

//インジケーターストップ
void ActivityIndicator::stopAnimating()
{
    JniMethodInfo m;
    if (JniHelper::getStaticMethodInfo(m, CLASS_NAME_PROGRESS, "stopAnimating", "()V"))
    {
            m.env->CallStaticVoidMethod(m.classID, m.methodID);
            m.env->DeleteLocalRef(m.classID);
    }
#ifdef DEBUG
    CCLOG("ActivityIndicator::stopAnimating() end");
#endif
}

//中心位置の指定
void ActivityIndicator::setPosition(float x, float y)
{
//    ActivityIndicator_objc *instance = ActivityIndicator_objc::getInstance();
//    instance->setPosition(x, y);
}
