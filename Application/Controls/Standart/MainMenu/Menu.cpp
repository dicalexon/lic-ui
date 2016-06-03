// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#include "MainMenu.h"
#include "..\..\..\..\Utils\Utils.h"
#include "..\..\..\DefaultStyle.h"
#include "..\..\..\Style.h"
#include "..\..\..\StyleSkin.h"
#include "..\..\..\StyleImage.h"
#include "..\..\..\Form.h"
#include "..\..\..\ImageManager.h"
#include "..\..\..\Presenter.h"

namespace licui
{
	namespace application
	{
		const unsigned int SCROLL_TIMER_INTERVAL{ 250 };

	#pragma region Constructors
		CMenu::CMenu() :
			CBaseBlock(),
			m_sSize{ 0, 0, 0, 0, {0, 0}, {0, 0}, false, 0, 10, 0 },
			m_iActiveMenuItemIndex{ -1 },
			m_hScrollTimer{ 0 },
			m_pImageList{ nullptr },
			m_bShowImages{ true },
			m_fOnClick{ nullptr },
			m_sMarginTopScrollArrow{ 2, 2 },
			m_sMarginBottomScrollArrow{ 2, 2 },
			m_bMouseOverTopScrollArrow{ false },
			m_bMouseOverBottomScrollArrow{ false },
			m_bMouseDownOnTopScrollArrow{ false },
			m_bMouseDownOnBottomScrollArrow{ false }
		{
			m_sClassName = L"CMenu";
			m_bVisible = false;
			FillBlock();
		}

		CMenu::CMenu(CMainMenuItem *item) :CMenu()
		{
			if (item)
				item->setMenu(this);
		}

		CMenu::CMenu(CMenuItem *item) :CMenu()
		{
			if (item)
				item->setMenu(this);
		}

		void CMenu::FillBlock()
		{
			m_sBlock.BorderWidth = { 1, 1, 1, 1 };
			m_sBlock.BorderColor[0] = { 152, 152, 152, 255 };
			m_sBlock.BorderColor[1] = { 152, 152, 152, 255 };
			m_sBlock.BorderColor[2] = { 152, 152, 152, 255 };
			m_sBlock.BorderColor[3] = { 152, 152, 152, 255 };
			m_sBlock.BackgroundColor = { 241, 241, 241, 255 };
			m_sBlock.BoxShadow = true;
			m_sBlock.BoxShadowColor = { 152, 152, 152, 200 };
			m_sBlock.BoxShadowShift = { 2, 2 };
			m_sBlock.BoxShadowRadius = 3;
		}
	#pragma endregion

	#pragma region Getters
		CMenu::BLOCK *CMenu::getBlock()
		{
			return &m_sBlock;
		}

		APP_RECT CMenu::getVisibleRect()
		{
			return ClientToForm(getRenderRect());
		}

		APP_RECT CMenu::getClientRect()
		{
			APP_RECT result = CBaseBlock::getClientRect();
			if (m_sSize.ScrollExists)
			{
				APP_IMAGE *image;
				APP_RECT rect;
				if (SearchTopScrollArrow(&image, rect, true))
					result.Top += rect.Height() + m_sMarginTopScrollArrow[0] + m_sMarginTopScrollArrow[1];
				if (SearchBottomScrollArrow(&image, rect, true))
					result.Bottom -= rect.Height() + (int)m_sMarginBottomScrollArrow[0] + (int)m_sMarginBottomScrollArrow[1];
				if (!result.IsValid())
					result.Bottom = result.Top;
			}
			return result;
		}

		CControl *CMenu::setConstraints(const math::RECTANGLE<size_t> &value)
		{
			if (m_pForm)
				m_pForm->LockRepaint();
			CControl::setConstraints(value);
			Update();
			if (m_pForm)
				m_pForm->UnlockRepaint();
			return this;
		}

		CMainMenu *CMenu::getMainMenu()
		{
			if (getMainMenuItem())
				return getMainMenuItem()->getMainMenu();
			if (getParentMenuItem() && getParentMenuItem()->getParentMenu())
				return getParentMenuItem()->getParentMenu()->getMainMenu();
			return nullptr;
		}

		CMainMenuItem *CMenu::getMainMenuItem()
		{
			return cast<CMainMenuItem*>(getParent());
		}

		CMenuItem *CMenu::getParentMenuItem()
		{
			return cast<CMenuItem*>(getParent());
		}

		size_t CMenu::getMenuItemCount() const
		{
			return getControlCount();
		}

		CMenuItem *CMenu::getMenuItem(const int index)
		{
			return dynamic_cast<CMenuItem*>(getControl(index));
		}

		bool CMenu::getHaveScroll() const
		{
			return m_sSize.ScrollExists;
		}

		size_t CMenu::getScrollMax() const
		{
			return m_sSize.ScrollMax;
		}

		size_t CMenu::getScrollDelta() const
		{
			return m_sSize.ScrollDelta;
		}

		size_t CMenu::getScroll() const
		{
			return m_sSize.ScrollValue;
		}

		int CMenu::getActiveMenuItemIndex() const
		{
			return m_iActiveMenuItemIndex;
		}

		CMenuItem *CMenu::getActiveMenuItem()
		{
			if (m_iActiveMenuItemIndex >= 0)
				return getMenuItem(m_iActiveMenuItemIndex);
			return nullptr;
		}

		CImageList *CMenu::getImageList()
		{
			if (m_pImageList)
				return m_pImageList;
			if (getParentMenuItem() && getParentMenuItem()->getParentMenu())
				return getParentMenuItem()->getParentMenu()->getImageList();
			if (getMainMenu())
				return getMainMenu()->getImageList();
			return nullptr;
		}

		bool CMenu::getShowImages()
		{
			return m_bShowImages;
		}

		CMenuItem::FOnClick CMenu::getOnClick() const
		{
			return m_fOnClick;
		}

		math::POINT<size_t> CMenu::getMarginTopScrollArrow() const
		{
			return m_sMarginTopScrollArrow;
		}

		size_t CMenu::getMarginTopScrollArrowTop() const
		{
			return m_sMarginTopScrollArrow.X;
		}

		size_t CMenu::getMarginTopScrollArrowBottom() const
		{
			return m_sMarginTopScrollArrow.Y;
		}

		math::POINT<size_t> CMenu::getMarginBottomScrollArrow() const
		{
			return m_sMarginBottomScrollArrow;
		}

