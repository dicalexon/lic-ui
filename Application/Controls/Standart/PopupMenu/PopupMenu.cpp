// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#include "PopupMenu.h"
#include "..\..\..\Presenter.h"
#include "..\..\..\DefaultStyle.h"
#include "..\..\..\Style.h"
#include "..\..\..\StyleSkin.h"
#include "..\..\..\StyleImage.h"
#include "..\..\..\ImageManager.h"

namespace licui
{
	namespace application
	{
#pragma region Constructors and destructor
		CPopupMenu::CPopupMenu() :CBaseBlock(),
			m_sSize{ {0, 0}, {0, 0}, 0, 0, 0, 0, false, 0 },
			m_iScroll{ 0 },
			m_iScrollHeight{ 10 },
			m_iScrollDelta{ 5 },
			m_pImageList{ nullptr },
			m_iActiveItemIndex{ -1 },
			m_iRightArrowWidth{ 10 },
			m_bUpdating{ false },
			m_bMouseOverUpArrow{ false },
			m_bMouseOverDownArrow{ false },
			m_bMouseDownOnUpArrow{ false },
			m_bMouseDownOnDownArrow{ false },
			m_hScrollTimer{ 0 },
			m_sSubmenuShift{ -5, -1 },
			m_fOnClick{ nullptr },
			m_bShowImages{ true }
		{
			m_sClassName = L"CPopupMenu";
			m_bAcceptForm = true;
			m_bVisible = false;
			m_sInitialRect = { 0, 0, 10, 10 };
			FillBlock();
		}

		CPopupMenu::CPopupMenu(CForm *form) :CPopupMenu()
		{
			setForm(form);
		}

		void CPopupMenu::FillBlock()
		{
			m_sBlock.BorderWidth[0] = 1;
			m_sBlock.BorderWidth[1] = 1;
			m_sBlock.BorderWidth[2] = 1;
			m_sBlock.BorderWidth[3] = 1;
			m_sBlock.BorderColor[0] = { 152, 152, 152, 255 };
			m_sBlock.BorderColor[1] = { 152, 152, 152, 255 };
			m_sBlock.BorderColor[2] = { 152, 152, 152, 255 };
			m_sBlock.BorderColor[3] = { 152, 152, 152, 255 };
			m_sBlock.BackgroundColor = { 241, 241, 241, 255 };
			m_sBlock.StyleName = L"";
			m_sBlock.BoxShadow = true;
			m_sBlock.BoxShadowColor = { 152, 152, 152, 200 };
			m_sBlock.BoxShadowShift = { 2, 2 };
			m_sBlock.BoxShadowRadius = 3;
		}
#pragma endregion

#pragma region Getters
		CBaseBlock::BLOCK *CPopupMenu::getBlock()
		{
			return &m_sBlock;
		}

		APP_RECT CPopupMenu::getVisibleRect()
		{
			return ClientToForm(getRenderRect());
		}

		APP_RECT CPopupMenu::getClientRect()
		{
			APP_RECT result = CBaseBlock::getClientRect();
			if (m_sSize.HaveScroll)
			{
				result.Top += m_iScrollHeight;
				result.Bottom -= (int)m_iScrollHeight;
				if (!result.IsValid())
				{
					result.Right = result.Left;
					result.Bottom = result.Top;
				}
			}
			return result;
		}

		CPopupMenuItem *CPopupMenu::getParentMenuItem()
		{
			return (CPopupMenuItem*)getParent();
		}

		size_t CPopupMenu::getMenuItemCount() const
		{
			return getControlCount();
		}

		CPopupMenuItem *CPopupMenu::getMenuItem(const int index)
		{
			return (CPopupMenuItem*)getControl(index);
		}

		CImageList *CPopupMenu::getImageList()
		{
			return m_pImageList;
		}

		CPopupMenuItem *CPopupMenu::getActiveMenuItem()
		{
			if (m_iActiveItemIndex >= 0)
				return (CPopupMenuItem*)getControl(m_iActiveItemIndex);
			return nullptr;
		}

		bool CPopupMenu::getShowImages() const
		{
			return m_bShowImages;
		}

		int CPopupMenu::getActiveMenuItemIndex() const
		{
			return m_iActiveItemIndex;
		}

		bool CPopupMenu::getHaveScroll() const
		{
			return m_sSize.HaveScroll;
		}

		size_t CPopupMenu::getScroll() const
		{
			return m_iScroll;
		}

		size_t CPopupMenu::getScrollMax() const
		{
			return m_sSize.ScrollMax;
		}

		size_t CPopupMenu::getScrollHeight() const
		{
			return m_iScrollHeight;
		}

		size_t CPopupMenu::getScrollDelta() const
		{
			return m_iScrollDelta;
		}

		size_t CPopupMenu::getRightArrowWidth() const
		{
			return m_iRightArrowWidth;
		}

		APP_POINT CPopupMenu::getSubmenuShift() const
		{
			return m_sSubmenuShift;
		}

		int CPopupMenu::getSubmenuShiftX() const
		{
			return m_sSubmenuShift.X;
		}

		int CPopupMenu::getSubmenuShiftY() const
		{
			return m_sSubmenuShift.Y;
		}

		CPopupMenu *CPopupMenu::getRootMenu()
		{
			if (getParentMenuItem())
				return getParentMenuItem()->getRootMenu();
			return this;
		}

		CPopupMenu::FOnClick CPopupMenu::getOnClick() const
		{
			return m_fOnClick;
		}
#pragma endregion

#pragma region Setters
		CPopupMenu *CPopupMenu::setParentMenuItem(CPopupMenuItem *value)
		{
			if (value != getParentMenuItem())
			{
				if (getParentMenuItem())
					getParentMenuItem()->setMenu(nullptr);
				if (value)
					value->setMenu(this);
			}
			return this;
		}

		CPopupMenu *CPopupMenu::setImageList(CImageList *value)
		{
			if (value != m_pImageList)
			{
				m_pImageList = value;
				Repaint(true);
			}
			return this;
		}

		CPopupMenu *CPopupMenu::setShowImages(const bool value)
		{
			if (value != m_bShowImages)
			{
				m_bShowImages = value;
				if (m_pImageList)
					Repaint(true);
			}
			return this;
		}

