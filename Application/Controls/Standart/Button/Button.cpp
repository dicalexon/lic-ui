// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#include "Button.h"
#include "..\..\..\Form.h"
#include "..\..\..\Style.h"
#include "..\..\..\Presenter.h"
#include "..\..\..\ImageManager.h"

namespace licui
{
	namespace application
	{
	#pragma region Constructors
		CButton::CButton() :CControl(),
			m_eCaptionHorizontalAlign{ taCenter },
			m_eCaptionVerticalAlign{ vaMiddle },
			m_eImageAlign{ ialLeft },
			m_sImageMargin{ 0, 0, 8, 0 },
			m_iBorderRadius{ 2 },
			m_iBorderOuterWidth{ 1 },
			m_iBorderInnerWidth{ 1 },
			m_iBorderAntiAliazing{ 0 },
			m_fOnClick{ nullptr },
			m_bIsActive{ false }
		{
			m_sClassName = L"CButton";
			m_bAcceptFocus = true;
			m_bAcceptForm = true;
			m_bAcceptParent = true;
			m_bSupportText = true;
			m_bTabStop = true;
			m_sInitialRect = { 0, 0, 104, 23 };
			InitStates();
		}

		CButton::CButton(CForm *form) :CButton()
		{
			setForm(form);
		}

		CButton::CButton(CControl *parent) : CButton()
		{
			setParent(parent);
		}

		void CButton::InitStates()
		{
			m_aStates[stNormal].ImageList = nullptr;
			m_aStates[stNormal].ImageIndex = -1;
			m_aStates[stNormal].TextColor = { 0, 0, 0, 0 };
			m_aStates[stNormal].ShadowColor = { 0, 0, 0, 0 };
			m_aStates[stNormal].BorderOuterColor = { 112, 112, 112, 255 };
			m_aStates[stNormal].BorderInnerColor = { 243, 243, 243, 255 };
			m_aStates[stNormal].BackgroundColor = { 0, 0, 0, 0 };
			m_aStates[stNormal].GradientType = IImage::gtVertical;
			m_aStates[stNormal].GradientPointCount = 4;
			m_aStates[stNormal].GradientPoints = new IImage::GRADIENT_POINT[4];
			m_aStates[stNormal].GradientPoints[0].Position = 0;
			m_aStates[stNormal].GradientPoints[0].Color = { 242, 242, 242, 255 };
			m_aStates[stNormal].GradientPoints[1].Position = 0.499;
			m_aStates[stNormal].GradientPoints[1].Color = { 235, 235, 235, 255 };
			m_aStates[stNormal].GradientPoints[2].Position = 0.5;
			m_aStates[stNormal].GradientPoints[2].Color = { 221, 221, 221, 255 };
			m_aStates[stNormal].GradientPoints[3].Position = 1;
			m_aStates[stNormal].GradientPoints[3].Color = { 207, 207, 207, 255 };
			m_aStates[stNormal].GradientPointsSorted = true;

			m_aStates[stNormalHovered].ImageList = nullptr;
			m_aStates[stNormalHovered].ImageIndex = -1;
			m_aStates[stNormalHovered].TextColor = { 0, 0, 0, 0 };
			m_aStates[stNormalHovered].ShadowColor = { 0, 0, 0, 0 };
			m_aStates[stNormalHovered].BorderOuterColor = { 60, 127, 177, 255 };
			m_aStates[stNormalHovered].BorderInnerColor = { 250, 253, 254, 255 };
			m_aStates[stNormalHovered].BackgroundColor = { 0, 0, 0, 0 };
			m_aStates[stNormalHovered].GradientType = IImage::gtVertical;
			m_aStates[stNormalHovered].GradientPointCount = 4;
			m_aStates[stNormalHovered].GradientPoints = new IImage::GRADIENT_POINT[4];
			m_aStates[stNormalHovered].GradientPoints[0].Position = 0;
			m_aStates[stNormalHovered].GradientPoints[0].Color = { 234, 246, 253, 255 };
			m_aStates[stNormalHovered].GradientPoints[1].Position = 0.499;
			m_aStates[stNormalHovered].GradientPoints[1].Color = { 217, 240, 252, 255 };
			m_aStates[stNormalHovered].GradientPoints[2].Position = 0.5;
			m_aStates[stNormalHovered].GradientPoints[2].Color = { 190, 230, 253, 255 };
			m_aStates[stNormalHovered].GradientPoints[3].Position = 1;
			m_aStates[stNormalHovered].GradientPoints[3].Color = { 167, 217, 245, 255 };
			m_aStates[stNormalHovered].GradientPointsSorted = true;

			m_aStates[stFocused].ImageList = nullptr;
			m_aStates[stFocused].ImageIndex = -1;
			m_aStates[stFocused].TextColor = { 0, 0, 0, 0 };
			m_aStates[stFocused].ShadowColor = { 0, 0, 0, 0 };
			m_aStates[stFocused].BorderOuterColor = { 60, 127, 177, 255 };
			m_aStates[stFocused].BorderInnerColor = { 59, 214, 253, 255 };
			m_aStates[stFocused].BackgroundColor = { 0, 0, 0, 0 };
			m_aStates[stFocused].GradientType = IImage::gtVertical;
			m_aStates[stFocused].GradientPointCount = 4;
			m_aStates[stFocused].GradientPoints = new IImage::GRADIENT_POINT[4];
			m_aStates[stFocused].GradientPoints[0].Position = 0;
			m_aStates[stFocused].GradientPoints[0].Color = { 238, 244, 247, 255 };
			m_aStates[stFocused].GradientPoints[1].Position = 0.499;
			m_aStates[stFocused].GradientPoints[1].Color = { 232, 239, 244, 255 };
			m_aStates[stFocused].GradientPoints[2].Position = 0.5;
			m_aStates[stFocused].GradientPoints[2].Color = { 211, 227, 236, 255 };
			m_aStates[stFocused].GradientPoints[3].Position = 1;
			m_aStates[stFocused].GradientPoints[3].Color = { 195, 216, 228, 255 };
			m_aStates[stFocused].GradientPointsSorted = true;

			m_aStates[stFocusedHovered].ImageList = nullptr;
			m_aStates[stFocusedHovered].ImageIndex = -1;
			m_aStates[stFocusedHovered].TextColor = { 0, 0, 0, 0 };
			m_aStates[stFocusedHovered].ShadowColor = { 0, 0, 0, 0 };
			m_aStates[stFocusedHovered].BorderOuterColor = { 60, 127, 177, 255 };
			m_aStates[stFocusedHovered].BorderInnerColor = { 250, 253, 254, 255 };
			m_aStates[stFocusedHovered].BackgroundColor = { 0, 0, 0, 0 };
			m_aStates[stFocusedHovered].GradientType = IImage::gtVertical;
			m_aStates[stFocusedHovered].GradientPointCount = 4;
			m_aStates[stFocusedHovered].GradientPoints = new IImage::GRADIENT_POINT[4];
			m_aStates[stFocusedHovered].GradientPoints[0].Position = 0;
			m_aStates[stFocusedHovered].GradientPoints[0].Color = { 234, 246, 253, 255 };
			m_aStates[stFocusedHovered].GradientPoints[1].Position = 0.499;
			m_aStates[stFocusedHovered].GradientPoints[1].Color = { 217, 240, 252, 255 };
			m_aStates[stFocusedHovered].GradientPoints[2].Position = 0.5;
			m_aStates[stFocusedHovered].GradientPoints[2].Color = { 190, 230, 253, 255 };
			m_aStates[stFocusedHovered].GradientPoints[3].Position = 1;
			m_aStates[stFocusedHovered].GradientPoints[3].Color = { 167, 217, 245, 255 };
			m_aStates[stFocusedHovered].GradientPointsSorted = true;

			m_aStates[stActive].ImageList = nullptr;
			m_aStates[stActive].ImageIndex = -1;
			m_aStates[stActive].TextColor = { 0, 0, 0, 0 };
			m_aStates[stActive].ShadowColor = { 0, 0, 0, 0 };
			m_aStates[stActive].BorderOuterColor = { 44, 98, 139, 255 };
			m_aStates[stActive].BorderInnerColor = { 158, 176, 186, 255 };
			m_aStates[stActive].BackgroundColor = { 0, 0, 0, 0 };
			m_aStates[stActive].GradientType = IImage::gtVertical;
			m_aStates[stActive].GradientPointCount = 4;
			m_aStates[stActive].GradientPoints = new IImage::GRADIENT_POINT[4];
			m_aStates[stActive].GradientPoints[0].Position = 0;
			m_aStates[stActive].GradientPoints[0].Color = { 229, 244, 252, 255 };
			m_aStates[stActive].GradientPoints[1].Position = 0.499;
			m_aStates[stActive].GradientPoints[1].Color = { 196, 229, 246, 255 };
			m_aStates[stActive].GradientPoints[2].Position = 0.5;
			m_aStates[stActive].GradientPoints[2].Color = { 152, 209, 239, 255 };
			m_aStates[stActive].GradientPoints[3].Position = 1;
			m_aStates[stActive].GradientPoints[3].Color = { 109, 182, 221, 255 };
			m_aStates[stActive].GradientPointsSorted = true;

			m_aStates[stDisabled].ImageList = nullptr;
			m_aStates[stDisabled].ImageIndex = -1;
			m_aStates[stDisabled].TextColor = { 133, 135, 139, 255 };
			m_aStates[stDisabled].ShadowColor = { 133, 135, 139, 255 };
			m_aStates[stDisabled].BorderOuterColor = { 173, 178, 181, 255 };
			m_aStates[stDisabled].BorderInnerColor = { 252, 252, 252, 255 };
			m_aStates[stDisabled].BackgroundColor = { 244, 244, 244, 255 };
			m_aStates[stDisabled].GradientType = IImage::gtVertical;
			m_aStates[stDisabled].GradientPointCount = 0;
			m_aStates[stDisabled].GradientPoints = nullptr;
			m_aStates[stDisabled].GradientPointsSorted = true;
		}
	#pragma endregion

