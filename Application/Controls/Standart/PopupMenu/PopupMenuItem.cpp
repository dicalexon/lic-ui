// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#include "PopupMenu.h"
#include "..\..\..\Presenter.h"
#include "..\..\..\Style.h"
#include "..\..\..\StyleSkin.h"
#include "..\..\..\StyleImage.h"
#include "..\..\..\DefaultStyle.h"
#include "..\..\..\ImageManager.h"

namespace licui
{
	namespace application
	{
#pragma region Constructors
		CPopupMenuItem::CPopupMenuItem() : CControl(),
			m_eType{ mitNormal },
			m_eState{ misNormal },
			m_sShortcut{ IWindow::keyUnknown, false, false, false },
			m_iGroup{ 0 },
			m_sMarginImage{ 2, 2, 2, 2 },
			m_sMarginCaptionImage{ 2, 2, 2, 2 },
			m_sMarginCaption{ 4, 4, 4, 4 },
			m_sMarginShortcut{ 4, 4, 4, 4 },
			m_sMarginArrow{ 4, 4, 4, 4 },
			m_bIsSeparator{ false },
			m_iSeparatorHeight{ 2 },
			m_sSeparatorColor{ 225, 225, 225, 255 },
			m_sDisabledTextColor{ 133, 135, 139, 255 },
			m_sDisabledShadowColor{ 133, 135, 139, 255 },
			m_sActiveBackgroundColor{ 0, 0, 255, 255 },
			m_sActiveTextColor{ 255, 255, 255, 255 },
			m_sActiveShadowColor{ 255, 255, 255, 255 }
		{
			m_sClassName = L"CPopupMenuItem";
			m_bSupportText = true;
			FillStates();
		}

		CPopupMenuItem::CPopupMenuItem(CPopupMenu *menu) :CPopupMenuItem()
		{
			if (menu)
				menu->AddMenuItem(this);
		}

		void CPopupMenuItem::FillStates()
		{
			m_sState[mitNormal][misNormal][0][0].ImageIndex = -1;
			m_sState[mitNormal][misNormal][0][1].ImageIndex = -1;
			m_sState[mitNormal][misNormal][1][0].ImageIndex = -1;
			m_sState[mitNormal][misNormal][1][1].ImageIndex = -1;
			m_sState[mitNormal][misChecked][0][0].ImageIndex = -1;
			m_sState[mitNormal][misChecked][0][1].ImageIndex = -1;
			m_sState[mitNormal][misChecked][1][0].ImageIndex = -1;
			m_sState[mitNormal][misChecked][1][1].ImageIndex = -1;
			m_sState[mitNormal][misGrayed][0][0].ImageIndex = -1;
			m_sState[mitNormal][misGrayed][0][1].ImageIndex = -1;
			m_sState[mitNormal][misGrayed][1][0].ImageIndex = -1;
			m_sState[mitNormal][misGrayed][1][1].ImageIndex = -1;

			m_sState[mitCheckBox][misNormal][0][0].ImageIndex = -1;
			m_sState[mitCheckBox][misNormal][0][1].ImageIndex = -1;
			m_sState[mitCheckBox][misNormal][1][0].ImageIndex = -1;
			m_sState[mitCheckBox][misNormal][1][1].ImageIndex = -1;
			m_sState[mitCheckBox][misChecked][0][0].ImageIndex = -1;
			m_sState[mitCheckBox][misChecked][0][1].ImageIndex = -1;
			m_sState[mitCheckBox][misChecked][1][0].ImageIndex = -1;
			m_sState[mitCheckBox][misChecked][1][1].ImageIndex = -1;
			m_sState[mitCheckBox][misGrayed][0][0].ImageIndex = -1;
			m_sState[mitCheckBox][misGrayed][0][1].ImageIndex = -1;
			m_sState[mitCheckBox][misGrayed][1][0].ImageIndex = -1;
			m_sState[mitCheckBox][misGrayed][1][1].ImageIndex = -1;

			m_sState[mitRadioButton][misNormal][0][0].ImageIndex = -1;
			m_sState[mitRadioButton][misNormal][0][1].ImageIndex = -1;
			m_sState[mitRadioButton][misNormal][1][0].ImageIndex = -1;
			m_sState[mitRadioButton][misNormal][1][1].ImageIndex = -1;
			m_sState[mitRadioButton][misChecked][0][0].ImageIndex = -1;
			m_sState[mitRadioButton][misChecked][0][1].ImageIndex = -1;
			m_sState[mitRadioButton][misChecked][1][0].ImageIndex = -1;
			m_sState[mitRadioButton][misChecked][1][1].ImageIndex = -1;
			m_sState[mitRadioButton][misGrayed][0][0].ImageIndex = -1;
			m_sState[mitRadioButton][misGrayed][0][1].ImageIndex = -1;
			m_sState[mitRadioButton][misGrayed][1][0].ImageIndex = -1;
			m_sState[mitRadioButton][misGrayed][1][1].ImageIndex = -1;
		}
#pragma endregion

#pragma region Helpers
		APP_POINT CPopupMenuItem::CalculateCaptionImageSize()
		{
			CStyle *style{ getStyle() }, *def{ GetDefaultStyle() };
			if (!style)
				style = def;
			String name;
			switch (m_eType)
			{
			case mitCheckBox:
				name = L".CheckBox.normal.unchecked";
				break;
			case mitRadioButton:
				name = L".RadioButton.normal.unchecked";
				break;
			default:
				return{ 0, 0 };
			}
			CStyleSkin *skin{ style->getSkinByName(m_sClassName + name) };
			if (!skin)
				skin = def->getSkinByName(m_sClassName + name);
			if (skin)
				return{
					(int)skin->getRect().Width() + (int)m_sMarginCaptionImage.Left + (int)m_sMarginCaptionImage.Right,
					(int)skin->getRect().Height() + (int)m_sMarginCaptionImage.Top + (int)m_sMarginCaptionImage.Bottom
				};
			return{ 0, 0 };
		}

