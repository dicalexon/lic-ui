// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#include "Memo.h"
#include "..\..\..\Form.h"
#include "..\..\..\Presenter.h"

namespace licui
{
	namespace application
	{
	#pragma region Constructors & destructor
		CMemo::CMemo():CControl(),
			m_eVerticalScrollBarVisibility{ sbvAuto },
			m_eHorizontalScrollBarVisibility{ sbvAuto },
			m_eHoveredElement{ elNone },
			m_eMouseDownElement{ elNone },
			m_iScrollBarSize{ 19 },
			m_sBorderWidth{ 1, 1, 1, 1 },
			m_sBorderRadius{ 0, 0, 0, 0 },
			m_iBorderAntiAliazing{ 0 },
			m_sPadding{ 1, 1, 1, 1 },
			m_sTextPadding{ 2, 2, 2, 2 }
		{
			m_sClassName = L"CMemo";
			m_bAcceptFocus = true;
			m_bAcceptForm = true;
			m_bAcceptParent = true;
			m_bSupportText = true;
			m_bTabStop = true;
			m_sInitialRect = { 0, 0, 121, 89 };

			m_pVerticalScrollBar = new CMemoScrollBar(this, CBaseScrollBar::sbVertical);
			m_pHorizontalScrollBar = new CMemoScrollBar(this, CBaseScrollBar::sbHorizontal);
			m_pText = new CMemoText(this);

			FillStyles();
		}

		CMemo::CMemo(CForm *form) :CMemo()
		{
			setForm(form);
		}

		CMemo::CMemo(CControl *parent) : CMemo()
		{
			setParent(parent);
		}

		CMemo::~CMemo()
		{
			delete m_pVerticalScrollBar;
			delete m_pHorizontalScrollBar;
			delete m_pText;
			m_pVerticalScrollBar = m_pHorizontalScrollBar = nullptr;
			m_pText = nullptr;
		}

		void CMemo::FillStyles()
		{
			m_aStyle[stNormal].BorderColor[0] = { 219, 223, 230, 255 };
			m_aStyle[stNormal].BorderColor[1] = { 171, 173, 179, 255 };
			m_aStyle[stNormal].BorderColor[2] = { 219, 223, 230, 255 };
			m_aStyle[stNormal].BorderColor[3] = { 227, 233, 239, 255 };
			m_aStyle[stNormal].BackgroundColor = { 255, 255, 255, 255 };
			m_aStyle[stNormal].BoxShadow = false;
			m_aStyle[stNormal].BoxShadowShift = { 0, 0 };
			m_aStyle[stNormal].BoxShadowRadius = 0;
			m_aStyle[stNormal].BoxShadowColor = { 0, 0, 0, 0 };

			m_aStyle[stHovered].BorderColor[0] = { 197, 218, 237, 255 };
			m_aStyle[stHovered].BorderColor[1] = { 87, 148, 191, 255 };
			m_aStyle[stHovered].BorderColor[2] = { 197, 218, 237, 255 };
			m_aStyle[stHovered].BorderColor[3] = { 199, 226, 241, 255 };
			m_aStyle[stHovered].BackgroundColor = { 255, 255, 255, 255 };
			m_aStyle[stHovered].BoxShadow = false;
			m_aStyle[stHovered].BoxShadowShift = { 0, 0 };
			m_aStyle[stHovered].BoxShadowRadius = 0;
			m_aStyle[stHovered].BoxShadowColor = { 0, 0, 0, 0 };

			m_aStyle[stActive].BorderColor[0] = { 181, 207, 231, 255 };
			m_aStyle[stActive].BorderColor[1] = { 61, 123, 173, 255 };
			m_aStyle[stActive].BorderColor[2] = { 181, 207, 231, 255 };
			m_aStyle[stActive].BorderColor[3] = { 183, 217, 237, 255 };
			m_aStyle[stActive].BackgroundColor = { 255, 255, 255, 255 };
			m_aStyle[stActive].BoxShadow = false;
			m_aStyle[stActive].BoxShadowShift = { 0, 0 };
			m_aStyle[stActive].BoxShadowRadius = 0;
			m_aStyle[stActive].BoxShadowColor = { 0, 0, 0, 0 };

			m_aStyle[stActiveHovered].BorderColor[0] = { 181, 207, 231, 255 };
			m_aStyle[stActiveHovered].BorderColor[1] = { 61, 123, 173, 255 };
			m_aStyle[stActiveHovered].BorderColor[2] = { 181, 207, 231, 255 };
			m_aStyle[stActiveHovered].BorderColor[3] = { 183, 217, 237, 255 };
			m_aStyle[stActiveHovered].BackgroundColor = { 255, 255, 255, 255 };
			m_aStyle[stActiveHovered].BoxShadow = false;
			m_aStyle[stActiveHovered].BoxShadowShift = { 0, 0 };
			m_aStyle[stActiveHovered].BoxShadowRadius = 0;
			m_aStyle[stActiveHovered].BoxShadowColor = { 0, 0, 0, 0 };

			m_aStyle[stDisabled].BorderColor[0] = { 175, 175, 175, 255 };
			m_aStyle[stDisabled].BorderColor[1] = { 175, 175, 175, 255 };
			m_aStyle[stDisabled].BorderColor[2] = { 175, 175, 175, 255 };
			m_aStyle[stDisabled].BorderColor[3] = { 175, 175, 175, 255 };
			m_aStyle[stDisabled].BackgroundColor = { 255, 255, 255, 255 };
			m_aStyle[stDisabled].BoxShadow = false;
			m_aStyle[stDisabled].BoxShadowShift = { 0, 0 };
			m_aStyle[stDisabled].BoxShadowRadius = 0;
			m_aStyle[stDisabled].BoxShadowColor = { 0, 0, 0, 0 };
		}
	#pragma endregion

	#pragma region Getters
		APP_RECT CMemo::getClientRect()
		{
			APP_RECT rect = CControl::getClientRect();
			rect.Left += (int)m_sBorderWidth.Left + (int)m_sPadding.Left;
			rect.Top += (int)m_sBorderWidth.Top + (int)m_sPadding.Top;
			rect.Right -= (int)m_sBorderWidth.Right + (int)m_sPadding.Right;
			rect.Bottom -= (int)m_sBorderWidth.Bottom + (int)m_sPadding.Bottom;
			if (!rect.IsValid())
			{
				rect.Right = rect.Left;
				rect.Bottom = rect.Top;
			}
			return rect;
		}

		APP_RECT CMemo::getRenderRect()
		{
			APP_RECT result = getRect();
			STATE state{ getState() };
			if (m_aStyle[state].BoxShadow)
			{
				if (m_aStyle[state].BoxShadowShift.X > 0)
					result.Right += m_aStyle[state].BoxShadowShift.X;
				else
					result.Left += m_aStyle[state].BoxShadowShift.X;
				if (m_aStyle[state].BoxShadowShift.Y > 0)
					result.Bottom += m_aStyle[state].BoxShadowShift.Y;
				else
					result.Top += m_aStyle[state].BoxShadowShift.Y;
				result.Left -= (int)m_aStyle[state].BoxShadowRadius;
				result.Right += (int)m_aStyle[state].BoxShadowRadius;
				result.Top -= (int)m_aStyle[state].BoxShadowRadius;
				result.Bottom += (int)m_aStyle[state].BoxShadowRadius;
				if (!result.IsValid())
				{
					result.Right = result.Left;
					result.Bottom = result.Top;
				}
			}
			return result;
		}

		CURSOR_TYPE CMemo::getCursor() const
		{
			if (m_eHoveredElement == elText)
				return ctIBeam;
			return m_eCursor;
		}

		CMemo::STATE CMemo::getState() const
		{
			if (!m_bEnabled)
				return stDisabled;
			if (m_pForm)
			{
				if (m_pForm->getActiveControl() == this)
				{
					if (m_pForm->getHoveredControl() == this)
						return stActiveHovered;
					return stActive;
				}
				if (m_pForm->getHoveredControl() == this)
					return stHovered;
			}
			return stNormal;
		}

		CMemo::SCROLLBAR_VISIBILITY CMemo::getVerticalScrollBarVisibility() const
		{
			return m_eVerticalScrollBarVisibility;
		}

		CMemo::SCROLLBAR_VISIBILITY CMemo::getHorizontalScrollBarVisibility() const
		{
			return m_eHorizontalScrollBarVisibility;
		}

		size_t CMemo::getScrollBarSize() const
		{
			return m_iScrollBarSize;
		}

		math::RECTANGLE<size_t> CMemo::getBorderWidth() const
		{
			return m_sBorderWidth;
		}

		size_t CMemo::getBorderWidthLeft() const
		{
			return m_sBorderWidth.Left;
		}

		size_t CMemo::getBorderWidthTop() const
		{
			return m_sBorderWidth.Top;
		}

		size_t CMemo::getBorderWidthRight() const
		{
			return m_sBorderWidth.Right;
		}

		size_t CMemo::getBorderWidthBottom() const
		{
			return m_sBorderWidth.Bottom;
		}

		math::RECTANGLE<size_t> CMemo::getBorderRadius() const
		{
			return m_sBorderRadius;
		}

		size_t CMemo::getBorderRadiusLeftTop() const
		{
			return m_sBorderRadius[0];
		}

		size_t CMemo::getBorderRadiusRightTop() const
		{
			return m_sBorderRadius[1];
		}

		size_t CMemo::getBorderRadiusRightBottom() const
		{
			return m_sBorderRadius[2];
		}

		size_t CMemo::getBorderRadiusLeftBottom() const
		{
			return m_sBorderRadius[3];
		}

		size_t CMemo::getBorderAntiAliazing() const
		{
			return m_iBorderAntiAliazing;
		}

		math::RECTANGLE<size_t> CMemo::getPadding() const
		{
			return m_sPadding;
		}

		size_t CMemo::getPaddingLeft() const
		{
			return m_sPadding.Left;
		}

		size_t CMemo::getPaddingTop() const
		{
			return m_sPadding.Top;
		}

		size_t CMemo::getPaddingRight() const
		{
			return m_sPadding.Right;
		}

		size_t CMemo::getPaddingBottom() const
		{
			return m_sPadding.Bottom;
		}

		math::RECTANGLE<size_t> CMemo::getTextPadding() const
		{
			return m_sTextPadding;
		}

		size_t CMemo::getTextPaddingLeft() const
		{
			return m_sTextPadding.Left;
		}

		size_t CMemo::getTextPaddingTop() const
		{
			return m_sTextPadding.Top;
		}

		size_t CMemo::getTextPaddingRight() const
		{
			return m_sTextPadding.Right;
		}

		size_t CMemo::getTextPaddingBottom() const
		{
			return m_sTextPadding.Bottom;
		}

		APP_COLOR CMemo::getBorderColorLeft(const STATE state) const
		{
			return m_aStyle[state].BorderColor[0];
		}

		APP_COLOR CMemo::getBorderColorTop(const STATE state) const
		{
			return m_aStyle[state].BorderColor[1];
		}

		APP_COLOR CMemo::getBorderColorRight(const STATE state) const
		{
			return m_aStyle[state].BorderColor[2];
		}

		APP_COLOR CMemo::getBorderColorBottom(const STATE state) const
		{
			return m_aStyle[state].BorderColor[3];
		}

		APP_COLOR CMemo::getBackgroundColor(const STATE state) const
		{
			return m_aStyle[state].BackgroundColor;
		}

		bool CMemo::getBoxShadow(const STATE state) const
		{
			return m_aStyle[state].BoxShadow;
		}

		APP_POINT CMemo::getBoxShadowShift(const STATE state) const
		{
			return m_aStyle[state].BoxShadowShift;
		}

		int CMemo::getBoxShadowShiftX(const STATE state) const
		{
			return m_aStyle[state].BoxShadowShift.X;
		}

		int CMemo::getBoxShadowShiftY(const STATE state) const
		{
			return m_aStyle[state].BoxShadowShift.Y;
		}

		size_t CMemo::getBoxShadowRadius(const STATE state) const
		{
			return m_aStyle[state].BoxShadowRadius;
		}

		APP_COLOR CMemo::getBoxShadowColor(const STATE state) const
		{
			return m_aStyle[state].BoxShadowColor;
		}

