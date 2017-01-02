/***************************************************************
		通用函数定义类
		by Shixc 2014-04-10
***************************************************************/
#ifndef __lyGame__lyCocosFunc__
#define __lyGame__lyCocosFunc__

#include "lyInclude.h"


/////////////////////////////////////////////////////////////////
class lyCocosFunc
{
public:
    static Touch convertToGL(Node* pNode, Touch* parTouch);    //将坐标系从父坐标系，转换为自身的坐标系(备注：只通过openGL坐标系，不使用屏幕坐标系)
    static bool isTouchInWin(Node* pNode, Touch* pTouch);          //判断窗口控件是否被点中
    static bool isTouchInUnitWin(Rect& collRect, Touch* pTouch);    //判断单位是否被点中
    static bool isRectCollision(Rect rect1, Rect rect2);            //判断两个矩形是否重叠
    static bool createPopupViewScriptFile(string scriptFile, string winName);
};


#endif  //__lyGame__lyCocosFunc__
