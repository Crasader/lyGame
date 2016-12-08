//
//  lyWebView.cpp
//  ly-client
//  外链类，使用网页打开指定url
//  Created by loveyur on 2016/11/11
//


#import "lyWebView.h"
#import "lyWebInterfaceiOS.h"


lyWebInterfaceiOS* g_lyWebInterfaceiOS = nullptr;

lyWebView::lyWebView()
{
    // TODO: auto generated code
}

lyWebView::~lyWebView()
{
    if(g_lyWebInterfaceiOS)
    {
        [g_lyWebInterfaceiOS release];
        g_lyWebInterfaceiOS = NULL;
    }
}

void lyWebView::openWebView(const char* url)
{
    if(!g_lyWebInterfaceiOS)
    {
        g_lyWebInterfaceiOS = [[lyWebInterfaceiOS alloc] init];
    }
    
    [g_lyWebInterfaceiOS openWebView:url];
}