		CPopupMenu *CPopupMenu::setActiveMenuItemIndex(int value)
		{
			if (value < -1)
				value = -1;
			else if (value >= (int)getMenuItemCount())
				value = - 1;
			if (value >= 0 && (!getMenuItem(value)->getEnabled() || getMenuItem(value)->getIsSeparator()))
				return this;
			if (value != m_iActiveItemIndex)
			{
				bool show{ getMenuItem(m_iActiveItemIndex) && getMenuItem(m_iActiveItemIndex)->getMenu() && getMenuItem(m_iActiveItemIndex)->getMenu()->getVisible() };
				if (show)
					getMenuItem(m_iActiveItemIndex)->getMenu()->Hide();
				// Calc new scroll
				bool perform_update{ false };
				if (m_sSize.HaveScroll)
				{
					APP_RECT item_rect = getMenuItem(value)->ClientToForm(getMenuItem(value)->getRect()), rect = ClientToForm(getClientRect());
					if (item_rect.Top < rect.Top)
					{
						m_iScroll = 0;
						for (size_t i = 0; i < (size_t)value; i++)
							m_iScroll += getMenuItem(i)->getHeight();
						perform_update = true;
					}
					else if (item_rect.Bottom > rect.Bottom)
					{
						m_iScroll = 0;
						for (size_t i = 0; i <= (size_t)value; i++)
							m_iScroll += getMenuItem(i)->getHeight();
						m_iScroll -= getClientRect().Height();
						perform_update = true;
					}
				}
				// Update or repaint
				if (perform_update)
				{
					m_iActiveItemIndex = value;
					Update();
				}
				else
				{
					int old{ m_iActiveItemIndex };
					m_iActiveItemIndex = value;
					if (m_pForm)
					{
						m_pForm->LockRepaint();
						if (getMenuItem(old))
							getMenuItem(old)->Repaint(false);
						if (getMenuItem(m_iActiveItemIndex))
							getMenuItem(m_iActiveItemIndex)->Repaint(false);
						m_pForm->UnlockRepaint();
					}
				}
				if (show && getMenuItem(m_iActiveItemIndex) && getMenuItem(m_iActiveItemIndex)->getMenu())
				{
					APP_RECT rect = getMenuItem(m_iActiveItemIndex)->getRect();
					getMenuItem(m_iActiveItemIndex)->getMenu()->Show(rect.Width() + m_sSubmenuShift.X, m_sSubmenuShift.Y);
				}
			}
			return this;
		}

		CPopupMenu *CPopupMenu::setScroll(const size_t value)
		{
			if (m_sSize.HaveScroll && value <= m_sSize.ScrollMax && value != m_iScroll)
			{
				m_iScroll = value;
				Update();
			}
			return this;
		}

		CPopupMenu *CPopupMenu::setScrollHeight(const size_t value)
		{
			if (value != m_iScrollHeight)
			{
				m_iScrollHeight = value;
				if (m_sSize.HaveScroll)
					Update();
			}
			return this;
		}

		CPopupMenu *CPopupMenu::setScrollDelta(size_t value)
		{
			if (value < 1)
				value = 1;
			m_iScrollDelta = value;
			return this;
		}

		CPopupMenu *CPopupMenu::setRightArrowWidth(const size_t value)
		{
			if (value != m_iRightArrowWidth)
			{
				m_iRightArrowWidth = value;
				Update();
			}
			return this;
		}

		CPopupMenu *CPopupMenu::setSubmenuShift(const APP_POINT &value)
		{
			if (value != m_sSubmenuShift)
			{
				m_sSubmenuShift = value;
				if (getVisibleWithParents() && getActiveMenuItem() && getActiveMenuItem()->getMenu() && getActiveMenuItem()->getMenu()->getVisible())
					getActiveMenuItem()->getMenu()->Show(getActiveMenuItem()->getWidth() + m_sSubmenuShift.X, m_sSubmenuShift.Y);
			}
			return this;
		}

		CPopupMenu *CPopupMenu::setSubmenuShiftX(const int value)
		{
			if (value != m_sSubmenuShift.X)
			{
				m_sSubmenuShift.X = value;
				if (getVisibleWithParents() && getActiveMenuItem() && getActiveMenuItem()->getMenu() && getActiveMenuItem()->getMenu()->getVisible())
					getActiveMenuItem()->getMenu()->Show(getActiveMenuItem()->getWidth() + m_sSubmenuShift.X, m_sSubmenuShift.Y);
			}
			return this;
		}

		CPopupMenu *CPopupMenu::setSubmenuShiftY(const int value)
		{
			if (value != m_sSubmenuShift.Y)
			{
				m_sSubmenuShift.Y = value;
				if (getVisibleWithParents() && getActiveMenuItem() && getActiveMenuItem()->getMenu() && getActiveMenuItem()->getMenu()->getVisible())
					getActiveMenuItem()->getMenu()->Show(getActiveMenuItem()->getWidth() + m_sSubmenuShift.X, m_sSubmenuShift.Y);
			}
			return this;
		}

		CPopupMenu *CPopupMenu::setOnClick(FOnClick value)
		{
			m_fOnClick = value;
			return this;
		}
#pragma endregion

#pragma region Items
		void CPopupMenu::AddMenuItem(CPopupMenuItem *item)
		{
			if (item)
			{
				if (m_pForm)
					m_pForm->LockRepaint();
				item->m_bVisible = true;
				m_bAcceptControls = true;
				item->m_bAcceptParent = true;
				AddControl(item);
				m_bAcceptControls = false;
				item->m_bAcceptParent = false;
				item->UpdateState();
				Update();
				if (m_pForm)
					m_pForm->UnlockRepaint();
			}
		}

		void CPopupMenu::InsertMenuItem(CPopupMenuItem *item, const size_t before)
		{
			if (item)
				if (before >= getMenuItemCount())
					AddMenuItem(item);
				else
				{
					if (m_pForm)
						m_pForm->LockRepaint();
					item->m_bVisible = true;
					m_bAcceptControls = true;
					item->m_bAcceptParent = true;
					InsertControl(item, before);
					m_bAcceptControls = false;
					item->m_bAcceptParent = false;
					item->UpdateState();
					Update();
					if (m_pForm)
						m_pForm->UnlockRepaint();
				}
		}

		void CPopupMenu::DeleteMenuItem(CPopupMenuItem *item)
		{
			DeleteControl(item);
		}

