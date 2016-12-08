//
//  lyWebView.h
//  ly-client
//  外链类，使用网页打开指定url
//  Created by loveyur on 2016/11/11
//

#ifndef ly_lyWebView_h
#define ly_lyWebView_h

#include "cocos2d.h"


class lyWebView
{
public:
    lyWebView();
	virtual ~lyWebView();

    static void openWebView(const char* url);
};

#endif /* defined(ly_lyWebView_h) */