	#pragma region Getter
		CButton::STATE CButton::getState() const
		{
			if (m_bEnabled)
				if (m_pForm && m_pForm->getActiveControl() == this)
					if (m_bIsActive)
						return stActive;
					else
						if (m_pForm && m_pForm->getHoveredControl() == this)
							return stFocusedHovered;
						else
							return stFocused;
				else
					if (m_pForm && m_pForm->getHoveredControl() == this)
						return stNormalHovered;
					else
						return stNormal;
			else
				return stDisabled;
		}

		String CButton::getCaption() const
		{
			return m_sCaption;
		}

		TEXT_ALIGN CButton::getCaptionHorizontalAlign() const
		{
			return m_eCaptionHorizontalAlign;
		}

		VERTICAL_ALIGN CButton::getCaptionVerticalAlign() const
		{
			return m_eCaptionVerticalAlign;
		}

		CButton::IMAGE_ALIGN CButton::getImageAlign() const
		{
			return m_eImageAlign;
		}

		math::RECTANGLE<size_t> CButton::getImageMargin() const
		{
			return m_sImageMargin;
		}

		size_t CButton::getImageMarginLeft() const
		{
			return m_sImageMargin.Left;
		}

		size_t CButton::getImageMarginTop() const
		{
			return m_sImageMargin.Top;
		}

		size_t CButton::getImageMarginRight() const
		{
			return m_sImageMargin.Right;
		}

		size_t CButton::getImageMarginBottom() const
		{
			return m_sImageMargin.Bottom;
		}

		size_t CButton::getBorderRadius() const
		{
			return m_iBorderRadius;
		}

		size_t CButton::getBorderOuterWidth() const
		{
			return m_iBorderOuterWidth;
		}

		size_t CButton::getBorderInnerWidth() const
		{
			return m_iBorderInnerWidth;
		}

		size_t CButton::getBorderAntiAliazing() const
		{
			return m_iBorderAntiAliazing;
		}

		CImageList *CButton::getImageList(const STATE state)
		{
			return m_aStates[state].ImageList;
		}

