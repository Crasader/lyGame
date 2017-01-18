/***************************************************************
*	lyUIBase
*	by Shixc 2014-04-10
***************************************************************/
#ifndef __lyGame__lyUIBase__
#define __lyGame__lyUIBase__



#include "lyInclude.h"
#include "lyCocosNode.h"


USING_NS_CC;

#define CTRL_NAME_SIZE 16

#define TEST_COLLISION
#ifdef TEST_COLLISION
extern bool gShowTestCollition;
#endif

class lyUIBase :
public lyCocosNode
{
public:
	lyUIBase();
	virtual ~lyUIBase();

	static lyUIBase* Create();
    //CREATE_FUNC_POOL(lyUIBase);
    bool init();

    virtual void onEnter() override;
    virtual void onExit() override;
    virtual void update(float delta) override;
    virtual void visit(Renderer *renderer, const Mat4 &parentTransform, uint32_t parentFlags) override;
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
    
    virtual bool onTouchBegan(cocos2d::Touch *touches, cocos2d::Event *event);
    virtual void onTouchMoved(cocos2d::Touch *touches, cocos2d::Event *event);
    virtual void onTouchEnded(cocos2d::Touch *touches, cocos2d::Event *event);
    virtual void onTouchCancelled(cocos2d::Touch *touches, cocos2d::Event *event);
    
    void setTouchEnabled(bool bTouch);
    
	void SetCtrlName(const char* strCtrlName);
	long GetObjID();
    
    void setBulletId(int nId)
    {
        m_nBulletId = nId;
    }
    
    Touch convertToCurWinCoordinateOnlyGL(Node* desWin, Touch* parTouch);    //将坐标系从父坐标系，转换为自身的坐标系(备注：只通过openGL坐标系，不使用屏幕坐标系)
    bool isTouched(Node* desWin, Touch* pTouch);
    bool checkCollision(lyUIBase* temp);
    //判断是否在屏幕外
    bool isOutScreen();
protected:
    Vec2    m_TouchBeginPoint;
	bool    m_bIsCtrlVisible;
	bool    m_bIsTouched;
    bool    m_bTouchEnabled;
    EventListenerTouchOneByOne* m_touchListener;
	bool    m_bCtrlEnable;
	bool    m_bAdjustCtrlSpr;
	char	m_szCtrlName[CTRL_NAME_SIZE];
    
    int     m_nBulletId;    //0 非发射器，>0 发射器及其id


};


#endif //__lyGame__lyUIBase__
