// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#include "ListBox.h"
#include "..\..\..\..\Utils\Utils.h"
#include "..\..\..\Form.h"
#include "..\..\..\Presenter.h"
#include "..\..\..\Style.h"

namespace licui
{
	namespace application
	{
		const unsigned int SCROLL_TIMER_INTERVAL{ 250 };

	#pragma region CListBoxScrollBar
		CCustomListBox::CListBoxScrollBar::CListBoxScrollBar(CCustomListBox *parent) :CScrollBar()
		{
			m_bVisible = false;
			m_bEnabled = false;
			m_bAcceptForm = false;
			
			for (int i = 0; i <= stDisabled; i++)
			{
				setBorderColor((STATE)i, { 227, 227, 227, 255 });
				setBoxShadowColor((STATE)i, { 248, 248, 248, 255 });
				setGradientPointColor((STATE)i, 0, { 229, 229, 229, 255 });
				setGradientPointColor((STATE)i, 1, { 237, 237, 237, 255 });
				setGradientPointColor((STATE)i, 2, { 240, 240, 240, 255 });
			}

			setParent(parent);
		}

		void CCustomListBox::CListBoxScrollBar::NotifyOnScroll()
		{
			(dynamic_cast<CCustomListBox*>(getParent()))->NotifyOnScroll(this);
			CScrollBar::NotifyOnScroll();
		}

		void CCustomListBox::CListBoxScrollBar::NotifyOnMouseHover()
		{
			CScrollBar::NotifyOnMouseHover();
			(dynamic_cast<CCustomListBox*>(getParent()))->Repaint(false);
		}

		void CCustomListBox::CListBoxScrollBar::NotifyOnMouseLeave()
		{
			CScrollBar::NotifyOnMouseLeave();
			(dynamic_cast<CCustomListBox*>(getParent()))->Repaint(false);
		}
	#pragma endregion

	#pragma region Constructors
		CCustomListBox::CCustomListBox() : CControl(),
			m_iColumns{ 0 },
			m_iBorderWidth{ 1 },
			m_aBorderColor{ { 130, 135, 144, 255 }, { 130, 135, 144, 255 }, { 130, 135, 144, 255 }, { 173, 178, 181, 255 } },
			m_aBackgroundColor{ { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 } },
			m_bBoxShadow{ false },
			m_sBoxShadowShift{ 0, 0 },
			m_iBoxShadowRadius{ 0 },
			m_aBoxShadowColor{ { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } },
			m_sPadding{ 1, 1, 1, 1 },
			m_eVerticalScrollBar{ sbAuto },
			m_eHorizontalScrollBar{ sbNone },
			m_iActiveItemIndex{ -1 },
			m_iResetSearchInterval{ 2000 },
			m_bAllowMultiSelect{ true },
			m_bAllowSearch{ true },
			m_bMouseDown{ false },
			m_iHoverItemIndex{ -1 },
			m_hTimer{ 0 }
		{
			m_sClassName = L"CCustomListBox";
			m_bAcceptFocus = true;
			m_bAcceptForm = true;
			m_bAcceptParent = true;
			m_bSupportText = true;
			m_bTabStop = true;
			m_sInitialRect = { 0, 0, 121, 97 };
			m_iLastPressedCharTime = std::chrono::steady_clock::now();
			// Create scrollbars
			m_bAcceptControls = true;
			CListBoxScrollBar *scroll = new CListBoxScrollBar(this);
			scroll->setType(CScrollBar::sbVertical);
			new CListBoxScrollBar(this);
			m_bAcceptControls = false;
			// Setup scrollbars
			getHScrollBar()->setBoxShadowShift({ 0, -1 });
			getVScrollBar()->setBoxShadowShift({ -1, 0 });
		}

		CCustomListBox::~CCustomListBox()
		{
			DeleteAll();
		}
	#pragma endregion

	#pragma region Getters
		APP_RECT CCustomListBox::getClientRect()
		{
			APP_RECT result = CControl::getClientRect();
			result.Left += (int)m_iBorderWidth + (int)m_sPadding.Left;
			result.Top += (int)m_iBorderWidth + (int)m_sPadding.Top;
			result.Right -= (int)m_iBorderWidth + (int)m_sPadding.Right;
			result.Bottom -= (int)m_iBorderWidth + (int)m_sPadding.Bottom;
			if (!result.IsValid())
			{
				result.Right = result.Left;
				result.Bottom = result.Top;
			}
			return result;
		}

		APP_RECT CCustomListBox::getRenderRect()
		{
			APP_RECT result = getRect();
			if (m_bBoxShadow)
			{
				if (m_sBoxShadowShift.X > 0)
					result.Right += m_sBoxShadowShift.X;
				else
					result.Left += m_sBoxShadowShift.X;
				if (m_sBoxShadowShift.Y > 0)
					result.Bottom += m_sBoxShadowShift.Y;
				else
					result.Top += m_sBoxShadowShift.Y;
				result.Left -= (int)m_iBoxShadowRadius;
				result.Right += (int)m_iBoxShadowRadius;
				result.Top -= (int)m_iBoxShadowRadius;
				result.Bottom += (int)m_iBoxShadowRadius;
				if (!result.IsValid())
				{
					result.Right = result.Left;
					result.Bottom = result.Top;
				}
			}
			return result;
		}

		CCustomListBox::STATE CCustomListBox::getState()
		{
			if (!m_bEnabled)
				return stDisabled;
			if (m_pForm)
			{
				if (m_pForm->getActiveControl() == this)
					return stActive;
				if (m_pForm->getHoveredControl() == this || m_pForm->getHoveredControl() == getHScrollBar() || m_pForm->getHoveredControl() == getVScrollBar())
					return stHovered;
			}
			return stNormal;
		}

		CCustomListBox::CListBoxScrollBar *CCustomListBox::getVScrollBar()
		{
			return cast<CListBoxScrollBar*>(getControl(0));
		}

		CCustomListBox::CListBoxScrollBar *CCustomListBox::getHScrollBar()
		{
			return cast<CListBoxScrollBar*>(getControl(1));
		}

		size_t CCustomListBox::getColumns() const
		{
			return m_iColumns;
		}

		size_t CCustomListBox::getBorderWidth() const
		{
			return m_iBorderWidth;
		}

		APP_COLOR CCustomListBox::getBorderColor(const STATE state) const
		{
			return m_aBorderColor[state];
		}

		APP_COLOR CCustomListBox::getBackgroundColor(const STATE state) const
		{
			return m_aBackgroundColor[state];
		}

		bool CCustomListBox::getBoxShadow() const
		{
			return m_bBoxShadow;
		}

		APP_POINT CCustomListBox::getBoxShadowShift() const
		{
			return m_sBoxShadowShift;
		}

		int CCustomListBox::getBoxShadowShiftX() const
		{
			return m_sBoxShadowShift.X;
		}

		int CCustomListBox::getBoxShadowShiftY() const
		{
			return m_sBoxShadowShift.Y;
		}

		size_t CCustomListBox::getBoxShadowRadius() const
		{
			return m_iBoxShadowRadius;
		}

		APP_COLOR CCustomListBox::getBoxShadowColor(const STATE state) const
		{
			return m_aBoxShadowColor[state];
		}

		math::RECTANGLE<size_t> CCustomListBox::getPadding() const
		{
			return m_sPadding;
		}

		size_t CCustomListBox::getPaddingLeft() const
		{
			return m_sPadding.Left;
		}

		size_t CCustomListBox::getPaddingTop() const
		{
			return m_sPadding.Top;
		}

		size_t CCustomListBox::getPaddingRight() const
		{
			return m_sPadding.Right;
		}

		size_t CCustomListBox::getPaddingBottom() const
		{
			return m_sPadding.Bottom;
		}

		CCustomListBox::SCROLLBAR CCustomListBox::getVerticalScrollBar() const
		{
			return m_eVerticalScrollBar;
		}

		CCustomListBox::SCROLLBAR CCustomListBox::getHorizontalScrollBar() const
		{
			return m_eHorizontalScrollBar;
		}

		size_t CCustomListBox::getItemCount() const
		{
			return m_aItems.size();
		}

