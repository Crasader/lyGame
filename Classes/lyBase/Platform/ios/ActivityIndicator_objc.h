
#import <Foundation/Foundation.h>

@interface ActivityIndicator_objc : NSObject
{
	int m_nCount;
}

+ (ActivityIndicator_objc *) getInstance;

- (UIActivityIndicatorView *) getActivitiIndicatorView;
//- (void) setPosition:(float) x:(float) y;
- (void) setPosition:(float) x setPosition:(float) y;
- (void) startAnimating;
- (void) stopAnimating;
- (void) forceStopAnimating;

@end
