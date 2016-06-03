// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#include "ImageList.h"
#include "..\..\Form.h"

namespace licui
{
	namespace application
	{
		CImageList::CImageList() :CComponent()
		{
			m_sClassName = L"CImageList";
		}

		CImageList::CImageList(CForm *form) : CImageList()
		{
			setForm(form);
		}

		size_t CImageList::getCount() const
		{
			return m_aImages.size();
		}

		APP_IMAGE *CImageList::getImage(const size_t index)
		{
			if (index < m_aImages.size())
				return &m_aImages[index];
			return nullptr;
		}

		APP_IMAGE *CImageList::Add()
		{
			m_aImages.push_back(APP_IMAGE());
			return &m_aImages[m_aImages.size() - 1];
		}

		void CImageList::Delete(const size_t index)
		{
			if (index < m_aImages.size())
			{
				auto pos = m_aImages.begin();
				m_aImages.erase(pos + index);
			}
		}

		void CImageList::Clear()
		{
			m_aImages.clear();
		}

		void CImageList::Update()
		{
			NotifyOnUpdate();
		}
	}
}