		void CPopupMenu::DeleteMenuItem(const size_t index)
		{
			DeleteControl(index);
		}

		void CPopupMenu::ClearMenuItems()
		{
			DeleteControls();
		}
#pragma endregion

#pragma region Helpers
		void CPopupMenu::ClearActiveMenuItemIndex()
		{
			m_iActiveItemIndex = -1;
			for (size_t i = 0; i < getMenuItemCount(); i++)
				getMenuItem(i)->ClearActiveMenuItemIndex();
		}

		bool CPopupMenu::HaveMenuItem(CPopupMenuItem *item)
		{
			for (size_t i = 0; i < getMenuItemCount(); i++)
			{
				if (getMenuItem(i) == item)
					return true;
				if (getMenuItem(i)->getMenu() && getMenuItem(i)->getMenu()->HaveMenuItem(item))
					return true;
			}
			return false;
		}

		bool CPopupMenu::ProcessMenuItemOnHover(CPopupMenuItem *item)
		{
			if (!getVisible())
				return false;
			bool result{ false };
			for (size_t i = 0; i < getMenuItemCount(); i++)
				if (getMenuItem(i) == item)
				{
					if (item->getEnabled() && !item->getIsSeparator() && m_iActiveItemIndex != i)
					{
						CPopupMenuItem *old{ getMenuItem(m_iActiveItemIndex) };
						m_iActiveItemIndex = i;
						if (old)
						{
							if (old->getMenu() && old->getMenu()->getVisible())
								old->getMenu()->Hide();
							old->Repaint(false);
						}
						item->Repaint(false);
						if (item->getMenu() && !item->getMenu()->getVisible())
							item->getMenu()->Show(item->getWidth() + m_sSubmenuShift.X, m_sSubmenuShift.Y);
					}
					result = true;
					break;
				}
			for (size_t i = 0; i < getMenuItemCount(); i++)
				if (getMenuItem(i)->getVisible() && getMenuItem(i)->getEnabled() && getMenuItem(i)->getMenu() && getMenuItem(i)->getMenu()->getVisible())
					if (getMenuItem(i)->getMenu()->ProcessMenuItemOnHover(item))
					{
						if (m_iActiveItemIndex != i)
						{
							CPopupMenuItem *old{ getMenuItem(m_iActiveItemIndex) };
							m_iActiveItemIndex = i;
							if (old)
								old->Repaint(false);
							getMenuItem(i)->Repaint(false);
						}
						result = true;
					}
			return result;
		}

		void CPopupMenu::Show(const int x, const int y)
		{
			if (getMenuItemCount() == 0)
				return;
			m_sInitialRect.Left = x;
			m_sInitialRect.Top = y;
			if (m_pForm)
				m_pForm->LockRepaint();
			if (!m_bVisible)
			{
				m_bVisible = true;
				NotifyOnShow();
				m_bCaretVisibleOnShow = false;
				if (!getParentMenuItem() && m_pForm)
				{
					m_pForm->CaptureKeyboard(this);
					m_pForm->CaptureMouse(this);
					if (m_pForm->getWindow())
					{
						m_bCaretVisibleOnShow = m_pForm->getWindow()->IsCaretVisible();
						m_pForm->getWindow()->HideCaret();
					}
				}
			}
			Update();
			if (m_pForm)
				m_pForm->UnlockRepaint();
		}

		void CPopupMenu::Hide()
		{
			setVisible(false);
		}

		void CPopupMenu::CalculateSize()
		{
			// Calculate required size and parts sizes
			m_sSize = { {0, 0}, {0, 0}, 0, 0, 0, 0, false, 0 };
			m_sSize.RequiredSize.X += m_sBlock.BorderWidth[0] + m_sBlock.BorderWidth[2] + m_sBlock.Padding[0] + m_sBlock.Padding[2];
			m_sSize.RequiredSize.Y += m_sBlock.BorderWidth[1] + m_sBlock.BorderWidth[3] + m_sBlock.Padding[1] + m_sBlock.Padding[3];
			for (size_t i = 0; i < getMenuItemCount(); i++)
			{
				CPopupMenuItem::MENU_ITEM_SIZE size = getMenuItem(i)->CalculateSize();
				m_sSize.WidthCaptions = std::max(m_sSize.WidthCaptions, size.WidthCaption);
				if (size.WidthShortcut > 0)
					m_sSize.WidthShortcuts = std::max(m_sSize.WidthShortcuts, size.WidthShortcut);
				if (!getMenuItem(i)->getIsSeparator() && getMenuItem(i)->getMenu())
					m_sSize.WidthArrows = std::max(m_sSize.WidthArrows, m_iRightArrowWidth + getMenuItem(i)->m_sMarginArrow.Left + getMenuItem(i)->m_sMarginArrow.Right);
				m_sSize.RequiredSize.Y += size.Height;
				if (m_bShowImages && !getMenuItem(i)->getIsSeparator())
					m_sSize.WidthImages = std::max(m_sSize.WidthImages, size.Height);
			}
			m_sSize.RequiredSize.X += m_sSize.WidthImages + m_sSize.WidthCaptions + m_sSize.WidthShortcuts + m_sSize.WidthArrows;
			// Calculate real size(adjust by constraints)
			m_sSize.Size = m_sSize.RequiredSize;
			if (m_sConstraints.Left > 0)
				m_sSize.Size.X = std::max(m_sSize.Size.X, (int)m_sConstraints.Left);
			if (m_sConstraints.Top > 0)
				m_sSize.Size.Y = std::max(m_sSize.Size.Y, (int)m_sConstraints.Top);
			if (m_sConstraints.Right > 0)
				m_sSize.Size.X = std::min(m_sSize.Size.X, (int)m_sConstraints.Right);
			if (m_sConstraints.Bottom > 0)
				m_sSize.Size.Y = std::min(m_sSize.Size.Y, (int)m_sConstraints.Bottom);
			// Calculate scrolling
			if (m_sSize.Size.Y < m_sSize.RequiredSize.Y)
			{
				m_sSize.HaveScroll = true;
				m_sSize.ScrollMax = (size_t)((int)m_sSize.RequiredSize.Y - (int)m_sSize.Size.Y + 2 * (int)m_iScrollHeight);
			}
			else
			{
				m_sSize.HaveScroll = false;
				m_sSize.ScrollMax = 0;
			}
			// Calculate parts
			size_t w{ (size_t)std::max(0, m_sSize.Size.X - (int)m_sBlock.BorderWidth[0] - (int)m_sBlock.BorderWidth[2] - (int)m_sBlock.Padding[0] - (int)m_sBlock.Padding[2]) };
			m_sSize.WidthImages = std::min(m_sSize.WidthImages, w);
			w -= m_sSize.WidthImages;
			m_sSize.WidthArrows = std::min(m_sSize.WidthArrows, w);
			w -= m_sSize.WidthArrows;
			m_sSize.WidthShortcuts = std::min(m_sSize.WidthShortcuts, w);
			w -= m_sSize.WidthShortcuts;
			m_sSize.WidthCaptions = w;
		}

