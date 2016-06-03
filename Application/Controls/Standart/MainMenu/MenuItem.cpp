// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#include "MainMenu.h"
#include "..\..\..\DefaultStyle.h"
#include "..\..\..\Style.h"
#include "..\..\..\StyleSkin.h"
#include "..\..\..\StyleImage.h"
#include "..\..\..\ImageManager.h"
#include "..\..\..\Presenter.h"

namespace licui
{
	namespace application
	{
	#pragma region Constructors
		CMenuItem::CMenuItem():
			CControl(),
			m_eType{ mitNormal },
			m_eState{ misNormal },
			m_sMarginImage{ 2, 2, 2, 2 },
			m_sMarginCaptionImage{ 2, 2, 2, 2 },
			m_sMarginCaption{ 4, 4, 4, 4 },
			m_sMarginShortcut{ 4, 4, 4, 4 },
			m_sMarginArrow{ 4, 4, 4, 4 },
			m_iImageIndex{ -1 },
			m_iGroupIndex{ 0 },
			m_sShortcut{ IWindow::keyUnknown, false, false, false },
			m_iSeparatorHeight{ 2 },
			m_sSeparatorColor{ 225, 225, 225, 255 },
			m_sDisabledTextColor{ 133, 135, 139, 255 },
			m_sDisabledShadowColor{ 133, 135, 139, 255 },
			m_sActiveBackgroundColor{ 0, 0, 255, 255 },
			m_sActiveTextColor{ 255, 255, 255, 255 },
			m_sActiveShadowColor{ 255, 255, 255, 255 },
			m_fOnClick{ nullptr },
			m_sMenuShift{ 0, 0 }
		{
			m_sClassName = L"CMenuItem";
			m_bSupportText = true;
		}

		CMenuItem::CMenuItem(CMenu *menu) :CMenuItem()
		{
			setParentMenu(menu);
		}
	#pragma endregion

	#pragma region Getters
		APP_RECT CMenuItem::getVisibleRect()
		{
			APP_RECT result = ClientToForm(getRenderRect());
			if (getParentMenu())
				result *= getParentMenu()->ClientToForm(getParentMenu()->getClientRect());
			return result;
		}

		CMainMenu *CMenuItem::getMainMenu()
		{
			if (getParentMenu())
				return getParentMenu()->getMainMenu();
			return nullptr;
		}

		CMenu *CMenuItem::getParentMenu()
		{
			return dynamic_cast<CMenu*>(getParent());
		}

		CMenu *CMenuItem::getMenu()
		{
			return dynamic_cast<CMenu*>(getControl(0));
		}

		bool CMenuItem::getIsActive()
		{
			return getParentMenu() && getParentMenu()->getActiveMenuItem() == this;
		}

		CMenuItem::TYPE CMenuItem::getType() const
		{
			return m_eType;
		}

		CMenuItem::STATE CMenuItem::getState() const
		{
			return m_eState;
		}

		math::RECTANGLE<size_t> CMenuItem::getMarginImage() const
		{
			return m_sMarginImage;
		}

		size_t CMenuItem::getMarginImageLeft() const
		{
			return m_sMarginImage.Left;
		}

		size_t CMenuItem::getMarginImageTop() const
		{
			return m_sMarginImage.Top;
		}

		size_t CMenuItem::getMarginImageRight() const
		{
			return m_sMarginImage.Right;
		}

		size_t CMenuItem::getMarginImageBottom() const
		{
			return m_sMarginImage.Bottom;
		}

		math::RECTANGLE<size_t> CMenuItem::getMarginCaptionImage() const
		{
			return m_sMarginCaptionImage;
		}

		size_t CMenuItem::getMarginCaptionImageLeft() const
		{
			return m_sMarginCaptionImage.Left;
		}

		size_t CMenuItem::getMarginCaptionImageTop() const
		{
			return m_sMarginCaptionImage.Top;
		}

		size_t CMenuItem::getMarginCaptionImageRight() const
		{
			return m_sMarginCaptionImage.Right;
		}

		size_t CMenuItem::getMarginCaptionImageBottom() const
		{
			return m_sMarginCaptionImage.Bottom;
		}

		math::RECTANGLE<size_t> CMenuItem::getMarginCaption() const
		{
			return m_sMarginCaption;
		}

		size_t CMenuItem::getMarginCaptionLeft() const
		{
			return m_sMarginCaption.Left;
		}

		size_t CMenuItem::getMarginCaptionTop() const
		{
			return m_sMarginCaption.Top;
		}

		size_t CMenuItem::getMarginCaptionRight() const
		{
			return m_sMarginCaption.Right;
		}

		size_t CMenuItem::getMarginCaptionBottom() const
		{
			return m_sMarginCaption.Bottom;
		}

		math::RECTANGLE<size_t> CMenuItem::getMarginShortcut() const
		{
			return m_sMarginShortcut;
		}

		size_t CMenuItem::getMarginShortcutLeft() const
		{
			return m_sMarginShortcut.Left;
		}

		size_t CMenuItem::getMarginShortcutTop() const
		{
			return m_sMarginShortcut.Top;
		}

		size_t CMenuItem::getMarginShortcutRight() const
		{
			return m_sMarginShortcut.Right;
		}

		size_t CMenuItem::getMarginShortcutBottom() const
		{
			return m_sMarginShortcut.Bottom;
		}

		math::RECTANGLE<size_t> CMenuItem::getMarginArrow() const
		{
			return m_sMarginArrow;
		}

		size_t CMenuItem::getMarginArrowLeft() const
		{
			return m_sMarginArrow.Left;
		}

		size_t CMenuItem::getMarginArrowTop() const
		{
			return m_sMarginArrow.Top;
		}

		size_t CMenuItem::getMarginArrowRight() const
		{
			return m_sMarginArrow.Right;
		}

		size_t CMenuItem::getMarginArrowBottom() const
		{
			return m_sMarginArrow.Bottom;
		}

		int CMenuItem::getImageIndex() const
		{
			return m_iImageIndex;
		}

		CImageList *CMenuItem::getImageList()
		{
			if (getParentMenu())
				return getParentMenu()->getImageList();
			return nullptr;
		}

		size_t CMenuItem::getGroupIndex() const
		{
			return m_iGroupIndex;
		}

