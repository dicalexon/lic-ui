// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#include "ListBox.h"
#include "..\..\..\Form.h"
#include "..\..\..\Presenter.h"
#include "..\..\..\Style.h"

namespace licui
{
	namespace application
	{
	#pragma region Constructor
		CListBoxItem::CListBoxItem():
			m_pListBox{ nullptr },
			m_bSelected{ false },
			m_sPadding{ 1, 1, 1, 1 },
			m_iBorderWidth{ 1 }
		{
			m_aBorderColor[stNormal] = { 0, 0, 0, 0 };
			m_aBorderColor[stNormalHovered] = { 245, 245, 245, 255 };
			m_aBorderColor[stActive] = { 100, 100, 100, 255 };
			m_aBorderColor[stActiveHovered] = { 100, 100, 100, 255 };
			m_aBorderColor[stActiveSelected] = { 100, 100, 100, 255 };
			m_aBorderColor[stActiveSelectedHovered] = { 100, 100, 100, 255 };
			m_aBorderColor[stSelected] = { 51, 153, 235, 255 };
			m_aBorderColor[stSelectedHovered] = { 51, 153, 235, 255 };
			m_aBorderColor[stDisabled] = { 0, 0, 0, 0 };
		
			m_aBackgroundColor[stNormal] = { 0, 0, 0, 0 };
			m_aBackgroundColor[stNormalHovered] = { 245, 245, 245, 255 };
			m_aBackgroundColor[stActive] = { 0, 0, 0, 0 };
			m_aBackgroundColor[stActiveHovered] = { 245, 245, 245, 255 };
			m_aBackgroundColor[stActiveSelected] = { 51, 153, 235, 255 };
			m_aBackgroundColor[stActiveSelectedHovered] = { 51, 153, 235, 255 };
			m_aBackgroundColor[stSelected] = { 51, 153, 235, 255 };
			m_aBackgroundColor[stSelectedHovered] = { 51, 153, 235, 255 };
			m_aBackgroundColor[stDisabled] = { 0, 0, 0, 0 };

			m_aTextColor[stNormal] = { 0, 0, 0, 255 };
			m_aTextColor[stNormalHovered] = { 0, 0, 0, 255 };
			m_aTextColor[stActive] = { 0, 0, 0, 255 };
			m_aTextColor[stActiveHovered] = { 0, 0, 0, 255 };
			m_aTextColor[stActiveSelected] = { 255, 255, 255, 255 };
			m_aTextColor[stActiveSelectedHovered] = { 255, 255, 255, 255 };
			m_aTextColor[stSelected] = { 255, 255, 255, 255 };
			m_aTextColor[stSelectedHovered] = { 255, 255, 255, 255 };
			m_aTextColor[stDisabled] = { 131, 131, 131, 255 };

			m_aShadowColor[stNormal] = { 0, 0, 0, 255 };
			m_aShadowColor[stNormalHovered] = { 0, 0, 0, 255 };
			m_aShadowColor[stActive] = { 0, 0, 0, 255 };
			m_aShadowColor[stActiveHovered] = { 0, 0, 0, 255 };
			m_aShadowColor[stActiveSelected] = { 255, 255, 255, 255 };
			m_aShadowColor[stActiveSelectedHovered] = { 255, 255, 255, 255 };
			m_aShadowColor[stSelected] = { 255, 255, 255, 255 };
			m_aShadowColor[stSelectedHovered] = { 255, 255, 255, 255 };
			m_aShadowColor[stDisabled] = { 131, 131, 131, 255 };
		}
	#pragma endregion

	#pragma region Getters
		bool CListBoxItem::getSelectedInternal() const
		{
			return m_bSelected;
		}

		CListBoxItem::STATE CListBoxItem::getState() const
		{
			if (m_pListBox)
			{
				if (!m_pListBox->getEnabled())
					return stDisabled;
				if (m_pListBox->getActiveItem() == this)
				{
					if (m_pListBox->getHoveredItem() == this)
					{
						if (m_bSelected)
							return stActiveSelectedHovered;
						return stActiveHovered;
					}
					if (m_bSelected)
						return stActiveSelected;
					return stActive;
				}
				if (m_pListBox->getHoveredItem() == this)
				{
					if (m_bSelected)
						return stSelectedHovered;
					return stNormalHovered;
				}
				if (m_bSelected)
					return stSelected;
				return stNormal;
			}
			if (m_bSelected)
				return stSelected;
			return stNormal;
		}

		String CListBoxItem::getCaption() const
		{
			return m_sCaption;
		}

		bool CListBoxItem::getSelected() const
		{
			return getSelectedInternal();
		}

		math::RECTANGLE<size_t> CListBoxItem::getPadding() const
		{
			return m_sPadding;
		}

		size_t CListBoxItem::getPaddingLeft() const
		{
			return m_sPadding.Left;
		}

		size_t CListBoxItem::getPaddingTop() const
		{
			return m_sPadding.Top;
		}

