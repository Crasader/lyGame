#ifndef _XENUM_H_
#define _XENUM_H_


/***************************************************************
*	Enum
*	by Shixc 2014-04-10
***************************************************************/

#define SZ_MAX_NUM 256

#define SZ_MAX_ACT_GROUP 256

enum{
	enProBarBaseType_Left = 0,		//左边是根
	enProBarBaseType_Right,			//右边是根
	enProBarBaseType_Up,			//上边是根
	enProBarBaseType_Down,			//下边是根

	enProBarBaseType_Max
};
//进度条的显示文本类型
enum{
	enBarTextType_None = 0,
	enBarTextType_Curr,
	enBarTextType_CurrPer,
	enBarTextType_CurrMax,


	enBarTextType_Max,
};
enum{
	enBarChgType_None = 0,		//直接设置值到指定处
	enBarChgType_Add,			//从0增加到指定处
	enBarChgType_Reduce,		//从满减少到指定处

	enBarChgType_Max
};

//面板移动类型
enum
{
	enPanelMoveType_None,				//不移动
	enPanelMoveType_ToDest,				//移动到目的地
	enPanelMoveType_ToBack,				//返回
	enPanelMoveType_FollowMouse,		//跟随鼠标

	enPanelMoveType_Max
};


enum{
	enListType_Vertical,
	enListType_Horizontal,

	enListType_Max
};

enum
{
	enUILayer_0,
	enUILayer_1,
	enUILayer_2,
	enUILayer_3,
	enUILayer_4,
	enUILayer_5,


	enUILayer_N,
};

//action state 动作的状态
enum
{
	enActState_Wait = 0,	//待机状态
	enActState_Run,			//奔跑状态
	enActState_Fly,			//飞状态
	enActState_GC1,			//GC1招式
	enActState_GC2,			//GC2招式
	enActState_GC3,			//GC3招式
	enActState_GC4,			//GC4招式
	enActState_Skill1,		//技能招式


	enActState_Max
};

#endif  //_XENUM_H_
