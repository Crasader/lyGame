//
//  CCLocalizedString.h
//  SkeletonX
//
//  Created by 小苏 on 11-12-1.
//  Copyright (c) 2011年 GeekStudio. All rights reserved.
//

#ifndef _LocalizedString_h
#define _LocalizedString_h

/*get the localized string by the key, if can't get the value then return mComment
 */
const char * LocalizedString(const char * mKey,const char * mComment);

#define CCLS(key) LocalizedString(key, nullptr)

#endif
