//
//  UISceneID.h
//
//  ly-Game
//
//  Created by loveyur on 2016/12/14
//  Copyright 2016 loveyur. All rights reserved.
//
//

#ifdef DEF_SCENE_TYPE

DEF_SCENE_TYPE_1(SCENE_NONE, kUISceneIDPrefix)
DEF_SCENE_TYPE(SCENE_APP_TOP)
DEF_SCENE_TYPE(SCENE_APP_STARTMENU)
DEF_SCENE_TYPE(SCENE_TEST_SCENE)
DEF_SCENE_TYPE(SCENE_LOGIN)
DEF_SCENE_TYPE(SCENE_LOADING)
DEF_SCENE_TYPE(SCENE_LOADING_TEXT)



DEF_SCENE_TYPE(SCENE_LAST)

#else

#ifndef __lyGame__UISceneID_h
#define __lyGame__UISceneID_h

#define kUISceneIDPrefix       0x00000000
#define DEF_SCENE_TYPE(name)        name,
#define DEF_SCENE_TYPE_1(name, val) name = val,

#include "ISceneInterfaces.h"
enum UISceneType : SceneID {
#include "UISceneID.h"
};

#undef DEF_SCENE_TYPE
#undef DEF_SCENE_TYPE_1

#endif
#endif // __lyGame__UISceneID_h