		void CPopupMenu::UpdateRect()
		{
			CalculateSize();
			m_sInitialRect.Right = m_sInitialRect.Left + m_sSize.Size.X;
			m_sInitialRect.Bottom = m_sInitialRect.Top + m_sSize.Size.Y;
			CControl::UpdateRect();
		}

		void CPopupMenu::Update()
		{
			if (!m_bUpdating)
			{
				if (!getVisibleWithParents() || !m_pForm)
					return;
				m_pForm->LockRepaint();
				Repaint(true);
				m_bUpdating = true;
				UpdateRect();
				UpdateControls();
				Repaint(true);
				m_bUpdating = false;
				m_pForm->UnlockRepaint();
			}
		}

		void CPopupMenu::ActivateSubmenu()
		{
			CPopupMenu *menu{ getActiveMenuItem()->getMenu() };
			if (!menu->getVisible())
			{
				APP_RECT rect = getActiveMenuItem()->getRect();
				menu->Show(rect.Width() + m_sSubmenuShift.X, m_sSubmenuShift.Y);
			}
			if (!menu->getActiveMenuItem())
			{
				int index{ 0 };
				while (index < (int)menu->getMenuItemCount() && (menu->getMenuItem(index)->getIsSeparator() || !menu->getMenuItem(index)->getEnabled()))
					index++;
				if (menu->getMenuItem(index) && !menu->getMenuItem(index)->getIsSeparator() && menu->getMenuItem(index)->getEnabled())
					menu->setActiveMenuItemIndex(index);
			}
		}

		APP_RECT CPopupMenu::CalculateScrollUpRect()
		{
			APP_RECT result = CBaseBlock::getClientRect();
			result.Bottom = result.Top + (int)m_iScrollHeight;
			if (!result.IsValid())
				result.Bottom = result.Top;
			return result;
		}

		APP_RECT CPopupMenu::CalculateScrollDownRect()
		{
			APP_RECT result = CBaseBlock::getClientRect();
			result.Top = result.Bottom - (int)m_iScrollHeight;
			if (!result.IsValid())
				result.Top = result.Bottom;
			return result;
		}

		void CPopupMenu::DoOnScrollTimer(void *param)
		{
			CPopupMenu *self{ (CPopupMenu*)param };
			if (self->getVisibleWithParents() && (self->m_bMouseDownOnUpArrow || self->m_bMouseDownOnDownArrow) && self->m_sSize.HaveScroll)
			{
				if (self->m_bMouseDownOnUpArrow)
					self->m_iScroll = std::max(0, (int)self->m_iScroll - (int)self->m_iScrollDelta);
				else
					self->m_iScroll = std::min(self->m_sSize.ScrollMax, self->m_iScroll + self->m_iScrollDelta);
				self->Update();
			}
			else
			{
				self->m_pForm->DeleteTimer(self->m_hScrollTimer);
				self->m_hScrollTimer = 0;
				self->m_bMouseDownOnUpArrow = self->m_bMouseDownOnDownArrow = false;
			}
		}

		bool CPopupMenu::TestMenuRect(const int x, const int y)
		{
			if (!getVisible())
				return false;
			APP_RECT rect = ClientToForm(getRect());
			if (x >= rect.Left && x < rect.Right && y >= rect.Top && y < rect.Bottom)
				return true;
			for (size_t index = 0; index < getMenuItemCount(); index++)
				if (getMenuItem(index)->getMenu() && getMenuItem(index)->getMenu()->TestMenuRect(x, y))
					return true;
			return false;
		}

		void CPopupMenu::UpdateControls()
		{
			APP_RECT rect = getClientRect();
			for (size_t i = 0; i < getMenuItemCount(); i++)
			{
				CPopupMenuItem::MENU_ITEM_SIZE size = getMenuItem(i)->CalculateSize();
				getMenuItem(i)->setRect({ rect.Left - getRect().Left, rect.Top - getRect().Top - (int)m_iScroll, rect.Right - getRect().Left, rect.Top - getRect().Top + (int)size.Height - (int)m_iScroll });
				rect.Top += size.Height;
			}
		}
#pragma endregion

#pragma region Notifications
		void CPopupMenu::NotifyOnHide()
		{
			ClearActiveMenuItemIndex();
			if (m_bCaretVisibleOnShow && !getParentMenuItem() && m_pForm && m_pForm->getWindow())
				m_pForm->getWindow()->ShowCaret();
		}

		void CPopupMenu::NotifyOnDetachControl(CControl *control)
		{
			Update();
			CBaseBlock::NotifyOnDetachControl(control);
		}

		void CPopupMenu::NotifyOnBeforeDetachComponentFromForm(CComponent *component)
		{
			CBaseBlock::NotifyOnBeforeDetachComponentFromForm(component);
			if (component == m_pImageList)
			{
				m_pImageList = nullptr;
				if (getVisibleWithParents())
					for (size_t i = 0; i < getMenuItemCount(); i++)
						getMenuItem(i)->Repaint(false);
			}
		}

		void CPopupMenu::NotifyOnBeforeDetachFromForm()
		{
			if (m_hScrollTimer)
			{
				m_pForm->DeleteTimer(m_hScrollTimer);
				m_hScrollTimer = 0;
			}
			CBaseBlock::NotifyOnBeforeDetachFromForm();
		}

		void CPopupMenu::NotifyOnMouseHover()
		{
			if (m_sSize.HaveScroll)
				Repaint(false);
			CBaseBlock::NotifyOnMouseHover();
		}