		IImage::GRADIENT_TYPE CMemo::getGradientType(const STATE state) const
		{
			return m_aStyle[state].GradientType;
		}

		size_t CMemo::getGradientPointCount(const STATE state) const
		{
			return m_aStyle[state].GradientPointCount;
		}

		double CMemo::getGradientPointPosition(const STATE state, const size_t index) const
		{
			if (index < m_aStyle[state].GradientPointCount)
				return m_aStyle[state].GradientPoints[index].Position;
			return 0;
		}

		APP_COLOR CMemo::getGradientPointColor(const STATE state, const size_t index) const
		{
			if (index < m_aStyle[state].GradientPointCount)
				return m_aStyle[state].GradientPoints[index].Color;
			return{ 0, 0, 0, 0 };
		}
	#pragma endregion

	#pragma region Setters
		CMemo *CMemo::setVerticalScrollBarVisibility(const SCROLLBAR_VISIBILITY value)
		{
			if (value != m_eVerticalScrollBarVisibility)
			{
				m_eVerticalScrollBarVisibility = value;
				Update();
				m_pText->UpdateCaret();
				Repaint(false);
			}
			return this;
		}

		CMemo *CMemo::setHorizontalScrollBarVisibility(const SCROLLBAR_VISIBILITY value)
		{
			if (value != m_eHorizontalScrollBarVisibility)
			{
				m_eHorizontalScrollBarVisibility = value;
				Update();
				m_pText->UpdateCaret();
				Repaint(false);
			}
			return this;
		}

		CMemo *CMemo::setScrollBarSize(size_t value)
		{
			if (value < 1)
				value = 1;
			if (value != m_iScrollBarSize)
			{
				m_iScrollBarSize = value;
				if (m_eVerticalScrollBarVisibility != sbvNone || m_eHorizontalScrollBarVisibility != sbvNone)
					UpdateAll();
			}
			return this;
		}

		CMemo *CMemo::setBorderWidth(const math::RECTANGLE<size_t> &value)
		{
			if (value != m_sBorderWidth)
			{
				m_sBorderWidth = value;
				UpdateAll();
			}
			return this;
		}

		CMemo *CMemo::setBorderWidthLeft(const size_t value)
		{
			return setBorderWidth({ value, m_sBorderWidth.Top, m_sBorderWidth.Right, m_sBorderWidth.Bottom });
		}

		CMemo *CMemo::setBorderWidthTop(const size_t value)
		{
			return setBorderWidth({ m_sBorderWidth.Left, value, m_sBorderWidth.Right, m_sBorderWidth.Bottom });
		}

		CMemo *CMemo::setBorderWidthRight(const size_t value)
		{
			return setBorderWidth({ m_sBorderWidth.Left, m_sBorderWidth.Top, value, m_sBorderWidth.Bottom });
		}

		CMemo *CMemo::setBorderWidthBottom(const size_t value)
		{
			return setBorderWidth({ m_sBorderWidth.Left, m_sBorderWidth.Top, m_sBorderWidth.Right, value });
		}

		CMemo *CMemo::setBorderRadius(const math::RECTANGLE<size_t> &value)
		{
			if (value != m_sBorderRadius)
			{
				m_sBorderRadius = value;
				UpdateAll();
			}
			return this;
		}

		CMemo *CMemo::setBorderRadiusLeftTop(const size_t value)
		{
			return setBorderRadius({ value, m_sBorderRadius[1], m_sBorderRadius[2], m_sBorderRadius[3] });
		}

		CMemo *CMemo::setBorderRadiusRightTop(const size_t value)
		{
			return setBorderRadius({ m_sBorderRadius[0], value, m_sBorderRadius[2], m_sBorderRadius[3] });
		}

		CMemo *CMemo::setBorderRadiusRightBottom(const size_t value)
		{
			return setBorderRadius({ m_sBorderRadius[0], m_sBorderRadius[1], value, m_sBorderRadius[3] });
		}

		CMemo *CMemo::setBorderRadiusLeftBottom(const size_t value)
		{
			return setBorderRadius({ m_sBorderRadius[0], m_sBorderRadius[1], m_sBorderRadius[2], value });
		}

		CMemo *CMemo::setBorderAntiAliazing(const size_t value)
		{
			if (value != m_iBorderAntiAliazing)
			{
				m_iBorderAntiAliazing = value;
				Repaint(false);
			}
			return this;
		}

		CMemo *CMemo::setPadding(const math::RECTANGLE<size_t> &value)
		{
			if (value != m_sPadding)
			{
				m_sPadding = value;
				UpdateAll();
			}
			return this;
		}

		CMemo *CMemo::setPaddingLeft(const size_t value)
		{
			return setPadding({ value, m_sPadding.Top, m_sPadding.Right, m_sPadding.Bottom });
		}

		CMemo *CMemo::setPaddingTop(const size_t value)
		{
			return setPadding({ m_sPadding.Left, value, m_sPadding.Right, m_sPadding.Bottom });
		}

		CMemo *CMemo::setPaddingRight(const size_t value)
		{
			return setPadding({ m_sPadding.Left, m_sPadding.Top, value, m_sPadding.Bottom });
		}

		CMemo *CMemo::setPaddingBottom(const size_t value)
		{
			return setPadding({ m_sPadding.Left, m_sPadding.Top, m_sPadding.Right, value });
		}

		CMemo *CMemo::setTextPadding(const math::RECTANGLE<size_t> &value)
		{
			if (value != m_sTextPadding)
			{
				m_sTextPadding = value;
				UpdateAll();
			}
			return this;
		}

		CMemo *CMemo::setTextPaddingLeft(const size_t value)
		{
			return setTextPadding({ value, m_sTextPadding.Top, m_sTextPadding.Right, m_sTextPadding.Bottom });
		}

		CMemo *CMemo::setTextPaddingTop(const size_t value)
		{
			return setTextPadding({ m_sTextPadding.Left, value, m_sTextPadding.Right, m_sTextPadding.Bottom });
		}

		CMemo *CMemo::setTextPaddingRight(const size_t value)
		{
			return setTextPadding({ m_sTextPadding.Left, m_sTextPadding.Top, value, m_sTextPadding.Bottom });
		}

		CMemo *CMemo::setTextPaddingBottom(const size_t value)
		{
			return setTextPadding({ m_sTextPadding.Left, m_sTextPadding.Top, m_sTextPadding.Right, value });
		}

		CMemo *CMemo::setBorderColorLeft(const STATE state, const APP_COLOR &value)
		{
			if (value != m_aStyle[state].BorderColor[0])
			{
				m_aStyle[state].BorderColor[0] = value;
				if (state == getState())
					Repaint(false);
			}
			return this;
		}

		CMemo *CMemo::setBorderColorTop(const STATE state, const APP_COLOR &value)
		{
			if (value != m_aStyle[state].BorderColor[1])
			{
				m_aStyle[state].BorderColor[1] = value;
				if (state == getState())
					Repaint(false);
			}
			return this;
		}

		CMemo *CMemo::setBorderColorRight(const STATE state, const APP_COLOR &value)
		{
			if (value != m_aStyle[state].BorderColor[2])
			{
				m_aStyle[state].BorderColor[2] = value;
				if (state == getState())
					Repaint(false);
			}
			return this;
		}

		CMemo *CMemo::setBorderColorBottom(const STATE state, const APP_COLOR &value)
		{
			if (value != m_aStyle[state].BorderColor[3])
			{
				m_aStyle[state].BorderColor[3] = value;
				if (state == getState())
					Repaint(false);
			}
			return this;
		}

		CMemo *CMemo::setBackgroundColor(const STATE state, const APP_COLOR &value)
		{
			if (value != m_aStyle[state].BackgroundColor)
			{
				m_aStyle[state].BackgroundColor = value;
				if (state == getState())
					Repaint(false);
			}
			return this;
		}

		CMemo *CMemo::setBoxShadow(const STATE state, const bool value)
		{
			if (value != m_aStyle[state].BoxShadow)
			{
				m_aStyle[state].BoxShadow = value;
				if (state == getState())
					Repaint(false);
			}
			return this;
		}

		CMemo *CMemo::setBoxShadowShift(const STATE state, const APP_POINT &value)
		{
			if (value != m_aStyle[state].BoxShadowShift)
			{
				m_aStyle[state].BoxShadowShift = value;
				if (state == getState() && m_aStyle[state].BoxShadow)
					Repaint(false);
			}
			return this;
		}

		CMemo *CMemo::setBoxShadowShiftX(const STATE state, const int value)
		{
			return setBoxShadowShift(state, { value, m_aStyle[state].BoxShadowShift.Y });
		}

		CMemo *CMemo::setBoxShadowShiftY(const STATE state, const int value)
		{
			return setBoxShadowShift(state, { m_aStyle[state].BoxShadowShift.X, value });
		}

		CMemo *CMemo::setBoxShadowRadius(const STATE state, const size_t value)
		{
			if (value != m_aStyle[state].BoxShadowRadius)
			{
				m_aStyle[state].BoxShadowRadius = value;
				if (state == getState() && m_aStyle[state].BoxShadow)
					Repaint(false);
			}
			return this;
		}

		CMemo *CMemo::setBoxShadowColor(const STATE state, const APP_COLOR &value)
		{
			if (value != m_aStyle[state].BoxShadowColor)
			{
				m_aStyle[state].BoxShadowColor = value;
				if (state == getState() && m_aStyle[state].BoxShadow)
					Repaint(false);
			}
			return this;
		}

		CMemo *CMemo::setGradientType(const STATE state, const IImage::GRADIENT_TYPE value)
		{
			if (value != m_aStyle[state].GradientType)
			{
				m_aStyle[state].GradientType = value;
				if (state == getState() && m_aStyle[state].GradientPointCount > 0)
					Repaint(false);
			}
			return this;
		}

		CMemo *CMemo::setGradientPointCount(const STATE state, const size_t value)
		{
			if (value != m_aStyle[state].GradientType)
			{
				m_aStyle[state].setGradientPointCount(value);
				if (state == getState())
					Repaint(false);
			}
			return this;
		}

		CMemo *CMemo::setGradientPointPosition(const STATE state, const size_t index, const double value)
		{
			if (index < m_aStyle[state].GradientPointCount && value != m_aStyle[state].GradientPoints[index].Position)
			{
				m_aStyle[state].GradientPoints[index].Position = value;
				m_aStyle[state].GradientPointsSorted = false;
				if (getState() == state)
					Repaint(false);
			}
			return this;
		}

		CMemo *CMemo::setGradientPointColor(const STATE state, const size_t index, const APP_COLOR &value)
		{
			if (index < m_aStyle[state].GradientPointCount && value != m_aStyle[state].GradientPoints[index].Color)
			{
				m_aStyle[state].GradientPoints[index].Color = value;
				if (getState() == state)
					Repaint(false);
			}
			return this;
		}

		CMemo *CMemo::setGradientPoints(const STATE state, const size_t count, IImage::GRADIENT_POINT *points)
		{
			m_aStyle[state].setGradientPointCount(count);
			for (size_t i = 0; i < m_aStyle[state].GradientPointCount; i++)
				m_aStyle[state].GradientPoints[i] = points[i];
			m_aStyle[state].GradientPointsSorted = false;
			if (state == getState())
				Repaint(false);
			return this;
		}
	#pragma endregion

	#pragma region Notifications
		void CMemo::NotifyOnChangeUseParentFont()
		{
			CControl::NotifyOnChangeUseParentFont();
			Update();
			m_pText->UpdateCaret();
		}

		void CMemo::NotifyOnParentFontChangeSize()
		{
			CControl::NotifyOnParentFontChangeSize();
			Update();
			m_pText->UpdateCaret();
		}

		void CMemo::NotifyOnFontChangeSize()
		{
			CControl::NotifyOnFontChangeSize();
			Update();
			m_pText->UpdateCaret();
		}

		void CMemo::NotifyOnChangeParentStyle()
		{
			CControl::NotifyOnChangeParentStyle();
			Update();
			m_pText->UpdateCaret();
		}

		void CMemo::NotifyOnChangeStyle()
		{
			CControl::NotifyOnChangeStyle();
			Update();
			m_pText->UpdateCaret();
		}

