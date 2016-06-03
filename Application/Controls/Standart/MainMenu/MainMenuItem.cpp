// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#include "MainMenu.h"
#include "..\..\..\DefaultStyle.h"
#include "..\..\..\Style.h"
#include "..\..\..\StyleSkin.h"
#include "..\..\..\StyleImage.h"
#include "..\..\..\Presenter.h"
#include "..\..\..\ImageManager.h"

namespace licui
{
	namespace application
	{
	#pragma region Constructors
		CMainMenuItem::CMainMenuItem() :
			CControl(),
			m_sMarginCaption{ 10, 4, 10, 4 },
			m_sMenuShift{ 0, 0 },
			m_sActiveBackgroundColor{ 0, 0, 255, 255 },
			m_sActiveTextColor{ 255, 255, 255, 255 },
			m_sActiveShadowColor{ 255, 255, 255, 255 },
			m_sHoverBackgroundColor{ 200, 200, 200, 255 },
			m_sHoverTextColor{ 0, 0, 0, 255 },
			m_sHoverShadowColor{ 0, 0, 0, 255 },
			m_sDisabledTextColor{ 133, 135, 139, 255 },
			m_sDisabledShadowColor{ 133, 135, 139, 255 },
			m_eAlign{ ialLeft },
			m_bImageVisible{ false },
			m_iImageIndex{ -1 },
			m_eImageAlign{ ialLeft },
			m_sImageMargin{ 0, 0, 0, 0 },
			m_bArrowVisible{ false },
			m_eArrowAlign{ ialRight },
			m_sArrowMargin{ 4, 0, 4, 0 },
			m_fOnClick{ nullptr }
		{
			m_sClassName = L"CMainMenuItem";
			m_bSupportText = true;
		}

		CMainMenuItem::CMainMenuItem(CMainMenu *menu): CMainMenuItem()
		{
			if (menu)
				setMainMenu(menu);
		}
	#pragma endregion

	#pragma region Getters
		bool CMainMenuItem::getIsActive()
		{
			return getMainMenu() && getMainMenu()->getActiveMenuItem() == this;
		}

		CMainMenu *CMainMenuItem::getMainMenu()
		{
			return dynamic_cast<CMainMenu*>(getParent());
		}

		CMenu* CMainMenuItem::getMenu()
		{
			return dynamic_cast<CMenu*>(getControl(0));
		}

		String CMainMenuItem::getCaption() const
		{
			return m_sCaption;
		}

		math::RECTANGLE<size_t> CMainMenuItem::getMarginCaption() const
		{
			return m_sMarginCaption;
		}

		size_t CMainMenuItem::getMarginCaptionLeft() const
		{
			return m_sMarginCaption.Left;
		}

		size_t CMainMenuItem::getMarginCaptionTop() const
		{
			return m_sMarginCaption.Top;
		}

		size_t CMainMenuItem::getMarginCaptionRight() const
		{
			return m_sMarginCaption.Right;
		}

		size_t CMainMenuItem::getMarginCaptionBottom() const
		{
			return m_sMarginCaption.Bottom;
		}

		APP_POINT CMainMenuItem::getMenuShift() const
		{
			return m_sMenuShift;
		}

		int CMainMenuItem::getMenuShiftX() const
		{
			return m_sMenuShift.X;
		}

		int CMainMenuItem::getMenuShiftY() const
		{
			return m_sMenuShift.Y;
		}

		APP_COLOR CMainMenuItem::getActiveBackgroundColor() const
		{
			return m_sActiveBackgroundColor;
		}

		APP_COLOR CMainMenuItem::getActiveTextColor() const
		{
			return m_sActiveTextColor;
		}

		APP_COLOR CMainMenuItem::getActiveShadowColor() const
		{
			return m_sActiveShadowColor;
		}

		APP_COLOR CMainMenuItem::getHoverBackgroundColor() const
		{
			return m_sHoverBackgroundColor;
		}

		APP_COLOR CMainMenuItem::getHoverTextColor() const
		{
			return m_sHoverTextColor;
		}

		APP_COLOR CMainMenuItem::getHoverShadowColor() const
		{
			return m_sHoverShadowColor;
		}

