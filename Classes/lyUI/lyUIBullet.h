/***************************************************************
*	lyUIBullet
*	发射器
*	by Shixc 2014-05-05
***************************************************************/
#ifndef __lyGame__lyUIBullet__
#define __lyGame__lyUIBullet__

#include "lyUIBase.h"
#include "lyAction.h"
#include "lyFrame.h"

enum LAUNCHER_BULLET_TYPE
{
    LAUNCHER_BULLET_SPR = 0,
    LAUNCHER_BULLET_ACT,
    
    LAUNCHER_BULLET_MAX
};


class lyUIBullet
	:public lyUIBase
{
public:
	lyUIBullet();
	~lyUIBullet();
	static lyUIBullet* Create();
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
    
    void setBulletId(int nId)
    {
        m_nBulletId = nId;
       
    }
    void setTime(int nMS)
    {
        m_nMillisecond = nMS;
    }
    void InitBulletPath(const char* strPath);
    
    void InitPoint(CCPoint pointStart, CCPoint pointEnd)
    {
        m_pointS = pointStart;
        m_pointE = pointEnd;
        m_diffPoint = (m_pointE-m_pointS)/20;
        CCLOG("======================m_diffPoint %f,%f",m_diffPoint.x,m_diffPoint.y);
    }
    
    Vec2 getPointS()
    {
        return m_pointS;
    }
    Vec2 getPointE()
    {
        return m_pointE;
    }
    Vec2 getDiffPoint()
    {
        return m_diffPoint;
    }
    
private:
    lyFrame*    m_pBulletFrame;
    int         m_nBulletId;    //id
    Vec2        m_pointS;       //起始point
    Vec2        m_pointE;       //终结point
    Vec2        m_diffPoint;
    int         m_nMillisecond; //时间
    float       m_fSpeed;       //移动速度
    
    
};

#endif //__lyGame__lyUIBullet__