		String CMenuItem::getCaption() const
		{
			return m_sCaption;
		}

		CForm::SHORTCUT CMenuItem::getShortcut() const
		{
			return m_sShortcut;
		}

		String CMenuItem::getShortcutName() const
		{
			return m_sShortcutName;
		}

		size_t CMenuItem::getSeparatorHeight() const
		{
			return m_iSeparatorHeight;
		}

		APP_COLOR CMenuItem::getSeparatorColor() const
		{
			return m_sSeparatorColor;
		}

		APP_COLOR CMenuItem::getDisabledTextColor() const
		{
			return m_sDisabledTextColor;
		}

		APP_COLOR CMenuItem::getDisabledShadowColor() const
		{
			return m_sDisabledShadowColor;
		}

		APP_COLOR CMenuItem::getActiveBackgroundColor() const
		{
			return m_sActiveBackgroundColor;
		}

		APP_COLOR CMenuItem::getActiveTextColor() const
		{
			return m_sActiveTextColor;
		}

		APP_COLOR CMenuItem::getActiveShadowColor() const
		{
			return m_sActiveShadowColor;
		}

		CMenuItem::FOnClick CMenuItem::getOnClick() const
		{
			return m_fOnClick;
		}

		APP_POINT CMenuItem::getMenuShift() const
		{
			return m_sMenuShift;
		}

		int CMenuItem::getMenuShiftX() const
		{
			return m_sMenuShift.X;
		}

		int CMenuItem::getMenuShiftY() const
		{
			return m_sMenuShift.Y;
		}
	#pragma endregion

	#pragma region Setters
		CMenuItem *CMenuItem::setParentMenu(CMenu *value)
		{
			if (value != getParentMenu())
			{
				CForm *form{ m_pForm };
				if (form)
					form->LockRepaint();
				if (getParentMenu())
					getParentMenu()->DetachControl(this);
				if (value)
				{
					value->m_bAcceptControls = true;
					m_bAcceptParent = true;
					value->AddControl(this);
					value->m_bAcceptControls = false;
					m_bAcceptParent = false;
					value->Update();
				}
				if (form)
					form->UnlockRepaint();
			}
			return this;
		}

		CMenuItem *CMenuItem::setMenu(CMenu *value)
		{
			if (value != getMenu())
			{
				if (m_pForm)
					m_pForm->LockRepaint();
				DeleteControls();
				if (value)
				{
					value->m_bVisible = false;
					value->m_bAcceptParent = true;
					m_bAcceptControls = true;
					AddControl(value);
					value->m_bAcceptParent = false;
					m_bAcceptControls = false;
				}
				if (getParentMenu())
					getParentMenu()->Update();
				if (m_pForm)
					m_pForm->UnlockRepaint();
			}
			return this;
		}

		CMenuItem *CMenuItem::setType(const TYPE value)
		{
			if (value != m_eType)
			{
				m_eType = value;
				UpdateState();
				if (getParentMenu())
				{
					if (getIsActive() && (m_eType == mitSeparator || !m_bEnabled))
						getParentMenu()->ClearActiveMenuItem();
					getParentMenu()->Update();
				}
			}
			return this;
		}

		CMenuItem *CMenuItem::setState(const STATE value)
		{
			if (value != m_eState)
			{
				switch (m_eType)
				{
				case mitCheckBox:
					m_eState = value;
					Repaint(false);
					break;
				case mitRadioButton:
					if (value != misGrayed)
					{
						m_eState = value;
						if (m_pForm)
							m_pForm->LockRepaint();
						if (m_eState == misChecked && getParentMenu())
							for (size_t index = 0; index < getParentMenu()->getMenuItemCount(); index++)
							{
								CMenuItem *item{ getParentMenu()->getMenuItem(index) };
								if (item != this && item->m_eType == mitRadioButton && item->m_iGroupIndex == m_iGroupIndex && item->m_eState != misNormal)
								{
									item->m_eState = misNormal;
									item->Repaint(false);
								}
							}
						Repaint(false);
						if (m_pForm)
							m_pForm->UnlockRepaint();
					}
					break;
				}
			}
			return this;
		}

		CMenuItem *CMenuItem::setMarginImage(const math::RECTANGLE<size_t> &value)
		{
			if (value != m_sMarginImage)
			{
				m_sMarginImage = value;
				if (getParentMenu())
					getParentMenu()->Update();
			}
			return this;
		}

		CMenuItem *CMenuItem::setMarginImageLeft(const size_t value)
		{
			return setMarginImage({ value, m_sMarginImage.Top, m_sMarginImage.Right, m_sMarginImage.Bottom });
		}

		CMenuItem *CMenuItem::setMarginImageTop(const size_t value)
		{
			return setMarginImage({ m_sMarginImage.Left, value, m_sMarginImage.Right, m_sMarginImage.Bottom });
		}

		CMenuItem *CMenuItem::setMarginImageRight(const size_t value)
		{
			return setMarginImage({ m_sMarginImage.Left, m_sMarginImage.Top, value, m_sMarginImage.Bottom });
		}

		CMenuItem *CMenuItem::setMarginImageBottom(const size_t value)
		{
			return setMarginImage({ m_sMarginImage.Left, m_sMarginImage.Top, m_sMarginImage.Right, value });
		}

		CMenuItem *CMenuItem::setMarginCaptionImage(const math::RECTANGLE<size_t> &value)
		{
			if (value != m_sMarginCaptionImage)
			{
				m_sMarginCaptionImage = value;
				if (getParentMenu())
					getParentMenu()->Update();
			}
			return this;
		}

		CMenuItem *CMenuItem::setMarginCaptionImageLeft(const size_t value)
		{
			return setMarginImage({ value, m_sMarginCaptionImage.Top, m_sMarginCaptionImage.Right, m_sMarginCaptionImage.Bottom });
		}

		CMenuItem *CMenuItem::setMarginCaptionImageTop(const size_t value)
		{
			return setMarginImage({ m_sMarginCaptionImage.Left, value, m_sMarginCaptionImage.Right, m_sMarginCaptionImage.Bottom });
		}

		CMenuItem *CMenuItem::setMarginCaptionImageRight(const size_t value)
		{
			return setMarginImage({ m_sMarginCaptionImage.Left, m_sMarginCaptionImage.Top, value, m_sMarginCaptionImage.Bottom });
		}

