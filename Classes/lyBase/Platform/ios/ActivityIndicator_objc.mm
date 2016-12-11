
#import "ActivityIndicator_objc.h"
#import "CCEAGLView.h"
#include <cocos2d.h>

static UIActivityIndicatorView * m_indicatorView = nil;
static cocos2d::Size m_winSize;

@implementation ActivityIndicator_objc

+ (ActivityIndicator_objc *) getInstance
{
    static ActivityIndicator_objc * _instance = nil;
    @synchronized( self )
    {
        if( _instance == nil )
        {
            _instance = [[ActivityIndicator_objc alloc ] init];
            m_winSize = cocos2d::Director::getInstance()->getWinSize();
        }
    }
    return _instance;
}

- (UIActivityIndicatorView *) getActivitiIndicatorView
{
    @synchronized( self )
    {
        if (m_indicatorView == nil)
        {
            m_indicatorView = [[UIActivityIndicatorView alloc] initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleWhite];
            m_indicatorView.center = CGPointMake(m_winSize.width / 2.0f, m_winSize.height / 2.0f);
            m_indicatorView.hidesWhenStopped = true;
            [m_indicatorView stopAnimating];
            
            cocos2d::GLView *glview = cocos2d::Director::getInstance()->getOpenGLView();
            CCEAGLView *baseView = (CCEAGLView*) glview->getEAGLView();
            
            [baseView addSubview:m_indicatorView];
        }
    }
    return m_indicatorView;
}

- (void) setPosition:(float) x setPosition:(float) y
{
    UIActivityIndicatorView *view = [self getActivitiIndicatorView];
    view.center = CGPointMake(x, y);
}

- (void) startAnimating
{
    UIActivityIndicatorView *view = [self getActivitiIndicatorView];
    [view startAnimating];
}

- (void) stopAnimating
{
    UIActivityIndicatorView *view = [self getActivitiIndicatorView];
    [view stopAnimating];
}

- (void) forceStopAnimating
{
    UIActivityIndicatorView *view = [self getActivitiIndicatorView];
    [view stopAnimating];
	m_nCount = 0;
}

@end