		CCustomListBoxItem *CCustomListBox::getItem(const size_t index)
		{
			if (index < m_aItems.size())
				return m_aItems[index];
			return nullptr;
		}

		int CCustomListBox::getActiveItemIndex() const
		{
			return m_iActiveItemIndex;
		}

		CCustomListBoxItem *CCustomListBox::getActiveItem()
		{
			if (m_iActiveItemIndex >= 0 && m_iActiveItemIndex < (int)m_aItems.size())
				return m_aItems[(size_t)m_iActiveItemIndex];
			return nullptr;
		}

		CCustomListBoxItem *CCustomListBox::getHoveredItem()
		{
			if (m_iHoverItemIndex >= 0 && m_iHoverItemIndex < (int)m_aItems.size())
				return m_aItems[(size_t)m_iHoverItemIndex];
			return nullptr;
		}

		size_t CCustomListBox::getResetSearchInterval() const
		{
			return m_iResetSearchInterval;
		}

		bool CCustomListBox::getAllowMultiSelect() const
		{
			return m_bAllowMultiSelect;
		}

		bool CCustomListBox::getAllowSearch() const
		{
			return m_bAllowSearch;
		}
	#pragma endregion

	#pragma region Setters
		CCustomListBox *CCustomListBox::setColumns(size_t value)
		{
			if (value < 2)
				value = 0;
			if (value != m_iColumns)
			{
				m_iColumns = value;
				Update();
			}
			return this;
		}

		CCustomListBox *CCustomListBox::setBorderWidth(const size_t value)
		{
			if (value != m_iBorderWidth)
			{
				m_iBorderWidth = value;
				Update();
			}
			return this;
		}

		CCustomListBox *CCustomListBox::setBorderColor(const STATE state, const APP_COLOR &value)
		{
			if (value != m_aBorderColor[state])
			{
				m_aBorderColor[state] = value;
				if (getState() == state)
					Repaint(false);
			}
			return this;
		}

		CCustomListBox *CCustomListBox::setBackgroundColor(const STATE state, const APP_COLOR &value)
		{
			if (value != m_aBackgroundColor[state])
			{
				m_aBackgroundColor[state] = value;
				if (getState() == state)
					Repaint(false);
			}
			return this;
		}

		CCustomListBox *CCustomListBox::setBoxShadow(const bool value)
		{
			if (value != m_bBoxShadow)
			{
				m_bBoxShadow = value;
				Repaint(false);
			}
			return this;
		}

		CCustomListBox *CCustomListBox::setBoxShadowShift(const APP_POINT &value)
		{
			if (value != m_sBoxShadowShift)
			{
				m_sBoxShadowShift = value;
				if (m_bBoxShadow)
					Repaint(false);
			}
			return this;
		}

		CCustomListBox *CCustomListBox::setBoxShadowShiftX(const int value)
		{
			return setBoxShadowShift({ value, m_sBoxShadowShift.Y });
		}

		CCustomListBox *CCustomListBox::setBoxShadowShiftY(const int value)
		{
			return setBoxShadowShift({ m_sBoxShadowShift.X, value });
		}

		CCustomListBox *CCustomListBox::setBoxShadowRadius(const size_t value)
		{
			if (value != m_iBoxShadowRadius)
			{
				m_iBoxShadowRadius = value;
				if (m_bBoxShadow)
					Repaint(false);
			}
			return this;
		}

		CCustomListBox *CCustomListBox::setBoxShadowColor(const STATE state, const APP_COLOR &value)
		{
			if (value != m_aBoxShadowColor[state])
			{
				m_aBoxShadowColor[state] = value;
				if (m_bBoxShadow && getState() == state)
					Repaint(false);
			}
			return this;
		}

		CCustomListBox *CCustomListBox::setPadding(const math::RECTANGLE<size_t> &value)
		{
			if (value != m_sPadding)
			{
				m_sPadding = value;
				Update();
			}
			return this;
		}

		CCustomListBox *CCustomListBox::setPaddingLeft(const size_t value)
		{
			return setPadding({ value, m_sPadding.Top, m_sPadding.Right, m_sPadding.Bottom });
		}

		CCustomListBox *CCustomListBox::setPaddingTop(const size_t value)
		{
			return setPadding({ m_sPadding.Left, value, m_sPadding.Right, m_sPadding.Bottom });
		}

		CCustomListBox *CCustomListBox::setPaddingRight(const size_t value)
		{
			return setPadding({ m_sPadding.Left, m_sPadding.Top, value, m_sPadding.Bottom });
		}

		CCustomListBox *CCustomListBox::setPaddingBottom(const size_t value)
		{
			return setPadding({ m_sPadding.Left, m_sPadding.Top, m_sPadding.Right, value });
		}

		CCustomListBox *CCustomListBox::setVerticalScrollBar(const SCROLLBAR value)
		{
			if (value != m_eVerticalScrollBar)
			{
				m_eVerticalScrollBar = value;
				Update();
			}
			return this;
		}

		CCustomListBox *CCustomListBox::setHorizontalScrollBar(const SCROLLBAR value)
		{
			if (value != m_eHorizontalScrollBar)
			{
				m_eHorizontalScrollBar = value;
				Update();
			}
			return this;
		}

		CCustomListBox *CCustomListBox::setActiveItemIndex(int value)
		{
			if (value < -1 || value >= (int)m_aItems.size())
				value = -1;
			if (value != m_iActiveItemIndex)
			{
				if (getActiveItem())
					getActiveItem()->NotifyOnDeactivate();
				m_iActiveItemIndex = value;
				if (getActiveItem())
					getActiveItem()->NotifyOnActivate();
				Repaint(false);
			}
			return this;
		}

		CCustomListBox *CCustomListBox::setResetSearchInterval(const size_t value)
		{
			m_iResetSearchInterval = std::max((size_t)1, value);
			return this;
		}

		CCustomListBox *CCustomListBox::setAllowMultiSelect(const bool value)
		{
			if (value != m_bAllowMultiSelect)
			{
				m_bAllowMultiSelect = value;
				if (value)
					DeselectAllInternal();
				Repaint(false);
			}
			return this;
		}

		CCustomListBox *CCustomListBox::setAllowSearch(const bool value)
		{
			m_bAllowSearch = value;
			return this;
		}
	#pragma endregion

	#pragma region Items
		CCustomListBox *CCustomListBox::Add(CCustomListBoxItem *item)
		{
			if (item)
			{
				m_aItems.push_back(item);
				if (!m_bAllowMultiSelect)
					DeselectAllExceptFirst();
				item->UpdateFromStyle();
				Update();
			}
			return this;
		}

		CCustomListBox *CCustomListBox::Insert(const size_t before, CCustomListBoxItem *item)
		{
			if (item && m_aItems.size() > 0 && before < m_aItems.size() - 1)
			{
				if (getActiveItem())
					getActiveItem()->NotifyOnDeactivate();
				auto pos{ m_aItems.begin() };
				size_t index{ 0 };
				while (index++ < before && pos != m_aItems.end())
					pos++;
				m_aItems.insert(pos, item);
				m_iActiveItemIndex = -1;
				if (!m_bAllowMultiSelect)
					DeselectAllExceptFirst();
				item->UpdateFromStyle();
				Update();
			}
			return this;
		}

		CCustomListBox *CCustomListBox::Delete(const size_t index)
		{
			if (m_aItems.size() > 0 && index < m_aItems.size() - 1)
			{
				if (getActiveItem())
					getActiveItem()->NotifyOnDeactivate();
				auto pos{ m_aItems.begin() };
				size_t i{ 0 };
				while (i++ < index && pos != m_aItems.end())
					pos++;
				delete (*pos);
				m_aItems.erase(pos);
				m_iActiveItemIndex = -1;
				Update();
			}
			return this;
		}

		CCustomListBox *CCustomListBox::DeleteAll()
		{
			if (m_aItems.size() > 0)
			{
				if (getActiveItem())
					getActiveItem()->NotifyOnDeactivate();
				for (auto pos = m_aItems.begin(); pos != m_aItems.end(); pos++)
					delete (*pos);
				m_aItems.clear();
				m_iActiveItemIndex = -1;
				Update();
			}
			return this;
		}

