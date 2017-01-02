//
//  lyTouchElement.h
//  act00
//
//  Created by songGT on 15/8/12.
//
//

#ifndef __act00__lyTouchElement__
#define __act00__lyTouchElement__

#include "lyInclude.h"

class lyTouchElement
{
public:
    virtual bool    onTouchBegan(cocos2d::Touch *touches, cocos2d::Event *event) = 0;
    virtual void    onTouchMoved(cocos2d::Touch *touches, cocos2d::Event *event) = 0;
    virtual void    onTouchEnded(cocos2d::Touch *touches, cocos2d::Event *event) = 0;
    virtual void    onTouchCancelled(cocos2d::Touch *touches, cocos2d::Event *event) = 0;
    
    virtual void    cleanTouch();
    virtual void    cleanChildrenTouch(){}
protected:
    lyTouchElement();
	~lyTouchElement();
    
protected:
    bool    m_bIsTouchBegan;
};


#endif /* defined(__act00__lyTouchElement__) */