		int CButton::getImageIndex(const STATE state) const
		{
			return m_aStates[state].ImageIndex;
		}

		APP_COLOR CButton::getTextColor(const STATE state) const
		{
			return m_aStates[state].TextColor;
		}

		APP_COLOR CButton::getShadowColor(const STATE state) const
		{
			return m_aStates[state].ShadowColor;
		}

		APP_COLOR CButton::getBorderOuterColor(const STATE state) const
		{
			return m_aStates[state].BorderOuterColor;
		}

		APP_COLOR CButton::getBorderInnerColor(const STATE state) const
		{
			return m_aStates[state].BorderInnerColor;
		}

		APP_COLOR CButton::getBackgroundColor(const STATE state) const
		{
			return m_aStates[state].BackgroundColor;
		}

		IImage::GRADIENT_TYPE CButton::getGradientType(const STATE state) const
		{
			return m_aStates[state].GradientType;
		}

		size_t CButton::getGradientPointCount(const STATE state) const
		{
			return m_aStates[state].GradientPointCount;
		}

		double CButton::getGradientPointPosition(const STATE state, const size_t index) const
		{
			if (index < m_aStates[state].GradientPointCount)
				return m_aStates[state].GradientPoints[index].Position;
			return 0;
		}

		APP_COLOR CButton::getGradientPointColor(const STATE state, const size_t index) const
		{
			if (index < m_aStates[state].GradientPointCount)
				return m_aStates[state].GradientPoints[index].Color;
			return{ 0, 0, 0, 0 };
		}

		CButton::FOnClick CButton::getOnClick() const
		{
			return m_fOnClick;
		}
	#pragma endregion

	#pragma region Setters
		CButton *CButton::setCaption(const String &value)
		{
			if (value != m_sCaption)
			{
				m_sCaption = value;
				Repaint(false);
			}
			return this;
		}

		CButton *CButton::setCaptionHorizontalAlign(const TEXT_ALIGN value)
		{
			if (value != m_eCaptionHorizontalAlign)
			{
				m_eCaptionHorizontalAlign = value;
				Repaint(false);
			}
			return this;
		}

		CButton *CButton::setCaptionVerticalAlign(const VERTICAL_ALIGN value)
		{
			if (value != m_eCaptionVerticalAlign)
			{
				m_eCaptionVerticalAlign = value;
				Repaint(false);
			}
			return this;
		}

		CButton *CButton::setImageAlign(const IMAGE_ALIGN value)
		{
			if (value != m_eImageAlign)
			{
				m_eImageAlign = value;
				Repaint(false);
			}
			return this;
		}

		CButton *CButton::setImageMargin(const math::RECTANGLE<size_t> &value)
		{
			if (value != m_sImageMargin)
			{
				m_sImageMargin = value;
				Repaint(false);
			}
			return this;
		}

		CButton *CButton::setImageMarginLeft(const size_t value)
		{
			return setImageMargin({ value, m_sImageMargin.Top, m_sImageMargin.Right, m_sImageMargin.Bottom });
		}

		CButton *CButton::setImageMarginTop(const size_t value)
		{
			return setImageMargin({ m_sImageMargin.Left, value, m_sImageMargin.Right, m_sImageMargin.Bottom });
		}

		CButton *CButton::setImageMarginRight(const size_t value)
		{
			return setImageMargin({ m_sImageMargin.Left, m_sImageMargin.Top, value, m_sImageMargin.Bottom });
		}

		CButton *CButton::setImageMarginBottom(const size_t value)
		{
			return setImageMargin({ m_sImageMargin.Left, m_sImageMargin.Top, m_sImageMargin.Right, value });
		}

		CButton *CButton::setBorderRadius(const size_t value)
		{
			if (value != m_iBorderRadius)
			{
				m_iBorderRadius = value;
				Repaint(false);
			}
			return this;
		}

		CButton *CButton::setBorderOuterWidth(const size_t value)
		{
			if (value != m_iBorderOuterWidth)
			{
				m_iBorderOuterWidth = value;
				Repaint(false);
			}
			return this;
		}

		CButton *CButton::setBorderInnerWidth(const size_t value)
		{
			if (value != m_iBorderInnerWidth)
			{
				m_iBorderInnerWidth = value;
				Repaint(false);
			}
			return this;
		}

		CButton *CButton::setBorderAntiAliazing(const size_t value)
		{
			if (value != m_iBorderAntiAliazing)
			{
				m_iBorderAntiAliazing = value;
				Repaint(false);
			}
			return this;
		}

		CButton *CButton::setImageList(CImageList *value)
		{
			for (int i = 0; i <= stDisabled; i++)
				m_aStates[i].ImageList = value;
			Repaint(false);
			return this;
		}

		CButton *CButton::setImageList(const STATE state, CImageList *value)
		{
			if (value != m_aStates[state].ImageList)
			{
				m_aStates[state].ImageList = value;
				if (getState() == state)
					Repaint(false);
			}
			return this;
		}

		CButton *CButton::setImageIndex(const int value)
		{
			for (int i = 0; i <= stDisabled; i++)
				m_aStates[i].ImageIndex = value;
			Repaint(false);
			return this;
		}

		CButton *CButton::setImageIndex(const STATE state, const int value)
		{
			if (value != m_aStates[state].ImageIndex)
			{
				m_aStates[state].ImageIndex = value;
				if (getState() == state)
					Repaint(false);
			}
			return this;
		}

		CButton *CButton::setTextColor(const APP_COLOR &value)
		{
			for (int i = 0; i <= stDisabled; i++)
				m_aStates[i].TextColor = value;
			Repaint(false);
			return this;
		}

		CButton *CButton::setTextColor(const STATE state, const APP_COLOR &value)
		{
			if (value != m_aStates[state].TextColor)
			{
				m_aStates[state].TextColor = value;
				if (getState() == state)
					Repaint(false);
			}
			return this;
		}

		CButton *CButton::setShadowColor(const APP_COLOR &value)
		{
			for (int i = 0; i <= stDisabled; i++)
				m_aStates[i].ShadowColor = value;
			Repaint(false);
			return this;
		}

