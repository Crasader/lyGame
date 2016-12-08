//
//  VitaminID.h
//  VitaminProject
//
//  Created by Shinji Hiramatsu on 2014/05/24.
//  Copyright 2014 GCREST,Inc. All rights reserved.
//

#ifndef __VitaminProject__VitaminID_h
#define __VitaminProject__VitaminID_h

#include "ApplicationID.h"


#define kQuestPrefix       0x00010000
#define kCmdFeatureSpace    100

// Quest EventID
enum {
    QuestEvent_Init = kQuestPrefix+1,
    QuestEvent_Start,
    QuestEvent_Clear,
    QuestEvent_Pause,
    QuestEvent_Resume,
    QuestEvent_ChangeScene,
    QuestEvent_Terminate,
    
    QuestEvent_StartTurn,
    QuestEvent_TurnTimeUp,
    QuestEvent_StartAttack,
    QuestEvent_ChangeTime,
    QuestEvent_ChangePlayerHP,
    QuestEvent_CharaHP,
    
    QuestEvent_Last
};

// Vitamin Application CommandID
enum {
    Cmd_StartScene = Cmd_Last+1,
    Cmd_SceneAppTop,
    Cmd_SceneTopPage,
    Cmd_ScenePrinceTop,
    Cmd_SceneGachaTop,
    Cmd_SceneQuestTop,
    Cmd_SceneQuestBattle,
    Cmd_SceneShop,
    Cmd_SceneFriend,
    Cmd_SceneOthersMenu,
    
    Cmd_SceneLoginBonus,
    
    // クエスト画面
    Cmd_SceneQuestContriesDetail,
    Cmd_SceneQuestList,
    Cmd_SceneSelectSupportPrince,
    Cmd_SceneShowCharaDetail,
    Cmd_SceneCharaStoryList,
    Cmd_SceneSelectBattleMember,
    Cmd_SceneQuestResultPlayerInfo,
    Cmd_ScesneLevelUp,
    Cmd_SceneTiesStory,
    Cmd_SceneQuestResultItems,
    Cmd_SceneGotCharacter,
    Cmd_SceneGotCharacterDetail,
    
    Cmd_SceneHoldParty,
    Cmd_ResultParty,
    
    // 新規登録画面
    Cmd_SceneUsePolicy,
    Cmd_SceneJogaMessage,
    Cmd_SceneAttentionSound,
    Cmd_SceneOpeningMovie,
    Cmd_SceneAccountTransfer,
    Cmd_SceneDownloadData,
    
    Cmd_VitaminFeatureBase,
    
    Cmd_PuzzleQuestStart = Cmd_VitaminFeatureBase + kCmdFeatureSpace,
    Cmd_PrinceStart = Cmd_PuzzleQuestStart + kCmdFeatureSpace,
    
    Cmd_Vitamin_Last
};


#endif
