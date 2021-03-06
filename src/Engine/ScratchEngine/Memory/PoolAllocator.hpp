#pragma once

#include <queue>

#include "../Common/Typedefs.h"

#include "Allocator.h"

namespace ScratchEngine
{
	namespace Memory
	{
		struct PoolBlock				// 16 bytes
		{
			PoolBlock* next;			// 8 bytes
			PoolBlock* previous;		// 8 bytes
		};

		template<size_t BLOCKSIZE> class __declspec(dllexport) PoolAllocator : StaticAllocator
		{
		private:
			void* memory;

			size_t numAllocated;
			size_t capcity;
			size_t count;

			PoolBlock* freeList;


		public:
			PoolAllocator(size_t capacity);
			~PoolAllocator();


			void* Allocate(size_t numAllocated = BLOCKSIZE);

			void Free(void* p);
		};

		template<size_t BLOCKSIZE> inline PoolAllocator<BLOCKSIZE>::PoolAllocator(size_t capacity)
		{
			_ASSERT(BLOCKSIZE >= sizeof(PoolBlock));

			register size_t numAllocated = BLOCKSIZE * capacity;

			this->numAllocated = numAllocated;
			this->capcity = capacity;
			this->count = 0;

			memory = _aligned_malloc(numAllocated, 16);

			freeList = reinterpret_cast<PoolBlock*>(memory);
			freeList->previous = nullptr;

			register PoolBlock* a = freeList;
			register PoolBlock* b = reinterpret_cast<PoolBlock*>(reinterpret_cast<uptr>(a) + BLOCKSIZE);
			freeList = a;

			for (size_t i = 1; i < capacity; i++)
			{
				a->next = b;
				b->previous = a;

				a = b;
				b = reinterpret_cast<PoolBlock*>(reinterpret_cast<uptr>(b) + BLOCKSIZE);
			}

			b->next = nullptr;
		}

		template<size_t BLOCKSIZE> inline PoolAllocator<BLOCKSIZE>::~PoolAllocator()
		{
			_aligned_free(memory);
		}

		template<size_t BLOCKSIZE> inline void * PoolAllocator<BLOCKSIZE>::Allocate(size_t numAllocated)
		{
			void* p = freeList;

			freeList = freeList->next;

			return p;
		}

		template<size_t BLOCKSIZE> inline void PoolAllocator<BLOCKSIZE>::Free(void * p)
		{
			register PoolBlock* b = reinterpret_cast<PoolBlock*>(p);
			b->next = freeList;
			b->previous = nullptr;

			if (freeList)
			{
				freeList->previous = b;
			}

			freeList = b;
		}
	}
}