		CButton *CButton::setShadowColor(const STATE state, const APP_COLOR &value)
		{
			if (value != m_aStates[state].ShadowColor)
			{
				m_aStates[state].ShadowColor = value;
				if (getState() == state)
					Repaint(false);
			}
			return this;
		}

		CButton *CButton::setBorderOuterColor(const APP_COLOR &value)
		{
			for (int i = 0; i <= stDisabled; i++)
				m_aStates[i].BorderOuterColor = value;
			Repaint(false);
			return this;
		}

		CButton *CButton::setBorderOuterColor(const STATE state, const APP_COLOR &value)
		{
			if (value != m_aStates[state].BorderOuterColor)
			{
				m_aStates[state].BorderOuterColor = value;
				if (getState() == state)
					Repaint(false);
			}
			return this;
		}

		CButton *CButton::setBorderInnerColor(const APP_COLOR &value)
		{
			for (int i = 0; i <= stDisabled; i++)
				m_aStates[i].BorderInnerColor = value;
			Repaint(false);
			return this;
		}

		CButton *CButton::setBorderInnerColor(const STATE state, const APP_COLOR &value)
		{
			if (value != m_aStates[state].BorderInnerColor)
			{
				m_aStates[state].BorderInnerColor = value;
				if (getState() == state)
					Repaint(false);
			}
			return this;
		}

		CButton *CButton::setBackgroundColor(const APP_COLOR &value)
		{
			for (int i = 0; i <= stDisabled; i++)
				m_aStates[i].BackgroundColor = value;
			Repaint(false);
			return this;
		}

		CButton *CButton::setBackgroundColor(const STATE state, const APP_COLOR &value)
		{
			if (value != m_aStates[state].BackgroundColor)
			{
				m_aStates[state].BackgroundColor = value;
				if (getState() == state)
					Repaint(false);
			}
			return this;
		}

		CButton *CButton::setGradientType(const IImage::GRADIENT_TYPE value)
		{
			for (int i = 0; i <= stDisabled; i++)
				m_aStates[i].GradientType = value;
			Repaint(false);
			return this;
		}

		CButton *CButton::setGradientType(const STATE state, const IImage::GRADIENT_TYPE value)
		{
			if (value != m_aStates[state].GradientType)
			{
				m_aStates[state].GradientType = value;
				if (getState() == state && m_aStates[state].GradientPointCount > 0)
					Repaint(false);
			}
			return this;
		}

		CButton *CButton::setGradientPointCount(const size_t value)
		{
			if (value == 0 || value >= 2)
			{
				for (int i = 0; i <= stDisabled; i++)
					m_aStates[i].setGradientPointCount(value);
				Repaint(false);
			}
			return this;
		}

		CButton *CButton::setGradientPointCount(const STATE state, const size_t value)
		{
			if (value == 0 || value >= 2)
				if (value != m_aStates[state].GradientPointCount)
				{
					m_aStates[state].setGradientPointCount(value);
					if (getState() == state)
						Repaint(false);
				}
			return this;
		}

		CButton *CButton::setGradientPointPosition(const size_t index, const double value)
		{
			if (value >= 0 && value <= 1)
			{
				for (int i = 0; i <= stDisabled; i++)
					if (index < m_aStates[i].GradientPointCount)
					{
						m_aStates[i].GradientPoints[index].Position = value;
						m_aStates[i].GradientPointsSorted = false;
					}
				Repaint(false);
			}
			return this;
		}

		CButton *CButton::setGradientPointPosition(const STATE state, const size_t index, const double value)
		{
			if (value >= 0 && value <= 1 && index < m_aStates[state].GradientPointCount && m_aStates[state].GradientPoints[index].Position != value)
			{
				m_aStates[state].GradientPoints[index].Position = value;
				m_aStates[state].GradientPointsSorted = false;
				if (getState() == state)
					Repaint(false);
			}
			return this;
		}

		CButton *CButton::setGradientPointColor(const size_t index, const APP_COLOR &value)
		{
			for (int i = 0; i <= stDisabled; i++)
				if (index < m_aStates[i].GradientPointCount)
					m_aStates[i].GradientPoints[index].Color = value;
			Repaint(false);
			return this;
		}

		CButton *CButton::setGradientPointColor(const STATE state, const size_t index, const APP_COLOR &value)
		{
			if (index < m_aStates[state].GradientPointCount && m_aStates[state].GradientPoints[index].Color != value)
			{
				m_aStates[state].GradientPoints[index].Color = value;
				if (getState() == state)
					Repaint(false);
			}
			return this;
		}

		CButton *CButton::setGradientPoints(const size_t count, IImage::GRADIENT_POINT *points)
		{
			if (count == 0 || (count >= 2 && points))
			{
				for (int i = 0; i <= stDisabled; i++)
				{
					m_aStates[i].setGradientPointCount(count);
					for (size_t j = 0; j < count; j++)
						m_aStates[i].GradientPoints[j] = points[j];
					m_aStates[i].GradientPointsSorted = false;
				}
				Repaint(false);
			}
			return this;
		}

		CButton *CButton::setGradientPoints(const STATE state, const size_t count, IImage::GRADIENT_POINT *points)
		{
			if (count == 0 || (count >= 2 && points))
			{
				m_aStates[state].setGradientPointCount(count);
				for (size_t j = 0; j < count; j++)
					m_aStates[state].GradientPoints[j] = points[j];
				m_aStates[state].GradientPointsSorted = false;
				if (getState() == state)
					Repaint(false);
			}
			return this;
		}

		CButton *CButton::setOnClick(FOnClick value)
		{
			m_fOnClick = value;
			return this;
		}
	#pragma endregion

	#pragma region Notifications
		void CButton::NotifyOnBeforeDetachComponentFromForm(CComponent *component)
		{
			bool changed{ false };
			for (int i= 0; i <= stDisabled; i++)
				if (m_aStates[i].ImageList == component)
				{
					m_aStates[i].ImageList = nullptr;
					if (getState() == i)
						changed = true;
				}
			if (changed)
				Repaint(false);
			CControl::NotifyOnBeforeDetachComponentFromForm(component);
		}