		void CMemo::NotifyOnResize(const APP_POINT &old_size, const APP_POINT &new_size)
		{
			CControl::NotifyOnResize(old_size, new_size);
			Update();
			m_pText->UpdateCaret();
		}

		bool CMemo::NotifyOnKeyDown(const IWindow::KEY key)
		{
			if (m_bEnabled)
			{
				bool ctrl, alt, shift, text_changed, caret_moved;
				m_pForm->getWindow()->getControlKeys(ctrl, shift, alt);
				if (m_pText->ProcessKeyDown(key, ctrl, alt, shift, text_changed, caret_moved))
				{
					if (text_changed)
						Update();
					if (caret_moved)
						m_pText->ScrollToCaret();
					if (m_pVerticalScrollBar->getEnabled())
						m_pVerticalScrollBar->setScroll(m_pText->getVerticalScroll());
					if (m_pHorizontalScrollBar->getEnabled())
						m_pHorizontalScrollBar->setScroll(m_pText->getHorizontalScroll());
					m_pText->UpdateCaret();
					Repaint(false);
				}
			}
			return CControl::NotifyOnKeyDown(key);
		}

		bool CMemo::NotifyOnChar(const wchar_t chr)
		{
			if (m_bEnabled && m_pText->ProcessChar(chr))
			{
				Update();
				m_pText->ScrollToCaret();
				if (m_pVerticalScrollBar->getEnabled())
					m_pVerticalScrollBar->setScroll(m_pText->getVerticalScroll());
				if (m_pHorizontalScrollBar->getEnabled())
					m_pHorizontalScrollBar->setScroll(m_pText->getHorizontalScroll());
				m_pText->UpdateCaret();
				Repaint(false);
			}
			return CControl::NotifyOnChar(chr);
		}

		bool CMemo::NotifyOnMouseMove(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			if (m_bEnabled)
			{
				bool changed{ UpdateHoveredElement(x, y) }, repaint_required{ false };
				if (m_eHoveredElement == elVScroll && m_pVerticalScrollBar->ProcessMouseMove(x, y, repaint_required) && repaint_required)
				{
					changed = true;
					m_pText->setVerticalScroll((size_t)m_pVerticalScrollBar->getScroll());
				}
				else if (m_eHoveredElement == elHScroll && m_pHorizontalScrollBar->ProcessMouseMove(x, y, repaint_required) && repaint_required)
				{
					changed = true;
					m_pText->setHorizontalScroll((size_t)m_pHorizontalScrollBar->getScroll());
				}
				else if (m_eHoveredElement == elText && m_pText->ProcessMouseMove(x, y))
				{
					changed = true;
					if (m_pVerticalScrollBar->getEnabled())
						m_pVerticalScrollBar->setScroll((int)m_pText->getVerticalScroll());
					if (m_pHorizontalScrollBar->getEnabled())
						m_pHorizontalScrollBar->setScroll((int)m_pText->getHorizontalScroll());
				}
				if (changed)
				{
					m_pText->UpdateCaret();
					Repaint(false);
				}
			}
			CControl::NotifyOnMouseMove(x, y, ctrl, left, middle, right, shift);
			return true;
		}

		bool CMemo::NotifyOnLeftMouseButtonDown(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			bool alt{ m_pForm->getWindow()->getKeyIsDown(IWindow::keyMenu) };
			if (m_bEnabled && (ProcessMouseUp(x, y, ctrl, shift) || ProcessMouseDown(x, y, ctrl, alt, shift)))
				Repaint(false);
			CControl::NotifyOnLeftMouseButtonDown(x, y, ctrl, left, middle, right, shift);
			return true;
		}

		bool CMemo::NotifyOnLeftMouseButtonUp(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			if (ProcessMouseUp(x, y, ctrl, shift))
				Repaint(false);
			CControl::NotifyOnLeftMouseButtonUp(x, y, ctrl, left, middle, right, shift);
			return true;
		}

		bool CMemo::NotifyOnLeftMouseButtonDoubleClick(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			if (ProcessMouseUp(x, y, ctrl, shift) || (m_eHoveredElement == elText && m_pText->ProcessMouseDoubleClick(x, y)))
			{
				m_pText->UpdateCaret();
				Repaint(false);
			}
			CControl::NotifyOnLeftMouseButtonDoubleClick(x, y, ctrl, left, middle, right, shift);
			return true;
		}

		bool CMemo::NotifyOnRightMouseButtonDown(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			if (ProcessMouseUp(x, y, ctrl, shift))
				Repaint(false);
			return CControl::NotifyOnRightMouseButtonDown(x, y, ctrl, left, middle, right, shift);
		}

		bool CMemo::NotifyOnRightMouseButtonUp(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			if (ProcessMouseUp(x, y, ctrl, shift))
				Repaint(false);
			CControl::NotifyOnRightMouseButtonUp(x, y, ctrl, left, middle, right, shift);
			return true;
		}

		bool CMemo::NotifyOnRightMouseButtonDoubleClick(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			if (ProcessMouseUp(x, y, ctrl, shift))
				Repaint(false);
			CControl::NotifyOnRightMouseButtonDoubleClick(x, y, ctrl, left, middle, right, shift);
			return true;
		}

		bool CMemo::NotifyOnMiddleMouseButtonDown(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			if (ProcessMouseUp(x, y, ctrl, shift))
				Repaint(false);
			return CControl::NotifyOnMiddleMouseButtonDown(x, y, ctrl, left, middle, right, shift);
		}

		bool CMemo::NotifyOnMiddleMouseButtonUp(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			if (ProcessMouseUp(x, y, ctrl, shift))
				Repaint(false);
			CControl::NotifyOnMiddleMouseButtonUp(x, y, ctrl, left, middle, right, shift);
			return true;
		}

		bool CMemo::NotifyOnMiddleMouseButtonDoubleClick(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			if (ProcessMouseUp(x, y, ctrl, shift))
				Repaint(false);
			CControl::NotifyOnMiddleMouseButtonDoubleClick(x, y, ctrl, left, middle, right, shift);
			return true;
		}

		bool CMemo::NotifyOnMouseVerticalWheel(const int x, const int y, const int delta, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			if (m_bEnabled)
			{
				bool changed{ false };
				switch (m_eHoveredElement)
				{
				case elVScroll:
					if (m_pVerticalScrollBar->ProcessMouseWheel(x, y, delta))
					{
						changed = true;
						m_pText->setVerticalScroll((size_t)m_pVerticalScrollBar->getScroll());
					}
					break;
				case elHScroll:
					if (m_pHorizontalScrollBar->ProcessMouseWheel(x, y, delta))
					{
						changed = true;
						m_pText->setHorizontalScroll((size_t)m_pHorizontalScrollBar->getScroll());
					}
					break;
				case elText:
				case elControl:
					if (m_pText->ProcessMouseVerticalWheel(x, y, delta))
					{
						changed = true;
						if (m_pVerticalScrollBar->getEnabled())
							m_pVerticalScrollBar->setScroll(m_pText->getVerticalScroll());
					}
					break;
				}
				if (changed)
				{
					m_pText->UpdateCaret();
					Repaint(false);
				}
			}
			return CControl::NotifyOnMouseVerticalWheel(x, y, delta, ctrl, left, middle, right, shift);
		}

		bool CMemo::NotifyOnMouseHorizontalWheel(const int x, const int y, const int delta, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			if (m_bEnabled)
			{
				bool changed{ false };
				switch (m_eHoveredElement)
				{
				case elHScroll:
					if (m_pHorizontalScrollBar->ProcessMouseWheel(x, y, delta))
					{
						changed = true;
						m_pText->setHorizontalScroll((size_t)m_pHorizontalScrollBar->getScroll());
					}
					break;
				case elText:
				case elControl:
					if (m_pText->ProcessMouseHorizontalWheel(x, y, delta))
					{
						changed = true;
						if (m_pHorizontalScrollBar->getEnabled())
							m_pHorizontalScrollBar->setScroll(m_pText->getHorizontalScroll());
					}
					break;
				}
				if (changed)
				{
					m_pText->UpdateCaret();
					Repaint(false);
				}
			}
			return CControl::NotifyOnMouseHorizontalWheel(x, y, delta, ctrl, left, middle, right, shift);
		}

		void CMemo::NotifyOnMouseHover()
		{
			int x, y;
			if (m_bEnabled && m_pForm->getWindow()->getCursorPosition(x, y) && UpdateHoveredElement(x, y))
				Repaint(false);
			CControl::NotifyOnMouseHover();
		}

		void CMemo::NotifyOnMouseLeave()
		{
			if (m_bEnabled)
			{
				bool changed{ false };
				switch (m_eHoveredElement)
				{
				case elVScroll:
					changed = m_pVerticalScrollBar->ProcessMouseLeave();
					break;
				case elHScroll:
					changed = m_pHorizontalScrollBar->ProcessMouseLeave();
					break;
				case elText:
					changed = m_pText->ProcessMouseLeave();
					break;
				}
				m_eHoveredElement = elNone;
				if (changed)
					Repaint(false);
			}
			CControl::NotifyOnMouseLeave();
		}

		void CMemo::NotifyOnKillFocus()
		{
			m_pText->ProcessKillFocus();
			Repaint(false);
			CControl::NotifyOnKillFocus();
		}

		void CMemo::NotifyOnSetFocus(CControl *old)
		{
			m_pText->ProcessSetFocus();
			m_pText->UpdateCaret();
			Repaint(false);
			CControl::NotifyOnSetFocus(old);
		}

		void CMemo::NotifyOnResetFocus()
		{
			m_pText->ProcessSetFocus();
			m_pText->UpdateCaret();
			Repaint(false);
			CControl::NotifyOnResetFocus();
		}

		void CMemo::NotifyOnKillCaptureMouse()
		{
			m_pForm->getWindow()->ReleaseMouseCapture();
			CControl::NotifyOnKillCaptureMouse();
		}

		void CMemo::NotifyOnSetCaptureMouse()
		{
			m_pForm->getWindow()->CaptureMouse();
			CControl::NotifyOnSetCaptureMouse();
		}

		void CMemo::NotifyOnPaint(APP_RECT clip)
		{
			clip *= getVisibleRect();
			if (!clip.IsEmpty())
			{
				PaintBackground(clip);
				m_pVerticalScrollBar->Paint(clip);
				m_pHorizontalScrollBar->Paint(clip);
				m_pText->Paint(clip);
			}
			CControl::NotifyOnPaint(clip);
		}

		void CMemo::NotifyOnScrollBarChange(CMemoScrollBar *scrollbar)
		{
			bool changed;
			if (scrollbar == m_pVerticalScrollBar)
				changed = m_pText->setVerticalScroll((size_t)scrollbar->getScroll());
			else
				changed = m_pText->setHorizontalScroll((size_t)scrollbar->getScroll());
			if (changed)
			{
				m_pText->UpdateCaret();
				Repaint(false);
			}
		}

		void CMemo::NotifyOnTextChange()
		{
			m_pVerticalScrollBar->setScroll(m_pText->getVerticalScroll());
			m_pHorizontalScrollBar->setScroll(m_pText->getHorizontalScroll());
			m_pText->UpdateCaret();
			Repaint(false);
		}
	#pragma endregion