		CCustomListBox *CCustomListBox::DeleteSelected()
		{
			if (m_aItems.size() > 0)
			{
				bool changed{ false };
				auto pos{ m_aItems.end() }, begin{ m_aItems.begin() };
				pos--;
				while (true)
				{
					if ((*pos)->getSelectedInternal())
					{
						if (!changed && getActiveItem())
							getActiveItem()->NotifyOnDeactivate();
						changed = true;
						delete (*pos);
						m_aItems.erase(pos);
					}
					if (pos == begin)
						break;
					pos--;
				}
				if (changed)
				{
					m_iActiveItemIndex = -1;
					Update();
				}
			}
			return this;
		}

		CCustomListBox *CCustomListBox::DeleteUnselected()
		{
			if (m_aItems.size() > 0)
			{
				bool changed{ false };
				auto pos{ m_aItems.end() }, begin{ m_aItems.begin() };
				pos--;
				while (true)
				{
					if (!(*pos)->getSelectedInternal())
					{
						if (!changed && getActiveItem())
							getActiveItem()->NotifyOnDeactivate();
						changed = true;
						delete (*pos);
						m_aItems.erase(pos);
					}
					if (pos == m_aItems.begin())
						break;
					pos--;
				}
				if (changed)
				{
					m_iActiveItemIndex = -1;
					Update();
				}
			}
			return this;
		}

		CCustomListBox *CCustomListBox::SelectAll()
		{
			bool changed{ false };
			for (auto pos = m_aItems.begin(); pos != m_aItems.end(); pos++)
				if ((*pos)->setSelectedInternal(true))
					changed = true;
			if (changed)
			{
				if (!m_bAllowMultiSelect)
					DeselectAllExceptFirst();
				Repaint(false);
			}
			return this;
		}

		CCustomListBox *CCustomListBox::DeselectAll()
		{
			if (DeselectAllInternal())
				Repaint(false);
			return this;
		}

		CCustomListBox *CCustomListBox::InvertSelection()
		{
			if (m_aItems.size() > 0)
			{
				bool changed{ false };
				for (auto pos = m_aItems.begin(); pos != m_aItems.end(); pos++)
					if ((*pos)->setSelectedInternal(!(*pos)->getSelectedInternal()))
						changed = true;
				if (changed)
				{
					if (!m_bAllowMultiSelect)
						DeselectAllExceptFirst();
					Repaint(false);
				}
			}
			return this;
		}

		CCustomListBox *CCustomListBox::SelectRange(size_t start, size_t end)
		{
			if (m_aItems.size() > 0)
			{
				if (start >= m_aItems.size())
					start = m_aItems.size() - 1;
				if (end >= m_aItems.size())
					end = m_aItems.size() - 1;
				if (end < start)
				{
					size_t t{ start };
					start = end;
					end = t;
				}
				bool changed{ false };
				for (size_t i = start; i <= end; i++)
					if (m_aItems[i]->setSelectedInternal(true))
						changed = true;
				if (changed)
				{
					if (!m_bAllowMultiSelect)
						DeselectAllExceptFirst();
					Repaint(false);
				}
			}
			return this;
		}
	#pragma endregion

	#pragma region Notifications
		bool CCustomListBox::NotifyOnKeyDown(const IWindow::KEY key)
		{
			if (m_aItems.size() > 0)
			{
				bool ctrl, alt, shift;
				m_pForm->getWindow()->getControlKeys(ctrl, shift, alt);
				switch (key)
				{
				case IWindow::keyUp:
					ProcessKeyUp(shift);
					break;
				case IWindow::keyDown:
					ProcessKeyDown(shift);
					break;
				case IWindow::keyLeft:
					if (m_iColumns > 0)
						ProcessKeyLeft(shift);
					break;
				case IWindow::keyRight:
					if (m_iColumns > 0)
						ProcessKeyRight(shift);
					break;
				case IWindow::keyHome:
					ProcessKeyHome(shift);
					break;
				case IWindow::keyEnd:
					ProcessKeyEnd(shift);
					break;
				case IWindow::keyPrior:
					ProcessKeyPageUp(shift);
					break;
				case IWindow::keyNext:
					ProcessKeyPageDown(shift);
					break;
				case IWindow::keySpace:
					ProcessKeySpace();
					break;
				case IWindow::keyReturn:
					ProcessKeyReturn();
					break;
				case IWindow::keyA:
					if (ctrl && !alt && !shift)
						SelectAll();
					break;
				}
			}
			return CControl::NotifyOnKeyDown(key);
		}

		bool CCustomListBox::NotifyOnChar(const wchar_t chr)
		{
			if (m_bAllowSearch && m_aItems.size() > 0)
			{
				bool ctrl, alt, shift;
				m_pForm->getWindow()->getControlKeys(ctrl, shift, alt);
				if (!ctrl && !alt && std::isgraph(chr, std::locale()))
				{
					if (std::chrono::steady_clock::now() - m_iLastPressedCharTime > std::chrono::milliseconds(m_iResetSearchInterval))
						m_sSearchChars.clear();
					m_sSearchChars.push_back(chr);
					m_iLastPressedCharTime = std::chrono::steady_clock::now();
					ProcessSearch();
				}
			}
			return CControl::NotifyOnChar(chr);
		}

		bool CCustomListBox::NotifyOnMouseMove(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			if (m_bEnabled)
			{
				int index{ ItemAtPos(x, y) };
				if (index != m_iHoverItemIndex)
				{
					if (getHoveredItem())
						getHoveredItem()->NotifyOnLeave();
					m_iHoverItemIndex = index;
					if (getHoveredItem())
						getHoveredItem()->NotifyOnHover();
					Repaint(false);
				}
				if (m_bMouseDown)
					ProcessMouseMove(x, y);
			}
			CControl::NotifyOnMouseMove(x, y, ctrl, left, middle, right, shift);
			return true;
		}

		bool CCustomListBox::NotifyOnLeftMouseButtonDown(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			if (m_bEnabled)
			{
				if (!m_bMouseDown && m_aItems.size() > 0)
				{
					StartCapture();
					m_bMouseDownWithCtrl = ctrl;
					m_bMouseDownWithShift = shift;
					CCustomListBoxItem *item{ getHoveredItem() };
					if (item)
						if (m_bAllowMultiSelect && (m_bMouseDownWithCtrl || m_bMouseDownWithShift))
						{
							if (m_bMouseDownWithCtrl)
							{
								item->setSelectedInternal(!m_aItems[m_iHoverItemIndex]->getSelectedInternal());
								m_iActiveItemIndex = m_iHoverItemIndex;
								item->NotifyOnClick();
								Repaint(false);
							}
							else
							{
								if (m_iActiveItemIndex < 0)
									m_iActiveItemIndex = m_iHoverItemIndex;
								DeselectAll();
								SelectRange(m_iHoverItemIndex, m_iActiveItemIndex);
								Repaint(false);
							}
						}
						else
						{
							DeselectAllInternal();
							m_iActiveItemIndex = m_iHoverItemIndex;
							m_aItems[m_iHoverItemIndex]->setSelectedInternal(true);
							item->NotifyOnClick();
							Repaint(false);
						}
				}
				else
					EndCapture();
			}
			CControl::NotifyOnLeftMouseButtonDown(x, y, ctrl, left, middle, right, shift);
			APP_RECT r = ClientToForm(getRect());
			return x < r.Left || x >= r.Right || y < r.Top || y >= r.Bottom; // If event appears on control, return false(required for correct processing of scrollbars)
		}

		bool CCustomListBox::NotifyOnLeftMouseButtonUp(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			EndCapture();
			CControl::NotifyOnLeftMouseButtonUp(x, y, ctrl, left, middle, right, shift);
			return true;
		}

		bool CCustomListBox::NotifyOnLeftMouseButtonDoubleClick(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			EndCapture();
			CControl::NotifyOnLeftMouseButtonDoubleClick(x, y, ctrl, left, middle, right, shift);
			return true;
		}