		void CButton::NotifyOnUpdateComponent(CComponent *component)
		{
			for (int i = 0; i <= stDisabled; i++)
				if (m_aStates[i].ImageList == component && getState() == i)
				{
					Repaint(false);
					break;
				}
			CControl::NotifyOnUpdateComponent(component);
		}

		bool CButton::NotifyOnKeyDown(const IWindow::KEY key)
		{
			if (key == IWindow::keyReturn && !m_bIsActive)
			{
				m_bIsActive = true;
				Repaint(false);
			}
			return CControl::NotifyOnKeyDown(key);
		}

		bool CButton::NotifyOnKeyUp(const IWindow::KEY key)
		{
			if (key == IWindow::keyReturn && m_bIsActive)
			{
				m_bIsActive = false;
				Repaint(false);
				NotifyOnClick();
			}
			return CControl::NotifyOnKeyUp(key);
		}

		bool CButton::NotifyOnMouseMove(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			CControl::NotifyOnMouseMove(x, y, ctrl, left, middle, right, shift);
			return true;
		}

		bool CButton::NotifyOnLeftMouseButtonDown(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			m_bIsActive = true;
			m_pForm->CaptureMouse(this);
			Repaint(false);
			CControl::NotifyOnLeftMouseButtonDown(x, y, ctrl, left, middle, right, shift);
			return true;
		}

		bool CButton::NotifyOnLeftMouseButtonUp(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			if (m_bIsActive)
			{
				m_bIsActive = false;
				Repaint(false);
				APP_RECT rect = getVisibleRect();
				if (x >= rect.Left && x < rect.Right && y >= rect.Top && y < rect.Bottom)
					NotifyOnClick();
			}
			if (m_pForm->getCaptureMouseControl() == this)
				m_pForm->ReleaseCaptureMouse();
			CControl::NotifyOnLeftMouseButtonUp(x, y, ctrl, left, middle, right, shift);
			return true;
		}

		bool CButton::NotifyOnLeftMouseButtonDoubleClick(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			if (m_bIsActive)
			{
				m_bIsActive = false;
				Repaint(false);
			}
			if (m_pForm->getCaptureMouseControl() == this)
				m_pForm->ReleaseCaptureMouse();
			CControl::NotifyOnLeftMouseButtonDoubleClick(x, y, ctrl, left, middle, right, shift);
			return true;
		}

		bool CButton::NotifyOnRightMouseButtonDown(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			if (m_bIsActive)
			{
				m_bIsActive = false;
				Repaint(false);
			}
			if (m_pForm->getCaptureMouseControl() == this)
				m_pForm->ReleaseCaptureMouse();
			CControl::NotifyOnRightMouseButtonDown(x, y, ctrl, left, middle, right, shift);
			return true;
		}

		bool CButton::NotifyOnRightMouseButtonUp(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			if (m_bIsActive)
			{
				m_bIsActive = false;
				Repaint(false);
			}
			if (m_pForm->getCaptureMouseControl() == this)
				m_pForm->ReleaseCaptureMouse();
			CControl::NotifyOnRightMouseButtonUp(x, y, ctrl, left, middle, right, shift);
			return true;
		}

		bool CButton::NotifyOnRightMouseButtonDoubleClick(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			if (m_bIsActive)
			{
				m_bIsActive = false;
				Repaint(false);
			}
			if (m_pForm->getCaptureMouseControl() == this)
				m_pForm->ReleaseCaptureMouse();
			CControl::NotifyOnRightMouseButtonDoubleClick(x, y, ctrl, left, middle, right, shift);
			return true;
		}

		bool CButton::NotifyOnMiddleMouseButtonDown(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			if (m_bIsActive)
			{
				m_bIsActive = false;
				Repaint(false);
			}
			if (m_pForm->getCaptureMouseControl() == this)
				m_pForm->ReleaseCaptureMouse();
			CControl::NotifyOnMiddleMouseButtonDown(x, y, ctrl, left, middle, right, shift);
			return true;
		}

		bool CButton::NotifyOnMiddleMouseButtonUp(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			if (m_bIsActive)
			{
				m_bIsActive = false;
				Repaint(false);
			}
			if (m_pForm->getCaptureMouseControl() == this)
				m_pForm->ReleaseCaptureMouse();
			CControl::NotifyOnMiddleMouseButtonUp(x, y, ctrl, left, middle, right, shift);
			return true;
		}

		bool CButton::NotifyOnMiddleMouseButtonDoubleClick(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			if (m_bIsActive)
			{
				m_bIsActive = false;
				Repaint(false);
			}
			if (m_pForm->getCaptureMouseControl() == this)
				m_pForm->ReleaseCaptureMouse();
			CControl::NotifyOnMiddleMouseButtonDoubleClick(x, y, ctrl, left, middle, right, shift);
			return true;
		}

		bool CButton::NotifyOnMouseVerticalWheel(const int x, const int y, const int delta, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			CControl::NotifyOnMouseVerticalWheel(x, y, delta, ctrl, left, middle, right, shift);
			return true;
		}

		bool CButton::NotifyOnMouseHorizontalWheel(const int x, const int y, const int delta, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			CControl::NotifyOnMouseHorizontalWheel(x, y, delta, ctrl, left, middle, right, shift);
			return true;
		}

		void CButton::NotifyOnKillCaptureMouse()
		{
			m_pForm->getWindow()->ReleaseMouseCapture();
			CControl::NotifyOnKillCaptureMouse();
		}

		void CButton::NotifyOnSetCaptureMouse()
		{
			m_pForm->getWindow()->CaptureMouse();
			CControl::NotifyOnSetCaptureMouse();
		}

		void CButton::NotifyOnMouseHover()
		{
			Repaint(false);
			CControl::NotifyOnMouseHover();
		}

		void CButton::NotifyOnMouseLeave()
		{
			Repaint(false);
			CControl::NotifyOnMouseLeave();
		}

