/***************************************************************
		通用函数定义类
		by Shixc 2014-04-10
***************************************************************/
#ifndef __lyGame__lyFunc__
#define __lyGame__lyFunc__

const double   Pi        = 3.14159;
const double   TwoPi     = Pi * 2;
const double   HalfPi    = Pi / 2;
const double   QuarterPi = Pi / 4;

/*** ***---------------------------------------------------------------*** ***/
#define fIsZero(fVal)	( -0.00001f <= (fVal) && (fVal) <= 0.00001f )  //判断float是否为0
#define fAbs(fVal)	( (fVal) >= 0.f ? (fVal) :  -(fVal))				//求绝对值
/*** ***---------------------------------------------------------------*** ***/

/*** ***---------------------------------------------------------------*** ***/
#define SAFE_DELETE(p)		if(p){ delete(p); (p) = NULL;}
#define SAFE_DELETE_ARRAY(p)		if(p){ delete[] (p); (p) = NULL;}
/*** ***---------------------------------------------------------------*** ***/

float fNowTick = 0;
unsigned long GetMillisecondNow()
{
    return (unsigned long)fNowTick;
}

void AddMillisecondTime(float nDelta)
{
    fNowTick += nDelta * 1000;
}

/*** ***---------------------------------------------------------------*** ***/
inline bool IsPng(const char* strName)
{
	int nLen = 0;
	if (!strName || !strName[0])
		return false;
	nLen = sizeof(strName);
	if (nLen <= 4)
		return false;
	if ('.' != strName[nLen-4])
		return false;
	if ('p' != tolower(strName[nLen-3]) )
		return false;
	if ('n' != tolower(strName[nLen-2]) )
		return false;
	if ('g' != tolower(strName[nLen-1]) )
		return false;
	return true;		
}
inline bool IsJpg(const char* strName)
{
	int nLen = 0;
	if (!strName || !strName[0])
		return false;
	nLen = sizeof(strName);
	if (nLen <= 4)
		return false;
	if ('.' != strName[nLen-4])
		return false;
	if ('j' != tolower(strName[nLen-3]) )
		return false;
	if ('p' != tolower(strName[nLen-2]) )
		return false;
	if ('g' != tolower(strName[nLen-1]) )
		return false;
	return true;		
}
inline bool IsJpeg(const char* strName)
{
	int nLen = 0;
	if (!strName || !strName[0])
		return false;
	nLen = sizeof(strName);
	if (nLen <= 5)
		return false;
	if ('.' != strName[nLen-5])
		return false;
	if ('j' != tolower(strName[nLen-4]) )
		return false;
	if ('p' != tolower(strName[nLen-3]) )
		return false;
	if ('e' != tolower(strName[nLen-2]) )
		return false;
	if ('g' != tolower(strName[nLen-1]) )
		return false;
	return true;		
}
/*** ***---------------------------------------------------------------*** ***/





//角度转弧度
inline double lyDegsToRads(double degs)
{
    return TwoPi * (degs/360.0);
}

//compares two real numbers. Returns true if they are equal
inline bool lyIsEqual(float a, float b)
{
    if (fabs(a-b) < 1E-12)
    {
        return true;
    }
    
    return false;
}

inline bool lyIsEqual(double a, double b)
{
    if (fabs(a-b) < 1E-12)
    {
        return true;
    }
    
    return false;
}

//
inline bool InRange(double start, double end, double val)
{
    if (start < end)
    {
        if ( (val > start) && (val < end) )
            return true;
        else
            return false;
    }
    
    else
    {
        if ( (val < start) && (val > end) )
            return true;
        else
            return false;
    }
}

//返回最大值
template <class T>
T lyMax(const T& v1, const T& v2)
{
    return v1 > v2 ? v1 : v2;
}

//返回最小值
template <class T>
T lyMin(const T& v1, const T& v2)
{
    return v1 > v2 ? v2 : v1;
}

//x,y之间随机数
inline int lyRandInt(int x,int y)
{
    assert(y>=x && "<lyRandInt>: y is less than x");
    return rand()%(y-x+1)+x;
}

//returns a random double between zero and 1
inline double lyRandFloat()
{
    return ((rand())/(RAND_MAX+1.0));
}

inline int lyStrToInt(const char* str)
{
    std::istringstream iss(str);
    int val = 0;
    iss >> val;
    return val;
}


#endif  //__lyGame__lyFunc__