		void CPopupMenuItem::SelectImage(APP_IMAGE **img, APP_RECT &rect)
		{
			*img = nullptr;
			CStyle *style{ getStyle() }, *def{ GetDefaultStyle() };
			if (!style)
				style = def;
			String name;
			switch (m_eType)
			{
			case mitCheckBox:
				name = L".CheckBox";
				break;
			case mitRadioButton:
				name = L".RadioButton";
				break;
			default:
				return;
			}
			name += getEnabled() ? (getIsActive() ? L".active" : L".normal") : L".disabled",
				name += m_eState == misChecked ? L".checked" : (m_eState == misGrayed ? L".grayed" : L".unchecked");
			CStyleSkin *skin{ style->getSkinByName(m_sClassName + name) };
			if (!skin)
				skin = def->getSkinByName(m_sClassName + name);
			if (skin)
			{
				*img = skin->getImage()->getImage();
				rect = skin->getRect();
			}
		}

		CPopupMenuItem::MENU_ITEM_SIZE CPopupMenuItem::CalculateSize()
		{
			if (!getParentMenu() || !getFont())
				return{ 0, 0, 0 };
			if (m_bIsSeparator)
			{
				if (m_iSeparatorHeight == 0)
					return{ 0, 0, 0 };
				return{ m_iSeparatorHeight, 1, 0 };
			}
			APP_POINT size_h = getFont()->getStringSize(L"W"), size_c = getFont()->getStringSize(m_sCaption), size_s{ 0, 0 }, size_i = CalculateCaptionImageSize();
			if (!m_sShortcutName.empty())
			{
				size_s = getFont()->getStringSize(m_sShortcutName);
				size_s.X += (int)m_sMarginShortcut.Left + (int)m_sMarginShortcut.Right;
				size_s.Y += (int)m_sMarginShortcut.Top + (int)m_sMarginShortcut.Bottom;
			}
			return{
				(size_t)std::max(size_h.Y + (int)std::max(m_sMarginCaption.Top + m_sMarginCaption.Bottom, m_sMarginShortcut.Top + m_sMarginShortcut.Bottom), (int)size_i.Y),
				(size_t)size_i.X + (size_t)size_c.X,
				(size_t)size_s.X
			};
		}

		String CPopupMenuItem::GetKeyName(const IWindow::KEY key)
		{
			switch (key)
			{
			case IWindow::keyLButton:
			case IWindow::keyRButton:
			case IWindow::keyMButton:
			case IWindow::keyBack:
			case IWindow::keyTab:
			case IWindow::keyReturn:
			case IWindow::keyShift:
			case IWindow::keyControl:
			case IWindow::keyMenu:
			case IWindow::keyPause:
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
			case IWindow::keyExecute:
			case IWindow::keySnapshot:
			case IWindow::keyInsert:
			case IWindow::keyDelete:
			case IWindow::keyHelp:
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
			case IWindow::keyLWin:
			case IWindow::keyRWin:
			case IWindow::keyApps:
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
			}
			return L"";
		}

		bool CPopupMenuItem::UpdateState()
		{
			ITEM_STATE new_state{ m_eState };
			switch (m_eType)
			{
			case mitNormal:
				new_state = misNormal;
				break;
			case mitRadioButton:
				if (new_state == misGrayed)
					new_state = misNormal;
			case mitCheckBox:
				if (!getVisible())
				{
					new_state = misNormal;
					break;
				}
				if (getParentMenu() && m_eState != misNormal)
				{
					for (size_t i = 0; i < getParentMenu()->getMenuItemCount(); i++)
					{
						CPopupMenuItem *item{ getParentMenu()->getMenuItem(i) };
						if (item != this && item->m_eType == m_eType && item->m_eState != misNormal)
						{
							new_state = misNormal;
							break;
						}
					}
				}
				break;
			}
			if (new_state != m_eState)
			{
				m_eState = new_state;
				return true;
			}
			return false;
		}

		void CPopupMenuItem::BeforeChange(const bool hide_menu)
		{
			if (m_pForm)
			{
				m_pForm->LockRepaint();
				if (getParentMenu() && getParentMenu()->getVisibleWithParents())
					Repaint(true);
				if (hide_menu && getMenu() && getMenu()->getVisible())
					getMenu()->Hide();
			}
		}

		void CPopupMenuItem::AfterChange()
		{
			if (getParentMenu() && getParentMenu()->getVisibleWithParents())
			{
				if ((!getEnabled() || m_bIsSeparator) && getParentMenu()->getActiveMenuItem() == this)
					getParentMenu()->ClearActiveMenuItemIndex();
				getParentMenu()->Update();
			}
			if (m_pForm)
				m_pForm->UnlockRepaint();
		}

		void CPopupMenuItem::ClearActiveMenuItemIndex()
		{
			if (getMenu())
				getMenu()->ClearActiveMenuItemIndex();
		}

		APP_RECT CPopupMenuItem::CalculateRectImage()
		{
			if (!getParentMenu())
				return{ 0, 0, 0, 0 };
			APP_RECT result = getRect();
			result.Right = result.Left + (int)getParentMenu()->m_sSize.WidthImages;
			result.Left += m_sMarginImage.Left;
			result.Top += m_sMarginImage.Top;
			result.Right -= (int)m_sMarginImage.Right;
			result.Bottom -= (int)m_sMarginImage.Bottom;
			if (!result.IsValid())
			{
				result.Right = result.Left;
				result.Bottom = result.Top;
			}
			return result;
		}

		APP_RECT CPopupMenuItem::CalculateRectCaptionImage()
		{
			if (!getParentMenu() || (m_eType != mitCheckBox && m_eType != mitRadioButton))
				return{ 0, 0, 0, 0 };
			APP_RECT result = getRect();
			result.Left += (int)getParentMenu()->m_sSize.WidthImages;
			APP_POINT p = CalculateCaptionImageSize();
			result.Right = result.Left + (int)p.X;
			result.Left += m_sMarginCaptionImage.Left;
			result.Top += m_sMarginCaptionImage.Top;
			result.Right -= (int)m_sMarginCaptionImage.Right;
			result.Bottom -= (int)m_sMarginCaptionImage.Bottom;
			if (!result.IsValid())
			{
				result.Right = result.Left;
				result.Bottom = result.Top;
			}
			return result;
		}

