// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#include "DropDown.h"
#include "..\..\..\ImageManager.h"
#include "..\..\..\Presenter.h"
#include "..\..\..\DefaultStyle.h"
#include "..\..\..\Style.h"
#include "..\..\..\StyleSkin.h"
#include "..\..\..\StyleImage.h"

namespace licui
{
	namespace application
	{
	#pragma region Constructors
		CDropDown::CDropDown() :CControl(),
			m_bEditable{ true },
			m_sPadding{ 4, 2, 2, 2 },
			m_sBorderWidth{ 1, 1, 1, 1 },
			m_sBorderRadius{ 2, 2, 2, 2 },
			m_iBorderAntiAliazing{ 0 },
			m_eArrowAlign{ aalRight },
			m_sArrowPadding{ 3, 3, 3, 3 },
			m_sArrowBorderWidth{ 1, 1, 1, 1 },
			m_sArrowBorderRadius{ 0, 2, 2, 0 },
			m_iArrowBorderAntiAliazing{ 0 },
			m_bArrowHovered{ false }
		{
			m_sClassName = L"CDropDown";
			m_bAcceptForm = true;
			m_bAcceptParent = true;
			m_bAcceptFocus = true;
			m_bTabStop = true;
			m_sInitialRect = { 0, 0, 145, 21 };
			FillStyles();

			m_bAcceptControls = true;
			new CDropDownEdit(this);
			new CDropDownListBox(this);
			m_bAcceptControls = false;
		}

		CDropDown::CDropDown(CForm *form) : CDropDown()
		{
			setForm(form);
		}

		CDropDown::CDropDown(CControl *parent) : CDropDown()
		{
			setParent(parent);
		}

		CDropDown::~CDropDown()
		{
			DeleteControls();
		}