		bool CCustomListBox::NotifyOnRightMouseButtonDown(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			EndCapture();
			CControl::NotifyOnRightMouseButtonDown(x, y, ctrl, left, middle, right, shift);
			return true;
		}

		bool CCustomListBox::NotifyOnRightMouseButtonUp(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			EndCapture();
			CControl::NotifyOnRightMouseButtonUp(x, y, ctrl, left, middle, right, shift);
			return true;
		}

		bool CCustomListBox::NotifyOnRightMouseButtonDoubleClick(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			EndCapture();
			CControl::NotifyOnRightMouseButtonDoubleClick(x, y, ctrl, left, middle, right, shift);
			return true;
		}

		bool CCustomListBox::NotifyOnMiddleMouseButtonDown(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			EndCapture();
			CControl::NotifyOnMiddleMouseButtonDown(x, y, ctrl, left, middle, right, shift);
			return true;
		}

		bool CCustomListBox::NotifyOnMiddleMouseButtonUp(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			EndCapture();
			CControl::NotifyOnMiddleMouseButtonUp(x, y, ctrl, left, middle, right, shift);
			return true;
		}

		bool CCustomListBox::NotifyOnMiddleMouseButtonDoubleClick(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			EndCapture();
			CControl::NotifyOnMiddleMouseButtonDoubleClick(x, y, ctrl, left, middle, right, shift);
			return true;
		}

		bool CCustomListBox::NotifyOnMouseVerticalWheel(const int x, const int y, const int delta, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			if (m_bEnabled && getVScrollBar()->getEnabled())
			{
				if (delta > 0 && getVScrollBar()->getScroll() > getVScrollBar()->getMin())
					getVScrollBar()->setScroll(getVScrollBar()->getScroll() - getVScrollBar()->getDeltaScroll());
				else if (delta < 0 && getVScrollBar()->getScroll() < getVScrollBar()->getMax())
					getVScrollBar()->setScroll(getVScrollBar()->getScroll() + getVScrollBar()->getDeltaScroll());
			}
			CControl::NotifyOnMouseVerticalWheel(x, y, delta, ctrl, left, middle, right, shift);
			return true;
		}

		bool CCustomListBox::NotifyOnMouseHorizontalWheel(const int x, const int y, const int delta, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			if (m_bEnabled && getHScrollBar()->getEnabled())
			{
				if (delta > 0 && getHScrollBar()->getScroll() > getHScrollBar()->getMin())
					getHScrollBar()->setScroll(getHScrollBar()->getScroll() - getHScrollBar()->getDeltaScroll());
				else if (delta < 0 && getHScrollBar()->getScroll() < getHScrollBar()->getMax())
					getHScrollBar()->setScroll(getHScrollBar()->getScroll() + getHScrollBar()->getDeltaScroll());
			}
			CControl::NotifyOnMouseHorizontalWheel(x, y, delta, ctrl, left, middle, right, shift);
			return true;
		}

		void CCustomListBox::NotifyOnChangeUseParentFont()
		{
			CControl::NotifyOnChangeUseParentFont();
			Update();
		}

		void CCustomListBox::NotifyOnParentFontChangeSize()
		{
			CControl::NotifyOnParentFontChangeSize();
			Update();
		}

		void CCustomListBox::NotifyOnFontChangeSize()
		{
			CControl::NotifyOnFontChangeSize();
			Update();
		}

		void CCustomListBox::NotifyOnMouseHover()
		{
			Repaint(false);
			CControl::NotifyOnMouseHover();
		}

		void CCustomListBox::NotifyOnMouseLeave()
		{
			if (getHoveredItem())
				getHoveredItem()->NotifyOnLeave();
			m_iHoverItemIndex = -1;
			Repaint(false);
			CControl::NotifyOnMouseLeave();
		}

		void CCustomListBox::NotifyOnKillFocus()
		{
			Repaint(false);
			CControl::NotifyOnKillFocus();
		}

		void CCustomListBox::NotifyOnSetFocus(CControl *old)
		{
			Repaint(false);
			CControl::NotifyOnSetFocus(old);
		}

		void CCustomListBox::NotifyOnResetFocus()
		{
			Repaint(false);
			CControl::NotifyOnResetFocus();
		}

		void CCustomListBox::NotifyOnKillCaptureMouse()
		{
			if (m_hTimer)
			{
				m_pForm->DeleteTimer(m_hTimer);
				m_hTimer = 0;
			}
			m_bMouseDown = false;
			m_pForm->getWindow()->ReleaseMouseCapture();
			CControl::NotifyOnKillCaptureMouse();
		}

		void CCustomListBox::NotifyOnSetCaptureMouse()
		{
			m_hTimer = m_pForm->AddTimer(TimerCallback, this, SCROLL_TIMER_INTERVAL);
			m_pForm->getWindow()->CaptureMouse();
			CControl::NotifyOnSetCaptureMouse();
		}

		void CCustomListBox::NotifyOnChangeParentStyle()
		{
			CControl::NotifyOnChangeParentStyle();
			Update();
		}

		void CCustomListBox::NotifyOnChangeStyle()
		{
			CControl::NotifyOnChangeStyle();
			Update();
		}

		void CCustomListBox::NotifyOnShow()
		{
			CControl::NotifyOnShow();
			Update();
		}

		void CCustomListBox::NotifyOnPaint(APP_RECT clip)
		{
			PaintBoxShadow(clip);
			PaintBackground(clip);
			PaintItems(clip);
			PaintScrollbarsCorner(clip);
			CControl::NotifyOnPaint(clip);
		}

		void CCustomListBox::NotifyOnResize(const APP_POINT &old_size, const APP_POINT &new_size)
		{
			CControl::NotifyOnResize(old_size, new_size);
			Update();
		}

		void CCustomListBox::NotifyOnScroll(CListBoxScrollBar *sender)
		{
			Update();
		}
	#pragma endregion

	#pragma region Helpers
		bool CCustomListBox::DeselectAllInternal()
		{
			bool result{ false };
			for (auto pos = m_aItems.begin(); pos != m_aItems.end(); pos++)
				if ((*pos)->setSelectedInternal(false))
					result = true;
			return result;
		}

		void CCustomListBox::DeselectAllExceptFirst()
		{
			bool found{ false };
			for (auto pos = m_aItems.begin(); pos != m_aItems.end(); pos++)
				if (found)
					(*pos)->setSelectedInternal(false);
				else if ((*pos)->getSelectedInternal())
					found = true;
		}

		bool CCustomListBox::PosToGrid(const int x, const int y, int &col, int &row)
		{
			if (m_aItems.size() == 0 || m_sItemSize.X == 0 || m_sItemSize.Y == 0)
				return false;
			int scroll_v{ getVScrollBar()->getEnabled() ? getVScrollBar()->getScroll() : 0 };
			int scroll_h{ getHScrollBar()->getEnabled() ? getHScrollBar()->getScroll() : 0 };
			APP_POINT p = ClientToForm(getPosition());
			p.X = x - p.X + scroll_h;
			p.Y = y - p.Y + scroll_v;
			col = p.X / (int)m_sItemSize.X;
			row = p.Y / (int)m_sItemSize.Y;
			return true;
		}

		int CCustomListBox::ItemAtPos(const int x, const int y)
		{
			if (m_aItems.size() == 0)
				return -1;
			APP_RECT rect = ClientToForm(getClientRect());
			if (getHScrollBar()->getVisible())
				rect.Bottom -= getHScrollBar()->getHeight();
			if (getVScrollBar()->getVisible())
				rect.Right -= getVScrollBar()->getWidth();
			if (!rect.IsValid() || x < rect.Left || x >= rect.Right || y < rect.Top || y >= rect.Bottom) // Check out of client area
				return -1;
			int col, row;
			if (!PosToGrid(x, y, col, row))
				return -1;
			int index;
			if (m_iColumns > 0)
			{
				int cols, rows;
				GridSize(cols, rows);
				index = col * rows + row;
				if (index < 0 || index >= (int)m_aItems.size())
					index = -1;
			}
			else
			{
				index = row;
				if (index < 0 || index >= (int)m_aItems.size())
					index = -1;
			}
			return index;
		}