		size_t CMenu::getMarginBottomScrollArrowTop() const
		{
			return m_sMarginBottomScrollArrow.X;
		}

		size_t CMenu::getMarginBottomScrollArrowBottom() const
		{
			return m_sMarginBottomScrollArrow.Y;
		}
	#pragma endregion

	#pragma region Setters
		CBaseBlock *CMenu::setBorderWidth(const size_t value)
		{
			if (value != m_sBlock.BorderWidth[0] || value != m_sBlock.BorderWidth[1] || value != m_sBlock.BorderWidth[2] || value != m_sBlock.BorderWidth[3])
			{
				m_sBlock.BorderWidth[0] = m_sBlock.BorderWidth[1] = m_sBlock.BorderWidth[2] = m_sBlock.BorderWidth[3] = value;
				Update();
			}
			return this;
		}

		CBaseBlock *CMenu::setBorderWidth(const size_t left, const size_t top, const size_t right, const size_t bottom)
		{
			if (left != m_sBlock.BorderWidth.Left || top != m_sBlock.BorderWidth.Top || right != m_sBlock.BorderWidth.Right || bottom != m_sBlock.BorderWidth.Bottom)
			{
				m_sBlock.BorderWidth.Left = left;
				m_sBlock.BorderWidth.Top = top;
				m_sBlock.BorderWidth.Right = right;
				m_sBlock.BorderWidth.Bottom = bottom;
				Update();
			}
			return this;
		}

		CBaseBlock *CMenu::setLeftBorderWidth(const size_t value)
		{
			if (value != m_sBlock.BorderWidth.Left)
			{
				m_sBlock.BorderWidth.Left = value;
				Update();
			}
			return this;
		}

		CBaseBlock *CMenu::setTopBorderWidth(const size_t value)
		{
			if (value != m_sBlock.BorderWidth.Top)
			{
				m_sBlock.BorderWidth.Top = value;
				Update();
			}
			return this;
		}

		CBaseBlock *CMenu::setRightBorderWidth(const size_t value)
		{
			if (value != m_sBlock.BorderWidth.Right)
			{
				m_sBlock.BorderWidth.Right = value;
				Update();
			}
			return this;
		}

		CBaseBlock *CMenu::setBottomBorderWidth(const size_t value)
		{
			if (value != m_sBlock.BorderWidth.Bottom)
			{
				m_sBlock.BorderWidth.Bottom = value;
				Update();
			}
			return this;
		}

		CBaseBlock *CMenu::setBorderRadius(const size_t value)
		{
			if (value != m_sBlock.BorderRadius[0] || value != m_sBlock.BorderRadius[1] || value != m_sBlock.BorderRadius[2] || value != m_sBlock.BorderRadius[3])
			{
				m_sBlock.BorderRadius[0] = m_sBlock.BorderRadius[1] = m_sBlock.BorderRadius[2] = m_sBlock.BorderRadius[3] = value;
				Update();
			}
			return this;
		}

		CBaseBlock *CMenu::setBorderRadius(const size_t left_top, const size_t right_top, const size_t right_bottom, const size_t left_bottom)
		{
			if (left_top != m_sBlock.BorderRadius[0] || right_top != m_sBlock.BorderRadius[1] || right_bottom != m_sBlock.BorderRadius[2] || left_bottom != m_sBlock.BorderRadius[3])
			{
				m_sBlock.BorderRadius[0] = left_top;
				m_sBlock.BorderRadius[1] = right_top;
				m_sBlock.BorderRadius[2] = right_bottom;
				m_sBlock.BorderRadius[3] = left_bottom;
				Update();
			}
			return this;
		}

		CBaseBlock *CMenu::setLeftTopRadius(const size_t value)
		{
			if (value != m_sBlock.BorderRadius[0])
			{
				m_sBlock.BorderRadius[0] = value;
				Update();
			}
			return this;
		}

		CBaseBlock *CMenu::setRightTopRadius(const size_t value)
		{
			if (value != m_sBlock.BorderRadius[1])
			{
				m_sBlock.BorderRadius[1] = value;
				Update();
			}
			return this;
		}

		CBaseBlock *CMenu::setRightBottomRadius(const size_t value)
		{
			if (value != m_sBlock.BorderRadius[2])
			{
				m_sBlock.BorderRadius[2] = value;
				Update();
			}
			return this;
		}

		CBaseBlock *CMenu::setLeftBottomRadius(const size_t value)
		{
			if (value != m_sBlock.BorderRadius[3])
			{
				m_sBlock.BorderRadius[3] = value;
				Update();
			}
			return this;
		}

		CBaseBlock *CMenu::setPadding(const math::RECTANGLE<size_t> &value)
		{
			if (value != m_sBlock.Padding)
			{
				m_sBlock.Padding = value;
				Update();
			}
			return this;
		}

		CBaseBlock *CMenu::setPadding(const size_t value)
		{
			if (value != m_sBlock.Padding[0] || value != m_sBlock.Padding[1] || value != m_sBlock.Padding[2] || value != m_sBlock.Padding[3])
			{
				m_sBlock.Padding[0] = m_sBlock.Padding[1] = m_sBlock.Padding[2] = m_sBlock.Padding[3] = value;
				Update();
			}
			return this;
		}

		CBaseBlock *CMenu::setPaddingLeft(const size_t value)
		{
			if (value != m_sBlock.Padding.Left)
			{
				m_sBlock.Padding.Left = value;
				Update();
			}
			return this;
		}

		CBaseBlock *CMenu::setPaddingTop(const size_t value)
		{
			if (value != m_sBlock.Padding.Top)
			{
				m_sBlock.Padding.Top = value;
				Update();
			}
			return this;
		}

		CBaseBlock *CMenu::setPaddingRight(const size_t value)
		{
			if (value != m_sBlock.Padding.Right)
			{
				m_sBlock.Padding.Right = value;
				Update();
			}
			return this;
		}

		CBaseBlock *CMenu::setPaddingBottom(const size_t value)
		{
			if (value != m_sBlock.Padding.Bottom)
			{
				m_sBlock.Padding.Bottom = value;
				Update();
			}
			return this;
		}

