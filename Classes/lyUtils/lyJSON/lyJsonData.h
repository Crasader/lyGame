//
//  lyJsonData.h
//  cocos2d-x-jc
//
//  Created by LIN BOYU on 11/14/12.
//
//

#ifndef __cocos2d__lyJsonData__
#define __cocos2d__lyJsonData__

#include "cocos2d.h"
USING_NS_CC;

class lyNumber : public Ref {
private:
    int m_nValue;
    double m_dValue;
public:
    lyNumber(int v)
    : m_nValue(v),m_dValue(v) {}
    
    lyNumber(double v)
    : m_nValue(v),m_dValue(v) {}
    
    static lyNumber * create(int v)
    {
        lyNumber* pRet = new lyNumber(v);
        pRet->autorelease();
        return pRet;
    }
    static lyNumber* create(double v)
    {
        lyNumber* pRet = new lyNumber(v);
        pRet->autorelease();
        return pRet;
    }
    int getIntValue() const {return m_nValue;}
    double getDoubleValue() const {return m_dValue;}
    void setValue(int v)  { m_nValue=v; m_dValue=v;}
    void setValue(double v)  { m_nValue=v; m_dValue=v;}
};

//class CCBool : public Ref {
//private:
//    bool m_bValue;
//public:
//    CCBool(bool v)
//    :m_bValue(v){}
//    
//    static CCBool * create(bool v)
//    {
//        CCBool * pRet = new CCBool(v);
//        pRet->autorelease();
//        return pRet;
//    }
//    
//    bool getValue() const { return m_bValue; }
//    void setValue(bool v) { m_bValue = v; }
//};

class lyNull : public Ref {
public:
    static lyNull * create()
    {
        lyNull * pRet = new lyNull();
        pRet->autorelease();
        return pRet;
    }
};

#endif /* defined(__cocos2d__lyJsonData__) */
