namespace Pool
{
	inline unsigned int HashedString::Get() const
	{
		return m_hash;
	}

	inline bool HashedString::operator==(const HashedString & i_hashString) const
	{
		return m_hash == i_hashString.m_hash;
	}
}