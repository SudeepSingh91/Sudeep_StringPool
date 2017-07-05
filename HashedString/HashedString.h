#ifndef HASHEDSTRING_H
#define HASHEDSTRING_H

namespace Pool
{
	class HashedString
	{
	public:
		HashedString();
		HashedString(const char* i_string);
		HashedString(const HashedString& i_hash);
		HashedString& operator=(const HashedString& i_hash);

		~HashedString();

		static unsigned int Hash(const char* i_string);
		static unsigned int Hash(const void * i_bytes, const unsigned int i_count);
		
		inline unsigned int Get() const;
		inline bool operator==(const HashedString & i_hash) const;

	private:
		unsigned int m_hash;

#if _DEBUG
		char* m_string;
#endif
	};
}

#include "HashedString-inl.h"

#endif