		CMenu *CMenu::setMainMenuItem(CMainMenuItem *value)
		{
			if (value != getMainMenuItem())
			{
				CForm *form{ m_pForm };
				if (form)
					form->LockRepaint();
				if (value)
				{
					value->m_bAcceptControls = true;
					m_bAcceptParent = true;
				}
				setParent(value);
				if (value)
				{
					value->m_bAcceptControls = false;
					m_bAcceptParent = false;
				}
				if (form)
					form->UnlockRepaint();
			}
			return this;
		}

		CMenu *CMenu::setParentMenuItem(CMenuItem *value)
		{
			if (value != getParentMenuItem())
			{
				CForm *form{ m_pForm };
				if (form)
					form->LockRepaint();
				if (value)
				{
					value->m_bAcceptControls = true;
					m_bAcceptParent = true;
				}
				setParent(value);
				if (value)
				{
					value->m_bAcceptControls = false;
					m_bAcceptParent = false;
				}
				if (form)
					form->UnlockRepaint();
			}
			return this;
		}

		CMenu *CMenu::setScrollDelta(const size_t value)
		{
			m_sSize.ScrollDelta = value;
			return this;
		}

		CMenu *CMenu::setScroll(size_t value)
		{
			if (value > m_sSize.ScrollMax)
				value = m_sSize.ScrollMax;
			if (m_sSize.ScrollExists && value != m_sSize.ScrollValue)
			{
				m_sSize.ScrollValue = value;
				Update();
			}
			return this;
		}

		CMenu *CMenu::setActiveMenuItemIndex(int value)
		{
			if (value < -1 || value >= (int)getMenuItemCount())
				value = -1;
			if (value != m_iActiveMenuItemIndex)
			{
				if (!getMenuItem(value) || (getMenuItem(value)->m_eType != CMenuItem::mitSeparator && getMenuItem(value)->m_bEnabled))
				{
					if (m_pForm)
						m_pForm->LockRepaint();
					if (getActiveMenuItem())
						getActiveMenuItem()->Repaint(false);
					bool visible{ getActiveMenuItem() && getActiveMenuItem()->getMenu() && getActiveMenuItem()->getMenu()->m_bVisible };
					if (visible)
						getActiveMenuItem()->getMenu()->Hide();
					m_iActiveMenuItemIndex = value;
					// Calc new scroll
					bool perform_update{ false };
					if (m_sSize.ScrollExists)
					{
						APP_RECT item_rect = getMenuItem(m_iActiveMenuItemIndex)->ClientToForm(getMenuItem(m_iActiveMenuItemIndex)->getRect()), rect = ClientToForm(getClientRect());
						if (item_rect.Top < rect.Top)
						{
							m_sSize.ScrollValue = 0;
							for (size_t i = 0; i < (size_t)m_iActiveMenuItemIndex; i++)
								m_sSize.ScrollValue += getMenuItem(i)->getHeight();
							perform_update = true;
						}
						else if (item_rect.Bottom > rect.Bottom)
						{
							m_sSize.ScrollValue = 0;
							for (size_t i = 0; i <= (size_t)m_iActiveMenuItemIndex; i++)
								m_sSize.ScrollValue += getMenuItem(i)->getHeight();
							m_sSize.ScrollValue -= getClientRect().Height();
							perform_update = true;
						}
					}					
					if (perform_update)
						Update();
					if (visible && getActiveMenuItem() && getActiveMenuItem()->m_eType != CMenuItem::mitSeparator && getActiveMenuItem()->m_bEnabled && getActiveMenuItem()->getMenu())
						getActiveMenuItem()->getMenu()->Show(getWidth() + getActiveMenuItem()->m_sMenuShift.X, getActiveMenuItem()->m_sMenuShift.Y);
					if (getActiveMenuItem())
						getActiveMenuItem()->Repaint(false);
					if (m_pForm)
						m_pForm->UnlockRepaint();
				}
			}
			return this;
		}

		CMenu *CMenu::setActiveMenuItem(CMenuItem *value)
		{
			int index{ -1 };
			for (index = 0; index < (int)getMenuItemCount(); index++)
				if (getMenuItem(index) == value)
					break;
			return setActiveMenuItemIndex(index);
		}

		CMenu *CMenu::setImageList(CImageList *value)
		{
			if (value != m_pImageList)
			{
				m_pImageList = value;
				Repaint(true);
			}
			return this;
		}

		CMenu *CMenu::setShowImages(const bool value)
		{
			if (value != m_bShowImages)
			{
				m_bShowImages = value;
				Update();
			}
			return this;
		}

		CMenu *CMenu::setOnClick(CMenuItem::FOnClick value)
		{
			m_fOnClick = value;
			return this;
		}

		CMenu *CMenu::setMarginTopScrollArrow(const math::POINT<size_t> &value)
		{
			if (value != m_sMarginTopScrollArrow)
			{
				m_sMarginTopScrollArrow = value;
				if (m_sSize.ScrollExists)
					Update();
			}
			return this;
		}

		CMenu *CMenu::setMarginTopScrollArrowTop(const size_t value)
		{
			if (value != m_sMarginTopScrollArrow.X)
			{
				m_sMarginTopScrollArrow.X = value;
				if (m_sSize.ScrollExists)
					Update();
			}
			return this;
		}

		CMenu *CMenu::setMarginTopScrollArrowBottom(const size_t value)
		{
			if (value != m_sMarginTopScrollArrow.Y)
			{
				m_sMarginTopScrollArrow.Y = value;
				if (m_sSize.ScrollExists)
					Update();
			}
			return this;
		}

		CMenu *CMenu::setMarginBottomScrollArrow(const math::POINT<size_t> &value)
		{
			if (value != m_sMarginBottomScrollArrow)
			{
				m_sMarginBottomScrollArrow = value;
				if (m_sSize.ScrollExists)
					Update();
			}
			return this;
		}

		CMenu *CMenu::setMarginBottomScrollArrowTop(const size_t value)
		{
			if (value != m_sMarginBottomScrollArrow.X)
			{
				m_sMarginBottomScrollArrow.X = value;
				if (m_sSize.ScrollExists)
					Update();
			}
			return this;
		}

		CMenu *CMenu::setMarginBottomScrollArrowBottom(const size_t value)
		{
			if (value != m_sMarginBottomScrollArrow.Y)
			{
				m_sMarginBottomScrollArrow.Y = value;
				if (m_sSize.ScrollExists)
					Update();
			}
			return this;
		}
	#pragma endregion

	#pragma region Menu items
		CMenu *CMenu::AddMenuItem(CMenuItem *item)
		{
			if (item)
				item->setParentMenu(this);
			return this;
		}