		CMenuItem *CMenuItem::setMarginCaptionImageBottom(const size_t value)
		{
			return setMarginImage({ m_sMarginCaptionImage.Left, m_sMarginCaptionImage.Top, m_sMarginCaptionImage.Right, value });
		}

		CMenuItem *CMenuItem::setMarginCaption(const math::RECTANGLE<size_t> &value)
		{
			if (value != m_sMarginCaption)
			{
				m_sMarginCaption = value;
				if (getParentMenu())
					getParentMenu()->Update();
			}
			return this;
		}

		CMenuItem *CMenuItem::setMarginCaptionLeft(const size_t value)
		{
			return setMarginImage({ value, m_sMarginCaption.Top, m_sMarginCaption.Right, m_sMarginCaption.Bottom });
		}

		CMenuItem *CMenuItem::setMarginCaptionTop(const size_t value)
		{
			return setMarginImage({ m_sMarginCaption.Left, value, m_sMarginCaption.Right, m_sMarginCaption.Bottom });
		}

		CMenuItem *CMenuItem::setMarginCaptionRight(const size_t value)
		{
			return setMarginImage({ m_sMarginCaption.Left, m_sMarginCaption.Top, value, m_sMarginCaption.Bottom });
		}

		CMenuItem *CMenuItem::setMarginCaptionBottom(const size_t value)
		{
			return setMarginImage({ m_sMarginCaption.Left, m_sMarginCaption.Top, m_sMarginCaption.Right, value });
		}

		CMenuItem *CMenuItem::setMarginShortcut(const math::RECTANGLE<size_t> &value)
		{
			if (value != m_sMarginShortcut)
			{
				m_sMarginShortcut = value;
				if (getParentMenu())
					getParentMenu()->Update();
			}
			return this;
		}

		CMenuItem *CMenuItem::setMarginShortcutLeft(const size_t value)
		{
			return setMarginImage({ value, m_sMarginShortcut.Top, m_sMarginShortcut.Right, m_sMarginShortcut.Bottom });
		}

		CMenuItem *CMenuItem::setMarginShortcutTop(const size_t value)
		{
			return setMarginImage({ m_sMarginShortcut.Left, value, m_sMarginShortcut.Right, m_sMarginShortcut.Bottom });
		}

		CMenuItem *CMenuItem::setMarginShortcutRight(const size_t value)
		{
			return setMarginImage({ m_sMarginShortcut.Left, m_sMarginShortcut.Top, value, m_sMarginShortcut.Bottom });
		}

		CMenuItem *CMenuItem::setMarginShortcutBottom(const size_t value)
		{
			return setMarginImage({ m_sMarginShortcut.Left, m_sMarginShortcut.Top, m_sMarginShortcut.Right, value });
		}

		CMenuItem *CMenuItem::setMarginArrow(const math::RECTANGLE<size_t> &value)
		{
			if (value != m_sMarginArrow)
			{
				m_sMarginArrow = value;
				if (getParentMenu())
					getParentMenu()->Update();
			}
			return this;
		}

		CMenuItem *CMenuItem::setMarginArrowLeft(const size_t value)
		{
			return setMarginImage({ value, m_sMarginArrow.Top, m_sMarginArrow.Right, m_sMarginArrow.Bottom });
		}

		CMenuItem *CMenuItem::setMarginArrowTop(const size_t value)
		{
			return setMarginImage({ m_sMarginArrow.Left, value, m_sMarginArrow.Right, m_sMarginArrow.Bottom });
		}

		CMenuItem *CMenuItem::setMarginArrowRight(const size_t value)
		{
			return setMarginImage({ m_sMarginArrow.Left, m_sMarginArrow.Top, value, m_sMarginArrow.Bottom });
		}

		CMenuItem *CMenuItem::setMarginArrowBottom(const size_t value)
		{
			return setMarginImage({ m_sMarginArrow.Left, m_sMarginArrow.Top, m_sMarginArrow.Right, value });
		}

		CMenuItem *CMenuItem::setImageIndex(int value)
		{
			if (value < -1)
				value = -1;
			if (value != m_iImageIndex)
			{
				m_iImageIndex = value;
				Repaint(false);
			}
			return this;
		}

		CMenuItem *CMenuItem::setGroupIndex(const size_t value)
		{
			if (value != m_iGroupIndex)
			{
				m_iGroupIndex = value;
				if (UpdateState())
					Repaint(false);
			}
			return this;
		}

		CMenuItem *CMenuItem::setCaption(const String &value)
		{
			if (value != m_sCaption)
			{
				m_sCaption = value;
				if (getParentMenu())
					getParentMenu()->Update();
			}
			return this;
		}

		CMenuItem *CMenuItem::setShortcut(const IWindow::KEY key, const bool control, const bool alt, const bool shift)
		{
			if (key == IWindow::keyUnknown)
			{
				if (m_pForm)
					m_pForm->UnregisterHotkeys(this);
				if (m_sShortcut.Key != key)
				{
					m_sShortcut.Key = key;
					m_sShortcutName = L"";
					if (getParentMenu())
						getParentMenu()->Update();
				}
			}
			else
			{
				String key_name = GetKeyName(key);
				if (!key_name.empty() && (key != m_sShortcut.Key || control != m_sShortcut.Control || alt != m_sShortcut.Alt || shift != m_sShortcut.Shift))
				{
					m_sShortcut.Key = key;
					m_sShortcut.Control = control;
					m_sShortcut.Alt = alt;
					m_sShortcut.Shift = shift;
					m_sShortcutName = key_name;
					if (shift)
						m_sShortcutName = CForm::SHORTCUT::GetKeyName(IWindow::keyShift) + L"+" + m_sShortcutName;
					if (alt)
						m_sShortcutName = CForm::SHORTCUT::GetKeyName(IWindow::keyMenu) + L"+" + m_sShortcutName;
					if (control)
						m_sShortcutName = CForm::SHORTCUT::GetKeyName(IWindow::keyControl) + L"+" + m_sShortcutName;
					if (getParentMenu())
						getParentMenu()->Update();
					if (m_pForm)
					{
						m_pForm->UnregisterHotkeys(this);
						m_pForm->RegisterHotkey(this, key, control, alt, shift, false);
					}
				}
			}
			return this;
		}

