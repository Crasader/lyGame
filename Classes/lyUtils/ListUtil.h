//
//  ListUtil.h
//
//  ly-Game
//
//  Created by loveyur on 2016/12/14
//  Copyright 2016 loveyur. All rights reserved.
//
//

#ifndef Donut_ListUtil_h
#define Donut_ListUtil_h

#include <list>

namespace ListUtil {
    
    // サーバ側のListUtilsを移植なんかしてくれると助かるなあ。。。
    
    /**
     * std::mergeがうまくできないので仕方なくこれでやってみた
     */
    template <class T>
    static void addAll(std::list<T> &base, const std::list<T> &add)
    {
        for (auto a : add) { base.push_back(a);}
    }
    
    /**
     * 中身とか合計したいときとか
     */
    template <class T, class R>
    static R total(const std::list<T> &list, const std::function<R(void)> defaultFunc, const std::function<R(T)> &totalFunc)
    {
        if (list.size() == 0)
        {
            return 0;
        }
        
        R result = defaultFunc();
        for (auto t : list)
        {
            result += totalFunc(t);
        }
        return result;
    }
    
    /**
     * リストから条件にあったやつをリストで返す
     */
    template <class T>
    static std::list<T> findList(const std::list<T> &list, const std::function<bool(T)> &checkFunc)
    {
        assert(!list.empty() && "list是空的");

        std::list<T> result;
        for (auto t : list)
        {
            if (checkFunc(t))
            {
                result.push_back(t);
            }
        }
        return result;
    }

    /**
     * リストから条件にあったやつをリストで返す
     * 条件要素渡す的な？
     */
    template <class T, class C>
    static std::list<T> findList(const std::list<T> &list, const C &condition, const std::function<bool(T, C)> &checkFunc)
    {
        assert(!list.empty() && "list是空的");

        std::list<T> result;
        for (T t : list)
        {
            if (checkFunc(t, condition))
            {
                result.push_back(t);
            }
        }
        return result;
    }

    /**
     * リストから条件にあったものを１件かえす。
     * ないときは空オブジェクトを返す
     */
    template <class T>
    static T findOne(const std::list<T> &list, const std::function<bool(T)> &checkFunc)
    {
        assert(!list.empty() && "list是空的");
        
        for (auto it = list.begin(); it != list.end(); it++)
        {
            T obj = (T)*it;
            if (checkFunc(obj))
            {
                return obj;
            }
        }
        return T{};
    }
    
    /**
     * リストの型を変換したリストを返す
     */
    template <class T, class C>
    static std::list<C> convertList(const std::list<T> &list, const std::function<C(T)> &convertFunc)
    {
        std::list<C> result;
        for (T t : list)
        {
            result.push_back(convertFunc(t));
        }
        return result;
    }
    
    /**
     * 条件にあったものがリストにあるか
     */
    template <class T>
    static bool find(const std::list<T> &list, const std::function<bool(T)> &checkFunc)
    {
        for (T t : list)
        {
            if (checkFunc(t))
            {
                return true;
            }
        }
        return false;
    }

    /**
     * 条件にあったものがリストにあるか
     */
    template <class T, class C>
    static bool find(const std::list<T> &list, const C &condition, const std::function<bool(T, C)> &checkFunc)
    {
        for (T t : list)
        {
            if (checkFunc(t, condition))
            {
                return true;
            }
        }
        return false;
    }
    
    
    // vector用
    template <class T>
    static void addAll(std::vector<T> &base, const std::vector<T> &add)
    {
        for (auto a : add) { base.push_back(a);}
    }
    
    template <class T, class R>
    static R total(const std::vector<T> &list, const std::function<R(void)> defaultFunc, const std::function<R(T)> &totalFunc)
    {
        R result = defaultFunc();
        for (auto t : list)
        {
            result += totalFunc(t);
        }
        return result;
    }

    template <class T>
    static std::vector<T> findList(const std::vector<T> &list, const std::function<bool(T)> &checkFunc)
    {
        assert(!list.empty() && "list是空的");
        
        std::vector<T> result;
        for (auto t : list)
        {
            if (checkFunc(t))
            {
                result.push_back(t);
            }
        }
        return result;
    }
    
    template <class T, class C>
    static std::vector<T> findList(const std::vector<T> &list, const C &condition, const std::function<bool(T, C)> &checkFunc)
    {
        assert(!list.empty() && "list是空的");
        
        std::vector<T> result;
        for (T t : list)
        {
            if (checkFunc(t, condition))
            {
                result.push_back(t);
            }
        }
        return result;
    }
    
    template <class T>
    static T findOne(const std::vector<T> &list, const std::function<bool(T)> &checkFunc)
    {
        assert(!list.empty() && "list是空的");
        
        for (auto it = list.begin(); it != list.end(); it++)
        {
            T obj = (T)*it;
            if (checkFunc(obj))
            {
                return obj;
            }
        }
        return T{};
    }
    
    template <class T, class C>
    static std::vector<C> convertList(const std::vector<T> &list, const std::function<C(T)> &convertFunc)
    {
        std::vector<C> result;
        for (T t : list)
        {
            result.push_back(convertFunc(t));
        }
        return result;
    }

    template <class T>
    static bool find(const std::vector<T> &list, const std::function<bool(T)> &checkFunc)
    {
        for (T t : list)
        {
            if (checkFunc(t))
            {
                return true;
            }
        }
        return false;
    }

    template <class T, class C>
    static bool find(const std::vector<T> &list, const C &condition, const std::function<bool(T, C)> &checkFunc)
    {
        for (T t : list)
        {
            if (checkFunc(t, condition))
            {
                return true;
            }
        }
        return false;
    }

}

#endif