		CMenu *CMenu::DeleteMenuItem(const size_t index)
		{
			return dynamic_cast<CMenu*>(DeleteControl(index));
		}

		CMenu *CMenu::DeleteMenuItem(CMenuItem *item)
		{
			return dynamic_cast<CMenu*>(DeleteControl(item));
		}

		CMenu *CMenu::DeleteMenuItems()
		{
			return dynamic_cast<CMenu*>(DeleteControls());
		}
	#pragma endregion

	#pragma region Notifications
		void CMenu::NotifyOnBeforeDetachComponentFromForm(CComponent *component)
		{
			// Handle remove image list
			if (component == m_pImageList)
			{
				m_pImageList = nullptr;
				Repaint(true);
			}
			CBaseBlock::NotifyOnBeforeDetachComponentFromForm(component);
		}

		void CMenu::NotifyOnBeforeDetachFromForm()
		{
			StopScrollTimer();
			CBaseBlock::NotifyOnBeforeDetachFromForm();
		}

		void CMenu::NotifyOnUpdateComponent(CComponent *component)
		{
			if (component == m_pImageList)
				Update();
			CControl::NotifyOnUpdateComponent(component);
		}

		bool CMenu::NotifyOnMouseMove(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			if (m_sSize.ScrollExists)
			{
				APP_RECT rect = ClientToForm(CalculateTopScrollArrowRect());
				if (x >= rect.Left && x < rect.Right && y >= rect.Top && y < rect.Bottom)
				{
					if (!m_bMouseOverTopScrollArrow)
					{
						m_bMouseOverTopScrollArrow = true;
						m_bMouseOverBottomScrollArrow = false;
						Repaint(true);
					}
				}
				else
				{
					rect = ClientToForm(CalculateBottomScrollArrowRect());
					if (x >= rect.Left && x < rect.Right && y >= rect.Top && y < rect.Bottom)
					{
						if (!m_bMouseOverBottomScrollArrow)
						{
							m_bMouseOverTopScrollArrow = false;
							m_bMouseOverBottomScrollArrow = true;
							Repaint(true);
						}
					}
					else if (m_bMouseOverTopScrollArrow || m_bMouseOverBottomScrollArrow)
					{
						m_bMouseOverTopScrollArrow = false;
						m_bMouseOverBottomScrollArrow = false;
						Repaint(true);
					}
				}
			}
			return CBaseBlock::NotifyOnMouseMove(x, y, ctrl, left, middle, right, shift);
		}

		bool CMenu::NotifyOnLeftMouseButtonDown(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			if (m_sSize.ScrollExists && !m_hScrollTimer)
			{
				APP_RECT rect = ClientToForm(CalculateTopScrollArrowRect());
				if (x >= rect.Left && x < rect.Right && y >= rect.Top && y < rect.Bottom)
				{
					m_bMouseDownOnTopScrollArrow = true;
					m_bMouseDownOnBottomScrollArrow = false;
					if (m_sSize.ScrollValue > 0)
					{
						m_sSize.ScrollValue = std::max(0, (int)m_sSize.ScrollValue - (int)m_sSize.ScrollDelta);
						Update();
					}
					m_hScrollTimer = m_pForm->AddTimer(TimerCallback, this, SCROLL_TIMER_INTERVAL);
				}
				else
				{
					rect = ClientToForm(CalculateBottomScrollArrowRect());
					if (x >= rect.Left && x < rect.Right && y >= rect.Top && y < rect.Bottom)
					{
						m_bMouseDownOnTopScrollArrow = false;
						m_bMouseDownOnBottomScrollArrow = true;
						if (m_sSize.ScrollValue < m_sSize.ScrollMax)
						{
							m_sSize.ScrollValue = std::min(m_sSize.ScrollMax, m_sSize.ScrollValue + m_sSize.ScrollDelta);
							Update();
						}
						m_hScrollTimer = m_pForm->AddTimer(TimerCallback, this, SCROLL_TIMER_INTERVAL);
					}
				}
			}
			return CBaseBlock::NotifyOnLeftMouseButtonDown(x, y, ctrl, left, middle, right, shift);
		}

		void CMenu::NotifyOnMouseHover()
		{
			if (m_sSize.ScrollExists)
			{
				int x, y;
				if (m_pForm->getWindow()->getCursorPosition(x, y))
				{
					APP_RECT rect = ClientToForm(CalculateTopScrollArrowRect());
					
					if (x >= rect.Left && x < rect.Right && y >= rect.Top && y < rect.Bottom)
					{
						m_bMouseOverTopScrollArrow = true;
						m_bMouseOverBottomScrollArrow = false;
						Repaint(true);
					}
					else
					{
						rect = ClientToForm(CalculateBottomScrollArrowRect());
						if (x >= rect.Left && x < rect.Right && y >= rect.Top && y < rect.Bottom)
						{
							m_bMouseOverTopScrollArrow = false;
							m_bMouseOverBottomScrollArrow = true;
							Repaint(true);
						}
					}
				}
			}
			CBaseBlock::NotifyOnMouseHover();
		}

		void CMenu::NotifyOnMouseLeave()
		{
			if (m_sSize.ScrollExists && (m_bMouseOverTopScrollArrow || m_bMouseOverBottomScrollArrow))
			{
				m_bMouseOverTopScrollArrow = m_bMouseOverBottomScrollArrow = false;
				Repaint(true);
			}
			CBaseBlock::NotifyOnMouseLeave();
		}

		void CMenu::NotifyOnChangeParentStyle()
		{
			CBaseBlock::NotifyOnChangeParentStyle();
			Update();
		}

		void CMenu::NotifyOnChangeStyle()
		{
			CBaseBlock::NotifyOnChangeStyle();
			Update();
		}

		void CMenu::NotifyOnHide()
		{
			StopScrollTimer();
			if (getActiveMenuItem() && getActiveMenuItem()->getMenu() && getActiveMenuItem()->getMenu()->m_bVisible)
				getActiveMenuItem()->getMenu()->Hide();
			ClearActiveMenuItem();
			CBaseBlock::NotifyOnHide();
		}

		void CMenu::NotifyOnDetachControl(CControl *control)
		{
			if (getActiveMenuItem() && getActiveMenuItem()->getMenu() && getActiveMenuItem()->getMenu()->m_bVisible)
				getActiveMenuItem()->getMenu()->Hide();
			ClearActiveMenuItem();
			Update();
			CBaseBlock::NotifyOnDetachControl(control);
		}