		APP_RECT CPopupMenuItem::CalculateRectCaption()
		{
			if (!getParentMenu())
				return{ 0, 0, 0, 0 };
			APP_RECT result = getRect();
			result.Left += (int)getParentMenu()->m_sSize.WidthImages;
			result.Right = result.Left + (int)getParentMenu()->m_sSize.WidthCaptions;
			if (m_eType == mitCheckBox || m_eType == mitRadioButton)
			{
				APP_POINT p = CalculateCaptionImageSize();
				result.Left += p.X;
			}
			result.Left += m_sMarginCaption.Left;
			result.Top += m_sMarginCaption.Top;
			result.Right -= (int)m_sMarginCaption.Right;
			result.Bottom -= (int)m_sMarginCaption.Bottom;
			if (!result.IsValid())
			{
				result.Right = result.Left;
				result.Bottom = result.Top;
			}
			return result;
		}

		APP_RECT CPopupMenuItem::CalculateRectShortcut()
		{
			if (!getParentMenu())
				return{ 0, 0, 0, 0 };
			APP_RECT result = getRect();
			result.Left += (int)getParentMenu()->m_sSize.WidthImages + (int)getParentMenu()->m_sSize.WidthCaptions;
			result.Right = result.Left + (int)getParentMenu()->m_sSize.WidthShortcuts;
			result.Left += m_sMarginShortcut.Left;
			result.Top += m_sMarginShortcut.Top;
			result.Right -= (int)m_sMarginShortcut.Right;
			result.Bottom -= (int)m_sMarginShortcut.Bottom;
			if (!result.IsValid())
			{
				result.Right = result.Left;
				result.Bottom = result.Top;
			}
			return result;
		}

		APP_RECT CPopupMenuItem::CalculateRectArrow()
		{
			if (!getParentMenu())
				return{ 0, 0, 0, 0 };
			APP_RECT result = getRect();
			result.Left += (int)getParentMenu()->m_sSize.WidthImages + (int)getParentMenu()->m_sSize.WidthCaptions + (int)getParentMenu()->m_sSize.WidthShortcuts;
			result.Left += m_sMarginArrow.Left;
			result.Top += m_sMarginArrow.Top;
			result.Right -= (int)m_sMarginArrow.Right;
			result.Bottom -= (int)m_sMarginArrow.Bottom;
			if (!result.IsValid())
			{
				result.Right = result.Left;
				result.Bottom = result.Top;
			}
			return result;
		}
#pragma endregion

#pragma region Getters
		APP_RECT CPopupMenuItem::getVisibleRect()
		{
			APP_RECT result = ClientToForm(getRenderRect());
			if (getParentMenu())
				result *= getParentMenu()->ClientToForm(getParentMenu()->getClientRect());
			return result;
		}

		CPopupMenuItem::ITEM_TYPE CPopupMenuItem::getType() const
		{
			return m_eType;
		}

		CPopupMenuItem::ITEM_STATE CPopupMenuItem::getState() const
		{
			return m_eState;
		}

		CForm::SHORTCUT CPopupMenuItem::getShortcut() const
		{
			return m_sShortcut;
		}

		String CPopupMenuItem::getShortcutName() const
		{
			return m_sShortcutName;
		}

		String CPopupMenuItem::getCaption() const
		{
			return m_sCaption;
		}

		size_t CPopupMenuItem::getGroup() const
		{
			return m_iGroup;
		}

		CPopupMenu *CPopupMenuItem::getParentMenu()
		{
			return (CPopupMenu*)getParent();
		}

		CPopupMenu *CPopupMenuItem::getRootMenu()
		{
			CPopupMenu *result{ getParentMenu() };
			while (result && result->getParentMenuItem() && result->getParentMenuItem()->getParentMenu())
				result = result->getParentMenuItem()->getParentMenu();
			return result;
		}

		CPopupMenu *CPopupMenuItem::getMenu()
		{
			return (CPopupMenu*)getControl(0);
		}

		math::RECTANGLE<size_t> CPopupMenuItem::getMarginImage() const
		{
			return m_sMarginImage;
		}

		size_t CPopupMenuItem::getMarginImageLeft() const
		{
			return m_sMarginImage.Left;
		}

		size_t CPopupMenuItem::getMarginImageTop() const
		{
			return m_sMarginImage.Top;
		}

		size_t CPopupMenuItem::getMarginImageRight() const
		{
			return m_sMarginImage.Right;
		}

		size_t CPopupMenuItem::getMarginImageBottom() const
		{
			return m_sMarginImage.Bottom;
		}

		math::RECTANGLE<size_t> CPopupMenuItem::getMarginCaptionImage() const
		{
			return m_sMarginCaptionImage;
		}

		size_t CPopupMenuItem::getMarginCaptionImageLeft() const
		{
			return m_sMarginCaptionImage.Left;
		}

		size_t CPopupMenuItem::getMarginCaptionImageTop() const
		{
			return m_sMarginCaptionImage.Top;
		}

		size_t CPopupMenuItem::getMarginCaptionImageRight() const
		{
			return m_sMarginCaptionImage.Right;
		}

		size_t CPopupMenuItem::getMarginCaptionImageBottom() const
		{
			return m_sMarginCaptionImage.Bottom;
		}

		math::RECTANGLE<size_t> CPopupMenuItem::getMarginCaption() const
		{
			return m_sMarginCaption;
		}

		size_t CPopupMenuItem::getMarginCaptionLeft() const
		{
			return m_sMarginCaption.Left;
		}

		size_t CPopupMenuItem::getMarginCaptionTop() const
		{
			return m_sMarginCaption.Top;
		}