	#pragma region Helpers
		void CMemo::CalculateScrollBarsVisibility(bool &vscroll, bool &hscroll)
		{
			APP_RECT client = getClientRect();
			switch (m_eVerticalScrollBarVisibility)
			{
			case sbvNone:
				vscroll = false;
				break;
			case sbvVisible:
				vscroll = true;
				break;
			default:
				switch (m_eHorizontalScrollBarVisibility)
				{
				case sbvNone:
					vscroll = m_pText->getVerticalScrollRequired(
						std::max(0, client.Width() - (int)m_sTextPadding.Left - (int)m_sTextPadding.Right),
						std::max(0, client.Height() - (int)m_sTextPadding.Top - (int)m_sTextPadding.Bottom));
					break;
				case sbvVisible:
					vscroll = m_pText->getVerticalScrollRequired(
						std::max(0, client.Width() - (int)m_sTextPadding.Left - (int)m_sTextPadding.Right),
						std::max(0, client.Height() - (int)m_iScrollBarSize - (int)m_sTextPadding.Top - (int)m_sTextPadding.Bottom));
					break;
				default:
					if (m_pText->getVerticalScrollRequired(
						std::max(0, client.Width() - (int)m_sTextPadding.Left - (int)m_sTextPadding.Right),
						std::max(0, client.Height() - (int)m_sTextPadding.Top - (int)m_sTextPadding.Bottom)))
						vscroll = true;
					else if (m_pText->getVerticalScrollRequired(
						std::max(0, client.Width() - (int)m_sTextPadding.Left - (int)m_sTextPadding.Right),
						std::max(0, client.Height() - (int)m_iScrollBarSize - (int)m_sTextPadding.Top - (int)m_sTextPadding.Bottom)))
						if (m_pText->getHorizontalScrollRequired(std::max(0, client.Width() - (int)m_sTextPadding.Left - (int)m_sTextPadding.Right)))
							vscroll = true;
						else if (m_pText->getHorizontalScrollRequired(std::max(0, client.Width() - (int)m_iScrollBarSize - (int)m_sTextPadding.Left - (int)m_sTextPadding.Right)))
							vscroll = true;
						else
							vscroll = false;
					else
						vscroll = false;
					break;
				}
				break;
			}
			if (vscroll)
				client.Right = std::max(client.Left, client.Right - (int)m_iScrollBarSize);
			switch (m_eHorizontalScrollBarVisibility)
			{
			case sbvNone:
				hscroll = false;
				break;
			case sbvVisible:
				hscroll = true;
				break;
			default:
				hscroll = m_pText->getHorizontalScrollRequired(std::max(0, client.Width() - (int)m_sTextPadding.Left - (int)m_sTextPadding.Right));
				break;
			}
		}

		void CMemo::Update()
		{
			bool vscroll, hscroll;
			CalculateScrollBarsVisibility(vscroll, hscroll);
			APP_RECT client = getClientRect();
			client.Left -= getRect().Left;
			client.Right -= getRect().Left;
			client.Top -= getRect().Top;
			client.Bottom -= getRect().Top;
			m_pVerticalScrollBar->setVisible(vscroll);
			if (vscroll)
				client.Right -= (int)m_iScrollBarSize;
			m_pHorizontalScrollBar->setVisible(hscroll);
			if (hscroll)
				client.Bottom -= (int)m_iScrollBarSize;
			if (!client.IsValid())
			{
				client.Right = client.Left;
				client.Bottom = client.Top;
			}
			APP_RECT text_client = client;
			text_client.Left += m_sTextPadding.Left;
			text_client.Top += m_sTextPadding.Top;
			text_client.Right -= (int)m_sTextPadding.Right;
			text_client.Bottom -= (int)m_sTextPadding.Bottom;
			if (!text_client.IsValid())
			{
				text_client.Right = text_client.Left;
				text_client.Bottom = text_client.Top;
			}
			bool changed{ false };
			changed = m_pText->setMaxWidth(m_eHorizontalScrollBarVisibility == sbvNone ? text_client.Width() : 0) || changed;
			changed = m_pText->setRect(text_client) || changed;
			if (changed)
				m_pText->Update();
			// Setup scrollbars enable, range and page size, delta
			if ((int)m_pText->getTextSize().X > text_client.Width())
			{
				m_pHorizontalScrollBar->setEnabled(true);
				m_pHorizontalScrollBar->setMax((int)m_pText->getTextSize().X - text_client.Width());
				m_pHorizontalScrollBar->setPageSize((size_t)((double)client.Width() / (double)m_pText->getTextSize().X * ((double)m_pText->getTextSize().X - (double)text_client.Width())));
				m_pHorizontalScrollBar->setDeltaWheel(m_pText->getLineHeight());
			}
			else
				m_pHorizontalScrollBar->setEnabled(false);
			if ((int)m_pText->getTextSize().Y > text_client.Height())
			{
				m_pVerticalScrollBar->setEnabled(true);
				m_pVerticalScrollBar->setMax((int)m_pText->getTextSize().Y - text_client.Height());
				m_pVerticalScrollBar->setPageSize((size_t)((double)client.Height() / (double)m_pText->getTextSize().Y * ((double)m_pText->getTextSize().Y - (double)text_client.Height())));
				m_pVerticalScrollBar->setDeltaWheel(m_pText->getLineHeight());
			}
			else
				m_pVerticalScrollBar->setEnabled(false);
			// Setup scrollbars positions and sizes
			if (m_pHorizontalScrollBar->getVisible())
				m_pHorizontalScrollBar->setRect({ client.Left, client.Bottom, client.Right, client.Bottom + (int)m_iScrollBarSize });
			if (m_pVerticalScrollBar->getVisible())
				m_pVerticalScrollBar->setRect({ client.Right, client.Top, client.Right + (int)m_iScrollBarSize, client.Bottom });
			// Update hovered element
			int x, y;
			if (m_pForm->getWindow()->getCursorPosition(x, y))
				UpdateHoveredElement(x, y);
		}

		void CMemo::UpdateAll()
		{
			Update();
			m_pVerticalScrollBar->setScroll(m_pText->getVerticalScroll());
			m_pHorizontalScrollBar->setScroll(m_pText->getHorizontalScroll());
			m_pText->UpdateCaret();
			Repaint(false);
		}

		bool CMemo::UpdateHoveredElement(const int x, const int y)
		{
			APP_RECT r = ClientToForm(getRect());
			ELEMENT element{ elNone };
			if (x >= r.Left && x < r.Right && y >= r.Top && y < r.Bottom)
			{
				APP_RECT client = ClientToForm(getClientRect());
				if (m_pVerticalScrollBar->getVisible())
				{
					APP_RECT rect = m_pVerticalScrollBar->ClientToForm(m_pVerticalScrollBar->getRect()) * client;
					if (x >= rect.Left && x < rect.Right && y >= rect.Top && y < rect.Bottom)
						element = elVScroll;
				}
				if (element == elNone && m_pHorizontalScrollBar->getVisible())
				{
					APP_RECT rect = m_pHorizontalScrollBar->ClientToForm(m_pHorizontalScrollBar->getRect()) * client;
					if (x >= rect.Left && x < rect.Right && y >= rect.Top && y < rect.Bottom)
						element = elHScroll;
				}
				if (element == elNone)
				{
					APP_RECT rect = m_pText->ClientToForm(m_pText->getRect()) * client;
					if (x >= rect.Left && x < rect.Right && y >= rect.Top && y < rect.Bottom)
						element = elText;
				}
				if (element == elNone)
					element = elControl;
			}
			if (element == m_eHoveredElement)
				return false;
			switch (m_eHoveredElement)
			{
			case elVScroll:
				m_pVerticalScrollBar->ProcessMouseLeave();
				break;
			case elHScroll:
				m_pHorizontalScrollBar->ProcessMouseLeave();
				break;
			case elText:
				m_pText->ProcessMouseLeave();
				break;
			}
			m_eHoveredElement = element;
			switch (m_eHoveredElement)
			{
			case elVScroll:
				m_pVerticalScrollBar->ProcessMouseHover(x, y);
				break;
			case elHScroll:
				m_pHorizontalScrollBar->ProcessMouseHover(x, y);
				break;
			case elText:
				m_pText->ProcessMouseHover(x, y);
				break;
			}
			return true;
		}

		bool CMemo::UpdateFromStyle()
		{
			if (!getStyle())
				return false;
			m_pVerticalScrollBar->UpdateFromStyle();
			m_pHorizontalScrollBar->UpdateFromStyle();
			m_pText->UpdateFromStyle();

			return true;
		}
	#pragma endregion

	#pragma region Process events
		bool CMemo::ProcessMouseDown(const int x, const int y, const bool ctrl, const bool alt, const bool shift)
		{
			bool result{ false };
			switch (m_eHoveredElement)
			{
			case elVScroll:
				if (result = m_pVerticalScrollBar->ProcessMouseDown(x, y))
					m_pText->setVerticalScroll(m_pVerticalScrollBar->getScroll());
				break;
			case elHScroll:
				if (result = m_pHorizontalScrollBar->ProcessMouseDown(x, y))
					m_pText->setHorizontalScroll(m_pHorizontalScrollBar->getScroll());
				break;
			case elText:
				result = m_pText->ProcessMouseDown(x, y, ctrl, alt, shift);
				break;
			}
			if (result)
			{
				m_eMouseDownElement = m_eHoveredElement;
				m_pText->UpdateCaret();
				m_pForm->CaptureMouse(this);
			}
			return result;
		}

		bool CMemo::ProcessMouseUp(const int x, const int y, const bool ctrl, const bool shift)
		{
			bool result{ false };
			switch (m_eMouseDownElement)
			{
			case elVScroll:
				if (m_pVerticalScrollBar->ProcessMouseUp())
					result = true;
				break;
			case elHScroll:
				if (m_pHorizontalScrollBar->ProcessMouseUp())
					result = true;
				break;
			case elText:
				if (m_pText->ProcessMouseUp(x, y, ctrl, shift))
				{
					m_pText->UpdateCaret();
					result = true;
				}
				break;
			}
			m_eMouseDownElement = elNone;
			if (m_pForm->getCaptureMouseControl() == this)
			{
				result = true;
				m_pForm->ReleaseCaptureMouse();
			}
			return result;
		}
	#pragma endregion

	#pragma region Paint
		void CMemo::PaintBackground(APP_RECT clip)
		{
			STATE state{ getState() };
			APP_RECT rect = ClientToForm(getRect());
			// Box shadow
			if (m_aStyle[state].BoxShadow)
				m_pForm->getPresenter()->BoxBlur(m_aStyle[state].BoxShadowColor, m_aStyle[state].BoxShadowShift.X, m_aStyle[state].BoxShadowShift.Y, m_aStyle[state].BoxShadowRadius,
					clip, rect, m_sBorderRadius, m_iBorderAntiAliazing, nullptr, nullptr, true);
			// Gradient
			if (m_aStyle[state].GradientPointCount > 0)
			{
				// Borders
				if (m_sBorderWidth[0] != 0 && m_aStyle[state].BorderColor[0].getAlpha() > 0)
					m_pForm->getPresenter()->RenderBorder(graphics::bplLeft, m_aStyle[state].BorderColor[0], clip, rect, m_sBorderWidth, m_sBorderRadius, m_iBorderAntiAliazing, nullptr, nullptr, true);
				if (m_sBorderWidth[1] != 0 && m_aStyle[state].BorderColor[1].getAlpha() > 0)
					m_pForm->getPresenter()->RenderBorder(graphics::bplTop, m_aStyle[state].BorderColor[1], clip, rect, m_sBorderWidth, m_sBorderRadius, m_iBorderAntiAliazing, nullptr, nullptr, true);
				if (m_sBorderWidth[2] != 0 && m_aStyle[state].BorderColor[2].getAlpha() > 0)
					m_pForm->getPresenter()->RenderBorder(graphics::bplRight, m_aStyle[state].BorderColor[2], clip, rect, m_sBorderWidth, m_sBorderRadius, m_iBorderAntiAliazing, nullptr, nullptr, true);
				if (m_sBorderWidth[3] != 0 && m_aStyle[state].BorderColor[3].getAlpha() > 0)
					m_pForm->getPresenter()->RenderBorder(graphics::bplBottom, m_aStyle[state].BorderColor[3], clip, rect, m_sBorderWidth, m_sBorderRadius, m_iBorderAntiAliazing, nullptr, nullptr, true);
				m_aStyle[state].SortGradientPoints();
				m_pForm->getPresenter()->RenderGradient(m_aStyle[state].GradientType, m_aStyle[state].GradientPointCount, m_aStyle[state].GradientPoints, graphics::bplInside, clip, rect, rect,
					m_sBorderWidth, m_sBorderRadius, m_iBorderAntiAliazing, nullptr, nullptr, true);
			}
			else
			{
				// Background color
				APP_COLOR colors[graphics::bplBottom + 1];
				colors[graphics::bplOutside] = { 0, 0, 0, 0 };
				colors[graphics::bplInside] = m_aStyle[state].BackgroundColor;
				colors[graphics::bplLeft] = m_aStyle[state].BorderColor[0];
				colors[graphics::bplTop] = m_aStyle[state].BorderColor[1];
				colors[graphics::bplRight] = m_aStyle[state].BorderColor[2];
				colors[graphics::bplBottom] = m_aStyle[state].BorderColor[3];
				m_pForm->getPresenter()->MultiFillRect(colors, clip, rect, m_sBorderWidth, m_sBorderRadius, m_iBorderAntiAliazing, nullptr, nullptr, true);
			}
		}
	#pragma endregion

