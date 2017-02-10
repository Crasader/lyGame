
#include "GestureRecognizer.h"
//#include "../core/BaseFunction.h"
#include "lyFunc.h"
USING_NS_CC;


GestureRecognizer::GestureRecognizer()
	:isRecognizing(false)
	,isTouched(false)
	,longPressStartTime(0)
	,doubleClickType(0)
	,doubleClickLastTime(0)
	,fingerNum(0)
	,touchedNum(0)
	,isMoving(0)
	,target(NULL)
	,selector(NULL)
    ,bTwTouchNow(false)
{

}

CCLabelTTF* pLabel2;

bool GestureRecognizer::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
	this->setTouchEnabled(true);

	m_RecognizerName[GESTURE_TYPE_NONE] = "NONE";
	m_RecognizerName[GESTURE_TYPE_UP] = "UP";
	m_RecognizerName[GESTURE_TYPE_RIGHT_UP] = "RIGHT_UP";
	m_RecognizerName[GESTURE_TYPE_RIGHT] = "RIGHT";
	m_RecognizerName[GESTURE_TYPE_RIGHT_DOWN] = "RIGHT_DOWN";
	m_RecognizerName[GESTURE_TYPE_DOWN] = "DOWN";
	m_RecognizerName[GESTURE_TYPE_LEFT_DOWN] = "LEFT_DOWN";
	m_RecognizerName[GESTURE_TYPE_LEFT] = "LEFT";
	m_RecognizerName[GESTURE_TYPE_LEFT_UP] = "LEFT_UP";
	m_RecognizerName[GESTURE_TYPE_TIP_CLICK] = "CLICK";
	m_RecognizerName[GESTURE_TYPE_CURVE_UP] = "CURVE_UP";
	m_RecognizerName[GESTURE_TYPE_CURVE_RIGHT] = "CURVE_RIGHT";
	m_RecognizerName[GESTURE_TYPE_CURVE_DOWN] = "CURVE_DOWN";
	m_RecognizerName[GESTURE_TYPE_CURVE_LEFT] = "CURVE_LEFT";
	m_RecognizerName[GESTURE_TYPE_TRIANGLE] = "TRIANGLE";
	m_RecognizerName[GESTURE_TYPE_CIRCLE] = "CIRCLE";
	m_RecognizerName[GESTURE_TYPE_DOUBLE_CLICK] = "DOUBLE CLICK";
	

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

//    CCLabelTTF* pLabel1 = CCLabelTTF::create("finger one", "Arial", 24);
//    pLabel2 = CCLabelTTF::create("finger two", "Arial", 24);
//    CCLabelTTF* pLabel = CCLabelTTF::create("Ready GO", "Arial", 24);

//    pLabel1->setPosition(ccp(origin.x + visibleSize.width/2,
//                            origin.y + visibleSize.height - pLabel1->getContentSize().height));
//    pLabel2->setPosition(ccp(origin.x + visibleSize.width/2,
//                            origin.y + visibleSize.height - pLabel1->getContentSize().height - pLabel2->getContentSize().height));
//    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
//                            origin.y + visibleSize.height - pLabel1->getContentSize().height - pLabel2->getContentSize().height - pLabel->getContentSize().height));
    //m_Labellist.push_back(pLabel1);
//    m_Labellist.push_back(pLabel2);
//    m_Label = pLabel;
//    this->addChild(pLabel1, 1);
//	  this->addChild(pLabel2, 1);
//    this->addChild(pLabel, 1);

	return true;
}
void GestureRecognizer::setTarget(cocos2d::CCObject * tar, cocos2d::SEL_CallFuncO sel)
{
    target = tar;
    selector = sel;
}
void GestureRecognizer::gestureRecognized(cocos2d::CCObject * gesture)
{
    if (target && selector) (target->*selector)(gesture); //call selector
}