		void CDropDown::FillStyles()
		{
			// Non-editable
			m_aStyle[stNormal][0].BorderColor = { 112, 112, 112, 255 };
			m_aStyle[stNormal][0].BackgroundColor = { 0, 0, 0, 0 };
			m_aStyle[stNormal][0].GradientType = IImage::gtVertical;
			m_aStyle[stNormal][0].GradientPointCount = 4;
			m_aStyle[stNormal][0].GradientPoints = new IImage::GRADIENT_POINT[4];
			m_aStyle[stNormal][0].GradientPoints[0] = { 0, { 242, 242, 242, 255} };
			m_aStyle[stNormal][0].GradientPoints[1] = { 0.499, { 235, 235, 235, 255 } };
			m_aStyle[stNormal][0].GradientPoints[2] = { 0.5, { 221, 221, 221, 255 } };
			m_aStyle[stNormal][0].GradientPoints[3] = { 1.0, { 207, 207, 207, 255 } };
			m_aStyle[stNormal][0].GradientPointsSorted = true;
			m_aStyle[stNormal][0].Text = { 0, 0, 0, 255 };
			m_aStyle[stNormal][0].Shadow = { 0, 0, 0, 255 };
			m_aArrowStyle[stNormal][0].BorderColor = { 0, 0, 0, 0 };
			m_aArrowStyle[stNormal][0].BackgroundColor = { 0, 0, 0, 0 };
			m_aArrowStyle[stNormal][0].GradientType = IImage::gtVertical;
			m_aArrowStyle[stNormal][0].GradientPointCount = 4;
			m_aArrowStyle[stNormal][0].GradientPoints = new IImage::GRADIENT_POINT[4];
			m_aArrowStyle[stNormal][0].GradientPoints[0] = { 0, {242, 242, 242, 255} };
			m_aArrowStyle[stNormal][0].GradientPoints[1] = { 0.499,{ 235, 235, 235, 255 } };
			m_aArrowStyle[stNormal][0].GradientPoints[2] = { 0.5,{ 221, 221, 221, 255 } };
			m_aArrowStyle[stNormal][0].GradientPoints[3] = { 1.0,{ 207, 207, 207, 255 } };
			m_aArrowStyle[stNormal][0].GradientPointsSorted = true;

			m_aStyle[stActive][0].BorderColor = { 44, 98, 139, 255 };
			m_aStyle[stActive][0].BackgroundColor = { 0, 0, 0, 0 };
			m_aStyle[stActive][0].GradientType = IImage::gtVertical;
			m_aStyle[stActive][0].GradientPointCount = 4;
			m_aStyle[stActive][0].GradientPoints = new IImage::GRADIENT_POINT[4];
			m_aStyle[stActive][0].GradientPoints[0] = { 0, {222, 237, 246, 255} };
			m_aStyle[stActive][0].GradientPoints[1] = { 0.499,{ 196, 229, 246, 255 } };
			m_aStyle[stActive][0].GradientPoints[2] = { 0.5,{ 152, 209, 239, 255 } };
			m_aStyle[stActive][0].GradientPoints[3] = { 1.0,{ 102, 175, 215, 255 } };
			m_aStyle[stActive][0].GradientPointsSorted = true;
			m_aStyle[stActive][0].Text = { 0, 0, 0, 255 };
			m_aStyle[stActive][0].Shadow = { 0, 0, 0, 255 };
			m_aArrowStyle[stActive][0].BorderColor = { 0, 0, 0, 0 };
			m_aArrowStyle[stActive][0].BackgroundColor = { 0, 0, 0, 0 };
			m_aArrowStyle[stActive][0].GradientType = IImage::gtVertical;
			m_aArrowStyle[stActive][0].GradientPointCount = 4;
			m_aArrowStyle[stActive][0].GradientPoints = new IImage::GRADIENT_POINT[4];
			m_aArrowStyle[stActive][0].GradientPoints[0] = { 0, {222, 237, 246, 255} };
			m_aArrowStyle[stActive][0].GradientPoints[1] = { 0.499,{ 196, 229, 246, 255 } };
			m_aArrowStyle[stActive][0].GradientPoints[2] = { 0.5,{ 152, 209, 239, 255 } };
			m_aArrowStyle[stActive][0].GradientPoints[3] = { 1.0,{ 102, 175, 215, 255 } };
			m_aArrowStyle[stActive][0].GradientPointsSorted = true;

			m_aStyle[stHovered][0].BorderColor = { 60, 127, 177, 255 };
			m_aStyle[stHovered][0].BackgroundColor = { 0, 0, 0, 0 };
			m_aStyle[stHovered][0].GradientType = IImage::gtVertical;
			m_aStyle[stHovered][0].GradientPointCount = 4;
			m_aStyle[stHovered][0].GradientPoints = new IImage::GRADIENT_POINT[4];
			m_aStyle[stHovered][0].GradientPoints[0] = { 0, {234, 246, 253, 255} };
			m_aStyle[stHovered][0].GradientPoints[1] = { 0.499,{ 217, 240, 252, 255 } };
			m_aStyle[stHovered][0].GradientPoints[2] = { 0.5,{ 190, 230, 253, 255 } };
			m_aStyle[stHovered][0].GradientPoints[3] = { 1.0,{ 167, 217, 245, 255 } };
			m_aStyle[stHovered][0].GradientPointsSorted = true;
			m_aStyle[stHovered][0].Text = { 0, 0, 0, 255 };
			m_aStyle[stHovered][0].Shadow = { 0, 0, 0, 255 };
			m_aArrowStyle[stHovered][0].BorderColor = { 0, 0, 0, 0 };
			m_aArrowStyle[stHovered][0].BackgroundColor = { 0, 0, 0, 0 };
			m_aArrowStyle[stHovered][0].GradientType = IImage::gtVertical;
			m_aArrowStyle[stHovered][0].GradientPointCount = 4;
			m_aArrowStyle[stHovered][0].GradientPoints = new IImage::GRADIENT_POINT[4];
			m_aArrowStyle[stHovered][0].GradientPoints[0] = { 0, {234, 246, 253, 255} };
			m_aArrowStyle[stHovered][0].GradientPoints[1] = { 0.499,{ 217, 240, 252, 255 } };
			m_aArrowStyle[stHovered][0].GradientPoints[2] = { 0.5,{ 190, 230, 253, 255 } };
			m_aArrowStyle[stHovered][0].GradientPoints[3] = { 1.0,{ 167, 217, 245, 255 } };
			m_aArrowStyle[stHovered][0].GradientPointsSorted = true;

			m_aStyle[stArrowHovered][0].GradientPointCount = 0;
			m_aStyle[stArrowHovered][0].GradientPoints = nullptr;
			m_aArrowStyle[stArrowHovered][0].BorderColor = { 0, 0, 0, 0 };
			m_aArrowStyle[stArrowHovered][0].BackgroundColor = { 0, 0, 0, 0 };
			m_aArrowStyle[stArrowHovered][0].GradientType = IImage::gtVertical;
			m_aArrowStyle[stArrowHovered][0].GradientPointCount = 4;
			m_aArrowStyle[stArrowHovered][0].GradientPoints = new IImage::GRADIENT_POINT[4];
			m_aArrowStyle[stArrowHovered][0].GradientPoints[0] = { 0,{ 234, 246, 253, 255 } };
			m_aArrowStyle[stArrowHovered][0].GradientPoints[1] = { 0.499,{ 217, 240, 252, 255 } };
			m_aArrowStyle[stArrowHovered][0].GradientPoints[2] = { 0.5,{ 190, 230, 253, 255 } };
			m_aArrowStyle[stArrowHovered][0].GradientPoints[3] = { 1.0,{ 167, 217, 245, 255 } };
			m_aArrowStyle[stArrowHovered][0].GradientPointsSorted = true;

			m_aStyle[stOpened][0].BorderColor = { 44, 98, 139, 255 };
			m_aStyle[stOpened][0].BackgroundColor = { 0, 0, 0, 0 };
			m_aStyle[stOpened][0].GradientType = IImage::gtVertical;
			m_aStyle[stOpened][0].GradientPointCount = 4;
			m_aStyle[stOpened][0].GradientPoints = new IImage::GRADIENT_POINT[4];
			m_aStyle[stOpened][0].GradientPoints[0] = { 0,{ 222, 237, 246, 255 } };
			m_aStyle[stOpened][0].GradientPoints[1] = { 0.499,{ 196, 229, 246, 255 } };
			m_aStyle[stOpened][0].GradientPoints[2] = { 0.5,{ 152, 209, 239, 255 } };
			m_aStyle[stOpened][0].GradientPoints[3] = { 1.0,{ 102, 175, 215, 255 } };
			m_aStyle[stOpened][0].GradientPointsSorted = true;
			m_aStyle[stOpened][0].Text = { 0, 0, 0, 255 };
			m_aStyle[stOpened][0].Shadow = { 0, 0, 0, 255 };
			m_aArrowStyle[stOpened][0].BorderColor = { 0, 0, 0, 0 };
			m_aArrowStyle[stOpened][0].BackgroundColor = { 0, 0, 0, 0 };
			m_aArrowStyle[stOpened][0].GradientType = IImage::gtVertical;
			m_aArrowStyle[stOpened][0].GradientPointCount = 4;
			m_aArrowStyle[stOpened][0].GradientPoints = new IImage::GRADIENT_POINT[4];
			m_aArrowStyle[stOpened][0].GradientPoints[0] = { 0, {222, 237, 246, 255} };
			m_aArrowStyle[stOpened][0].GradientPoints[1] = { 0.499,{ 196, 229, 246, 255 } };
			m_aArrowStyle[stOpened][0].GradientPoints[2] = { 0.5,{ 152, 209, 239, 255 } };
			m_aArrowStyle[stOpened][0].GradientPoints[3] = { 1.0,{ 102, 175, 215, 255 } };
			m_aArrowStyle[stOpened][0].GradientPointsSorted = true;

			m_aStyle[stDisabled][0].BorderColor = { 173, 178, 181, 255 };
			m_aStyle[stDisabled][0].BackgroundColor = { 244, 244, 244, 255 };
			m_aStyle[stDisabled][0].GradientType = IImage::gtVertical;
			m_aStyle[stDisabled][0].GradientPointCount = 0;
			m_aStyle[stDisabled][0].GradientPoints = nullptr;
			m_aStyle[stDisabled][0].GradientPointsSorted = true;
			m_aStyle[stDisabled][0].Text = { 109, 109, 109, 255 };
			m_aStyle[stDisabled][0].Shadow = { 109, 109, 109, 255 };
			m_aArrowStyle[stDisabled][0].BorderColor = { 0, 0, 0, 0 };
			m_aArrowStyle[stDisabled][0].BackgroundColor = { 0, 0, 0, 0 };
			m_aArrowStyle[stDisabled][0].GradientType = IImage::gtVertical;
			m_aArrowStyle[stDisabled][0].GradientPointCount = 0;
			m_aArrowStyle[stDisabled][0].GradientPoints = nullptr;
			m_aArrowStyle[stDisabled][0].GradientPointsSorted = true;

			// Editable
			m_aStyle[stNormal][1].BorderColor = { 171, 173, 179, 255 };
			m_aStyle[stNormal][1].BackgroundColor = { 255, 255, 255, 255 };
			m_aStyle[stNormal][1].GradientType = IImage::gtVertical;
			m_aStyle[stNormal][1].GradientPointCount = 0;
			m_aStyle[stNormal][1].GradientPoints = nullptr;
			m_aStyle[stNormal][1].GradientPointsSorted = true;
			m_aArrowStyle[stNormal][1].BorderColor = { 0, 0, 0, 0 };
			m_aArrowStyle[stNormal][1].BackgroundColor = { 0, 0, 0, 0 };
			m_aArrowStyle[stNormal][1].GradientType = IImage::gtVertical;
			m_aArrowStyle[stNormal][1].GradientPointCount = 0;
			m_aArrowStyle[stNormal][1].GradientPoints = nullptr;
			m_aArrowStyle[stNormal][1].GradientPointsSorted = true;

			m_aStyle[stActive][1].BorderColor = { 61, 123, 173, 255 };
			m_aStyle[stActive][1].BackgroundColor = { 255, 255, 255, 255 };
			m_aStyle[stActive][1].GradientType = IImage::gtVertical;
			m_aStyle[stActive][1].GradientPointCount = 0;
			m_aStyle[stActive][1].GradientPoints = nullptr;
			m_aStyle[stActive][1].GradientPointsSorted = true;
			m_aArrowStyle[stActive][1].BorderColor = { 0, 0, 0, 0 };
			m_aArrowStyle[stActive][1].BackgroundColor = { 0, 0, 0, 0 };
			m_aArrowStyle[stActive][1].GradientType = IImage::gtVertical;
			m_aArrowStyle[stActive][1].GradientPointCount = 0;
			m_aArrowStyle[stActive][1].GradientPoints = nullptr;
			m_aArrowStyle[stActive][1].GradientPointsSorted = true;

			m_aStyle[stHovered][1].BorderColor = { 87, 148, 191, 255 };
			m_aStyle[stHovered][1].BackgroundColor = { 255, 255, 255, 255 };
			m_aStyle[stHovered][1].GradientType = IImage::gtVertical;
			m_aStyle[stHovered][1].GradientPointCount = 0;
			m_aStyle[stHovered][1].GradientPoints = nullptr;
			m_aStyle[stHovered][1].GradientPointsSorted = true;
			m_aArrowStyle[stHovered][1].BorderColor = { 0, 0, 0, 0 };
			m_aArrowStyle[stHovered][1].BackgroundColor = { 0, 0, 0, 0 };
			m_aArrowStyle[stHovered][1].GradientType = IImage::gtVertical;
			m_aArrowStyle[stHovered][1].GradientPointCount = 0;
			m_aArrowStyle[stHovered][1].GradientPoints = nullptr;
			m_aArrowStyle[stHovered][1].GradientPointsSorted = true;

			m_aStyle[stArrowHovered][1].GradientPointCount = 0;
			m_aStyle[stArrowHovered][1].GradientPoints = nullptr;
			m_aArrowStyle[stArrowHovered][1].BorderColor = { 87, 148, 191, 255 };
			m_aArrowStyle[stArrowHovered][1].BackgroundColor = { 0, 0, 0, 0 };
			m_aArrowStyle[stArrowHovered][1].GradientType = IImage::gtVertical;
			m_aArrowStyle[stArrowHovered][1].GradientPointCount = 4;
			m_aArrowStyle[stArrowHovered][1].GradientPoints = new IImage::GRADIENT_POINT[4];
			m_aArrowStyle[stArrowHovered][1].GradientPoints[0] = { 0, {234, 246, 253, 255} };
			m_aArrowStyle[stArrowHovered][1].GradientPoints[1] = { 0.499,{ 217, 240, 252, 255 } };
			m_aArrowStyle[stArrowHovered][1].GradientPoints[2] = { 0.5,{ 190, 230, 253, 255 } };
			m_aArrowStyle[stArrowHovered][1].GradientPoints[3] = { 1.0,{ 169, 219, 246, 255 } };
			m_aArrowStyle[stArrowHovered][1].GradientPointsSorted = true;

			m_aStyle[stOpened][1].BorderColor = { 61, 123, 173, 255 };
			m_aStyle[stOpened][1].BackgroundColor = { 255, 255, 255, 255 };
			m_aStyle[stOpened][1].GradientType = IImage::gtVertical;
			m_aStyle[stOpened][1].GradientPointCount = 0;
			m_aStyle[stOpened][1].GradientPoints = nullptr;
			m_aStyle[stOpened][1].GradientPointsSorted = true;
			m_aArrowStyle[stOpened][1].BorderColor = { 61, 123, 173, 255 };
			m_aArrowStyle[stOpened][1].BackgroundColor = { 0, 0, 0, 0 };
			m_aArrowStyle[stOpened][1].GradientType = IImage::gtVertical;
			m_aArrowStyle[stOpened][1].GradientPointCount = 4;
			m_aArrowStyle[stOpened][1].GradientPoints = new IImage::GRADIENT_POINT[4];
			m_aArrowStyle[stOpened][1].GradientPoints[0] = { 0, {222, 237, 246, 255} };
			m_aArrowStyle[stOpened][1].GradientPoints[1] = { 0.499,{ 196, 229, 246, 255 } };
			m_aArrowStyle[stOpened][1].GradientPoints[2] = { 0.5,{ 152, 209, 239, 255 } };
			m_aArrowStyle[stOpened][1].GradientPoints[3] = { 1.0,{ 99, 172, 211, 255 } };
			m_aArrowStyle[stOpened][1].GradientPointsSorted = true;

			m_aStyle[stDisabled][1].BorderColor = { 175, 175, 175, 255 };
			m_aStyle[stDisabled][1].BackgroundColor = { 244, 244, 244, 255 };
			m_aStyle[stDisabled][1].GradientType = IImage::gtVertical;
			m_aStyle[stDisabled][1].GradientPointCount = 0;
			m_aStyle[stDisabled][1].GradientPoints = nullptr;
			m_aStyle[stDisabled][1].GradientPointsSorted = true;
			m_aArrowStyle[stDisabled][1].BorderColor = { 0, 0, 0, 0 };
			m_aArrowStyle[stDisabled][1].BackgroundColor = { 0, 0, 0, 0 };
			m_aArrowStyle[stDisabled][1].GradientType = IImage::gtVertical;
			m_aArrowStyle[stDisabled][1].GradientPointCount = 0;
			m_aArrowStyle[stDisabled][1].GradientPoints = nullptr;
			m_aArrowStyle[stDisabled][1].GradientPointsSorted = true;
		}
	#pragma endregion