		size_t CPopupMenuItem::getMarginCaptionRight() const
		{
			return m_sMarginCaption.Right;
		}

		size_t CPopupMenuItem::getMarginCaptionBottom() const
		{
			return m_sMarginCaption.Bottom;
		}

		math::RECTANGLE<size_t> CPopupMenuItem::getMarginShortcut() const
		{
			return m_sMarginShortcut;
		}

		size_t CPopupMenuItem::getMarginShortcutLeft() const
		{
			return m_sMarginShortcut.Left;
		}

		size_t CPopupMenuItem::getMarginShortcutTop() const
		{
			return m_sMarginShortcut.Top;
		}

		size_t CPopupMenuItem::getMarginShortcutRight() const
		{
			return m_sMarginShortcut.Right;
		}

		size_t CPopupMenuItem::getMarginShortcutBottom() const
		{
			return m_sMarginShortcut.Bottom;
		}

		math::RECTANGLE<size_t> CPopupMenuItem::getMarginArrow() const
		{
			return m_sMarginArrow;
		}

		size_t CPopupMenuItem::getMarginArrowLeft() const
		{
			return m_sMarginArrow.Left;
		}

		size_t CPopupMenuItem::getMarginArrowTop() const
		{
			return m_sMarginArrow.Top;
		}

		size_t CPopupMenuItem::getMarginArrowRight() const
		{
			return m_sMarginArrow.Right;
		}

		size_t CPopupMenuItem::getMarginArrowBottom() const
		{
			return m_sMarginArrow.Bottom;
		}

		bool CPopupMenuItem::getIsSeparator() const
		{
			return m_bIsSeparator;
		}

		int CPopupMenuItem::getImageIndex(const ITEM_TYPE type, const ITEM_STATE state, const bool active, const bool enabled)
		{
			return m_sState[type][state][active][enabled].ImageIndex;
		}

		bool CPopupMenuItem::getIsActive()
		{
			return getParentMenu() && getParentMenu()->getActiveMenuItem() == this;
		}

		CPopupMenuItem::FOnClick CPopupMenuItem::getOnClick()
		{
			return m_fOnClick;
		}

		APP_COLOR CPopupMenuItem::getDisabledTextColor() const
		{
			return m_sDisabledTextColor;
		}

		APP_COLOR CPopupMenuItem::getDisabledShadowColor() const
		{
			return m_sDisabledShadowColor;
		}

		APP_COLOR CPopupMenuItem::getActiveBackgroundColor() const
		{
			return m_sActiveBackgroundColor;
		}

		APP_COLOR CPopupMenuItem::getActiveTextColor() const
		{
			return m_sActiveTextColor;
		}

		APP_COLOR CPopupMenuItem::getActiveShadowColor() const
		{
			return m_sActiveShadowColor;
		}
#pragma endregion

#pragma region Setters
		CPopupMenuItem *CPopupMenuItem::setType(const ITEM_TYPE value)
		{
			if (value != m_eType)
			{
				BeforeChange(true);
				m_eType = value;
				UpdateState();
				AfterChange();
			}
			return this;
		}

		CPopupMenuItem *CPopupMenuItem::setState(const ITEM_STATE value)
		{
			if (value != m_eState && m_eType != mitNormal)
			{
				m_eState = value;
				if (m_pForm)
					m_pForm->LockRepaint();
				if (getParentMenu() && m_eState != misNormal)
					for (size_t i = 0; i < getParentMenu()->getMenuItemCount(); i++) // Remove checked/grayed state from all parent menu items of same type and group
					{
						CPopupMenuItem *item{ getParentMenu()->getMenuItem(i) };
						if (item != this && item->m_eType == mitRadioButton && item->m_eType == m_eType && item->m_iGroup == m_iGroup && item->m_eState != misNormal)
						{
							item->m_eState = misNormal;
							item->Repaint(false);
						}
					}
				Repaint(false);
				if (m_pForm)
					m_pForm->UnlockRepaint();
			}
			return this;
		}

		CPopupMenuItem *CPopupMenuItem::setShortcut(const IWindow::KEY key, const bool control, const bool alt, const bool shift)
		{
			if (key == IWindow::keyUnknown)
			{
				if (key != m_sShortcut.Key)
				{
					m_sShortcut.Key = key;
					m_sShortcutName = L"";
					BeforeChange(false);
					AfterChange();
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
					BeforeChange(false);
					AfterChange();
				}
			}
			return this;
		}

		CPopupMenuItem *CPopupMenuItem::setCaption(const String &value)
		{
			if (value != m_sCaption)
			{
				m_sCaption = value;
				BeforeChange(false);
				AfterChange();
			}
			return this;
		}

		CPopupMenuItem *CPopupMenuItem::setGroup(const size_t value)
		{
			if (value != m_iGroup)
			{
				m_iGroup = value;
				if (UpdateState())
					Repaint(false);
			}
			return this;
		}

		CPopupMenuItem *CPopupMenuItem::setMarginImage(const math::RECTANGLE<size_t> &value)
		{
			if (value != m_sMarginImage)
			{
				m_sMarginImage = value;
				BeforeChange(false);
				AfterChange();
			}
			return this;
		}

		CPopupMenuItem *CPopupMenuItem::setMarginImageLeft(const size_t value)
		{
			return setMarginImage({ value, m_sMarginImage.Top, m_sMarginImage.Right, m_sMarginImage.Bottom });
		}

		CPopupMenuItem *CPopupMenuItem::setMarginImageTop(const size_t value)
		{
			return setMarginImage({ m_sMarginImage.Left, value, m_sMarginImage.Right, m_sMarginImage.Bottom });
		}

		CPopupMenuItem *CPopupMenuItem::setMarginImageRight(const size_t value)
		{
			return setMarginImage({ m_sMarginImage.Left, m_sMarginImage.Top, value, m_sMarginImage.Bottom });
		}

