//
//  lyWebView.cpp
//  ly-client
//
//  Created by loveyur on 2016/11/10
//


#include "base/CCPlatformMacros.h"s

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "cocos2d.h"
#include "lyWebView.h"
#include <jni.h>
#include "platform/android/jni/JniHelper.h"

#define  CLASS_NAME "com/ly/android/lyWebInterface"

lyWebView::lyWebView()
{
	// TODO: auto generated code
}

lyWebView::~lyWebView()
{
	// TODO: auto generated code
}

void lyWebView::openWebView(const char* url)
{
    cocos2d::JniMethodInfo methodInfo;
    if (! cocos2d::JniHelper::getStaticMethodInfo(methodInfo,CLASS_NAME, "openWebView", "(Ljava/lang/String;)V"))
    {
        CCLOG("java没有接口openWebView");
        return;
    }
    jstring stringMsg = methodInfo.env->NewStringUTF(url);
    methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, stringMsg);
    methodInfo.env->DeleteLocalRef(stringMsg);
    methodInfo.env->DeleteLocalRef(methodInfo.classID);
}


#endif