		void CCustomListBox::Update()
		{
			// Calculate client rect
			APP_RECT allowed = getRect();
			allowed.Left += (int)m_iBorderWidth + (int)m_sPadding.Left;
			allowed.Top += (int)m_iBorderWidth + (int)m_sPadding.Top;
			allowed.Right -= (int)m_iBorderWidth + (int)m_sPadding.Right;
			allowed.Bottom -= (int)m_iBorderWidth + (int)m_sPadding.Bottom;
			if (!allowed.IsValid() || allowed.IsEmpty())
				return;
			// Calculate required size
			m_sItemSize = { 0, 0 };
			for (auto pos = m_aItems.begin(); pos != m_aItems.end(); pos++)
			{
				math::POINT<size_t> size = (*pos)->CalculateSize();
				m_sItemSize.X = std::max(m_sItemSize.X, size.X);
				m_sItemSize.Y = std::max(m_sItemSize.Y, size.Y);
			}
			int cols{ 0 }, rows{ 0 };
			GridSize(cols, rows);
			math::POINT<size_t> required{ (size_t)cols * m_sItemSize.X, (size_t)rows * m_sItemSize.Y };
			if (m_pForm)
				m_pForm->LockRepaint();
			// Setup scrollbars visibility and update allowed rect depend on it
			switch (m_eHorizontalScrollBar)
			{
			case sbNone:
				getHScrollBar()->setVisible(false);
				break;
			case sbVisible:
				allowed.Bottom -= getHScrollBar()->getHeight();
				getHScrollBar()->setVisible(true);
				break;
			case sbAuto:
				switch (m_eVerticalScrollBar)
				{
				case sbNone:
					if ((int)required.X > allowed.Width())
					{
						allowed.Bottom -= getHScrollBar()->getHeight();
						getHScrollBar()->setVisible(true);
					}
					else
						getHScrollBar()->setVisible(false);
					break;
				case sbVisible:
					if ((int)required.X > allowed.Width() - getVScrollBar()->getWidth())
					{
						allowed.Bottom -= getHScrollBar()->getHeight();
						getHScrollBar()->setVisible(true);
					}
					else
						getHScrollBar()->setVisible(false);
					break;
				case sbAuto:
					if ((int)required.X > allowed.Width())
					{
						allowed.Bottom -= getHScrollBar()->getHeight();
						getHScrollBar()->setVisible(true);
					}
					else if ((int)required.X < allowed.Width() - getVScrollBar()->getWidth())
						getHScrollBar()->setVisible(false);
					else if ((int)required.Y > allowed.Height())
					{
						allowed.Bottom -= getHScrollBar()->getHeight();
						getHScrollBar()->setVisible(true);
					}
					else
						getHScrollBar()->setVisible(false);
					break;
				}
				break;
			}
			switch (m_eVerticalScrollBar)
			{
			case sbNone:
				getVScrollBar()->setVisible(false);
				break;
			case sbVisible:
				allowed.Right -= getVScrollBar()->getWidth();
				getVScrollBar()->setVisible(true);
				break;
			case sbAuto:
				if ((int)required.Y > allowed.Height())
				{
					allowed.Right -= getVScrollBar()->getWidth();
					getVScrollBar()->setVisible(true);
				}
				else
					getVScrollBar()->setVisible(false);
				break;
			}
			// Setup scrollbars enable, range and page size, delta
			if (required.X > (size_t)allowed.Width())
			{
				getHScrollBar()->setEnabled(true);
				getHScrollBar()->setMax(required.X - allowed.Width());
				getHScrollBar()->setPageSize((size_t)((double)allowed.Width() / (double)required.X * ((double)required.X - (double)allowed.Width())));
				getHScrollBar()->setDeltaScroll(m_sItemSize.X);
			}
			else
				getHScrollBar()->setEnabled(false);
			if (required.Y > (size_t)allowed.Height())
			{
				getVScrollBar()->setEnabled(true);
				getVScrollBar()->setMax(required.Y - allowed.Height());
				getVScrollBar()->setPageSize((size_t)((double)allowed.Height() / (double)required.Y * ((double)required.Y - (double)allowed.Height())));
				getVScrollBar()->setDeltaScroll(m_sItemSize.Y);
			}
			else
				getVScrollBar()->setEnabled(false);
			// Setup scrollbars positions and sizes
			if (getHScrollBar()->getVisible())
			{
				getHScrollBar()->setPosition({ allowed.Left - getLeft(), allowed.Bottom - getTop() });
				getHScrollBar()->setWidth(allowed.Width());
			}
			if (getVScrollBar()->getVisible())
			{
				getVScrollBar()->setPosition({ allowed.Right - getLeft(), allowed.Top - getTop() });
				getVScrollBar()->setHeight(allowed.Height());
			}
			// Adjust item width to allowed area width if no hscroll is required
			if (!getHScrollBar()->getEnabled())
			{
				m_sItemSize.X = (size_t)allowed.Width();
				if (getVScrollBar()->getBoxShadow() && getVScrollBar()->getBoxShadowShiftX() - (int)getVScrollBar()->getBoxShadowRadius() < 0)
					m_sItemSize.X -= std::min((int)m_sItemSize.X, -getVScrollBar()->getBoxShadowShiftX() + (int)getVScrollBar()->getBoxShadowRadius());
			}
			// Update hover item index
			if (m_pForm)
			{
				int x, y;
				if (m_pForm->getWindow()->getCursorPosition(x, y))
				{
					int index{ ItemAtPos(x, y) };
					if (index != m_iHoverItemIndex)
					{
						if (getHoveredItem())
							getHoveredItem()->NotifyOnLeave();
						m_iHoverItemIndex = index;
						if (getHoveredItem())
							getHoveredItem()->NotifyOnHover();
					}
				}
				Repaint(false);
				m_pForm->UnlockRepaint();
			}
		}

		void CCustomListBox::ScrollToItem(const int index)
		{
			if (index < 0 || index >= (int)m_aItems.size() || (!getHScrollBar()->getEnabled() && !getVScrollBar()->getEnabled()))
				return;
			APP_RECT client = ClientToForm(getClientRect());
			if (getHScrollBar()->getVisible())
				client.Bottom -= getHScrollBar()->getHeight();
			if (getVScrollBar()->getVisible())
				client.Right -= getVScrollBar()->getWidth();
			if (!client.IsValid() || client.IsEmpty())
				return;
			int cols, rows;
			GridSize(cols, rows);
			int dx{ getHScrollBar()->getEnabled() ? getHScrollBar()->getScroll() : 0 };
			int dy{ getVScrollBar()->getEnabled() ? getVScrollBar()->getScroll() : 0 };
			int col{ index / rows }, row{ index % rows };
			APP_RECT item_rect{
				client.Left + col * (int)m_sItemSize.X - dx, client.Top + row * (int)m_sItemSize.Y - dy,
				client.Left + (col + 1) * (int)m_sItemSize.X - dx, client.Top + (row + 1) * (int)m_sItemSize.Y - dy
			};
			if (getVScrollBar()->getEnabled())
			{
				if (item_rect.Top < client.Top)
					getVScrollBar()->setScroll(getVScrollBar()->getScroll() - (client.Top - item_rect.Top));
				else if (item_rect.Bottom > client.Bottom)
					getVScrollBar()->setScroll(getVScrollBar()->getScroll() + (item_rect.Top - client.Top));
			}
			if (getHScrollBar()->getEnabled())
			{
				if (item_rect.Left < client.Left)
					getHScrollBar()->setScroll(getHScrollBar()->getScroll() - (client.Left - item_rect.Left));
				else if (item_rect.Right > client.Right)
					getHScrollBar()->setScroll(getHScrollBar()->getScroll() + (item_rect.Left - client.Left));
			}
		}

		bool CCustomListBox::GridSize(int &cols, int &rows)
		{
			if (m_aItems.size() == 0)
				return false;
			cols = (int)std::max((size_t)1, std::min(m_iColumns, m_aItems.size()));
			rows = m_aItems.size() / cols;
			if (m_aItems.size() % cols > 0)
				rows++;
			return true;
		}