void GestureRecognizer::onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event)
{
    if (true) {
        
    }
    tlongPressStartTime = GetMillisecondNow();
	unsigned long curTime = GetMillisecondNow();
	if(isTouched == false)
	{
		isTouched = true;
		touchedNum = 0;
		fingerNum = 0;
		longPressStartTime = curTime;
	}
    for(auto&& touch : touches)
    {
        int num = touch->getID();
        GesturePoint pos;
        pos.m_gPos = touch->getLocation();
        pos.m_touchTime = curTime;
        std::vector<GesturePoint> poslist;
        poslist.push_back(pos);
        m_GestureList[num] = poslist;
    }
	touchedNum++;
	int num = m_GestureList.size();
	if( isTouched == true && fingerNum < num )
	{
		fingerNum = num;

		char cc[1024];
		sprintf(cc, "touch num %d", num);
//		pLabel2->setString(cc);
	}
	if(fingerNum == 1 || fingerNum == 2)
	{
		this->schedule(schedule_selector(GestureRecognizer::LongPressRecognizer),0.1f);
	}
}
void GestureRecognizer::LongPressRecognizer(float dt)
{
	if( isTouched == true )
	{
		unsigned long curTime = GetMillisecondNow();
		if(curTime - longPressStartTime < MinLongPressTime)
		{
			return;
		}
		longPressStartTime = curTime;
		for( int i = 0; i < m_GestureList.size(); i++ )
		{
			int num = m_GestureList[i].size();
			int del = 0;
			std::vector<GesturePoint>::iterator its = m_GestureList[i].begin();
			for( ; its != m_GestureList[i].end(); )
			{
				if( curTime - its->m_touchTime > MinGestureOnceTime )
				{
					del++;
					if( num > del )
					{
						its = m_GestureList[i].erase(its);
					}
					else
					{
						its->m_touchTime = curTime;
						break;
					}
				}
				else
				{
					break;
				}
			}
		}
		if( fingerNum == 1 )
		{
			int type = TouchesEndRecognizer(0);
			if( 1/*type == GESTURE_TYPE_TIP_CLICK || type == GESTURE_TYPE_NONE*/ )
			{
				//m_Label->setString("Move");
				m_result.recognizerResult = GESTURE_TYPE_MOVE;
				if( doubleClickType == 1 && (curTime-doubleClickLastTime) < MinTipClickTime )
				{
					m_result.recognizerResult = GESTURE_TYPE_DOUBLE_MOVE;
					if(isMoving == 0)
					{
						isMoving = 2;
					}
				}
				if(isMoving == 2)
				{
					m_result.recognizerResult = GESTURE_TYPE_DOUBLE_MOVE;
				}
				else if( isMoving == 0 )
				{
					isMoving = 1;
				}
				//CCLOG("Move %d",curTime);
				m_result.point = m_GestureList[0][m_GestureList[0].size()-1].m_gPos;
				gestureRecognized(&m_result);
			}
		}
        if(fingerNum == 2)
        {
            unsigned long currentTime = GetMillisecondNow();
            if((currentTime - tlongPressStartTime)> 200 && (currentTime - tlongPressStartTime) < 1500)
            {
                bTwTouchNow = true;
                m_result.recognizerResult = GESTURE_TYPE_TWO_TAP_DOWN;
                gestureRecognized(&m_result);
            }
            //wanggang 0418pm
            /*else if((currentTime - tlongPressStartTime) > 1500)
            {
                printf("long press finger 2 --exceed 2s\n");
                m_result.recognizerResult = GESTURE_TYPE_TWO_TAP_UP;
                gestureRecognized(&m_result);
            }*/
             
        }
	}
    
}