		void CPopupMenu::NotifyOnMouseLeave()
		{
			if (m_sSize.HaveScroll)
				Repaint(false);
			CBaseBlock::NotifyOnMouseLeave();
		}

		void CPopupMenu::NotifyOnKillFocus()
		{
			Hide();
			CBaseBlock::NotifyOnKillFocus();
		}

		void CPopupMenu::NotifyOnKillCaptureKeyboard()
		{
			Hide();
			CBaseBlock::NotifyOnKillCaptureKeyboard();
		}

		void CPopupMenu::NotifyOnKillCaptureMouse()
		{
			m_pForm->getWindow()->ReleaseMouseCapture();
			Hide();
			CBaseBlock::NotifyOnKillCaptureMouse();
		}

		void CPopupMenu::NotifyOnSetCaptureMouse()
		{
			m_pForm->getWindow()->CaptureMouse();
			CBaseBlock::NotifyOnSetCaptureMouse();
		}

		bool CPopupMenu::NotifyOnKeyDown(const IWindow::KEY key)
		{
			switch (key)
			{
			case IWindow::keyUp:
				ProcessKeyUp();
				break;
			case IWindow::keyDown:
				ProcessKeyDown();
				break;
			case IWindow::keyLeft:
				ProcessKeyLeft();
				break;
			case IWindow::keyRight:
				ProcessKeyRight();
				break;
			case IWindow::keyHome:
				ProcessKeyHome();
				break;
			case IWindow::keyEnd:
				ProcessKeyEnd();
				break;
			case IWindow::keyEscape:
				ProcessKeyEscape();
				break;
			case IWindow::keyReturn:
				ProcessKeyReturn();
				break;
			case IWindow::keySpace:
				ProcessKeySpace();
				break;
			default:
				bool ctrl, alt, shift;
				m_pForm->getWindow()->getControlKeys(ctrl, shift, alt);
				ProcessShortcut(key, ctrl, alt, shift);
				break;
			}
			CBaseBlock::NotifyOnKeyDown(key);
			return true;
		}

		bool CPopupMenu::NotifyOnKeyUp(const IWindow::KEY key)
		{
			CBaseBlock::NotifyOnKeyUp(key);
			return true;
		}

		bool CPopupMenu::NotifyOnChar(const wchar_t chr)
		{
			CBaseBlock::NotifyOnChar(chr);
			return true;
		}

		bool CPopupMenu::NotifyOnDeadChar(const wchar_t chr)
		{
			CBaseBlock::NotifyOnDeadChar(chr);
			return true;
		}

		bool CPopupMenu::NotifyOnSysKeyDown(const IWindow::KEY key)
		{
			CBaseBlock::NotifyOnSysKeyDown(key);
			return true;
		}

		bool CPopupMenu::NotifyOnSysKeyUp(const IWindow::KEY key)
		{
			CBaseBlock::NotifyOnSysKeyUp(key);
			return true;
		}

		bool CPopupMenu::NotifyOnSysChar(const wchar_t chr)
		{
			CBaseBlock::NotifyOnSysChar(chr);
			return true;
		}

		bool CPopupMenu::NotifyOnSysDeadChar(const wchar_t chr)
		{
			CBaseBlock::NotifyOnSysDeadChar(chr);
			return true;
		}

		bool CPopupMenu::NotifyOnMouseMove(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			if (m_pForm->getHoveredControl() == this && m_sSize.HaveScroll)
			{
				APP_RECT up = ClientToForm(CalculateScrollUpRect()), down = ClientToForm(CalculateScrollDownRect());
				if (x >= up.Left && x < up.Right && y >= up.Top && y < up.Bottom)
				{
					if (m_bMouseOverDownArrow)
					{
						m_bMouseOverDownArrow = false;
						Repaint(false);
					}
					if (!m_bMouseOverUpArrow)
					{
						m_bMouseOverUpArrow = true;
						Repaint(false);
					}
				}
				else if (x >= down.Left && x < down.Right && y >= down.Top && y < down.Bottom)
				{
					if (!m_bMouseOverDownArrow)
					{
						m_bMouseOverDownArrow = true;
						Repaint(false);
					}
					if (m_bMouseOverUpArrow)
					{
						m_bMouseOverUpArrow = false;
						Repaint(false);
					}
				}
				else if (m_bMouseOverUpArrow || m_bMouseOverDownArrow)
				{
					m_bMouseOverUpArrow = false;
					m_bMouseOverDownArrow = false;
					Repaint(false);
				}
			}
			CBaseBlock::NotifyOnMouseMove(x, y, ctrl, left, middle, right, shift);
			return true;
		}

		bool CPopupMenu::NotifyOnLeftMouseButtonDown(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			if (m_sSize.HaveScroll && !m_bMouseDownOnUpArrow && !m_bMouseDownOnDownArrow && m_pForm->getHoveredControl() == this && !m_hScrollTimer)
			{
				APP_RECT up = ClientToForm(CalculateScrollUpRect()), down = ClientToForm(CalculateScrollDownRect());
				if (x >= up.Left && x < up.Right && y >= up.Top && y < up.Bottom)
					m_bMouseDownOnUpArrow = true;
				else if (x >= down.Left && x < down.Right && y >= down.Top && y < down.Bottom)
					m_bMouseDownOnDownArrow = true;
				if (m_bMouseDownOnUpArrow || m_bMouseDownOnDownArrow)
				{
					if (m_bMouseDownOnUpArrow)
						m_iScroll = std::max(0, (int)m_iScroll - (int)m_iScrollDelta);
					else
						m_iScroll = std::min(m_sSize.ScrollMax, m_iScroll + m_iScrollDelta);
					m_hScrollTimer = m_pForm->AddTimer(DoOnScrollTimer, this, 250);
					Update();
				}
			}
			else
				if (!getRootMenu()->TestMenuRect(x, y))
					Hide();
			return CBaseBlock::NotifyOnLeftMouseButtonDown(x, y, ctrl, left, middle, right, shift);
		}

		bool CPopupMenu::NotifyOnLeftMouseButtonUp(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			if (m_bMouseDownOnUpArrow || m_bMouseDownOnDownArrow || m_hScrollTimer)
			{
				m_bMouseDownOnUpArrow = m_bMouseDownOnDownArrow = false;
				if (m_hScrollTimer)
				{
					m_pForm->DeleteTimer(m_hScrollTimer);
					m_hScrollTimer = 0;
				}
				Repaint(false);
			}
			return CBaseBlock::NotifyOnLeftMouseButtonUp(x, y, ctrl, left, middle, right, shift);
		}

