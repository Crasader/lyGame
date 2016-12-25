/***************************************************************
	lyCounter
	by Shixc 2014-01-28
***************************************************************/

#ifndef _lyCounter_H_
#define _lyCounter_H_



class lyCounterData
{
public:
	lyCounterData(const char *pName);
	~lyCounterData(){};

	void Inc();
	void Dec();
	inline int CurrentCount()
	{
		return nCounter;
	}
	inline int MaxCount()
	{
		return nMax;
	}
private:
	int nCounter;
	int nMax;
};


template<class T> 
class lyCounter
{
public:
	lyCounter(){_data.Inc();}
	~lyCounter(){_data.Dec();}
	lyCounter(const lyCounter&){_data.Dec();}
public:
	int CurrentCount(){return _data.CurrentCount();}
	int MaxCount(){return _data.MaxCount();}

private:
	static lyCounterData _data;
};

template<class T> lyCounterData lyCounter<T>::_data = lyCounterData(typeid(T).name());

#endif
