#include "HashedString.h"

#include <string>

namespace Pool
{
	unsigned int HashedString::Hash(const char* i_string)
	{
		const unsigned int bytes = static_cast<const unsigned int>(strlen(i_string));
		return Hash(reinterpret_cast<void*>(const_cast<char*>(i_string)), bytes);
	}

	unsigned int HashedString::Hash(const void * i_bytes, const unsigned int i_count)
	{
		register const unsigned char * p = static_cast<const unsigned char *>(i_bytes);
		unsigned int hash = 2166136261;

		for (unsigned int i = 0; i < i_count; ++i)
		{
			hash = 16777619 * (hash ^ p[i]);
		}

		return hash ^ (hash >> 16);
	}

	HashedString::HashedString() : m_hash(Hash("")),
#if _DEBUG
		m_string(nullptr)
#endif 
	{

	}

	HashedString::HashedString(const char* i_string) : m_hash(Hash(i_string)),
#if _DEBUG
		m_string(_strdup(i_string))
#endif 
	{

	}

	HashedString::HashedString(const HashedString& i_hash) : m_hash(i_hash.m_hash),
#if _DEBUG
		m_string(_strdup(i_hash.m_string))
#endif 
	{

	}

	HashedString& HashedString::operator=(const HashedString& i_hash)
	{
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
#if _DEBUG
		if (m_string)
		{
			free(m_string);
		}
#endif 
	}
}