		bool CPopupMenu::NotifyOnLeftMouseButtonDoubleClick(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			CBaseBlock::NotifyOnLeftMouseButtonDoubleClick(x, y, ctrl, left, middle, right, shift);
			return true;
		}

		bool CPopupMenu::NotifyOnRightMouseButtonDown(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			CBaseBlock::NotifyOnRightMouseButtonDown(x, y, ctrl, left, middle, right, shift);
			return true;
		}

		bool CPopupMenu::NotifyOnRightMouseButtonUp(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			CBaseBlock::NotifyOnRightMouseButtonUp(x, y, ctrl, left, middle, right, shift);
			return true;
		}

		bool CPopupMenu::NotifyOnRightMouseButtonDoubleClick(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			CBaseBlock::NotifyOnRightMouseButtonDoubleClick(x, y, ctrl, left, middle, right, shift);
			return true;
		}

		bool CPopupMenu::NotifyOnMiddleMouseButtonDown(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			CBaseBlock::NotifyOnMiddleMouseButtonDown(x, y, ctrl, left, middle, right, shift);
			return true;
		}

		bool CPopupMenu::NotifyOnMiddleMouseButtonUp(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			CBaseBlock::NotifyOnMiddleMouseButtonUp(x, y, ctrl, left, middle, right, shift);
			return true;
		}

		bool CPopupMenu::NotifyOnMiddleMouseButtonDoubleClick(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			CBaseBlock::NotifyOnMiddleMouseButtonDoubleClick(x, y, ctrl, left, middle, right, shift);
			return true;
		}

		bool CPopupMenu::NotifyOnMouseVerticalWheel(const int x, const int y, const int delta, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			if (m_sSize.HaveScroll)
			{
				APP_RECT rect = ClientToForm(getRect());
				if (x >= rect.Left && x < rect.Right && y >= rect.Top && y < rect.Bottom)
				{
					if (delta > 0)
						m_iScroll = (size_t)std::max(0, (int)m_iScroll - (int)m_iScrollDelta);
					else
						m_iScroll = std::min(m_sSize.ScrollMax, m_iScroll + m_iScrollDelta);
					Update();
				}
			}
			CBaseBlock::NotifyOnMouseVerticalWheel(x, y, delta, ctrl, left, middle, right, shift);
			return true;
		}

		bool CPopupMenu::NotifyOnMouseHorizontalWheel(const int x, const int y, const int delta, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			CBaseBlock::NotifyOnMouseHorizontalWheel(x, y, delta, ctrl, left, middle, right, shift);
			return true;
		}

		void CPopupMenu::NotifyOnPaint(APP_RECT clip)
		{
			DoRender(L"", clip);
			RenderUpArrow(clip);
			RenderDownArrow(clip);
			CBaseBlock::NotifyOnPaint(clip);
		}

		void CPopupMenu::NotifyOnClick(CPopupMenuItem *sender)
		{
			if (sender->m_fOnClick)
				sender->m_fOnClick(sender, sender->getCallbackParam());
			if (m_fOnClick)
				m_fOnClick(getCallbackParam(), sender);
		}
#pragma endregion

#pragma region Process events
		void CPopupMenu::ProcessKeyUp()
		{
			CPopupMenuItem *item{ getActiveMenuItem() };
			if (item && !item->getIsSeparator() && item->getEnabled() && item->getMenu() && item->getMenu()->getVisible() && item->getMenu()->getActiveMenuItem())
			{
				item->getMenu()->ProcessKeyUp();
				return;
			}
			int index{ m_iActiveItemIndex - 1};
			while (index >= 0 && getMenuItem(index) && (getMenuItem(index)->getIsSeparator() || !getMenuItem(index)->getEnabled()))
				index--;
			if (!getMenuItem(index))
			{
				index = getMenuItemCount() - 1;
				while (index > m_iActiveItemIndex && (getMenuItem(index)->getIsSeparator() || !getMenuItem(index)->getEnabled()))
					index--;
			}
			if (!getMenuItem(index) || getMenuItem(index)->getIsSeparator() || !getMenuItem(index)->getEnabled())
				index = -1;
			setActiveMenuItemIndex(index);
		}

		void CPopupMenu::ProcessKeyDown()
		{
			CPopupMenuItem *item{ getActiveMenuItem() };
			if (item && !item->getIsSeparator() && item->getEnabled() && item->getMenu() && item->getMenu()->getVisible() && item->getMenu()->getActiveMenuItem())
			{
				item->getMenu()->ProcessKeyDown();
				return;
			}
			int index{ m_iActiveItemIndex + 1 };
			while (index < (int)getMenuItemCount() && getMenuItem(index) && (getMenuItem(index)->getIsSeparator() || !getMenuItem(index)->getEnabled()))
				index++;
			if (!getMenuItem(index))
			{
				index = 0;
				while (index < m_iActiveItemIndex && (getMenuItem(index)->getIsSeparator() || !getMenuItem(index)->getEnabled()))
					index++;
			}
			if (!getMenuItem(index) || getMenuItem(index)->getIsSeparator() || !getMenuItem(index)->getEnabled())
				index = -1;
			setActiveMenuItemIndex(index);
		}

		void CPopupMenu::ProcessKeyLeft()
		{
			CPopupMenuItem *item{ getActiveMenuItem() };
			if (item && !item->getIsSeparator() && item->getEnabled() && item->getMenu() && item->getMenu()->getVisible() && item->getMenu()->getActiveMenuItem())
			{
				item->getMenu()->ProcessKeyLeft();
				return;
			}
			if (getParentMenuItem())
				Hide();
		}

		void CPopupMenu::ProcessKeyRight()
		{
			CPopupMenuItem *item{ getActiveMenuItem() };
			if (item && !item->getIsSeparator() && item->getEnabled() && item->getMenu() && item->getMenu()->getVisible() && item->getMenu()->getActiveMenuItem())
			{
				item->getMenu()->ProcessKeyRight();
				return;
			}
			if (item && !item->getIsSeparator() && item->getEnabled() && item->getMenu())
			{
				m_pForm->LockRepaint();
				ActivateSubmenu();
				m_pForm->UnlockRepaint();
			}
		}