		CMenuItem *CMenuItem::setSeparatorHeight(size_t value)
		{
			if (value < 1)
				value = 1;
			if (value != m_iSeparatorHeight)
			{
				m_iSeparatorHeight = value;
				if (m_eType == mitSeparator &&getParentMenu())
					getParentMenu()->Update();
			}
			return this;
		}

		CMenuItem *CMenuItem::setSeparatorColor(const APP_COLOR &value)
		{
			if (value != m_sSeparatorColor)
			{
				m_sSeparatorColor = value;
				if (m_eType == mitSeparator)
					Repaint(false);
			}
			return this;
		}

		CMenuItem *CMenuItem::setDisabledTextColor(const APP_COLOR &value)
		{
			if (value != m_sDisabledTextColor)
			{
				m_sDisabledTextColor = value;
				if (m_eType != mitSeparator && !m_bEnabled)
					Repaint(false);
			}
			return this;
		}

		CMenuItem *CMenuItem::setDisabledShadowColor(const APP_COLOR &value)
		{
			if (value != m_sDisabledShadowColor)
			{
				m_sDisabledShadowColor = value;
				if (m_eType != mitSeparator && !m_bEnabled)
					Repaint(false);
			}
			return this;
		}

		CMenuItem *CMenuItem::setActiveBackgroundColor(const APP_COLOR &value)
		{
			if (value != m_sActiveBackgroundColor)
			{
				m_sActiveBackgroundColor = value;
				if (getIsActive())
					Repaint(false);
			}
			return this;
		}

		CMenuItem *CMenuItem::setActiveTextColor(const APP_COLOR &value)
		{
			if (value != m_sActiveTextColor)
			{
				m_sActiveTextColor = value;
				if (getIsActive())
					Repaint(false);
			}
			return this;
		}

		CMenuItem *CMenuItem::setActiveShadowColor(const APP_COLOR &value)
		{
			if (value != m_sActiveShadowColor)
			{
				m_sActiveShadowColor = value;
				if (getIsActive())
					Repaint(false);
			}
			return this;
		}

		CMenuItem *CMenuItem::setOnClick(FOnClick value)
		{
			m_fOnClick = value;
			return this;
		}

		CMenuItem *CMenuItem::setMenuShift(const APP_POINT &value)
		{
			if (value != m_sMenuShift)
			{
				m_sMenuShift = value;
				if (getMenu() && getMenu()->m_bVisible)
					getMenu()->Show(getWidth() + m_sMenuShift.X, m_sMenuShift.Y);
			}
			return this;
		}

		CMenuItem *CMenuItem::setMenuShiftX(const int value)
		{
			if (value != m_sMenuShift.X)
			{
				m_sMenuShift.X = value;
				if (getMenu() && getMenu()->m_bVisible)
					getMenu()->Show(getWidth() + m_sMenuShift.X, m_sMenuShift.Y);
			}
			return this;
		}

		CMenuItem *CMenuItem::setMenuShiftY(const int value)
		{
			if (value != m_sMenuShift.Y)
			{
				m_sMenuShift.Y = value;
				if (getMenu() && getMenu()->m_bVisible)
					getMenu()->Show(getWidth() + m_sMenuShift.X, m_sMenuShift.Y);
			}
			return this;
		}
	#pragma endregion

	#pragma region Notifications
		void CMenuItem::NotifyOnAttachToForm()
		{
			if (m_sShortcut.Key != IWindow::keyUnknown)
				m_pForm->RegisterHotkey(this, m_sShortcut.Key, m_sShortcut.Control, m_sShortcut.Alt, m_sShortcut.Shift, false);
		}

		bool CMenuItem::NotifyOnLeftMouseButtonDown(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			if (m_bEnabled)
			{
				switch (m_eType)
				{
				case mitCheckBox:
					if (m_eState == misNormal)
						m_eState = misChecked;
					else
						m_eState = misNormal;
					Repaint(false);
					break;
				case mitRadioButton:
					if (m_eState != misChecked)
					{
						m_eState = misChecked;
						m_pForm->LockRepaint();
						for (size_t index = 0; index < getParentMenu()->getMenuItemCount(); index++)
						{
							CMenuItem *item{ getParentMenu()->getMenuItem(index) };
							if (item != this && item->m_eType == mitRadioButton && item->m_iGroupIndex == m_iGroupIndex && item->m_eState != misNormal)
							{
								item->m_eState = misNormal;
								item->Repaint(false);
							}
						}
						Repaint(false);
						m_pForm->UnlockRepaint();
					}
				}
			}
			return CControl::NotifyOnLeftMouseButtonDown(x, y, ctrl, left, middle, right, shift);
		}

		bool CMenuItem::NotifyOnLeftMouseButtonUp(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			if (m_bEnabled && m_eType != mitSeparator && !getMenu())
			{
				getMainMenu()->Deactivate();
				NotifyOnClick();
			}
			return CControl::NotifyOnLeftMouseButtonUp(x, y, ctrl, left, middle, right, shift);
		}

		void CMenuItem::NotifyOnChangeUseParentFont()
		{
			CControl::NotifyOnChangeUseParentFont();
			if (getParentMenu())
				getParentMenu()->Update();
		}

		void CMenuItem::NotifyOnParentFontChangeSize()
		{
			CControl::NotifyOnParentFontChangeSize();
			getParentMenu()->Update();
		}

		void CMenuItem::NotifyOnFontChangeSize()
		{
			CControl::NotifyOnFontChangeSize();
			if (getParentMenu())
				getParentMenu()->Update();
		}

		void CMenuItem::NotifyOnMouseHover()
		{
			if (m_bEnabled && m_eType != mitSeparator && (!getIsActive() || (getMenu() && !getMenu()->m_bVisible)))
			{
				getParentMenu()->setActiveMenuItem(this);
				if (getMenu() && !getMenu()->m_bVisible)
					getMenu()->Show(getWidth() + m_sMenuShift.X, m_sMenuShift.Y);
			}
			CControl::NotifyOnMouseHover();
		}