		void CButton::NotifyOnKillFocus()
		{
			Repaint(false);
			CControl::NotifyOnKillFocus();
		}

		void CButton::NotifyOnSetFocus(CControl *old)
		{
			Repaint(false);
			CControl::NotifyOnSetFocus(old);
		}

		void CButton::NotifyOnResetFocus()
		{
			Repaint(false);
			CControl::NotifyOnResetFocus();
		}

		void CButton::NotifyOnPaint(APP_RECT clip)
		{
			clip *= getVisibleRect();
			if (!clip.IsEmpty())
			{
				APP_RECT rect = ClientToForm(getRect());
				PaintBorderOuter(clip, rect);
				PaintBorderInner(clip, rect);
				PaintBackground(clip, rect);
				PaintCaption(clip, rect);
				PaintImage(clip, rect);
			}
			CControl::NotifyOnPaint(clip);
		}

		void CButton::NotifyOnClick()
		{
			if (m_fOnClick)
				m_fOnClick(this, getCallbackParam());
		}
	#pragma endregion

	#pragma region Helpers
		bool CButton::UpdateFromStyle()
		{
			if (!getStyle())
				return false;
			m_aStates[stNormal].TextColor = getStyle()->getParameterByName(m_sClassName + L".Normal.TextColor", m_aStates[stNormal].TextColor);
			m_aStates[stNormal].ShadowColor = getStyle()->getParameterByName(m_sClassName + L".Normal.ShadowColor", m_aStates[stNormal].ShadowColor);
			m_aStates[stNormal].BorderOuterColor = getStyle()->getParameterByName(m_sClassName + L".Normal.BorderOuterColor", m_aStates[stNormal].BorderOuterColor);
			m_aStates[stNormal].BorderInnerColor = getStyle()->getParameterByName(m_sClassName + L".Normal.BorderInnerColor", m_aStates[stNormal].BorderInnerColor);
			m_aStates[stNormal].BackgroundColor = getStyle()->getParameterByName(m_sClassName + L".Normal.BackgroundColor", m_aStates[stNormal].BackgroundColor);
			// Normal
			m_aStates[stNormal].GradientType = (IImage::GRADIENT_TYPE)getStyle()->getParameterByName(m_sClassName + L".Normal.GradientType", (int)m_aStates[stNormal].GradientType);
			m_aStates[stNormal].setGradientPointCount(getStyle()->getParameterByName(m_sClassName + L".Normal.GradientPointCount", m_aStates[stNormal].GradientPointCount));
			for (size_t i = 0; i <= m_aStates[stNormal].GradientPointCount; i++)
			{
				m_aStates[stNormal].GradientPoints[i].Position = getStyle()->getParameterByName(m_sClassName + L".Normal.GradientPoints[" + ToString(i) + L"].Position", m_aStates[stNormal].GradientPoints[i].Position);
				m_aStates[stNormal].GradientPoints[i].Color = getStyle()->getParameterByName(m_sClassName + L".Normal.GradientPoints[" + ToString(i) + L"].Color", m_aStates[stNormal].GradientPoints[i].Color);
			}
			m_aStates[stNormal].GradientPointsSorted = false;
			// Normal hovered
			m_aStates[stNormalHovered].GradientType = (IImage::GRADIENT_TYPE)getStyle()->getParameterByName(m_sClassName + L".Normal.Hovered.GradientType", (int)m_aStates[stNormalHovered].GradientType);
			m_aStates[stNormalHovered].setGradientPointCount(getStyle()->getParameterByName(m_sClassName + L".Normal.Hovered.GradientPointCount", m_aStates[stNormalHovered].GradientPointCount));
			for (size_t i = 0; i <= m_aStates[stNormalHovered].GradientPointCount; i++)
			{
				m_aStates[stNormalHovered].GradientPoints[i].Position = getStyle()->getParameterByName(m_sClassName + L".Normal.Hovered.GradientPoints[" + ToString(i) + L"].Position", m_aStates[stNormalHovered].GradientPoints[i].Position);
				m_aStates[stNormalHovered].GradientPoints[i].Color = getStyle()->getParameterByName(m_sClassName + L".Normal.Hovered.GradientPoints[" + ToString(i) + L"].Color", m_aStates[stNormalHovered].GradientPoints[i].Color);
			}
			m_aStates[stNormalHovered].GradientPointsSorted = false;
			// Focused
			m_aStates[stFocused].GradientType = (IImage::GRADIENT_TYPE)getStyle()->getParameterByName(m_sClassName + L".Focused.GradientType", (int)m_aStates[stFocused].GradientType);
			m_aStates[stFocused].setGradientPointCount(getStyle()->getParameterByName(m_sClassName + L".Focused.GradientPointCount", m_aStates[stFocused].GradientPointCount));
			for (size_t i = 0; i <= m_aStates[stFocused].GradientPointCount; i++)
			{
				m_aStates[stFocused].GradientPoints[i].Position = getStyle()->getParameterByName(m_sClassName + L".Focused.GradientPoints[" + ToString(i) + L"].Position", m_aStates[stFocused].GradientPoints[i].Position);
				m_aStates[stFocused].GradientPoints[i].Color = getStyle()->getParameterByName(m_sClassName + L".Focused.GradientPoints[" + ToString(i) + L"].Color", m_aStates[stFocused].GradientPoints[i].Color);
			}
			m_aStates[stFocused].GradientPointsSorted = false;
			// Focused hovered
			m_aStates[stFocusedHovered].GradientType = (IImage::GRADIENT_TYPE)getStyle()->getParameterByName(m_sClassName + L".Focused.Hovered.GradientType", (int)m_aStates[stFocusedHovered].GradientType);
			m_aStates[stFocusedHovered].setGradientPointCount(getStyle()->getParameterByName(m_sClassName + L".Focused.Hovered.GradientPointCount", m_aStates[stFocusedHovered].GradientPointCount));
			for (size_t i = 0; i <= m_aStates[stFocusedHovered].GradientPointCount; i++)
			{
				m_aStates[stFocusedHovered].GradientPoints[i].Position = getStyle()->getParameterByName(m_sClassName + L".Focused.Hovered.GradientPoints[" + ToString(i) + L"].Position", m_aStates[stFocusedHovered].GradientPoints[i].Position);
				m_aStates[stFocusedHovered].GradientPoints[i].Color = getStyle()->getParameterByName(m_sClassName + L".Focused.Hovered.GradientPoints[" + ToString(i) + L"].Color", m_aStates[stFocusedHovered].GradientPoints[i].Color);
			}
			m_aStates[stFocusedHovered].GradientPointsSorted = false;
			// Active
			m_aStates[stActive].GradientType = (IImage::GRADIENT_TYPE)getStyle()->getParameterByName(m_sClassName + L".Active.GradientType", (int)m_aStates[stActive].GradientType);
			m_aStates[stActive].setGradientPointCount(getStyle()->getParameterByName(m_sClassName + L".Active.GradientPointCount", m_aStates[stActive].GradientPointCount));
			for (size_t i = 0; i <= m_aStates[stActive].GradientPointCount; i++)
			{
				m_aStates[stActive].GradientPoints[i].Position = getStyle()->getParameterByName(m_sClassName + L".Active.GradientPoints[" + ToString(i) + L"].Position", m_aStates[stActive].GradientPoints[i].Position);
				m_aStates[stActive].GradientPoints[i].Color = getStyle()->getParameterByName(m_sClassName + L".Active.GradientPoints[" + ToString(i) + L"].Color", m_aStates[stActive].GradientPoints[i].Color);
			}
			m_aStates[stActive].GradientPointsSorted = false;
			// Disabled
			m_aStates[stDisabled].GradientType = (IImage::GRADIENT_TYPE)getStyle()->getParameterByName(m_sClassName + L".Disabled.GradientType", (int)m_aStates[stDisabled].GradientType);
			m_aStates[stDisabled].setGradientPointCount(getStyle()->getParameterByName(m_sClassName + L".Disabled.GradientPointCount", m_aStates[stDisabled].GradientPointCount));
			for (size_t i = 0; i <= m_aStates[stDisabled].GradientPointCount; i++)
			{
				m_aStates[stDisabled].GradientPoints[i].Position = getStyle()->getParameterByName(m_sClassName + L".Disabled.GradientPoints[" + ToString(i) + L"].Position", m_aStates[stDisabled].GradientPoints[i].Position);
				m_aStates[stDisabled].GradientPoints[i].Color = getStyle()->getParameterByName(m_sClassName + L".Disabled.GradientPoints[" + ToString(i) + L"].Color", m_aStates[stDisabled].GradientPoints[i].Color);
			}
			m_aStates[stDisabled].GradientPointsSorted = false;

			return true;
		}

