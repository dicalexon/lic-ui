// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#include "Memo.h"

namespace licui
{
	namespace application
	{
	#pragma region Constructor
		CMemo::CMemoScrollBar::CMemoScrollBar(CMemo *memo, const TYPE type) :CBaseScrollBar(),
			m_pMemo{ memo }
		{
			m_bVisible = false;
			setType(type);
		}
	#pragma endregion

	#pragma region Getters
		String CMemo::CMemoScrollBar::getClassName() const
		{
			return L"CScrollBar";
		}

		CStyle *CMemo::CMemoScrollBar::getStyle()
		{
			if (m_pMemo)
				return m_pMemo->getStyle();
			return nullptr;
		}

		CForm *CMemo::CMemoScrollBar::getForm()
		{
			if (m_pMemo)
				return m_pMemo->getForm();
			return nullptr;
		}
	#pragma endregion

	#pragma region Notifications
		void CMemo::CMemoScrollBar::NotifyOnChange()
		{
			if (m_pMemo)
				m_pMemo->NotifyOnScrollBarChange(this);
		}
	#pragma endregion

	#pragma region Helpers
		APP_RECT CMemo::CMemoScrollBar::ClientToForm(APP_RECT rect)
		{
			if (m_pMemo)
			{
				rect.Left += m_pMemo->getLeft();
				rect.Right += m_pMemo->getLeft();
				rect.Top += m_pMemo->getTop();
				rect.Bottom += m_pMemo->getTop();
				return m_pMemo->ClientToForm(rect);
			}
			return rect;
		}
	#pragma endregion
	}
}