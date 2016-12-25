#include "lyMemory.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

lyMemory::lyMemory()
{
	_chunklist = 0;
	memset(_freelist,0,sizeof(_freelist));
}

lyMemory::~lyMemory()
{
	int s = 0;
	//计算内存块数
	chunk_list * tmp = _chunklist;
	while(tmp)
	{
		s++;
		tmp = tmp->_next;
	}

	//保存内存块链表指针
	void ** chunk = reinterpret_cast<void **>(malloc(s * sizeof(void *)));
	tmp = _chunklist;
	int i = 0;
	while(tmp)
	{
		chunk[i] = tmp->_data;
		++i;
		tmp = tmp->_next;
	}
	//释放指针
	for(i=0;i<s;i++)
	{
		free(chunk[i]);
	}
	free(chunk);
}

//返回待分配的idx，8byte的倍数，向下取整
size_t lyMemory::chunk_index(size_t bytes)
{
	size_t idx = (bytes - 1) / align_size;
	assert(idx >= 0 && idx < chunk_number);
	return idx;
}
//分配内存块
lyMemory::memory_list* lyMemory::alloc_chunk(size_t idx)
{
	const size_t node_size = (idx + 1) * align_size;
	//最多分配max_number个或者chunk_limit大小
	size_t chunk_size = MIN(chunk_limit / node_size * node_size,node_size * max_number); 
	memory_list *&current_list = _freelist[idx];
	//有可用内存 则返回
	if(current_list)
		return current_list;
	//没有可用内存，重新分配一块内存，挂在可用内存表后面
	memory_list * ret = current_list = reinterpret_cast<memory_list *>(malloc(chunk_size));
	memory_list * iter = ret;
	//自由内存块大小/指针大小==指针移动距离
	int align =  node_size / sizeof(*iter);
	for (size_t i = 0;i <= chunk_size - node_size * 2;i += node_size)
	{
		iter->_next = iter + align;
		iter = iter->_next;
	}
	iter->_next = 0;

	return ret;
}
//内存分配
void * lyMemory::allocate(size_t size)
{
	size_t idx = chunk_index(size);
	assert(idx < chunk_number);

	memory_list *& tmp = _freelist[idx];
	//内存池还没有分配
	if(!tmp)
	{
		//分配内存池
		memory_list * new_chunk = alloc_chunk(idx);
		chunk_list * chunk_node;
		//内存块占用的信息分配在8byte的内存块列表中
		if(chunk_index(sizeof(chunk_node)) == idx)
		{
			chunk_node = reinterpret_cast<chunk_list *>(tmp);
			//当前节点留给块节点指针
			tmp = tmp->_next;
		}
		else
		{
			chunk_node = reinterpret_cast<chunk_list *>(allocate(sizeof(chunk_list)));
		}

		//把内存块插入到列表开头
		chunk_node->_next = _chunklist;
		chunk_node->_data = new_chunk;
		_chunklist = chunk_node;
	}
	void * ret = tmp;
	tmp = tmp->_next;
	return ret;
}
//内存释放
void lyMemory::deallocate(void * p,size_t size)
{
	size_t idx = chunk_index(size);
	assert(idx < chunk_number);
	memory_list * free_block = reinterpret_cast<memory_list *>(p);
	memory_list *& tmp = _freelist[idx];
	free_block->_next = tmp;
	tmp = free_block;
}
