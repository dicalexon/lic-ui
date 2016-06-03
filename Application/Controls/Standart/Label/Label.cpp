// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#include "Label.h"
#include "..\..\..\..\Math\Utils.h"
#include "..\..\..\Form.h"
#include "..\..\..\Presenter.h"

namespace licui
{
	namespace application
	{
#pragma region Constructors
		CLabel::CLabel() :CControl(),
			m_bAutoSize{ true },
			m_iAntiAliazing{ 2 },
			m_eHotizontalAlign{ taLeft },
			m_eVerticalAlign{ vaTop },
			m_dScale{ 1, 1 }
		{
			m_sClassName = L"CLabel";
			m_bAcceptForm = true;
			m_bAcceptParent = true;
			m_sInitialRect = { 0, 0, 1, 1 };
			m_bSupportText = true;
		}

		CLabel::CLabel(CControl *parent) : CLabel()
		{
			setParent(parent);
		}

		CLabel::CLabel(CForm *form) :CLabel()
		{
			setForm(form);
		}
#pragma endregion

#pragma region Helpers
		void CLabel::UpdateRect()
		{
			if (m_bAutoSize && getFont())
			{
				APP_POINT p = getFont()->getStringSize(m_sCaption);
				p.X = (int)(0.5 + p.X * m_dScale.X);
				p.Y = (int)(0.5 + p.Y * m_dScale.Y);
				p = math::RotatedRectangleSize(p, getFont()->getOrientation() * math::PI / 1800.0);
				m_sInitialRect.Right = m_sInitialRect.Left + p.X;
				m_sInitialRect.Bottom = m_sInitialRect.Top + p.Y;
			}
			CControl::UpdateRect();
		}
#pragma endregion

#pragma region Notifications
		void CLabel::NotifyOnPaint(APP_RECT clip)
		{
			/*if (!m_bBufferValid)
			{
				APP_POINT p = getFont()->getStringSize(m_sCaption);
				if (p.X > 0 && p.Y > 0 && (m_pBuffer = m_pForm->getPresenter()->ImageCreate(p.X, p.Y, L"", m_pBuffer, { "RGBA" })))
				{
					m_pBuffer->BeginPaint();
					m_pBuffer->Clear({ 0, 0, 0, 0 });
					m_pBuffer->RenderString(m_sCaption, getFont(), 0, 0, 0, 1, 1, { 0, 0, p.X, p.Y }, m_iAntiAliazing, { 0, 0, p.X, p.Y }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, 0, graphics::bplInside,
						true, false, getFont()->getColor(), getFont()->getShadowColor(), nullptr, nullptr, false);
					m_pBuffer->EndPaint();
				}
				else if (m_pBuffer)
				{
					m_pBuffer->Release();
					m_pBuffer = nullptr;
				}
				m_bBufferValid = true;
			}
			if (!m_bShadowBufferValid)
			{
				if (m_pBuffer && getFont()->getShadow() && getFont()->getShadowColor().getAlpha() > 0 &&
					(m_pShadowBuffer = m_pForm->getPresenter()->ImageCreate(m_pBuffer->getWidth() + getFont()->getShadowBlur() + 1, m_pBuffer->getHeight() + getFont()->getShadowBlur() + 1,
						L"", m_pShadowBuffer, { "RGBA" })))
				{
					m_pShadowBuffer->BeginPaint();
					m_pShadowBuffer->Clear({ 0, 0, 0, 0 });
					APP_RECT rect{ 0, 0, (int)m_pBuffer->getWidth(), (int)m_pBuffer->getHeight() };
					m_pShadowBuffer->RenderImage(m_pBuffer, rect, getFont()->getShadowBlur() / 2, getFont()->getShadowBlur() / 2, 0, 1, 1, false, false, false, rect, rect, { 0, 0, 0, 0 }, { 0, 0, 0, 0 },
						0, graphics::bplInside, nullptr, nullptr, false);
					m_pShadowBuffer->Blur(getFont()->getShadowColor(), getFont()->getShadowBlur(), rect);
					m_pShadowBuffer->EndPaint();
				}
				else if (m_pShadowBuffer)
				{
					m_pShadowBuffer->Release();
					m_pShadowBuffer = nullptr;
				}
				m_bShadowBufferValid = true;
			}
			clip *= getVisibleRect();
			if (!m_sCaption.empty() && getVisibleWithParents() && !clip.IsEmpty())
			{
				if (m_pBuffer)
				{
					APP_POINT p{ (int)m_pBuffer->getWidth(), (int)m_pBuffer->getHeight() };
					p.X = (int)(0.5 + p.X * m_dScale.X);
					p.Y = (int)(0.5 + p.Y * m_dScale.Y);
					p = math::RotatedRectangleSize(p, getFont()->getOrientation() * math::PI / 1800.0);
					int x{ getRect().Left }, y{ getRect().Top };
					switch (m_eHotizontalAlign)
					{
					case taRight:
						x = getRect().Right - p.X;
						break;
					case taCenter:
						x = (getRect().Left + getRect().Right - p.X) / 2;
						break;
					}
					switch (m_eVerticalAlign)
					{
					case vaBottom:
						y = getRect().Bottom - p.Y;
						break;
					case vaMiddle:
						y = (getRect().Top + getRect().Bottom - p.Y) / 2;
						break;
					}
					APP_POINT r = ClientToForm(APP_POINT{ x, y });
					if (m_pShadowBuffer && getFont()->getShadow() && getFont()->getShadowColor().getAlpha() > 0)
					{
						double pos_x, pos_y;
						pos_x = r.X + (getFont()->getShadowShiftX() - getFont()->getShadowBlur() * 0.5) * m_dScale.X;
						pos_y = r.Y + (getFont()->getShadowShiftY() - getFont()->getShadowBlur() * 0.5) * m_dScale.Y;
						APP_RECT rect{ 0, 0, (int)m_pShadowBuffer->getWidth(), (int)m_pShadowBuffer->getHeight() };
						m_pForm->getPresenter()->RenderImage(m_pShadowBuffer, rect, pos_x, pos_y, getFont()->getOrientation() * math::PI / 1800.0, m_dScale.X, m_dScale.Y,
							false, false, true, clip, ClientToForm(getRect()), { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, 0, graphics::bplInside, nullptr, nullptr, true);
					}
					if (getFont()->getColor().getAlpha() > 0)
					{
						APP_RECT rect{ 0, 0, (int)m_pBuffer->getWidth(), (int)m_pBuffer->getHeight() };
						m_pForm->getPresenter()->RenderImage(m_pBuffer, rect, r.X, r.Y, getFont()->getOrientation() * math::PI / 1800.0, m_dScale.X, m_dScale.Y,
							false, false, true, clip, ClientToForm(getRect()), { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, 0, graphics::bplInside, nullptr, nullptr, true);
					}
				}
			}*/
			clip *= getVisibleRect();
			if (!m_sCaption.empty() && getVisibleWithParents() && !clip.IsEmpty())
			{
				APP_POINT p = getFont()->getStringSize(m_sCaption);
				p.X = (int)(0.5 + p.X * m_dScale.X);
				p.Y = (int)(0.5 + p.Y * m_dScale.Y);
				p = math::RotatedRectangleSize(p, getFont()->getOrientation() * math::PI / 1800.0);
				int x{ getRect().Left }, y{ getRect().Top };
				switch (m_eHotizontalAlign)
				{
				case taRight:
					x = getRect().Right - p.X;
					break;
				case taCenter:
					x = (getRect().Left + getRect().Right - p.X) / 2;
					break;
				}
				switch (m_eVerticalAlign)
				{
				case vaBottom:
					y = getRect().Bottom - p.X;
					break;
				case vaMiddle:
					y = (getRect().Top + getRect().Bottom - p.Y) / 2;
					break;
				}
				APP_POINT r = ClientToForm(APP_POINT{ x, y });
				m_pForm->getPresenter()->RenderString(
					m_sCaption,
					getFont(),
					r.X, r.Y, -getFont()->getOrientation() * math::PI / 1800.0, m_dScale.X, m_dScale.Y,
					clip,
					m_iAntiAliazing,
					ClientToForm(getRect()),
					{ 0, 0, 0, 0 },
					{ 0, 0, 0, 0 },
					0, graphics::bplInside,
					true, true,
					getFont()->getColor(), getFont()->getShadowColor(),
					nullptr, nullptr, true);
			}
			CControl::NotifyOnPaint(clip);
		}
#pragma endregion

#pragma region Getters
		bool CLabel::getAutoSize() const
		{
			return m_bAutoSize;
		}