	#pragma region Text getters
		size_t CMemo::getLineHeight()
		{
			return m_pText->getLineHeight();
		}

		math::POINT<size_t> CMemo::getLineMargin() const
		{
			return m_pText->getLineMargin();
		}

		size_t CMemo::getLineMarginTop() const
		{
			return m_pText->getLineMarginTop();
		}

		size_t CMemo::getLineMarginBottom() const
		{
			return m_pText->getLineMarginBottom();
		}

		const String &CMemo::getText() const
		{
			return m_pText->getText();
		}

		APP_COLOR CMemo::getTextColor(const CBaseText::STATE state) const
		{
			return m_pText->getTextColor(state);
		}

		APP_COLOR CMemo::getShadowColor(const CBaseText::STATE state) const
		{
			return m_pText->getShadowColor(state);
		}

		APP_COLOR CMemo::getSelectionBackgroundColor(const CBaseText::STATE state) const
		{
			return m_pText->getSelectionBackgroundColor(state);
		}

		APP_COLOR CMemo::getSelectionTextColor(const CBaseText::STATE state) const
		{
			return m_pText->getSelectionTextColor(state);
		}

		APP_COLOR CMemo::getSelectionShadowColor(const CBaseText::STATE state) const
		{
			return m_pText->getSelectionShadowColor(state);
		}

		size_t CMemo::getMaxLength() const
		{
			return m_pText->getMaxLength();
		}

		bool CMemo::getReadOnly() const
		{
			return m_pText->getReadOnly();
		}

		bool CMemo::getInserting() const
		{
			return m_pText->getInserting();
		}

		math::POINT<size_t> CMemo::getSelection() const
		{
			return m_pText->getSelection();
		}

		size_t CMemo::getCaretPosition() const
		{
			return m_pText->getCaretPosition();
		}

		size_t CMemo::getDeltaWheelVertical() const
		{
			return m_pText->getDeltaWheelVertical();
		}

		size_t CMemo::getDeltaWheelHorizontal() const
		{
			return m_pText->getDeltaWheelHorizontal();
		}

		size_t CMemo::getHistoryLimitCount() const
		{
			return m_pText->getHistoryLimitCount();
		}

		size_t CMemo::getHistoryLimitSize() const
		{
			return m_pText->getHistoryLimitSize();
		}
	#pragma endregion

	#pragma region Text setters
		CMemo *CMemo::setLineMargin(const math::POINT<size_t> &value)
		{
			if (m_pText->setLineMargin(value))
				UpdateAll();
			return this;
		}

		CMemo *CMemo::setLineMarginTop(const size_t value)
		{
			if (m_pText->setLineMarginTop(value))
				UpdateAll();
			return this;
		}

		CMemo *CMemo::setLineMarginBottom(const size_t value)
		{
			if (m_pText->setLineMarginBottom(value))
				UpdateAll();
			return this;
		}

		CMemo *CMemo::setText(const String &value)
		{
			if (m_pText->setText(value))
				UpdateAll();
			return this;
		}

		CMemo *CMemo::setTextColor(const CBaseText::STATE state, const APP_COLOR &value)
		{
			if (m_pText->setTextColor(state, value))
				Repaint(false);
			return this;
		}

		CMemo *CMemo::setShadowColor(const CBaseText::STATE state, const APP_COLOR &value)
		{
			if (m_pText->setShadowColor(state, value))
				Repaint(false);
			return this;
		}

		CMemo *CMemo::setSelectionBackgroundColor(const CBaseText::STATE state, const APP_COLOR &value)
		{
			if (m_pText->setSelectionBackgroundColor(state, value))
				Repaint(false);
			return this;
		}

		CMemo *CMemo::setSelectionTextColor(const CBaseText::STATE state, const APP_COLOR &value)
		{
			if (m_pText->setSelectionTextColor(state, value))
				Repaint(false);
			return this;
		}

		CMemo *CMemo::setSelectionShadowColor(const CBaseText::STATE state, const APP_COLOR &value)
		{
			if (m_pText->setSelectionShadowColor(state, value))
				Repaint(false);
			return this;
		}

		CMemo *CMemo::setMaxLength(const size_t value)
		{
			if (m_pText->setMaxLength(value))
				UpdateAll();
			return this;
		}

		CMemo *CMemo::setReadOnly(const bool value)
		{
			m_pText->setReadOnly(value);
			return this;
		}

		CMemo *CMemo::setInserting(const bool value)
		{
			if (m_pText->setInserting(value))
				m_pText->UpdateCaret();
			return this;
		}

		CMemo *CMemo::setSelection(const math::POINT<size_t> &value)
		{
			if (m_pText->setSelection(value))
				Repaint(false);
			return this;
		}

		CMemo *CMemo::setCaretPosition(const size_t value)
		{
			if (m_pText->setCaretPosition(value))
				m_pText->UpdateCaret();
			return this;
		}

		CMemo *CMemo::setDeltaWheelVertical(const size_t value)
		{
			m_pText->setDeltaWheelVertical(value);
			return this;
		}

		CMemo *CMemo::setDeltaWheelHorizontal(const size_t value)
		{
			m_pText->setDeltaWheelHorizontal(value);
			return this;
		}

		CMemo *CMemo::setHistoryLimitCount(const size_t value)
		{
			m_pText->setHistoryLimitCount(value);
			return this;
		}

		CMemo *CMemo::setHistoryLimitSize(const size_t value)
		{
			m_pText->setHistoryLimitSize(value);
			return this;
		}
	#pragma endregion

	#pragma region Text helpers
		CMemo *CMemo::ScrollToCaret()
		{
			if (m_pText->ScrollToCaret())
			{
				m_pVerticalScrollBar->setScroll(m_pText->getVerticalScroll());
				m_pHorizontalScrollBar->setScroll(m_pText->getHorizontalScroll());
				m_pText->UpdateCaret();
				Repaint(false);
			}
			return this;
		}

		bool CMemo::CanUndo()
		{
			return m_pText->CanUndo();
		}

		bool CMemo::CanRedo()
		{
			return m_pText->CanRedo();
		}

		CMemo *CMemo::Undo()
		{
			if (m_pText->Undo())
				UpdateAll();
			return this;
		}

		CMemo *CMemo::Redo()
		{
			if (m_pText->Redo())
				UpdateAll();
			return this;
		}

		CMemo *CMemo::ScrollLineUp()
		{
			if (m_pText->ScrollLineUp())
			{
				m_pText->ScrollToCaret();
				m_pVerticalScrollBar->setScroll(m_pText->getVerticalScroll());
				m_pHorizontalScrollBar->setScroll(m_pText->getHorizontalScroll());
				m_pText->UpdateCaret();
				Repaint(false);
			}
			return this;
		}

		CMemo *CMemo::MoveCaretLineUpAndSelect()
		{
			if (m_pText->MoveCaretLineUpAndSelect())
			{
				m_pText->ScrollToCaret();
				m_pVerticalScrollBar->setScroll(m_pText->getVerticalScroll());
				m_pHorizontalScrollBar->setScroll(m_pText->getHorizontalScroll());
				m_pText->UpdateCaret();
				Repaint(false);
			}
			return this;
		}

		CMemo *CMemo::MoveCaretLineUp()
		{
			if (m_pText->MoveCaretLineUp())
			{
				m_pText->ScrollToCaret();
				m_pVerticalScrollBar->setScroll(m_pText->getVerticalScroll());
				m_pHorizontalScrollBar->setScroll(m_pText->getHorizontalScroll());
				m_pText->UpdateCaret();
				Repaint(false);
			}
			return this;
		}

		CMemo *CMemo::ScrollLineDown()
		{
			if (m_pText->ScrollLineDown())
			{
				m_pText->ScrollToCaret();
				m_pVerticalScrollBar->setScroll(m_pText->getVerticalScroll());
				m_pHorizontalScrollBar->setScroll(m_pText->getHorizontalScroll());
				m_pText->UpdateCaret();
				Repaint(false);
			}
			return this;
		}

		CMemo *CMemo::MoveCaretLineDownAndSelect()
		{
			if (m_pText->MoveCaretLineDownAndSelect())
			{
				m_pText->ScrollToCaret();
				m_pVerticalScrollBar->setScroll(m_pText->getVerticalScroll());
				m_pHorizontalScrollBar->setScroll(m_pText->getHorizontalScroll());
				m_pText->UpdateCaret();
				Repaint(false);
			}
			return this;
		}

		CMemo *CMemo::MoveCaretLineDown()
		{
			if (m_pText->MoveCaretLineDown())
			{
				m_pText->ScrollToCaret();
				m_pVerticalScrollBar->setScroll(m_pText->getVerticalScroll());
				m_pHorizontalScrollBar->setScroll(m_pText->getHorizontalScroll());
				m_pText->UpdateCaret();
				Repaint(false);
			}
			return this;
		}

		CMemo *CMemo::MoveCaretWordStartAndSelect()
		{
			if (m_pText->MoveCaretWordStartAndSelect())
			{
				m_pText->ScrollToCaret();
				m_pVerticalScrollBar->setScroll(m_pText->getVerticalScroll());
				m_pHorizontalScrollBar->setScroll(m_pText->getHorizontalScroll());
				m_pText->UpdateCaret();
				Repaint(false);
			}
			return this;
		}

		CMemo *CMemo::MoveCaretWordStart()
		{
			if (m_pText->MoveCaretWordStart())
			{
				m_pText->ScrollToCaret();
				m_pVerticalScrollBar->setScroll(m_pText->getVerticalScroll());
				m_pHorizontalScrollBar->setScroll(m_pText->getHorizontalScroll());
				m_pText->UpdateCaret();
				Repaint(false);
			}
			return this;
		}

		CMemo *CMemo::MoveCaretLeftAndSelect()
		{
			if (m_pText->MoveCaretLeftAndSelect())
			{
				m_pText->ScrollToCaret();
				m_pVerticalScrollBar->setScroll(m_pText->getVerticalScroll());
				m_pHorizontalScrollBar->setScroll(m_pText->getHorizontalScroll());
				m_pText->UpdateCaret();
				Repaint(false);
			}
			return this;
		}

		CMemo *CMemo::MoveCaretLeft()
		{
			if (m_pText->MoveCaretLeft())
			{
				m_pText->ScrollToCaret();
				m_pVerticalScrollBar->setScroll(m_pText->getVerticalScroll());
				m_pHorizontalScrollBar->setScroll(m_pText->getHorizontalScroll());
				m_pText->UpdateCaret();
				Repaint(false);
			}
			return this;
		}

		CMemo *CMemo::MoveCaretWordEndAndSelect()
		{
			if (m_pText->MoveCaretWordEndAndSelect())
			{
				m_pText->ScrollToCaret();
				m_pVerticalScrollBar->setScroll(m_pText->getVerticalScroll());
				m_pHorizontalScrollBar->setScroll(m_pText->getHorizontalScroll());
				m_pText->UpdateCaret();
				Repaint(false);
			}
			return this;
		}

		CMemo *CMemo::MoveCaretWordEnd()
		{
			if (m_pText->MoveCaretWordEnd())
			{
				m_pText->ScrollToCaret();
				m_pVerticalScrollBar->setScroll(m_pText->getVerticalScroll());
				m_pHorizontalScrollBar->setScroll(m_pText->getHorizontalScroll());
				m_pText->UpdateCaret();
				Repaint(false);
			}
			return this;
		}

		CMemo *CMemo::MoveCaretRightAndSelect()
		{
			if (m_pText->MoveCaretRightAndSelect())
			{
				m_pText->ScrollToCaret();
				m_pVerticalScrollBar->setScroll(m_pText->getVerticalScroll());
				m_pHorizontalScrollBar->setScroll(m_pText->getHorizontalScroll());
				m_pText->UpdateCaret();
				Repaint(false);
			}
			return this;
		}