		size_t CListBoxItem::getPaddingRight() const
		{
			return m_sPadding.Right;
		}

		size_t CListBoxItem::getPaddingBottom() const
		{
			return m_sPadding.Bottom;
		}

		size_t CListBoxItem::getBorderWidth() const
		{
			return m_iBorderWidth;
		}

		APP_COLOR CListBoxItem::getBorderColor(const STATE state) const
		{
			return m_aBorderColor[state];
		}

		APP_COLOR CListBoxItem::getBackgroundColor(const STATE state) const
		{
			return m_aBackgroundColor[state];
		}

		APP_COLOR CListBoxItem::getTextColor(const STATE state) const
		{
			return m_aTextColor[state];
		}

		APP_COLOR CListBoxItem::getShadowColor(const STATE state) const
		{
			return m_aShadowColor[state];
		}
	#pragma endregion

	#pragma region Setters
		bool CListBoxItem::setSelectedInternal(const bool value)
		{
			if (value == m_bSelected)
				return false;
			m_bSelected = value;
			if (m_bSelected)
				NotifyOnSelect();
			else
				NotifyOnDeselect();
			return true;
		}

		CListBoxItem *CListBoxItem::setCaption(const String &value)
		{
			if (value != m_sCaption)
			{
				m_sCaption = value;
				if (m_pListBox)
					m_pListBox->Update();
			}
			return this;
		}

		CListBoxItem *CListBoxItem::setSelected(const bool value)
		{
			if (value != m_bSelected)
			{
				if (value && m_pListBox && !m_pListBox->m_bAllowMultiSelect)
					m_pListBox->DeselectAll();
				m_bSelected = value;
				if (m_pListBox)
					m_pListBox->Repaint(false);
			}
			return this;
		}

		CListBoxItem *CListBoxItem::setPadding(const math::RECTANGLE<size_t> &value)
		{
			if (value != m_sPadding)
			{
				m_sPadding = value;
				if (m_pListBox)
					m_pListBox->Update();
			}
			return this;
		}

		CListBoxItem *CListBoxItem::setPaddingLeft(const size_t value)
		{
			return setPadding({ value, m_sPadding.Top, m_sPadding.Right, m_sPadding.Bottom });
		}

		CListBoxItem *CListBoxItem::setPaddingTop(const size_t value)
		{
			return setPadding({ m_sPadding.Left, value, m_sPadding.Right, m_sPadding.Bottom });
		}

		CListBoxItem *CListBoxItem::setPaddingRight(const size_t value)
		{
			return setPadding({ m_sPadding.Left, m_sPadding.Top, value, m_sPadding.Bottom });
		}

		CListBoxItem *CListBoxItem::setPaddingBottom(const size_t value)
		{
			return setPadding({ m_sPadding.Left, m_sPadding.Top, m_sPadding.Right, value });
		}

		CListBoxItem *CListBoxItem::setBorderWidth(const size_t value)
		{
			if (value != m_iBorderWidth)
			{
				m_iBorderWidth = value;
				if (m_pListBox)
					m_pListBox->Update();
			}
			return this;
		}

		CListBoxItem *CListBoxItem::setBorderColor(const STATE state, const APP_COLOR &value)
		{
			if (value != m_aBorderColor[state])
			{
				m_aBorderColor[state] = value;
				if (m_pListBox && getState() == state)
					m_pListBox->Repaint(false);
			}
			return this;
		}

		CListBoxItem *CListBoxItem::setBackgroundColor(const STATE state, const APP_COLOR &value)
		{
			if (value != m_aBackgroundColor[state])
			{
				m_aBackgroundColor[state] = value;
				if (m_pListBox && getState() == state)
					m_pListBox->Update();
			}
			return this;
		}

		CListBoxItem *CListBoxItem::setTextColor(const STATE state, const APP_COLOR &value)
		{
			if (value != m_aTextColor[state])
			{
				m_aTextColor[state] = value;
				if (m_pListBox && getState() == state)
					m_pListBox->Update();
			}
			return this;
		}

		CListBoxItem *CListBoxItem::setShadowColor(const STATE state, const APP_COLOR &value)
		{
			if (value != m_aShadowColor[state])
			{
				m_aShadowColor[state] = value;
				if (m_pListBox && getState() == state)
					m_pListBox->Update();
			}
			return this;
		}
	#pragma endregion

	#pragma region Helpers
		math::POINT<size_t> CListBoxItem::CalculateSize()
		{
			APP_POINT size = m_pListBox->getFont()->getStringSize(m_sCaption);
			return{ (size_t)size.X + m_sPadding.Left + m_sPadding.Right + 2 * m_iBorderWidth, (size_t)size.Y + m_sPadding.Top + m_sPadding.Bottom + 2 * m_iBorderWidth };
		}

