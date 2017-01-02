//
//  lyMemoryPool.h
//  act00
//
//  Created by songGT on 15/8/16.
//
//

#ifndef __act00__lyMemoryPool__
#define __act00__lyMemoryPool__

#include "lyInclude.h"
#include "lyLink.h"

#define __MEMPOOL_NODE_ELEM_NUM 20


template<class T>
class lyMemoryNode
:public lyLinkItem<lyMemoryNode<T>>
{
public:
    typedef T	_DataType;
    
    lyMemoryNode()
    {
        OnCreate();
    }
    
    ~lyMemoryNode()
    {
        OnRelease();
    }
    
    _DataType* MemMalloc()
    {
        if (m_nUsedElemNum < m_nTotalElemNum)
        {
            m_pMemIndex[m_nUsedElemNum]->init();
            return m_pMemIndex[m_nUsedElemNum++];
        }
        return NULL;
    }
    
    bool MemFree(_DataType* pMem)
    {
        if (pMem >= m_pMemSet && pMem < m_pMemSet+m_nTotalElemNum)
        {
            for (int nIndex=0; nIndex<m_nUsedElemNum; ++nIndex)
            {
                if (m_pMemIndex[nIndex] == pMem)
                {
                    //
                    if (nIndex != m_nUsedElemNum-1)
                    {
                        _DataType* pMem = m_pMemIndex[nIndex];
                        m_pMemIndex[nIndex] = m_pMemIndex[m_nUsedElemNum-1];
                        m_pMemIndex[m_nUsedElemNum-1] = pMem;
                        pMem->onRelease();
                    }
                    --m_nUsedElemNum;
                    return true;
                }
            }
        }
        return false;
    }
    
    int GetUsedElemNum()
    {
        return m_nUsedElemNum;
    }
    
protected:
    void InitMem()
    {
        //m_pMemSet = (_DataType*)malloc(sizeof(_DataType)*m_nTotalElemNum);
        m_pMemSet = new _DataType[m_nTotalElemNum];
        for (int nIndex=0; nIndex<m_nTotalElemNum; ++nIndex)
        {
            m_pMemIndex[nIndex] = (m_pMemSet+nIndex);
        }
    }
    
    void OnCreate()
    {
        m_nUsedElemNum = 0;
        m_nTotalElemNum = __MEMPOOL_NODE_ELEM_NUM;
        m_pMemSet = NULL;
        //memset(m_pMemIndex, 0 , sizeof(_DataType*)*m_nTotalElemNum);
        for (int nIndex=0; nIndex<m_nTotalElemNum; ++nIndex)
        {
            m_pMemIndex[nIndex] = NULL;
        }
        
        InitMem();
    }
    
    void OnRelease()
    {
        delete []m_pMemSet;
        
        //memset(m_pMemIndex, 0 , sizeof(_DataType*)*m_nTotalElemNum);
        for (int nIndex=0; nIndex<m_nTotalElemNum; ++nIndex)
        {
            m_pMemIndex[nIndex] = NULL;
        }
        m_pMemSet = NULL;
    }
    
    int		m_nUsedElemNum;
    int		m_nTotalElemNum;
    
private:
    _DataType*		m_pMemSet;
    _DataType*		m_pMemIndex[__MEMPOOL_NODE_ELEM_NUM];
    
};


//memory allocate and free
template<class T>
class lyMemoryPool
{
public:
    typedef T			_DataType;
    typedef lyMemoryNode<T>	_NodeType;
    
    static lyMemoryPool* getInstance()
    {
        if (NULL == m_pMemInstance)
        {
            m_pMemInstance = new lyMemoryPool;
        }
        return m_pMemInstance;
    }
    
    _DataType* MemMalloc()
    {
        //malloc from exist mem
        _NodeType* pHead = m_objMemoryPool.SLM_GetHead();
        while (pHead)
        {
            _DataType* pData = pHead->MemMalloc();
            if (pData)
            {
                return pData;
            }
            pHead = m_objMemoryPool.SLM_GetNextItem(pHead);
        }
        //create new mem
        _NodeType* pNode = new _NodeType;
        m_objMemoryPool.SLM_AddItem(pNode);
        return pNode->MemMalloc();
    }
    
    bool MemFree(_DataType* pData)
    {
        _NodeType* pHead = m_objMemoryPool.SLM_GetHead();
        while (pHead)
        {
            bool bRes = pHead->MemFree(pData);
            if (bRes)
            {
                //if pHead 0 == usednum change the node to the end or delete;
                int nUsedElemNum = pHead->GetUsedElemNum();
                if (0 == nUsedElemNum)
                {
                    //change the node state(change to the tail)
                    m_objMemoryPool.SLM_DelItem(pHead);
                    m_objMemoryPool.SLM_AddItem(pHead);
                }
                return true;
            }
            pHead = m_objMemoryPool.SLM_GetNextItem(pHead);
        }
        return false;
    }
    
protected:
    lyMemoryPool()
    {
        OnCreate();
    }
    
    void OnCreate()
    {
        m_pMemInstance = NULL;
    }
    
private:
    lyLinkMgr<lyMemoryNode<T>>    m_objMemoryPool;
    static lyMemoryPool*		m_pMemInstance;
};
template<class T>	lyMemoryPool<T>* lyMemoryPool<T>::m_pMemInstance = NULL;



#endif /* defined(__act00__lyMemoryPool__) */