		bool CCustomListBox::ItemIndexToGrid(const int index, int &col, int &row)
		{
			int cols, rows;
			if (!GridSize(cols, rows))
				return false;
			col = index / rows;
			row = index % rows;
			return true;
		}

		void CCustomListBox::TimerCallback(void *param)
		{
			CCustomListBox *listbox{ (CCustomListBox*)param };
			listbox->m_pForm->LockRepaint();
			listbox->ProcessTimer();
			listbox->m_pForm->UnlockRepaint();
		}

		bool CCustomListBox::UpdateFromStyle()
		{
			if (!getStyle())
				return false;
			m_iBorderWidth = getStyle()->getParameterByName(m_sClassName + L".BorderWidth", m_iBorderWidth);
			m_bBoxShadow = getStyle()->getParameterByName(m_sClassName + L".BoxShadow", m_bBoxShadow);
			m_sBoxShadowShift = getStyle()->getParameterByName(m_sClassName + L".BoxShadowShift", m_sBoxShadowShift);
			m_iBoxShadowRadius = getStyle()->getParameterByName(m_sClassName + L".BoxShadowRadius", m_iBoxShadowRadius);
			m_sPadding = getStyle()->getParameterByName(m_sClassName + L".Padding", m_sPadding);
			for (int i = 0; i <= stDisabled; i++)
			{
				String name;
				switch (i)
				{
				case stNormal:
					name = L".normal";
					break;
				case stHovered:
					name = L".hovered";
					break;
				case stActive:
					name = L".active";
					break;
				default:
					name = L".disabled";
					break;
				}
				m_aBorderColor[i] = getStyle()->getParameterByName(m_sClassName + L".BorderColor" + name, m_aBorderColor[i]);
				m_aBackgroundColor[i] = getStyle()->getParameterByName(m_sClassName + L".BackgroundColor" + name, m_aBackgroundColor[i]);
				m_aBoxShadowColor[i] = getStyle()->getParameterByName(m_sClassName + L".BoxShadowColor" + name, m_aBoxShadowColor[i]);
			}
			for (auto pos = m_aItems.begin(); pos != m_aItems.end(); pos++)
				(*pos)->UpdateFromStyle();
			return true;
		}

		void CCustomListBox::StartCapture()
		{
			m_pForm->CaptureMouse(this);
			m_bMouseDown = true;
		}

		void CCustomListBox::EndCapture()
		{
			m_bMouseDown = false;
			if (m_pForm->getCaptureMouseControl() == this)
				m_pForm->ReleaseCaptureMouse();
		}
	#pragma endregion

	#pragma region Process events
		void CCustomListBox::ProcessKeyUp(const bool shift)
		{
			if (shift && m_bAllowMultiSelect && m_aItems.size() > 1 && m_iActiveItemIndex > 0)
			{
				if (getActiveItem())
					getActiveItem()->NotifyOnDeactivate();
				m_iActiveItemIndex--;
				if (!m_aItems[(size_t)m_iActiveItemIndex]->getSelectedInternal())
					m_aItems[(size_t)m_iActiveItemIndex]->setSelectedInternal(!m_aItems[(size_t)m_iActiveItemIndex]->getSelectedInternal());
				else
					m_aItems[(size_t)m_iActiveItemIndex + 1]->setSelectedInternal(false);
				if (getActiveItem())
					getActiveItem()->NotifyOnActivate();
				ScrollToItem(m_iActiveItemIndex);
				Repaint(false);
			}
			else
			{
				int old{ m_iActiveItemIndex };
				if (m_iActiveItemIndex < 0)
					m_iActiveItemIndex = m_aItems.size() - 1;
				else if (m_iActiveItemIndex > 0)
					m_iActiveItemIndex--;
				if (old != m_iActiveItemIndex)
				{
					if (getItem(old))
						getItem(old)->NotifyOnDeactivate();
					DeselectAllInternal();
					m_aItems[(size_t)m_iActiveItemIndex]->setSelectedInternal(true);
					if (getActiveItem())
						getActiveItem()->NotifyOnActivate();
					ScrollToItem(m_iActiveItemIndex);
					Repaint(false);
				}
			}
		}

		void CCustomListBox::ProcessKeyDown(const bool shift)
		{
			if (shift && m_bAllowMultiSelect && m_aItems.size() > 1 && m_iActiveItemIndex < (int)m_aItems.size() - 1)
			{
				if (getActiveItem())
					getActiveItem()->NotifyOnDeactivate();
				m_iActiveItemIndex++;
				if (!m_aItems[(size_t)m_iActiveItemIndex]->getSelectedInternal())
					m_aItems[(size_t)m_iActiveItemIndex]->setSelectedInternal(!m_aItems[(size_t)m_iActiveItemIndex]->getSelectedInternal());
				else
					m_aItems[(size_t)m_iActiveItemIndex - 1]->setSelectedInternal(false);
				if (getActiveItem())
					getActiveItem()->NotifyOnActivate();
				ScrollToItem(m_iActiveItemIndex);
				Repaint(false);
			}
			else
			{
				int old{ m_iActiveItemIndex };
				if (m_iActiveItemIndex < 0)
					m_iActiveItemIndex = 0;
				else if (m_iActiveItemIndex < (int)m_aItems.size() - 1)
					m_iActiveItemIndex++;
				if (old != m_iActiveItemIndex)
				{
					if (getItem(old))
						getItem(old)->NotifyOnDeactivate();
					DeselectAllInternal();
					m_aItems[(size_t)m_iActiveItemIndex]->setSelectedInternal(true);
					if (getActiveItem())
						getActiveItem()->NotifyOnActivate();
					ScrollToItem(m_iActiveItemIndex);
					Repaint(false);
				}
			}
		}

		void CCustomListBox::ProcessKeyHome(const bool shift)
		{
			if (shift && m_bAllowMultiSelect && m_aItems.size() > 0 && m_iActiveItemIndex > 0)
			{
				if (getActiveItem())
					getActiveItem()->NotifyOnDeactivate();
				do
				{
					m_iActiveItemIndex--;
					if (!m_aItems[(size_t)m_iActiveItemIndex]->getSelectedInternal())
						m_aItems[(size_t)m_iActiveItemIndex]->setSelectedInternal(!m_aItems[(size_t)m_iActiveItemIndex]->getSelectedInternal());
					else
						m_aItems[(size_t)m_iActiveItemIndex + 1]->setSelectedInternal(false);
				} while (m_iActiveItemIndex > 0);
				if (getActiveItem())
					getActiveItem()->NotifyOnActivate();
				ScrollToItem(m_iActiveItemIndex);
				Repaint(false);
			}
			else if (m_iActiveItemIndex != 0)
			{
				if (getActiveItem())
					getActiveItem()->NotifyOnDeactivate();
				m_iActiveItemIndex = 0;
				DeselectAllInternal();
				m_aItems[(size_t)m_iActiveItemIndex]->setSelectedInternal(true);
				if (getActiveItem())
					getActiveItem()->NotifyOnActivate();
				ScrollToItem(m_iActiveItemIndex);
				Repaint(false);
			}
		}

		void CCustomListBox::ProcessKeyEnd(const bool shift)
		{
			if (shift && m_bAllowMultiSelect && m_aItems.size() > 1 && m_iActiveItemIndex < (int)m_aItems.size() - 1)
			{
				if (getActiveItem())
					getActiveItem()->NotifyOnDeactivate();
				do
				{
					m_iActiveItemIndex++;
					if (!m_aItems[(size_t)m_iActiveItemIndex]->getSelectedInternal())
						m_aItems[(size_t)m_iActiveItemIndex]->setSelectedInternal(!m_aItems[(size_t)m_iActiveItemIndex]->getSelectedInternal());
					else
						m_aItems[(size_t)m_iActiveItemIndex - 1]->setSelectedInternal(false);
				} while (m_iActiveItemIndex < (int)m_aItems.size() - 1);
				if (getActiveItem())
					getActiveItem()->NotifyOnActivate();
				ScrollToItem(m_iActiveItemIndex);
				Repaint(false);
			}
			else if (m_iActiveItemIndex != (int)m_aItems.size() - 1)
			{
				if (getActiveItem())
					getActiveItem()->NotifyOnDeactivate();
				m_iActiveItemIndex = (int)m_aItems.size() - 1;
				DeselectAllInternal();
				m_aItems[(size_t)m_iActiveItemIndex]->setSelectedInternal(true);
				if (getActiveItem())
					getActiveItem()->NotifyOnActivate();
				ScrollToItem(m_iActiveItemIndex);
				Repaint(false);
			}
		}

