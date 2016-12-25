#ifndef _lyArray_H_
#define _lyArray_H_


/*** ***
	数组类
	实现类似lua的数组功能
	by Shixc 2014-01-28

*** ***/

#define SZ_MAX_NUM 256

#define SZ_MAX_ACT_GROUP 256


template<class T, int nMaxNum>

class lyArray
{
public:
	lyArray();
	static ~lyArray();

    //传参数的话，插入到指定的位置，后边数据依次后移。默认从最后插入
    void Insert_To_SZ(unsigned int nSzPos = SZ_MAX_NUM);
    //从nSzPos移除pData数据，pos不传的话默认从最后开始往前寻找第一个pData数据 移除
    void Remove_From_SZ(T* pData, unsigned int nSzPos = SZ_MAX_NUM);

};



#endif  //_lyArray_H_
