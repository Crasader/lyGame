
#include <time.h>
#include "RandomUtil.h"
#include "cocos2d.h"

long RandomUtil::m_multiplier = 0x5DEECE6C;
long RandomUtil::m_addend = 0xB;
//long RandomUtil::m_mask = (1LL << 48) - 1;
long RandomUtil::m_seed= 0x2342dda;

RandomUtil::RandomUtil(void) {
    setSeed(time(nullptr));
}

RandomUtil::RandomUtil(long seed) {
    setSeed(seed);
}

void RandomUtil::setSeed(long seed) {
    m_seed = (unsigned)(seed & 0x7fffffffU);
}

long RandomUtil::getSeed()
{
    return m_seed;
}

int RandomUtil::next() {
    m_seed = (m_seed * 1103515245U + 12345U) & 0x7fffffffU;
    return (int)(m_seed);
}