		void CCustomListBox::ProcessKeyPageUp(const bool shift)
		{
			APP_RECT client = getClientRect();
			int page_size{ std::max(1, client.Height() / (int)m_sItemSize.Y) };
			if (shift && m_bAllowMultiSelect && m_aItems.size() > 0 && m_iActiveItemIndex > 0)
			{
				if (getActiveItem())
					getActiveItem()->NotifyOnDeactivate();
				int counter{ 0 };
				do
				{
					m_iActiveItemIndex--;
					if (!m_aItems[(size_t)m_iActiveItemIndex]->getSelectedInternal())
						m_aItems[(size_t)m_iActiveItemIndex]->setSelectedInternal(!m_aItems[(size_t)m_iActiveItemIndex]->getSelectedInternal());
					else
						m_aItems[(size_t)m_iActiveItemIndex + 1]->setSelectedInternal(false);
					counter++;
				} while (m_iActiveItemIndex > 0 && counter < page_size);
				if (getActiveItem())
					getActiveItem()->NotifyOnActivate();
				ScrollToItem(m_iActiveItemIndex);
				Repaint(false);
			}
			else if (m_iActiveItemIndex != 0)
			{
				if (getActiveItem())
					getActiveItem()->NotifyOnDeactivate();
				m_iActiveItemIndex = std::max(0, m_iActiveItemIndex - page_size);
				DeselectAllInternal();
				m_aItems[(size_t)m_iActiveItemIndex]->setSelectedInternal(true);
				if (getActiveItem())
					getActiveItem()->NotifyOnActivate();
				ScrollToItem(m_iActiveItemIndex);
				Repaint(false);
			}
		}

		void CCustomListBox::ProcessKeyPageDown(const bool shift)
		{
			APP_RECT client = getClientRect();
			int page_size{ std::max(1, client.Height() / (int)m_sItemSize.Y) };
			if (shift && m_bAllowMultiSelect && m_aItems.size() > 1 && m_iActiveItemIndex < (int)m_aItems.size() - 1)
			{
				if (getActiveItem())
					getActiveItem()->NotifyOnDeactivate();
				int counter{ 0 };
				do
				{
					m_iActiveItemIndex++;
					if (!m_aItems[(size_t)m_iActiveItemIndex]->getSelectedInternal())
						m_aItems[(size_t)m_iActiveItemIndex]->setSelectedInternal(!m_aItems[(size_t)m_iActiveItemIndex]->getSelectedInternal());
					else
						m_aItems[(size_t)m_iActiveItemIndex - 1]->setSelectedInternal(false);
					counter++;
				} while (m_iActiveItemIndex < (int)m_aItems.size() - 1 && counter < page_size);
				if (getActiveItem())
					getActiveItem()->NotifyOnActivate();
				ScrollToItem(m_iActiveItemIndex);
				Repaint(false);
			}
			else if (m_iActiveItemIndex != (int)m_aItems.size() - 1)
			{
				if (getActiveItem())
					getActiveItem()->NotifyOnDeactivate();
				m_iActiveItemIndex = std::min((int)m_aItems.size() - 1, m_iActiveItemIndex + page_size);
				DeselectAllInternal();
				m_aItems[(size_t)m_iActiveItemIndex]->setSelectedInternal(true);
				if (getActiveItem())
					getActiveItem()->NotifyOnActivate();
				ScrollToItem(m_iActiveItemIndex);
				Repaint(false);
			}
		}

		void CCustomListBox::ProcessKeySpace()
		{
			if (m_iActiveItemIndex >= 0)
			{
				if (!m_aItems[(size_t)m_iActiveItemIndex]->getSelectedInternal() && !m_bAllowMultiSelect)
				{
					DeselectAllInternal();
					m_aItems[(size_t)m_iActiveItemIndex]->setSelectedInternal(true);
				}
				else
					m_aItems[(size_t)m_iActiveItemIndex]->setSelectedInternal(!m_aItems[(size_t)m_iActiveItemIndex]->getSelectedInternal());
				Repaint(false);
			}
		}

		void CCustomListBox::ProcessKeyReturn()
		{
			if (m_iActiveItemIndex >= 0)
				m_aItems[m_iActiveItemIndex]->NotifyOnClick();
		}

		void CCustomListBox::ProcessKeyRight(const bool shift)
		{
			int cols, rows, col{ -1 }, row{ 0 };
			GridSize(cols, rows);
			if (m_iActiveItemIndex >= 0)
				ItemIndexToGrid(m_iActiveItemIndex, col, row);
			int last{ std::min((col + 1) * rows + row, (int)m_aItems.size() - 1) };
			if (shift && m_bAllowMultiSelect && m_aItems.size() > 1 && m_iActiveItemIndex < last)
			{
				if (getActiveItem())
					getActiveItem()->NotifyOnDeactivate();
				do
				{
					m_iActiveItemIndex++;
					if (!m_aItems[(size_t)m_iActiveItemIndex]->getSelectedInternal())
						m_aItems[(size_t)m_iActiveItemIndex]->setSelectedInternal(!m_aItems[(size_t)m_iActiveItemIndex]->getSelectedInternal());
					else
						m_aItems[(size_t)m_iActiveItemIndex - 1]->setSelectedInternal(false);
				} while (m_iActiveItemIndex < last);
				if (getActiveItem())
					getActiveItem()->NotifyOnActivate();
				ScrollToItem(m_iActiveItemIndex);
				Repaint(false);
			}
			else if (m_iActiveItemIndex != last)
			{
				if (getActiveItem())
					getActiveItem()->NotifyOnDeactivate();
				m_iActiveItemIndex = last;
				DeselectAllInternal();
				m_aItems[(size_t)m_iActiveItemIndex]->setSelectedInternal(true);
				if (getActiveItem())
					getActiveItem()->NotifyOnActivate();
				ScrollToItem(m_iActiveItemIndex);
				Repaint(false);
			}
		}

		void CCustomListBox::ProcessKeyLeft(const bool shift)
		{
			int cols, rows;
			GridSize(cols, rows);
			int col{ cols }, row{ rows };
			if (m_iActiveItemIndex >= 0)
				ItemIndexToGrid(m_iActiveItemIndex, col, row);
			else
			{
				ItemIndexToGrid((int)m_aItems.size() - 1, col, row);
				col++;
			}
			int last{ std::max((col - 1) * rows + row, 0) };
			if (shift && m_bAllowMultiSelect && m_aItems.size() > 0 && m_iActiveItemIndex > 0)
			{
				if (getActiveItem())
					getActiveItem()->NotifyOnDeactivate();
				do
				{
					m_iActiveItemIndex--;
					if (!m_aItems[(size_t)m_iActiveItemIndex]->getSelectedInternal())
						m_aItems[(size_t)m_iActiveItemIndex]->setSelectedInternal(!m_aItems[(size_t)m_iActiveItemIndex]->getSelectedInternal());
					else
						m_aItems[(size_t)m_iActiveItemIndex + 1]->setSelectedInternal(false);
				} while (m_iActiveItemIndex > last);
				if (getActiveItem())
					getActiveItem()->NotifyOnActivate();
				ScrollToItem(m_iActiveItemIndex);
				Repaint(false);
			}
			else if (m_iActiveItemIndex != last)
			{
				if (getActiveItem())
					getActiveItem()->NotifyOnDeactivate();
				m_iActiveItemIndex = last;
				DeselectAllInternal();
				m_aItems[(size_t)m_iActiveItemIndex]->setSelectedInternal(true);
				if (getActiveItem())
					getActiveItem()->NotifyOnActivate();
				ScrollToItem(m_iActiveItemIndex);
				Repaint(false);
			}
		}

