// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#include "RadioButton.h"
#include "..\..\..\..\Utils\Utils.h"
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
		CRadioButton::CRadioButton() :CControl(),
			m_bAutoSize{ true },
			m_bChecked{ false },
			m_sCaption{ L"" },
			m_sMarginImage{ 4, 4, 4, 4 },
			m_sMarginCaption{ 0, 4, 4, 4 },
			m_iGroupIndex{ 0 },
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
			m_sClassName = L"CRadioButton";
			m_bAcceptFocus = true;
			m_bAcceptForm = true;
			m_bAcceptParent = true;
			m_bSupportText = true;
			m_bTabStop = true;
			m_sInitialRect = { 0, 0, 120, 20 };
		}

		CRadioButton::CRadioButton(CForm *form) : CRadioButton()
		{
			setForm(form);
		}

		CRadioButton::CRadioButton(CControl *parent) : CRadioButton()
		{
			setParent(parent);
		}
	#pragma endregion

	#pragma region Getters
		bool CRadioButton::getAutoSize() const
		{
			return m_bAutoSize;
		}

		bool CRadioButton::getChecked() const
		{
			return m_bChecked;
		}

		String CRadioButton::getCaption() const
		{
			return m_sCaption;
		}

		math::RECTANGLE<size_t> CRadioButton::getMarginImage() const
		{
			return m_sMarginImage;
		}

		size_t CRadioButton::getMarginImageLeft() const
		{
			return m_sMarginImage.Left;
		}

		size_t CRadioButton::getMarginImageTop() const
		{
			return m_sMarginImage.Top;
		}

		size_t CRadioButton::getMarginImageRight() const
		{
			return m_sMarginImage.Right;
		}

		size_t CRadioButton::getMarginImageBottom() const
		{
			return m_sMarginImage.Bottom;
		}

		math::RECTANGLE<size_t> CRadioButton::getMarginCaption() const
		{
			return m_sMarginCaption;
		}

		size_t CRadioButton::getMarginCaptionLeft() const
		{
			return m_sMarginCaption.Left;
		}

		size_t CRadioButton::getMarginCaptionTop() const
		{
			return m_sMarginCaption.Top;
		}

		size_t CRadioButton::getMarginCaptionRight() const
		{
			return m_sMarginCaption.Right;
		}

		size_t CRadioButton::getMarginCaptionBottom() const
		{
			return m_sMarginCaption.Bottom;
		}

		size_t CRadioButton::getGroupIndex() const
		{
			return m_iGroupIndex;
		}

		APP_COLOR CRadioButton::getDisabledTextColor() const
		{
			return m_sDisabledTextColor;
		}

		APP_COLOR CRadioButton::getDisabledShadowColor() const
		{
			return m_sDisabledShadowColor;
		}

		APP_COLOR CRadioButton::getFocusedTextColor() const
		{
			return m_sFocusedTextColor;
		}

		APP_COLOR CRadioButton::getFocusedShadowColor() const
		{
			return m_sFocusedShadowColor;
		}

		APP_COLOR CRadioButton::getHoveredTextColor() const
		{
			return m_sHoveredTextColor;
		}

		APP_COLOR CRadioButton::getHoveredShadowColor() const
		{
			return m_sHoveredShadowColor;
		}

		APP_COLOR CRadioButton::getFocusedHoveredTextColor() const
		{
			return m_sFocusedHoveredTextColor;
		}

		APP_COLOR CRadioButton::getFocusedHoveredShadowColor() const
		{
			return m_sFocusedHoveredShadowColor;
		}

		CRadioButton::FOnChange CRadioButton::getOnChange() const
		{
			return m_fOnChange;
		}
	#pragma endregion

	#pragma region Setters
		CControl *CRadioButton::setRect(APP_RECT value)
		{
			if (value.Width() != getWidth() || value.Height() != getHeight())
				m_bAutoSize = false;
			return CControl::setRect(value);
		}

		CRadioButton *CRadioButton::setAutoSize(const bool value)
		{
			if (value != m_bAutoSize)
			{
				m_bAutoSize = value;
				UpdateRect();
			}
			return this;
		}

		CRadioButton *CRadioButton::setChecked(const bool value)
		{
			if (value != m_bChecked)
			{
				m_bChecked = value;
				if (m_pForm)
					m_pForm->LockRepaint();
				if (m_bChecked)
					UpdateGroup();
				Repaint(false);
				if (m_pForm)
					m_pForm->UnlockRepaint();
			}
			return this;
		}

		CRadioButton *CRadioButton::setCaption(const String &value)
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

		CRadioButton *CRadioButton::setMarginImage(const math::RECTANGLE<size_t> &value)
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

		CRadioButton *CRadioButton::setMarginImageLeft(const size_t value)
		{
			return setMarginImage({ value, m_sMarginImage.Top, m_sMarginImage.Right, m_sMarginImage.Bottom });
		}

		CRadioButton *CRadioButton::setMarginImageTop(const size_t value)
		{
			return setMarginImage({ m_sMarginImage.Left, value, m_sMarginImage.Right, m_sMarginImage.Bottom });
		}

		CRadioButton *CRadioButton::setMarginImageRight(const size_t value)
		{
			return setMarginImage({ m_sMarginImage.Left, m_sMarginImage.Top, value, m_sMarginImage.Bottom });
		}

		CRadioButton *CRadioButton::setMarginImageBottom(const size_t value)
		{
			return setMarginImage({ m_sMarginImage.Left, m_sMarginImage.Top, m_sMarginImage.Right, value });
		}

		CRadioButton *CRadioButton::setMarginCaption(const math::RECTANGLE<size_t> &value)
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

		CRadioButton *CRadioButton::setMarginCaptionLeft(const size_t value)
		{
			return setMarginCaption({ value, m_sMarginCaption.Top, m_sMarginCaption.Right, m_sMarginCaption.Bottom });
		}

		CRadioButton *CRadioButton::setMarginCaptionTop(const size_t value)
		{
			return setMarginCaption({ m_sMarginCaption.Left, value, m_sMarginCaption.Right, m_sMarginCaption.Bottom });
		}

		CRadioButton *CRadioButton::setMarginCaptionRight(const size_t value)
		{
			return setMarginCaption({ m_sMarginCaption.Left, m_sMarginCaption.Top, value, m_sMarginCaption.Bottom });
		}

		CRadioButton *CRadioButton::setMarginCaptionBottom(const size_t value)
		{
			return setMarginCaption({ m_sMarginCaption.Left, m_sMarginCaption.Top, m_sMarginCaption.Right, value });
		}

		CRadioButton *CRadioButton::setGroupIndex(const size_t value)
		{
			if (value != m_iGroupIndex)
			{
				m_iGroupIndex = value;
				if (UpdateState())
					Repaint(false);
			}
			return this;
		}

		CRadioButton *CRadioButton::setDisabledTextColor(const APP_COLOR &value)
		{
			if (value != m_sDisabledTextColor)
			{
				m_sDisabledTextColor = value;
				if (!m_bEnabled)
					Repaint(false);
			}
			return this;
		}

		CRadioButton *CRadioButton::setDisabledShadowColor(const APP_COLOR &value)
		{
			if (value != m_sDisabledShadowColor)
			{
				m_sDisabledShadowColor = value;
				if (!m_bEnabled)
					Repaint(false);
			}
			return this;
		}

		CRadioButton *CRadioButton::setFocusedTextColor(const APP_COLOR &value)
		{
			if (value != m_sFocusedTextColor)
			{
				m_sFocusedTextColor = value;
				if (m_pForm && m_pForm->getActiveControl() == this)
					Repaint(false);
			}
			return this;
		}

		CRadioButton *CRadioButton::setFocusedShadowColor(const APP_COLOR &value)
		{
			if (value != m_sFocusedShadowColor)
			{
				m_sFocusedShadowColor = value;
				if (m_pForm && m_pForm->getActiveControl() == this)
					Repaint(false);
			}
			return this;
		}

		CRadioButton *CRadioButton::setHoveredTextColor(const APP_COLOR &value)
		{
			if (value != m_sHoveredTextColor)
			{
				m_sHoveredTextColor = value;
				if (m_pForm && m_pForm->getHoveredControl() == this)
					Repaint(false);
			}
			return this;
		}

		CRadioButton *CRadioButton::setHoveredShadowColor(const APP_COLOR &value)
		{
			if (value != m_sHoveredShadowColor)
			{
				m_sHoveredShadowColor = value;
				if (m_pForm && m_pForm->getHoveredControl() == this)
					Repaint(false);
			}
			return this;
		}

		CRadioButton *CRadioButton::setFocusedHoveredTextColor(const APP_COLOR &value)
		{
			if (value != m_sFocusedHoveredTextColor)
			{
				m_sFocusedHoveredTextColor = value;
				if (m_pForm && m_pForm->getActiveControl() == this && m_pForm->getHoveredControl() == this)
					Repaint(false);
			}
			return this;
		}

		CRadioButton *CRadioButton::setFocusedHoveredShadowColor(const APP_COLOR &value)
		{
			if (value != m_sFocusedHoveredShadowColor)
			{
				m_sFocusedHoveredShadowColor = value;
				if (m_pForm && m_pForm->getActiveControl() == this && m_pForm->getHoveredControl() == this)
					Repaint(false);
			}
			return this;
		}

		CRadioButton *CRadioButton::setOnChange(FOnChange value)
		{
			m_fOnChange = value;
			return this;
		}
	#pragma endregion

	#pragma region Notifications
		void CRadioButton::NotifyOnAttachToForm()
		{
			if (UpdateState())
				Repaint(false);
			CControl::NotifyOnAttachToForm();
		}

		void CRadioButton::NotifyOnAttachToControl(CControl *control)
		{
			if (UpdateState())
				Repaint(false);
			CControl::NotifyOnAttachToControl(control);
		}

		bool CRadioButton::NotifyOnKeyDown(const IWindow::KEY key)
		{
			if (m_bEnabled && key == IWindow::keySpace && !m_bChecked)
			{
				m_bChecked = true;
				UpdateGroup();
				NotifyOnChange();
				Repaint(false);
			}
			return CControl::NotifyOnKeyDown(key);
		}

		bool CRadioButton::NotifyOnLeftMouseButtonDown(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			if (m_bEnabled && !m_bChecked)
			{
				m_bChecked = true;
				UpdateGroup();
				NotifyOnChange();
				Repaint(false);
			}
			return CControl::NotifyOnLeftMouseButtonUp(x, y, ctrl, left, middle, right, shift);
		}

		void CRadioButton::NotifyOnMouseHover()
		{
			if (m_bEnabled)
				Repaint(false);
			CControl::NotifyOnMouseHover();
		}

		void CRadioButton::NotifyOnMouseLeave()
		{
			if (m_bEnabled)
				Repaint(false);
			CControl::NotifyOnMouseLeave();
		}

		void CRadioButton::NotifyOnKillFocus()
		{
			Repaint(false);
			CControl::NotifyOnKillFocus();
		}

		void CRadioButton::NotifyOnSetFocus(CControl *old)
		{
			Repaint(false);
			CControl::NotifyOnSetFocus(old);
		}

		void CRadioButton::NotifyOnResetFocus()
		{
			Repaint(false);
			CControl::NotifyOnResetFocus();
		}

		void CRadioButton::NotifyOnPaint(APP_RECT clip)
		{
			clip *= getVisibleRect();
			if (!clip.IsEmpty())
				Paint(clip);
			CControl::NotifyOnPaint(clip);
		}

		void CRadioButton::NotifyOnChange()
		{
			if (m_fOnChange)
				m_fOnChange(this, getCallbackParam());
		}
	#pragma endregion

	#pragma region Helpers
		bool CRadioButton::UpdateFromStyle()
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

		bool CRadioButton::SearchImage(APP_IMAGE **image, APP_RECT &rect, const bool ignore_state)
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
				name += m_bChecked ? L".checked" : L".unchecked";
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

		APP_RECT CRadioButton::CalculateImageRect()
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

		APP_RECT CRadioButton::CalculateCaptionRect()
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

		math::POINT<size_t> CRadioButton::CalculateSize()
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

		void CRadioButton::UpdateRect()
		{
			if (m_bAutoSize)
			{
				math::POINT<size_t> size = CalculateSize();
				m_sInitialRect.Right = m_sInitialRect.Left + size.X;
				m_sInitialRect.Bottom = m_sInitialRect.Top + size.Y;
			}
			CControl::UpdateRect();
		}

		void CRadioButton::UpdateGroup()
		{
			if (getParent())
				for (size_t i = 0; i < getParent()->getControlCount(); i++)
				{
					CRadioButton *control{ cast<CRadioButton*>(getParent()->getControl(i)) };
					if (control && control != this && control->m_iGroupIndex == m_iGroupIndex && control->m_bChecked)
					{
						control->m_bChecked = false;
						control->Repaint(false);
					}
				}
			else if (m_pForm)
				for (size_t i = 0; i < m_pForm->getRootControlCount(); i++)
				{
					CRadioButton *control{ cast<CRadioButton*>(m_pForm->getRootControl(i)) };
					if (control && control != this && control->m_iGroupIndex == m_iGroupIndex && control->m_bChecked)
					{
						control->m_bChecked = false;
						control->Repaint(false);
					}
				}
		}

		bool CRadioButton::UpdateState()
		{
			if (!m_bChecked)
				return false;
			if (getParent())
				for (size_t i = 0; i < getParent()->getControlCount(); i++)
				{
					CRadioButton *control{ cast<CRadioButton*>(getParent()->getControl(i)) };
					if (control && control != this && control->m_iGroupIndex == m_iGroupIndex && control->m_bChecked)
					{
						m_bChecked = false;
						return true;
					}
				}
			else if (m_pForm)
				for (size_t i = 0; i < m_pForm->getRootControlCount(); i++)
				{
					CRadioButton *control{ cast<CRadioButton*>(m_pForm->getRootControl(i)) };
					if (control && control != this && control->m_iGroupIndex == m_iGroupIndex && control->m_bChecked)
					{
						m_bChecked = false;
						return true;
					}
				}
			return false;
		}

		void CRadioButton::SelectColors(APP_COLOR &text, APP_COLOR &shadow)
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
		void CRadioButton::Paint(APP_RECT clip)
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