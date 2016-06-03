// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#pragma once

#include <vector>

namespace licui
{
	namespace application
	{
		template<class Type>
		class CHistory
		{
		private:
			struct ITEM
			{
				Type Data;
				size_t Size;
			};

			std::vector<ITEM> m_aItems;
			size_t m_iLimitCount;
			size_t m_iLimitSize;
			size_t m_iPosition;

			void ApplyLimits();
		public:
			size_t getCount() const;
			Type getItem(const size_t index);
			size_t getLimitCount() const;
			size_t getLimitSize() const;
			size_t getPosition() const;

			CHistory<Type> *setLimitCount(const size_t value);
			CHistory<Type> *setLimitSize(const size_t value);
			CHistory<Type> *setPosition(size_t value);

			CHistory();

			void Store(const Type item, const size_t size);
			void Clear();
		};

#pragma region Implementation
		template<class Type> CHistory<Type>::CHistory() :
			m_iLimitCount{ 0 },
			m_iLimitSize{ 0 }
		{

		}

		template<class Type> size_t CHistory<Type>::getCount() const
		{
			return m_aItems.size();
		}

		template<class Type> Type CHistory<Type>::getItem(const size_t index)
		{
			return m_aItems[index].Data;
		}

		template<class Type> size_t CHistory<Type>::getLimitCount() const
		{
			return m_iLimitCount;
		}

		template<class Type> size_t CHistory<Type>::getLimitSize() const
		{
			return m_iLimitSize;
		}

		template<class Type> size_t CHistory<Type>::getPosition() const
		{
			return m_iPosition;
		}

		template<class Type> CHistory<Type> *CHistory<Type>::setLimitCount(const size_t value)
		{
			if (value != m_iLimitCount)
			{
				m_iLimitCount = value;
				ApplyLimits();
			}
			return this;
		}

		template<class Type> CHistory<Type> *CHistory<Type>::setLimitSize(const size_t value)
		{
			if (value != m_iLimitSize)
			{
				m_iLimitSize = value;
				ApplyLimits();
			}
			return this;
		}

		template<class Type> CHistory<Type> *CHistory<Type>::setPosition(size_t value)
		{
			if (m_aItems.size() == 0)
				value = 0;
			else if (value >= m_aItems.size())
				value = m_aItems.size() - 1;
			if (value != m_iPosition)
				m_iPosition = value;
			return this;
		}

		template<class Type> void CHistory<Type>::Store(const Type item, const size_t size)
		{
			if (m_iLimitCount > 1)
			{
				if (m_aItems.size() > 0 && m_iPosition < m_aItems.size() - 1)
				{
					auto pos = m_aItems.begin();
					m_aItems.erase(pos + m_iPosition + 1, m_aItems.end());
				}
				if (m_iLimitSize == 0 || size < m_iLimitSize)
				{
					m_aItems.push_back({ item, size });
					m_iPosition = m_aItems.size() - 1;
					ApplyLimits();
				}
			}
		}

		template<class Type> void CHistory<Type>::ApplyLimits()
		{
			if (m_aItems.size() == 0)
				return;
			if (m_iLimitCount > 0 && m_aItems.size() > m_iLimitCount)
			{
				while (m_aItems.size() > m_iLimitCount && m_iPosition < m_aItems.size() - 1)
				{
					auto pos = m_aItems.end();
					pos--;
					m_aItems.erase(pos);
				}
				while (m_aItems.size() > m_iLimitCount && m_iPosition > 0)
				{
					m_aItems.erase(m_aItems.begin());
					m_iPosition--;
				}
			}
			if (m_iLimitSize > 0)
			{
				size_t size{ 0 };
				for (auto pos = m_aItems.begin(); pos != m_aItems.end(); pos++)
					size += (*pos).Size;
				while (size > m_iLimitSize && m_iPosition < m_aItems.size() - 1)
				{
					size -= m_aItems[m_aItems.size() - 1].Size;
					auto pos = m_aItems.end();
					pos--;
					m_aItems.erase(pos);
				}
				while (size > m_iLimitSize && m_iPosition > 0)
				{
					size -= m_aItems[0].Size;
					m_aItems.erase(m_aItems.begin());
					m_iPosition--;
				}
			}
		}

		template<class Type> void CHistory<Type>::Clear()
		{
			m_aItems.clear();
			m_iPosition = 0;
		}
#pragma endregion
	}
}