		void CMenuItem::NotifyOnChangeParentStyle()
		{
			CControl::NotifyOnChangeParentStyle();
			if (getParentMenu())
				getParentMenu()->Update();
		}

		void CMenuItem::NotifyOnChangeStyle()
		{
			CControl::NotifyOnChangeStyle();
			if (getParentMenu())
				getParentMenu()->Update();
		}

		void CMenuItem::NotifyOnDisable()
		{
			CControl::NotifyOnDisable();
			if (getMenu() && getMenu()->m_bVisible)
				getMenu()->Hide();
		}

		void CMenuItem::NotifyOnDetachControl(CControl *control)
		{
			if (getParentMenu())
				getParentMenu()->Update();
			CControl::NotifyOnDetachControl(control);
		}

		void CMenuItem::NotifyOnPaint(APP_RECT clip)
		{
			Paint(clip);
			CControl::NotifyOnPaint(clip);
		}

		void CMenuItem::NotifyOnHotkey(const IWindow::KEY key, const bool ctrl, const bool alt, const bool shift, const bool is_down)
		{
			if (m_bEnabled && m_eType != mitSeparator && !getMenu())
			{
				getMainMenu()->Deactivate();
				if (m_eType == mitCheckBox || m_eType == mitRadioButton)
					if (m_eState == misNormal)
						setState(misChecked);
					else if (m_eType != mitRadioButton)
						setState(misNormal);
				NotifyOnClick();
			}
			CControl::NotifyOnHotkey(key, ctrl, alt, shift, is_down);
		}

		void CMenuItem::NotifyOnClick()
		{
			getMainMenu()->NotifyOnClick(this);
			getParentMenu()->NotifyOnClick(this);
			if (m_fOnClick)
				m_fOnClick(this, getCallbackParam());
		}
	#pragma endregion

	#pragma region Helpers
		bool CMenuItem::UpdateState()
		{
			// Clear checked/grayed state if there is another one in same group. Return if changed
			if (m_eType == mitRadioButton && m_eState != misNormal && getParentMenu())
				for (size_t index = 0; index < getParentMenu()->getMenuItemCount(); index++)
				{
					CMenuItem *item{ getParentMenu()->getMenuItem(index) };
					if (item != this && item->m_eType == mitRadioButton && item->m_eState != misNormal && item->m_iGroupIndex == m_iGroupIndex)
					{
						m_eState = misNormal;
						return true;
					}
				}
			return false;
		}

		bool CMenuItem::SearchImage(APP_IMAGE **image, APP_RECT &rect)
		{
			if (m_eType != mitSeparator && m_iImageIndex > 0)
			{
				CImageList *image_list{ getImageList() };
				if (image_list)
				{
					*image = image_list->getImage(m_iImageIndex);
					if (*image)
					{
						rect = { 0, 0, (int)(*image)->getWidth(), (int)(*image)->getHeight() };
						return rect.Width() > 0 && rect.Height() > 0;
					}
				}
			}
			return false;
		}

		bool CMenuItem::SearchCaptionImage(APP_IMAGE **image, APP_RECT &rect, const bool ignore_state)
		{
			String name{ m_sClassName };
			switch (m_eType)
			{
			case mitCheckBox:
				name += L".CheckBox";
				if (ignore_state)
					name += L".normal.unchecked";
				else
				{
					if (!m_bEnabled)
						name += L".disabled";
					else if (getIsActive())
						name += L".active";
					else
						name += L".normal";
					switch (m_eState)
					{
					case misChecked:
						name += L".checked";
						break;
					case misGrayed:
						name += L".grayed";
						break;
					default:
						name += L".unchecked";
						break;
					}
				}
				break;
			case mitRadioButton:
				name += L".RadioButton";
				if (ignore_state)
					name += L".normal.unchecked";
				else
				{
					if (!m_bEnabled)
						name += L".disabled";
					else if (getIsActive())
						name += L".active";
					else
						name += L".normal";
					switch (m_eState)
					{
					case misChecked:
						name += L".checked";
						break;
					default:
						name += L".unchecked";
						break;
					}
				}
				break;
			default:
				return false;
			}
			CStyle *style{ getStyle() }, *def{ GetDefaultStyle() };
			if (!style)
				style = def;
			if (!style)
				return false;
			CStyleSkin *skin{ style->getSkinByName(name) };
			if (!skin)
				skin = def->getSkinByName(name);
			if (!skin || !skin->getImage())
				return false;
			*image = skin->getImage()->getImage();
			if (*image)
			{
				rect = skin->getRect();
				return rect.Width() > 0 && rect.Height() > 0;
			}
			return false;
		}

		bool CMenuItem::SearchArrowImage(APP_IMAGE **image, APP_RECT &rect, const bool ignore_state)
		{
			if (m_eType == mitSeparator || !getMenu())
				return false;
			String name{ m_sClassName + L".Arrow" };
			if (ignore_state)
				name += L".normal";
			else
			{
				if (!m_bEnabled)
					name += L".disabled";
				else if (getIsActive())
					name += L".active";
				else
					name += L".normal";
			}
			CStyle *style{ getStyle() }, *def{ GetDefaultStyle() };
			if (!style)
				style = def;
			if (!style)
				return false;
			CStyleSkin *skin{ style->getSkinByName(name) };
			if (!skin)
				skin = def->getSkinByName(name);
			if (!skin || !skin->getImage())
				return false;
			*image = skin->getImage()->getImage();
			if (*image)
			{
				rect = skin->getRect();
				return rect.Width() > 0 && rect.Height() > 0;
			}
			return false;
		}