		CMemo *CMemo::MoveCaretRight()
		{
			if (m_pText->MoveCaretRight())
			{
				m_pText->ScrollToCaret();
				m_pVerticalScrollBar->setScroll(m_pText->getVerticalScroll());
				m_pHorizontalScrollBar->setScroll(m_pText->getHorizontalScroll());
				m_pText->UpdateCaret();
				Repaint(false);
			}
			return this;
		}

		CMemo *CMemo::DeleteSelection()
		{
			if (m_pText->DeleteSelection())
				UpdateAll();
			return this;
		}

		CMemo *CMemo::DeleteLeft()
		{
			if (m_pText->DeleteLeft())
				UpdateAll();
			return this;
		}

		CMemo *CMemo::DeleteRight()
		{
			if (m_pText->DeleteRight())
				UpdateAll();
			return this;
		}

		CMemo *CMemo::MoveCaretTextStartAndSelect()
		{
			if (m_pText->MoveCaretTextStartAndSelect())
			{
				m_pText->ScrollToCaret();
				m_pVerticalScrollBar->setScroll(m_pText->getVerticalScroll());
				m_pHorizontalScrollBar->setScroll(m_pText->getHorizontalScroll());
				m_pText->UpdateCaret();
				Repaint(false);
			}
			return this;
		}

		CMemo *CMemo::MoveCaretTextStart()
		{
			if (m_pText->MoveCaretTextStart())
			{
				m_pText->ScrollToCaret();
				m_pVerticalScrollBar->setScroll(m_pText->getVerticalScroll());
				m_pHorizontalScrollBar->setScroll(m_pText->getHorizontalScroll());
				m_pText->UpdateCaret();
				Repaint(false);
			}
			return this;
		}

		CMemo *CMemo::MoveCaretLineStartAndSelect()
		{
			if (m_pText->MoveCaretLineStartAndSelect())
			{
				m_pText->ScrollToCaret();
				m_pVerticalScrollBar->setScroll(m_pText->getVerticalScroll());
				m_pHorizontalScrollBar->setScroll(m_pText->getHorizontalScroll());
				m_pText->UpdateCaret();
				Repaint(false);
			}
			return this;
		}

		CMemo *CMemo::MoveCaretLineStart()
		{
			if (m_pText->MoveCaretLineStart())
			{
				m_pText->ScrollToCaret();
				m_pVerticalScrollBar->setScroll(m_pText->getVerticalScroll());
				m_pHorizontalScrollBar->setScroll(m_pText->getHorizontalScroll());
				m_pText->UpdateCaret();
				Repaint(false);
			}
			return this;
		}

		CMemo *CMemo::MoveCaretTextEndAndSelect()
		{
			if (m_pText->MoveCaretTextEndAndSelect())
			{
				m_pText->ScrollToCaret();
				m_pVerticalScrollBar->setScroll(m_pText->getVerticalScroll());
				m_pHorizontalScrollBar->setScroll(m_pText->getHorizontalScroll());
				m_pText->UpdateCaret();
				Repaint(false);
			}
			return this;
		}

		CMemo *CMemo::MoveCaretTextEnd()
		{
			if (m_pText->MoveCaretTextEnd())
			{
				m_pText->ScrollToCaret();
				m_pVerticalScrollBar->setScroll(m_pText->getVerticalScroll());
				m_pHorizontalScrollBar->setScroll(m_pText->getHorizontalScroll());
				m_pText->UpdateCaret();
				Repaint(false);
			}
			return this;
		}

		CMemo *CMemo::MoveCaretLineEndAndSelect()
		{
			if (m_pText->MoveCaretLineEndAndSelect())
			{
				m_pText->ScrollToCaret();
				m_pVerticalScrollBar->setScroll(m_pText->getVerticalScroll());
				m_pHorizontalScrollBar->setScroll(m_pText->getHorizontalScroll());
				m_pText->UpdateCaret();
				Repaint(false);
			}
			return this;
		}

		CMemo *CMemo::MoveCaretLineEnd()
		{
			if (m_pText->MoveCaretLineEnd())
			{
				m_pText->ScrollToCaret();
				m_pVerticalScrollBar->setScroll(m_pText->getVerticalScroll());
				m_pHorizontalScrollBar->setScroll(m_pText->getHorizontalScroll());
				m_pText->UpdateCaret();
				Repaint(false);
			}
			return this;
		}

		CMemo *CMemo::MoveCaretPageStartAndSelect()
		{
			if (m_pText->MoveCaretPageStartAndSelect())
			{
				m_pText->ScrollToCaret();
				m_pVerticalScrollBar->setScroll(m_pText->getVerticalScroll());
				m_pHorizontalScrollBar->setScroll(m_pText->getHorizontalScroll());
				m_pText->UpdateCaret();
				Repaint(false);
			}
			return this;
		}

		CMemo *CMemo::MoveCaretPageStart()
		{
			if (m_pText->MoveCaretPageStart())
			{
				m_pText->ScrollToCaret();
				m_pVerticalScrollBar->setScroll(m_pText->getVerticalScroll());
				m_pHorizontalScrollBar->setScroll(m_pText->getHorizontalScroll());
				m_pText->UpdateCaret();
				Repaint(false);
			}
			return this;
		}

		CMemo *CMemo::MoveCaretPageUpAndSelect()
		{
			if (m_pText->MoveCaretPageUpAndSelect())
			{
				m_pText->ScrollToCaret();
				m_pVerticalScrollBar->setScroll(m_pText->getVerticalScroll());
				m_pHorizontalScrollBar->setScroll(m_pText->getHorizontalScroll());
				m_pText->UpdateCaret();
				Repaint(false);
			}
			return this;
		}

		CMemo *CMemo::MoveCaretPageUp()
		{
			if (m_pText->MoveCaretPageUp())
			{
				m_pText->ScrollToCaret();
				m_pVerticalScrollBar->setScroll(m_pText->getVerticalScroll());
				m_pHorizontalScrollBar->setScroll(m_pText->getHorizontalScroll());
				m_pText->UpdateCaret();
				Repaint(false);
			}
			return this;
		}

		CMemo *CMemo::MoveCaretPageEndAndSelect()
		{
			if (m_pText->MoveCaretPageEndAndSelect())
			{
				m_pText->ScrollToCaret();
				m_pVerticalScrollBar->setScroll(m_pText->getVerticalScroll());
				m_pHorizontalScrollBar->setScroll(m_pText->getHorizontalScroll());
				m_pText->UpdateCaret();
				Repaint(false);
			}
			return this;
		}

		CMemo *CMemo::MoveCaretPageEnd()
		{
			if (m_pText->MoveCaretPageEnd())
			{
				m_pText->ScrollToCaret();
				m_pVerticalScrollBar->setScroll(m_pText->getVerticalScroll());
				m_pHorizontalScrollBar->setScroll(m_pText->getHorizontalScroll());
				m_pText->UpdateCaret();
				Repaint(false);
			}
			return this;
		}

		CMemo *CMemo::MoveCaretPageDownAndSelect()
		{
			if (m_pText->MoveCaretPageDownAndSelect())
			{
				m_pText->ScrollToCaret();
				m_pVerticalScrollBar->setScroll(m_pText->getVerticalScroll());
				m_pHorizontalScrollBar->setScroll(m_pText->getHorizontalScroll());
				m_pText->UpdateCaret();
				Repaint(false);
			}
			return this;
		}

		CMemo *CMemo::MoveCaretPageDown()
		{
			if (m_pText->MoveCaretPageDown())
			{
				m_pText->ScrollToCaret();
				m_pVerticalScrollBar->setScroll(m_pText->getVerticalScroll());
				m_pHorizontalScrollBar->setScroll(m_pText->getHorizontalScroll());
				m_pText->UpdateCaret();
				Repaint(false);
			}
			return this;
		}

		CMemo *CMemo::SelectAll()
		{
			if (m_pText->SelectAll())
				Repaint(false);
			return this;
		}

		CMemo *CMemo::Paste()
		{
			if (m_pText->Paste())
				UpdateAll();
			return this;
		}

		CMemo *CMemo::Copy()
		{
			m_pText->Copy();
			return this;
		}

		CMemo *CMemo::Cut()
		{
			if (m_pText->Cut())
				UpdateAll();
			return this;
		}

		CMemo *CMemo::ClearHistory()
		{
			m_pText->ClearHistory();
			return this;
		}
	#pragma endregion

	#pragma region Vertical scrollbar getters
		bool CMemo::getVerticalScrollBarEnabled() const
		{
			return m_pVerticalScrollBar->getEnabled();
		}

		bool CMemo::getVerticalScrollBarVisible() const
		{
			return m_pVerticalScrollBar->getVisible();
		}

		int CMemo::getVerticalScrollBarMax() const
		{
			return m_pVerticalScrollBar->getMax();
		}

		int CMemo::getVerticalScrollBarScroll() const
		{
			return m_pVerticalScrollBar->getScroll();
		}

		size_t CMemo::getVerticalScrollBarPageSize() const
		{
			return m_pVerticalScrollBar->getPageSize();
		}

		size_t CMemo::getVerticalScrollBarDeltaArrow() const
		{
			return m_pVerticalScrollBar->getDeltaArrow();
		}

		size_t CMemo::getVerticalScrollBarDeltaWheel() const
		{
			return m_pVerticalScrollBar->getDeltaWheel();
		}

		CBaseScrollBar::ELEMENT_STATE CMemo::getVerticalScrollBarElementState(const CBaseScrollBar::ELEMENT_TYPE type) const
		{
			return m_pVerticalScrollBar->getElementState(type);
		}

		size_t CMemo::getVerticalScrollBarScrollerSize() const
		{
			return m_pVerticalScrollBar->getScrollerSize();
		}

		size_t CMemo::getVerticalScrollBarBorderWidth() const
		{
			return m_pVerticalScrollBar->getBorderWidth();
		}

		bool CMemo::getVerticalScrollBarBoxShadow() const
		{
			return m_pVerticalScrollBar->getBoxShadow();
		}

		APP_POINT CMemo::getVerticalScrollBarBoxShadowShift() const
		{
			return m_pVerticalScrollBar->getBoxShadowShift();
		}

		int CMemo::getVerticalScrollBarBoxShadowShiftX() const
		{
			return m_pVerticalScrollBar->getBoxShadowShiftX();
		}

		int CMemo::getVerticalScrollBarBoxShadowShiftY() const
		{
			return m_pVerticalScrollBar->getBoxShadowShiftY();
		}

		size_t CMemo::getVerticalScrollBarBoxShadowRadius() const
		{
			return m_pVerticalScrollBar->getBoxShadowRadius();
		}

		APP_COLOR CMemo::getVerticalScrollBarBackgroundColor(const CBaseScrollBar::STATE state) const
		{
			return m_pVerticalScrollBar->getBackgroundColor(state);
		}

		APP_COLOR CMemo::getVerticalScrollBarBorderColor(const CBaseScrollBar::STATE state) const
		{
			return m_pVerticalScrollBar->getBorderColor(state);
		}

		APP_COLOR CMemo::getVerticalScrollBarBoxShadowColor(const CBaseScrollBar::STATE state) const
		{
			return m_pVerticalScrollBar->getBoxShadowColor(state);
		}

		IImage::GRADIENT_TYPE CMemo::getVerticalScrollBarGradientType(const CBaseScrollBar::STATE state) const
		{
			return m_pVerticalScrollBar->getGradientType(state);
		}

		size_t CMemo::getVerticalScrollBarGradientPointCount(const CBaseScrollBar::STATE state) const
		{
			return m_pVerticalScrollBar->getGradientPointCount(state);
		}

		double CMemo::getVerticalScrollBarGradientPointPosition(const CBaseScrollBar::STATE state, const size_t index) const
		{
			return m_pVerticalScrollBar->getGradientPointPosition(state, index);
		}

		APP_COLOR CMemo::getVerticalScrollBarGradientPointColor(const CBaseScrollBar::STATE state, const size_t index) const
		{
			return m_pVerticalScrollBar->getGradientPointColor(state, index);
		}

