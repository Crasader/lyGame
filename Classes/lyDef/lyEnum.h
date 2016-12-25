#ifndef _XENUM_H_
#define _XENUM_H_


/***************************************************************
*	Enum
*	by Shixc 2014-04-10
***************************************************************/

#define SZ_MAX_NUM 256

#define SZ_MAX_ACT_GROUP 256

enum{
	enProBarBaseType_Left = 0,		//����Ǹ�
	enProBarBaseType_Right,			//�ұ��Ǹ�
	enProBarBaseType_Up,			//�ϱ��Ǹ�
	enProBarBaseType_Down,			//�±��Ǹ�

	enProBarBaseType_Max
};
//����������ʾ�ı�����
enum{
	enBarTextType_None = 0,
	enBarTextType_Curr,
	enBarTextType_CurrPer,
	enBarTextType_CurrMax,


	enBarTextType_Max,
};
enum{
	enBarChgType_None = 0,		//ֱ������ֵ��ָ����
	enBarChgType_Add,			//��0���ӵ�ָ����
	enBarChgType_Reduce,		//�������ٵ�ָ����

	enBarChgType_Max
};

//����ƶ�����
enum
{
	enPanelMoveType_None,				//���ƶ�
	enPanelMoveType_ToDest,				//�ƶ���Ŀ�ĵ�
	enPanelMoveType_ToBack,				//����
	enPanelMoveType_FollowMouse,		//�������

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

//action state ������״̬
enum
{
	enActState_Wait = 0,	//����״̬
	enActState_Run,			//����״̬
	enActState_Fly,			//��״̬
	enActState_GC1,			//GC1��ʽ
	enActState_GC2,			//GC2��ʽ
	enActState_GC3,			//GC3��ʽ
	enActState_GC4,			//GC4��ʽ
	enActState_Skill1,		//������ʽ


	enActState_Max
};

#endif  //_XENUM_H_