		CMenuItem::SIZE CMenuItem::CalculateSize()
		{
			SIZE result{ 0, 0, 0, 0, 0, 0 };
			if (m_eType == mitSeparator)
			{
				result.Height = m_iSeparatorHeight;
				result.WidthCaption = 1;
				return result;
			}
			APP_POINT size_caption = getFont()->getStringSize(m_sCaption), size_shortcut = getFont()->getStringSize(m_sShortcutName), size_w = getFont()->getStringSize(L"W");
			APP_IMAGE *image, *caption_image, *arrow_image;
			APP_RECT image_rect, caption_rect, arrow_rect;
			bool have_image{ SearchImage(&image, image_rect) }, have_caption_image{ SearchCaptionImage(&caption_image, caption_rect, true) }, have_arrow_image{ SearchArrowImage(&arrow_image, arrow_rect, true) };
			result.Height = std::max(result.Height, size_w.Y + m_sMarginCaption.Top + m_sMarginCaption.Bottom);
			if (have_image)
			{
				result.Height = std::max(result.Height, image_rect.Height() + m_sMarginImage.Top + m_sMarginImage.Bottom);
				result.WidthImage = image_rect.Width() + m_sMarginImage.Left + m_sMarginImage.Right;
			}
			if (have_caption_image)
			{
				result.Height = std::max(result.Height, caption_rect.Height() + m_sMarginCaptionImage.Top + m_sMarginCaptionImage.Bottom);
				result.WidthCaptionImage += caption_rect.Width() + m_sMarginCaptionImage.Left + m_sMarginCaptionImage.Right;
			}
			if (!m_sCaption.empty())
			{
				result.Height = std::max(result.Height, size_caption.Y + m_sMarginCaption.Top + m_sMarginCaption.Bottom);
				result.WidthCaption += std::max(size_w.X, size_caption.X) + m_sMarginCaption.Left + m_sMarginCaption.Right;
			}
			if (!m_sShortcutName.empty())
			{
				result.Height = std::max(result.Height, size_shortcut.Y + m_sMarginShortcut.Top + m_sMarginShortcut.Bottom);
				result.WidthShortcut = size_shortcut.X + m_sMarginShortcut.Left + m_sMarginShortcut.Right;
			}
			if (have_arrow_image)
			{
				result.Height = std::max(result.Height, arrow_rect.Height() + m_sMarginArrow.Top + m_sMarginArrow.Bottom);
				result.WidthArrow = arrow_rect.Width() + m_sMarginArrow.Left + m_sMarginArrow.Right;
			}
			return result;
		}

		APP_RECT CMenuItem::CalculateRectSeparator()
		{
			APP_RECT result = getRect();
			result.Left += getParentMenu()->m_sSize.WidthImage;
			if (!result.IsValid())
				result.Left = result.Right;
			return result;
		}

		APP_RECT CMenuItem::CalculateRectImage()
		{
			APP_RECT result = getRect();
			result.Right = result.Left + getParentMenu()->m_sSize.WidthImage;
			if (!result.IsValid())
				result.Right = result.Left;
			return result;
		}

		APP_RECT CMenuItem::CalculateRectCaptionImage()
		{
			APP_RECT result = getRect(), rect;
			APP_IMAGE *image;
			if (SearchCaptionImage(&image, rect, true))
			{
				result.Left += getParentMenu()->m_sSize.WidthImage;
				result.Right = result.Left + rect.Width() + m_sMarginCaptionImage.Left + m_sMarginCaptionImage.Right;
				if (result.Width() > (int)getParentMenu()->m_sSize.WidthCaption)
					result.Right = result.Left + getParentMenu()->m_sSize.WidthCaption;
				if (result.Right > getRect().Right)
					result.Right = getRect().Right;
				if (!result.IsValid())
					result.Right = result.Left;
			}
			else
			{
				result.Right = result.Left;
				result.Bottom = result.Top;
			}
			return result;
		}

		APP_RECT CMenuItem::CalculateRectCaption()
		{
			APP_RECT result = getRect();
			result.Left += getParentMenu()->m_sSize.WidthImage;
			result.Right = result.Left + getParentMenu()->m_sSize.WidthCaption;
			APP_RECT rect;
			APP_IMAGE *image;
			if (SearchCaptionImage(&image, rect, true))
				result.Left += rect.Width() + m_sMarginCaptionImage.Left + m_sMarginCaptionImage.Right;
			if (result.Right > getRect().Right)
				result.Right = getRect().Right;
			if (!result.IsValid())
				result.Right = result.Left;
			return result;
		}

		APP_RECT CMenuItem::CalculateRectShortcut()
		{
			APP_RECT result = getRect();
			result.Left += getParentMenu()->m_sSize.WidthImage + getParentMenu()->m_sSize.WidthCaption;
			result.Right = result.Left + getParentMenu()->m_sSize.WidthShortcut;
			if (result.Right > getRect().Right)
				result.Right = getRect().Right;
			if (!result.IsValid())
				result.Right = result.Left;
			return result;
		}

		APP_RECT CMenuItem::CalculateRectArrow()
		{
			APP_RECT result = getRect();
			result.Left += getParentMenu()->m_sSize.WidthImage + getParentMenu()->m_sSize.WidthCaption + getParentMenu()->m_sSize.WidthShortcut;
			result.Right = result.Left + getParentMenu()->m_sSize.WidthArrow;
			if (result.Right > getRect().Right)
				result.Right = getRect().Right;
			if (!result.IsValid())
				result.Right = result.Left;
			return result;
		}

		bool CMenuItem::UpdateFromStyle()
		{
			if (!getStyle())
				return false;
			m_sMarginImage = getStyle()->getParameterByName(m_sClassName + L".MarginImage", m_sMarginImage);
			m_sMarginCaptionImage = getStyle()->getParameterByName(m_sClassName + L".MarginCaptionImage", m_sMarginCaptionImage);
			m_sMarginCaption = getStyle()->getParameterByName(m_sClassName + L".MarginCaption", m_sMarginCaption);
			m_sMarginShortcut = getStyle()->getParameterByName(m_sClassName + L".MarginShortcut", m_sMarginShortcut);
			m_sMarginArrow = getStyle()->getParameterByName(m_sClassName + L".MarginArrow", m_sMarginArrow);
			m_iSeparatorHeight = getStyle()->getParameterByName(m_sClassName + L".SeparatorHeight", m_iSeparatorHeight);
			m_sSeparatorColor = getStyle()->getParameterByName(m_sClassName + L".SeparatorColor", m_sSeparatorColor);
			m_sDisabledTextColor = getStyle()->getParameterByName(m_sClassName + L".DisabledTextColor", m_sDisabledTextColor);
			m_sDisabledShadowColor = getStyle()->getParameterByName(m_sClassName + L".DisabledShadowColor", m_sDisabledShadowColor);
			m_sActiveBackgroundColor = getStyle()->getParameterByName(m_sClassName + L".ActiveBackgroundColor", m_sActiveBackgroundColor);
			m_sActiveTextColor = getStyle()->getParameterByName(m_sClassName + L".ActiveTextColor", m_sActiveTextColor);
			m_sActiveShadowColor = getStyle()->getParameterByName(m_sClassName + L".ActiveShadowColor", m_sActiveShadowColor);
			m_sMenuShift = getStyle()->getParameterByName(m_sClassName + L".MenuShift", m_sMenuShift);
			return true;
		}

