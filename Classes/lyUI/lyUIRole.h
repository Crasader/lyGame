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
    virtual void onEnter() override;
    virtual void onExit() override;
    virtual void update(float delta) override;
    virtual void visit(Renderer *renderer, const Mat4 &parentTransform, uint32_t parentFlags) override;
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
    
    virtual bool onTouchBegan(cocos2d::Touch *touches, cocos2d::Event *event);
    virtual void onTouchMoved(cocos2d::Touch *touches, cocos2d::Event *event);
    virtual void onTouchEnded(cocos2d::Touch *touches, cocos2d::Event *event);
    virtual void onTouchCancelled(cocos2d::Touch *touches, cocos2d::Event *event);
    
	void setRoleId(unsigned int nRoleId);
	unsigned int getRoleId(void);
	void setGroupId(unsigned int Id);
	void setAction( unsigned char byState );
    void updateNextAction();
    
    void Clear();

private:
	unsigned int        m_nRoleId;
	unsigned int        m_nActionGroupId;
	lyAction*           m_pAction;
	lyFrame*            m_pCurrFrame;

    int                 m_nCurrState;
    int                 m_nNextState;
	//end*/

};

#endif //__lyGame__lyUIRole__