		APP_COLOR CMainMenuItem::getDisabledTextColor() const
		{
			return m_sDisabledTextColor;
		}

		APP_COLOR CMainMenuItem::getDisabledShadowColor() const
		{
			return m_sDisabledShadowColor;
		}

		CMainMenuItem::ALIGN CMainMenuItem::getAlignment() const
		{
			return m_eAlign;
		}

		bool CMainMenuItem::getImageVisible() const
		{
			return m_bImageVisible;
		}

		int CMainMenuItem::getImageIndex() const
		{
			return m_iImageIndex;
		}

		CMainMenuItem::ALIGN CMainMenuItem::getImageAlign() const
		{
			return m_eImageAlign;
		}

		math::RECTANGLE<size_t> CMainMenuItem::getImageMargin() const
		{
			return m_sImageMargin;
		}

		size_t CMainMenuItem::getImageMarginLeft() const
		{
			return m_sImageMargin.Left;
		}

		size_t CMainMenuItem::getImageMarginTop() const
		{
			return m_sImageMargin.Top;
		}

		size_t CMainMenuItem::getImageMarginRight() const
		{
			return m_sImageMargin.Right;
		}

		size_t CMainMenuItem::getImageMarginBottom() const
		{
			return m_sImageMargin.Bottom;
		}

		bool CMainMenuItem::getArrowVisible() const
		{
			return m_bArrowVisible;
		}

		CMainMenuItem::ALIGN CMainMenuItem::getArrowAlign() const
		{
			return m_eArrowAlign;
		}

		math::RECTANGLE<size_t> CMainMenuItem::getArrowMargin() const
		{
			return m_sArrowMargin;
		}

		size_t CMainMenuItem::getArrowMarginLeft() const
		{
			return m_sArrowMargin.Left;
		}

		size_t CMainMenuItem::getArrowMarginTop() const
		{
			return m_sArrowMargin.Top;
		}

		size_t CMainMenuItem::getArrowMarginRight() const
		{
			return m_sArrowMargin.Right;
		}

		size_t CMainMenuItem::getArrowMarginBottom() const
		{
			return m_sArrowMargin.Bottom;
		}

		CMenuItem::FOnClick CMainMenuItem::getOnClick() const
		{
			return m_fOnClick;
		}
	#pragma endregion