		String CMenuItem::GetKeyName(const IWindow::KEY key)
		{
			switch (key)
			{
			case IWindow::keyBack:
			case IWindow::keyTab:
			case IWindow::keyPause:
			case IWindow::keyCapital:
			case IWindow::keyEscape:
			case IWindow::keySpace:
			case IWindow::keyPrior:
			case IWindow::keyNext:
			case IWindow::keyEnd:
			case IWindow::keyHome:
			case IWindow::keyLeft:
			case IWindow::keyUp:
			case IWindow::keyRight:
			case IWindow::keyDown:
			case IWindow::keySnapshot:
			case IWindow::keyInsert:
			case IWindow::keyDelete:
			case IWindow::key0:
			case IWindow::key1:
			case IWindow::key2:
			case IWindow::key3:
			case IWindow::key4:
			case IWindow::key5:
			case IWindow::key6:
			case IWindow::key7:
			case IWindow::key8:
			case IWindow::key9:
			case IWindow::keyA:
			case IWindow::keyB:
			case IWindow::keyC:
			case IWindow::keyD:
			case IWindow::keyE:
			case IWindow::keyF:
			case IWindow::keyG:
			case IWindow::keyH:
			case IWindow::keyI:
			case IWindow::keyJ:
			case IWindow::keyK:
			case IWindow::keyL:
			case IWindow::keyM:
			case IWindow::keyN:
			case IWindow::keyO:
			case IWindow::keyP:
			case IWindow::keyQ:
			case IWindow::keyR:
			case IWindow::keyS:
			case IWindow::keyT:
			case IWindow::keyU:
			case IWindow::keyV:
			case IWindow::keyW:
			case IWindow::keyX:
			case IWindow::keyY:
			case IWindow::keyZ:
			case IWindow::keyNumpad0:
			case IWindow::keyNumpad1:
			case IWindow::keyNumpad2:
			case IWindow::keyNumpad3:
			case IWindow::keyNumpad4:
			case IWindow::keyNumpad5:
			case IWindow::keyNumpad6:
			case IWindow::keyNumpad7:
			case IWindow::keyNumpad8:
			case IWindow::keyNumpad9:
			case IWindow::keyMultiply:
			case IWindow::keyAdd:
			case IWindow::keySeparator:
			case IWindow::keySubtract:
			case IWindow::keyDecimal:
			case IWindow::keyDivide:
			case IWindow::keyF1:
			case IWindow::keyF2:
			case IWindow::keyF3:
			case IWindow::keyF4:
			case IWindow::keyF5:
			case IWindow::keyF6:
			case IWindow::keyF7:
			case IWindow::keyF8:
			case IWindow::keyF9:
			case IWindow::keyF10:
			case IWindow::keyF11:
			case IWindow::keyF12:
			case IWindow::keyF13:
			case IWindow::keyF14:
			case IWindow::keyF15:
			case IWindow::keyF16:
			case IWindow::keyF17:
			case IWindow::keyF18:
			case IWindow::keyF19:
			case IWindow::keyF20:
			case IWindow::keyF21:
			case IWindow::keyF22:
			case IWindow::keyF23:
			case IWindow::keyF24:
			case IWindow::keyNumLock:
			case IWindow::keyScroll:
			case IWindow::keyBrowserBack:
			case IWindow::keyBrowserForward:
			case IWindow::keyBrowserRefresh:
			case IWindow::keyBrowserStop:
			case IWindow::keyBrowserSearch:
			case IWindow::keyBrowserFavorites:
			case IWindow::keyBrowserHome:
			case IWindow::keyVolumeMute:
			case IWindow::keyVolumeDown:
			case IWindow::keyVolumeUp:
			case IWindow::keyMediaNextTrack:
			case IWindow::keyMediaPrevTrack:
			case IWindow::keyMediaStop:
			case IWindow::keyMediaPlayPause:
			case IWindow::keyLaunchMail:
			case IWindow::keyLaunchMediaSelect:
			case IWindow::keyLaunchApp1:
			case IWindow::keyLaunchApp2:
			case IWindow::keyOem1:
			case IWindow::keyOemPlus:
			case IWindow::keyOemComma:
			case IWindow::keyOemMinus:
			case IWindow::keyOemPeriod:
			case IWindow::keyOem2:
			case IWindow::keyOem3:
			case IWindow::keyOem4:
			case IWindow::keyOem5:
			case IWindow::keyOem6:
			case IWindow::keyOem7:
			case IWindow::keyPlay:
			case IWindow::keyZoom:
				return CForm::SHORTCUT::GetKeyName(key);
			default:
				return L"";
			}
		}
	#pragma endregion

	#pragma region Draw
		void CMenuItem::Paint(APP_RECT clip)
		{
			clip *= getVisibleRect();
			if (clip.IsEmpty())
				return;
			m_eType == mitSeparator ? PaintSeparator(clip) : PaintControl(clip);
		}

		void CMenuItem::PaintSeparator(APP_RECT clip)
		{
			APP_RECT rect = ClientToForm(CalculateRectSeparator());
			if (rect.IsEmpty())
				return;
			CStyle *style{ getStyle() }, *def{ GetDefaultStyle() };
			if (!style)
				style = def;
			CStyleSkin *skin{ style->getSkinByName(m_sClassName + L".Separator") };
			if (!skin)
				skin = def->getSkinByName(m_sClassName + L".Separator");
			IImage *image{ nullptr };
			APP_RECT image_rect;
			if (skin)
			{
				APP_IMAGE *app_image{ skin->getImage()->getImage() };
				if (app_image)
				{
					image_rect = skin->getRect();
					if (image_rect.Width() > 0 && image_rect.Height() > 0)
						image = m_pForm->getImageManager()->getImage(app_image);
				}
			}
			if (image)
				m_pForm->getPresenter()->RenderImage(image, image_rect, rect.Left, rect.Top, 0, 1, 1, true, true, false, clip, rect, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, 0, graphics::bplInside, nullptr, nullptr, true);
			else
				m_pForm->getPresenter()->FillRect(m_sSeparatorColor, clip, rect, rect, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, 0, graphics::bplInside, nullptr, nullptr, true);
		}