		String CLabel::getCaption() const
		{
			return m_sCaption;
		}

		size_t CLabel::getAntiAliazing() const
		{
			return m_iAntiAliazing;
		}

		TEXT_ALIGN CLabel::getHorizontalAlign() const
		{
			return m_eHotizontalAlign;
		}

		VERTICAL_ALIGN CLabel::getVerticalAlign() const
		{
			return m_eVerticalAlign;
		}

		math::POINT<double> CLabel::getScale() const
		{
			return m_dScale;
		}

		double CLabel::getScaleX() const
		{
			return m_dScale.X;
		}

		double CLabel::getScaleY() const
		{
			return m_dScale.Y;
		}
#pragma endregion

#pragma region Setters
		CLabel *CLabel::setAutoSize(const bool value)
		{
			if (m_bAutoSize != value)
			{
				m_bAutoSize = value;
				UpdateRect();
			}
			return this;
		}

		CLabel *CLabel::setCaption(const String &value)
		{
			if (m_sCaption != value)
			{
				m_sCaption = value;
				if (m_pForm)
					m_pForm->LockRepaint();
				UpdateRect();
				Repaint(false);
				if (m_pForm)
					m_pForm->UnlockRepaint();
			}
			return this;
		}

		CLabel *CLabel::setAntiAliazing(size_t value)
		{
			if (value == 1)
				value = 0;
			if (m_iAntiAliazing != value)
			{
				m_iAntiAliazing = value;
				if (!m_sCaption.empty())
					Repaint(false);
			}
			return this;
		}

