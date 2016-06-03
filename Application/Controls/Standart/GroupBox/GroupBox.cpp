// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#include "GroupBox.h"
#include "..\..\..\Form.h"
#include "..\..\..\Style.h"
#include "..\..\..\Presenter.h"

namespace licui
{
	namespace application
	{
	#pragma region Constructors
		CGroupBox::CGroupBox() :CControl(),
			m_sBackgroundColor{ 240, 240, 240, 255 },
			m_sBorderInnerColor{ 255, 255, 255, 255 },
			m_sBorderOuterColor{ 213, 223, 229, 255 },
			m_sDisabledTextColor{ 133, 135, 139, 255 },
			m_sDisabledShadowColor{ 133, 135, 139, 255 },
			m_iBorderInnerWidth{ 1 },
			m_iBorderOuterWidth{ 1 },
			m_iBorderRadius{ 1 },
			m_sPadding{ 4, 4, 4, 4 },
			m_iBorderAntiAliazing{ 0 },
			m_iMarginCaptionLeft{ 5 }
		{
			m_sClassName = L"CGroupBox";
			m_bAcceptForm = true;
			m_bAcceptControls = true;
			m_bAcceptParent = true;
			m_bSupportText = true;
			m_sInitialRect = { 0, 0, 185, 105 };
		}

		CGroupBox::CGroupBox(CForm *form) : CGroupBox()
		{
			setForm(form);
		}

		CGroupBox::CGroupBox(CControl *parent) : CGroupBox()
		{
			setParent(parent);
		}
	#pragma endregion

	#pragma region Getters
		APP_RECT CGroupBox::getClientRect()
		{
			APP_RECT result = CControl::getClientRect();
			result.Left += std::max(m_iBorderRadius, m_iBorderInnerWidth + m_iBorderOuterWidth) + m_sPadding.Left;
			result.Right -= std::max((int)m_iBorderRadius, (int)m_iBorderInnerWidth + (int)m_iBorderOuterWidth) + (int)m_sPadding.Right;
			result.Bottom -= std::max((int)m_iBorderRadius, (int)m_iBorderInnerWidth + (int)m_iBorderOuterWidth) + (int)m_sPadding.Bottom;
			if (!m_sCaption.empty())
			{
				APP_POINT size = getFont()->getStringSize(m_sCaption);
				result.Top += std::max(size.Y, std::max((int)m_iBorderRadius, (int)m_iBorderInnerWidth + (int)m_iBorderOuterWidth)) + (int)m_sPadding.Top;
			}
			else
				result.Top += std::max(m_iBorderRadius, m_iBorderInnerWidth + m_iBorderOuterWidth) + (int)m_sPadding.Top;
			if (!result.IsValid())
			{
				result.Right = result.Left;
				result.Bottom = result.Top;
			}
			return result;
		}

		APP_COLOR CGroupBox::getBackgroundColor() const
		{
			return m_sBackgroundColor;
		}

		APP_COLOR CGroupBox::getBorderInnerColor() const
		{
			return m_sBorderInnerColor;
		}

		APP_COLOR CGroupBox::getBorderOuterColor() const
		{
			return m_sBorderOuterColor;
		}

		APP_COLOR CGroupBox::getDisabledTextColor() const
		{
			return m_sDisabledTextColor;
		}

		APP_COLOR CGroupBox::getDisabledShadowColor() const
		{
			return m_sDisabledShadowColor;
		}

		size_t CGroupBox::getBorderInnerWidth() const
		{
			return m_iBorderInnerWidth;
		}

		size_t CGroupBox::getBorderOuterWidth() const
		{
			return m_iBorderOuterWidth;
		}

		size_t CGroupBox::getBorderRadius() const
		{
			return m_iBorderRadius;
		}

		String CGroupBox::getCaption() const
		{
			return m_sCaption;
		}

		math::RECTANGLE<size_t> CGroupBox::getPadding() const
		{
			return m_sPadding;
		}

		size_t CGroupBox::getPaddingLeft() const
		{
			return m_sPadding.Left;
		}

		size_t CGroupBox::getPaddingTop() const
		{
			return m_sPadding.Top;
		}

		size_t CGroupBox::getPaddingRight() const
		{
			return m_sPadding.Right;
		}

		size_t CGroupBox::getPaddingBottom() const
		{
			return m_sPadding.Bottom;
		}

