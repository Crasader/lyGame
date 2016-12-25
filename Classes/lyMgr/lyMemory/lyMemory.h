#pragma once


#define MIN(a,b) ((a) < (b) ? (a) : (b))

class lyMemory
{
public:
    lyMemory();
    ~lyMemory();
    static lyMemory * GetInstance()
    {
        static lyMemory sInstance;
        return &sInstance;
    }
    
    void * allocate(size_t size);
    void deallocate(void * p,size_t size);
    enum
	{
		chunk_limit = 16384,							//16K
		max_number = 64,								
		align_size = 8,
		chunk_number = chunk_limit/align_size,			//2K
	};
private:
	struct memory_list{
		memory_list * _next;
	};
	struct chunk_list{
		chunk_list * _next;
		memory_list * _data;
	};

	memory_list * _freelist[chunk_number];
	chunk_list * _chunklist;

	size_t chunk_index(size_t bytes);
	memory_list * alloc_chunk(size_t idx);

};


struct lyMemoryAlloc
{
	static void * operator new(size_t size)
	{
		return lyMemory::GetInstance()->allocate(size);
	}
	static void operator delete(void * p,size_t size)
	{
		lyMemory::GetInstance()->deallocate(p,size);
	}
};

