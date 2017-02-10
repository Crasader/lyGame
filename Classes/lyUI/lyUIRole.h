/***************************************************************
*	lyUIRole
*	角色类
*	by Shixc 2014-05-05
***************************************************************/
#ifndef __lyGame__lyUIRole__
#define __lyGame__lyUIRole__

#include "lyUIBase.h"
#include "lyAction.h"
#include "lyFrame.h"

#define UIROLE_INDEX 99

class lyUIRole
	:public lyUIBase
{
public:
	lyUIRole();
	~lyUIRole();
	static lyUIRole* Create();
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
    
    void setRoleIdXLS( int nRoleId );
    
    int getRoleId(void);
	void setGroupId(  int Id);
	void setAction(   char byState );
    void updateNextAction();
    
    void initRolebyName(const char* plistname, int startIndex, int indexNum);
    //属性计算
    void setMaxBlood(int max)
    {
        m_nCurrBlood = max;
        m_nMaxBlood = max;
        
    }
    bool isDead();
    int calcHurt(lyUIRole* pUIBase);
    int calcAttack();
    
   
protected:
    lyFrame*            m_pCurrFrame;
    int                 m_nActionGroupId;
    lyAction*           m_pAction;

    int                 m_nCurrState;
    int                 m_nNextState;
private:
	  
	//end*/
    
    
    // 属性相关
    int     m_nRoleId;
    int     m_nCurrBlood;
    int     m_nMaxBlood;

};

#endif //__lyGame__lyUIRole__
