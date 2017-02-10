#ifndef _GESTURE_RECOGNIZER_H_
#define _GESTURE_RECOGNIZER_H_

#include "cocos2d.h"
//#include "../logic/PlayerManager.h"

const int MinStepX = 5;
const int MinStepY = 5;
const int MinGestureStepTime = 200;
const int MinGestureOnceTime = 800;
const int MinGestureLength = 100;
const int MinTipClickTime = 250;
const long MinLongPressTime = 100;

const int GESTURE_TYPE_NONE = 0;
const int GESTURE_TYPE_UP = 1;
const int GESTURE_TYPE_RIGHT_UP = 2;
const int GESTURE_TYPE_RIGHT = 3;
const int GESTURE_TYPE_RIGHT_DOWN = 4;
const int GESTURE_TYPE_DOWN = 5;
const int GESTURE_TYPE_LEFT_DOWN = 6;
const int GESTURE_TYPE_LEFT = 7;
const int GESTURE_TYPE_LEFT_UP = 8;
const int GESTURE_TYPE_TIP_CLICK = 9;
const int GESTURE_TYPE_CURVE_UP = 10;
const int GESTURE_TYPE_CURVE_RIGHT = 11;
const int GESTURE_TYPE_CURVE_DOWN = 12;
const int GESTURE_TYPE_CURVE_LEFT = 13;
const int GESTURE_TYPE_TRIANGLE = 14;
const int GESTURE_TYPE_CIRCLE = 15;
const int GESTURE_TYPE_DOUBLE_CLICK = 16;
const int GESTURE_TYPE_MOVE = 17;
const int GESTURE_TYPE_MOVE_END = 18;
const int GESTURE_TYPE_TWO_NONE = 19;
const int GESTURE_TYPE_TWO_UP = 20;
const int GESTURE_TYPE_TWO_RIGHT_UP = 21;
const int GESTURE_TYPE_TWO_RIGHT = 22;
const int GESTURE_TYPE_TWO_RIGHT_DOWN = 23;
const int GESTURE_TYPE_TWO_DOWN = 24;
const int GESTURE_TYPE_TWO_LEFT_DOWN = 25;
const int GESTURE_TYPE_TWO_LEFT = 26;
const int GESTURE_TYPE_TWO_LEFT_UP = 27;
const int GESTURE_TYPE_TWO_TIP_CLICK = 28;
const int GESTURE_TYPE_TWO_CURVE_UP = 29;
const int GESTURE_TYPE_TWO_CURVE_RIGHT = 30;
const int GESTURE_TYPE_TWO_CURVE_DOWN = 31;
const int GESTURE_TYPE_TWO_CURVE_LEFT = 32;
////const int GESTURE_TYPE_TWO_TRIANGLE = 33;
const int GESTURE_TYPE_TWO_CIRCLE = 34;
const int GESTURE_TYPE_TWO_DOUBLE_CLICK = 35;
const int GESTURE_TYPE_DOUBLE_MOVE = 36;
const int GESTURE_TYPE_TWO_TAP_DOWN = 37;
const int GESTURE_TYPE_TWO_TAP_UP = 38;
const int GESTURE_TYPE_TWO_TAP_GIVEUP = 39;

using namespace cocos2d;

class GesturePoint
{
public:
	GesturePoint():m_touchTime(0),sumlength(0),toteltime(0){}
	cocos2d::CCPoint m_gPos;
	long m_touchTime;
	float sumlength;
	long toteltime;
};

class RecognizerResult : public cocos2d::CCObject
{
public:
	RecognizerResult():recognizerResult(0){}
    //bool init() {return true;}
	
	int recognizerResult;
	cocos2d::CCPoint point;

};

class GestureRecognizer : public cocos2d::CCLayer
{
public:
	GestureRecognizer();
    virtual bool init();
    virtual void onTouchesBegan(const std::vector<Touch*>& touches, cocos2d::Event *unused_event);
    
    virtual void ccTouchesMoved(const std::vector<Touch*>& touches, cocos2d::Event *unused_event);
    virtual void ccTouchesEnded(const std::vector<Touch*>& touches, cocos2d::Event *unused_event);
	
	void keypressDown(int key);


    void setTarget(cocos2d::CCObject * tar, cocos2d::SEL_CallFuncO sel);
    void gestureRecognized(cocos2d::CCObject * gesture);

	int TouchesEndRecognizer(int idx);
	void LongPressRecognizer(float dt);
    cocos2d::CCRect frame;
    bool isRecognizing;
	std::map<int, std::vector<GesturePoint> > m_GestureList;
	bool isTouched;
	unsigned long longPressStartTime;
    unsigned long tlongPressStartTime;
    bool bTwTouchNow;
    
	int doubleClickType;
	long doubleClickLastTime;
	int fingerNum;
	int touchedNum;
	std::map<int,int> m_resultlist;
	int isMoving;
	cocos2d::CCPoint m_DestPos;

	std::vector<cocos2d::CCLabelTTF*> m_Labellist;
	cocos2d::CCLabelTTF* m_Label;

	std::map<int,std::string> m_RecognizerName;

	cocos2d::SEL_CallFuncO selector;
    cocos2d::CCObject * target;

	RecognizerResult m_result;
    CREATE_FUNC(GestureRecognizer);
    cocos2d::CCRect mPlayBounds;
    int touchCrossedCount;
};


#endif