		void CMenu::NotifyOnPaint(APP_RECT clip)
		{
			DoRender(L"", clip);
			RenderTopScrollArrow(clip);
			RenderBottomScrollArrow(clip);
			CBaseBlock::NotifyOnPaint(clip);
		}

		void CMenu::NotifyOnClick(CControl *sender)
		{
			if (m_fOnClick)
				m_fOnClick(sender, getCallbackParam());
		}
	#pragma endregion

	#pragma region Helpers
		bool CMenu::SearchTopScrollArrow(APP_IMAGE **image, APP_RECT &rect, const bool ignore_state)
		{
			String name{ m_sClassName + L".Arrow.TopScroll" };
			if (ignore_state)
				name += L".normal";
			else
				if (m_sSize.ScrollValue == 0)
					name += L".disabled";
				else if (m_bMouseOverTopScrollArrow)
					name += L".hovered";
				else
					name += L".normal";
			CStyle *style{ getStyle() }, *def{ GetDefaultStyle() };
			if (!style)
				style = def;
			CStyleSkin *skin{ style->getSkinByName(name) };
			if (!skin)
				skin = def->getSkinByName(name);
			if (!skin)
				return false;
			*image = skin->getImage()->getImage();
			rect = skin->getRect();
			return *image && rect.Width() > 0 && rect.Height() > 0;
		}

		bool CMenu::SearchBottomScrollArrow(APP_IMAGE **image, APP_RECT &rect, const bool ignore_state)
		{
			String name{ m_sClassName + L".Arrow.BottomScroll" };
			if (ignore_state)
				name += L".normal";
			else
				if (m_sSize.ScrollValue == m_sSize.ScrollMax)
					name += L".disabled";
				else if (m_bMouseOverBottomScrollArrow)
					name += L".hovered";
				else
					name += L".normal";
				CStyle *style{ getStyle() }, *def{ GetDefaultStyle() };
				if (!style)
					style = def;
				CStyleSkin *skin{ style->getSkinByName(name) };
				if (!skin)
					skin = def->getSkinByName(name);
				if (!skin)
					return false;
				*image = skin->getImage()->getImage();
				rect = skin->getRect();
				return *image && rect.Width() > 0 && rect.Height() > 0;
		}

		void CMenu::ClearActiveMenuItem()
		{
			if (getActiveMenuItem())
			{
				if (getActiveMenuItem()->getMenu())
					getActiveMenuItem()->getMenu()->ClearActiveMenuItem();
				m_iActiveMenuItemIndex = -1;
			}
		}

		void CMenu::CalculateSize()
		{
			m_sSize.WidthImage = m_sSize.WidthCaption = m_sSize.WidthShortcut = m_sSize.WidthArrow = 0;
			m_sSize.SizeRequired.X = m_sBlock.Padding.Left + m_sBlock.Padding.Right + m_sBlock.BorderWidth.Left + m_sBlock.BorderWidth.Right;
			m_sSize.SizeRequired.Y = m_sBlock.Padding.Top + m_sBlock.Padding.Bottom + m_sBlock.BorderWidth.Top + m_sBlock.BorderWidth.Bottom;
			for (size_t index = 0; index < getMenuItemCount(); index++)
			{
				CMenuItem::SIZE size = getMenuItem(index)->CalculateSize();
				if (m_bShowImages)
					m_sSize.WidthImage = std::max(m_sSize.WidthImage, size.WidthImage);
				m_sSize.WidthCaption = std::max(m_sSize.WidthCaption, size.WidthCaptionImage + size.WidthCaption);
				m_sSize.WidthShortcut = std::max(m_sSize.WidthShortcut, size.WidthShortcut);
				m_sSize.WidthArrow = std::max(m_sSize.WidthArrow, size.WidthArrow);
				m_sSize.SizeRequired.Y += size.Height;
			}
			m_sSize.SizeRequired.X += m_sSize.WidthImage + m_sSize.WidthCaption + m_sSize.WidthShortcut + m_sSize.WidthArrow;
			m_sSize.SizeActual = m_sSize.SizeRequired;
			if (m_sConstraints.Left > 0 && m_sSize.SizeActual.X < m_sConstraints.Left)
				m_sSize.SizeActual.X = m_sConstraints.Left;
			if (m_sConstraints.Right > 0 && m_sSize.SizeActual.X > m_sConstraints.Right)
				m_sSize.SizeActual.X = m_sConstraints.Right;
			if (m_sConstraints.Top > 0 && m_sSize.SizeActual.Y < m_sConstraints.Top)
				m_sSize.SizeActual.Y = m_sConstraints.Top;
			if (m_sConstraints.Bottom > 0 && m_sSize.SizeActual.Y > m_sConstraints.Bottom)
				m_sSize.SizeActual.Y = m_sConstraints.Bottom;
			size_t w{ (size_t)std::max(0, (int)m_sSize.SizeActual.X - (int)m_sBlock.Padding.Left - (int)m_sBlock.Padding.Right - (int)m_sBlock.BorderWidth.Left - (int)m_sBlock.BorderWidth.Right) };
			m_sSize.WidthImage = std::max((size_t)0, std::min(m_sSize.WidthImage, w));
			w = std::max(0, (int)w - (int)m_sSize.WidthImage);
			m_sSize.WidthCaption = std::max((size_t)0, std::min(m_sSize.WidthCaption, w));
			w = std::max(0, (int)w - (int)m_sSize.WidthCaption);
			m_sSize.WidthShortcut = std::max((size_t)0, std::min(m_sSize.WidthShortcut, w));
			w = std::max(0, (int)w - (int)m_sSize.WidthShortcut);
			m_sSize.WidthArrow = std::max((size_t)0, std::min(m_sSize.WidthArrow, w));
			if (m_sSize.SizeActual.Y == m_sSize.SizeRequired.Y)
			{
				m_sSize.ScrollExists = false;
				m_sSize.ScrollMax = 0;
				m_sSize.ScrollValue = 0;
			}
			else
			{
				m_sSize.ScrollExists = true;
				m_sSize.ScrollMax = m_sSize.SizeRequired.Y - m_sSize.SizeActual.Y;
				APP_IMAGE *image;
				APP_RECT rect;
				if (SearchTopScrollArrow(&image, rect, true))
					m_sSize.ScrollMax += rect.Height() + m_sMarginTopScrollArrow.X + m_sMarginTopScrollArrow.Y;
				if (SearchBottomScrollArrow(&image, rect, true))
					m_sSize.ScrollMax += rect.Height() + m_sMarginBottomScrollArrow.X + m_sMarginBottomScrollArrow.Y;
				if (m_sSize.ScrollValue > m_sSize.ScrollMax)
					m_sSize.ScrollValue = m_sSize.ScrollMax;
			}
		}

