// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#include "Panel.h"
#include "..\..\..\Form.h"
#include "..\..\..\Style.h"
#include "..\..\..\Presenter.h"
#include "..\..\..\..\Math\Utils.h"

namespace licui
{
	namespace application
	{
	#pragma region Constructors
		CPanel::CPanel() :CControl(),
			m_sBackgroundColor{ 240, 240, 240, 255 },
			m_sDisabledTextColor{ 133, 135, 139, 255 },
			m_sDisabledShadowColor{ 133, 135, 139, 255 },
			m_sBevelRaisedColor{ 255, 255, 255, 255 },
			m_sBevelLoweredColor{ 160, 160, 160, 255 },
			m_sBorderColor{ 240, 240, 240, 255 },
			m_sBoxShadowColor{ 0, 0, 255, 255 },
			m_eBevelOuterType{ btRaised },
			m_eBevelInnerType{ btRaised },
			m_iBevelOuterWidth{ 1 },
			m_iBevelInnerWidth{ 1 },
			m_iBorderWidth{ 0 },
			m_iBorderRadius{ 0 },
			m_bBoxShadow{ false },
			m_sBoxShadowShift{ 0, 0 },
			m_iBoxShadowRadius{ 0 },
			m_eCaptionHorizontalAlign{ taCenter },
			m_eCaptionVerticalAlign{ vaMiddle },
			m_sCaptionScale{ 1, 1 },
			m_iCaptionAntiAliazing{ 0 },
			m_sPadding{ 0, 0, 0, 0 },
			m_iBorderAntiAliazing{ 0 }
		{
			m_sClassName = L"CPanel";
			m_bAcceptForm = true;
			m_bAcceptControls = true;
			m_bAcceptParent = true;
			m_bSupportText = true;
			m_sInitialRect = { 0, 0, 185, 105 };
		}

		CPanel::CPanel(CForm *form) :CPanel()
		{
			setForm(form);
		}

		CPanel::CPanel(CControl *parent) : CPanel()
		{
			setParent(parent);
		}
	#pragma endregion

	#pragma region Getters
		APP_RECT CPanel::getClientRect()
		{
			APP_RECT result = CControl::getClientRect();
			result.Left += m_iBevelOuterWidth + m_iBorderWidth + m_iBevelInnerWidth + m_sPadding.Left;
			result.Top += m_iBevelOuterWidth + m_iBorderWidth + m_iBevelInnerWidth + m_sPadding.Top;
			result.Right -= (int)m_iBevelOuterWidth + (int)m_iBorderWidth + (int)m_iBevelInnerWidth + (int)m_sPadding.Right;
			result.Bottom -= (int)m_iBevelOuterWidth + (int)m_iBorderWidth + (int)m_iBevelInnerWidth + (int)m_sPadding.Bottom;
			if (!result.IsValid())
			{
				result.Right = result.Left;
				result.Bottom = result.Top;
			}
			return result;
		}

