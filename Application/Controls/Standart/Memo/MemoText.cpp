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
		CMemo::CMemoText::CMemoText(CMemo *memo) :CBaseText(),
			m_pMemo{ memo }
		{

		}
	#pragma endregion

	#pragma region Notifications
		void CMemo::CMemoText::NotifyOnChange()
		{
			if (m_pMemo)
				m_pMemo->NotifyOnTextChange();
		}
	#pragma endregion

	#pragma region Helpers
		APP_RECT CMemo::CMemoText::ClientToForm(APP_RECT rect)
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

	#pragma region Getters
		CForm *CMemo::CMemoText::getForm()
		{
			if (m_pMemo)
				return m_pMemo->getForm();
			return nullptr;
		}

		bool CMemo::CMemoText::getEnabled()
		{
			if (m_pMemo)
				return m_pMemo->getEnabledWithParents();
			return false;
		}

		bool CMemo::CMemoText::getFocused()
		{
			if (m_pMemo)
				return m_pMemo->getState() == stActive || m_pMemo->getState() == stActiveHovered;
			return false;
		}

		IFont *CMemo::CMemoText::getFont()
		{
			if (m_pMemo)
				return m_pMemo->getFont();
			return nullptr;
		}

		CStyle *CMemo::CMemoText::getStyle()
		{
			if (m_pMemo)
				return m_pMemo->getStyle();
			return nullptr;
		}

		String CMemo::CMemoText::getClassName()
		{
			return L"CText";
		}
	#pragma endregion
	}
}