		size_t CMemo::getVerticalScrollBarElementBorderWidth(const CBaseScrollBar::ELEMENT_TYPE element) const
		{
			return m_pVerticalScrollBar->getElementBorderWidth(element);
		}

		size_t CMemo::getVerticalScrollBarElementBorderRadius(const CBaseScrollBar::ELEMENT_TYPE element) const
		{
			return m_pVerticalScrollBar->getElementBorderRadius(element);
		}

		size_t CMemo::getVerticalScrollBarElementBorderAntiAliazing(const CBaseScrollBar::ELEMENT_TYPE element) const
		{
			return m_pVerticalScrollBar->getElementBorderAntiAliazing(element);
		}

		APP_COLOR CMemo::getVerticalScrollBarElementBackgroundColor(const CBaseScrollBar::ELEMENT_TYPE element, const CBaseScrollBar::ELEMENT_STATE state) const
		{
			return m_pVerticalScrollBar->getElementBackgroundColor(element, state);
		}

		APP_COLOR CMemo::getVerticalScrollBarElementBorderColor(const CBaseScrollBar::ELEMENT_TYPE element, const CBaseScrollBar::ELEMENT_STATE state) const
		{
			return m_pVerticalScrollBar->getElementBorderColor(element, state);
		}

		IImage::GRADIENT_TYPE CMemo::getVerticalScrollBarElementGradientType(const CBaseScrollBar::ELEMENT_TYPE element, const CBaseScrollBar::ELEMENT_STATE state) const
		{
			return m_pVerticalScrollBar->getElementGradientType(element, state);
		}

		size_t CMemo::getVerticalScrollBarElementGradientPointCount(const CBaseScrollBar::ELEMENT_TYPE element, const CBaseScrollBar::ELEMENT_STATE state) const
		{
			return m_pVerticalScrollBar->getElementGradientPointCount(element, state);
		}

		double CMemo::getVerticalScrollBarElementGradientPointPosition(const CBaseScrollBar::ELEMENT_TYPE element, const CBaseScrollBar::ELEMENT_STATE state, const size_t index) const
		{
			return m_pVerticalScrollBar->getElementGradientPointPosition(element, state, index);
		}

		APP_COLOR CMemo::getVerticalScrollBarElementGradientPointColor(const CBaseScrollBar::ELEMENT_TYPE element, const CBaseScrollBar::ELEMENT_STATE state, const size_t index) const
		{
			return m_pVerticalScrollBar->getElementGradientPointColor(element, state, index);
		}

		bool CMemo::getVerticalScrollBarHovered() const
		{
			return m_pVerticalScrollBar->getHovered();
		}
	#pragma endregion

	#pragma region Vertical scrollbar setters
		CMemo *CMemo::setVerticalScrollBarScroll(const int value)
		{
			if (m_pVerticalScrollBar->setScroll(value))
			{
				m_pText->setVerticalScroll(m_pVerticalScrollBar->getScroll());
				m_pText->UpdateCaret();
				Repaint(false);
			}
			return this;
		}

		CMemo *CMemo::setVerticalScrollBarDeltaArrow(const size_t value)
		{
			m_pVerticalScrollBar->setDeltaArrow(value);
			return this;
		}

		CMemo *CMemo::setVerticalScrollBarDeltaWheel(const size_t value)
		{
			m_pVerticalScrollBar->setDeltaWheel(value);
			return this;
		}

		CMemo *CMemo::setVerticalScrollBarBorderWidth(const size_t value)
		{
			if (m_pVerticalScrollBar->setBorderWidth(value))
				UpdateAll();
			return this;
		}

		CMemo *CMemo::setVerticalScrollBarBoxShadow(const bool value)
		{
			if (m_pVerticalScrollBar->setBoxShadow(value))
				Repaint(false);
			return this;
		}

		CMemo *CMemo::setVerticalScrollBarBoxShadowShift(const APP_POINT &value)
		{
			if (m_pVerticalScrollBar->setBoxShadowShift(value))
				Repaint(false);
			return this;
		}

		CMemo *CMemo::setVerticalScrollBarBoxShadowShiftX(const int value)
		{
			if (m_pVerticalScrollBar->setBoxShadowShiftX(value))
				Repaint(false);
			return this;
		}

		CMemo *CMemo::setVerticalScrollBarBoxShadowShiftY(const int value)
		{
			if (m_pVerticalScrollBar->setBoxShadowShiftY(value))
				Repaint(false);
			return this;
		}

		CMemo *CMemo::setVerticalScrollBarBoxShadowRadius(const size_t value)
		{
			if (m_pVerticalScrollBar->setBoxShadowRadius(value))
				Repaint(false);
			return this;
		}

		CMemo *CMemo::setVerticalScrollBarBackgroundColor(const CBaseScrollBar::STATE state, const APP_COLOR &value)
		{
			if (m_pVerticalScrollBar->setBackgroundColor(state, value))
				Repaint(false);
			return this;
		}

		CMemo *CMemo::setVerticalScrollBarBorderColor(const CBaseScrollBar::STATE state, const APP_COLOR &value)
		{
			if (m_pVerticalScrollBar->setBorderColor(state, value))
				Repaint(false);
			return this;
		}

		CMemo *CMemo::setVerticalScrollBarBoxShadowColor(const CBaseScrollBar::STATE state, const APP_COLOR &value)
		{
			if (m_pVerticalScrollBar->setBoxShadowColor(state, value))
				Repaint(false);
			return this;
		}

		CMemo *CMemo::setVerticalScrollBarGradientType(const CBaseScrollBar::STATE state, const IImage::GRADIENT_TYPE value)
		{
			if (m_pVerticalScrollBar->setGradientType(state, value))
				Repaint(false);
			return this;
		}

		CMemo *CMemo::setVerticalScrollBarGradientPointCount(const CBaseScrollBar::STATE state, const size_t value)
		{
			if (m_pVerticalScrollBar->setGradientPointCount(state, value))
				Repaint(false);
			return this;
		}

		CMemo *CMemo::setVerticalScrollBarGradientPointPosition(const CBaseScrollBar::STATE state, const size_t index, const double value)
		{
			if (m_pVerticalScrollBar->setGradientPointPosition(state, index, value))
				Repaint(false);
			return this;
		}

		CMemo *CMemo::setVerticalScrollBarGradientPointColor(const CBaseScrollBar::STATE state, const size_t index, const APP_COLOR &value)
		{
			if (m_pVerticalScrollBar->setGradientPointColor(state, index, value))
				Repaint(false);
			return this;
		}

		CMemo *CMemo::setVerticalScrollBarGradientPoints(const CBaseScrollBar::STATE state, const size_t count, IImage::GRADIENT_POINT *points)
		{
			if (m_pVerticalScrollBar->setGradientPoints(state, count, points))
				Repaint(false);
			return this;
		}

		CMemo *CMemo::setVerticalScrollBarElementBorderWidth(const CBaseScrollBar::ELEMENT_TYPE element, const size_t value)
		{
			if (m_pVerticalScrollBar->setElementBorderWidth(element, value))
				Repaint(false);
			return this;
		}

		CMemo *CMemo::setVerticalScrollBarElementBorderRadius(const CBaseScrollBar::ELEMENT_TYPE element, const size_t value)
		{
			if (m_pVerticalScrollBar->setElementBorderRadius(element, value))
				Repaint(false);
			return this;
		}

		CMemo *CMemo::setVerticalScrollBarElementBorderAntiAliazing(const CBaseScrollBar::ELEMENT_TYPE element, const size_t value)
		{
			if (m_pVerticalScrollBar->setElementBorderAntiAliazing(element, value))
				Repaint(false);
			return this;
		}

		CMemo *CMemo::setVerticalScrollBarElementBackgroundColor(const CBaseScrollBar::ELEMENT_TYPE element, const CBaseScrollBar::ELEMENT_STATE state, const APP_COLOR &value)
		{
			if (m_pVerticalScrollBar->setElementBackgroundColor(element, state, value))
				Repaint(false);
			return this;
		}

		CMemo *CMemo::setVerticalScrollBarElementBorderColor(const CBaseScrollBar::ELEMENT_TYPE element, const CBaseScrollBar::ELEMENT_STATE state, const APP_COLOR &value)
		{
			if (m_pVerticalScrollBar->setElementBorderColor(element, state, value))
				Repaint(false);
			return this;
		}

		CMemo *CMemo::setVerticalScrollBarElementGradientType(const CBaseScrollBar::ELEMENT_TYPE element, const CBaseScrollBar::ELEMENT_STATE state, const IImage::GRADIENT_TYPE value)
		{
			if (m_pVerticalScrollBar->setElementGradientType(element, state, value))
				Repaint(false);
			return this;
		}

		CMemo *CMemo::setVerticalScrollBarElementGradientPointCount(const CBaseScrollBar::ELEMENT_TYPE element, const CBaseScrollBar::ELEMENT_STATE state, const size_t value)
		{
			if (m_pVerticalScrollBar->setElementGradientPointCount(element, state, value))
				Repaint(false);
			return this;
		}

		CMemo *CMemo::setVerticalScrollBarElementGradientPointPosition(const CBaseScrollBar::ELEMENT_TYPE element, const CBaseScrollBar::ELEMENT_STATE state, const size_t index, const double value)
		{
			if (m_pVerticalScrollBar->setElementGradientPointPosition(element, state, index, value))
				Repaint(false);
			return this;
		}

		CMemo *CMemo::setVerticalScrollBarElementGradientPointColor(const CBaseScrollBar::ELEMENT_TYPE element, const CBaseScrollBar::ELEMENT_STATE state, const size_t index, const APP_COLOR &value)
		{
			if (m_pVerticalScrollBar->setElementGradientPointColor(element, state, index, value))
				Repaint(false);
			return this;
		}

		CMemo *CMemo::setVerticalScrollBarElementGradientPoints(const CBaseScrollBar::ELEMENT_TYPE element, const CBaseScrollBar::ELEMENT_STATE state, const size_t count, IImage::GRADIENT_POINT *points)
		{
			if (m_pVerticalScrollBar->setElementGradientPoints(element, state, count, points))
				Repaint(false);
			return this;
		}
	#pragma endregion

	#pragma region Horizontal scrollbar getter
		bool CMemo::getHorizontalScrollBarEnabled() const
		{
			return m_pHorizontalScrollBar->getEnabled();
		}

		bool CMemo::getHorizontalScrollBarVisible() const
		{
			return m_pHorizontalScrollBar->getVisible();
		}

		int CMemo::getHorizontalScrollBarMax() const
		{
			return m_pHorizontalScrollBar->getMax();
		}

		int CMemo::getHorizontalScrollBarScroll() const
		{
			return m_pHorizontalScrollBar->getScroll();
		}

		size_t CMemo::getHorizontalScrollBarPageSize() const
		{
			return m_pHorizontalScrollBar->getPageSize();
		}

		size_t CMemo::getHorizontalScrollBarDeltaArrow() const
		{
			return m_pHorizontalScrollBar->getDeltaArrow();
		}

		size_t CMemo::getHorizontalScrollBarDeltaWheel() const
		{
			return m_pHorizontalScrollBar->getDeltaWheel();
		}

		CBaseScrollBar::ELEMENT_STATE CMemo::getHorizontalScrollBarElementState(const CBaseScrollBar::ELEMENT_TYPE type) const
		{
			return m_pHorizontalScrollBar->getElementState(type);
		}

		size_t CMemo::getHorizontalScrollBarScrollerSize() const
		{
			return m_pHorizontalScrollBar->getScrollerSize();
		}

		size_t CMemo::getHorizontalScrollBarBorderWidth() const
		{
			return m_pHorizontalScrollBar->getBorderWidth();
		}

		bool CMemo::getHorizontalScrollBarBoxShadow() const
		{
			return m_pHorizontalScrollBar->getBoxShadow();
		}

		APP_POINT CMemo::getHorizontalScrollBarBoxShadowShift() const
		{
			return m_pHorizontalScrollBar->getBoxShadowShift();
		}

		int CMemo::getHorizontalScrollBarBoxShadowShiftX() const
		{
			return m_pHorizontalScrollBar->getBoxShadowShiftX();
		}