		size_t CGroupBox::getBorderAntiAliazing() const
		{
			return m_iBorderAntiAliazing;
		}

		size_t CGroupBox::getMarginCaptionLeft() const
		{
			return m_iMarginCaptionLeft;
		}
	#pragma endregion

	#pragma region Setters
		CGroupBox *CGroupBox::setBackgroundColor(const APP_COLOR &value)
		{
			if (value != m_sBackgroundColor)
			{
				m_sBackgroundColor = value;
				Repaint(false);
			}
			return this;
		}

		CGroupBox *CGroupBox::setBorderInnerColor(const APP_COLOR &value)
		{
			if (value != m_sBorderInnerColor)
			{
				m_sBorderInnerColor = value;
				if (m_iBorderInnerWidth > 0)
					Repaint(false);
			}
			return this;
		}

		CGroupBox *CGroupBox::setBorderOuterColor(const APP_COLOR &value)
		{
			if (value != m_sBorderOuterColor)
			{
				m_sBorderOuterColor = value;
				if (m_iBorderOuterWidth > 0)
					Repaint(false);
			}
			return this;
		}

		CGroupBox *CGroupBox::setDisabledTextColor(const APP_COLOR &value)
		{
			if (value != m_sDisabledTextColor)
			{
				m_sDisabledTextColor = value;
				if (!m_bEnabled)
					Repaint(false);
			}
			return this;
		}

		CGroupBox *CGroupBox::setDisabledShadowColor(const APP_COLOR &value)
		{
			if (value != m_sDisabledShadowColor)
			{
				m_sDisabledShadowColor = value;
				if (!m_bEnabled)
					Repaint(false);
			}
			return this;
		}

		CGroupBox *CGroupBox::setBorderInnerWidth(const size_t value)
		{
			if (value != m_iBorderInnerWidth)
			{
				m_iBorderInnerWidth = value;
				if (m_pForm)
					m_pForm->LockRepaint();
				UpdateRect();
				Repaint(true);
				if (m_pForm)
					m_pForm->UnlockRepaint();
			}
			return this;
		}

		CGroupBox *CGroupBox::setBorderOuterWidth(const size_t value)
		{
			if (value != m_iBorderOuterWidth)
			{
				m_iBorderOuterWidth = value;
				if (m_pForm)
					m_pForm->LockRepaint();
				UpdateRect();
				Repaint(true);
				if (m_pForm)
					m_pForm->UnlockRepaint();
			}
			return this;
		}

		CGroupBox *CGroupBox::setBorderRadius(const size_t value)
		{
			if (value != m_iBorderRadius)
			{
				m_iBorderRadius = value;
				if (m_iBorderInnerWidth > 0 || m_iBorderOuterWidth > 0)
				{
					if (m_pForm)
						m_pForm->LockRepaint();
					UpdateRect();
					Repaint(true);
					if (m_pForm)
						m_pForm->UnlockRepaint();
				}
			}
			return this;
		}

		CGroupBox *CGroupBox::setCaption(const String &value)
		{
			if (value != m_sCaption)
			{
				m_sCaption = value;
				if (m_pForm)
					m_pForm->LockRepaint();
				UpdateRect();
				Repaint(true);
				if (m_pForm)
					m_pForm->UnlockRepaint();
			}
			return this;
		}

		CGroupBox *CGroupBox::setPadding(const math::RECTANGLE<size_t> &value)
		{
			if (value != m_sPadding)
			{
				m_sPadding = value;
				if (m_pForm)
					m_pForm->LockRepaint();
				UpdateRect();
				Repaint(true);
				if (m_pForm)
					m_pForm->UnlockRepaint();
			}
			return this;
		}

		CGroupBox *CGroupBox::setPaddingLeft(const size_t value)
		{
			return setPadding({ value, m_sPadding.Top, m_sPadding.Right, m_sPadding.Bottom });
		}

		CGroupBox *CGroupBox::setPaddingTop(const size_t value)
		{
			return setPadding({ m_sPadding.Left, value, m_sPadding.Right, m_sPadding.Bottom });
		}

		CGroupBox *CGroupBox::setPaddingRight(const size_t value)
		{
			return setPadding({ m_sPadding.Left, m_sPadding.Top, value, m_sPadding.Bottom });
		}

		CGroupBox *CGroupBox::setPaddingBottom(const size_t value)
		{
			return setPadding({ m_sPadding.Left, m_sPadding.Top, m_sPadding.Right, value });
		}

