//
//  LotteryUtil.h
//
//  ly-Game
//
//  Created by loveyur on 2016/12/14
//  Copyright 2016 loveyur. All rights reserved.
//
//

#ifndef __lyGame__LotteryUtil__
#define __lyGame__LotteryUtil__

#include <string>
#include <list>
#include <random>

namespace LotteryUtil {

    namespace RandomUtils {
        static int nextInt() {
            std::random_device rdev;
            std::mt19937 engine(rdev()); // 乱数生成器
            std::uniform_int_distribution<> dist(0, INT32_MAX);
            return dist(engine);
        }
    }
    
	/** 抽選の一万分率を使用する際の定数 */
	static constexpr int LOTTERY_BASE_PROBABILITY = 10000;
    
	/**
	 * 抽選を行い、当たったオブジェクトを返します。
	 *
	 * @param targetLotteryList
	 *            抽選対象のオブジェクト一覧
	 * @return 当選したオブジェクト
	 */
    template <class T>
	static T* lot(const std::list<T> &targetLotteryList, const std::function<int(T)> &probFunc)
    {
        assert(!targetLotteryList.empty() && "listが空です");

		int entireProbability = 0;
		for (auto targetLottery : targetLotteryList) {
			entireProbability += probFunc(targetLottery);
		}
        return lot(targetLotteryList, entireProbability);
	}
    
	/**
	 * 抽選を行い、当たったオブジェクトを返します。<br/>
	 * ヒットしなかった場合、nullを返します。
	 *
	 * @param targetLotteryList
	 *            抽選対象のオブジェクト一覧
	 * @param entireProbability
	 *            全体の割合
	 * @return 当選したオブジェクト
	 */
    template <class T>
	static T* lot(const std::list<T> &targetLotteryList, int entireProbability, const std::function<int(T)> &probFunc)
    {
        assert(!targetLotteryList.empty() && "listが空です");

		int tempEntireProbability = 0;
		for (auto targetLottery : targetLotteryList) {
			tempEntireProbability += probFunc(targetLottery);
		}
        
		if (entireProbability < tempEntireProbability) {
			entireProbability = tempEntireProbability;
		}
        
		T *result = nullptr;
        
		int randomProbability = (RandomUtils::nextInt() % entireProbability) + 1;
		int tempProbability = 0;
		for (auto targetLottery : targetLotteryList) {
            
			tempProbability += probFunc(targetLottery);
			if (tempProbability >= randomProbability) {
				result = &targetLottery;
				break;
			}
		}
        
		return result;
	}
    
    // TODO: 使う？
	/**
	 * 抽選を行い、当たった場合「真」を返します。
	 *
	 * @param targetLotteryList
	 *            抽選対象のオブジェクト一覧
	 * @param entireProbability
	 *            全体の割合
	 * @return ヒットした場合：「真」
	 */
//    template <class T>
//	static bool isHit(std::list<T> targetLotteryList, int entireProbability, std::function<int(T)> probFunc) {
//		return lot(targetLotteryList, entireProbability, probFunc) != nullptr;
//	}
    
	/**
	 * 抽選を行い当たった場合「真」を返します。
	 * @param lotProbability 抽選の割合
	 * @param totalProbability  全体の割合
	 * @return ヒットした場合：「真」
	 */
	static bool isHit(int lotProbability, int totalProbability) {
        
		if(lotProbability == 0 || totalProbability == 0) {
			return false;
		}
        
		int randomProbability = (RandomUtils::nextInt() % totalProbability);
        
		return lotProbability > randomProbability;
	}
    
    /**
	 * 抽選を行い当たった場合「真」を返します。
	 * 全体の割合 は LOTTERY_BASE_PROBABILITY ( 10000)として計算します
	 * @param lotProbability 抽選の割合
	 * @return ヒットした場合：「真」
	 */
	static bool isHit(int lotProbability) {
		return isHit(lotProbability, LOTTERY_BASE_PROBABILITY);
	}
}

#endif