		APP_RECT CMenu::CalculateTopScrollArrowRect()
		{
			APP_IMAGE *image;
			APP_RECT rect;
			if (SearchTopScrollArrow(&image, rect, true))
			{
				APP_RECT result = CBaseBlock::getClientRect();
				result.Bottom = result.Top + rect.Height() + m_sMarginTopScrollArrow[0] + m_sMarginTopScrollArrow[1];
				if (result.Bottom > CBaseBlock::getClientRect().Bottom)
					result.Bottom = CBaseBlock::getClientRect().Bottom;
				if (!result.IsValid())
					result.Bottom = result.Top;
				return result;
			}
			return{ 0, 0, 0, 0 };
		}

		APP_RECT CMenu::CalculateBottomScrollArrowRect()
		{
			APP_IMAGE *image;
			APP_RECT rect;
			if (SearchBottomScrollArrow(&image, rect, true))
			{
				APP_RECT result = CBaseBlock::getClientRect();
				result.Top = result.Bottom - (int)m_sMarginBottomScrollArrow[0] - rect.Height() - m_sMarginBottomScrollArrow[1];
				if (result.Top < CBaseBlock::getClientRect().Top)
					result.Top = CBaseBlock::getClientRect().Top;
				if (!result.IsValid())
					result.Top = result.Bottom;
				return result;
			}
			return{ 0, 0, 0, 0 };
		}

		void CMenu::Update()
		{
			if (!m_pForm || !getVisibleWithParents())
				return;
			m_pForm->LockRepaint();
			Repaint(true);
			CalculateSize();
			m_sInitialRect.Right = m_sInitialRect.Left + m_sSize.SizeActual.X;
			m_sInitialRect.Bottom = m_sInitialRect.Top + m_sSize.SizeActual.Y;
			UpdateRect();
			UpdateControls();
			Repaint(true);
			m_pForm->UnlockRepaint();
		}

		void CMenu::UpdateControls()
		{
			APP_RECT rect = getClientRect();
			for (size_t index = 0; index < getMenuItemCount(); index++)
			{
				CMenuItem::SIZE size = getMenuItem(index)->CalculateSize();
				getMenuItem(index)->setRect({
					rect.Left - getRect().Left, rect.Top - getRect().Top - (int)m_sSize.ScrollValue,
					rect.Right - getRect().Left, rect.Top - getRect().Top + (int)size.Height - (int)m_sSize.ScrollValue });
				rect.Top += size.Height;
			}
			if (getActiveMenuItem() && getActiveMenuItem()->getMenu() && getActiveMenuItem()->getMenu()->m_bVisible)
				getActiveMenuItem()->getMenu()->Show(getWidth() + getActiveMenuItem()->m_sMenuShift.X, getActiveMenuItem()->m_sMenuShift.Y);
		}

		void CMenu::Show(const int x, const int y)
		{
			if (m_pForm && getMainMenu() && (!m_bVisible || x != getLeft() || y != getTop()))
			{
				m_pForm->LockRepaint();
				Repaint(true);
				m_sInitialRect.Left = x;
				m_sInitialRect.Top = y;
				if (getParent() && getParent()->getVisibleWithParents())
					m_bVisible = true;
				Update();
				m_pForm->UnlockRepaint();
			}
		}

		void CMenu::Hide()
		{
			setVisible(false);
		}

		void CMenu::StopScrollTimer()
		{
			if (m_hScrollTimer)
			{
				m_pForm->DeleteTimer(m_hScrollTimer);
				m_hScrollTimer = 0;
			}
		}

		void CMenu::TimerCallback(void *param)
		{
			CMenu *menu{ (CMenu*)param };
			if (menu->m_bMouseDownOnTopScrollArrow && menu->m_bMouseOverTopScrollArrow && menu->m_sSize.ScrollValue > 0)
			{
				menu->m_sSize.ScrollValue = std::max(0, (int)menu->m_sSize.ScrollValue - (int)menu->m_sSize.ScrollDelta);
				menu->Update();
			}
			else if (menu->m_bMouseDownOnBottomScrollArrow && menu->m_bMouseOverBottomScrollArrow && menu->m_sSize.ScrollValue < menu->m_sSize.ScrollMax)
			{
				menu->m_sSize.ScrollValue = std::min(menu->m_sSize.ScrollMax, menu->m_sSize.ScrollValue + menu->m_sSize.ScrollDelta);
				menu->Update();
			}
		}

		void CMenu::ActivateSubmenu()
		{
			if (getActiveMenuItem() && getActiveMenuItem()->getMenu() && !getActiveMenuItem()->getMenu()->m_bVisible)
			{
				int index{ 0 };
				while (index < (int)getActiveMenuItem()->getMenu()->getMenuItemCount() && (getActiveMenuItem()->getMenu()->getMenuItem(index)->m_eType == CMenuItem::mitSeparator || !getActiveMenuItem()->getMenu()->getMenuItem(index)->m_bEnabled))
					index++;
				if (getActiveMenuItem()->getMenu()->getMenuItem(index) && getActiveMenuItem()->getMenu()->getMenuItem(index)->m_eType != CMenuItem::mitSeparator && getActiveMenuItem()->getMenu()->getMenuItem(index)->m_bEnabled)
					getActiveMenuItem()->getMenu()->m_iActiveMenuItemIndex = index;
				getActiveMenuItem()->getMenu()->Show(getWidth() + getActiveMenuItem()->m_sMenuShift.X, getActiveMenuItem()->m_sMenuShift.Y);
			}
		}

		bool CMenu::HitTest(const int x, const int y)
		{
			bool result{ false };
			if (getActiveMenuItem() && getActiveMenuItem()->getMenu() && getActiveMenuItem()->getMenu()->m_bVisible)
				result = getActiveMenuItem()->getMenu()->HitTest(x, y);
			if (!result)
			{
				APP_RECT r = ClientToForm(getRect());
				if (x >= r.Left && x < r.Right && y >= r.Top && y < r.Bottom)
					result = true;
			}
			return result;
		}