		void CMenuItem::PaintControl(APP_RECT clip)
		{
			APP_RECT rect_image;
			APP_IMAGE *image;
			// Active background
			if (m_bEnabled && getIsActive() && m_sActiveBackgroundColor.getAlpha() > 0)
			{
				APP_RECT rect = ClientToForm(getRect());
				m_pForm->getPresenter()->FillRect(m_sActiveBackgroundColor, clip, rect, rect, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, 0, graphics::bplInside, nullptr, nullptr, true);
			}
			// Image
			if (SearchImage(&image, rect_image))
			{
				APP_RECT rect = ClientToForm(CalculateRectImage()),
					new_clip{ rect.Left + (int)m_sMarginImage.Left, rect.Top + (int)m_sMarginImage.Top, rect.Right - (int)m_sMarginImage.Right, rect.Bottom - (int)m_sMarginImage.Bottom };
				new_clip *= clip;
				if (!rect.IsEmpty() && new_clip.IsValid() && !new_clip.IsEmpty())
				{
					IImage *img{ m_pForm->getImageManager()->getImage(image) };
					if (img)
					{
						int x{ rect.Left + (int)m_sMarginImage.Left + (rect.Width() - (int)m_sMarginImage.Left - (int)m_sMarginImage.Right - (int)rect_image.Width()) / 2 };
						int y{ rect.Top + (int)m_sMarginImage.Top + (rect.Height() - (int)m_sMarginImage.Top - (int)m_sMarginImage.Bottom - (int)rect_image.Height()) / 2 };
						m_pForm->getPresenter()->RenderImage(img, rect_image, x, y, 0, 1, 1, false, false, false, new_clip, rect, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, 0, graphics::bplInside, nullptr, nullptr, true);
					}
				}
			}
			// Caption image
			if (SearchCaptionImage(&image, rect_image, false))
			{
				APP_RECT rect = ClientToForm(CalculateRectCaptionImage()),
					new_clip{ rect.Left + (int)m_sMarginCaptionImage.Left, rect.Top + (int)m_sMarginCaptionImage.Top, rect.Right - (int)m_sMarginCaptionImage.Right, rect.Bottom - (int)m_sMarginCaptionImage.Bottom };
				new_clip *= clip;
				if (!rect.IsEmpty() && new_clip.IsValid() && !new_clip.IsEmpty())
				{
					IImage *img{ m_pForm->getImageManager()->getImage(image) };
					if (img)
					{
						int x{ rect.Left + (int)m_sMarginCaptionImage.Left + (rect.Width() - (int)m_sMarginCaptionImage.Left - (int)m_sMarginCaptionImage.Right - (int)rect_image.Width()) / 2 };
						int y{ rect.Top + (int)m_sMarginCaptionImage.Top + (rect.Height() - (int)m_sMarginCaptionImage.Top - (int)m_sMarginCaptionImage.Bottom - (int)rect_image.Height()) / 2 };
						m_pForm->getPresenter()->RenderImage(img, rect_image, x, y, 0, 1, 1, false, false, false, new_clip, rect, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, 0, graphics::bplInside, nullptr, nullptr, true);
					}
				}
			}
			// Caption
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
					m_pForm->getPresenter()->RenderString(m_sCaption, getFont(), x, y, 0, 1, 1, new_clip, 0, rect, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, 0, graphics::bplInside, true, true, text_color, shadow_color, nullptr, nullptr, true);
				}
			}
			// Shortcut
			if (!m_sShortcutName.empty())
			{
				APP_RECT rect = ClientToForm(CalculateRectShortcut()),
					new_clip{ rect.Left + (int)m_sMarginShortcut.Left, rect.Top + (int)m_sMarginShortcut.Top, rect.Right - (int)m_sMarginShortcut.Right, rect.Bottom - (int)m_sMarginShortcut.Bottom };
				new_clip *= clip;
				if (!rect.IsEmpty() && new_clip.IsValid() && !new_clip.IsEmpty())
				{
					APP_POINT size = getFont()->getStringSize(m_sCaption);
					int x{ rect.Left + (int)m_sMarginShortcut.Left };
					int y{ rect.Top + (int)m_sMarginShortcut.Top + (rect.Height() - (int)m_sMarginShortcut.Top - (int)m_sMarginShortcut.Bottom - size.Y) / 2 };
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
					m_pForm->getPresenter()->RenderString(m_sShortcutName, getFont(), x, y, 0, 1, 1, new_clip, 0, rect, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, 0, graphics::bplInside, true, true, text_color, shadow_color, nullptr, nullptr, true);
				}
			}
			// Arrow
			if (SearchArrowImage(&image, rect_image, false))
			{
				APP_RECT rect = ClientToForm(CalculateRectArrow()),
					new_clip{ rect.Left + (int)m_sMarginArrow.Left, rect.Top + (int)m_sMarginArrow.Top, rect.Right - (int)m_sMarginArrow.Right, rect.Bottom - (int)m_sMarginArrow.Bottom };
				new_clip *= clip;
				if (!rect.IsEmpty() && new_clip.IsValid() && !new_clip.IsEmpty())
				{
					IImage *img{ m_pForm->getImageManager()->getImage(image) };
					if (img)
					{
						int x{ rect.Left + (int)m_sMarginArrow.Left + (rect.Width() - (int)m_sMarginArrow.Left - (int)m_sMarginArrow.Right - (int)rect_image.Width()) / 2 };
						int y{ rect.Top + (int)m_sMarginArrow.Top + (rect.Height() - (int)m_sMarginArrow.Top - (int)m_sMarginArrow.Bottom - (int)rect_image.Height()) / 2 };
						m_pForm->getPresenter()->RenderImage(img, rect_image, x, y, 0, 1, 1, false, false, false, new_clip, rect, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, 0, graphics::bplInside, nullptr, nullptr, true);
					}
				}
			}
		}
	#pragma endregion
	}
}