	#pragma region Helpers
		String CDropDown::getStateName(const STATE state)
		{
			switch (state)
			{
			case stNormal:
				return L".normal";
			case stActive:
				return L".active";
			case stHovered:
				return L".hovered";
			case stOpened:
				return L".opened";
			}
			return L".disabled";
		}

		void CDropDown::ToggleListBox()
		{
			if (getListBox()->getVisible())
			{
				getListBox()->setVisible(false);
				if (m_bEditable)
					getEdit()->setFocus();
				else
					setFocus();
			}
			else
			{
				getListBox()->setPosition({ 0, getHeight() });
				getListBox()->setWidth(getWidth());
				size_t required_height{ getListBox()->m_sItemSize.Y * getListBox()->getItemCount() + getListBox()->m_iBorderWidth * 2 + getListBox()->m_sPadding.Top + getListBox()->m_sPadding.Bottom };
				if (getListBox()->m_sConstraints.Top > 0 && required_height < getListBox()->m_sConstraints.Top)
					required_height = getListBox()->m_sConstraints.Top;
				else if (getListBox()->m_sConstraints.Bottom > 0 && required_height > getListBox()->m_sConstraints.Bottom)
					required_height = getListBox()->m_sConstraints.Bottom;
				getListBox()->setHeight(required_height);
				getListBox()->setVisible(true);
				getListBox()->setFocus();
			}
			Repaint(true);
		}

