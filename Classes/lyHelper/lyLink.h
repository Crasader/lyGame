/***************************************************************
		链表模版类
		by Shixc 2014-01-28
***************************************************************/
#ifndef __lyGame__lyLink__
#define __lyGame__lyLink__

#ifndef NULL
#ifdef __cplusplus
		#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif


template<class T> class lyLinkMgr;

template<class T>

class lyLinkItem
{
public:
	lyLinkItem()
	{
		lyLinkItem_Reset();
	}
	~lyLinkItem()
	{

	}
	lyLinkMgr<T>* _plyLinkItem_Parent;
	T*			_plyLinkItem_Prev;
	T*			_plyLinkItem_Next;
protected:
	friend class lyLinkMgr<T>;

	inline void lyLinkItem_Reset()
	{
		_plyLinkItem_Parent = NULL;
		_plyLinkItem_Prev	= NULL;
		_plyLinkItem_Next	= NULL;		
	}
};

template<class T>
class lyLinkMgr
{
public:
	lyLinkMgr() :
		_pLinkItem_ItemListH(NULL),
		_pLinkItem_ItemListE(NULL),
		_pLinkItem_Num(0){}

	virtual ~lyLinkMgr(){}
	//追加item
	inline void AddLinkItem(T* pItem)
	{
		if(!pItem)
			return;
		if (!_pLinkItem_ItemListH)
		{
            //如果head是空的，则end肯定是空的，后边那步骤肯定也会走到
            _pLinkItem_ItemListH = pItem;
            //赋值给链表头，既然是链表头，那么头的前边肯定是空，否则就不叫头了
            _pLinkItem_ItemListH->_plyLinkItem_Prev = NULL;
		}
		if (!_pLinkItem_ItemListE)
		{
			//如果head是空的，end也是空的，end也要赋值，此时证明原先链表是空的，add后，有了唯一的一个元素，head和end同时指向同一个数据
			_pLinkItem_ItemListE = pItem;
			_pLinkItem_ItemListE->_plyLinkItem_Next	= NULL;
		}
		else
		{
			//前边两个if都没走，证明链表原先有数据，这步是寻找插入
			_pLinkItem_ItemListE->_plyLinkItem_Next = pItem;
			pItem->_plyLinkItem_Next = NULL;
			pItem->_plyLinkItem_Prev = _pLinkItem_ItemListE;
			_pLinkItem_ItemListE = pItem;
		}
		pItem->_plyLinkItem_Parent = this;//must have this line ,this be used for judge 
		++_pLinkItem_Num;
	}
	//从链表中删除指定Item
	inline void DelLinkItem(T* pItem)
	{
		if(!pItem)
			return;
		if (this != pItem->_plyLinkItem_Parent)
			return;
		if (_pLinkItem_Num == 0)
			return;
		if ( pItem == _pLinkItem_ItemListH )
		{
			_pLinkItem_ItemListH = pItem->_plyLinkItem_Next;
		}
		if (pItem == _pLinkItem_ItemListE )
		{
			_pLinkItem_ItemListE = pItem->_plyLinkItem_Prev;
		}
		if (pItem->_plyLinkItem_Prev)
		{
			pItem->_plyLinkItem_Prev->_plyLinkItem_Next = pItem->_plyLinkItem_Next;
		}
		if (pItem->_plyLinkItem_Next )
		{
			//del center
			pItem->_plyLinkItem_Next->_plyLinkItem_Prev = pItem->_plyLinkItem_Prev;

		}
		pItem->lyLinkItem_Reset();
		--_pLinkItem_Num;
	}
	//插入item  参考的item为pRefItem  要插入的item为pInsertItem
	inline void InsertBehindLinkItem(T* pRefItem, T* pInsertItem)
	{
		if(!pInsertItem)
			return;
		do 
		{
			//如果head是null，那整个链表都为null，不管参考pRefItem是不是为空，都先插入
			if (!_pLinkItem_ItemListH)
			{
				_pLinkItem_ItemListH = pInsertItem;
				pInsertItem->_plyLinkItem_Prev = NULL;
				if (!_pLinkItem_ItemListE)
				{
					_pLinkItem_ItemListE = pInsertItem;
					pInsertItem->_plyLinkItem_Next = NULL;
				}
				break;
			}
			//如果上面的if 没进入，则下面先要判断参考item是不是本list的item
			if(!pRefItem)
				return;
			if (this != pRefItem->_plyLinkItem_Parent)
				return;
			if ( pRefItem == _pLinkItem_ItemListE )
			{
				_pLinkItem_ItemListE = pInsertItem;
			}
			pInsertItem->_plyLinkItem_Next = pRefItem->_plyLinkItem_Next;
			pInsertItem->_plyLinkItem_Prev = pRefItem;
			pRefItem->_plyLinkItem_Next = pInsertItem;
			if (pInsertItem->_plyLinkItem_Next)
			{
				pInsertItem->_plyLinkItem_Next->_plyLinkItem_Prev = pInsertItem;
			}
		} while (false);
		pInsertItem->_plyLinkItem_Parent = this;
		++_pLinkItem_Num;
	}
	//在某一个item前边插入一个新的item
	inline void InsertPreLinkItem(T* pRefItem, T* pInsertItem)
	{
		if(!pInsertItem)
			return;
		do 
		{
			//如果head是null，那整个链表都为null，不管参考pRefItem是不是为空，都先插入
			if (!_pLinkItem_ItemListH)
			{
				_pLinkItem_ItemListH = pInsertItem;
				pInsertItem->_plyLinkItem_Prev = NULL;
				if (!_pLinkItem_ItemListE)
				{
					_pLinkItem_ItemListE = pInsertItem;
					pInsertItem->_plyLinkItem_Next = NULL;
				}
				break;
			}
			//如果上面的if 没进入，则下面先要判断参考item是不是本list的item
			if(!pRefItem)
				return;
			if (this != pRefItem->_plyLinkItem_Parent)
				return;
			if ( pRefItem == _pLinkItem_ItemListH )
			{
				_pLinkItem_ItemListH = pInsertItem;
			}
			pInsertItem->_plyLinkItem_Prev = pRefItem->_plyLinkItem_Prev;
			if (pInsertItem->_plyLinkItem_Prev)
			{
				pInsertItem->_plyLinkItem_Prev->_plyLinkItem_Next = pInsertItem;
			}
			pInsertItem->_plyLinkItem_Next = pRefItem;	
			pRefItem->_plyLinkItem_Prev = pInsertItem;
		} while (false);
		pInsertItem->_plyLinkItem_Parent = this;
		++_pLinkItem_Num;

	}
	//获取链表元素个数
	inline unsigned long GetNumber()
	{
		return _pLinkItem_Num;
	}
	//获取链表头部item
	inline T* GetHeader()
	{
		return _pLinkItem_ItemListH;
	}
	//获取链表尾部item
	inline T* GetTail()
	{
		return _pLinkItem_ItemListE;
	}
	//获取某一个item的下一个item
	inline T* GetNextItem(T* pItem)
	{
		if(!pItem)
			return NULL;
		return pItem->_plyLinkItem_Next;
	}
	//获取某一个item前边的那个item
	inline T* GetPreItem(T* pItem)
	{
		if(!pItem)
			return NULL;
		return pItem->_plyLinkItem_Prev;
	}

protected:
    T*				_pLinkItem_ItemListH; //链表头
    T*				_pLinkItem_ItemListE; //链表尾
    unsigned long	_pLinkItem_Num;       //链表元素数目


};




#endif  //_lyLink_H
