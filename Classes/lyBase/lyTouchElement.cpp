//
//  lyTouchElement.cpp
//  act00
//
//  Created by songGT on 15/8/12.
//
//

#include "lyTouchElement.h"


lyTouchElement::lyTouchElement()
: m_bIsTouchBegan(false)
{
	// TODO: auto generated code
}

lyTouchElement::~lyTouchElement()
{
	// TODO: auto generated code
}

void lyTouchElement::cleanTouch()
{
    m_bIsTouchBegan = false;
    cleanChildrenTouch();
}
