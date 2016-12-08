//
//  lyWebInterfaceiOS.h
//  ly-client
//  外链类，使用网页打开指定url
//  Created by loveyur on 2016/11/11
//

#import "lyWebInterfaceiOS.h"

@implementation lyWebInterfaceiOS


- (void)openWebView:(const char*)url
{
    NSString *request = [NSString stringWithUTF8String:url];
    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:request]];
}

@end