		bool CButton::SearchImage(APP_IMAGE **image, APP_RECT &rect)
		{
			STATE state{ getState() };
			if (!m_aStates[state].ImageList || m_aStates[state].ImageIndex < 0)
				return false;
			*image = m_aStates[state].ImageList->getImage(m_aStates[state].ImageIndex);
			if (!(*image))
				return false;
			rect = { 0, 0, (int)(*image)->getWidth(), (int)(*image)->getHeight() };
			return rect.Width() > 0 && rect.Height() > 0;
		}
	#pragma endregion

	#pragma region Paint
		void CButton::PaintBorderOuter(APP_RECT clip, APP_RECT &rect)
		{
			if (m_iBorderOuterWidth > 0 && !rect.IsEmpty())
			{
				STATE state{ getState() };
				if (m_aStates[state].BorderOuterColor.getAlpha() > 0)
				{
					math::RECTANGLE<size_t> border{ m_iBorderOuterWidth, m_iBorderOuterWidth, m_iBorderOuterWidth, m_iBorderOuterWidth };
					math::RECTANGLE<size_t> radius{ m_iBorderRadius, m_iBorderRadius, m_iBorderRadius, m_iBorderRadius };
					m_pForm->getPresenter()->RenderBorder(graphics::bplLeft, m_aStates[state].BorderOuterColor, clip, rect, border, radius, m_iBorderAntiAliazing, nullptr, nullptr, true);
					m_pForm->getPresenter()->RenderBorder(graphics::bplTop, m_aStates[state].BorderOuterColor, clip, rect, border, radius, m_iBorderAntiAliazing, nullptr, nullptr, true);
					m_pForm->getPresenter()->RenderBorder(graphics::bplRight, m_aStates[state].BorderOuterColor, clip, rect, border, radius, m_iBorderAntiAliazing, nullptr, nullptr, true);
					m_pForm->getPresenter()->RenderBorder(graphics::bplBottom, m_aStates[state].BorderOuterColor, clip, rect, border, radius, m_iBorderAntiAliazing, nullptr, nullptr, true);
				}
				rect.Left += (int)m_iBorderOuterWidth;
				rect.Top += (int)m_iBorderOuterWidth;
				rect.Right -= (int)m_iBorderOuterWidth;
				rect.Bottom -= (int)m_iBorderOuterWidth;
				if (!rect.IsValid())
				{
					rect.Right = rect.Left;
					rect.Bottom = rect.Top;
				}
			}
		}