		CPopupMenuItem *CPopupMenuItem::setMarginImageBottom(const size_t value)
		{
			return setMarginImage({ m_sMarginImage.Left, m_sMarginImage.Top, m_sMarginImage.Right, value });
		}

		CPopupMenuItem *CPopupMenuItem::setMarginCaptionImage(const math::RECTANGLE<size_t> &value)
		{
			if (value != m_sMarginCaptionImage)
			{
				m_sMarginCaptionImage = value;
				BeforeChange(false);
				AfterChange();
			}
			return this;
		}

		CPopupMenuItem *CPopupMenuItem::setMarginCaptionImageLeft(const size_t value)
		{
			return setMarginImage({ value, m_sMarginCaptionImage.Top, m_sMarginCaptionImage.Right, m_sMarginCaptionImage.Bottom });
		}

		CPopupMenuItem *CPopupMenuItem::setMarginCaptionImageTop(const size_t value)
		{
			return setMarginImage({ m_sMarginCaptionImage.Left, value, m_sMarginCaptionImage.Right, m_sMarginCaptionImage.Bottom });
		}

		CPopupMenuItem *CPopupMenuItem::setMarginCaptionImageRight(const size_t value)
		{
			return setMarginImage({ m_sMarginCaptionImage.Left, m_sMarginCaptionImage.Top, value, m_sMarginCaptionImage.Bottom });
		}

		CPopupMenuItem *CPopupMenuItem::setMarginCaptionImageBottom(const size_t value)
		{
			return setMarginImage({ m_sMarginCaptionImage.Left, m_sMarginCaptionImage.Top, m_sMarginCaptionImage.Right, value });
		}

		CPopupMenuItem *CPopupMenuItem::setMarginCaption(const math::RECTANGLE<size_t> &value)
		{
			if (value != m_sMarginCaption)
			{
				m_sMarginCaption = value;
				BeforeChange(false);
				AfterChange();
			}
			return this;
		}

		CPopupMenuItem *CPopupMenuItem::setMarginCaptionLeft(const size_t value)
		{
			return setMarginImage({ value, m_sMarginCaption.Top, m_sMarginCaption.Right, m_sMarginCaption.Bottom });
		}

		CPopupMenuItem *CPopupMenuItem::setMarginCaptionTop(const size_t value)
		{
			return setMarginImage({ m_sMarginCaption.Left, value, m_sMarginCaption.Right, m_sMarginCaption.Bottom });
		}

		CPopupMenuItem *CPopupMenuItem::setMarginCaptionRight(const size_t value)
		{
			return setMarginImage({ m_sMarginCaption.Left, m_sMarginCaption.Top, value, m_sMarginCaption.Bottom });
		}

		CPopupMenuItem *CPopupMenuItem::setMarginCaptionBottom(const size_t value)
		{
			return setMarginImage({ m_sMarginCaption.Left, m_sMarginCaption.Top, m_sMarginCaption.Right, value });
		}

		CPopupMenuItem *CPopupMenuItem::setMarginShortcut(const math::RECTANGLE<size_t> &value)
		{
			if (value != m_sMarginShortcut)
			{
				m_sMarginShortcut = value;
				BeforeChange(false);
				AfterChange();
			}
			return this;
		}

		CPopupMenuItem *CPopupMenuItem::setMarginShortcutLeft(const size_t value)
		{
			return setMarginImage({ value, m_sMarginShortcut.Top, m_sMarginShortcut.Right, m_sMarginShortcut.Bottom });
		}

		CPopupMenuItem *CPopupMenuItem::setMarginShortcutTop(const size_t value)
		{
			return setMarginImage({ m_sMarginShortcut.Left, value, m_sMarginShortcut.Right, m_sMarginShortcut.Bottom });
		}

		CPopupMenuItem *CPopupMenuItem::setMarginShortcutRight(const size_t value)
		{
			return setMarginImage({ m_sMarginShortcut.Left, m_sMarginShortcut.Top, value, m_sMarginShortcut.Bottom });
		}

		CPopupMenuItem *CPopupMenuItem::setMarginShortcutBottom(const size_t value)
		{
			return setMarginImage({ m_sMarginShortcut.Left, m_sMarginShortcut.Top, m_sMarginShortcut.Right, value });
		}

		CPopupMenuItem *CPopupMenuItem::setMarginArrow(const math::RECTANGLE<size_t> &value)
		{
			if (value != m_sMarginArrow)
			{
				m_sMarginArrow = value;
				BeforeChange(false);
				AfterChange();
			}
			return this;
		}

		CPopupMenuItem *CPopupMenuItem::setMarginArrowLeft(const size_t value)
		{
			return setMarginImage({ value, m_sMarginArrow.Top, m_sMarginArrow.Right, m_sMarginArrow.Bottom });
		}

		CPopupMenuItem *CPopupMenuItem::setMarginArrowTop(const size_t value)
		{
			return setMarginImage({ m_sMarginArrow.Left, value, m_sMarginArrow.Right, m_sMarginArrow.Bottom });
		}

		CPopupMenuItem *CPopupMenuItem::setMarginArrowRight(const size_t value)
		{
			return setMarginImage({ m_sMarginArrow.Left, m_sMarginArrow.Top, value, m_sMarginArrow.Bottom });
		}

		CPopupMenuItem *CPopupMenuItem::setMarginArrowBottom(const size_t value)
		{
			return setMarginImage({ m_sMarginArrow.Left, m_sMarginArrow.Top, m_sMarginArrow.Right, value });
		}

		CPopupMenuItem *CPopupMenuItem::setIsSeparator(const bool value)
		{
			if (value != m_bIsSeparator)
			{
				m_bIsSeparator = value;
				BeforeChange(true);
				AfterChange();
			}
			return this;
		}