		void CDropDown::ActivateNextItem()
		{
			if (getListBox()->getItemCount() > 0 && getListBox()->getActiveItemIndex() < (int)getListBox()->getItemCount() - 1)
			{
				getListBox()->setActiveItemIndex(getListBox()->getActiveItemIndex() + 1);
				getEdit()->setText(getListBox()->getActiveItem()->getCaption());
				Repaint(true);
			}
		}

		void CDropDown::ActivatePrevItem()
		{
			if (getListBox()->getItemCount() > 0)
				if (getListBox()->getActiveItemIndex() < 0)
				{
					getListBox()->setActiveItemIndex(getListBox()->getItemCount() - 1);
					getEdit()->setText(getListBox()->getActiveItem()->getCaption());
					Repaint(true);
				}
				else if (getListBox()->getActiveItemIndex() > 0)
				{
					getListBox()->setActiveItemIndex(getListBox()->getActiveItemIndex() - 1);
					getEdit()->setText(getListBox()->getActiveItem()->getCaption());
					Repaint(true);
				}
		}

		APP_RECT CDropDown::CalculateArrowRect()
		{
			APP_RECT rect = CControl::getClientRect(), image_rect;
			APP_IMAGE *image;
			size_t arrow_width;
			if (SearchArrowImage(&image, image_rect, true))
				arrow_width = (size_t)image_rect.Width() + m_sArrowBorderWidth.Left + m_sArrowBorderWidth.Right + m_sArrowPadding.Left + m_sArrowPadding.Right;
			else
				arrow_width = (size_t)getHeight();
			if (m_eArrowAlign == aalLeft)
				rect.Right = std::min(rect.Left + (int)arrow_width, rect.Right);
			else
				rect.Left = std::max(rect.Right - (int)arrow_width, rect.Left);
			if (!rect.IsValid())
			{
				rect.Right = rect.Left;
				rect.Bottom = rect.Top;
			}
			return rect;
		}

