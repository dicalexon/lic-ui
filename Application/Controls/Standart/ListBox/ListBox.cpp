// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#include "ListBox.h"

namespace licui
{
	namespace application
	{
	#pragma region Constructors
		CListBox::CListBox() : CCustomListBox(),
			m_fOnClickItem{ nullptr },
			m_fOnSelectItem{ nullptr },
			m_fOnDeselectItem{ nullptr },
			m_fOnActivateItem{ nullptr },
			m_fOnDeactivateItem{ nullptr },
			m_fOnHoverItem{ nullptr },
			m_fOnLeaveItem{ nullptr }
		{
			m_sClassName = L"CListBox";
		}

		CListBox::CListBox(CForm *form) : CListBox()
		{
			setForm(form);
		}

		CListBox::CListBox(CControl *parent) : CListBox()
		{
			setParent(parent);
		}

		CListBox::~CListBox()
		{
			DeleteAll();
		}
	#pragma endregion

	#pragma region Getters
		CListBoxItem *CListBox::getItem(const size_t index)
		{
			return dynamic_cast<CListBoxItem*>(CCustomListBox::getItem(index));
		}

		CListBoxItem *CListBox::getActiveItem()
		{
			return dynamic_cast<CListBoxItem*>(CCustomListBox::getActiveItem());
		}

		CListBoxItem *CListBox::getHoveredItem()
		{
			return dynamic_cast<CListBoxItem*>(CCustomListBox::getHoveredItem());
		}
	#pragma endregion

	#pragma region Callback getters
		CListBox::FOnClickItem CListBox::getOnClickItem() const
		{
			return m_fOnClickItem;
		}

		CListBox::FOnSelectItem CListBox::getOnSelectItem() const
		{
			return m_fOnSelectItem;
		}

		CListBox::FOnDeselectItem CListBox::getOnDeselectItem() const
		{
			return m_fOnDeselectItem;
		}

		CListBox::FOnActivateItem CListBox::getOnActivateItem() const
		{
			return m_fOnActivateItem;
		}

		CListBox::FOnDeactivateItem CListBox::getOnDeactivateItem() const
		{
			return m_fOnDeactivateItem;
		}

		CListBox::FOnHoverItem CListBox::getOnHoverItem() const
		{
			return m_fOnHoverItem;
		}

		CListBox::FOnLeaveItem CListBox::getOnLeaveItem() const
		{
			return m_fOnLeaveItem;
		}
	#pragma endregion

	#pragma region Callback setters
		CListBox *CListBox::setOnClickItem(FOnClickItem value)
		{
			m_fOnClickItem = value;
			return this;
		}

		CListBox *CListBox::setOnSelectItem(FOnSelectItem value)
		{
			m_fOnSelectItem = value;
			return this;
		}

		CListBox *CListBox::setOnDeselectItem(FOnDeselectItem value)
		{
			m_fOnDeselectItem = value;
			return this;
		}

		CListBox *CListBox::setOnActivateItem(FOnActivateItem value)
		{
			m_fOnActivateItem = value;
			return this;
		}

		CListBox *CListBox::setOnDeactivateItem(FOnDeactivateItem value)
		{
			m_fOnDeactivateItem = value;
			return this;
		}

		CListBox *CListBox::setOnHoverItem(FOnHoverItem value)
		{
			m_fOnHoverItem = value;
			return this;
		}

		CListBox *CListBox::setOnLeaveItem(FOnLeaveItem value)
		{
			m_fOnLeaveItem = value;
			return this;
		}
	#pragma endregion

	#pragma region Items
		CListBox *CListBox::Add(CListBoxItem *item)
		{
			if (item)
			{
				item->m_pListBox = this;
				CCustomListBox::Add(item);
			}
			return this;
		}

		CListBox *CListBox::Insert(const size_t before, CListBoxItem *item)
		{
			if (item)
			{
				item->m_pListBox = this;
				CCustomListBox::Insert(before, item);
			}
			return this;
		}
	#pragma endregion

	#pragma region Helpers
		void CListBox::ProcessSearch()
		{
			if (!m_sSearchChars.empty())
			{
				String search{ ToLower(m_sSearchChars) };
				for (size_t i = 0; i < getItemCount(); i++)
					if (ToLower(getItem(i)->getCaption()).find(search) != String::npos)
					{
						m_iActiveItemIndex = i;
						DeselectAllInternal();
						getActiveItem()->setSelectedInternal(true);
						ScrollToItem(m_iActiveItemIndex);
						Repaint(false);
						break;
					}
			}
		}
	#pragma endregion

	#pragma region Notifications
		void CListBox::NotifyOnClickItem(CListBoxItem *item)
		{
			if (m_fOnClickItem)
				m_fOnClickItem(item, getCallbackParam());
		}

		void CListBox::NotifyOnSelectItem(CListBoxItem *item)
		{
			if (m_fOnSelectItem)
				m_fOnSelectItem(item, getCallbackParam());
		}

		void CListBox::NotifyOnDeselectItem(CListBoxItem *item)
		{
			if (m_fOnDeselectItem)
				m_fOnDeselectItem(item, getCallbackParam());
		}

		void CListBox::NotifyOnActivateItem(CListBoxItem *item)
		{
			if (m_fOnActivateItem)
				m_fOnActivateItem(item, getCallbackParam());
		}

		void CListBox::NotifyOnDeactivateItem(CListBoxItem *item)
		{
			if (m_fOnDeactivateItem)
				m_fOnDeactivateItem(item, getCallbackParam());
		}

		void CListBox::NotifyOnHoverItem(CListBoxItem *item)
		{
			if (m_fOnHoverItem)
				m_fOnHoverItem(item, getCallbackParam());
		}

		void CListBox::NotifyOnLeaveItem(CListBoxItem *item)
		{
			if (m_fOnLeaveItem)
				m_fOnLeaveItem(item, getCallbackParam());
		}
	#pragma endregion
	}
}