		CPopupMenuItem *CPopupMenuItem::setImageIndex(int value)
		{
			if (value < -1)
				value = -1;
			if (value != m_sState[mitNormal][misNormal][0][0].ImageIndex || value != m_sState[mitNormal][misNormal][0][1].ImageIndex ||
				value != m_sState[mitNormal][misNormal][1][0].ImageIndex || value != m_sState[mitNormal][misNormal][1][1].ImageIndex ||
				value != m_sState[mitNormal][misChecked][0][0].ImageIndex || value != m_sState[mitNormal][misChecked][0][1].ImageIndex ||
				value != m_sState[mitNormal][misChecked][1][0].ImageIndex || value != m_sState[mitNormal][misChecked][1][1].ImageIndex ||
				value != m_sState[mitNormal][misGrayed][0][0].ImageIndex || value != m_sState[mitNormal][misGrayed][0][1].ImageIndex ||
				value != m_sState[mitNormal][misGrayed][1][0].ImageIndex || value != m_sState[mitNormal][misGrayed][1][1].ImageIndex ||

				value != m_sState[mitCheckBox][misNormal][0][0].ImageIndex || value != m_sState[mitCheckBox][misNormal][0][1].ImageIndex ||
				value != m_sState[mitCheckBox][misNormal][1][0].ImageIndex || value != m_sState[mitCheckBox][misNormal][1][1].ImageIndex ||
				value != m_sState[mitCheckBox][misChecked][0][0].ImageIndex || value != m_sState[mitCheckBox][misChecked][0][1].ImageIndex ||
				value != m_sState[mitCheckBox][misChecked][1][0].ImageIndex || value != m_sState[mitCheckBox][misChecked][1][1].ImageIndex ||
				value != m_sState[mitCheckBox][misGrayed][0][0].ImageIndex || value != m_sState[mitCheckBox][misGrayed][0][1].ImageIndex ||
				value != m_sState[mitCheckBox][misGrayed][1][0].ImageIndex || value != m_sState[mitCheckBox][misGrayed][1][1].ImageIndex ||

				value != m_sState[mitRadioButton][misNormal][0][0].ImageIndex || value != m_sState[mitRadioButton][misNormal][0][1].ImageIndex ||
				value != m_sState[mitRadioButton][misNormal][1][0].ImageIndex || value != m_sState[mitRadioButton][misNormal][1][1].ImageIndex ||
				value != m_sState[mitRadioButton][misChecked][0][0].ImageIndex || value != m_sState[mitRadioButton][misChecked][0][1].ImageIndex ||
				value != m_sState[mitRadioButton][misChecked][1][0].ImageIndex || value != m_sState[mitRadioButton][misChecked][1][1].ImageIndex ||
				value != m_sState[mitRadioButton][misGrayed][0][0].ImageIndex || value != m_sState[mitRadioButton][misGrayed][0][1].ImageIndex ||
				value != m_sState[mitRadioButton][misGrayed][1][0].ImageIndex || value != m_sState[mitRadioButton][misGrayed][1][1].ImageIndex)
			{
				m_sState[mitNormal][misNormal][0][0].ImageIndex = value;
				m_sState[mitNormal][misNormal][0][1].ImageIndex = value;
				m_sState[mitNormal][misNormal][1][0].ImageIndex = value;
				m_sState[mitNormal][misNormal][1][1].ImageIndex = value;
				m_sState[mitNormal][misChecked][0][0].ImageIndex = value;
				m_sState[mitNormal][misChecked][0][1].ImageIndex = value;
				m_sState[mitNormal][misChecked][1][0].ImageIndex = value;
				m_sState[mitNormal][misChecked][1][1].ImageIndex = value;
				m_sState[mitNormal][misGrayed][0][0].ImageIndex = value;
				m_sState[mitNormal][misGrayed][0][1].ImageIndex = value;
				m_sState[mitNormal][misGrayed][1][0].ImageIndex = value;
				m_sState[mitNormal][misGrayed][1][1].ImageIndex = value;
				m_sState[mitCheckBox][misNormal][0][0].ImageIndex = value;
				m_sState[mitCheckBox][misNormal][0][1].ImageIndex = value;
				m_sState[mitCheckBox][misNormal][1][0].ImageIndex = value;
				m_sState[mitCheckBox][misNormal][1][1].ImageIndex = value;
				m_sState[mitCheckBox][misChecked][0][0].ImageIndex = value;
				m_sState[mitCheckBox][misChecked][0][1].ImageIndex = value;
				m_sState[mitCheckBox][misChecked][1][0].ImageIndex = value;
				m_sState[mitCheckBox][misChecked][1][1].ImageIndex = value;
				m_sState[mitCheckBox][misGrayed][0][0].ImageIndex = value;
				m_sState[mitCheckBox][misGrayed][0][1].ImageIndex = value;
				m_sState[mitCheckBox][misGrayed][1][0].ImageIndex = value;
				m_sState[mitCheckBox][misGrayed][1][1].ImageIndex = value;
				m_sState[mitRadioButton][misNormal][0][0].ImageIndex = value;
				m_sState[mitRadioButton][misNormal][0][1].ImageIndex = value;
				m_sState[mitRadioButton][misNormal][1][0].ImageIndex = value;
				m_sState[mitRadioButton][misNormal][1][1].ImageIndex = value;
				m_sState[mitRadioButton][misChecked][0][0].ImageIndex = value;
				m_sState[mitRadioButton][misChecked][0][1].ImageIndex = value;
				m_sState[mitRadioButton][misChecked][1][0].ImageIndex = value;
				m_sState[mitRadioButton][misChecked][1][1].ImageIndex = value;
				m_sState[mitRadioButton][misGrayed][0][0].ImageIndex = value;
				m_sState[mitRadioButton][misGrayed][0][1].ImageIndex = value;
				m_sState[mitRadioButton][misGrayed][1][0].ImageIndex = value;
				m_sState[mitRadioButton][misGrayed][1][1].ImageIndex = value;
				if (getParentMenu() && getParentMenu()->getImageList())
					Repaint(false);
			}
			return this;
		}