		CLabel *CLabel::setHorizontalAlign(const TEXT_ALIGN value)
		{
			if (m_eHotizontalAlign != value)
			{
				m_eHotizontalAlign = value;
				if (!m_sCaption.empty())
					Repaint(false);
			}
			return this;
		}

		CLabel *CLabel::setVerticalAlign(const VERTICAL_ALIGN value)
		{
			if (m_eVerticalAlign != value)
			{
				m_eVerticalAlign = value;
				if (!m_sCaption.empty())
					Repaint(false);
			}
			return this;
		}

		CLabel *CLabel::setScale(const math::POINT<double> &value)
		{
			if (value != m_dScale)
			{
				m_dScale = value;
				if (m_pForm)
					m_pForm->LockRepaint();
				UpdateRect();
				Repaint(false);
				if (m_pForm)
					m_pForm->UnlockRepaint();
			}
			return this;
		}

		CLabel *CLabel::setScaleX(const double value)
		{
			if (value != m_dScale.X)
			{
				m_dScale.X = value;
				if (m_pForm)
					m_pForm->LockRepaint();
				UpdateRect();
				Repaint(false);
				if (m_pForm)
					m_pForm->UnlockRepaint();
			}
			return this;
		}

		CLabel *CLabel::setScaleY(const double value)
		{
			if (value != m_dScale.Y)
			{
				m_dScale.Y = value;
				if (m_pForm)
					m_pForm->LockRepaint();
				UpdateRect();
				Repaint(false);
				if (m_pForm)
					m_pForm->UnlockRepaint();
			}
			return this;
		}
#pragma endregion

#pragma region Overwrited parent setters
		CControl *CLabel::setAlign(const ALIGN value)
		{
			m_bAutoSize = false;
			return CControl::setAlign(value);
		}

		CControl *CLabel::setRect(APP_RECT value)
		{
			if (value.Width() != getRect().Width() || value.Height() != getRect().Height())
				m_bAutoSize = false;
			return CControl::setRect(value);
		}
#pragma endregion
	}
}