		APP_RECT CPanel::getRenderRect()
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
				result.Top -= (int)m_iBorderRadius;
				result.Right += (int)m_iBoxShadowRadius;
				result.Bottom += (int)m_iBoxShadowRadius;
				if (!result.IsValid())
				{
					result.Right = result.Left;
					result.Bottom = result.Top;
				}
			}
			return result;
		}

		APP_COLOR CPanel::getBackgroundColor() const
		{
			return m_sBackgroundColor;
		}

		APP_COLOR CPanel::getDisabledTextColor() const
		{
			return m_sDisabledTextColor;
		}

		APP_COLOR CPanel::getDisabledShadowColor() const
		{
			return m_sDisabledShadowColor;
		}

		APP_COLOR CPanel::getBevelRaisedColor() const
		{
			return m_sBevelRaisedColor;
		}

		APP_COLOR CPanel::getBevelLoweredColor() const
		{
			return m_sBevelLoweredColor;
		}

		APP_COLOR CPanel::getBorderColor() const
		{
			return m_sBorderColor;
		}

		APP_COLOR CPanel::getBoxShadowColor() const
		{
			return m_sBoxShadowColor;
		}

		CPanel::BEVEL_TYPE CPanel::getBevelOuterType() const
		{
			return m_eBevelOuterType;
		}

		CPanel::BEVEL_TYPE CPanel::getBevelInnerType() const
		{
			return m_eBevelInnerType;
		}

		size_t CPanel::getBevelOuterWidth() const
		{
			return m_iBevelOuterWidth;
		}

		size_t CPanel::getBevelInnerWidth() const
		{
			return m_iBevelInnerWidth;
		}

		size_t CPanel::getBorderWidth() const
		{
			return m_iBorderWidth;
		}

		size_t CPanel::getBorderRadius() const
		{
			return m_iBorderRadius;
		}

		bool CPanel::getBoxShadow() const
		{
			return m_bBoxShadow;
		}

		APP_POINT CPanel::getBoxShadowShift() const
		{
			return m_sBoxShadowShift;
		}

		int CPanel::getBoxShadowShiftX() const
		{
			return m_sBoxShadowShift.X;
		}

		int CPanel::getBoxShadowShiftY() const
		{
			return m_sBoxShadowShift.Y;
		}

		size_t CPanel::getBoxShadowRadius() const
		{
			return m_iBoxShadowRadius;
		}

		TEXT_ALIGN CPanel::getCaptionHorizontalAlign() const
		{
			return m_eCaptionHorizontalAlign;
		}

		VERTICAL_ALIGN CPanel::getCaptionVerticalAlign() const
		{
			return m_eCaptionVerticalAlign;
		}

		math::POINT<double> CPanel::getCaptionScale() const
		{
			return m_sCaptionScale;
		}

		double CPanel::getCaptionScaleX() const
		{
			return m_sCaptionScale.X;
		}

		double CPanel::getCaptionScaleY() const
		{
			return m_sCaptionScale.Y;
		}

		size_t CPanel::getCaptionAntiAliazing() const
		{
			return m_iCaptionAntiAliazing;
		}

		math::RECTANGLE<size_t> CPanel::getPadding() const
		{
			return m_sPadding;
		}

		size_t CPanel::getPaddingLeft() const
		{
			return m_sPadding.Left;
		}

		size_t CPanel::getPaddingTop() const
		{
			return m_sPadding.Top;
		}

		size_t CPanel::getPaddingRight() const
		{
			return m_sPadding.Right;
		}

		size_t CPanel::getPaddingBottom() const
		{
			return m_sPadding.Bottom;
		}

		String CPanel::getCaption() const
		{
			return m_sCaption;
		}

		size_t CPanel::getBorderAntiAliazing() const
		{
			return m_iBorderAntiAliazing;
		}
	#pragma endregion

	#pragma region Setters
		CPanel *CPanel::setBackgroundColor(const APP_COLOR &value)
		{
			if (value != m_sBackgroundColor)
			{
				m_sBackgroundColor = value;
				Repaint(false);
			}
			return this;
		}

		CPanel *CPanel::setDisabledTextColor(const APP_COLOR &value)
		{
			if (value != m_sDisabledTextColor)
			{
				m_sDisabledTextColor = value;
				if (!m_bEnabled && !m_sCaption.empty())
					Repaint(false);
			}
			return this;
		}

		CPanel *CPanel::setDisabledShadowColor(const APP_COLOR &value)
		{
			if (value != m_sDisabledShadowColor)
			{
				m_sDisabledShadowColor = value;
				if (!m_bEnabled && !m_sCaption.empty())
					Repaint(false);
			}
			return this;
		}

		CPanel *CPanel::setBevelRaisedColor(const APP_COLOR &value)
		{
			if (value != m_sBevelRaisedColor)
			{
				m_sBevelRaisedColor = value;
				if (m_iBevelOuterWidth > 0 || m_iBevelInnerWidth > 0)
					Repaint(false);
			}
			return this;
		}

		CPanel *CPanel::setBevelLoweredColor(const APP_COLOR &value)
		{
			if (value != m_sBevelLoweredColor)
			{
				m_sBevelLoweredColor = value;
				if (m_iBevelOuterWidth > 0 || m_iBevelInnerWidth > 0)
					Repaint(false);
			}
			return this;
		}

		CPanel *CPanel::setBorderColor(const APP_COLOR &value)
		{
			if (value != m_sBorderColor)
			{
				m_sBorderColor = value;
				if (m_iBorderWidth > 0)
					Repaint(false);
			}
			return this;
		}

		CPanel *CPanel::setBoxShadowColor(const APP_COLOR &value)
		{
			if (value != m_sBoxShadowColor)
			{
				m_sBoxShadowColor = value;
				if (m_bBoxShadow)
					Repaint(false);
			}
			return this;
		}

		CPanel *CPanel::setBevelOuterType(const BEVEL_TYPE value)
		{
			if (value != m_eBevelOuterType)
			{
				m_eBevelOuterType = value;
				if (m_iBevelOuterWidth > 0)
					Repaint(false);
			}
			return this;
		}

		CPanel *CPanel::setBevelInnerType(const BEVEL_TYPE value)
		{
			if (value != m_eBevelInnerType)
			{
				m_eBevelInnerType = value;
				if (m_iBevelInnerWidth > 0)
					Repaint(false);
			}
			return this;
		}

		CPanel *CPanel::setBevelOuterWidth(const size_t value)
		{
			if (value != m_iBevelOuterWidth)
			{
				m_iBevelOuterWidth = value;
				if (m_pForm)
					m_pForm->LockRepaint();
				UpdateRect();
				Repaint(true);
				if (m_pForm)
					m_pForm->UnlockRepaint();
			}
			return this;
		}

		CPanel *CPanel::setBevelInnerWidth(const size_t value)
		{
			if (value != m_iBevelInnerWidth)
			{
				m_iBevelInnerWidth = value;
				if (m_pForm)
					m_pForm->LockRepaint();
				UpdateRect();
				Repaint(true);
				if (m_pForm)
					m_pForm->UnlockRepaint();
			}
			return this;
		}

		CPanel *CPanel::setBorderWidth(const size_t value)
		{
			if (value != m_iBorderWidth)
			{
				m_iBorderWidth = value;
				if (m_pForm)
					m_pForm->LockRepaint();
				UpdateRect();
				Repaint(true);
				if (m_pForm)
					m_pForm->UnlockRepaint();
			}
			return this;
		}

		CPanel *CPanel::setBorderRadius(const size_t value)
		{
			if (value != m_iBorderRadius)
			{
				m_iBorderRadius = value;
				if (m_iBevelOuterWidth > 0 || m_iBorderWidth > 0 || m_iBevelInnerWidth > 0)
					Repaint(false);
			}
			return this;
		}

		CPanel *CPanel::setBoxShadow(const bool value)
		{
			if (value != m_bBoxShadow)
			{
				if (m_pForm)
					m_pForm->LockRepaint();
				Repaint(false);
				m_bBoxShadow = value;
				Repaint(false);
				if (m_pForm)
					m_pForm->UnlockRepaint();
			}
			return this;
		}

		CPanel *CPanel::setBoxShadowShift(const APP_POINT &value)
		{
			if (value != m_sBoxShadowShift)
			{
				if (m_pForm)
					m_pForm->LockRepaint();
				if (m_bBoxShadow)
					Repaint(false);
				m_sBoxShadowShift = value;
				if (m_bBoxShadow)
					Repaint(false);
				if (m_pForm)
					m_pForm->UnlockRepaint();
			}
			return this;
		}

		CPanel *CPanel::setBoxShadowShiftX(const int value)
		{
			return setBoxShadowShift({ value, m_sBoxShadowShift.Y });
		}

		CPanel *CPanel::setBoxShadowShiftY(const int value)
		{
			return setBoxShadowShift({ m_sBoxShadowShift.X, value });
		}

		CPanel *CPanel::setBoxShadowRadius(const size_t value)
		{
			if (value != m_iBoxShadowRadius)
			{
				if (m_pForm)
					m_pForm->LockRepaint();
				if (m_bBoxShadow)
					Repaint(false);
				m_iBoxShadowRadius = value;
				if (m_bBoxShadow)
					Repaint(false);
				if (m_pForm)
					m_pForm->UnlockRepaint();
			}
			return this;
		}

		CPanel *CPanel::setCaptionHorizontalAlign(const TEXT_ALIGN value)
		{
			if (value != m_eCaptionHorizontalAlign)
			{
				m_eCaptionHorizontalAlign = value;
				if (!m_sCaption.empty())
					Repaint(false);
			}
			return this;
		}

		CPanel *CPanel::setCaptionVerticalAlign(const VERTICAL_ALIGN value)
		{
			if (value != m_eCaptionVerticalAlign)
			{
				m_eCaptionVerticalAlign = value;
				if (!m_sCaption.empty())
					Repaint(false);
			}
			return this;
		}

		CPanel *CPanel::setCaptionScale(const math::POINT<double> &value)
		{
			if (value != m_sCaptionScale)
			{
				m_sCaptionScale = value;
				if (!m_sCaption.empty())
					Repaint(false);
			}
			return this;
		}

		CPanel *CPanel::setCaptionScaleX(const double value)
		{
			return setCaptionScale({ value, m_sCaptionScale.Y });
		}

		CPanel *CPanel::setCaptionScaleY(const double value)
		{
			return setCaptionScale({ m_sCaptionScale.X, value });
		}

		CPanel *CPanel::setCaptionAntiAliazing(const size_t value)
		{
			if (value != m_iCaptionAntiAliazing)
			{
				m_iCaptionAntiAliazing = value;
				if (!m_sCaption.empty())
					Repaint(false);
			}
			return this;
		}

		CPanel *CPanel::setPadding(const math::RECTANGLE<size_t> &value)
		{
			if (value != m_sPadding)
			{
				m_sPadding = value;
				if (m_pForm)
					m_pForm->LockRepaint();
				UpdateRect();
				Repaint(false);
				if (m_pForm)
					m_pForm->UnlockRepaint();
			}
			return this;
		}

		CPanel *CPanel::setPaddingLeft(const size_t value)
		{
			return setPadding({ value, m_sPadding.Top, m_sPadding.Right, m_sPadding.Bottom });
		}

		CPanel *CPanel::setPaddingTop(const size_t value)
		{
			return setPadding({ m_sPadding.Left, value, m_sPadding.Right, m_sPadding.Bottom });
		}

		CPanel *CPanel::setPaddingRight(const size_t value)
		{
			return setPadding({ m_sPadding.Left, m_sPadding.Top, value, m_sPadding.Bottom });
		}

		CPanel *CPanel::setPaddingBottom(const size_t value)
		{
			return setPadding({ m_sPadding.Left, m_sPadding.Top, m_sPadding.Right, value });
		}

		CPanel *CPanel::setCaption(const String &value)
		{
			if (value != m_sCaption)
			{
				m_sCaption = value;
				Repaint(false);
			}
			return this;
		}

		CPanel *CPanel::setBorderAntiAliazing(const size_t value)
		{
			if (value != m_iBorderAntiAliazing)
			{
				m_iBorderAntiAliazing = value;
				if (m_iBorderRadius > 0)
					Repaint(false);
			}
			return this;
		}
	#pragma endregion

	#pragma region Notifications
		void CPanel::NotifyOnPaint(APP_RECT clip)
		{
			clip *= getVisibleRect();
			if (!clip.IsEmpty())
			{
				APP_RECT rect= ClientToForm(getRect());
				PaintBevelOuter(clip, rect);
				PaintBorder(clip, rect);
				PaintBevelInner(clip, rect);
				PaintBackground(clip, rect);
				PaintCaption(clip, rect);
				PaintBoxShadow(clip);
			}
			CControl::NotifyOnPaint(clip);
		}
	#pragma endregion

	#pragma region Helpers
		bool CPanel::UpdateFromStyle()
		{
			if (!getStyle())
				return false;
			m_sBackgroundColor = getStyle()->getParameterByName(m_sClassName + L".BackgroundColor", m_sBackgroundColor);
			m_sDisabledTextColor = getStyle()->getParameterByName(m_sClassName + L".DisabledTextColor", m_sDisabledTextColor);
			m_sDisabledShadowColor = getStyle()->getParameterByName(m_sClassName + L".DisabledShadowColor", m_sDisabledShadowColor);
			m_sBevelRaisedColor = getStyle()->getParameterByName(m_sClassName + L".BevelRaisedColor", m_sBevelRaisedColor);
			m_sBevelLoweredColor = getStyle()->getParameterByName(m_sClassName + L".BevelLoweredColor", m_sBevelLoweredColor);
			m_sBorderColor = getStyle()->getParameterByName(m_sClassName + L".BorderColor", m_sBorderColor);
			m_eBevelOuterType = (BEVEL_TYPE)getStyle()->getParameterByName(m_sClassName + L".BevelOuterType", (int)m_eBevelOuterType);
			m_eBevelInnerType = (BEVEL_TYPE)getStyle()->getParameterByName(m_sClassName + L".BevelInnerType", (int)m_eBevelInnerType);
			m_iBevelOuterWidth = getStyle()->getParameterByName(m_sClassName + L".BevelOuterWidth", m_iBevelOuterWidth);
			m_iBevelInnerWidth = getStyle()->getParameterByName(m_sClassName + L".BevelInnerWidth", m_iBevelInnerWidth);
			m_iBorderWidth = getStyle()->getParameterByName(m_sClassName + L".BorderWidth", m_iBorderWidth);
			m_iBorderRadius = getStyle()->getParameterByName(m_sClassName + L".BorderRadius", m_iBorderRadius);
			m_bBoxShadow = getStyle()->getParameterByName(m_sClassName + L".BoxShadow", m_bBoxShadow);
			m_sBoxShadowShift = getStyle()->getParameterByName(m_sClassName + L".BoxShadowShift", m_sBoxShadowShift);
			m_iBoxShadowRadius = getStyle()->getParameterByName(m_sClassName + L".BoxShadowRadius", m_iBoxShadowRadius);
			m_eCaptionHorizontalAlign = (TEXT_ALIGN)getStyle()->getParameterByName(m_sClassName + L".CaptionHorizontalAlign", (int)m_eCaptionHorizontalAlign);
			m_eCaptionVerticalAlign = (VERTICAL_ALIGN)getStyle()->getParameterByName(m_sClassName + L".CaptionVerticalAlign", (int)m_eCaptionVerticalAlign);
			m_sCaptionScale = getStyle()->getParameterByName(m_sClassName + L".CaptionScale", m_sCaptionScale);
			m_iCaptionAntiAliazing = getStyle()->getParameterByName(m_sClassName + L".CaptionAntiAliazing", m_iCaptionAntiAliazing);
			m_sPadding = getStyle()->getParameterByName(m_sClassName + L".Padding", m_sPadding);
			return true;
		}
	#pragma endregion

	#pragma region Paint
		void CPanel::PaintBackground(APP_RECT clip, APP_RECT &rect)
		{
			if (m_sBackgroundColor.getAlpha() > 0)
				m_pForm->getPresenter()->FillRect(m_sBackgroundColor, clip, rect,
					rect, { m_iBevelOuterWidth, m_iBevelOuterWidth, m_iBevelOuterWidth, m_iBevelOuterWidth }, { m_iBorderRadius, m_iBorderRadius, m_iBorderRadius, m_iBorderRadius },
					m_iBorderAntiAliazing, graphics::bplInside, nullptr, nullptr, true);
		}

		void CPanel::PaintBevelOuter(APP_RECT clip, APP_RECT &rect)
		{
			if (!rect.IsEmpty() && m_iBevelOuterWidth > 0)
			{
				APP_COLOR c1{ m_eBevelOuterType == btRaised ? m_sBevelRaisedColor : m_sBevelLoweredColor };
				APP_COLOR c2{ m_eBevelOuterType == btRaised ? m_sBevelLoweredColor : m_sBevelRaisedColor };
				math::RECTANGLE<size_t> border{ m_iBevelOuterWidth, m_iBevelOuterWidth, m_iBevelOuterWidth, m_iBevelOuterWidth };
				math::RECTANGLE<size_t> radius{ m_iBorderRadius, m_iBorderRadius, m_iBorderRadius, m_iBorderRadius };
				if (c1.getAlpha() > 0)
				{
					m_pForm->getPresenter()->RenderBorder(graphics::bplLeft, c1, clip, rect, border, radius, m_iBorderAntiAliazing, nullptr, nullptr, true);
					m_pForm->getPresenter()->RenderBorder(graphics::bplTop, c1, clip, rect, border, radius, m_iBorderAntiAliazing, nullptr, nullptr, true);
				}
				if (c2.getAlpha() > 0)
				{
					m_pForm->getPresenter()->RenderBorder(graphics::bplRight, c2, clip, rect, border, radius, m_iBorderAntiAliazing, nullptr, nullptr, true);
					m_pForm->getPresenter()->RenderBorder(graphics::bplBottom, c2, clip, rect, border, radius, m_iBorderAntiAliazing, nullptr, nullptr, true);
				}
				rect.Left += m_iBevelOuterWidth;
				rect.Top += m_iBevelOuterWidth;
				rect.Right -= (int)m_iBevelOuterWidth;
				rect.Bottom -= (int)m_iBevelOuterWidth;
				if (!rect.IsValid())
				{
					rect.Right = rect.Left;
					rect.Bottom = rect.Top;
				}
			}
		}

		void CPanel::PaintBorder(APP_RECT clip, APP_RECT &rect)
		{
			if (!rect.IsEmpty() && m_iBorderWidth > 0)
			{
				if (m_sBorderColor.getAlpha() > 0)
				{
					math::RECTANGLE<size_t> border{ m_iBorderWidth, m_iBorderWidth, m_iBorderWidth, m_iBorderWidth };
					math::RECTANGLE<size_t> radius{ m_iBorderRadius, m_iBorderRadius, m_iBorderRadius, m_iBorderRadius };
					m_pForm->getPresenter()->RenderBorder(graphics::bplLeft, m_sBorderColor, clip, rect, border, radius, m_iBorderAntiAliazing, nullptr, nullptr, true);
					m_pForm->getPresenter()->RenderBorder(graphics::bplTop, m_sBorderColor, clip, rect, border, radius, m_iBorderAntiAliazing, nullptr, nullptr, true);
					m_pForm->getPresenter()->RenderBorder(graphics::bplRight, m_sBorderColor, clip, rect, border, radius, m_iBorderAntiAliazing, nullptr, nullptr, true);
					m_pForm->getPresenter()->RenderBorder(graphics::bplBottom, m_sBorderColor, clip, rect, border, radius, m_iBorderAntiAliazing, nullptr, nullptr, true);
				}
				rect.Left += m_iBorderWidth;
				rect.Top += m_iBorderWidth;
				rect.Right -= (int)m_iBorderWidth;
				rect.Bottom -= (int)m_iBorderWidth;
				if (!rect.IsValid())
				{
					rect.Right = rect.Left;
					rect.Bottom = rect.Top;
				}
			}
		}

		void CPanel::PaintBevelInner(APP_RECT clip, APP_RECT &rect)
		{
			if (!rect.IsEmpty() && m_iBevelInnerWidth > 0)
			{
				APP_COLOR c1{ m_eBevelInnerType == btRaised ? m_sBevelRaisedColor : m_sBevelLoweredColor };
				APP_COLOR c2{ m_eBevelInnerType == btRaised ? m_sBevelLoweredColor : m_sBevelRaisedColor };
				math::RECTANGLE<size_t> border{ m_iBevelInnerWidth, m_iBevelInnerWidth, m_iBevelInnerWidth, m_iBevelInnerWidth };
				math::RECTANGLE<size_t> radius{ m_iBorderRadius, m_iBorderRadius, m_iBorderRadius, m_iBorderRadius };
				if (c1.getAlpha() > 0)
				{
					m_pForm->getPresenter()->RenderBorder(graphics::bplLeft, c1, clip, rect, border, radius, m_iBorderAntiAliazing, nullptr, nullptr, true);
					m_pForm->getPresenter()->RenderBorder(graphics::bplTop, c1, clip, rect, border, radius, m_iBorderAntiAliazing, nullptr, nullptr, true);
				}
				if (c2.getAlpha() > 0)
				{
					m_pForm->getPresenter()->RenderBorder(graphics::bplRight, c2, clip, rect, border, radius, m_iBorderAntiAliazing, nullptr, nullptr, true);
					m_pForm->getPresenter()->RenderBorder(graphics::bplBottom, c2, clip, rect, border, radius, m_iBorderAntiAliazing, nullptr, nullptr, true);
				}
				rect.Left += m_iBevelOuterWidth;
				rect.Top += m_iBevelOuterWidth;
				rect.Right -= (int)m_iBevelOuterWidth;
				rect.Bottom -= (int)m_iBevelOuterWidth;
				if (!rect.IsValid())
				{
					rect.Right = rect.Left;
					rect.Bottom = rect.Top;
				}
			}
		}

		void CPanel::PaintCaption(APP_RECT clip, APP_RECT &rect)
		{
			if (!rect.IsEmpty() && !m_sCaption.empty())
			{
				APP_COLOR text{ m_bEnabled ? getFont()->getColor() : m_sDisabledTextColor };
				APP_COLOR shadow{ m_bEnabled ? getFont()->getShadowColor() : m_sDisabledShadowColor };
				APP_POINT size = getFont()->getStringSize(m_sCaption);
				size.X = (int)(0.5 + size.X * m_sCaptionScale.X);
				size.Y = (int)(0.5 + size.Y * m_sCaptionScale.Y);
				size = math::RotatedRectangleSize(size, -getFont()->getOrientation() * math::PI / 1800.0);
				int x{ rect.Left }, y{ rect.Top };
				switch (m_eCaptionHorizontalAlign)
				{
				case taRight:
					x = rect.Right - size.X - (int)m_sPadding.Right;
					break;
				case taCenter:
					x = rect.Left + (rect.Width() - size.X) / 2;
					break;
				case taLeft:
					x += (int)m_sPadding.Left;
				}
				switch (m_eCaptionVerticalAlign)
				{
				case vaBottom:
					y = rect.Bottom - size.Y - (int)m_sPadding.Bottom;
					break;
				case vaMiddle:
					y = rect.Top + (rect.Height() - size.Y) / 2;
					break;
				case vaTop:
					y += (int)m_sPadding.Top;
				}
				m_pForm->getPresenter()->RenderString(m_sCaption, getFont(), x, y, -getFont()->getOrientation() * math::PI / 1800.0, m_sCaptionScale.X, m_sCaptionScale.Y, clip,
					m_iCaptionAntiAliazing, rect, { 0, 0, 0, 0 }, { m_iBorderRadius, m_iBorderRadius, m_iBorderRadius, m_iBorderRadius }, m_iBorderAntiAliazing,
					graphics::bplInside, true, true, text, shadow, nullptr, nullptr, true);
			}
		}

		void CPanel::PaintBoxShadow(APP_RECT clip)
		{
			if (m_bBoxShadow && m_sBorderColor.getAlpha() > 0)
			{
				APP_RECT rect = ClientToForm(getRect());
				m_pForm->getPresenter()->BoxBlur(m_sBoxShadowColor, m_sBoxShadowShift.X, m_sBoxShadowShift.Y, m_iBoxShadowRadius, clip,
					rect, { m_iBorderRadius, m_iBorderRadius, m_iBorderRadius, m_iBorderRadius }, m_iBorderAntiAliazing, nullptr, nullptr, true);
			}
		}
	#pragma endregion
	}
}