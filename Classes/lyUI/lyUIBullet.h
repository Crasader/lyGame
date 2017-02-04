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
    void setButtlePath(std::string strPath, char byMaxId = 0);
    
    void InitPoint(CCPoint pointStart, CCPoint pointEnd)
    {
        m_pointS = pointStart;
        m_pointE = pointEnd;
        m_diffPoint = (m_pointE-m_pointS)/20;
        //CCLOG("======================m_diffPoint %f,%f",m_diffPoint.x,m_diffPoint.y);
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
    //移动结束后，播放消失特效，播放完毕后释放本资源，如果没有消失特效，直接释放
    void setMissEffectId(int missId);
    void setMissSoundId(int missId);
    void playMissAction();
    void playMissEffect(const MAP_ONE_LINE* missData);
    
    void Clear();
    
private:
    lyAction*   m_pButtleAction;
    lyFrame*    m_pButtleFrame;
    int         m_nBulletId;    //id
    Vec2        m_pointS;       //起始point
    Vec2        m_pointE;       //终结point
    Vec2        m_diffPoint;
    int         m_nMillisecond; //时间
    float       m_fSpeed;       //移动速度
    
    //消失相关属性
    unsigned char		m_byMissInterval;
    bool        m_bPlayMiss;
    int         m_nMissEffectId; 
    lyAction*   m_pMissAction;
    lyFrame*    m_pMissFrame;
    
    
};

#endif //__lyGame__lyUIBullet__
