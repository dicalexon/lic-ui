// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#include "CheckBox.h"
#include "..\..\..\Form.h"
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
		CCheckBox::CCheckBox() :CControl(),
			m_bAutoSize{ true },
			m_eState{ cbsUnchecked },
			m_sCaption{ L"" },
			m_sMarginImage{ 4, 4, 4, 4 },
			m_sMarginCaption{ 0, 4, 4, 4 },
			m_sDisabledTextColor{ 133, 135, 139, 255 },
			m_sDisabledShadowColor{ 133, 135, 139, 255 },
			m_sFocusedTextColor{ 0, 0, 150, 255 },
			m_sFocusedShadowColor{ 0, 0, 150, 255 },
			m_sHoveredTextColor{ 25, 25, 25, 255 },
			m_sHoveredShadowColor{ 25, 25, 25, 255 },
			m_sFocusedHoveredTextColor{ 25, 25, 175, 255 },
			m_sFocusedHoveredShadowColor{ 25, 25, 175, 255 },
			m_fOnChange{ nullptr }
		{
			m_sClassName = L"CCheckBox";
			m_bAcceptFocus = true;
			m_bAcceptForm = true;
			m_bAcceptParent = true;
			m_bSupportText = true;
			m_bTabStop = true;
			m_sInitialRect = { 0, 0, 120, 20 };
		}

		CCheckBox::CCheckBox(CForm *form) : CCheckBox()
		{
			setForm(form);
		}

		CCheckBox::CCheckBox(CControl *parent) : CCheckBox()
		{
			setParent(parent);
		}
	#pragma endregion

	#pragma region Getters
		bool CCheckBox::getAutoSize() const
		{
			return m_bAutoSize;
		}

		CCheckBox::STATE CCheckBox::getState() const
		{
			return m_eState;
		}

		String CCheckBox::getCaption() const
		{
			return m_sCaption;
		}

		math::RECTANGLE<size_t> CCheckBox::getMarginImage() const
		{
			return m_sMarginImage;
		}

		size_t CCheckBox::getMarginImageLeft() const
		{
			return m_sMarginImage.Left;
		}

		size_t CCheckBox::getMarginImageTop() const
		{
			return m_sMarginImage.Top;
		}

		size_t CCheckBox::getMarginImageRight() const
		{
			return m_sMarginImage.Right;
		}

		size_t CCheckBox::getMarginImageBottom() const
		{
			return m_sMarginImage.Bottom;
		}

		math::RECTANGLE<size_t> CCheckBox::getMarginCaption() const
		{
			return m_sMarginCaption;
		}

		size_t CCheckBox::getMarginCaptionLeft() const
		{
			return m_sMarginCaption.Left;
		}

		size_t CCheckBox::getMarginCaptionTop() const
		{
			return m_sMarginCaption.Top;
		}

		size_t CCheckBox::getMarginCaptionRight() const
		{
			return m_sMarginCaption.Right;
		}

		size_t CCheckBox::getMarginCaptionBottom() const
		{
			return m_sMarginCaption.Bottom;
		}

		APP_COLOR CCheckBox::getDisabledTextColor() const
		{
			return m_sDisabledTextColor;
		}

		APP_COLOR CCheckBox::getDisabledShadowColor() const
		{
			return m_sDisabledShadowColor;
		}

		APP_COLOR CCheckBox::getFocusedTextColor() const
		{
			return m_sFocusedTextColor;
		}

		APP_COLOR CCheckBox::getFocusedShadowColor() const
		{
			return m_sFocusedShadowColor;
		}

		APP_COLOR CCheckBox::getHoveredTextColor() const
		{
			return m_sHoveredTextColor;
		}

		APP_COLOR CCheckBox::getHoveredShadowColor() const
		{
			return m_sHoveredShadowColor;
		}

		APP_COLOR CCheckBox::getFocusedHoveredTextColor() const
		{
			return m_sFocusedHoveredTextColor;
		}

		APP_COLOR CCheckBox::getFocusedHoveredShadowColor() const
		{
			return m_sFocusedHoveredShadowColor;
		}

		CCheckBox::FOnChange CCheckBox::getOnChange() const
		{
			return m_fOnChange;
		}
	#pragma endregion

	#pragma region Setters
		CControl *CCheckBox::setRect(APP_RECT value)
		{
			if (value.Width() != getWidth() || value.Height() != getHeight())
				m_bAutoSize = false;
			return CControl::setRect(value);
		}

		CCheckBox *CCheckBox::setAutoSize(const bool value)
		{
			if (value != m_bAutoSize)
			{
				m_bAutoSize = value;
				UpdateRect();
			}
			return this;
		}

		CCheckBox *CCheckBox::setState(const STATE value)
		{
			if (value != m_eState)
			{
				m_eState = value;
				Repaint(false);
			}
			return this;
		}

		CCheckBox *CCheckBox::setCaption(const String &value)
		{
			if (value != m_sCaption)
			{
				m_sCaption = value;
				if (m_pForm)
					m_pForm->LockRepaint();
				if (m_bAutoSize)
					UpdateRect();
				Repaint(false);
				if (m_pForm)
					m_pForm->UnlockRepaint();
			}
			return this;
		}

		CCheckBox *CCheckBox::setMarginImage(const math::RECTANGLE<size_t> &value)
		{
			if (value != m_sMarginImage)
			{
				m_sMarginImage = value;
				if (m_pForm)
					m_pForm->LockRepaint();
				if (m_bAutoSize)
					UpdateRect();
				Repaint(false);
				if (m_pForm)
					m_pForm->UnlockRepaint();
			}
			return this;
		}

		CCheckBox *CCheckBox::setMarginImageLeft(const size_t value)
		{
			return setMarginImage({ value, m_sMarginImage.Top, m_sMarginImage.Right, m_sMarginImage.Bottom });
		}

		CCheckBox *CCheckBox::setMarginImageTop(const size_t value)
		{
			return setMarginImage({ m_sMarginImage.Left, value, m_sMarginImage.Right, m_sMarginImage.Bottom });
		}

		CCheckBox *CCheckBox::setMarginImageRight(const size_t value)
		{
			return setMarginImage({ m_sMarginImage.Left, m_sMarginImage.Top, value, m_sMarginImage.Bottom });
		}

		CCheckBox *CCheckBox::setMarginImageBottom(const size_t value)
		{
			return setMarginImage({ m_sMarginImage.Left, m_sMarginImage.Top, m_sMarginImage.Right, value });
		}

		CCheckBox *CCheckBox::setMarginCaption(const math::RECTANGLE<size_t> &value)
		{
			if (value != m_sMarginCaption)
			{
				m_sMarginCaption = value;
				if (m_pForm)
					m_pForm->LockRepaint();
				if (m_bAutoSize)
					UpdateRect();
				Repaint(false);
				if (m_pForm)
					m_pForm->UnlockRepaint();
			}
			return this;
		}

		CCheckBox *CCheckBox::setMarginCaptionLeft(const size_t value)
		{
			return setMarginCaption({ value, m_sMarginCaption.Top, m_sMarginCaption.Right, m_sMarginCaption.Bottom });
		}

		CCheckBox *CCheckBox::setMarginCaptionTop(const size_t value)
		{
			return setMarginCaption({ m_sMarginCaption.Left, value, m_sMarginCaption.Right, m_sMarginCaption.Bottom });
		}

		CCheckBox *CCheckBox::setMarginCaptionRight(const size_t value)
		{
			return setMarginCaption({ m_sMarginCaption.Left, m_sMarginCaption.Top, value, m_sMarginCaption.Bottom });
		}

		CCheckBox *CCheckBox::setMarginCaptionBottom(const size_t value)
		{
			return setMarginCaption({ m_sMarginCaption.Left, m_sMarginCaption.Top, m_sMarginCaption.Right, value });
		}

		CCheckBox *CCheckBox::setDisabledTextColor(const APP_COLOR &value)
		{
			if (value != m_sDisabledTextColor)
			{
				m_sDisabledTextColor = value;
				if (!m_bEnabled)
					Repaint(false);
			}
			return this;
		}

		CCheckBox *CCheckBox::setDisabledShadowColor(const APP_COLOR &value)
		{
			if (value != m_sDisabledShadowColor)
			{
				m_sDisabledShadowColor = value;
				if (!m_bEnabled)
					Repaint(false);
			}
			return this;
		}

		CCheckBox *CCheckBox::setFocusedTextColor(const APP_COLOR &value)
		{
			if (value != m_sFocusedTextColor)
			{
				m_sFocusedTextColor = value;
				if (m_pForm && m_pForm->getActiveControl() == this)
					Repaint(false);
			}
			return this;
		}

		CCheckBox *CCheckBox::setFocusedShadowColor(const APP_COLOR &value)
		{
			if (value != m_sFocusedShadowColor)
			{
				m_sFocusedShadowColor = value;
				if (m_pForm && m_pForm->getActiveControl() == this)
					Repaint(false);
			}
			return this;
		}

		CCheckBox *CCheckBox::setHoveredTextColor(const APP_COLOR &value)
		{
			if (value != m_sHoveredTextColor)
			{
				m_sHoveredTextColor = value;
				if (m_pForm && m_pForm->getHoveredControl() == this)
					Repaint(false);
			}
			return this;
		}

		CCheckBox *CCheckBox::setHoveredShadowColor(const APP_COLOR &value)
		{
			if (value != m_sHoveredShadowColor)
			{
				m_sHoveredShadowColor = value;
				if (m_pForm && m_pForm->getHoveredControl() == this)
					Repaint(false);
			}
			return this;
		}

		CCheckBox *CCheckBox::setFocusedHoveredTextColor(const APP_COLOR &value)
		{
			if (value != m_sFocusedHoveredTextColor)
			{
				m_sFocusedHoveredTextColor = value;
				if (m_pForm && m_pForm->getActiveControl() == this && m_pForm->getHoveredControl() == this)
					Repaint(false);
			}
			return this;
		}

		CCheckBox *CCheckBox::setFocusedHoveredShadowColor(const APP_COLOR &value)
		{
			if (value != m_sFocusedHoveredShadowColor)
			{
				m_sFocusedHoveredShadowColor = value;
				if (m_pForm && m_pForm->getActiveControl() == this && m_pForm->getHoveredControl() == this)
					Repaint(false);
			}
			return this;
		}

		CCheckBox *CCheckBox::setOnChange(FOnChange value)
		{
			m_fOnChange = value;
			return this;
		}
	#pragma endregion

	#pragma region Notifications
		bool CCheckBox::NotifyOnKeyDown(const IWindow::KEY key)
		{
			if (m_bEnabled && key == IWindow::keySpace)
			{
				m_eState = m_eState == cbsUnchecked ? cbsChecked : cbsUnchecked;
				NotifyOnChange();
				Repaint(false);
			}
			return CControl::NotifyOnKeyDown(key);
		}

		bool CCheckBox::NotifyOnLeftMouseButtonDown(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			if (m_bEnabled)
			{
				m_eState = m_eState == cbsUnchecked ? cbsChecked : cbsUnchecked;
				NotifyOnChange();
				Repaint(false);
			}
			return CControl::NotifyOnLeftMouseButtonUp(x, y, ctrl, left, middle, right, shift);
		}

		void CCheckBox::NotifyOnMouseHover()
		{
			if (m_bEnabled)
				Repaint(false);
			CControl::NotifyOnMouseHover();
		}

		void CCheckBox::NotifyOnMouseLeave()
		{
			if (m_bEnabled)
				Repaint(false);
			CControl::NotifyOnMouseLeave();
		}

		void CCheckBox::NotifyOnKillFocus()
		{
			Repaint(false);
			CControl::NotifyOnKillFocus();
		}

		void CCheckBox::NotifyOnSetFocus(CControl *old)
		{
			Repaint(false);
			CControl::NotifyOnSetFocus(old);
		}

		void CCheckBox::NotifyOnResetFocus()
		{
			Repaint(false);
			CControl::NotifyOnResetFocus();
		}

		void CCheckBox::NotifyOnPaint(APP_RECT clip)
		{
			clip *= getVisibleRect();
			if (!clip.IsEmpty())
				Paint(clip);
			CControl::NotifyOnPaint(clip);
		}

		void CCheckBox::NotifyOnChange()
		{
			if (m_fOnChange)
				m_fOnChange(this, getCallbackParam());
		}
	#pragma endregion

	#pragma region Helpers
		bool CCheckBox::UpdateFromStyle()
		{
			if (!getStyle())
				return false;
			m_sMarginImage = getStyle()->getParameterByName(m_sClassName + L".MarginImage", m_sMarginImage);
			m_sMarginCaption = getStyle()->getParameterByName(m_sClassName + L".MargiCaption", m_sMarginCaption);
			m_sDisabledTextColor = getStyle()->getParameterByName(m_sClassName + L".DisabledTextColor", m_sDisabledTextColor);
			m_sDisabledShadowColor = getStyle()->getParameterByName(m_sClassName + L".DisabledShadowColor", m_sDisabledShadowColor);
			m_sHoveredTextColor = getStyle()->getParameterByName(m_sClassName + L".HoveredTextColor", m_sHoveredTextColor);
			m_sHoveredShadowColor = getStyle()->getParameterByName(m_sClassName + L".HoveredShadowColor", m_sHoveredShadowColor);
			m_sFocusedTextColor = getStyle()->getParameterByName(m_sClassName + L".FocusedTextColor", m_sFocusedTextColor);
			m_sFocusedShadowColor = getStyle()->getParameterByName(m_sClassName + L".FocusedShadowColor", m_sFocusedShadowColor);
			m_sFocusedHoveredTextColor = getStyle()->getParameterByName(m_sClassName + L".FocusedHoveredTextColor", m_sFocusedHoveredTextColor);
			m_sFocusedHoveredShadowColor = getStyle()->getParameterByName(m_sClassName + L".FocusedHoveredShadowColor", m_sFocusedHoveredShadowColor);
			return true;
		}

		bool CCheckBox::SearchImage(APP_IMAGE **image, APP_RECT &rect, const bool ignore_state)
		{
			String name{ m_sClassName };
			if (ignore_state)
				name += L".normal.unchecked";
			else
			{
				if (!m_bEnabled)
					name += L".disabled";
				else
				{
					if (m_pForm->getActiveControl() == this)
						name += L".focused";
					else
						name += L".normal";
					if (m_pForm->getHoveredControl() == this)
						name += L".hovered";
				}
				switch (m_eState)
				{
				case cbsChecked:
					name += L".checked";
					break;
				case cbsGrayed:
					name += L".grayed";
					break;
				default:
					name += L".unchecked";
				}
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

		APP_RECT CCheckBox::CalculateImageRect()
		{
			APP_IMAGE *image;
			APP_RECT rect;
			if (SearchImage(&image, rect, true))
			{
				APP_RECT result = getRect();
				result.Right = result.Left + rect.Width() + m_sMarginImage.Left + m_sMarginImage.Right;
				if (result.Right > getRect().Right)
					result.Right = getRect().Right;
				if (!result.IsValid())
					result.Right = result.Left;
				return result;
			}
			return{ 0, 0, 0, 0 };
		}

		APP_RECT CCheckBox::CalculateCaptionRect()
		{
			APP_RECT result = getRect();
			APP_IMAGE *image;
			APP_RECT image_rect;
			if (SearchImage(&image, image_rect, true))
			{
				result.Left += image_rect.Width() + m_sMarginImage.Left + m_sMarginImage.Right;
				if (!result.IsValid())
					result.Left = result.Right;
			}
			return result;
		}

		math::POINT<size_t> CCheckBox::CalculateSize()
		{
			math::POINT<size_t> result{ 0, 0 };
			APP_IMAGE *image;
			APP_RECT image_rect;
			if (SearchImage(&image, image_rect, true))
			{
				result.X += image_rect.Width() + m_sMarginImage.Left + m_sMarginImage.Right;
				result.Y = std::max(result.Y, (size_t)image_rect.Height() + m_sMarginImage.Top + m_sMarginImage.Bottom);
			}
			if (!m_sCaption.empty())
			{
				APP_POINT size = getFont()->getStringSize(m_sCaption);
				result.X += size.X + m_sMarginCaption.Left + m_sMarginCaption.Right;
				result.Y = std::max(result.Y, (size_t)size.Y + m_sMarginCaption.Top + m_sMarginCaption.Bottom);
			}
			return result;
		}

		void CCheckBox::UpdateRect()
		{
			if (m_bAutoSize)
			{
				math::POINT<size_t> size = CalculateSize();
				m_sInitialRect.Right = m_sInitialRect.Left + size.X;
				m_sInitialRect.Bottom = m_sInitialRect.Top + size.Y;
			}
			CControl::UpdateRect();
		}

		void CCheckBox::SelectColors(APP_COLOR &text, APP_COLOR &shadow)
		{
			text = getFont()->getColor();
			shadow = getFont()->getShadowColor();
			if (!m_bEnabled)
			{
				if (m_sDisabledTextColor.getAlpha() > 0)
					text = m_sDisabledTextColor;
				if (m_sDisabledShadowColor.getAlpha() > 0)
					shadow = m_sDisabledShadowColor;
				return;
			}
			if (m_pForm)
			{
				if (m_pForm->getActiveControl() == this)
				{
					if (m_sFocusedTextColor.getAlpha() > 0)
						text = m_sFocusedTextColor;
					if (m_sFocusedShadowColor.getAlpha() > 0)
						shadow = m_sFocusedShadowColor;
					if (m_pForm->getHoveredControl() == this)
					{
						if (m_sFocusedHoveredTextColor.getAlpha() > 0)
							text = m_sFocusedHoveredTextColor;
						if (m_sFocusedHoveredShadowColor.getAlpha() > 0)
							shadow = m_sFocusedHoveredShadowColor;
					}
				}
				else if (m_pForm->getHoveredControl() == this)
				{
					if (m_sHoveredTextColor.getAlpha() > 0)
						text = m_sHoveredTextColor;
					if (m_sHoveredShadowColor.getAlpha() > 0)
						shadow = m_sHoveredShadowColor;
				}
			}
		}
	#pragma endregion

	#pragma region Render
		void CCheckBox::Paint(APP_RECT clip)
		{
			APP_IMAGE *image;
			APP_RECT image_rect;
			if (SearchImage(&image, image_rect, false))
			{
				APP_RECT rect = ClientToForm(CalculateImageRect()),
					new_clip{ rect.Left + (int)m_sMarginImage.Left, rect.Top + (int)m_sMarginImage.Top, rect.Right - (int)m_sMarginImage.Right, rect.Bottom - (int)m_sMarginImage.Bottom };
				new_clip *= clip;
				if (!rect.IsEmpty() && new_clip.IsValid() && !new_clip.IsEmpty())
				{
					IImage *img{ m_pForm->getImageManager()->getImage(image) };
					if (img)
					{
						int x{ rect.Left + (int)m_sMarginImage.Left + (rect.Width() - (int)m_sMarginImage.Left - (int)m_sMarginImage.Right - (int)image_rect.Width()) / 2 };
						int y{ rect.Top + (int)m_sMarginImage.Top + (rect.Height() - (int)m_sMarginImage.Top - (int)m_sMarginImage.Bottom - (int)image_rect.Height()) / 2 };
						m_pForm->getPresenter()->RenderImage(img, image_rect, x, y, 0, 1, 1, false, false, false, new_clip, rect, { 0, 0, 0, 0 }, { 0, 0, 0, 0 },
							0, graphics::bplInside, nullptr, nullptr, true);
					}
				}
			}
			if (!m_sCaption.empty())
			{
				APP_RECT rect = ClientToForm(CalculateCaptionRect()),
					new_clip{ rect.Left + (int)m_sMarginCaption.Left, rect.Top + (int)m_sMarginCaption.Top, rect.Right - (int)m_sMarginCaption.Right, rect.Bottom - (int)m_sMarginCaption.Bottom };
				new_clip *= clip;
				if (!rect.IsEmpty() && new_clip.IsValid() && !new_clip.IsEmpty())
				{
					APP_COLOR text, shadow;
					SelectColors(text, shadow);
					APP_POINT size = getFont()->getStringSize(m_sCaption);
					int x{ rect.Left + (int)m_sMarginCaption.Left };
					int y{ rect.Top + (int)m_sMarginCaption.Top + (rect.Height() - (int)m_sMarginCaption.Top - (int)m_sMarginCaption.Bottom - size.Y) / 2 };
					m_pForm->getPresenter()->RenderString(m_sCaption, getFont(), x, y, 0, 1, 1, new_clip, 0, rect, { 0, 0, 0, 0 }, { 0, 0, 0, 0 },
						0, graphics::bplInside, true, true, text, shadow, nullptr, nullptr, true);
				}
			}
		}
	#pragma endregion
	}
}