		CGroupBox *CGroupBox::setBorderAntiAliazing(const size_t value)
		{
			if (value != m_iBorderAntiAliazing)
			{
				m_iBorderAntiAliazing = value;
				if ((m_iBorderInnerWidth > 0 || m_iBorderOuterWidth > 0) && m_iBorderRadius > 0)
					Repaint(false);
			}
			return this;
		}

		CGroupBox *CGroupBox::setMarginCaptionLeft(const size_t value)
		{
			if (value != m_iMarginCaptionLeft)
			{
				m_iMarginCaptionLeft = value;
				if (!m_sCaption.empty())
					Repaint(false);
			}
			return this;
		}
	#pragma endregion

	#pragma region Helpers
		bool CGroupBox::UpdateFromStyle()
		{
			if (!getStyle())
				return false;
			m_sBackgroundColor = getStyle()->getParameterByName(m_sClassName + L".BackgroundColor", m_sBackgroundColor);
			m_sBorderInnerColor = getStyle()->getParameterByName(m_sClassName + L".BorderInnerColor", m_sBorderInnerColor);
			m_sBorderOuterColor = getStyle()->getParameterByName(m_sClassName + L".BorderOuterColor", m_sBorderOuterColor);
			m_sDisabledTextColor = getStyle()->getParameterByName(m_sClassName + L".DisabledTextColor", m_sDisabledTextColor);
			m_sDisabledShadowColor = getStyle()->getParameterByName(m_sClassName + L".DisabledShadowColor", m_sDisabledShadowColor);
			m_iBorderInnerWidth = getStyle()->getParameterByName(m_sClassName + L".BorderInnerWidth", m_iBorderInnerWidth);
			m_iBorderOuterWidth = getStyle()->getParameterByName(m_sClassName + L".BorderOuterWidth", m_iBorderOuterWidth);
			m_iBorderRadius = getStyle()->getParameterByName(m_sClassName + L".BorderRadius", m_iBorderRadius);
			m_sPadding = getStyle()->getParameterByName(m_sClassName + L".Padding", m_sPadding);
			m_iBorderAntiAliazing = getStyle()->getParameterByName(m_sClassName + L".BorderAntiAliazing", m_iBorderAntiAliazing);
			m_iMarginCaptionLeft = getStyle()->getParameterByName(m_sClassName + L".MarginCaptionLeft", m_iMarginCaptionLeft);
			return true;
		}

		APP_RECT CGroupBox::CalculateCaptionRect()
		{
			if (m_sCaption.empty())
				return{ 0, 0, 0, 0 };
			APP_RECT result = getRect();
			result.Left += std::max(m_iBorderRadius, m_iBorderInnerWidth) + m_iBorderOuterWidth + m_iMarginCaptionLeft;
			APP_POINT size = getFont()->getStringSize(m_sCaption);
			result.Right = result.Left + size.X;
			result.Right = std::min(result.Right, getRect().Right - std::max((int)m_iBorderRadius, (int)m_iBorderInnerWidth) - (int)m_iBorderOuterWidth);
			result.Bottom = std::min(result.Top + size.Y, getRect().Bottom - (int)m_iBorderOuterWidth - (int)m_iBorderInnerWidth);
			if (!result.IsValid())
				result.Left = result.Right;
			return result;
		}
	#pragma endregion

