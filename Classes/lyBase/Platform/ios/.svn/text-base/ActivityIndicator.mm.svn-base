
#include "ActivityIndicator.h"
#include "ActivityIndicator_objc.h"
#include "cocos2d.h"



//インジケータースタート
void ActivityIndicator::startAnimating()
{
    ActivityIndicator_objc *instance = [ActivityIndicator_objc getInstance];
    [instance startAnimating];
}

//インジケータースタート
// スタートが複数呼ばれている場合中のカウントが０になったとき消されます。
void ActivityIndicator::stopAnimating()
{
    ActivityIndicator_objc *instance = [ActivityIndicator_objc getInstance];
    [instance stopAnimating];
}

//インジケーター強制ストップ
// スタートが呼ばれた数に限らず、強制的にカウントを０にして消されます。
void ActivityIndicator::forceStopAnimating()
{
    ActivityIndicator_objc *instance = [ActivityIndicator_objc getInstance];
    [instance forceStopAnimating];
}


//中心位置の指定
void ActivityIndicator::setPosition(float x, float y)
{
    ActivityIndicator_objc *instance = [ActivityIndicator_objc getInstance];
    [instance setPosition:x setPosition:y];
    CCLOG( "ActivityIndicator : %.0f,%.0f", x, y );
}