/***************************************************************
*	lyUIBullet
*	发射器
*	by Shixc 2014-05-05
***************************************************************/
#ifndef __lyGame__lyUIBullet__
#define __lyGame__lyUIBullet__

#include "lyUIRole.h"
#include "lyAction.h"
#include "lyFrame.h"

enum LAUNCHER_BULLET_TYPE
{
    LAUNCHER_BULLET_SPR = 0,
    LAUNCHER_BULLET_ACT,
    
    LAUNCHER_BULLET_MAX
};


class lyUIBullet
	:public lyUIRole
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
    
    //void setBulletId(int nId);
    void setTime(int nMS)
    {
        m_nMillisecond = nMS;
    }

    Vec2 getPointS()
    {
        return m_pointS;
    }
    Vec2 getPointE()
    {
        return m_pointE;
    }
    Vec2 getMoveVector()
    {
        return m_MoveVector;
    }
    //移动结束后，播放消失特效，播放完毕后释放本资源，如果没有消失特效，直接释放
    void setMissEffectId(int missId);
    void setMissSoundId(int missId);
    void playMissAction();
    void playMissEffect(const MAP_ONE_LINE* missData);
    
    void Clear();
    void setRoute();
    
  
    
private:
    //相关属性
    unsigned char		m_byMissInterval;
    bool        m_bPlayMiss;
    int         m_nMissEffectId; 
    lyAction*   m_pMissAction;
    lyFrame*    m_pMissFrame;
    
    //ui界面相关
    Vec2        m_pointS;       //起始point
    Vec2        m_pointE;       //终结point
    Vec2        m_MoveVector;
    int         m_nMillisecond; //时间
    float       m_fSpeed;       //移动速度
    
    
    //攻击 伤害相关
    
    
    
};

#endif //__lyGame__lyUIBullet__