		CPopupMenuItem *CPopupMenuItem::setImageIndex(const ITEM_TYPE type, const ITEM_STATE state, const bool active, const bool enabled, int value)
		{
			if (value < -1)
				value = -1;
			if (value != m_sState[type][state][active][enabled].ImageIndex)
			{
				m_sState[type][state][active][enabled].ImageIndex = value;
				if (getParentMenu() && getParentMenu()->getImageList() && type == m_eType && state == m_eState && active == getIsActive() && enabled == getEnabled())
					Repaint(false);
			}
			return this;
		}

		CPopupMenuItem *CPopupMenuItem::setOnClick(FOnClick value)
		{
			m_fOnClick = value;
			return this;
		}

		CPopupMenuItem *CPopupMenuItem::setMenu(CPopupMenu *menu)
		{
			if (menu != getMenu())
			{
				// Check menu is not in parent menus
				if (menu && menu->HaveMenuItem(this))
					return this;
				CForm *form{ m_pForm };
				if (form)
					form->LockRepaint();
				if (getParentMenu() && getParentMenu()->getVisibleWithParents())
					Repaint(true);
				if (getMenu() && getMenu()->getVisible())
					getMenu()->Hide();
				DeleteControls();
				if (menu)
				{
					if (menu->getParentMenuItem())
						menu->getParentMenuItem()->setMenu(nullptr);
					m_bAcceptControls = true;
					menu->m_bAcceptParent = true;
					AddControl(menu);
					m_bAcceptControls = false;
					menu->m_bAcceptParent = false;
				}
				if (getParentMenu() && getParentMenu()->getVisibleWithParents())
				{
					if ((!getEnabled() || m_bIsSeparator) && getParentMenu()->getActiveMenuItem() == this)
						getParentMenu()->ClearActiveMenuItemIndex();
					getParentMenu()->Update();
				}
				if (form)
					form->UnlockRepaint();
			}
			return this;
		}

		CPopupMenuItem *CPopupMenuItem::setDisabledTextColor(const APP_COLOR &value)
		{
			if (value != m_sDisabledTextColor)
			{
				m_sDisabledTextColor = value;
				if (!getEnabled() && !m_bIsSeparator && !m_sCaption.empty() && !m_sShortcutName.empty())
					Repaint(false);
			}
			return this;
		}

		CPopupMenuItem *CPopupMenuItem::setDisabledShadowColor(const APP_COLOR &value)
		{
			if (value != m_sDisabledShadowColor)
			{
				m_sDisabledShadowColor = value;
				if (!getEnabled() && !m_bIsSeparator && !m_sCaption.empty() && !m_sShortcutName.empty() && getFont() && getFont()->getShadow())
					Repaint(false);
			}
			return this;
		}

		CPopupMenuItem *CPopupMenuItem::setActiveBackgroundColor(const APP_COLOR &value)
		{
			if (value != m_sActiveBackgroundColor)
			{
				m_sActiveBackgroundColor = value;
				if (getIsActive())
					Repaint(false);
			}
			return this;
		}

		CPopupMenuItem *CPopupMenuItem::setActiveTextColor(const APP_COLOR &value)
		{
			if (value != m_sActiveTextColor)
			{
				m_sActiveTextColor = value;
				if (getIsActive())
					Repaint(false);
			}
			return this;
		}

		CPopupMenuItem *CPopupMenuItem::setActiveShadowColor(const APP_COLOR &value)
		{
			if (value != m_sActiveShadowColor)
			{
				m_sActiveShadowColor = value;
				if (getIsActive() && getFont() && getFont()->getShadow())
					Repaint(false);
			}
			return this;
		}
#pragma endregion

#pragma region Notifications
		void CPopupMenuItem::NotifyOnUpdateComponent(CComponent *component)
		{
			if (getParentMenu() && component == getParentMenu()->getImageList())
				Repaint(false);
			CControl::NotifyOnUpdateComponent(component);
		}

		void CPopupMenuItem::NotifyOnChangeUseParentFont()
		{
			CControl::NotifyOnChangeUseParentFont();
			if (getParentMenu())
				getParentMenu()->Update();
		}

		void CPopupMenuItem::NotifyOnParentFontChangeSize()
		{
			CControl::NotifyOnParentFontChangeSize();
			getParentMenu()->Update();
		}

		void CPopupMenuItem::NotifyOnFontChangeSize()
		{
			CControl::NotifyOnFontChangeSize();
			if (getParentMenu())
				getParentMenu()->Update();
		}

		void CPopupMenuItem::NotifyOnChangeParentStyle()
		{
			CControl::NotifyOnChangeParentStyle();
			if (getParentMenu())
				getParentMenu()->Update();
		}

		void CPopupMenuItem::NotifyOnChangeStyle()
		{
			CControl::NotifyOnChangeStyle();
			if (getParentMenu())
				getParentMenu()->Update();
		}

		void CPopupMenuItem::NotifyOnMouseHover()
		{
			if (!m_bIsSeparator && getEnabled())
				getRootMenu()->ProcessMenuItemOnHover(this);
			CControl::NotifyOnMouseHover();
		}

		bool CPopupMenuItem::NotifyOnLeftMouseButtonDown(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			if (getEnabled() && !getIsSeparator())
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
					for (size_t i = 0; i < getParentMenu()->getMenuItemCount(); i++)
					{
						CPopupMenuItem *item{ getParentMenu()->getMenuItem(i) };
						if (item == this && m_eState != misChecked)
						{
							m_eState = misChecked;
							Repaint(false);
						}
						else if (item != this && item->m_eType == mitRadioButton && item->m_iGroup == m_iGroup && item->m_eState != misNormal)
						{
							item->m_eState = misNormal;
							item->Repaint(false);
						}
					}
					break;
				}
			}
			return CControl::NotifyOnLeftMouseButtonDown(x, y, ctrl, left, middle, right, shift);
		}

		bool CPopupMenuItem::NotifyOnLeftMouseButtonUp(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			if (getEnabled() && !getMenu() && !getIsSeparator())
			{
				getRootMenu()->Hide();
				getParentMenu()->NotifyOnClick(this);
			}
			return CControl::NotifyOnLeftMouseButtonUp(x, y, ctrl, left, middle, right, shift);
		}

		void CPopupMenuItem::NotifyOnPaint(APP_RECT clip)
		{
			if (getVisibleWithParents())
				if (m_bIsSeparator)
					RenderSeparator(clip);
				else
					RenderControl(clip);
			CControl::NotifyOnPaint(clip);
		}
