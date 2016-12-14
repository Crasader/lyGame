//
//  ly-Game
//
//  Created by loveyur on 2016/12/14
//  Copyright 2016 loveyur. All rights reserved.
//
//
#ifndef __RANDOM_UTIL_H_
#define __RANDOM_UTIL_H_

#define RANDOM(X) RandomUtil::next()%(int)X
#define RANDOM_SEED(X) RandomUtil::setSeed(X)

/*!
 * 乱数クラス
 */
class RandomUtil {
public:
    RandomUtil(void);
    RandomUtil(long seed);
    static void setSeed(long seed);
    static long getSeed();
    static int next();
public:
    static long m_seed;
    static long m_multiplier;
    static long m_addend;
    static long m_mask;
};

#endif //__RANDOM_UTIL_H_
