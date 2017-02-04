/***************************************************************
		通用函数定义类
		by Shixc 2017-01-01
***************************************************************/

#include "lyCocosFunc.h"

Touch lyCocosFunc::convertToGL(cocos2d::Node *pNode, cocos2d::Touch *parTouch)
{
    Touch touch;
    if(pNode && parTouch)
    {
        float desCoorOriX = pNode->getPosition().x - pNode->getParent()->getPosition().x;
        float desCoorOriY = pNode->getPosition().y - pNode->getParent()->getPosition().y;
        //转换坐标系
        float selfCoorOriX = parTouch->getLocationInView().x-desCoorOriX;
        float seflCoorOriY = parTouch->getLocationInView().y-desCoorOriY;
        touch.setTouchInfo(parTouch->getID(), selfCoorOriX, seflCoorOriY);
    }
    
    return touch;
}

bool lyCocosFunc::isTouchInWin(Node* pNode, Touch* pTouch)
{
    bool bIsIn = false;
    if(pNode && pTouch)
    {
        //CCLOG("-------------------------------------");
        Point pointAnchor = pNode->getAnchorPoint();
        //CCLOG("pointAnchor x=%f, y=%f",pointAnchor.x,pointAnchor.y);
        Point touPoint = pNode->convertTouchToNodeSpace(pTouch);
        Size nodeSize = pNode->getContentSize();
        //CCLOG("touPoint x=%f, y=%f x=%f, y=%f",touPoint.x,touPoint.y, pTouch->getLocationInView().x,pTouch->getLocationInView().y);
        //CCLOG("touPoint x %f>-%f && %f<%f",touPoint.x ,nodeSize.width*pointAnchor.x,touPoint.x ,nodeSize.width-(nodeSize.width*pointAnchor.x) );
        //CCLOG("touPoint y %f>-%f && %f<%f",touPoint.y ,nodeSize.height*pointAnchor.y,touPoint.y ,nodeSize.height-(nodeSize.height*pointAnchor.y) );
        //CCLOG("-------------------------------------");
        if( touPoint.x > 0 && touPoint.x < nodeSize.width
           && touPoint.y > 0  && touPoint.y < nodeSize.height
           )
        {
            bIsIn = true;
        }
    }
    return bIsIn;
}

bool lyCocosFunc::isTouchInUnitWin(Rect& collRect, Touch* pTouch)
{
    bool bIsIn = false;
    if(pTouch)
    {
        Point touPoint = pTouch->getLocationInView();
        if(touPoint.x>collRect.origin.x
           && touPoint.x<collRect.size.width
           && touPoint.y>collRect.origin.y
           && touPoint.y<collRect.size.height)
        {
            bIsIn = true;
        }
    }
    return bIsIn;
}

bool lyCocosFunc::isRectCollision(Rect rect1, Rect rect2)
{
    float CLeft = max(rect1.origin.x, rect2.origin.x);
    float CRight = min(rect1.origin.x+rect1.size.width, rect2.origin.x+rect2.size.width);
    float CBottom = max(rect1.origin.y, rect2.origin.y);
    float CTop = min(rect1.origin.y+rect1.size.height, rect2.origin.y+rect2.size.height);
    //find the collision
    if (CLeft < CRight && CBottom < CTop)
    {
        return true;
    }
    return false;
}

bool lyCocosFunc::createPopupViewScriptFile(string scriptFile, string winName)
{
    
    return true;
}