	#pragma region Notifications
		void CGroupBox::NotifyOnPaint(APP_RECT clip)
		{
			clip *= getVisibleRect();
			if (!clip.IsEmpty())
			{
				APP_RECT rect = ClientToForm(getRect()), rect_caption = CalculateCaptionRect();
				APP_POINT size = getFont()->getStringSize(m_sCaption);
				math::RECTANGLE<size_t> radius{ m_iBorderRadius, m_iBorderRadius, m_iBorderRadius, m_iBorderRadius };
				if (m_sBackgroundColor.getAlpha() > 0)
					m_pForm->getPresenter()->FillRect(m_sBackgroundColor, clip, rect, rect, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, 0, graphics::bplInside, nullptr, nullptr, true);
				if (m_iBorderOuterWidth > 0 && m_sBorderOuterColor.getAlpha() > 0)
				{
					math::RECTANGLE<size_t> border{ m_iBorderOuterWidth, m_iBorderOuterWidth, m_iBorderOuterWidth, m_iBorderOuterWidth };
					APP_RECT block = rect;
					block.Top += size.Y / 2 - (int)m_iBorderOuterWidth;
					if (rect_caption.IsEmpty())
					{
						m_pForm->getPresenter()->RenderBorder(graphics::bplTop, m_sBorderOuterColor, clip, block, border, radius, m_iBorderAntiAliazing, nullptr, nullptr, true);
					}
					else
					{
						APP_RECT new_clip = clip;
						new_clip.Right = std::max(new_clip.Left, rect_caption.Left);
						m_pForm->getPresenter()->RenderBorder(graphics::bplTop, m_sBorderOuterColor, new_clip, block, border, radius, m_iBorderAntiAliazing, nullptr, nullptr, true);
						new_clip = clip;
						new_clip.Left = std::min(new_clip.Right, rect_caption.Right);
						m_pForm->getPresenter()->RenderBorder(graphics::bplTop, m_sBorderOuterColor, new_clip, block, border, radius, m_iBorderAntiAliazing, nullptr, nullptr, true);
					}
					m_pForm->getPresenter()->RenderBorder(graphics::bplLeft, m_sBorderOuterColor, clip, block, border, radius, m_iBorderAntiAliazing, nullptr, nullptr, true);
					m_pForm->getPresenter()->RenderBorder(graphics::bplRight, m_sBorderOuterColor, clip, block, border, radius, m_iBorderAntiAliazing, nullptr, nullptr, true);
					m_pForm->getPresenter()->RenderBorder(graphics::bplBottom, m_sBorderOuterColor, clip, block, border, radius, m_iBorderAntiAliazing, nullptr, nullptr, true);
				}
				if (m_iBorderInnerWidth > 0 && m_sBorderInnerColor.getAlpha() > 0)
				{
					math::RECTANGLE<size_t> border{ m_iBorderInnerWidth, m_iBorderInnerWidth, m_iBorderInnerWidth, m_iBorderInnerWidth };
					APP_RECT block = rect;
					block.Top += size.Y / 2;
					block.Left += m_iBorderOuterWidth;
					block.Right -= (int)m_iBorderOuterWidth;
					block.Bottom -= (int)m_iBorderOuterWidth;
					if (rect_caption.IsEmpty())
					{
						m_pForm->getPresenter()->RenderBorder(graphics::bplTop, m_sBorderInnerColor, clip, block, border, radius, m_iBorderAntiAliazing, nullptr, nullptr, true);
					}
					else
					{
						APP_RECT new_clip = clip;
						new_clip.Right = std::max(new_clip.Left, rect_caption.Left);
						m_pForm->getPresenter()->RenderBorder(graphics::bplTop, m_sBorderInnerColor, new_clip, block, border, radius, m_iBorderAntiAliazing, nullptr, nullptr, true);
						new_clip = clip;
						new_clip.Left = std::min(new_clip.Right, rect_caption.Right);
						m_pForm->getPresenter()->RenderBorder(graphics::bplTop, m_sBorderInnerColor, new_clip, block, border, radius, m_iBorderAntiAliazing, nullptr, nullptr, true);
					}
					m_pForm->getPresenter()->RenderBorder(graphics::bplLeft, m_sBorderInnerColor, clip, block, border, radius, m_iBorderAntiAliazing, nullptr, nullptr, true);
					m_pForm->getPresenter()->RenderBorder(graphics::bplRight, m_sBorderInnerColor, clip, block, border, radius, m_iBorderAntiAliazing, nullptr, nullptr, true);
					m_pForm->getPresenter()->RenderBorder(graphics::bplBottom, m_sBorderInnerColor, clip, block, border, radius, m_iBorderAntiAliazing, nullptr, nullptr, true);
				}
				if (!m_sCaption.empty())
				{
					APP_COLOR text{ m_bEnabled ? getFont()->getColor() : m_sDisabledTextColor };
					APP_COLOR shadow{ m_bEnabled ? getFont()->getShadowColor() : m_sDisabledShadowColor };
					m_pForm->getPresenter()->RenderString(m_sCaption, getFont(), rect_caption.Left, rect_caption.Top, 0, 1, 1, clip, 0, rect_caption, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, 0,
						graphics::bplInside, true, true, text, shadow, nullptr, nullptr, true);
				}
			}
		}
	#pragma endregion
	}
}