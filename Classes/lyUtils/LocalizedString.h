//
//  CCLocalizedString.h
//
//  ly-Game
//
//  Created by loveyur on 2016/12/14
//  Copyright 2016 loveyur. All rights reserved.
//
//

#ifndef _LocalizedString_h
#define _LocalizedString_h

/*get the localized string by the key, if can't get the value then return mComment
 */
const char * LocalizedString(const char * mKey,const char * mComment);

#define CCLS(key) LocalizedString(key, nullptr)

#endif
