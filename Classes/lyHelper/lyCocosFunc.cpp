/***************************************************************
		通用函数定义类
		by Shixc 2017-01-01
***************************************************************/

#include "lyCocosFunc.h"

Touch lyCocosFunc::convertToCurWinCoordinateOnlyGL(cocos2d::Node *pNode, cocos2d::Touch *parTouch)
{
    //备注：此坐标系是先对于窗体自身锚点的坐标系，考虑、消除了窗体自身的缩放，将其转换为初使坐标
    Touch touch;
    if(pNode && parTouch)
    {
        //获得目标坐标系在父亲坐标系的坐标（备注：左下角为坐标点）
        float desCoorOriX = pNode->getPosition().x - pNode->getParent()->getPosition().x;
        float desCoorOriY = pNode->getPosition().y - pNode->getParent()->getPosition().y;
        //转换坐标系
        float selfCoorOriX = (parTouch->getLocation().x-desCoorOriX)/pNode->getScaleX();
        float seflCoorOriY = (parTouch->getLocation().y-desCoorOriY)/pNode->getScaleY();
        touch.setTouchInfo(parTouch->getID(), selfCoorOriX, seflCoorOriY);
    }
    
    return touch;
}

bool lyCocosFunc::isTouchInWin(Node* pNode, Touch* pTouch)
{
    bool bIsIn = false;
    if(pNode && pTouch)
    {
        //坐标系都忽略锚点，以左下为坐标系！！！！
        Point touPoint = pTouch->getLocation();
        Point nodePoint = pNode->getPosition()+pNode->getParent()->getPosition();
        Size nodeSize = pNode->getContentSize();
        CCLOG("Touch x=%f, y=%f",touPoint.x,touPoint.y);
        CCLOG("Node x=%f, y=%f, width=%f, height=%f",nodePoint.x,nodePoint.y,nodeSize.width,nodeSize.height);
        if(touPoint.x > nodePoint.x && touPoint.x < nodePoint.x + nodeSize.width
           && touPoint.y > nodePoint.y  && touPoint.y < nodePoint.y + nodeSize.height
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