		void CCustomListBox::ProcessSearch()
		{
			// Shoudl be overwriten in derived class to perform correct search
		}

		void CCustomListBox::ProcessMouseMove(const int x, const int y)
		{
			if (m_iHoverItemIndex >= 0)
			{
				if (m_iActiveItemIndex < 0)
					m_iActiveItemIndex = m_iHoverItemIndex;
				DeselectAllInternal();
				if (m_bAllowMultiSelect)
					SelectRange(m_iHoverItemIndex, m_iActiveItemIndex);
				else
				{
					getHoveredItem()->setSelectedInternal(true);
					m_iActiveItemIndex = m_iHoverItemIndex;
				}
				Repaint(false);
			}
		}

		void CCustomListBox::ProcessTimer()
		{
			if (m_bMouseDown)
			{
				int x, y, col, row;
				if (m_pForm->getWindow()->getCursorPosition(x, y) && PosToGrid(x, y, col, row))
				{
					APP_RECT client = getClientRect();
					if (getHScrollBar()->getVisible())
						client.Bottom = getHScrollBar()->getTop() + getTop();
					if (getVScrollBar()->getVisible())
					{
						client.Right = getVScrollBar()->getLeft() + getLeft();
						if (getVScrollBar()->getBoxShadow() && getVScrollBar()->getBoxShadowShiftX() - (int)getVScrollBar()->getBoxShadowRadius() < 0)
							client.Right -= -getVScrollBar()->getBoxShadowShiftX() + (int)getVScrollBar()->getBoxShadowRadius();
					}
					bool handled{ false };
					if (client.IsValid() && !client.IsEmpty())
					{
						client = ClientToForm(client);
						int cols, rows;
						GridSize(cols, rows);
						if (getVScrollBar()->getEnabled())
						{
							int tcol{ col };
							if (tcol < 0)
								tcol = 0;
							else if (tcol > cols)
								tcol = cols;
							if (y < client.Top)
							{
								int trow{ std::max(0, row) };
								int index{ tcol * rows + trow };
								if (index < (int)m_aItems.size() - 1)
								{
									DeselectAllInternal();
									if (m_bAllowMultiSelect)
										SelectRange(index, m_iActiveItemIndex);
									else
									{
										m_aItems[(size_t)index]->setSelectedInternal(true);
										m_iActiveItemIndex = index;
									}
									ScrollToItem(index);
									Repaint(false);
								}
								else
									getVScrollBar()->setScroll(getVScrollBar()->getScroll() - getVScrollBar()->getDeltaScroll());
								handled = true;
							}
							else if (y > client.Bottom)
							{
								int trow{ std::min(rows - 1, row) };
								int index{ std::min(std::min(tcol * rows + trow, (tcol + 1) * rows - 1), (int)m_aItems.size() - 1) };
								DeselectAllInternal();
								if (m_bAllowMultiSelect)
									SelectRange(index, m_iActiveItemIndex);
								else
								{
									m_aItems[(size_t)index]->setSelectedInternal(true);
									m_iActiveItemIndex = index;
								}
								ScrollToItem(index);
								Repaint(false);
								handled = true;
							}
						}
						if (!handled && getHScrollBar()->getEnabled())
						{
							int trow{ row };
							if (trow < 0)
								trow = 0;
							else if (trow > rows)
								trow = rows;
							if (x < client.Left)
							{
								int tcol{ std::max(0, col) };
								int index{ tcol * rows + trow };
								if (index < (int)m_aItems.size() - 1)
								{
									DeselectAllInternal();
									if (m_bAllowMultiSelect)
										SelectRange(index, m_iActiveItemIndex);
									else
									{
										m_aItems[(size_t)index]->setSelectedInternal(true);
										m_iActiveItemIndex = index;
									}
									ScrollToItem(index);
									Repaint(false);
								}
								else
									getHScrollBar()->setScroll(getHScrollBar()->getScroll() - getHScrollBar()->getDeltaScroll());
							}
							else if (x > client.Right)
							{
								int tcol{ std::min(cols - 1, col) };
								int index{ std::min(std::min(tcol * rows + trow, (tcol + 1) * rows - 1), (int)m_aItems.size() - 1) };
								DeselectAllInternal();
								if (m_bAllowMultiSelect)
									SelectRange(index, m_iActiveItemIndex);
								else
								{
									m_aItems[(size_t)index]->setSelectedInternal(true);
									m_iActiveItemIndex = index;
								}
								ScrollToItem(index);
								Repaint(false);
							}
						}
					}
				}
			}
		}
	#pragma endregion

	#pragma region Paint
		void CCustomListBox::PaintBoxShadow(APP_RECT clip)
		{
			if (m_bBoxShadow)
			{
				STATE state{ getState() };
				if (m_aBoxShadowColor[state].getAlpha() > 0)
					m_pForm->getPresenter()->BoxBlur(m_aBoxShadowColor[state], m_sBoxShadowShift.X, m_sBoxShadowShift.Y, m_iBoxShadowRadius, clip, ClientToForm(getRect()), { 0, 0, 0, 0 }, 0,
						nullptr, nullptr, true);
			}
		}

		void CCustomListBox::PaintBackground(APP_RECT clip)
		{
			STATE state{ getState() };
			math::RECTANGLE<size_t> borders{ m_iBorderWidth, m_iBorderWidth, m_iBorderWidth, m_iBorderWidth };
			APP_COLOR colors[graphics::bplBottom + 1];
			colors[graphics::bplInside] = m_aBackgroundColor[state];
			colors[graphics::bplLeft] = m_aBorderColor[state];
			colors[graphics::bplTop] = m_aBorderColor[state];
			colors[graphics::bplRight] = m_aBorderColor[state];
			colors[graphics::bplBottom] = m_aBorderColor[state];
			m_pForm->getPresenter()->MultiFillRect(colors, clip, ClientToForm(getRect()), borders, { 0, 0, 0, 0 }, 0, nullptr, nullptr, true);
		}

		void CCustomListBox::PaintItems(APP_RECT clip)
		{
			if (m_aItems.size() > 0)
			{
				APP_RECT client = ClientToForm(getClientRect());
				if (getHScrollBar()->getVisible())
					client.Bottom -= getHScrollBar()->getHeight();
				if (getVScrollBar()->getVisible())
					client.Right -= getVScrollBar()->getWidth();
				if (client.IsValid())
				{
					clip *= client;
					int x1, x2, y1, y2;
					if (PosToGrid(client.Left, client.Top, x1, y1) && PosToGrid(client.Right - 1, client.Bottom - 1, x2, y2))
					{
						int cols, rows;
						GridSize(cols, rows);
						int dx{ getHScrollBar()->getEnabled() ? getHScrollBar()->getScroll() : 0 };
						int dy{ getVScrollBar()->getEnabled() ? getVScrollBar()->getScroll() : 0 };
						for (int y = y1; y <= y2; y++)
							for (int x = x1; x <= x2; x++)
							{
								int i{ x * rows + y };
								if (i >= 0 && i < (int)m_aItems.size())
									m_aItems[i]->Paint(clip, {
										client.Left + x * (int)m_sItemSize.X - dx, client.Top + y * (int)m_sItemSize.Y - dy,
										client.Left + (x + 1) * (int)m_sItemSize.X - dx, client.Top + (y + 1) * (int)m_sItemSize.Y - dy });
							}
					}
				}
			}
		}

		void CCustomListBox::PaintScrollbarsCorner(APP_RECT clip)
		{
			if (getVScrollBar()->getVisible() && getHScrollBar()->getVisible())
			{
				APP_POINT p = ClientToForm(getPosition());
				APP_RECT rect{
					getVScrollBar()->getLeft() + p.X,
					getVScrollBar()->getTop() + getVScrollBar()->getHeight() + p.Y,
					getVScrollBar()->getLeft() + getVScrollBar()->getWidth() + p.X,
					getHScrollBar()->getTop() + getHScrollBar()->getHeight() + p.Y
				};
				m_pForm->getPresenter()->FillRect({ 240, 240, 240, 255 }, clip, rect, rect, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, 0, graphics::bplInside, nullptr, nullptr, true);
			}
		}
	#pragma endregion
	}
}