		bool CMenu::UpdateFromStyle()
		{
			if (!CBaseBlock::UpdateFromStyle())
				return false;
			m_sSize.ScrollDelta = std::min((size_t)1, getStyle()->getParameterByName(m_sClassName + L".ScrollDelta", m_sSize.ScrollDelta));
			m_bShowImages = getStyle()->getParameterByName(m_sClassName + L".ShowImages", m_bShowImages);
			m_sMarginTopScrollArrow = getStyle()->getParameterByName(m_sClassName + L".MarginTopScrollArrow", m_sMarginTopScrollArrow);
			m_sMarginBottomScrollArrow = getStyle()->getParameterByName(m_sClassName + L".MarginBottomScrollArrow", m_sMarginBottomScrollArrow);
			return true;
		}
	#pragma endregion

	#pragma region Process keys
		void CMenu::ProcessKeyUp()
		{
			CMenuItem *item{ getActiveMenuItem() };
			if (item && item->getMenu() && item->getMenu()->m_bVisible && item->getMenu()->getActiveMenuItem())
			{
				item->getMenu()->ProcessKeyUp();
				return;
			}
			int index{ m_iActiveMenuItemIndex - 1 };
			while (index >= 0 && getMenuItem(index) && (getMenuItem(index)->m_eType == CMenuItem::mitSeparator || !getMenuItem(index)->m_bEnabled))
				index--;
			if (!getMenuItem(index))
			{
				index = getMenuItemCount() - 1;
				while (index > m_iActiveMenuItemIndex && (getMenuItem(index)->m_eType == CMenuItem::mitSeparator || !getMenuItem(index)->m_bEnabled))
					index--;
			}
			if (!getMenuItem(index) || getMenuItem(index)->m_eType == CMenuItem::mitSeparator || !getMenuItem(index)->m_bEnabled)
				index = -1;
			setActiveMenuItemIndex(index);
		}

		void CMenu::ProcessKeyDown()
		{
			CMenuItem *item{ getActiveMenuItem() };
			if (item && item->getMenu() && item->getMenu()->m_bVisible && item->getMenu()->getActiveMenuItem())
			{
				item->getMenu()->ProcessKeyDown();
				return;
			}
			int index{ m_iActiveMenuItemIndex + 1 };
			while (index < (int)getMenuItemCount() && getMenuItem(index) && (getMenuItem(index)->m_eType == CMenuItem::mitSeparator || !getMenuItem(index)->m_bEnabled))
				index++;
			if (!getMenuItem(index))
			{
				index = 0;
				while (index < m_iActiveMenuItemIndex && (getMenuItem(index)->m_eType == CMenuItem::mitSeparator || !getMenuItem(index)->m_bEnabled))
					index++;
			}
			if (!getMenuItem(index) || getMenuItem(index)->m_eType == CMenuItem::mitSeparator || !getMenuItem(index)->m_bEnabled)
				index = -1;
			setActiveMenuItemIndex(index);
		}

		void CMenu::ProcessKeyHome()
		{
			CMenuItem *item{ getActiveMenuItem() };
			if (item && item->getMenu() && item->getMenu()->m_bVisible && item->getMenu()->getActiveMenuItem())
			{
				item->getMenu()->ProcessKeyHome();
				return;
			}
			int index{ 0 };
			while (index < (int)getMenuItemCount() && (getMenuItem(index)->m_eType == CMenuItem::mitSeparator || !getMenuItem(index)->m_bEnabled))
				index++;
			if (getMenuItem(index) && getMenuItem(index)->m_eType != CMenuItem::mitSeparator && getMenuItem(index)->m_bEnabled)
				setActiveMenuItemIndex(index);
		}

		void CMenu::ProcessKeyEnd()
		{
			CMenuItem *item{ getActiveMenuItem() };
			if (item && item->getMenu() && item->getMenu()->m_bVisible && item->getMenu()->getActiveMenuItem())
			{
				item->getMenu()->ProcessKeyEnd();
				return;
			}
			int index{ (int)getMenuItemCount() - 1 };
			while (index >= 0 && (getMenuItem(index)->m_eType == CMenuItem::mitSeparator || !getMenuItem(index)->m_bEnabled))
				index--;
			if (getMenuItem(index) && getMenuItem(index)->m_eType != CMenuItem::mitSeparator && getMenuItem(index)->m_bEnabled)
				setActiveMenuItemIndex(index);
		}

		void CMenu::ProcessKeyLeft()
		{
			CMenuItem *item{ getActiveMenuItem() };
			if (item && item->getMenu() && item->getMenu()->m_bVisible && item->getMenu()->getActiveMenuItem())
			{
				item->getMenu()->ProcessKeyLeft();
				return;
			}
			if (getParentMenuItem()) // Submenu of other menu
			{
				Hide();
				return;
			}
			// Submenu of main menu
			int index{ getMainMenu()->getActiveMenuItemIndex() - 1 };
			while (index >= 0 && getMainMenu()->getMenuItem(index) && !getMainMenu()->getMenuItem(index)->m_bEnabled)
				index--;
			if (!getMainMenu()->getMenuItem(index) || !getMainMenu()->getMenuItem(index)->m_bEnabled)
			{
				index = getMainMenu()->getMenuItemCount() - 1;
				while (index > getMainMenu()->getActiveMenuItemIndex() && !getMainMenu()->getMenuItem(index)->m_bEnabled)
					index--;
			}
			if (getMainMenu()->getMenuItem(index) && getMainMenu()->getMenuItem(index)->m_bEnabled)
				getMainMenu()->setActiveMenuItemIndex(index);
		}

		void CMenu::ProcessKeyRight()
		{
			CMenuItem *item{ getActiveMenuItem() };
			if (item && item->getMenu() && item->getMenu()->m_bVisible && item->getMenu()->getActiveMenuItem())
			{
				item->getMenu()->ProcessKeyRight();
				return;
			}
			if (item && item->getMenu())
			{
				ActivateSubmenu();
				return;
			}
			if (!getParentMenuItem())
			{
				int index{ getMainMenu()->getActiveMenuItemIndex() + 1 };
				while (index < (int)getMainMenu()->getMenuItemCount() && getMainMenu()->getMenuItem(index) && !getMainMenu()->getMenuItem(index)->m_bEnabled)
					index++;
				if (!getMainMenu()->getMenuItem(index) || !getMainMenu()->getMenuItem(index)->m_bEnabled)
				{
					index = 0;
					while (index < getMainMenu()->getActiveMenuItemIndex() && !getMainMenu()->getMenuItem(index)->m_bEnabled)
						index++;
				}
				if (getMainMenu()->getMenuItem(index) && getMainMenu()->getMenuItem(index)->m_bEnabled)
					getMainMenu()->setActiveMenuItemIndex(index);
			}
		}