		int CMemo::getHorizontalScrollBarBoxShadowShiftY() const
		{
			return m_pHorizontalScrollBar->getBoxShadowShiftY();
		}

		size_t CMemo::getHorizontalScrollBarBoxShadowRadius() const
		{
			return m_pHorizontalScrollBar->getBoxShadowRadius();
		}

		APP_COLOR CMemo::getHorizontalScrollBarBackgroundColor(const CBaseScrollBar::STATE state) const
		{
			return m_pHorizontalScrollBar->getBackgroundColor(state);
		}

		APP_COLOR CMemo::getHorizontalScrollBarBorderColor(const CBaseScrollBar::STATE state) const
		{
			return m_pHorizontalScrollBar->getBorderColor(state);
		}

		APP_COLOR CMemo::getHorizontalScrollBarBoxShadowColor(const CBaseScrollBar::STATE state) const
		{
			return m_pHorizontalScrollBar->getBoxShadowColor(state);
		}

		IImage::GRADIENT_TYPE CMemo::getHorizontalScrollBarGradientType(const CBaseScrollBar::STATE state) const
		{
			return m_pHorizontalScrollBar->getGradientType(state);
		}

		size_t CMemo::getHorizontalScrollBarGradientPointCount(const CBaseScrollBar::STATE state) const
		{
			return m_pHorizontalScrollBar->getGradientPointCount(state);
		}

		double CMemo::getHorizontalScrollBarGradientPointPosition(const CBaseScrollBar::STATE state, const size_t index) const
		{
			return m_pHorizontalScrollBar->getGradientPointPosition(state, index);
		}

		APP_COLOR CMemo::getHorizontalScrollBarGradientPointColor(const CBaseScrollBar::STATE state, const size_t index) const
		{
			return m_pHorizontalScrollBar->getGradientPointColor(state, index);
		}

		size_t CMemo::getHorizontalScrollBarElementBorderWidth(const CBaseScrollBar::ELEMENT_TYPE element) const
		{
			return m_pHorizontalScrollBar->getElementBorderWidth(element);
		}

		size_t CMemo::getHorizontalScrollBarElementBorderRadius(const CBaseScrollBar::ELEMENT_TYPE element) const
		{
			return m_pHorizontalScrollBar->getElementBorderRadius(element);
		}

		size_t CMemo::getHorizontalScrollBarElementBorderAntiAliazing(const CBaseScrollBar::ELEMENT_TYPE element) const
		{
			return m_pHorizontalScrollBar->getElementBorderAntiAliazing(element);
		}

		APP_COLOR CMemo::getHorizontalScrollBarElementBackgroundColor(const CBaseScrollBar::ELEMENT_TYPE element, const CBaseScrollBar::ELEMENT_STATE state) const
		{
			return m_pHorizontalScrollBar->getElementBackgroundColor(element, state);
		}

		APP_COLOR CMemo::getHorizontalScrollBarElementBorderColor(const CBaseScrollBar::ELEMENT_TYPE element, const CBaseScrollBar::ELEMENT_STATE state) const
		{
			return m_pHorizontalScrollBar->getElementBorderColor(element, state);
		}

		IImage::GRADIENT_TYPE CMemo::getHorizontalScrollBarElementGradientType(const CBaseScrollBar::ELEMENT_TYPE element, const CBaseScrollBar::ELEMENT_STATE state) const
		{
			return m_pHorizontalScrollBar->getElementGradientType(element, state);
		}

		size_t CMemo::getHorizontalScrollBarElementGradientPointCount(const CBaseScrollBar::ELEMENT_TYPE element, const CBaseScrollBar::ELEMENT_STATE state) const
		{
			return m_pHorizontalScrollBar->getElementGradientPointCount(element, state);
		}

		double CMemo::getHorizontalScrollBarElementGradientPointPosition(const CBaseScrollBar::ELEMENT_TYPE element, const CBaseScrollBar::ELEMENT_STATE state, const size_t index) const
		{
			return m_pHorizontalScrollBar->getElementGradientPointPosition(element, state, index);
		}

		APP_COLOR CMemo::getHorizontalScrollBarElementGradientPointColor(const CBaseScrollBar::ELEMENT_TYPE element, const CBaseScrollBar::ELEMENT_STATE state, const size_t index) const
		{
			return m_pHorizontalScrollBar->getElementGradientPointColor(element, state, index);
		}

		bool CMemo::getHorizontalScrollBarHovered() const
		{
			return m_pHorizontalScrollBar->getHovered();
		}
	#pragma endregion

	#pragma region Horizontal scrollbar setters
		CMemo *CMemo::setHorizontalScrollBarScroll(const int value)
		{
			if (m_pHorizontalScrollBar->setScroll(value))
			{
				m_pText->setHorizontalScroll(m_pHorizontalScrollBar->getScroll());
				m_pText->UpdateCaret();
				Repaint(false);
			}
			return this;
		}

		CMemo *CMemo::setHorizontalScrollBarDeltaArrow(const size_t value)
		{
			m_pHorizontalScrollBar->setDeltaArrow(value);
			return this;
		}

		CMemo *CMemo::setHorizontalScrollBarDeltaWheel(const size_t value)
		{
			m_pHorizontalScrollBar->setDeltaWheel(value);
			return this;
		}

		CMemo *CMemo::setHorizontalScrollBarBorderWidth(const size_t value)
		{
			if (m_pHorizontalScrollBar->setBorderWidth(value))
				UpdateAll();
			return this;
		}

		CMemo *CMemo::setHorizontalScrollBarBoxShadow(const bool value)
		{
			if (m_pHorizontalScrollBar->setBoxShadow(value))
				Repaint(false);
			return this;
		}

		CMemo *CMemo::setHorizontalScrollBarBoxShadowShift(const APP_POINT &value)
		{
			if (m_pHorizontalScrollBar->setBoxShadowShift(value))
				Repaint(false);
			return this;
		}

		CMemo *CMemo::setHorizontalScrollBarBoxShadowShiftX(const int value)
		{
			if (m_pHorizontalScrollBar->setBoxShadowShiftX(value))
				Repaint(false);
			return this;
		}

		CMemo *CMemo::setHorizontalScrollBarBoxShadowShiftY(const int value)
		{
			if (m_pHorizontalScrollBar->setBoxShadowShiftY(value))
				Repaint(false);
			return this;
		}

		CMemo *CMemo::setHorizontalScrollBarBoxShadowRadius(const size_t value)
		{
			if (m_pHorizontalScrollBar->setBoxShadowRadius(value))
				Repaint(false);
			return this;
		}

		CMemo *CMemo::setHorizontalScrollBarBackgroundColor(const CBaseScrollBar::STATE state, const APP_COLOR &value)
		{
			if (m_pHorizontalScrollBar->setBackgroundColor(state, value))
				Repaint(false);
			return this;
		}

		CMemo *CMemo::setHorizontalScrollBarBorderColor(const CBaseScrollBar::STATE state, const APP_COLOR &value)
		{
			if (m_pHorizontalScrollBar->setBorderColor(state, value))
				Repaint(false);
			return this;
		}

		CMemo *CMemo::setHorizontalScrollBarBoxShadowColor(const CBaseScrollBar::STATE state, const APP_COLOR &value)
		{
			if (m_pHorizontalScrollBar->setBoxShadowColor(state, value))
				Repaint(false);
			return this;
		}

		CMemo *CMemo::setHorizontalScrollBarGradientType(const CBaseScrollBar::STATE state, const IImage::GRADIENT_TYPE value)
		{
			if (m_pHorizontalScrollBar->setGradientType(state, value))
				Repaint(false);
			return this;
		}

		CMemo *CMemo::setHorizontalScrollBarGradientPointCount(const CBaseScrollBar::STATE state, const size_t value)
		{
			if (m_pHorizontalScrollBar->setGradientPointCount(state, value))
				Repaint(false);
			return this;
		}

		CMemo *CMemo::setHorizontalScrollBarGradientPointPosition(const CBaseScrollBar::STATE state, const size_t index, const double value)
		{
			if (m_pHorizontalScrollBar->setGradientPointPosition(state, index, value))
				Repaint(false);
			return this;
		}

		CMemo *CMemo::setHorizontalScrollBarGradientPointColor(const CBaseScrollBar::STATE state, const size_t index, const APP_COLOR &value)
		{
			if (m_pHorizontalScrollBar->setGradientPointColor(state, index, value))
				Repaint(false);
			return this;
		}

		CMemo *CMemo::setHorizontalScrollBarGradientPoints(const CBaseScrollBar::STATE state, const size_t count, IImage::GRADIENT_POINT *points)
		{
			if (m_pHorizontalScrollBar->setGradientPoints(state, count, points))
				Repaint(false);
			return this;
		}

		CMemo *CMemo::setHorizontalScrollBarElementBorderWidth(const CBaseScrollBar::ELEMENT_TYPE element, const size_t value)
		{
			if (m_pHorizontalScrollBar->setElementBorderWidth(element, value))
				Repaint(false);
			return this;
		}

		CMemo *CMemo::setHorizontalScrollBarElementBorderRadius(const CBaseScrollBar::ELEMENT_TYPE element, const size_t value)
		{
			if (m_pHorizontalScrollBar->setElementBorderRadius(element, value))
				Repaint(false);
			return this;
		}

		CMemo *CMemo::setHorizontalScrollBarElementBorderAntiAliazing(const CBaseScrollBar::ELEMENT_TYPE element, const size_t value)
		{
			if (m_pHorizontalScrollBar->setElementBorderAntiAliazing(element, value))
				Repaint(false);
			return this;
		}

		CMemo *CMemo::setHorizontalScrollBarElementBackgroundColor(const CBaseScrollBar::ELEMENT_TYPE element, const CBaseScrollBar::ELEMENT_STATE state, const APP_COLOR &value)
		{
			if (m_pHorizontalScrollBar->setElementBackgroundColor(element, state, value))
				Repaint(false);
			return this;
		}

		CMemo *CMemo::setHorizontalScrollBarElementBorderColor(const CBaseScrollBar::ELEMENT_TYPE element, const CBaseScrollBar::ELEMENT_STATE state, const APP_COLOR &value)
		{
			if (m_pHorizontalScrollBar->setElementBorderColor(element, state, value))
				Repaint(false);
			return this;
		}

		CMemo *CMemo::setHorizontalScrollBarElementGradientType(const CBaseScrollBar::ELEMENT_TYPE element, const CBaseScrollBar::ELEMENT_STATE state, const IImage::GRADIENT_TYPE value)
		{
			if (m_pHorizontalScrollBar->setElementGradientType(element, state, value))
				Repaint(false);
			return this;
		}

		CMemo *CMemo::setHorizontalScrollBarElementGradientPointCount(const CBaseScrollBar::ELEMENT_TYPE element, const CBaseScrollBar::ELEMENT_STATE state, const size_t value)
		{
			if (m_pHorizontalScrollBar->setElementGradientPointCount(element, state, value))
				Repaint(false);
			return this;
		}

		CMemo *CMemo::setHorizontalScrollBarElementGradientPointPosition(const CBaseScrollBar::ELEMENT_TYPE element, const CBaseScrollBar::ELEMENT_STATE state, const size_t index, const double value)
		{
			if (m_pHorizontalScrollBar->setElementGradientPointPosition(element, state, index, value))
				Repaint(false);
			return this;
		}

		CMemo *CMemo::setHorizontalScrollBarElementGradientPointColor(const CBaseScrollBar::ELEMENT_TYPE element, const CBaseScrollBar::ELEMENT_STATE state, const size_t index, const APP_COLOR &value)
		{
			if (m_pHorizontalScrollBar->setElementGradientPointColor(element, state, index, value))
				Repaint(false);
			return this;
		}

		CMemo *CMemo::setHorizontalScrollBarElementGradientPoints(const CBaseScrollBar::ELEMENT_TYPE element, const CBaseScrollBar::ELEMENT_STATE state, const size_t count, IImage::GRADIENT_POINT *points)
		{
			if (m_pHorizontalScrollBar->setElementGradientPoints(element, state, count, points))
				Repaint(false);
			return this;
		}
	#pragma endregion
	}
}