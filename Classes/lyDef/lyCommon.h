//
//  lyCommon.h
//  ly-client
//	宏定义和常量定义
//  Created by loveyur on 2016/11/10
//

#ifndef ly_lyCommon_h
#define ly_lyCommon_h

#define LYGAME_DEFAULT_WIDTH   640
#define LYGAME_DEFAULT_HEIGHT  960

#define DEFAULT_LOW_WIDTH   320
#define IPHONE5_LOW_WIDTH   320
#define IPAD_LOW_WIDTH      426

#define DEFAULT_LOW_HEIGHT  480
#define IPHONE5_LOW_HEIGHT  568
#define IPAD_LOW_HEIGHT     568

#define POPUP_WINDOW_WIDTH  300

#define SHOW_MENU_DELAY_IN 0.02f
#define SHOW_MENU_DELAY_OUT 0.017f

#define APP_FONT "fonts/ModeMinAStd-B.ttf"

enum quest_age_status {
    AGE_UNREGISTRY   = 0, // 年齢未認証
    AGE_UNDER_18     = 1, // 18歳未満
    AGE_UPPER_18     = 2, // 18歳以上
};

#define NUM_DECK_MEMBER 5
#define RELATION_PRINCE_NUM 4


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#else

#endif



#endif /* ly_lyCommon_h */
