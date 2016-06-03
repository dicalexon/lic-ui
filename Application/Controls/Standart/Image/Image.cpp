// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#include "Image.h"
#include "..\..\..\..\Math\Utils.h"
#include "..\..\..\Form.h"
#include "..\..\..\Presenter.h"

namespace licui
{
	namespace application
	{
#pragma region Constructors
		CImage::CImage() :CBaseBlock(),
			m_bAutoSize{ true }
		{
			m_sClassName = L"CImage";
			m_bAcceptForm = true;
			m_bAcceptParent = true;
			m_sInitialRect = { 50, 50, 150, 150 };
			m_sBlock.BorderColor[0] = m_sBlock.BorderColor[1] = m_sBlock.BorderColor[2] = m_sBlock.BorderColor[3] = { 0, 0, 0, 0 };
			m_sBlock.BackgroundColor = { 0, 0, 0, 0 };
		}

		CImage::CImage(CControl *parent) : CImage()
		{
			setParent(parent);
		}

		CImage::CImage(CForm *form) : CImage()
		{
			setForm(form);
		}
#pragma endregion

#pragma region Helpers
		CBaseBlock::BLOCK *CImage::getBlock()
		{
			return &m_sBlock;
		}

		void CImage::UpdateRect()
		{
			if (m_bAutoSize && m_sBlock.BackgroundImage.getWidth() > 0)
			{
				math::POINT<double> p;
				if (m_sBlock.BackgroundSize[0] == 0)
					p.X = m_sBlock.BackgroundImage.getWidth();
				else if (m_sBlock.BackgroundSize[0] > 0)
					p.X = m_sBlock.BackgroundSize[0] * 0.1;
				else
					p.X = -m_sBlock.BackgroundSize[0] * 0.001 * m_sBlock.BackgroundImage.getWidth();
				if (m_sBlock.BackgroundSize[1] == 0)
					p.Y = m_sBlock.BackgroundImage.getHeight();
				else if (m_sBlock.BackgroundSize[1] > 0)
					p.Y = m_sBlock.BackgroundSize[1] * 0.1;
				else
					p.Y = -m_sBlock.BackgroundSize[1] * 0.001 * m_sBlock.BackgroundImage.getHeight();
				p = math::RotatedRectangleSize(p, m_sBlock.BackgroundRotation);
				m_sInitialRect.Right = m_sInitialRect.Left + (int)(0.5 + p.X);
				m_sInitialRect.Bottom = m_sInitialRect.Top + (int)(0.5 + p.Y);
			}
			CBaseBlock::UpdateRect();
		}
#pragma endregion

#pragma region Overwrited parent setters
		CControl *CImage::setAlign(const ALIGN value)
		{
			m_bAutoSize = false;
			return CBaseBlock::setAlign(value);
		}

		CControl *CImage::setRect(APP_RECT value)
		{
			if (value.Width() != getRect().Width() || value.Height() != getRect().Height())
				m_bAutoSize = false;
			return CBaseBlock::setRect(value);
		}
#pragma endregion

#pragma region Notifications
		void CImage::NotifyOnPaint(APP_RECT clip)
		{
			if (getVisibleWithParents())
			{
				if (m_sBlock.BackgroundColor.getAlpha() > 0)
					DoRenderBlock(clip);
				if (m_sBlock.BackgroundImage.getWidth() > 0)
					DoRenderBackgroundImage(clip);
			}
			CBaseBlock::NotifyOnPaint(clip);
		}
#pragma endregion

#pragma region Getters
		bool CImage::getAutoSize() const
		{
			return m_bAutoSize;
		}
#pragma endregion

#pragma region Setters
		CImage *CImage::setAutoSize(const bool value)
		{
			if (value != m_bAutoSize)
			{
				m_bAutoSize = value;
				m_eAlign = alNone;
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
	}
}