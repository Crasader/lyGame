
/***************************************************************
*	lyCocosSprite
*	by Shixc 2014-05-05
***************************************************************/

#ifndef _lyCocosSprite_H_
#define _lyCocosSprite_H_


#include "lyInclude.h"
#include "lyLink.h"

class lyCocosSprite
	: public CCSprite,
	public lyLinkItem<lyCocosSprite>
{
public:
	lyCocosSprite();
	~lyCocosSprite();
	static lyCocosSprite* Create();


};

#endif //_lyCocosSprite_H_
