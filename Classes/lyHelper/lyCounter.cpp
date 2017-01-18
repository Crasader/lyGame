#include "lyCounter.h"
#include <assert.h>
#include "lyAndLog.h"

lyCounterData::lyCounterData(const char *pName)
{
	
}
void lyCounterData::Inc()
{
	if(++nCounter > nMax)
		nMax = nCounter;
}
void lyCounterData::Dec()
{
	--nCounter;
	assert(nCounter >= 0);
}