		void CButton::PaintBorderInner(APP_RECT clip, APP_RECT &rect)
		{
			if (m_iBorderInnerWidth > 0 && !rect.IsEmpty())
			{
				STATE state{ getState() };
				if (m_aStates[state].BorderInnerColor.getAlpha() > 0)
				{
					math::RECTANGLE<size_t> border{ m_iBorderInnerWidth, m_iBorderInnerWidth, m_iBorderInnerWidth, m_iBorderInnerWidth };
					math::RECTANGLE<size_t> radius{ m_iBorderRadius, m_iBorderRadius, m_iBorderRadius, m_iBorderRadius };
					m_pForm->getPresenter()->RenderBorder(graphics::bplLeft, m_aStates[state].BorderInnerColor, clip, rect, border, radius, m_iBorderAntiAliazing, nullptr, nullptr, true);
					m_pForm->getPresenter()->RenderBorder(graphics::bplTop, m_aStates[state].BorderInnerColor, clip, rect, border, radius, m_iBorderAntiAliazing, nullptr, nullptr, true);
					m_pForm->getPresenter()->RenderBorder(graphics::bplRight, m_aStates[state].BorderInnerColor, clip, rect, border, radius, m_iBorderAntiAliazing, nullptr, nullptr, true);
					m_pForm->getPresenter()->RenderBorder(graphics::bplBottom, m_aStates[state].BorderInnerColor, clip, rect, border, radius, m_iBorderAntiAliazing, nullptr, nullptr, true);
				}
				rect.Left += (int)m_iBorderInnerWidth;
				rect.Top += (int)m_iBorderInnerWidth;
				rect.Right -= (int)m_iBorderInnerWidth;
				rect.Bottom -= (int)m_iBorderInnerWidth;
				if (!rect.IsValid())
				{
					rect.Right = rect.Left;
					rect.Bottom = rect.Top;
				}
			}
		}

		void CButton::PaintBackground(APP_RECT clip, APP_RECT &rect)
		{
			if (!rect.IsEmpty())
			{
				STATE state{ getState() };
				if (m_aStates[state].GradientPointCount > 0)
				{
					m_aStates[state].SortGradientPoints();
					m_pForm->getPresenter()->RenderGradient(m_aStates[state].GradientType, m_aStates[state].GradientPointCount, m_aStates[state].GradientPoints, graphics::bplInside, clip,
						rect, rect, { 0, 0, 0, 0 }, { m_iBorderRadius, m_iBorderRadius, m_iBorderRadius, m_iBorderRadius }, m_iBorderAntiAliazing, nullptr, nullptr, true);
				}
				else if (m_aStates[state].BackgroundColor.getAlpha() > 0)
					m_pForm->getPresenter()->FillRect(m_aStates[state].BackgroundColor, clip, rect, rect, { 0, 0, 0, 0 }, { m_iBorderRadius, m_iBorderRadius, m_iBorderRadius, m_iBorderRadius },
						m_iBorderAntiAliazing, graphics::bplInside, nullptr, nullptr, true);
			}
		}

		void CButton::PaintCaption(APP_RECT clip, const APP_RECT &rect)
		{
			if (!rect.IsEmpty() && !m_sCaption.empty())
			{
				APP_POINT size = getFont()->getStringSize(m_sCaption);
				APP_IMAGE *image;
				APP_RECT image_rect;
				int d{ 0 };
				if (SearchImage(&image, image_rect))
				{
					size.X += image_rect.Width() + m_sImageMargin.Left + m_sImageMargin.Right;
					if (m_eImageAlign == ialLeft)
						d = image_rect.Width() + m_sImageMargin.Left + m_sImageMargin.Right;
				}
				int x{ rect.Left }, y{ rect.Top };
				switch (m_eCaptionHorizontalAlign)
				{
				case taRight:
					x = rect.Right - size.X;
					break;
				case taCenter:
					x = rect.Left + (rect.Width() - size.X) / 2;
					break;
				}
				switch (m_eCaptionVerticalAlign)
				{
				case vaBottom:
					y = rect.Bottom - size.Y;
					break;
				case vaMiddle:
					y = rect.Top + (rect.Height() - size.Y) / 2;
					break;
				}
				APP_COLOR text{ getFont()->getColor() }, shadow{ getFont()->getShadowColor() };
				STATE state{ getState() };
				if (m_aStates[state].TextColor.getAlpha() > 0)
					text = m_aStates[state].TextColor;
				if (m_aStates[state].ShadowColor.getAlpha() > 0)
					shadow = m_aStates[state].ShadowColor;
				m_pForm->getPresenter()->RenderString(m_sCaption, getFont(), x + d, y, 0, 1, 1, clip, 0, rect, { 0, 0, 0, 0 }, { m_iBorderRadius, m_iBorderRadius, m_iBorderRadius, m_iBorderRadius },
					m_iBorderAntiAliazing, graphics::bplInside, true, true, text, shadow, nullptr, nullptr, true);
			}
		}

		void CButton::PaintImage(APP_RECT clip, const APP_RECT &rect)
		{
			if (!rect.IsEmpty())
			{
				STATE state{ getState() };
				APP_IMAGE *image;
				APP_RECT image_rect;
				if (SearchImage(&image, image_rect))
				{
					APP_POINT size = getFont()->getStringSize(m_sCaption);
					int d{ m_eImageAlign == ialLeft ? 0 : size.X };
					size.X += image_rect.Width() + m_sImageMargin.Left + m_sImageMargin.Right;
					int x{ rect.Left }, y{ rect.Top };
					switch (m_eCaptionHorizontalAlign)
					{
					case taRight:
						x = rect.Right - size.X;
						break;
					case taCenter:
						x = rect.Left + (rect.Width() - size.X) / 2;
						break;
					}
					switch (m_eCaptionVerticalAlign)
					{
					case vaBottom:
						y = rect.Bottom - image_rect.Height() - (int)m_sImageMargin.Top - (int)m_sImageMargin.Bottom;
						break;
					case vaMiddle:
						y = rect.Top + (rect.Height() - image_rect.Height() - (int)m_sImageMargin.Top - (int)m_sImageMargin.Bottom) / 2;
						break;
					}
					APP_RECT new_clip{ x + d + (int)m_sImageMargin.Left, y + (int)m_sImageMargin.Top, x + d + (int)m_sImageMargin.Left + image_rect.Width(), y + (int)m_sImageMargin.Top + image_rect.Height() };
					IImage *img{ m_pForm->getImageManager()->getImage(image) };
					if (img)
						m_pForm->getPresenter()->RenderImage(img, image_rect, new_clip.Left, new_clip.Top, 0, 1, 1, false, false, false, new_clip,
							rect, { 0, 0, 0, 0 }, { m_iBorderRadius, m_iBorderRadius, m_iBorderRadius, m_iBorderRadius }, m_iBorderAntiAliazing, graphics::bplInside, nullptr, nullptr, true);
				}
			}
		}
	#pragma endregion
	}
}