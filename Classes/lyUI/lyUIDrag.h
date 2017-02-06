/***************************************************************
*	lyUIDrag
*   拖拽控件
*	by Shixc 2017-01-01
***************************************************************/
#ifndef __lyGame__lyUIDrag__
#define __lyGame__lyUIDrag__



#include "lyInclude.h"
#include "lyUIBase.h"
#include "lyUIBullet.h"
#include "lyFrame.h"
USING_NS_CC;

#define CTRL_NAME_SIZE 16

#define TEST_COLLISION
#ifdef TEST_COLLISION
extern bool gShowTestCollition;
#endif

class lyUIDrag :
public lyUIBase
{
public:
	lyUIDrag();
	virtual ~lyUIDrag();

	static lyUIDrag* Create();
    bool init();
    void Clear();
    
    virtual void onEnter() override;
    virtual void onExit() override;
    virtual void update(float delta) override;
    virtual void visit(Renderer *renderer, const Mat4 &parentTransform, uint32_t parentFlags) override;
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
    
    virtual bool onTouchBegan(cocos2d::Touch *touches, cocos2d::Event *event);
    virtual void onTouchMoved(cocos2d::Touch *touches, cocos2d::Event *event);
    virtual void onTouchEnded(cocos2d::Touch *touches, cocos2d::Event *event);
    virtual void onTouchCancelled(cocos2d::Touch *touches, cocos2d::Event *event);
    

    void setSpritePath(const char* strPath, int byMaxId = 0);
    void setSpriteName(const char* strName, int byMaxId = 0);
    
    void setDragSpan(int minX, int maxX,int minY, int maxY);

    
    //属性计算
    void setMaxBlood(int max)
    {
        m_nCurrBlood = max;
        m_nMaxBlood = max;
    }
    bool isDead();
    int calcHurt(lyUIBullet* pBullet);
    int calcAttack();
    void setRoleId(int nid);
private:
    lyAction*   m_pPlaneAction;
    lyFrame*    m_pPlaneFrame;
    bool    m_bHadSpan;
    int     m_nMinX;
    int     m_nMinY;
    int     m_nMaxX;
    int     m_nMaxY;
    
    // 属性相关
    int     m_nRoleId;
    int     m_nCurrBlood;
    int     m_nMaxBlood;
};


#endif //__lyGame__lyUIDrag__
