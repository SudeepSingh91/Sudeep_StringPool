#include "Pool.h"

#include <new>
#include <stdint.h>
#include <string>

#include "../DebugInfo/DebugInfo.h"
#include "../HashedString/HashedString.h"

namespace Pool
{
	Pool* Pool::Create(void* i_memoryAddr, size_t i_size)
	{
		assert(i_memoryAddr != nullptr);
		assert(i_size > sizeof(Pool));
		
		void* poolMem = i_memoryAddr;
		i_memoryAddr = static_cast<uint8_t*>(i_memoryAddr) + sizeof(Pool);
		i_size -= sizeof(Pool);

		Pool* m_pool = new (poolMem) Pool(i_size, i_memoryAddr);
		return m_pool;
	}

	void Pool::Destroy()
	{
		void* memoryToFree = static_cast<uint8_t*>(m_poolBase) - sizeof(Pool);
		this->~Pool();
		_aligned_free(memoryToFree);
	}

	Pool::Pool(const size_t i_size, void* const i_pool) : m_totalSize(i_size), m_availSize(i_size), m_poolBase(i_pool)
	{

	}

	Pool::~Pool()
	{

	}

	const char* Pool::Add(const char* i_string)
	{
		assert(i_string != nullptr);
		
		const char* memAddr = Find(i_string);
		if (memAddr == nullptr)
		{
			size_t length = strlen(i_string);
			if (m_availSize < (sizeof(size_t) + length))
			{
				return nullptr;
			}
			else
			{
				size_t offset = m_totalSize - m_availSize;
				size_t* size = reinterpret_cast<size_t*>(static_cast<uint8_t*>(m_poolBase) + offset);
				*size = length;
				char* str = reinterpret_cast<char*>(static_cast<uint8_t*>(m_poolBase) + offset + sizeof(size_t));
				memcpy(str, i_string, length);
				m_availSize = m_availSize - sizeof(size_t) - length;
				return str;
			}
		}
		else
		{
			return memAddr;
		}
	}

	const char* Pool::Find(const char* i_string)
	{
		assert(i_string != nullptr);
		
		uint8_t* iterPool = static_cast<uint8_t*>(m_poolBase);
		uint8_t* endMemAddr = iterPool + m_totalSize - m_availSize;
		HashedString hash(i_string);
		size_t length = strlen(i_string);

		while (iterPool < endMemAddr)
		{
			size_t stringSize = *reinterpret_cast<size_t*>(iterPool);
			if (stringSize == length)
			{
				char* string = reinterpret_cast<char*>(iterPool + sizeof(size_t));
				HashedString tempHash(string);
				if (hash.Get() == tempHash.Get())
				{
					return string;
				}
			}

			iterPool = iterPool + sizeof(size_t) + stringSize;
		}

		return nullptr;
	}
}