#include "CppUnitTest.h"
#include "stdafx.h"

#include "../../src/Scratch Engine/Scratch Engine/Core/Memory/Pool.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace ScratchEngine::Memory;

namespace ScratchEngineTest
{
	TEST_CLASS(PoolTest)
	{
	public:
		TEST_METHOD(Constructor)
		{
			Pool pool(1024);

			Assert::AreEqual((size_t)1024, pool.capacity);
			Assert::AreEqual((size_t)0, pool.size);
			Assert::AreEqual((u32)1, pool.numBlocks);
			Assert::AreEqual((u32)0, pool.numAllocated);
			Assert::AreEqual((uptr)pool.memory, (uptr)pool.root);
		}

		TEST_METHOD(Allocate1)
		{
			Pool pool(1024);

			void* p = pool.Allocate(512);

			Assert::AreEqual((size_t)1024, pool.capacity);
			Assert::AreEqual(__data_offset + 512 + __block_tail_size, pool.size);
			Assert::AreEqual((u32)2, pool.numBlocks);
			Assert::AreEqual((u32)1, pool.numAllocated);
			Assert::AreEqual((uptr)pool.memory + pool.size, (uptr)pool.root);
			
			Assert::AreEqual((uptr)pool.memory + __data_offset, (uptr)p, L"The returned pointer was incorrect");
			Assert::AreEqual((size_t)512, (uptr)pool.memory + pool.size - (uptr)p - __block_tail_size, L"Incorrect amount of memory was allocated");
		}

		TEST_METHOD(Free)
		{
			Pool pool(1024);

			void* p = pool.Allocate(512);

			pool.Free(p);

			Assert::AreEqual((size_t)1024, pool.capacity);
			Assert::AreEqual((size_t)0, pool.size);
			Assert::AreEqual((u32)1, pool.numBlocks);
			Assert::AreEqual((u32)0, pool.numAllocated);
		}
	};
}