void GestureRecognizer::ccTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event)
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    mPlayBounds = CCRectMake(size.width/2-100, size.height/2-100, 200, 200);
	unsigned long curTime = GetMillisecondNow();
    for(auto&& touch : touches)
    {
		int num = touch->getID();
		GesturePoint pos;
		pos.m_gPos = touch->getLocation();
		pos.m_touchTime = curTime;
		int size = m_GestureList[num].size();
		if (size == 0)
			continue;

		GesturePoint last = m_GestureList[num][size-1];
		float len = (pos.m_gPos - last.m_gPos).getLength();
		pos.sumlength = last.sumlength + len;
		m_GestureList[num].push_back(pos);
		if( fingerNum == 1 )
		{
			float length = m_GestureList[num][size].sumlength - m_GestureList[num][0].sumlength;
			long t = m_GestureList[num][size].m_touchTime - m_GestureList[num][0].m_touchTime;
			float rat = len/t*1000;
			if( len > 10 && rat > 10 )
			{
				longPressStartTime = curTime;
			}
		}
        //wanggang
        CCPoint location = touch->getLocationInView();
        if (mPlayBounds.containsPoint(location))
        {
            touchCrossedCount += 1;
        }
	}
}
void GestureRecognizer::ccTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event)
{
	unsigned long curTime = GetMillisecondNow();
    for(auto&& touch : touches)
    {
        int num = touch->getID();

		if (num >= m_GestureList[num].size())
			continue;

		GesturePoint pos;
		pos.m_gPos = touch->getLocation();
		pos.m_touchTime = curTime;
		int size = m_GestureList[num].size();
		GesturePoint last = m_GestureList[num][size-1];
		pos.sumlength = last.sumlength + (pos.m_gPos - last.m_gPos).getLength();
		m_GestureList[num].push_back(pos);
	}
	//
    for(auto&& touch : touches)
    {
		int num = touch->getID();
        if (m_resultlist.size() > 1) {
            break;
        }
		m_resultlist[num] = TouchesEndRecognizer(num);
	}

	m_DestPos.x = 0;
	m_DestPos.y = 0;

    for(auto&& touch : touches)
    {
		if ((m_DestPos.x == 0) && (m_DestPos.y == 0))
			m_DestPos = touch->getLocation();
		else
		{
			m_DestPos.x = (m_DestPos.x + touch->getLocation().x) / 2;
			m_DestPos.y = (m_DestPos.y + touch->getLocation().y) / 2;
		}

		int num = touch->getID();
		m_GestureList.erase(num);
	}
    {
        unsigned long currentTime = GetMillisecondNow();
        if (((currentTime - tlongPressStartTime) > 1500) && bTwTouchNow)
        {
            bTwTouchNow = false;
            m_result.recognizerResult = GESTURE_TYPE_TWO_TAP_UP;
            gestureRecognized(&m_result);
        }
        else
        {
           if (bTwTouchNow)
           {
               bTwTouchNow = false;
               m_result.recognizerResult = GESTURE_TYPE_TWO_TAP_GIVEUP;
               gestureRecognized(&m_result);
           }
        }
    }
	if(m_GestureList.empty())
	{
		if( m_resultlist.size() == 1 )
		{
			m_result.recognizerResult = m_resultlist[0];
			//m_Label->setString(m_RecognizerName[m_result.recognizerResult].c_str());
			if( doubleClickType == 1 && m_result.recognizerResult == GESTURE_TYPE_TIP_CLICK && (curTime-doubleClickLastTime) < MinTipClickTime )
			{
				m_result.point = m_DestPos;
				m_result.recognizerResult = GESTURE_TYPE_DOUBLE_CLICK;
				//m_Label->setString(m_RecognizerName[m_result.recognizerResult].c_str());
				gestureRecognized(&m_result);
			}
			//µ¥»÷
			else if( m_result.recognizerResult == GESTURE_TYPE_TIP_CLICK )
			{
				doubleClickType = 1;
				doubleClickLastTime = curTime;
				keypressDown(m_result.recognizerResult);
			}
			else
			{
				//m_Label->setString(m_RecognizerName[m_result.recognizerResult].c_str());
				gestureRecognized(&m_result);
            }
		}
		else if( m_resultlist.size() == 2 )
		{
			if( m_resultlist[0] == m_resultlist[1] )
			{
                    m_result.point = m_DestPos;
                    m_result.recognizerResult = GESTURE_TYPE_TWO_NONE + m_resultlist[0];
                    std::string name = "two finger " + m_RecognizerName[m_resultlist[0]];
                    //pLabel2->setString(name.c_str());
                    gestureRecognized(&m_result);
			}
		}
		isTouched = false;
		touchedNum = 0;
		fingerNum = 0;
		m_resultlist.clear();
		this->unschedule(schedule_selector(GestureRecognizer::LongPressRecognizer));
	}
	if(isMoving == 1 || isMoving == 2)
	{
		//m_Label->setString("Stop");
		isMoving = 0;
		m_result.recognizerResult = GESTURE_TYPE_MOVE_END;
		gestureRecognized(&m_result);
	}
}
struct gesturestep
{
	gesturestep():dirX(0),dirY(0),from(CCPointZero),to(CCPointZero),count(0),length(0.0f),time(0){}
	int dirX,dirY;
	CCPoint from;
	CCPoint to;
	int count;
	float length;
	long time;
};
int GestureRecognizer::TouchesEndRecognizer(int idx)
{
	if( idx > 1 )
		return 0;
	//std::vector<GesturePoint> poslist = m_GestureList[idx];
	int num = m_GestureList[idx].size();

	if (num == 0)
		return 0;

	long time = m_GestureList[idx][num-1].m_touchTime - m_GestureList[idx][0].m_touchTime;
	float totellength = m_GestureList[idx][num-1].sumlength - m_GestureList[idx][0].sumlength;
	if( time < MinTipClickTime && totellength < MinGestureLength )
	{
		//m_Labellist[idx]->setString("CLICK");
		return GESTURE_TYPE_TIP_CLICK;
	}
	if( time > MinGestureOnceTime || totellength < MinGestureLength)
		return 0;
	std::vector<gesturestep> list;
	gesturestep cur;
	for(int i = 0 ; i < num ; i++ )
	{
		if( i == 0 )
		{
			cur.dirX = 0;
			cur.dirY = 0;
			cur.from = m_GestureList[idx][i].m_gPos;
			cur.to = CCPointZero;
			cur.count = 1;
			cur.length = 0;
			cur.time = 0;
		}
		else
		{
			CCPoint lastpos = m_GestureList[idx][i-1].m_gPos;
			CCPoint curpos = m_GestureList[idx][i].m_gPos;
			float len = (curpos - lastpos).getLength();
			int changeX = 0,changeY = 0;
			if( abs(curpos.x - lastpos.x) >= MinStepX || abs(curpos.x - cur.from.x) >= MinStepX )
			{
				changeX = curpos.x > lastpos.x ? 1:-1;
			}
			if( abs(curpos.y - lastpos.y) >= MinStepY || abs(curpos.y - cur.from.y) >= MinStepY )
			{
				changeY = curpos.y > lastpos.y ? 1:-1;
			}
			if( cur.count == 1 || (cur.dirX == changeX && cur.dirY == changeY) )
			{
				cur.dirX = changeX;
				cur.dirY = changeY;
				cur.count++;
				cur.to = curpos;
				cur.length += len;
				cur.time += m_GestureList[idx][i].m_touchTime - m_GestureList[idx][i-1].m_touchTime;
			}
			else
			{
				list.push_back(cur);
				cur.dirX = changeX;
				cur.dirY = changeY;
				cur.from = lastpos;
				cur.to = curpos;
				cur.count = 2;
				cur.length = len;
				cur.time = m_GestureList[idx][i].m_touchTime - m_GestureList[idx][i-1].m_touchTime;
			}
		}
		if( i == num - 1 )
		{
			list.push_back(cur);
		}
	}
	int listnum =  list.size();
	if(listnum == 0)
		return 0;
	std::vector<gesturestep> glist;
	int tepi=0;
	for(int i = 0; i < listnum; i++)
	{
		float var = list[i].length/totellength;
		if( var > 0.4*1/listnum )
		{
			list[i].from = list[tepi].from;
			for( int j = tepi; j < i ; j++ )
			{
				list[i].count += list[j].count;
				list[i].length += list[j].length;
				list[i].time += list[j].time;
			}
			tepi = i + 1;
			glist.push_back(list[i]);
		}
	}
	//gesture method
	int type = 0;
	int dirX = 0,dirY = 0;
	int countRightX = 0,countLeftX = 0,countUpY = 0,countDownY = 0;
	CCPoint minX=glist[0].from,maxX=glist[0].from,minY=glist[0].from,maxY=glist[0].from;
	for( int k = 0 ; k < glist.size() ; k++ )
	{
		if( glist[k].dirX == 1 && dirX  == 0 )
		{
			dirX = 1;
		}
		else if( glist[k].dirX == -1 && dirX == 0 )
		{
			dirX = -1;
		}
		else if( glist[k].dirX == 1 && dirX == -1 )
		{
			dirX = 1;
			countLeftX++;
		}
		else if( glist[k].dirX == -1 && dirX == 1 )
		{
			dirX = -1;
			countRightX++;
		}
		if( glist[k].dirY == 1 && dirY  == 0 )
		{
			dirY = 1;
		}
		else if( glist[k].dirY == -1 && dirY == 0 )
		{
			dirY = -1;
		}
		else if( glist[k].dirY == 1 && dirY == -1 )
		{
			dirY = 1;
			countDownY++;
		}
		else if( glist[k].dirY == -1 && dirY == 1 )
		{
			dirY = -1;
			countUpY++;
		}
		if( minX.x > glist[k].from.x ) minX = glist[k].from;
		if( minX.x > glist[k].to.x ) minX = glist[k].to;
		if( maxX.x < glist[k].from.x ) maxX = glist[k].from;
		if( maxX.x < glist[k].to.x ) maxX = glist[k].to;
		if( minY.y > glist[k].from.y ) minY = glist[k].from;
		if( minY.y > glist[k].to.y ) minY = glist[k].to;
		if( maxY.y < glist[k].from.y ) maxY = glist[k].from;
		if( maxY.y < glist[k].to.y ) maxY = glist[k].to;
	}
	int countX = countRightX + countLeftX;
	int countY = countUpY + countDownY;
	if( countX > 0 && abs(minX.x-maxX.x) < 50 )
	{
		countX = 0;
		dirX = 0;
	}
	if( countY > 0 && abs(minY.y-maxY.y) < 50 )
	{
		countY = 0;
		dirY = 0;
	}
	if( countX == 0 && countY == 0 )
	{
		int X = dirX,Y = dirY;
		if( X != 0 && Y != 0 )
		{
			float f = (maxY.y-minY.y)/(maxX.x - minX.x);
			if( f < 0.41421 )
			{
				Y = 0;
			}
			else if( f > 2.41421 )
			{
				X = 0;
			}
		}
		if( X == 0 && Y > 0 /*abs(glist[0].from.x - glist[0].to.x) < 5*/)
		{
            if (m_resultlist.size() > 1) {
                type = GESTURE_TYPE_TWO_UP;
            }
            else
            {
                type = GESTURE_TYPE_UP;
            }
			//m_Labellist[idx]->setString("UP");
			return type;
		}
		if( X > 0 && Y > 0 )
		{
            if (m_resultlist.size() > 1) {
                type = GESTURE_TYPE_TWO_RIGHT_UP;
            }
            else
            {
                type = GESTURE_TYPE_RIGHT_UP;
            }
			//m_Labellist[idx]->setString("RIGHT_UP");
			return type;
		}
		if( X > 0 && Y == 0 )
		{
            if (m_resultlist.size() > 1) {
                type = GESTURE_TYPE_TWO_RIGHT;
            }
            else
            {
                type = GESTURE_TYPE_RIGHT;
            }
			
			//m_Labellist[idx]->setString("RIGHT");
			return type;
		}
		if( X > 0 && Y < 0 )
		{
            if (m_resultlist.size() > 1) {
                type = GESTURE_TYPE_TWO_RIGHT_DOWN;
            }
            else
            {
                type = GESTURE_TYPE_RIGHT_DOWN;
            }
			//m_Labellist[idx]->setString("RIGHT_DOWN");
			return type;
		}
		if( X == 0 && Y < 0 )
		{
            if (m_resultlist.size() > 1) {
                type = GESTURE_TYPE_TWO_DOWN;
            }
            else
            {
                type = GESTURE_TYPE_DOWN;
            }
			//m_Labellist[idx]->setString("DOWN");
            m_result.recognizerResult = type;
            gestureRecognized(&m_result);
			return type;
		}
		if( X < 0 && Y < 0 )
		{
            if (m_resultlist.size() > 1) {
                type = GESTURE_TYPE_TWO_LEFT_DOWN;
            }
            else
            {
                type = GESTURE_TYPE_LEFT_DOWN;
            }
			//m_Labellist[idx]->setString("LEFT_DOWN");
			return type;
		}
		if( X < 0 && Y == 0 )
		{
            if (m_resultlist.size() > 1) {
                type = GESTURE_TYPE_TWO_LEFT;
            }
            else
            {
                type = GESTURE_TYPE_LEFT;
            }
			//m_Labellist[idx]->setString("LEFT");
			return type;
		}
		if( X < 0 && Y > 0 )
		{
            if (m_resultlist.size() > 1) {
                type = GESTURE_TYPE_TWO_LEFT_UP;
            }
            else
            {
                type = GESTURE_TYPE_LEFT_UP;
            }
			//m_Labellist[idx]->setString("LEFT_UP");
			return type;
		}
	}
	if( countX == 0 && countUpY == 1 && countDownY == 0 && glist.size() == 2 )
	{
		type = GESTURE_TYPE_CURVE_UP;
		//m_Labellist[idx]->setString("CURVE_UP");
		return type;
	}
	if( countX == 0 && countUpY == 0 && countDownY == 1 && glist.size() == 2 )
	{
		type = GESTURE_TYPE_CURVE_DOWN;
		//m_Labellist[idx]->setString("CURVE_DOWN");
		return type;
	}
	if( countRightX == 1 && countLeftX == 0 && countY == 0 && glist.size() == 2 )
	{
		type = GESTURE_TYPE_CURVE_RIGHT;
		//m_Labellist[idx]->setString("CURVE_RIGHT");
		return type;
	}
	if( countRightX == 0 && countLeftX == 1 && countY == 0 && glist.size() == 2 )
	{
		type = GESTURE_TYPE_CURVE_LEFT;
		//m_Labellist[idx]->setString("CURVE_LEFT");
		return type;
	}
	if( (countX == 1 && countY == 2 && glist.size() == 3) || (countX == 2 && countY == 1 && glist.size() == 3) )
	{
		float l_X = 0.0f,l_Y = 0.0f;
		for( int i = 0 ; i < glist.size() ; i++ )
		{
			l_X += abs(glist[i].from.x - glist[i].to.x);
			l_Y += abs(glist[i].from.y - glist[i].to.y);
		}
		if( (countX == 2 && l_X > 2*(maxX.x - minX.x)) || (countY == 2 && l_Y > 2*(maxY.y - minY.y)) )
		{
			type = GESTURE_TYPE_TRIANGLE;
			//m_Labellist[idx]->setString("TRIANGLE");
            m_result.recognizerResult = type;
            gestureRecognized(&m_result);
			return type;
		}
	}
	if( ( (countX == 2  && (countY == 1 || countY == 2)) || (countY == 2  && (countX == 1 || countX == 2)) ) && glist.size() > 3 )
	{
		float l_X = 0.0f,l_Y = 0.0f;
		for( int i = 0 ; i < glist.size() ; i++ )
		{
			l_X += abs(glist[i].from.x - glist[i].to.x);
			l_Y += abs(glist[i].from.y - glist[i].to.y);
		}
		if( (countX == 2 && l_X > 2*(maxX.x - minX.x)) || (countY == 2 && l_Y > 2*(maxY.y - minY.y)) )
		{
			type = GESTURE_TYPE_CIRCLE;
			//m_Labellist[idx]->setString("CIRCLE");
			return type;
		}
	}
	if( type == 0 )
	{
		char buff[256];
		snprintf(buff,127,"gesture nothing size = %d,countX = %d,countY = %d",glist.size(),countX,countY);
		//m_Labellist[idx]->setString(buff);
	}
	return type;
}
void GestureRecognizer::keypressDown(int key)
{
	key;
}