		void CMenu::ProcessKeySpace()
		{
			CMenuItem *item{ getActiveMenuItem() };
			if (item && item->getMenu() && item->getMenu()->m_bVisible && item->getMenu()->getActiveMenuItem())
			{
				item->getMenu()->ProcessKeySpace();
				return;
			}
			if (item && (item->m_eType == CMenuItem::mitCheckBox || item->m_eType == CMenuItem::mitRadioButton))
				if (item->m_eState == CMenuItem::misNormal)
					item->setState(CMenuItem::misChecked);
				else if (item->m_eType != CMenuItem::mitRadioButton)
					item->setState(CMenuItem::misNormal);
		}

		void CMenu::ProcessKeyEnter()
		{
			CMenuItem *item{ getActiveMenuItem() };
			if (item && item->getMenu() && item->getMenu()->m_bVisible && item->getMenu()->getActiveMenuItem())
			{
				item->getMenu()->ProcessKeyEnter();
				return;
			}
			if (item)
			{
				m_pForm->LockRepaint();
				if (item->getMenu())
					ActivateSubmenu();
				else
				{
					item->NotifyOnClick();
					getMainMenu()->Deactivate();
				}
				m_pForm->UnlockRepaint();
			}
		}

		void CMenu::ProcessKeyEscape()
		{
			CMenuItem *item{ getActiveMenuItem() };
			if (item && item->getMenu() && item->getMenu()->m_bVisible && item->getMenu()->getActiveMenuItem())
			{
				item->getMenu()->ProcessKeyEscape();
				return;
			}
			if (item && item->getMenu() && item->getMenu()->m_bVisible)
				item->getMenu()->Hide();
			else
				Hide();
		}

		void CMenu::ProcessKeyTab()
		{
			ProcessKeyDown();
		}

		void CMenu::ProcessMouseUp()
		{
			if (m_hScrollTimer)
				StopScrollTimer();
			else if (getActiveMenuItem() && getActiveMenuItem()->getMenu() && getActiveMenuItem()->getMenu()->m_bVisible)
				getActiveMenuItem()->getMenu()->ProcessMouseUp();
		}

		bool CMenu::ProcessMouseWheel(const int x, const int y, const int delta)
		{
			if (getActiveMenuItem() && getActiveMenuItem()->getMenu() && getActiveMenuItem()->getMenu()->m_bVisible)
				if (getActiveMenuItem()->getMenu()->ProcessMouseWheel(x, y, delta))
					return true;
			APP_RECT r = ClientToForm(getRect());
			if (x >= r.Left && x < r.Right && y >= r.Top && y < r.Bottom)
			{
				if (m_sSize.ScrollExists)
				{
					size_t old{ m_sSize.ScrollValue };
					if (delta > 0)
						m_sSize.ScrollValue = std::max(0, (int)m_sSize.ScrollValue - (int)m_sSize.ScrollDelta);
					else
						m_sSize.ScrollValue = std::min(m_sSize.ScrollMax, m_sSize.ScrollValue + m_sSize.ScrollDelta);
					if (m_sSize.ScrollValue != old)
						Update();
				}
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Render
		void CMenu::RenderTopScrollArrow(APP_RECT clip)
		{
			if (m_sSize.ScrollExists)
			{
				APP_IMAGE *image;
				APP_RECT image_rect;
				if (SearchTopScrollArrow(&image, image_rect, false))
				{
					APP_RECT rect = ClientToForm(CalculateTopScrollArrowRect());
					APP_RECT new_clip{ rect.Left, rect.Top + (int)m_sMarginTopScrollArrow[0], rect.Right, rect.Bottom - (int)m_sMarginTopScrollArrow[1] };
					new_clip *= clip;
					if (new_clip.IsValid() && !new_clip.IsEmpty())
					{
						IImage *img{ m_pForm->getImageManager()->getImage(image) };
						if (img)
						{
							int x{ rect.Left + (rect.Width() - image_rect.Width()) / 2 };
							int y{ rect.Top + (int)m_sMarginTopScrollArrow[0] + (rect.Height() - (int)m_sMarginTopScrollArrow[0] - (int)m_sMarginTopScrollArrow[1] - image_rect.Height()) / 2 };
							m_pForm->getPresenter()->RenderImage(img, image_rect, x, y, 0, 1, 1, false, false, false, new_clip, rect, { 0, 0, 0, 0 }, { 0, 0, 0, 0 },
								0, graphics::bplInside, nullptr, nullptr, true);
						}
					}
				}
			}
		}

		void CMenu::RenderBottomScrollArrow(APP_RECT clip)
		{
			if (m_sSize.ScrollExists)
			{
				APP_IMAGE *image;
				APP_RECT image_rect;
				if (SearchBottomScrollArrow(&image, image_rect, false))
				{
					APP_RECT rect = ClientToForm(CalculateBottomScrollArrowRect());
					APP_RECT new_clip{ rect.Left, rect.Top + (int)m_sMarginBottomScrollArrow[0], rect.Right, rect.Bottom - (int)m_sMarginBottomScrollArrow[1] };
					new_clip *= clip;
					if (new_clip.IsValid() && !new_clip.IsEmpty())
					{
						IImage *img{ m_pForm->getImageManager()->getImage(image) };
						if (img)
						{
							int x{ rect.Left + (rect.Width() - image_rect.Width()) / 2 };
							int y{ rect.Top + (int)m_sMarginBottomScrollArrow[0] + (rect.Height() - (int)m_sMarginBottomScrollArrow[0] - (int)m_sMarginBottomScrollArrow[1] - image_rect.Height()) / 2 };
							m_pForm->getPresenter()->RenderImage(img, image_rect, x, y, 0, 1, 1, false, false, false, new_clip, rect, { 0, 0, 0, 0 }, { 0, 0, 0, 0 },
								0, graphics::bplInside, nullptr, nullptr, true);
						}
					}
				}
			}
		}
	#pragma endregion
	}
}