//
//  ScrollingUtil.h
//
//  ly-Game
//
//  Created by loveyur on 2016/12/14
//  Copyright 2016 loveyur. All rights reserved.
//
//

#ifndef __lyGame__ScrollingUtil__
#define __lyGame__ScrollingUtil__

#include "cocos2d.h"


/**
 * スクロール補助ユーティリティ
 *
 * タッチイベントで拾った Point の値に応じてオブジェクトを動かしたり,
 * 回転させたり何だりするときの計算を抽象化したクラス.
 *
 * スワイプとともに変化させる値 (位置だったり角度だったり) は,
 * ここでは dependentValue と呼んでいます.
 *
 * タップとスワイプを判定するためのしきい値の処理だったり,
 * 移動方向を求めるための処理を毎回書くのが面倒だったので作りました.
 */
class ScrollingUtil
{
public:
    ScrollingUtil();
    virtual ~ScrollingUtil();
    
    
    /**
     * タッチ開始ハンドラ
     *
     * @param touchPoint タッチイベントで拾った値を渡す
     * @param startDependentValue タッチ開始時点での dependentValue の値
     */
    void handleTouchBegan(const cocos2d::Point &touchPoint, float startDependentValue);
    
    
    /**
     * タッチ移動ハンドラ
     * これを呼ぶと, スワイプの移動方向と dependentValue が更新される.
     *
     * @param touchPoint タッチイベントで拾った値を渡す
     */
    void handleTouchMoved(const cocos2d::Point &touchPoint);
    
    
    /**
     * タッチ終了ハンドラ
     *
     * @param touchPoint タッチイベントで拾った値を渡す
     */
    void handleTouchEnded(const cocos2d::Point &touchPoint);
    
    
    /**
     * スワイプの移動方向を取得する
     *
     * @return 正のとき, dependentValue が増加する方向にスワイプされた
     * @return 負のとき, dependentValue が減少する方向にスワイプされた
     * @return 0 のとき, 移動なし.
     */
    int getLastDirection() const;
    
    
    /**
     * @return dependentValue を取得する
     *
     * handleTouchMoved を呼ぶたびに新しい値が取れます.
     */
    float getDependentValue() const {
        return _dependentValue;
    }
    
    
    /**
     * @return タッチ開始点を取得する
     */
    cocos2d::Point getTouchStartPoint() const {
        return _touchStartPoint;
    }
    
    
    /**
     * @return スワイプ中かどうかを取得
     */
    bool isSwiping() const {
        return _swiping;
    }
    
    
    /**
     * @return タップだったかどうかを取得
     *
     * handleTouchEnded のあと, (スワイプではなく)タップだったと判定されたとき true
     */
    bool isTapped() const {
        return _tapped;
    }
    
    
    /**
     * 等速スクロールを開始する
     *
     * @param nowValue 現在の dependentValue
     * @param destValue 移動先の dependentValue
     * @param glidingTime 等速移動する時間(秒)
     * @param breakingTime 減速移動する時間(秒)
     */
    void startConstantScroll(float nowValue, float destValue, float glidingTime = 0.2f, float breakingTime = 0.1f);

    /**
     * 等速スクロールを停止させる
     *
     * @param glidingTime 等速移動する時間(秒)
     * @param breakingTime 減速移動する時間(秒)
     */
    void stopConstantScroll(float glidingTime, float breakingTime = 0.1f);
    
    /**
     * タイマーイベントハンドラ
     *
     * 自動スクロール中に呼ぶと dependentValue が更新される
     */
    void handleTimer(float dt);
    
    
    /**
     * @return 自動スクロール中かどうかを取得
     */
    bool isAutoScrolling() const {
        return _autoScrolling;
    }
    
    
private:
    float _dependentValue;
    bool _swiping;
    bool _tapped;
    
    float _startDependentValue;
    cocos2d::Point _touchStartPoint;
    std::list<cocos2d::Point> _touchPointHistory;
    
    void clearTouchHistory();
    void pushToTouchHistory(const cocos2d::Point &point);
    
    float calcTangentLength(const cocos2d::Point &p1, const cocos2d::Point &p2) const;
    float calcDependentValue(const cocos2d::Point &p1, const cocos2d::Point &p2) const;
    
    
    bool _autoScrolling;
    unsigned long long _autoScrollBeganTime;
    unsigned long long _autoScrollBreakTime;
    unsigned long long _autoScrollEndTime;
    
    float _autoScrollStartValue;
    float _autoScrollDestValue;
    float _autoScrollVelocity;
    float _autoScrollBreaking;
    
    unsigned long long getTick();

    
private:
    //! 移動方向を決めるときに平均化するタッチ点の数
    int _averagingTouchCount;
    
    //! タップの際に生じるタッチ座標の許容誤差
    float _tappingTolerancePoints;

    //! dependentValue が増加する方向の単位ベクトル
    std::function<cocos2d::Vec2(const cocos2d::Point &point)> _tangentVector;
    
    //! 二点の位置から dependentValue の増分への変換関数
    std::function<float(const cocos2d::Point &p1, const cocos2d::Point &p2)> _dependentValueConverter;
    
    
public:
    void setAveragingTouchCount(int value) {
        _averagingTouchCount = value;
    }
    
    int getAveragingTouchCount() const {
        return _averagingTouchCount;
    }
    
    void setTappingTolerancePoints(float value) {
        _tappingTolerancePoints = value;
    }
    
    float getTappingTolerancePoints() const {
        return _tappingTolerancePoints;
    }
    
    void setTangentVector(const std::function<cocos2d::Vec2(const cocos2d::Point &point)> &func) {
        _tangentVector = func;
    }
    
    void setDependentValueConverter(const std::function<float(const cocos2d::Point &p1, const cocos2d::Point &p2)> &func) {
        _dependentValueConverter = func;
    }
    
};

#endif /* defined(__lyGame__ScrollingUtil__) */