	#pragma region Setters
		CMainMenuItem *CMainMenuItem::setMainMenu(CMainMenu *value)
		{
			if (value != getMainMenu())
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
					value->Update();
				}
				if (form)
					form->UnlockRepaint();
			}
			return this;
		}

		CMainMenuItem *CMainMenuItem::setMenu(CMenu *value)
		{
			if (value != getMenu())
			{
				if (m_pForm)
					m_pForm->LockRepaint();
				DeleteControls();
				if (value)
				{
					value->m_bAcceptParent = true;
					m_bAcceptControls = true;
					AddControl(value);
					value->m_bAcceptParent = false;
					m_bAcceptControls = false;
				}
				if (m_pForm)
					m_pForm->UnlockRepaint();
			}
			return this;
		}

		CMainMenuItem *CMainMenuItem::setCaption(const String &value)
		{
			if (value != m_sCaption)
			{
				m_sCaption = value;
				if (getMainMenu())
					getMainMenu()->Update();
			}
			return this;
		}

		CMainMenuItem *CMainMenuItem::setMarginCaption(const math::RECTANGLE<size_t> &value)
		{
			if (value != m_sMarginCaption)
			{
				m_sMarginCaption = value;
				if (getMainMenu())
					getMainMenu()->Update();
			}
			return this;
		}

		CMainMenuItem *CMainMenuItem::setMarginCaptionLeft(const size_t value)
		{
			if (value != m_sMarginCaption.Left)
			{
				m_sMarginCaption.Left = value;
				if (getMainMenu())
					getMainMenu()->Update();
			}
			return this;
		}

		CMainMenuItem *CMainMenuItem::setMarginCaptionTop(const size_t value)
		{
			if (value != m_sMarginCaption.Top)
			{
				m_sMarginCaption.Top = value;
				if (getMainMenu())
					getMainMenu()->Update();
			}
			return this;
		}

		CMainMenuItem *CMainMenuItem::setMarginCaptionRight(const size_t value)
		{
			if (value != m_sMarginCaption.Right)
			{
				m_sMarginCaption.Right = value;
				if (getMainMenu())
					getMainMenu()->Update();
			}
			return this;
		}

		CMainMenuItem *CMainMenuItem::setMarginCaptionBottom(const size_t value)
		{
			if (value != m_sMarginCaption.Bottom)
			{
				m_sMarginCaption.Bottom = value;
				if (getMainMenu())
					getMainMenu()->Update();
			}
			return this;
		}

		CMainMenuItem *CMainMenuItem::setMenuShift(const APP_POINT &value)
		{
			if (value != m_sMenuShift)
			{
				m_sMenuShift = value;
				if (getMenu() && getMenu()->m_bVisible)
					getMenu()->Show(m_sMenuShift.X, getHeight() + m_sMenuShift.Y);
			}
			return this;
		}

		CMainMenuItem *CMainMenuItem::setMenuShiftX(const int value)
		{
			if (value != m_sMenuShift.X)
			{
				m_sMenuShift.X = value;
				if (getMenu() && getMenu()->m_bVisible)
					getMenu()->Show(m_sMenuShift.X, getHeight() + m_sMenuShift.Y);
			}
			return this;
		}

		CMainMenuItem *CMainMenuItem::setMenuShiftY(const int value)
		{
			if (value != m_sMenuShift.Y)
			{
				m_sMenuShift.Y = value;
				if (getMenu() && getMenu()->m_bVisible)
					getMenu()->Show(m_sMenuShift.X, getHeight() + m_sMenuShift.Y);
			}
			return this;
		}

		CMainMenuItem *CMainMenuItem::setActiveBackgroundColor(const APP_COLOR &value)
		{
			if (value != m_sActiveBackgroundColor)
			{
				m_sActiveBackgroundColor = value;
				if (getIsActive())
					Repaint(false);
			}
			return this;
		}

		CMainMenuItem *CMainMenuItem::setActiveTextColor(const APP_COLOR &value)
		{
			if (value != m_sActiveTextColor)
			{
				m_sActiveTextColor = value;
				if (getIsActive())
					Repaint(false);
			}
			return this;
		}

		CMainMenuItem *CMainMenuItem::setActiveShadowColor(const APP_COLOR &value)
		{
			if (value != m_sActiveShadowColor)
			{
				m_sActiveShadowColor = value;
				if (getIsActive())
					Repaint(false);
			}
			return this;
		}

		CMainMenuItem *CMainMenuItem::setHoverBackgroundColor(const APP_COLOR &value)
		{
			if (value != m_sHoverBackgroundColor)
			{
				m_sHoverBackgroundColor = value;
				if (m_bEnabled && m_pForm && m_pForm->getHoveredControl() == this)
					Repaint(false);
			}
			return this;
		}

		CMainMenuItem *CMainMenuItem::setHoverTextColor(const APP_COLOR &value)
		{
			if (value != m_sHoverTextColor)
			{
				m_sHoverTextColor = value;
				if (m_bEnabled && m_pForm && m_pForm->getHoveredControl() == this)
					Repaint(false);
			}
			return this;
		}

		CMainMenuItem *CMainMenuItem::setHoverShadowColor(const APP_COLOR &value)
		{
			if (value != m_sHoverShadowColor)
			{
				m_sHoverShadowColor = value;
				if (m_bEnabled && m_pForm && m_pForm->getHoveredControl() == this)
					Repaint(false);
			}
			return this;
		}

		CMainMenuItem *CMainMenuItem::setDisabledTextColor(const APP_COLOR &value)
		{
			if (value != m_sDisabledTextColor)
			{
				m_sDisabledTextColor = value;
				if (!m_bEnabled)
					Repaint(false);
			}
			return this;
		}

		CMainMenuItem *CMainMenuItem::setDisabledShadowColor(const APP_COLOR &value)
		{
			if (value != m_sDisabledShadowColor)
			{
				m_sDisabledShadowColor = value;
				if (!m_bEnabled)
					Repaint(false);
			}
			return this;
		}

		CMainMenuItem *CMainMenuItem::setAlignment(const ALIGN value)
		{
			if (value != m_eAlign)
			{
				m_eAlign = value;
				if (getMainMenu())
					getMainMenu()->Update();
			}
			return this;
		}

		CMainMenuItem *CMainMenuItem::setImageVisible(const bool value)
		{
			if (value != m_bImageVisible)
			{
				m_bImageVisible = value;
				if (getMainMenu())
					getMainMenu()->Update();
			}
			return this;
		}

		CMainMenuItem *CMainMenuItem::setImageIndex(int value)
		{
			if (value < -1)
				value = -1;
			if (value != m_iImageIndex)
			{
				m_iImageIndex = value;
				if (getMainMenu())
					getMainMenu()->Update();
			}
			return this;
		}

		CMainMenuItem *CMainMenuItem::setImageAlign(const ALIGN value)
		{
			if (value != m_eImageAlign)
			{
				m_eImageAlign = value;
				if (m_bImageVisible)
					Repaint(false);
			}
			return this;
		}

		CMainMenuItem *CMainMenuItem::setImageMargin(const math::RECTANGLE<size_t> &value)
		{
			if (value != m_sImageMargin)
			{
				m_sImageMargin = value;
				if (m_bImageVisible && getMainMenu())
					getMainMenu()->Update();
			}
			return this;
		}

		CMainMenuItem *CMainMenuItem::setImageMarginLeft(const size_t value)
		{
			if (value != m_sImageMargin.Left)
			{
				m_sImageMargin.Left = value;
				if (m_bImageVisible && getMainMenu())
					getMainMenu()->Update();
			}
			return this;
		}

		CMainMenuItem *CMainMenuItem::setImageMarginTop(const size_t value)
		{
			if (value != m_sImageMargin.Top)
			{
				m_sImageMargin.Top = value;
				if (m_bImageVisible && getMainMenu())
					getMainMenu()->Update();
			}
			return this;
		}

		CMainMenuItem *CMainMenuItem::setImageMarginRight(const size_t value)
		{
			if (value != m_sImageMargin.Right)
			{
				m_sImageMargin.Right = value;
				if (m_bImageVisible && getMainMenu())
					getMainMenu()->Update();
			}
			return this;
		}

		CMainMenuItem *CMainMenuItem::setImageMarginBottom(const size_t value)
		{
			if (value != m_sImageMargin.Bottom)
			{
				m_sImageMargin.Bottom = value;
				if (m_bImageVisible && getMainMenu())
					getMainMenu()->Update();
			}
			return this;
		}

		CMainMenuItem *CMainMenuItem::setArrowVisible(const bool value)
		{
			if (value != m_bArrowVisible)
			{
				m_bArrowVisible = value;
				if (getMainMenu())
					getMainMenu()->Update();
			}
			return this;
		}

		CMainMenuItem *CMainMenuItem::setArrowAlign(const ALIGN value)
		{
			if (value != m_eArrowAlign)
			{
				m_eArrowAlign = value;
				if (m_bArrowVisible && getMainMenu())
					getMainMenu()->Update();
			}
			return this;
		}

		CMainMenuItem *CMainMenuItem::setArrowMargin(const math::RECTANGLE<size_t> &value)
		{
			if (value != m_sArrowMargin)
			{
				m_sArrowMargin = value;
				if (m_bArrowVisible && getMainMenu())
					getMainMenu()->Update();
			}
			return this;
		}

		CMainMenuItem *CMainMenuItem::setArrowMarginLeft(const size_t value)
		{
			if (value != m_sArrowMargin.Left)
			{
				m_sArrowMargin.Left = value;
				if (m_bArrowVisible && getMainMenu())
					getMainMenu()->Update();
			}
			return this;
		}

		CMainMenuItem *CMainMenuItem::setArrowMarginTop(const size_t value)
		{
			if (value != m_sArrowMargin.Top)
			{
				m_sArrowMargin.Top = value;
				if (m_bArrowVisible && getMainMenu())
					getMainMenu()->Update();
			}
			return this;
		}

		CMainMenuItem *CMainMenuItem::setArrowMarginRight(const size_t value)
		{
			if (value != m_sArrowMargin.Right)
			{
				m_sArrowMargin.Right = value;
				if (m_bArrowVisible && getMainMenu())
					getMainMenu()->Update();
			}
			return this;
		}

		CMainMenuItem *CMainMenuItem::setArrowMarginBottom(const size_t value)
		{
			if (value != m_sArrowMargin.Bottom)
			{
				m_sArrowMargin.Bottom = value;
				if (m_bArrowVisible && getMainMenu())
					getMainMenu()->Update();
			}
			return this;
		}

		CMainMenuItem *CMainMenuItem::setOnClick(CMenuItem::FOnClick value)
		{
			m_fOnClick = value;
			return this;
		}
	#pragma endregion

	#pragma region Notifications
		bool CMainMenuItem::NotifyOnLeftMouseButtonDown(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			if (m_bEnabled)
			{
				if (getMainMenu()->getIsActive())
				{
					if (getMainMenu()->getActiveMenuItem() == this)
					{
						if (getMenu())
							if (getMenu()->m_bVisible)
								getMenu()->Hide();
							else
								getMenu()->Show(m_sMenuShift.X, getHeight() + m_sMenuShift.Y);
					}
					else
					{
						getMainMenu()->setActiveMenuItem(this);
						if (getMenu())
							if (!getMenu()->m_bVisible)
								getMenu()->Show(m_sMenuShift.X, getHeight() + m_sMenuShift.Y);
					}
				}
				else
				{
					getMainMenu()->Activate();
					getMainMenu()->setActiveMenuItem(this);
					if (getMenu())
						getMenu()->Show(m_sMenuShift.X, getHeight() + m_sMenuShift.Y);
				}
			}
			return CControl::NotifyOnLeftMouseButtonDown(x, y, ctrl, left, middle, right, shift);
		}

		bool CMainMenuItem::NotifyOnLeftMouseButtonUp(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			if (!m_bEnabled || !getMenu() || !getMenu()->m_bVisible)
			{
				getMainMenu()->Deactivate();
				if (m_bEnabled && !getMenu())
					NotifyOnClick();
			}
			return CControl::NotifyOnLeftMouseButtonUp(x, y, ctrl, left, middle, right, shift);
		}

		void CMainMenuItem::NotifyOnChangeUseParentFont()
		{
			CControl::NotifyOnChangeUseParentFont();
			getMainMenu()->Update();
		}

		void CMainMenuItem::NotifyOnParentFontChangeSize()
		{
			CControl::NotifyOnParentFontChangeSize();
			getMainMenu()->Update();
		}

		void CMainMenuItem::NotifyOnFontChangeSize()
		{
			CControl::NotifyOnFontChangeSize();
			if (getMainMenu())
				getMainMenu()->Update();
		}

		void CMainMenuItem::NotifyOnMouseHover()
		{
			if (m_bEnabled)
			{
				if (getMainMenu()->getIsActive())
					getMainMenu()->setActiveMenuItem(this);
				else
					Repaint(true);
			}
			CControl::NotifyOnMouseHover();
		}

		void CMainMenuItem::NotifyOnMouseLeave()
		{
			if (m_bEnabled)
				Repaint(false);
			CControl::NotifyOnMouseLeave();
		}

		void CMainMenuItem::NotifyOnChangeParentStyle()
		{
			CControl::NotifyOnChangeParentStyle();
			getMainMenu()->Update();
		}

		void CMainMenuItem::NotifyOnChangeStyle()
		{
			CControl::NotifyOnChangeStyle();
			if (getMainMenu())
				getMainMenu()->Update();
		}

		void CMainMenuItem::NotifyOnDisable()
		{
			if (getMainMenu() && getMainMenu()->getActiveMenuItem() == this)
				getMainMenu()->Deactivate();
			CControl::NotifyOnDisable();
		}

		void CMainMenuItem::NotifyOnPaint(APP_RECT clip)
		{
			Paint(clip);
			CControl::NotifyOnPaint(clip);
		}

		void CMainMenuItem::NotifyOnClick()
		{
			if (m_fOnClick)
				m_fOnClick(this, getCallbackParam());
			getMainMenu()->NotifyOnClick(this);
		}
	#pragma endregion

	#pragma region Helpers
		math::POINT<size_t> CMainMenuItem::CalculateSize()
		{
			math::POINT<size_t> result{ 0, 0 };
			APP_POINT size_caption = getFont()->getStringSize(m_sCaption), size_w = getFont()->getStringSize(L"W");
			APP_IMAGE *image, *arrow_image;
			APP_RECT image_rect, arrow_rect;
			bool have_image{ SearchImage(&image, image_rect) }, have_arrow_image{ SearchArrowImage(&arrow_image, arrow_rect, true) };
			result.Y = std::max(result.Y, size_w.Y + m_sMarginCaption.Top + m_sMarginCaption.Bottom);
			if (have_image)
			{
				result.Y = std::max(result.Y, image_rect.Height() + m_sImageMargin.Top + m_sImageMargin.Bottom);
				result.X += image_rect.Width() + m_sImageMargin.Left + m_sImageMargin.Right;
			}
			if (!m_sCaption.empty())
			{
				result.Y = std::max(result.Y, size_caption.Y + m_sMarginCaption.Top + m_sMarginCaption.Bottom);
				result.X += std::max(size_w.X, size_caption.X) + m_sMarginCaption.Left + m_sMarginCaption.Right;
			}
			if (have_arrow_image)
			{
				result.Y = std::max(result.Y, arrow_rect.Height() + m_sArrowMargin.Top + m_sArrowMargin.Bottom);
				result.X += arrow_rect.Width() + m_sArrowMargin.Left + m_sArrowMargin.Right;
			}
			return result;
		}

		APP_RECT CMainMenuItem::CalculateRectImage()
		{
			APP_RECT result = { 0, 0, 0, 0 }, image_rect;
			APP_IMAGE *image;
			if (SearchImage(&image, image_rect))
			{
				result = getRect();
				if (m_eImageAlign == ialLeft)
					result.Right = std::min(result.Left + image_rect.Width() + (int)m_sImageMargin.Left + (int)m_sImageMargin.Right, getRect().Right);
				else
					result.Left = std::max(result.Right - image_rect.Width() - (int)m_sImageMargin.Left - (int)m_sImageMargin.Right, getRect().Left);
			}
			return result;
		}

		APP_RECT CMainMenuItem::CalculateRectCaptionWithArrow()
		{
			APP_RECT result = getRect(), image_rect = CalculateRectImage();
			if (!image_rect.IsEmpty())
				if (m_eImageAlign == ialLeft)
					result.Left = image_rect.Right;
				else
					result.Right = image_rect.Left;
			return result;
		}

		APP_RECT CMainMenuItem::CalculateRectArrow()
		{
			APP_RECT result = { 0, 0, 0, 0 }, image_rect;
			APP_IMAGE *image;
			if (SearchArrowImage(&image, image_rect, true))
			{
				result = CalculateRectCaptionWithArrow();
				APP_RECT start = result;
				if (m_eArrowAlign == ialLeft)
					result.Right = std::min(result.Left + image_rect.Width() + (int)m_sArrowMargin.Left + (int)m_sArrowMargin.Right, start.Right);
				else
					result.Left = std::max(result.Right - image_rect.Width() - (int)m_sArrowMargin.Left - (int)m_sArrowMargin.Right, start.Left);
			}
			return result;
		}

		APP_RECT CMainMenuItem::CalculateRectCaption()
		{
			APP_RECT result = CalculateRectCaptionWithArrow(), arrow_rect = CalculateRectArrow();
			if (!arrow_rect.IsEmpty())
				if (m_eArrowAlign == ialLeft)
					result.Left = arrow_rect.Right;
				else
					result.Right = arrow_rect.Left;
			return result;
		}

		bool CMainMenuItem::SearchImage(APP_IMAGE **image, APP_RECT &rect)
		{
			if (m_bImageVisible && m_iImageIndex >= 0 && getMainMenu() && getMainMenu()->getImageList() && (*image = getMainMenu()->getImageList()->getImage(m_iImageIndex)))
			{
				rect = { 0, 0, (int)(*image)->getWidth(), (int)(*image)->getHeight() };
				return rect.Width() > 0 && rect.Height() > 0;
			}
			return false;
		}

		bool CMainMenuItem::SearchArrowImage(APP_IMAGE **image, APP_RECT &rect, const bool ignore_state)
		{
			if (!m_bArrowVisible)
				return false;
			String name{ m_sClassName + L".Arrow" };
			if (ignore_state)
				name += L".normal";
			else
			{
				if (!m_bEnabled)
					name += L".disabled";
				else
					if (getIsActive())
						name += L".active";
					else
						if (m_pForm && m_pForm->getHoveredControl() == this)
							name += L".hovered";
						else
							name += L".normal";
			}
			CStyle *style{ getStyle() }, *def{ GetDefaultStyle() };
			if (!style)
				style = def;
			CStyleSkin *skin{ style->getSkinByName(name) };
			if (!skin)
				skin = def->getSkinByName(name);
			if (!skin || !skin->getImage())
				return false;
			*image = skin->getImage()->getImage();
			if (!(*image))
				return false;
			rect = skin->getRect();
			return rect.Width() > 0 && rect.Height() > 0;
		}

		bool CMainMenuItem::UpdateFromStyle()
		{
			if (!getStyle())
				return false;
			m_sMarginCaption = getStyle()->getParameterByName(m_sClassName + L".MarginCaption", m_sMarginCaption);
			m_sMenuShift = getStyle()->getParameterByName(m_sClassName + L".MenuShift", m_sMenuShift);
			m_sActiveBackgroundColor = getStyle()->getParameterByName(m_sClassName + L".ActiveBackgroundColor", m_sActiveBackgroundColor);
			m_sActiveTextColor = getStyle()->getParameterByName(m_sClassName + L".ActiveTextColor", m_sActiveTextColor);
			m_sActiveShadowColor = getStyle()->getParameterByName(m_sClassName + L".ActiveShadowColor", m_sActiveShadowColor);
			m_sHoverBackgroundColor = getStyle()->getParameterByName(m_sClassName + L".HoverBackgroundColor", m_sHoverBackgroundColor);
			m_sHoverTextColor = getStyle()->getParameterByName(m_sClassName + L".HoverTextColor", m_sHoverTextColor);
			m_sHoverShadowColor = getStyle()->getParameterByName(m_sClassName + L".HoverShadowColor", m_sHoverShadowColor);
			m_sDisabledTextColor = getStyle()->getParameterByName(m_sClassName + L".DisabledTextColor", m_sDisabledTextColor);
			m_sDisabledShadowColor = getStyle()->getParameterByName(m_sClassName + L".DisabledShadowColor", m_sDisabledShadowColor);
			m_bImageVisible = getStyle()->getParameterByName(m_sClassName + L".ImageVisible", m_bImageVisible);
			m_eImageAlign = (ALIGN)getStyle()->getParameterByName(m_sClassName + L".ImageAlign", (int)m_eImageAlign);
			m_sImageMargin = getStyle()->getParameterByName(m_sClassName + L".ImageMargin", m_sImageMargin);
			m_bArrowVisible = getStyle()->getParameterByName(m_sClassName + L".ArrowVisible", m_bArrowVisible);
			m_eArrowAlign = (ALIGN)getStyle()->getParameterByName(m_sClassName + L".ArrowAlign", (int)m_eArrowAlign);
			m_sArrowMargin = getStyle()->getParameterByName(m_sClassName + L".ArrowMargin", m_sArrowMargin);
			return true;
		}

		void CMainMenuItem::Paint(APP_RECT clip)
		{
			if (m_bEnabled)
				if (getIsActive())
					m_pForm->getPresenter()->FillRect(m_sActiveBackgroundColor, clip, ClientToForm(getRect()), ClientToForm(getRect()), { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, 0, graphics::bplInside, nullptr, nullptr, true);
				else
					if (m_pForm->getHoveredControl() == this)
						m_pForm->getPresenter()->FillRect(m_sHoverBackgroundColor, clip, ClientToForm(getRect()), ClientToForm(getRect()), { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, 0, graphics::bplInside, nullptr, nullptr, true);
			APP_RECT image_rect;
			APP_IMAGE *image;
			if (SearchImage(&image, image_rect))
			{
				APP_RECT rect = ClientToForm(CalculateRectImage()),
					new_clip{ rect.Left + (int)m_sImageMargin.Left, rect.Top + (int)m_sImageMargin.Top, rect.Right - (int)m_sImageMargin.Right, rect.Bottom - (int)m_sImageMargin.Bottom };
				new_clip *= clip;
				if (!rect.IsEmpty() && new_clip.IsValid() && !new_clip.IsEmpty())
				{
					IImage *img{ m_pForm->getImageManager()->getImage(image) };
					if (img)
					{
						int x{ rect.Left + (int)m_sImageMargin.Left + (rect.Width() - (int)m_sImageMargin.Left - (int)m_sImageMargin.Right - (int)image_rect.Width()) / 2 };
						int y{ rect.Top + (int)m_sImageMargin.Top + (rect.Height() - (int)m_sImageMargin.Top - (int)m_sImageMargin.Bottom - (int)image_rect.Height()) / 2 };
						m_pForm->getPresenter()->RenderImage(img, image_rect, x, y, 0, 1, 1, false, false, false, new_clip, rect, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, 0, graphics::bplInside, nullptr, nullptr, true);
					}
				}
			}
			if (SearchArrowImage(&image, image_rect, false))
			{
				APP_RECT rect = ClientToForm(CalculateRectArrow()),
					new_clip{ rect.Left + (int)m_sArrowMargin.Left, rect.Top + (int)m_sArrowMargin.Top, rect.Right - (int)m_sArrowMargin.Right, rect.Bottom - (int)m_sArrowMargin.Bottom };
				new_clip *= clip;
				if (!rect.IsEmpty() && new_clip.IsValid() && !new_clip.IsEmpty())
				{
					IImage *img{ m_pForm->getImageManager()->getImage(image) };
					if (img)
					{
						int x{ rect.Left + (int)m_sArrowMargin.Left + (rect.Width() - (int)m_sArrowMargin.Left - (int)m_sArrowMargin.Right - (int)image_rect.Width()) / 2 };
						int y{ rect.Top + (int)m_sArrowMargin.Top + (rect.Height() - (int)m_sArrowMargin.Top - (int)m_sArrowMargin.Bottom - (int)image_rect.Height()) / 2 };
						m_pForm->getPresenter()->RenderImage(img, image_rect, x, y, 0, 1, 1, false, false, false, new_clip, rect, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, 0, graphics::bplInside, nullptr, nullptr, true);
					}
				}
			}
			if (!m_sCaption.empty())
			{
				APP_RECT rect = ClientToForm(CalculateRectCaption()),
					new_clip{ rect.Left + (int)m_sMarginCaption.Left, rect.Top + (int)m_sMarginCaption.Top, rect.Right - (int)m_sMarginCaption.Right, rect.Bottom - (int)m_sMarginCaption.Bottom };
				new_clip *= clip;
				if (!rect.IsEmpty() && new_clip.IsValid() && !new_clip.IsEmpty())
				{
					APP_POINT size = getFont()->getStringSize(m_sCaption);
					int x{ rect.Left + (int)m_sMarginCaption.Left };
					int y{ rect.Top + (int)m_sMarginCaption.Top + (rect.Height() - (int)m_sMarginCaption.Top - (int)m_sMarginCaption.Bottom - size.Y) / 2 };
					APP_COLOR text_color{ getFont()->getColor() }, shadow_color{ getFont()->getColor() };
					if (!m_bEnabled)
					{
						text_color = m_sDisabledTextColor;
						shadow_color = m_sDisabledShadowColor;
					}
					else if (getIsActive())
					{
						text_color = m_sActiveTextColor;
						shadow_color = m_sActiveShadowColor;
					}
					else if (m_pForm->getHoveredControl() == this)
					{
						text_color = m_sHoverTextColor;
						shadow_color = m_sHoverShadowColor;
					}
					m_pForm->getPresenter()->RenderString(m_sCaption, getFont(), x, y, 0, 1, 1, new_clip, 0, rect, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, 0, graphics::bplInside, true, true, text_color, shadow_color, nullptr, nullptr, true);
				}
			}
		}
	#pragma endregion
	}
}