//
//  ScrollingUtil.cpp
//  client-vitamin
//
//  Created by 大久保 孝一郎 on 2014/08/28.
//
//

#include "ScrollingUtil.h"

USING_NS_CC;


ScrollingUtil::ScrollingUtil()
: _averagingTouchCount(5)
, _tappingTolerancePoints(7.0f)
, _dependentValue(0.0f)
, _swiping(false)
, _tapped(false)
, _startDependentValue(0.0f)
, _touchStartPoint(Point::ZERO)
, _touchPointHistory()
{
    // デフォルトでは x 方向への移動量を dependentValue の更新に使う
    
    _tangentVector = [](const cocos2d::Point &p) {
        return Point(1, 0);
    };
    
    _dependentValueConverter = [](const cocos2d::Point &p1, const cocos2d::Point &p2) {
        return p2.x - p1.x;
    };
}


ScrollingUtil::~ScrollingUtil()
{
    
}


void ScrollingUtil::handleTouchBegan(const cocos2d::Point &touchPoint, float startDependentValue)
{
    // タッチ開始時の値を覚えておく
    _dependentValue = startDependentValue;
    _swiping = false;
    _tapped = false;
    _startDependentValue = startDependentValue;
    _touchStartPoint = touchPoint;
    
    // タッチ履歴のリセット
    clearTouchHistory();
    pushToTouchHistory(touchPoint);
}


void ScrollingUtil::handleTouchMoved(const cocos2d::Point &touchPoint)
{
    if (!_swiping) {
        // 許容移動方向への移動量
        float ds = calcTangentLength(_touchStartPoint, touchPoint);
        
        // 規定の移動量を超えたらスワイプと判定する
        if (fabsf(ds) > _tappingTolerancePoints) {
            _swiping = true;
        }
    }
    
    // スワイプ判定された場合だけ _dependentValue を更新する.
    // これがないとタップの時に誤差でぶるぶるするので.
    if (_swiping) {
        _dependentValue = _startDependentValue + calcDependentValue(_touchStartPoint, touchPoint);
        
    }

    pushToTouchHistory(touchPoint);
}


void ScrollingUtil::handleTouchEnded(const cocos2d::Point &touchPoint)
{
    if (!_swiping) {
        _tapped = true;
    }
    _swiping = false;
}


void ScrollingUtil::clearTouchHistory()
{
    _touchPointHistory.clear();
}


void ScrollingUtil::pushToTouchHistory(const cocos2d::Point &point)
{
    _touchPointHistory.push_back(point);
    
    // 直近の _averagingTouchCount 個の点だけ保存する
    while (_touchPointHistory.size() > this->getAveragingTouchCount()) {
        _touchPointHistory.pop_front();
    }
}


int ScrollingUtil::getLastDirection() const
{
    if (_touchPointHistory.size() <= 1) {
        // タップ開始時の1点しかタッチ点がないので移動なしと判定
        return 0;
    }
    else {
        // 直近の _averagingTouchCount 個のタッチ点を平均して移動量をもとめる
        float ds = calcTangentLength(_touchPointHistory.front(), _touchPointHistory.back());
        
        // 規定の移動量を超えたら移動中と判定する
        if (ds > _tappingTolerancePoints * +1.0f) {
            return +1;
        }
        if (ds < _tappingTolerancePoints * -1.0f) {
            return -1;
        }
        
        // 誤差の範囲内として, 移動なしと判定
        return 0;
    }
}


float ScrollingUtil::calcTangentLength(const cocos2d::Point &p1, const cocos2d::Point &p2) const
{
    return _tangentVector(p1).dot(p2 - p1);
}


float ScrollingUtil::calcDependentValue(const cocos2d::Point &p1, const cocos2d::Point &p2) const
{
    return _dependentValueConverter(p1, p2);
}


void ScrollingUtil::startConstantScroll(float nowValue, float destValue, float glidingTime, float breakingTime)
{
    _dependentValue = nowValue;
    
    float distance = destValue - _dependentValue;
    float t = glidingTime + breakingTime / 2;
    
    _autoScrolling = true;
    _autoScrollBeganTime = getTick();
    _autoScrollBreakTime = _autoScrollBeganTime + static_cast<unsigned long long>(glidingTime * 1000);
    _autoScrollEndTime = _autoScrollBreakTime + static_cast<unsigned long long>(breakingTime * 1000);
    _autoScrollStartValue = _dependentValue;
    _autoScrollDestValue = destValue;
    _autoScrollVelocity = distance / t;
    _autoScrollBreaking = - _autoScrollVelocity / breakingTime;
}


void ScrollingUtil::stopConstantScroll(float glidingTime, float breakingTime)
{
    if (!_autoScrolling) {
        return;
    }
    
    auto nowTime = getTick();
    
    if (nowTime >= _autoScrollBreakTime || nowTime >= _autoScrollEndTime) {
        // 既に減速中なのでそのまま
        return;
    }
    else {
        _autoScrollBreakTime = nowTime + static_cast<unsigned long long>(glidingTime * 1000);
        _autoScrollEndTime = _autoScrollBreakTime + static_cast<unsigned long long>(breakingTime * 1000);
        _autoScrollDestValue = _dependentValue + _autoScrollVelocity * (glidingTime + breakingTime / 2);
        _autoScrollBreaking = - _autoScrollVelocity / breakingTime;
    }
}


void ScrollingUtil::handleTimer(float dt)
{
    if (!_autoScrolling) {
        return;
    }
    
    auto nowTime = getTick();
    
    if (nowTime >= _autoScrollEndTime) {
        // auto scroll 終了
        _dependentValue = _autoScrollDestValue;
        _autoScrolling = false;
    }
    else if (nowTime >= _autoScrollBreakTime) {
        // 減速運動
        float t =  (_autoScrollEndTime - nowTime) * 1.0f / 1000;
        _dependentValue = _autoScrollDestValue + _autoScrollBreaking * t * t / 2;
    }
    else {
        // 等速運動
        float t = (nowTime - _autoScrollBeganTime) * 1.0f / 1000;
        _dependentValue = _autoScrollStartValue + _autoScrollVelocity * t;
    }
}


unsigned long long ScrollingUtil::getTick()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return t.tv_sec * 1000ull + t.tv_usec / 1000ull;
}