#pragma endregion

#pragma region Render
		void CPopupMenuItem::RenderSeparator(APP_RECT clip)
		{
			clip *= getVisibleRect();
			if (!clip.IsEmpty() && m_iSeparatorHeight > 0)
			{
				APP_RECT rect = ClientToForm(getRect()), img_rect;
				if (getParentMenu()->m_bShowImages)
					rect.Left += getParentMenu()->m_sSize.WidthImages;
				APP_IMAGE *img;
				SelectImage(&img, img_rect);
				IImage *image{ nullptr };
				if (img)
					image = m_pForm->getImageManager()->getImage(img);
				if (image)
					m_pForm->getPresenter()->RenderImage(image, img_rect, rect.Left, rect.Top, 0, 1, 1, true, false, false, clip, rect, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, 0,
						graphics::bplInside, nullptr, nullptr, true);
				else if (m_sSeparatorColor.getAlpha() > 0)
					m_pForm->getPresenter()->FillRect(m_sSeparatorColor, clip, rect, rect, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, 0, graphics::bplInside, nullptr, nullptr, true);
			}
		}

		void CPopupMenuItem::RenderImage(APP_RECT clip, const APP_RECT &rect_image)
		{
			int index{ m_sState[m_eType][m_eState][getIsActive()][getEnabled()].ImageIndex };
			if (getParentMenu()->getImageList() && index >= 0 && index < (int)getParentMenu()->getImageList()->getCount())
			{
				IImage *img{ m_pForm->getImageManager()->getImage(getParentMenu()->getImageList()->getImage(index)) };
				if (img)
				{
					int x{ rect_image.Left + (rect_image.Height() - (int)img->getWidth()) / 2 }, y{ rect_image.Top + (rect_image.Height() - (int)img->getHeight()) / 2 };
					m_pForm->getPresenter()->RenderImage(img, { 0, 0, (int)img->getWidth(), (int)img->getHeight() }, x, y, 0, 1, 1, false, false, false, clip * rect_image,
						rect_image, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, 0, graphics::bplInside, nullptr, nullptr, true);
				}
			}
		}

		void CPopupMenuItem::RenderArrow(APP_RECT clip, const APP_RECT &rect_arrow)
		{
			if (!m_bIsSeparator && getMenu() && !rect_arrow.IsEmpty())
				getParentMenu()->RenderArrowRight(clip, rect_arrow, getEnabled(), getIsActive());
		}

		void CPopupMenuItem::RenderControl(APP_RECT clip)
		{
			clip *= getVisibleRect();
			if (!clip.IsEmpty() && (!m_sCaption.empty() || !m_sShortcutName.empty()))
			{
				APP_RECT rect = ClientToForm(getRect()),
					rect_image = ClientToForm(CalculateRectImage()),
					rect_caption_image = ClientToForm(CalculateRectCaptionImage()),
					rect_caption = ClientToForm(CalculateRectCaption()),
					rect_shortcut = ClientToForm(CalculateRectShortcut()),
					rect_arrow = ClientToForm(CalculateRectArrow());
				APP_COLOR text_color{ getFont()->getColor() }, shadow_color{ getFont()->getShadowColor() };
				// Render background if required and setup text colors
				if (getIsActive())
				{
					m_pForm->getPresenter()->FillRect(m_sActiveBackgroundColor, clip, rect, rect, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, 0, graphics::bplInside, nullptr, nullptr, true);
					text_color = m_sActiveTextColor;
					shadow_color = m_sActiveShadowColor;
				}
				else if (!getEnabled())
				{
					text_color = m_sDisabledTextColor;
					shadow_color = m_sDisabledShadowColor;
				}
				// Render image
				if (getParentMenu()->m_bShowImages && !rect_image.IsEmpty())
					RenderImage(clip, rect_image);
				// Render checkbox or radiobutton image
				if (m_eType == mitCheckBox || m_eType == mitRadioButton)
				{
					APP_POINT size = CalculateCaptionImageSize();
					APP_IMAGE *img;
					APP_RECT img_rect;
					SelectImage(&img, img_rect);
					if (img)
					{
						IImage *image{ m_pForm->getImageManager()->getImage(img) };
						if (image)
						{
							int y{ rect_caption_image.Top + (rect_caption_image.Height() - img_rect.Height()) / 2 };
							m_pForm->getPresenter()->RenderImage(image, img_rect, rect_caption_image.Left, y, 0, 1, 1, false, false, false, clip * rect_caption_image, rect, { 0, 0, 0, 0 }, { 0, 0, 0, 0 },
								0, graphics::bplInside, nullptr, nullptr, true);
						}
					}
				}
				// Render caption
				if (!m_sCaption.empty() && !rect_caption.IsEmpty())
					m_pForm->getPresenter()->RenderString(m_sCaption, getFont(), rect_caption.Left, rect_caption.Top, 0, 1, 1, clip * rect_caption, 0,
						rect, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, 0, graphics::bplInside, true, true, text_color, shadow_color, nullptr, nullptr, true);
				// Render shortcut name
				if (!m_sShortcutName.empty() && !rect_shortcut.IsEmpty())
					m_pForm->getPresenter()->RenderString(m_sShortcutName, getFont(), rect_shortcut.Left, rect_shortcut.Top, 0, 1, 1, clip * rect_shortcut, 0,
						rect, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, 0, graphics::bplInside, true, true, text_color, shadow_color, nullptr, nullptr, true);
				// Render arrow
				if (!m_bIsSeparator && getMenu() && !rect_arrow.IsEmpty())
					RenderArrow(clip, rect_arrow);
			}
		}
#pragma endregion
	}
}