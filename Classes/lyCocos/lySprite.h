
/***************************************************************
*	lySprite
*	by Shixc 2014-05-05
***************************************************************/

#ifndef _lySprite_H_
#define _lySprite_H_


#include "lyInclude.h"
#include "lyLink.h"

class lySprite
	: public CCSprite,
	public lyLinkItem<lySprite>
{
public:
	lySprite();
	~lySprite();
	static lySprite* Create();


};

#endif //_lySprite_H_