		void CPopupMenu::ProcessKeyHome()
		{
			CPopupMenuItem *item{ getActiveMenuItem() };
			if (item && !item->getIsSeparator() && item->getEnabled() && item->getMenu() && item->getMenu()->getVisible() && item->getMenu()->getActiveMenuItem())
			{
				item->getMenu()->ProcessKeyHome();
				return;
			}
			int index{ 0 };
			while (index < (int)getMenuItemCount() && (getMenuItem(index)->getIsSeparator() || !getMenuItem(index)->getEnabled()))
				index++;
			if (getMenuItem(index) && !getMenuItem(index)->getIsSeparator() && getMenuItem(index)->getEnabled())
				setActiveMenuItemIndex(index);
		}

		void CPopupMenu::ProcessKeyEnd()
		{
			CPopupMenuItem *item{ getActiveMenuItem() };
			if (item && !item->getIsSeparator() && item->getEnabled() && item->getMenu() && item->getMenu()->getVisible() && item->getMenu()->getActiveMenuItem())
			{
				item->getMenu()->ProcessKeyEnd();
				return;
			}
			int index{ (int)getMenuItemCount() - 1 };
			while (index >= 0 && (getMenuItem(index)->getIsSeparator() || !getMenuItem(index)->getEnabled()))
				index--;
			if (getMenuItem(index) && !getMenuItem(index)->getIsSeparator() && getMenuItem(index)->getEnabled())
				setActiveMenuItemIndex(index);
		}

		void CPopupMenu::ProcessKeyEscape()
		{
			CPopupMenuItem *item{ getActiveMenuItem() };
			if (item && !item->getIsSeparator() && item->getEnabled() && item->getMenu() && item->getMenu()->getVisible() && item->getMenu()->getActiveMenuItem())
			{
				item->getMenu()->ProcessKeyEscape();
				return;
			}
			Hide();
		}

		void CPopupMenu::ProcessKeyReturn()
		{
			CPopupMenuItem *item{ getActiveMenuItem() };
			if (item && !item->getIsSeparator() && item->getEnabled() && item->getMenu() && item->getMenu()->getVisible() && item->getMenu()->getActiveMenuItem())
			{
				item->getMenu()->ProcessKeyReturn();
				return;
			}
			if (item && !item->getIsSeparator() && item->getEnabled())
			{
				m_pForm->LockRepaint();
				if (item->getMenu())
					ActivateSubmenu();
				else
				{
					if (getParentMenuItem())
						getParentMenuItem()->getRootMenu()->Hide();
					else
						Hide();
					NotifyOnClick(item);
				}
				m_pForm->UnlockRepaint();
			}
		}

		void CPopupMenu::ProcessKeySpace()
		{
			CPopupMenuItem *item{ getActiveMenuItem() };
			if (item && !item->getIsSeparator() && item->getEnabled() && item->getMenu() && item->getMenu()->getVisible() && item->getMenu()->getActiveMenuItem())
			{
				item->getMenu()->ProcessKeySpace();
				return;
			}
			if (item && !item->getIsSeparator() && item->getEnabled() && item->getType() != CPopupMenuItem::mitNormal)
				if (item->getState() == CPopupMenuItem::misNormal)
					item->setState(CPopupMenuItem::misChecked);
				else if (item->m_eType != CPopupMenuItem::mitRadioButton)
					item->setState(CPopupMenuItem::misNormal);
		}

		bool CPopupMenu::ProcessShortcut(const IWindow::KEY key, const bool ctrl, const bool alt, const bool shift)
		{
			for (size_t i = 0; i < getMenuItemCount(); i++)
			{
				CPopupMenuItem *item{ getMenuItem(i) };
				if (!item->getIsSeparator() && item->getEnabled() && item->getShortcut().Key == key && item->getShortcut().Control == ctrl && item->getShortcut().Alt == alt && item->getShortcut().Shift == shift)
				{
					switch (item->getType())
					{
					case CPopupMenuItem::mitCheckBox:
					case CPopupMenuItem::mitRadioButton:
						if (item->getState() == CPopupMenuItem::misNormal)
							item->setState(CPopupMenuItem::misChecked);
						else
							item->setState(CPopupMenuItem::misChecked);
						break;
					default:
						Hide();
						NotifyOnClick(item);
						return true;
					}
					Hide();
					return true;
				}
			}
			CPopupMenuItem *item{ getActiveMenuItem() };
			if (item && !item->getIsSeparator() && item->getEnabled() && item->getMenu() && item->getMenu()->getVisible())
				return item->getMenu()->ProcessShortcut(key, ctrl, alt, shift);
			return false;
		}
#pragma endregion

#pragma region Render
		void CPopupMenu::RenderArrowRight(APP_RECT clip, const APP_RECT &arrow_rect, const bool enabled, const bool active)
		{
			CStyle *style{ getStyle() }, *def{ GetDefaultStyle() };
			if (!style)
				style = def;
			String name{ L".Arrow.Right" };
			if (enabled)
				if (active)
					name += L".active";
				else
					name += L".normal";
			else
				name += L".disabled";
			CStyleSkin *skin{ style->getSkinByName(m_sClassName + name) };
			if (!skin)
				skin = def->getSkinByName(m_sClassName + name);
			if (skin)
			{
				IImage *img{ m_pForm->getImageManager()->getImage(skin->getImage()->getImage()) };
				if (img)
					m_pForm->getPresenter()->RenderImage(img, skin->getRect(), arrow_rect.Left, arrow_rect.Top + (arrow_rect.Height() - skin->getRect().Height()) / 2,
						0, 1, 1, false, false, false, clip * arrow_rect, arrow_rect, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, 0, graphics::bplInside, nullptr, nullptr, true);
			}
		}

