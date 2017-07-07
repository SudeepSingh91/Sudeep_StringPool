#ifndef POOL_H
#define POOL_H

namespace Pool
{
	class Pool
	{
	public:
		static Pool* Create(void* i_memoryAddr, size_t i_size);
		void Destroy();

		inline void* GetPool();

		const char* Add(const char* i_string);
		const char* Find(const char* i_string);

	private:
		Pool(const size_t i_size, void* const i_pool);
		Pool(const Pool& i_pool);
		Pool& operator=(const Pool& i_pool);

		~Pool();

		const size_t m_totalSize;
		size_t m_availSize;
		void* const m_poolBase;
	};
}

#include "Pool-inl.h"

#endif 