		void CListBoxItem::UpdateFromStyle()
		{
			if (m_pListBox && m_pListBox->getStyle())
			{
				m_sPadding = m_pListBox->getStyle()->getParameterByName(m_pListBox->m_sClassName + L".Item.Padding", m_sPadding);
				m_iBorderWidth = m_pListBox->getStyle()->getParameterByName(m_pListBox->m_sClassName + L".Item.BorderWidth", m_iBorderWidth);
				for (int i = 0; i <= stDisabled; i++)
				{
					String name;
					switch (i)
					{
					case stNormal:
						name = L".normal";
						break;
					case stNormalHovered:
						name = L".normal.hovered";
						break;
					case stActive:
						name = L".active";
						break;
					case stActiveHovered:
						name = L".active.hovered";
						break;
					case stActiveSelected:
						name = L".active.selected";
						break;
					case stActiveSelectedHovered:
						name = L".active.selected.hovered";
						break;
					case stSelected:
						name = L".selected";
						break;
					case stSelectedHovered:
						name = L".selected.hovered";
						break;
					default:
						name = L".disabled";
						break;
					}
					m_aBorderColor[i] = m_pListBox->getStyle()->getParameterByName(m_pListBox->m_sClassName + L".Item.BorderColor" + name, m_aBorderColor[i]);
					m_aBackgroundColor[i] = m_pListBox->getStyle()->getParameterByName(m_pListBox->m_sClassName + L".Item.BackgroundColor" + name, m_aBackgroundColor[i]);
					m_aTextColor[i] = m_pListBox->getStyle()->getParameterByName(m_pListBox->m_sClassName + L".Item.TextColor" + name, m_aTextColor[i]);
					m_aShadowColor[i] = m_pListBox->getStyle()->getParameterByName(m_pListBox->m_sClassName + L".Item.ShadowColor" + name, m_aShadowColor[i]);
				}
			}
		}
	#pragma endregion

	#pragma region Notifications
		void CListBoxItem::NotifyOnClick()
		{
			if (m_pListBox)
				m_pListBox->NotifyOnClickItem(this);
		}

		void CListBoxItem::NotifyOnSelect()
		{
			if (m_pListBox)
				m_pListBox->NotifyOnSelectItem(this);
		}

		void CListBoxItem::NotifyOnDeselect()
		{
			if (m_pListBox)
				m_pListBox->NotifyOnDeselectItem(this);
		}

		void CListBoxItem::NotifyOnActivate()
		{
			if (m_pListBox)
				m_pListBox->NotifyOnActivateItem(this);
		}

		void CListBoxItem::NotifyOnDeactivate()
		{
			if (m_pListBox)
				m_pListBox->NotifyOnDeactivateItem(this);
		}

		void CListBoxItem::NotifyOnHover()
		{
			if (m_pListBox)
				m_pListBox->NotifyOnHoverItem(this);
		}

		void CListBoxItem::NotifyOnLeave()
		{
			if (m_pListBox)
				m_pListBox->NotifyOnLeaveItem(this);
		}
	#pragma endregion

	#pragma region Paint
		void CListBoxItem::Paint(APP_RECT clip, APP_RECT rect)
		{
			STATE state{ getState() };
			// Background
			if (m_aBackgroundColor[state].getAlpha() > 0 || (m_iBorderWidth > 0 && m_aBorderColor[state].getAlpha() > 0))
			{
				math::RECTANGLE<size_t> borders{ m_iBorderWidth, m_iBorderWidth, m_iBorderWidth, m_iBorderWidth };
				APP_COLOR colors[graphics::bplBottom + 1];
				colors[graphics::bplInside] = m_aBackgroundColor[state];
				colors[graphics::bplLeft] = m_aBorderColor[state];
				colors[graphics::bplTop] = m_aBorderColor[state];
				colors[graphics::bplRight] = m_aBorderColor[state];
				colors[graphics::bplBottom] = m_aBorderColor[state];
				m_pListBox->m_pForm->getPresenter()->MultiFillRect(colors, clip, rect, borders, { 0, 0, 0, 0 }, 0, nullptr, nullptr, true);
			}
			// Text
			if (!m_sCaption.empty())
			{
				rect.Left += (int)m_iBorderWidth + (int)m_sPadding.Left;
				rect.Top += (int)m_iBorderWidth + (int)m_sPadding.Top;
				rect.Right -= (int)m_iBorderWidth + (int)m_sPadding.Right;
				rect.Bottom -= (int)m_iBorderWidth + (int)m_sPadding.Bottom;
				if (rect.IsValid() && !rect.IsEmpty())
				{
					APP_POINT size = m_pListBox->getFont()->getStringSize(m_sCaption);
					int y{ rect.Top + (rect.Height() - size.Y) / 2 };
					m_pListBox->m_pForm->getPresenter()->RenderString(m_sCaption, m_pListBox->getFont(), rect.Left, y, 0, 1, 1, clip * rect, 0, rect, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, 0,
						graphics::bplInside, true, true, m_aTextColor[state], m_aShadowColor[state], nullptr, nullptr, true);
				}
			}
		}
	#pragma endregion
	}
}