		bool CDropDown::SearchArrowImage(APP_IMAGE **image, APP_RECT &rect, const bool ignore_state)
		{
			String name{ m_sClassName + L".Arrow" };
			if (ignore_state)
				name += L".normal";
			else
				name += getStateName(getState());
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

		bool CDropDown::UpdateFromStyle()
		{
			if (!getStyle())
				return false;
			m_sPadding = getStyle()->getParameterByName(m_sClassName + L".Padding", m_sPadding);
			m_sBorderWidth = getStyle()->getParameterByName(m_sClassName + L".BorderWidth", m_sBorderWidth);
			m_sBorderRadius = getStyle()->getParameterByName(m_sClassName + L".BorderRadius", m_sBorderRadius);
			m_iBorderAntiAliazing = getStyle()->getParameterByName(m_sClassName + L".BorderAntiAliazing", m_iBorderAntiAliazing);
			m_eArrowAlign = (ARROW_ALIGN)getStyle()->getParameterByName(m_sClassName + L".Arrow.Align", (int)m_eArrowAlign);
			m_sArrowPadding = getStyle()->getParameterByName(m_sClassName + L".Arrow.Padding", m_sArrowPadding);
			m_sArrowBorderWidth = getStyle()->getParameterByName(m_sClassName + L".Arrow.BorderWidth", m_sArrowBorderWidth);
			m_sArrowBorderRadius = getStyle()->getParameterByName(m_sClassName + L".Arrow.BorderRadius", m_sArrowBorderRadius);
			m_iArrowBorderAntiAliazing = getStyle()->getParameterByName(m_sClassName + L".Arrow.BorderAntiAliazing", m_iArrowBorderAntiAliazing);
			for (int i = 0; i <= stDisabled; i++)
			{
				String name{ getStateName((STATE)i) };
				for (int j = 0; j <= 1; j++)
				{
					String editable{ j == 0 ? L".editable" : L"" };
					m_aStyle[i][j].BorderColor = getStyle()->getParameterByName(m_sClassName + L".BorderColor" + name + editable, m_aStyle[i][j].BorderColor);
					m_aStyle[i][j].BackgroundColor = getStyle()->getParameterByName(m_sClassName + L".BackgroundColor" + name + editable, m_aStyle[i][j].BackgroundColor);
					m_aStyle[i][j].GradientType = (IImage::GRADIENT_TYPE)getStyle()->getParameterByName(m_sClassName + L".GradientType" + name + editable, (int)m_aStyle[i][j].GradientType);
					m_aStyle[i][j].setGradientPointCount(getStyle()->getParameterByName(m_sClassName + L".GradientPointCount" + name + editable, m_aStyle[i][j].GradientPointCount));
					for (size_t k = 0; k <= m_aStyle[i][j].GradientPointCount; k++)
					{
						m_aStyle[i][j].GradientPoints[k].Position = getStyle()->getParameterByName(m_sClassName + L".GradientPoints[" + ToString(k) + L"].Position" + name + editable, m_aStyle[i][j].GradientPoints[k].Position);
						m_aStyle[i][j].GradientPoints[k].Color = getStyle()->getParameterByName(m_sClassName + L".GradientPoints[" + ToString(k) + L"].Color" + name + editable, m_aStyle[i][j].GradientPoints[k].Color);
					}
					m_aStyle[i][j].GradientPointsSorted = false;
					// Arrow
					m_aArrowStyle[i][j].BorderColor = getStyle()->getParameterByName(m_sClassName + L".Arrow.BorderColor" + name + editable, m_aArrowStyle[i][j].BorderColor);
					m_aArrowStyle[i][j].BackgroundColor = getStyle()->getParameterByName(m_sClassName + L".Arrow.BackgroundColor" + name + editable, m_aArrowStyle[i][j].BackgroundColor);
					m_aArrowStyle[i][j].GradientType = (IImage::GRADIENT_TYPE)getStyle()->getParameterByName(m_sClassName + L".Arrow.GradientType" + name + editable, (int)m_aArrowStyle[i][j].GradientType);
					m_aArrowStyle[i][j].setGradientPointCount(getStyle()->getParameterByName(m_sClassName + L".Arrow.GradientPointCount" + name + editable, m_aArrowStyle[i][j].GradientPointCount));
					for (size_t k = 0; k <= m_aArrowStyle[i][j].GradientPointCount; k++)
					{
						m_aArrowStyle[i][j].GradientPoints[k].Position = getStyle()->getParameterByName(m_sClassName + L".Arrow.GradientPoints[" + ToString(k) + L"].Position" + name + editable, m_aArrowStyle[i][j].GradientPoints[k].Position);
						m_aArrowStyle[i][j].GradientPoints[k].Color = getStyle()->getParameterByName(m_sClassName + L".Arrow.GradientPoints[" + ToString(k) + L"].Color" + name + editable, m_aArrowStyle[i][j].GradientPoints[k].Color);
					}
					m_aArrowStyle[i][j].GradientPointsSorted = false;
				}
			}
			return true;
		}
	#pragma endregion

	#pragma region Notifications
		bool CDropDown::NotifyOnKeyDown(const IWindow::KEY key)
		{
			switch (key)
			{
			case IWindow::keyUp:
				ProcessKeyUp();
				break;
			case IWindow::keyDown:
				ProcessKeyDown();
				break;
			case IWindow::keyF4:
				ToggleListBox();
				break;
			}
			return CControl::NotifyOnKeyDown(key);
		}

		bool CDropDown::NotifyOnMouseMove(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			if (m_bEnabled)
			{
				APP_RECT r = ClientToForm(CalculateArrowRect());
				bool hovered{ x >= r.Left&&x < r.Right&&y >= r.Top&&y < r.Bottom };
				if (hovered != m_bArrowHovered && getState() != stOpened)
					Repaint(false);
			}
			return CControl::NotifyOnMouseMove(x, y, ctrl, left, middle, right, shift);
		}

		bool CDropDown::NotifyOnLeftMouseButtonDown(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			if (m_bEnabled)
				ToggleListBox();
			return CControl::NotifyOnLeftMouseButtonDown(x, y, ctrl, left, middle, right, shift);
		}

		bool CDropDown::NotifyOnMouseVerticalWheel(const int x, const int y, const int delta, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			if (m_bEnabled && getListBox()->getItemCount() > 0)
			{
				if (delta > 0)
					ActivateNextItem();
				else
					ActivatePrevItem();
			}
			return CControl::NotifyOnMouseVerticalWheel(x, y, delta, ctrl, left, middle, right, shift);
		}

		void CDropDown::NotifyOnKillFocus()
		{
			Repaint(true);
			CControl::NotifyOnKillFocus();
		}

		void CDropDown::NotifyOnSetFocus(CControl *old)
		{
			Repaint(true);
			CControl::NotifyOnSetFocus(old);
		}

		void CDropDown::NotifyOnResetFocus()
		{
			Repaint(true);
			CControl::NotifyOnResetFocus();
		}

		void CDropDown::NotifyOnMouseHover()
		{
			Repaint(true);
			CControl::NotifyOnMouseHover();
		}

		void CDropDown::NotifyOnMouseLeave()
		{
			Repaint(true);
			CControl::NotifyOnMouseLeave();
		}

		void CDropDown::NotifyOnPaint(APP_RECT clip)
		{
			clip *= getVisibleRect();
			if (!clip.IsEmpty())
			{
				PaintBackground(clip);
				PaintArrow(clip);
				PaintText(clip);
			}
			CControl::NotifyOnPaint(clip);
		}

		void CDropDown::NotifyOnClickItem(CListBoxItem *item)
		{
			getEdit()->setText(item->getCaption());
			getListBox()->setVisible(false);
			if (m_bEditable)
				getEdit()->setFocus();
			else
				setFocus();
			Repaint(true);
		}

		void CDropDown::NotifyOnEditKeyDown()
		{
			ActivateNextItem();
		}

		void CDropDown::NotifyOnEditKeyUp()
		{
			ActivatePrevItem();
		}

		void CDropDown::NotifyOnEditKeyF4()
		{
			ToggleListBox();
		}

		void CDropDown::NotifyOnEditChange()
		{
			getListBox()->setActiveItemIndex(-1);
			for (size_t i = 0; i < getListBox()->getItemCount(); i++)
				if (getListBox()->getItem(i)->getCaption() == getEdit()->getText())
				{
					getListBox()->setActiveItemIndex(i);
					break;
				}
			Repaint(true);
		}
	#pragma endregion

	#pragma region Getters
		CDropDown::CDropDownEdit *CDropDown::getEdit()
		{
			return dynamic_cast<CDropDownEdit*>(getControl(0));
		}

		CDropDown::CDropDownListBox *CDropDown::getListBox()
		{
			return dynamic_cast<CDropDownListBox*>(getControl(1));
		}

		APP_RECT CDropDown::getClientRect()
		{
			APP_RECT rect = CControl::getClientRect(), image_rect;
			APP_IMAGE *image;
			size_t arrow_width;
			if (SearchArrowImage(&image, image_rect, true))
				arrow_width = (size_t)image_rect.Width() + m_sArrowBorderWidth.Left + m_sArrowBorderWidth.Right + m_sArrowPadding.Left + m_sArrowPadding.Right;
			else
				arrow_width = (size_t)getHeight();
			rect.Left += (int)m_sBorderWidth.Left + (int)m_sPadding.Left;
			rect.Top += (int)m_sBorderWidth.Top + (int)m_sPadding.Top;
			rect.Right -= (int)m_sBorderWidth.Right + (int)m_sPadding.Right;
			rect.Bottom -= (int)m_sBorderWidth.Bottom + (int)m_sPadding.Bottom;
			if (m_eArrowAlign == aalLeft)
				rect.Left += (int)arrow_width;
			else
				rect.Right -= (int)arrow_width;
			if (!rect.IsValid())
			{
				rect.Right = rect.Left;
				rect.Bottom = rect.Top;
			}
			return rect;
		}

		CDropDown::STATE CDropDown::getState()
		{
			if (!m_bEnabled)
				return stDisabled;
			if (getListBox()->getVisible())
				return stOpened;
			if (m_pForm)
			{
				if (m_pForm->getActiveControl() == this || m_pForm->getActiveControl() == getEdit() || m_pForm->getActiveControl() == getListBox())
					return stActive;
				if (m_pForm->getHoveredControl() == this || m_pForm->getHoveredControl() == getEdit() || m_pForm->getHoveredControl() == getListBox() ||
					m_pForm->getHoveredControl() == getListBox()->getHScrollBar() || m_pForm->getHoveredControl() == getListBox()->getVScrollBar())
					return stHovered;
			}
			return stNormal;
		}

		bool CDropDown::getEditable() const
		{
			return m_bEditable;
		}

		String CDropDown::getText()
		{
			return getEdit()->getText();
		}

		int CDropDown::getActiveItemIndex()
		{
			return getListBox()->getActiveItemIndex();
		}

		size_t CDropDown::getItemCount()
		{
			return getListBox()->getItemCount();
		}

		String CDropDown::getItem(const size_t index)
		{
			if (index < getListBox()->getItemCount())
				return getListBox()->getItem(index)->getCaption();
			return L"";
		}
	#pragma endregion

	#pragma region Setters
		CDropDown *CDropDown::setEditable(const bool value)
		{
			if (value != m_bEditable)
			{
				m_bEditable = value;
				getEdit()->setVisible(m_bEditable);
				getEdit()->setVisible(false);
			}
			return this;
		}

		CDropDown *CDropDown::setText(const String &value)
		{
			getEdit()->setText(value);
			return this;
		}

		CDropDown *CDropDown::setActiveItemIndex(int value)
		{
			if (m_pForm)
				m_pForm->LockRepaint();
			getListBox()->setActiveItemIndex(value);
			if (getListBox()->getActiveItem())
				getEdit()->setText(getListBox()->getActiveItem()->getCaption());
			else
				getEdit()->setText(L"");
			if (m_pForm)
				m_pForm->UnlockRepaint();
			return this;
		}

		CDropDown *CDropDown::setItem(const size_t index, const String &value)
		{
			if (index < getListBox()->getItemCount())
			{
				if (m_pForm)
					m_pForm->LockRepaint();
				getListBox()->getItem(index)->setCaption(value);
				if (getListBox()->getActiveItemIndex() == (int)index && getListBox()->getActiveItem()->getCaption() != getEdit()->getText())
					getListBox()->setActiveItemIndex(-1);
				if (m_pForm)
					m_pForm->UnlockRepaint();
			}
			return this;
		}
	#pragma endregion

	#pragma region Process events
		void CDropDown::ProcessKeyUp()
		{
			ActivatePrevItem();
		}

		void CDropDown::ProcessKeyDown()
		{
			ActivateNextItem();
		}
	#pragma endregion

	#pragma region Paint
		void CDropDown::PaintBackground(APP_RECT clip)
		{
			STATE state{ getState() };
			APP_COLOR colors[graphics::bplBottom + 1];
			colors[graphics::bplOutside] = { 0, 0, 0, 0 };
			colors[graphics::bplInside] = m_aStyle[state][m_bEditable].BackgroundColor;
			colors[graphics::bplLeft] = m_aStyle[state][m_bEditable].BorderColor;
			colors[graphics::bplTop] = m_aStyle[state][m_bEditable].BorderColor;
			colors[graphics::bplRight] = m_aStyle[state][m_bEditable].BorderColor;
			colors[graphics::bplBottom] = m_aStyle[state][m_bEditable].BorderColor;
			m_pForm->getPresenter()->MultiFillRect(colors, clip, ClientToForm(getRect()), m_sBorderWidth, m_sBorderRadius, m_iBorderAntiAliazing, nullptr, nullptr, true);
			if (m_aStyle[state][m_bEditable].GradientPointCount > 0)
			{
				m_aStyle[state][m_bEditable].SortGradientPoints();
				m_pForm->getPresenter()->RenderGradient(m_aStyle[state][m_bEditable].GradientType, m_aStyle[state][m_bEditable].GradientPointCount, m_aStyle[state][m_bEditable].GradientPoints,
					graphics::bplInside, clip, ClientToForm(getRect()), ClientToForm(getRect()), m_sBorderWidth, m_sBorderRadius, m_iBorderAntiAliazing, nullptr, nullptr, true);
			}
		}

		void CDropDown::PaintArrow(APP_RECT clip)
		{
			APP_RECT rect = ClientToForm(CalculateArrowRect());
			if (!rect.IsEmpty())
			{
				// Background
				STATE state{ getState() };
				int cx, cy;
				if (m_bEnabled && state != stOpened && m_pForm->getHoveredControl() == this && m_pForm->getWindow()->getCursorPosition(cx, cy) &&
					cx >= rect.Left && cx < rect.Right && cy >= rect.Top && cy < rect.Bottom)
				{
					state = stArrowHovered;
					m_bArrowHovered = true;
				}
				else
					m_bArrowHovered = false;
				APP_COLOR colors[graphics::bplBottom + 1];
				colors[graphics::bplOutside] = { 0, 0, 0, 0 };
				colors[graphics::bplInside] = m_aArrowStyle[state][m_bEditable].BackgroundColor;
				colors[graphics::bplLeft] = m_aArrowStyle[state][m_bEditable].BorderColor;
				colors[graphics::bplTop] = m_aArrowStyle[state][m_bEditable].BorderColor;
				colors[graphics::bplRight] = m_aArrowStyle[state][m_bEditable].BorderColor;
				colors[graphics::bplBottom] = m_aArrowStyle[state][m_bEditable].BorderColor;
				m_pForm->getPresenter()->MultiFillRect(colors, clip, rect, m_sArrowBorderWidth, m_sArrowBorderRadius, m_iArrowBorderAntiAliazing, nullptr, nullptr, true);
				if (m_aArrowStyle[state][m_bEditable].GradientPointCount > 0)
				{
					m_aArrowStyle[state][m_bEditable].SortGradientPoints();
					m_pForm->getPresenter()->RenderGradient(m_aArrowStyle[state][m_bEditable].GradientType, m_aArrowStyle[state][m_bEditable].GradientPointCount,
						m_aArrowStyle[state][m_bEditable].GradientPoints, graphics::bplInside, clip, rect, rect, m_sArrowBorderWidth, m_sArrowBorderRadius, m_iArrowBorderAntiAliazing,
						nullptr, nullptr, true);
				}
				// Arrow
				APP_IMAGE *image;
				APP_RECT image_rect;
				if (SearchArrowImage(&image, image_rect, false))
				{
					APP_RECT new_clip{
						rect.Left + (int)m_sArrowBorderWidth.Left + (int)m_sArrowPadding.Left,
						rect.Top + (int)m_sArrowBorderWidth.Top + (int)m_sArrowPadding.Top,
						rect.Right - (int)m_sArrowBorderWidth.Right - (int)m_sArrowPadding.Right,
						rect.Bottom - (int)m_sArrowBorderWidth.Bottom - (int)m_sArrowPadding.Bottom
					};
					new_clip *= clip;
					if (new_clip.IsValid() && !new_clip.IsEmpty())
					{
						IImage *img{ m_pForm->getImageManager()->getImage(image) };
						if (img)
						{
							int x{ new_clip.Left + (new_clip.Width() - (int)image_rect.Width()) / 2 };
							int y{ new_clip.Top + (new_clip.Height() - (int)image_rect.Height()) / 2 };
							m_pForm->getPresenter()->RenderImage(img, image_rect, x, y, 0, 1, 1, false, false, false, new_clip, rect, { 0, 0, 0, 0 }, { 0, 0, 0, 0 },
								0, graphics::bplInside, nullptr, nullptr, true);
						}
					}
				}
			}
		}

		void CDropDown::PaintText(APP_RECT clip)
		{
			if (!m_bEditable && !getEdit()->getText().empty())
			{
				APP_RECT client = ClientToForm(getClientRect());
				if (!client.IsEmpty())
				{
					STATE state{ getState() };
					APP_COLOR text{ getFont()->getColor() }, shadow{ getFont()->getShadowColor() };
					if (m_aStyle[state][0].Text.getAlpha() > 0)
						text = m_aStyle[state][0].Text;
					if (m_aStyle[state][0].Shadow.getAlpha() > 0)
						shadow = m_aStyle[state][0].Shadow;
					APP_POINT size = getFont()->getStringSize(getEdit()->getText());
					int y{ clip.Top + (clip.Height() - size.Y) / 2 };
					m_pForm->getPresenter()->RenderString(getEdit()->getText(), getFont(), client.Left, y, 0, 1, 1, clip, 0, client, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, 0, graphics::bplInside,
						true, true, text, shadow, nullptr, nullptr, true);
				}
			}
		}
	#pragma endregion

	#pragma region Items
		CDropDown *CDropDown::AddItem(const String &name)
		{
			CListBoxItem *item{ new CListBoxItem() };
			item->setCaption(name);
			getListBox()->Add(item);
			return this;
		}

		CDropDown *CDropDown::DeleteItem(const size_t index)
		{
			getListBox()->Delete(index);
			return this;
		}

		CDropDown *CDropDown::DeleteItems()
		{
			getListBox()->DeleteAll();
			return this;
		}
	#pragma endregion
	}
}