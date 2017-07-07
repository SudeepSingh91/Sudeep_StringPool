#include "HashedString.h"

#include <string>

#include "../DebugInfo/DebugInfo.h"

namespace Pool
{
	unsigned int HashedString::Hash(const char* i_string)
	{
		assert(i_string != nullptr);
		
		DEBUG_PRINT("Creating hash of string %s", i_string);

		const unsigned int bytes = static_cast<const unsigned int>(strlen(i_string));
		return Hash(reinterpret_cast<void*>(const_cast<char*>(i_string)), bytes);
	}

	unsigned int HashedString::Hash(const void * i_bytes, const unsigned int i_count)
	{
		assert(i_bytes != nullptr);
		
		register const unsigned char * p = static_cast<const unsigned char *>(i_bytes);
		unsigned int hash = 2166136261;

		for (unsigned int i = 0; i < i_count; ++i)
		{
			hash = 16777619 * (hash ^ p[i]);
		}

		DEBUG_PRINT("Created hash %u", hash);

		return hash ^ (hash >> 16);
	}

	HashedString::HashedString() : m_hash(Hash("")),
#if _DEBUG
		m_string(nullptr)
#endif 
	{
		DEBUG_PRINT("Called default constructor of Hashed String");
	}

	HashedString::HashedString(const char* i_string) : m_hash(Hash(i_string)),
#if _DEBUG
		m_string(_strdup(i_string))
#endif 
	{
		DEBUG_PRINT("Called overloaded constructor of Hashed String");
	}

	HashedString::HashedString(const HashedString& i_hash) : m_hash(i_hash.m_hash),
#if _DEBUG
		m_string(_strdup(i_hash.m_string))
#endif 
	{
		DEBUG_PRINT("Called copy constructor of Hashed String");
	}

	HashedString& HashedString::operator=(const HashedString& i_hash)
	{
		DEBUG_PRINT("Called assignment operator of Hashed String");
		
		if (this != &i_hash)
		{
			m_hash = i_hash.m_hash;
#if _DEBUG
			if (m_string)
			{
				free(m_string);
			}

			m_string = i_hash.m_string;
#endif 
		}

		return *this;
	}

	HashedString::~HashedString()
	{
		DEBUG_PRINT("Called destructor of Hashed String");

#if _DEBUG
		if (m_string)
		{
			free(m_string);
		}
#endif 
	}
}