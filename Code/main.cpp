#include "Pool\Pool.h"

#if _DEBUG
#include <crtdbg.h>
#endif

#include <stdio.h>
#include <malloc.h>

void main()
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
	
	const size_t poolSize = 100;
	const int cacheAlignment = 4;
	
	void* memBlock = _aligned_malloc(poolSize, cacheAlignment);
	Pool::Pool* stringPool = Pool::Pool::Create(memBlock, poolSize);
	
	const char* ryu = stringPool->Add("Ryu");
	const char* ken = stringPool->Add("Ken");
	const char* chunLi = stringPool->Add("Chun Li");
	const char* kenAgain = stringPool->Add("Ken");

	const char* getChunLi = stringPool->Find("Chun Li");
	const char* getBlanka = stringPool->Find("Blanka");

	stringPool->Destroy();
}