//
//  ApplicationID.h
//
//  ly-Game
//
//  Created by loveyur on 2016/12/14
//  Copyright 2016 loveyur. All rights reserved.
//
//

#ifndef __CoreAppFramework__ApplicationID_h
#define __CoreAppFramework__ApplicationID_h

#define kDefaultPrefix     0x00000000
#define kScenePrefix       0x00000100
#define kGameObjectPrefix  0x00000200

// Default EventID
enum {
    Event_Init = kDefaultPrefix+1,
    Event_Start,
    Event_Clear,
    Event_Pause,
    Event_Resume,
    Event_ChangeScene,
    Event_Terminate,
    Event_Last
};

// Scene EventID
enum {
    SceneEvent_Init = kScenePrefix+1,
    SceneEvent_Start,
    SceneEvent_End,
    SceneEvent_Enter,
    SceneEvent_EnterTransitionDidFinish,
    SceneEvent_Exit,
    SceneEvent_ExitTransitionDidStart,
    
    SceneEvent_ShowPopup,
    SceneEvent_HidePopup,
    SceneEvent_ShowCutIn,
    SceneEvent_HideCutIn,
    SceneEvent_ShowGlobalMenu,
    SceneEvent_HideGlobalMenu,
    SceneEvent_ShowStatusBar,
    SceneEvent_HideStatusBar,

    SceneEvent_Last
};

// GameObject EventID
enum {
    GameObjectEvent_Init = kGameObjectPrefix+1,
    
    GameObjectEvent_Show,
    GameObjectEvent_Hide,
    
    GameObjectEvent_Start,
    GameObjectEvent_End,
    GameObjectEvent_Pause,
    GameObjectEvent_Resume,
    
    GameObjectEvent_CreateSprite,
    GameObjectEvent_CreateSpine,
    GameObjectEvent_CreateCocoStudioAnimation,
    GameObjectEvent_CreateSpriteSheetAnimation,
    GameObjectEvent_CreateParticle,
    GameObjectEvent_CreateSuperAnimationConverterAnimation,
    GameObjectEvent_CreateLWFAnimation,
    
    GameObjectEvent_StartAnimation,
    GameObjectEvent_PauseAnimation,
    GameObjectEvent_EndAnimation,
    
    GameObjectEvent_TouchBegan,
    GameObjectEvent_TouchMoved,
    GameObjectEvent_TouchEnded,
   
    GameObjectEvent_ChangePosition,
    GameObjectEvent_ChangeScale,
    GameObjectEvent_ChangeRotation,
    
    GameObjectEvent_Last
};

// GameObject CommandID
enum {
    Cmd_Create = kGameObjectPrefix+1,
    Cmd_SetPos,
    Cmd_SetScale,
    Cmd_PlayAnimation,
    Cmd_StopAnimation,
    Cmd_Pause,
    Cmd_Resume,
    
    Cmd_Last
};


#endif