		void CPopupMenu::RenderUpArrow(APP_RECT clip)
		{
			if (m_sSize.HaveScroll)
			{
				APP_RECT scroll_rect = ClientToForm(CalculateScrollUpRect());
				String name{ m_sClassName + L".Arrow.Up.normal" };
				if (m_iScroll == 0)
					name = m_sClassName + L".Arrow.Up.disabled";
				else if (m_bMouseOverUpArrow || m_bMouseDownOnUpArrow)
					name = m_sClassName + L".Arrow.Up.hovered";
				CStyle *style{ getStyle() }, *def{ GetDefaultStyle() };
				if (!style)
					style = def;
				CStyleSkin *skin{ style->getSkinByName(name) };
				if (!skin)
					skin = def->getSkinByName(name);
				if (skin)
				{
					IImage *img{ m_pForm->getImageManager()->getImage(skin->getImage()->getImage()) };
					if (img)
					{
						int x{ scroll_rect.Left + (scroll_rect.Width() - skin->getRect().Width()) / 2 }, y{ scroll_rect.Top + (scroll_rect.Height() - skin->getRect().Height()) / 2 };
						m_pForm->getPresenter()->RenderImage(img, skin->getRect(), x, y, 0, 1, 1, false, false, false, clip * scroll_rect, scroll_rect, { 0, 0, 0, 0 }, { 0, 0, 0, 0 },
							0, graphics::bplInside, nullptr, nullptr, true);
					}
				}
			}
		}

		void CPopupMenu::RenderDownArrow(APP_RECT clip)
		{
			if (m_sSize.HaveScroll)
			{
				APP_RECT scroll_rect = ClientToForm(CalculateScrollDownRect());
				String name{ m_sClassName + L".Arrow.Down.normal" };
				if (m_iScroll == m_sSize.ScrollMax)
					name = m_sClassName + L".Arrow.Down.disabled";
				else if (m_bMouseOverDownArrow || m_bMouseDownOnDownArrow)
					name = m_sClassName + L".Arrow.Down.hovered";
				CStyle *style{ getStyle() }, *def{ GetDefaultStyle() };
				if (!style)
					style = def;
				CStyleSkin *skin{ style->getSkinByName(name) };
				if (!skin)
					skin = def->getSkinByName(name);
				if (skin)
				{
					IImage *img{ m_pForm->getImageManager()->getImage(skin->getImage()->getImage()) };
					if (img)
					{
						int x{ scroll_rect.Left + (scroll_rect.Width() - skin->getRect().Width()) / 2 }, y{ scroll_rect.Top + (scroll_rect.Height() - skin->getRect().Height()) / 2 };
						m_pForm->getPresenter()->RenderImage(img, skin->getRect(), x, y, 0, 1, 1, false, false, false, clip * scroll_rect, scroll_rect, { 0, 0, 0, 0 }, { 0, 0, 0, 0 },
							0, graphics::bplInside, nullptr, nullptr, true);
					}
				}
			}
		}
#pragma endregion

#pragma region Overwrite parent setters
		CBaseBlock *CPopupMenu::setBorderWidth(const size_t value)
		{
			if (m_pForm)
				m_pForm->LockRepaint();
			CBaseBlock::setBorderWidth(value);
			Update();
			if (m_pForm)
				m_pForm->UnlockRepaint();
			return this;
		}

		CBaseBlock *CPopupMenu::setBorderWidth(const size_t left, const size_t top, const size_t right, const size_t bottom)
		{
			if (m_pForm)
				m_pForm->LockRepaint();
			CBaseBlock::setBorderWidth(left, top, right, bottom);
			Update();
			if (m_pForm)
				m_pForm->UnlockRepaint();
			return this;
		}

		CBaseBlock *CPopupMenu::setLeftBorderWidth(const size_t value)
		{
			if (m_pForm)
				m_pForm->LockRepaint();
			CBaseBlock::setLeftBorderWidth(value);
				Update();
			if (m_pForm)
				m_pForm->UnlockRepaint();
			return this;
		}

		CBaseBlock *CPopupMenu::setTopBorderWidth(const size_t value)
		{
			if (m_pForm)
				m_pForm->LockRepaint();
			CBaseBlock::setTopBorderWidth(value);
				Update();
			if (m_pForm)
				m_pForm->UnlockRepaint();
			return this;
		}

		CBaseBlock *CPopupMenu::setRightBorderWidth(const size_t value)
		{
			if (m_pForm)
				m_pForm->LockRepaint();
			CBaseBlock::setRightBorderWidth(value);
				Update();
			if (m_pForm)
				m_pForm->UnlockRepaint();
			return this;
		}

		CBaseBlock *CPopupMenu::setBottomBorderWidth(const size_t value)
		{
			if (m_pForm)
				m_pForm->LockRepaint();
			CBaseBlock::setBottomBorderWidth(value);
				Update();
			if (m_pForm)
				m_pForm->UnlockRepaint();
			return this;
		}

		CBaseBlock *CPopupMenu::setPadding(const math::RECTANGLE<size_t> &value)
		{
			if (m_pForm)
				m_pForm->LockRepaint();
			CBaseBlock::setPadding(value);
				Update();
			if (m_pForm)
				m_pForm->UnlockRepaint();
			return this;
		}

		CBaseBlock *CPopupMenu::setPadding(const size_t value)
		{
			if (m_pForm)
				m_pForm->LockRepaint();
			CBaseBlock::setPadding(value);
				Update();
			if (m_pForm)
				m_pForm->UnlockRepaint();
			return this;
		}

		CBaseBlock *CPopupMenu::setPaddingLeft(const size_t value)
		{
			if (m_pForm)
				m_pForm->LockRepaint();
			CBaseBlock::setPaddingLeft(value);
				Update();
			if (m_pForm)
				m_pForm->UnlockRepaint();
			return this;
		}

		CBaseBlock *CPopupMenu::setPaddingTop(const size_t value)
		{
			if (m_pForm)
				m_pForm->LockRepaint();
			CBaseBlock::setPaddingTop(value);
				Update();
			if (m_pForm)
				m_pForm->UnlockRepaint();
			return this;
		}

		CBaseBlock *CPopupMenu::setPaddingRight(const size_t value)
		{
			if (m_pForm)
				m_pForm->LockRepaint();
			CBaseBlock::setPaddingRight(value);
				Update();
			if (m_pForm)
				m_pForm->UnlockRepaint();
			return this;
		}

		CBaseBlock *CPopupMenu::setPaddingBottom(const size_t value)
		{
			if (m_pForm)
				m_pForm->LockRepaint();
			CBaseBlock::setPaddingBottom(value);
				Update();
			if (m_pForm)
				m_pForm->UnlockRepaint();
			return this;
		}
#pragma endregion
	}
}