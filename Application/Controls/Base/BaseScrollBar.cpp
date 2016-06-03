// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#include "BaseScrollBar.h"
#include "..\..\DefaultStyle.h"
#include "..\..\Style.h"
#include "..\..\StyleSkin.h"
#include "..\..\StyleImage.h"
#include "..\..\Form.h"
#include "..\..\Presenter.h"
#include "..\..\ImageManager.h"

namespace licui
{
	namespace application
	{
		const unsigned int SCROLL_TIMER_INTERVAL{ 250 };

	#pragma region Constructor & destructor
		CBaseScrollBar::CBaseScrollBar():
			m_hTimer{ 0 },
			m_bMouseOverStartArrow{ false },
			m_bMouseOverEndArrow{ false },
			m_bMouseOverScroller{ false },
			m_bMouseDownOnStartArrow{ false },
			m_bMouseDownOnEndArrow{ false },
			m_bMouseDownOnScroller{ false },
			m_bMouseDownBeforeScroller{ false },
			m_bMouseDownAfterScroller{ false },
			m_iMouseDownScrollDelta{ false },
			m_bCancellingDown{ false },
			m_bHovered{ false },
			m_eType{ sbHorizontal },
			m_iMin{ 0 },
			m_iMax{ 100 },
			m_iScroll{ 0 },
			m_iPageSize{ 10 },
			m_iDeltaArrow{ 1 },
			m_iDeltaWheel{ 5 },
			m_iScrollerSize{ 0 },
			m_iBorderWidth{ 1 },
			m_bBoxShadow{ true },
			m_sBoxShadowShift{ -1, -1 },
			m_iBoxShadowRadius{ 0 },
			m_bVisible{ true },
			m_bEnabled{ true }
		{
			InitGradients();
		}

		void CBaseScrollBar::InitGradients()
		{
			// Start arrow
			m_aElements[etStartArrow].BorderWidth = 1;
			m_aElements[etStartArrow].BorderRadius = 1;
			m_aElements[etStartArrow].State[estNormal].BackgroundColor = { 0, 0, 0, 0 };
			m_aElements[etStartArrow].State[estActive].BackgroundColor = { 0, 0, 0, 0 };
			m_aElements[etStartArrow].State[estHovered].BackgroundColor = { 0, 0, 0, 0 };
			m_aElements[etStartArrow].State[estOver].BackgroundColor = { 0, 0, 0, 0 };
			m_aElements[etStartArrow].State[estDisabled].BackgroundColor = { 0, 0, 0, 0 };
			m_aElements[etStartArrow].State[estNormal].BorderColor = { 0, 0, 0, 0 };
			m_aElements[etStartArrow].State[estActive].BorderColor = { 24, 89, 138, 255 };
			m_aElements[etStartArrow].State[estHovered].BorderColor = { 151, 151, 151, 255 };
			m_aElements[etStartArrow].State[estOver].BorderColor = { 60, 127, 177, 255 };
			m_aElements[etStartArrow].State[estDisabled].BorderColor = { 0, 0, 0, 0 };
			m_aElements[etStartArrow].State[estNormal].GradientType = IImage::gtVertical;
			m_aElements[etStartArrow].State[estActive].GradientType = IImage::gtVertical;
			m_aElements[etStartArrow].State[estHovered].GradientType = IImage::gtVertical;
			m_aElements[etStartArrow].State[estOver].GradientType = IImage::gtVertical;
			m_aElements[etStartArrow].State[estDisabled].GradientType = IImage::gtVertical;
			m_aElements[etStartArrow].State[estNormal].GradientPointCount = 0;
			m_aElements[etStartArrow].State[estActive].GradientPointCount = 4;
			m_aElements[etStartArrow].State[estHovered].GradientPointCount = 4;
			m_aElements[etStartArrow].State[estOver].GradientPointCount = 4;
			m_aElements[etStartArrow].State[estDisabled].GradientPointCount = 0;
			m_aElements[etStartArrow].State[estNormal].GradientPoints = nullptr;
			m_aElements[etStartArrow].State[estActive].GradientPoints = new IImage::GRADIENT_POINT[4];
			m_aElements[etStartArrow].State[estHovered].GradientPoints = new IImage::GRADIENT_POINT[4];
			m_aElements[etStartArrow].State[estOver].GradientPoints = new IImage::GRADIENT_POINT[4];
			m_aElements[etStartArrow].State[estDisabled].GradientPoints = nullptr;
			m_aElements[etStartArrow].State[estNormal].GradientPointsSorted = true;
			m_aElements[etStartArrow].State[estActive].GradientPointsSorted = true;
			m_aElements[etStartArrow].State[estHovered].GradientPointsSorted = true;
			m_aElements[etStartArrow].State[estOver].GradientPointsSorted = true;
			m_aElements[etStartArrow].State[estDisabled].GradientPointsSorted = true;
			m_aElements[etStartArrow].State[estActive].GradientPoints[0] = { 0,{ 231, 246, 252, 255 } };
			m_aElements[etStartArrow].State[estActive].GradientPoints[1] = { 0.499,{ 175, 225, 247, 255 } };
			m_aElements[etStartArrow].State[estActive].GradientPoints[2] = { 0.5,{ 111, 202, 240, 255 } };
			m_aElements[etStartArrow].State[estActive].GradientPoints[3] = { 1.0,{ 158, 199, 217, 255 } };
			m_aElements[etStartArrow].State[estHovered].GradientPoints[0] = { 0,{ 245, 245, 245, 255 } };
			m_aElements[etStartArrow].State[estHovered].GradientPoints[1] = { 0.499,{ 233, 233, 235, 255 } };
			m_aElements[etStartArrow].State[estHovered].GradientPoints[2] = { 0.5,{ 217, 217, 219, 255 } };
			m_aElements[etStartArrow].State[estHovered].GradientPoints[3] = { 1.0,{ 191, 192, 195, 255 } };
			m_aElements[etStartArrow].State[estOver].GradientPoints[0] = { 0,{ 227, 244, 252, 255 } };
			m_aElements[etStartArrow].State[estOver].GradientPoints[1] = { 0.499,{ 214, 238, 251, 255 } };
			m_aElements[etStartArrow].State[estOver].GradientPoints[2] = { 0.5,{ 169, 219, 246, 255 } };
			m_aElements[etStartArrow].State[estOver].GradientPoints[3] = { 1.0,{ 156, 202, 227, 255 } };

			// End arrow
			m_aElements[etEndArrow].BorderWidth = 1;
			m_aElements[etEndArrow].BorderRadius = 1;
			m_aElements[etEndArrow].State[estNormal].BackgroundColor = { 0, 0, 0, 0 };
			m_aElements[etEndArrow].State[estActive].BackgroundColor = { 0, 0, 0, 0 };
			m_aElements[etEndArrow].State[estHovered].BackgroundColor = { 0, 0, 0, 0 };
			m_aElements[etEndArrow].State[estOver].BackgroundColor = { 0, 0, 0, 0 };
			m_aElements[etEndArrow].State[estDisabled].BackgroundColor = { 0, 0, 0, 0 };
			m_aElements[etEndArrow].State[estNormal].BorderColor = { 0, 0, 0, 0 };
			m_aElements[etEndArrow].State[estActive].BorderColor = { 24, 89, 138, 255 };
			m_aElements[etEndArrow].State[estHovered].BorderColor = { 151, 151, 151, 255 };
			m_aElements[etEndArrow].State[estOver].BorderColor = { 60, 127, 177, 255 };
			m_aElements[etEndArrow].State[estDisabled].BorderColor = { 0, 0, 0, 0 };
			m_aElements[etEndArrow].State[estNormal].GradientType = IImage::gtVertical;
			m_aElements[etEndArrow].State[estActive].GradientType = IImage::gtVertical;
			m_aElements[etEndArrow].State[estHovered].GradientType = IImage::gtVertical;
			m_aElements[etEndArrow].State[estOver].GradientType = IImage::gtVertical;
			m_aElements[etEndArrow].State[estDisabled].GradientType = IImage::gtVertical;
			m_aElements[etEndArrow].State[estNormal].GradientPointCount = 0;
			m_aElements[etEndArrow].State[estActive].GradientPointCount = 4;
			m_aElements[etEndArrow].State[estHovered].GradientPointCount = 4;
			m_aElements[etEndArrow].State[estOver].GradientPointCount = 4;
			m_aElements[etEndArrow].State[estDisabled].GradientPointCount = 0;
			m_aElements[etEndArrow].State[estNormal].GradientPoints = nullptr;
			m_aElements[etEndArrow].State[estActive].GradientPoints = new IImage::GRADIENT_POINT[4];
			m_aElements[etEndArrow].State[estHovered].GradientPoints = new IImage::GRADIENT_POINT[4];
			m_aElements[etEndArrow].State[estOver].GradientPoints = new IImage::GRADIENT_POINT[4];
			m_aElements[etEndArrow].State[estDisabled].GradientPoints = nullptr;
			m_aElements[etEndArrow].State[estNormal].GradientPointsSorted = true;
			m_aElements[etEndArrow].State[estActive].GradientPointsSorted = true;
			m_aElements[etEndArrow].State[estHovered].GradientPointsSorted = true;
			m_aElements[etEndArrow].State[estOver].GradientPointsSorted = true;
			m_aElements[etEndArrow].State[estDisabled].GradientPointsSorted = true;
			m_aElements[etEndArrow].State[estActive].GradientPoints[0] = { 0,{ 231, 246, 252, 255 } };
			m_aElements[etEndArrow].State[estActive].GradientPoints[1] = { 0.499,{ 175, 225, 247, 255 } };
			m_aElements[etEndArrow].State[estActive].GradientPoints[2] = { 0.5,{ 111, 202, 240, 255 } };
			m_aElements[etEndArrow].State[estActive].GradientPoints[3] = { 1.0,{ 158, 199, 217, 255 } };
			m_aElements[etEndArrow].State[estHovered].GradientPoints[0] = { 0,{ 245, 245, 245, 255 } };
			m_aElements[etEndArrow].State[estHovered].GradientPoints[1] = { 0.499,{ 233, 233, 235, 255 } };
			m_aElements[etEndArrow].State[estHovered].GradientPoints[2] = { 0.5,{ 217, 217, 219, 255 } };
			m_aElements[etEndArrow].State[estHovered].GradientPoints[3] = { 1.0,{ 191, 192, 195, 255 } };
			m_aElements[etEndArrow].State[estOver].GradientPoints[0] = { 0,{ 227, 244, 252, 255 } };
			m_aElements[etEndArrow].State[estOver].GradientPoints[1] = { 0.499,{ 214, 238, 251, 255 } };
			m_aElements[etEndArrow].State[estOver].GradientPoints[2] = { 0.5,{ 169, 219, 246, 255 } };
			m_aElements[etEndArrow].State[estOver].GradientPoints[3] = { 1.0,{ 156, 202, 227, 255 } };

			// Scroller
			m_aElements[etScroller].BorderWidth = 1;
			m_aElements[etScroller].BorderRadius = 1;
			m_aElements[etScroller].State[estNormal].BackgroundColor = { 0, 0, 0, 0 };
			m_aElements[etScroller].State[estActive].BackgroundColor = { 0, 0, 0, 0 };
			m_aElements[etScroller].State[estHovered].BackgroundColor = { 0, 0, 0, 0 };
			m_aElements[etScroller].State[estOver].BackgroundColor = { 0, 0, 0, 0 };
			m_aElements[etScroller].State[estDisabled].BackgroundColor = { 0, 0, 0, 0 };
			m_aElements[etScroller].State[estNormal].BorderColor = { 151, 151, 151, 255 };
			m_aElements[etScroller].State[estActive].BorderColor = { 24, 89, 138, 255 };
			m_aElements[etScroller].State[estHovered].BorderColor = { 151, 151, 151, 255 };
			m_aElements[etScroller].State[estOver].BorderColor = { 60, 127, 177, 255 };
			m_aElements[etScroller].State[estDisabled].BorderColor = { 0, 0, 0, 0 };
			m_aElements[etScroller].State[estNormal].GradientType = IImage::gtVertical;
			m_aElements[etScroller].State[estActive].GradientType = IImage::gtVertical;
			m_aElements[etScroller].State[estHovered].GradientType = IImage::gtVertical;
			m_aElements[etScroller].State[estOver].GradientType = IImage::gtVertical;
			m_aElements[etScroller].State[estDisabled].GradientType = IImage::gtVertical;
			m_aElements[etScroller].State[estNormal].GradientPointCount = 4;
			m_aElements[etScroller].State[estActive].GradientPointCount = 4;
			m_aElements[etScroller].State[estHovered].GradientPointCount = 4;
			m_aElements[etScroller].State[estOver].GradientPointCount = 4;
			m_aElements[etScroller].State[estDisabled].GradientPointCount = 0;
			m_aElements[etScroller].State[estNormal].GradientPoints = new IImage::GRADIENT_POINT[4];
			m_aElements[etScroller].State[estActive].GradientPoints = new IImage::GRADIENT_POINT[4];
			m_aElements[etScroller].State[estHovered].GradientPoints = new IImage::GRADIENT_POINT[4];
			m_aElements[etScroller].State[estOver].GradientPoints = new IImage::GRADIENT_POINT[4];
			m_aElements[etScroller].State[estDisabled].GradientPoints = nullptr;
			m_aElements[etScroller].State[estNormal].GradientPointsSorted = true;
			m_aElements[etScroller].State[estActive].GradientPointsSorted = true;
			m_aElements[etScroller].State[estHovered].GradientPointsSorted = true;
			m_aElements[etScroller].State[estOver].GradientPointsSorted = true;
			m_aElements[etScroller].State[estDisabled].GradientPointsSorted = true;
			m_aElements[etScroller].State[estNormal].GradientPoints[0] = { 0,{ 245, 245, 245, 255 } };
			m_aElements[etScroller].State[estNormal].GradientPoints[1] = { 0.499,{ 233, 233, 235, 255 } };
			m_aElements[etScroller].State[estNormal].GradientPoints[2] = { 0.5,{ 217, 217, 219, 255 } };
			m_aElements[etScroller].State[estNormal].GradientPoints[3] = { 1.0,{ 191, 192, 195, 255 } };
			m_aElements[etScroller].State[estActive].GradientPoints[0] = { 0,{ 231, 246, 252, 255 } };
			m_aElements[etScroller].State[estActive].GradientPoints[1] = { 0.499,{ 175, 225, 247, 255 } };
			m_aElements[etScroller].State[estActive].GradientPoints[2] = { 0.5,{ 111, 202, 240, 255 } };
			m_aElements[etScroller].State[estActive].GradientPoints[3] = { 1.0,{ 158, 199, 217, 255 } };
			m_aElements[etScroller].State[estHovered].GradientPoints[0] = { 0,{ 245, 245, 245, 255 } };
			m_aElements[etScroller].State[estHovered].GradientPoints[1] = { 0.499,{ 233, 233, 235, 255 } };
			m_aElements[etScroller].State[estHovered].GradientPoints[2] = { 0.5,{ 217, 217, 219, 255 } };
			m_aElements[etScroller].State[estHovered].GradientPoints[3] = { 1.0,{ 191, 192, 195, 255 } };
			m_aElements[etScroller].State[estOver].GradientPoints[0] = { 0,{ 227, 244, 252, 255 } };
			m_aElements[etScroller].State[estOver].GradientPoints[1] = { 0.499,{ 214, 238, 251, 255 } };
			m_aElements[etScroller].State[estOver].GradientPoints[2] = { 0.5,{ 169, 219, 246, 255 } };
			m_aElements[etScroller].State[estOver].GradientPoints[3] = { 1.0,{ 156, 202, 227, 255 } };

			m_aBackground[stNormal].BackgroundColor = { 240, 240, 240, 255 };
			m_aBackground[stNormal].BorderColor = { 255, 255, 255, 255 };
			m_aBackground[stNormal].BoxShadowColor = { 160, 160, 160, 255 };
			m_aBackground[stNormal].GradientType = IImage::gtVertical;
			m_aBackground[stNormal].GradientPointCount = 3;
			m_aBackground[stNormal].GradientPoints = new IImage::GRADIENT_POINT[3];
			m_aBackground[stNormal].GradientPointsSorted = true;
			m_aBackground[stNormal].GradientPoints[0] = { 0.0,{ 227, 227, 227, 255 } };
			m_aBackground[stNormal].GradientPoints[1] = { 0.5,{ 240, 240, 240, 255 } };
			m_aBackground[stNormal].GradientPoints[2] = { 1.0,{ 234, 234, 234, 255 } };

			m_aBackground[stActive].BackgroundColor = { 240, 240, 240, 255 };
			m_aBackground[stActive].BorderColor = { 255, 255, 255, 255 };
			m_aBackground[stActive].BoxShadowColor = { 160, 160, 160, 255 };
			m_aBackground[stActive].GradientType = IImage::gtVertical;
			m_aBackground[stActive].GradientPointCount = 3;
			m_aBackground[stActive].GradientPoints = new IImage::GRADIENT_POINT[3];
			m_aBackground[stActive].GradientPointsSorted = true;
			m_aBackground[stActive].GradientPoints[0] = { 0.0,{ 227, 227, 227, 255 } };
			m_aBackground[stActive].GradientPoints[1] = { 0.5,{ 240, 240, 240, 255 } };
			m_aBackground[stActive].GradientPoints[2] = { 1.0,{ 234, 234, 234, 255 } };

			m_aBackground[stHovered].BackgroundColor = { 240, 240, 240, 255 };
			m_aBackground[stHovered].BorderColor = { 255, 255, 255, 255 };
			m_aBackground[stHovered].BoxShadowColor = { 160, 160, 160, 255 };
			m_aBackground[stHovered].GradientType = IImage::gtVertical;
			m_aBackground[stHovered].GradientPointCount = 3;
			m_aBackground[stHovered].GradientPoints = new IImage::GRADIENT_POINT[3];
			m_aBackground[stHovered].GradientPointsSorted = true;
			m_aBackground[stHovered].GradientPoints[0] = { 0.0,{ 227, 227, 227, 255 } };
			m_aBackground[stHovered].GradientPoints[1] = { 0.5,{ 240, 240, 240, 255 } };
			m_aBackground[stHovered].GradientPoints[2] = { 1.0,{ 234, 234, 234, 255 } };

			m_aBackground[stDisabled].BackgroundColor = { 240, 240, 240, 255 };
			m_aBackground[stDisabled].BorderColor = { 255, 255, 255, 255 };
			m_aBackground[stDisabled].BoxShadowColor = { 160, 160, 160, 255 };
			m_aBackground[stDisabled].GradientType = IImage::gtVertical;
			m_aBackground[stDisabled].GradientPointCount = 3;
			m_aBackground[stDisabled].GradientPoints = new IImage::GRADIENT_POINT[3];
			m_aBackground[stDisabled].GradientPointsSorted = true;
			m_aBackground[stDisabled].GradientPoints[0] = { 0.0,{ 227, 227, 227, 255 } };
			m_aBackground[stDisabled].GradientPoints[1] = { 0.5,{ 240, 240, 240, 255 } };
			m_aBackground[stDisabled].GradientPoints[2] = { 1.0,{ 234, 234, 234, 255 } };
		}
	#pragma endregion

	#pragma region Helpers
		bool CBaseScrollBar::SearchElementImage(const ELEMENT_TYPE type, APP_IMAGE **image, APP_RECT &rect, const bool ignore_state)
		{
			String name{ getClassName() };
			switch (type)
			{
			case etStartArrow:
				name += L".Arrow.Start";
				break;
			case etEndArrow:
				name += L".Arrow.End";
				break;
			case etScroller:
				name += L".Scroller";
				break;
			}
			if (m_eType == sbHorizontal)
				name += L".Horizontal";
			else
				name += L".Vertical";
			if (ignore_state)
				name += L".normal";
			else
				name += ElementStateToString(getElementState(type));
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

		APP_RECT CBaseScrollBar::CalculateStartArrowRect()
		{
			APP_RECT result = getRect();
			result.Left += (int)m_iBorderWidth;
			result.Top += (int)m_iBorderWidth;
			if (m_eType == sbHorizontal)
			{
				result.Bottom -= (int)m_iBorderWidth;
				result.Right = result.Left + result.Height();
			}
			else
			{
				result.Right -= (int)m_iBorderWidth;
				result.Bottom = result.Top + result.Width();
			}
			if (!result.IsValid())
			{
				result.Right = result.Left;
				result.Bottom = result.Top;
			}
			return result;
		}

		APP_RECT CBaseScrollBar::CalculateEndArrowRect()
		{
			APP_RECT result = getRect();
			result.Right -= (int)m_iBorderWidth;
			result.Bottom -= (int)m_iBorderWidth;
			if (m_eType == sbHorizontal)
			{
				result.Top += (int)m_iBorderWidth;
				result.Left = result.Right - result.Height();
			}
			else
			{
				result.Left += (int)m_iBorderWidth;
				result.Top = result.Bottom - result.Width();
			}
			if (!result.IsValid())
			{
				result.Right = result.Left;
				result.Bottom = result.Top;
			}
			return result;
		}

		APP_RECT CBaseScrollBar::CalculateScrollerRect()
		{
			if ((int)m_iPageSize > m_iMax - m_iMin)
				return{ 0, 0, 0, 0 };
			APP_RECT rect_start = CalculateStartArrowRect(), rect_end = CalculateEndArrowRect();
			int d;
			if (m_eType == sbHorizontal)
				d = rect_end.Left - rect_start.Right;
			else
				d = rect_end.Top - rect_start.Bottom;
			if (d <= 0)
				return{ 0, 0, 0, 0 };
			size_t size{ m_iScrollerSize == 0 ? (size_t)std::max(1, (int)((double)d * (1.0 - ((double)m_iMax - (double)m_iMin - (double)m_iPageSize) / ((double)m_iMax - (double)m_iMin)))) : (size_t)std::min((int)m_iScrollerSize, m_iMax - m_iMin - 1) };
			APP_RECT result;
			d = d - (int)size;
			if (m_eType == sbHorizontal)
			{
				result.Left = rect_start.Right + (int)((double)d * (double)m_iScroll / ((double)m_iMax - (double)m_iMin));
				result.Top = rect_start.Top;
				result.Right = result.Left + size;
				result.Bottom = rect_start.Bottom;
				if (result.Right > rect_end.Left)
					return{ 0, 0, 0, 0 };
			}
			else
			{
				result.Left = rect_start.Left;
				result.Top = rect_start.Bottom + (int)((double)d * (double)m_iScroll / ((double)m_iMax - (double)m_iMin));
				result.Right = rect_start.Right;
				result.Bottom = result.Top + size;
				if (result.Bottom > rect_end.Top)
					return{ 0, 0, 0, 0 };
			}
			return result;
		}

		APP_RECT CBaseScrollBar::CalculateBeforeScrollerRect()
		{
			APP_RECT rect_start = CalculateStartArrowRect(), rect_scroller = CalculateScrollerRect();
			if (rect_start.IsEmpty() || rect_scroller.IsEmpty())
				return{ 0, 0, 0, 0 };
			APP_RECT result;
			if (m_eType == sbHorizontal)
			{
				result.Left = rect_start.Right;
				result.Top = rect_start.Top;
				result.Right = rect_scroller.Left;
				result.Bottom = rect_start.Bottom;
			}
			else
			{
				result.Left = rect_start.Left;
				result.Top = rect_start.Bottom;
				result.Right = rect_start.Right;
				result.Bottom = rect_scroller.Top;
			}
			return result;
		}

		APP_RECT CBaseScrollBar::CalculateAfterScrollerRect()
		{
			APP_RECT rect_end = CalculateEndArrowRect(), rect_scroller = CalculateScrollerRect();
			if (rect_end.IsEmpty() || rect_scroller.IsEmpty())
				return{ 0, 0, 0, 0 };
			APP_RECT result;
			if (m_eType == sbHorizontal)
			{
				result.Left = rect_scroller.Right;
				result.Top = rect_scroller.Top;
				result.Right = rect_end.Left;
				result.Bottom = rect_scroller.Bottom;
			}
			else
			{
				result.Left = rect_scroller.Left;
				result.Top = rect_scroller.Bottom;
				result.Right = rect_scroller.Right;
				result.Bottom = rect_end.Top;
			}
			return result;
		}

		void CBaseScrollBar::TimerCallback(void *param)
		{
			CBaseScrollBar *scrollbar{ (CBaseScrollBar*)param };
			if (scrollbar->getForm() && scrollbar->getForm()->getWindow())
			{
				int x, y;
				if (scrollbar->getForm()->getWindow()->getCursorPosition(x, y))
				{
					if (scrollbar->m_bMouseDownOnStartArrow)
					{
						APP_RECT rect = scrollbar->ClientToForm(scrollbar->CalculateStartArrowRect());
						if (x >= rect.Left && x < rect.Right && y >= rect.Top && y < rect.Bottom && scrollbar->m_iScroll > scrollbar->m_iMin)
						{
							scrollbar->m_iScroll -= 1;
							scrollbar->NotifyOnChange();
						}
					}
					else if (scrollbar->m_bMouseDownOnEndArrow)
					{
						APP_RECT rect = scrollbar->ClientToForm(scrollbar->CalculateEndArrowRect());
						if (x >= rect.Left && x < rect.Right && y >= rect.Top && y < rect.Bottom && scrollbar->m_iScroll < scrollbar->m_iMax)
						{
							scrollbar->m_iScroll += 1;
							scrollbar->NotifyOnChange();
						}
					}
					else if (scrollbar->m_bMouseDownBeforeScroller)
					{
						APP_RECT rect = scrollbar->ClientToForm(scrollbar->CalculateBeforeScrollerRect());
						if (x >= rect.Left && x < rect.Right && y >= rect.Top && y < rect.Bottom && scrollbar->m_iScroll > scrollbar->m_iMin)
						{
							scrollbar->m_iScroll = std::max(scrollbar->m_iMin, scrollbar->m_iScroll - (int)scrollbar->m_iPageSize);
							scrollbar->NotifyOnChange();
						}
					}
					else if (scrollbar->m_bMouseDownAfterScroller)
					{
						APP_RECT rect = scrollbar->ClientToForm(scrollbar->CalculateAfterScrollerRect());
						if (x >= rect.Left && x < rect.Right && y >= rect.Top && y < rect.Bottom && scrollbar->m_iScroll < scrollbar->m_iMax)
						{
							scrollbar->m_iScroll = std::min(scrollbar->m_iMax, scrollbar->m_iScroll + (int)scrollbar->m_iPageSize);
							scrollbar->NotifyOnChange();
						}
					}
				}
			}
		}

		int CBaseScrollBar::MouseToScroll(const int x, const int y)
		{
			APP_RECT start = ClientToForm(CalculateStartArrowRect()), end = ClientToForm(CalculateEndArrowRect()), scroller = ClientToForm(CalculateScrollerRect());
			int scroll_min{ m_eType == sbHorizontal ? start.Right : start.Bottom }, scroll_max{ m_eType == sbHorizontal ? (end.Left - scroller.Width()) : (end.Top - scroller.Height()) };
			int scroll_value{ (m_eType == sbHorizontal ? x : y) - scroll_min };
			return scroll_value * (m_iMax - m_iMin) / (scroll_max - scroll_min + 1);
		}

		String CBaseScrollBar::StateToString(const STATE state)
		{
			switch (state)
			{
			case stNormal:
				return L".normal";
			case stActive:
				return L".active";
			case stHovered:
				return L".hovered";
			}
			return L".disabled";
		}

		String CBaseScrollBar::ElementStateToString(const ELEMENT_STATE state)
		{
			switch (state)
			{
			case estNormal:
				return L".normal";
			case estActive:
				return L".active";
			case estHovered:
				return L".hovered";
			case estOver:
				return L".over";
			}
			return L".disabled";
		}

		bool CBaseScrollBar::UpdateFromStyle()
		{
			if (!getStyle())
				return false;
			m_iScrollerSize = getStyle()->getParameterByName(getClassName() + L".ScrollerSize", m_iScrollerSize);
			m_iBorderWidth = getStyle()->getParameterByName(getClassName() + L".BorderWidth", m_iBorderWidth);
			m_bBoxShadow = getStyle()->getParameterByName(getClassName() + L".BoxShadow", m_bBoxShadow);
			m_sBoxShadowShift = getStyle()->getParameterByName(getClassName() + L".BoxShadowShift", m_sBoxShadowShift);
			m_iBoxShadowRadius = getStyle()->getParameterByName(getClassName() + L".BoxShadowRadius", m_iBoxShadowRadius);
			for (int i = 0; i <= stDisabled; i++)
			{
				String name{ StateToString((STATE)i) };
				m_aBackground[i].BackgroundColor = getStyle()->getParameterByName(getClassName() + L".BackgroundColor" + name, m_aBackground[i].BackgroundColor);
				m_aBackground[i].BorderColor = getStyle()->getParameterByName(getClassName() + L".BorderColor" + name, m_aBackground[i].BorderColor);
				m_aBackground[i].BoxShadowColor = getStyle()->getParameterByName(getClassName() + L".BoxShadowColor" + name, m_aBackground[i].BoxShadowColor);

				m_aBackground[i].GradientType = (IImage::GRADIENT_TYPE)getStyle()->getParameterByName(getClassName() + L"GradientType" + name, (int)m_aBackground[i].GradientType);
				m_aBackground[i].setGradientPointCount(getStyle()->getParameterByName(getClassName() + L".GradientPointCount" + name, m_aBackground[i].GradientPointCount));
				for (size_t j = 0; j <= m_aBackground[i].GradientPointCount; j++)
				{
					m_aBackground[i].GradientPoints[j].Position = getStyle()->getParameterByName(getClassName() + L".GradientPoints[" + ToString(j) + L"].Position" + name, m_aBackground[i].GradientPoints[j].Position);
					m_aBackground[i].GradientPoints[j].Color = getStyle()->getParameterByName(getClassName() + L".GradientPoints[" + ToString(j) + L"].Color" + name, m_aBackground[i].GradientPoints[j].Color);
				}
				m_aBackground[i].GradientPointsSorted = false;
			}
			for (int i = 0; i <= etScroller; i++)
			{
				String element{ i == etStartArrow ? L".Arrow.Start" : (i == etEndArrow ? L".Arrow.End" : L".Scroller") };
				m_aElements[i].BorderWidth = getStyle()->getParameterByName(getClassName() + element + L".BorderWidth", m_aElements[i].BorderWidth);
				m_aElements[i].BorderRadius = getStyle()->getParameterByName(getClassName() + element + L".BorderRadius", m_aElements[i].BorderRadius);
				m_aElements[i].BorderAntiAliazing = getStyle()->getParameterByName(getClassName() + element + L".BorderAntiAliazing", m_aElements[i].BorderAntiAliazing);
				for (int j = 0; j <= estDisabled; j++)
				{
					String name{ ElementStateToString((ELEMENT_STATE)j) };
					m_aElements[i].State[j].BackgroundColor = getStyle()->getParameterByName(getClassName() + element + L".BackgroundColor" + name, m_aElements[i].State[j].BackgroundColor);
					m_aElements[i].State[j].BorderColor = getStyle()->getParameterByName(getClassName() + element + L".BorderColor" + name, m_aElements[i].State[j].BorderColor);
					m_aElements[i].State[j].GradientType = (IImage::GRADIENT_TYPE)getStyle()->getParameterByName(getClassName() + element + L".GradientType" + name, (int)m_aElements[i].State[j].GradientType);
					m_aElements[i].State[j].setGradientPointCount(getStyle()->getParameterByName(getClassName() + element + L".GradientPointCount" + name, m_aElements[i].State[j].GradientPointCount));
					for (size_t k = 0; k <= m_aElements[i].State[j].GradientPointCount; k++)
					{
						m_aElements[i].State[j].GradientPoints[k].Position = getStyle()->getParameterByName(getClassName() + element + L".GradientPoints[" + ToString(k) + L"].Position" + name, m_aElements[i].State[j].GradientPoints[k].Position);
						m_aElements[i].State[j].GradientPoints[k].Color = getStyle()->getParameterByName(getClassName() + element + L".GradientPoints[" + ToString(k) + L"].Color" + name, m_aElements[i].State[j].GradientPoints[k].Color);
					}
					m_aElements[i].State[j].GradientPointsSorted = false;
				}
			}

			return true;
		}
	#pragma endregion

	#pragma region Paint
		void CBaseScrollBar::PaintBackground(APP_RECT clip)
		{
			STATE state{ getState() };
			APP_RECT rect = ClientToForm(getRect());
			// Shadow
			if (m_bBoxShadow && m_aBackground[state].BoxShadowColor.getAlpha() > 0)
				getForm()->getPresenter()->BoxBlur(m_aBackground[state].BoxShadowColor, m_sBoxShadowShift.X, m_sBoxShadowShift.Y, m_iBoxShadowRadius, clip, rect, { 0, 0, 0, 0 }, 0, nullptr, nullptr, true);
			// Background + border
			if (m_aBackground[state].GradientPointCount > 1)
			{
				math::RECTANGLE<size_t> borders{ m_iBorderWidth, m_iBorderWidth, m_iBorderWidth, m_iBorderWidth };
				if (m_iBorderWidth > 0)
				{
					getForm()->getPresenter()->RenderBorder(graphics::bplLeft, m_aBackground[state].BorderColor, clip, rect, borders, { 0, 0, 0, 0 }, 0, nullptr, nullptr, true);
					getForm()->getPresenter()->RenderBorder(graphics::bplTop, m_aBackground[state].BorderColor, clip, rect, borders, { 0, 0, 0, 0 }, 0, nullptr, nullptr, true);
					getForm()->getPresenter()->RenderBorder(graphics::bplRight, m_aBackground[state].BorderColor, clip, rect, borders, { 0, 0, 0, 0 }, 0, nullptr, nullptr, true);
					getForm()->getPresenter()->RenderBorder(graphics::bplBottom, m_aBackground[state].BorderColor, clip, rect, borders, { 0, 0, 0, 0 }, 0, nullptr, nullptr, true);
				}
				m_aBackground[state].SortGradientPoints();
				getForm()->getPresenter()->RenderGradient(m_aBackground[state].GradientType, m_aBackground[state].GradientPointCount, m_aBackground[state].GradientPoints, graphics::bplInside,
					clip, rect, rect, borders, { 0, 0, 0, 0 }, 0, nullptr, nullptr, true);
			}
			else if (m_aBackground[state].BorderColor.getAlpha() > 0 || m_aBackground[state].BackgroundColor.getAlpha() > 0)
			{
				APP_COLOR colors[graphics::bplBottom + 1];
				colors[graphics::bplOutside] = { 0, 0, 0, 0 };
				colors[graphics::bplInside] = m_aBackground[state].BackgroundColor;
				colors[graphics::bplLeft] = m_aBackground[state].BorderColor;
				colors[graphics::bplTop] = m_aBackground[state].BorderColor;
				colors[graphics::bplRight] = m_aBackground[state].BorderColor;
				colors[graphics::bplBottom] = m_aBackground[state].BorderColor;
				math::RECTANGLE<size_t> borders{ m_iBorderWidth, m_iBorderWidth, m_iBorderWidth, m_iBorderWidth };
				getForm()->getPresenter()->MultiFillRect(colors, clip, rect, borders, { 0, 0, 0, 0 }, 0, nullptr, nullptr, true);
			}
		}

		void CBaseScrollBar::PaintElement(const ELEMENT_TYPE type, APP_RECT clip, APP_RECT rect)
		{
			if (!rect.IsEmpty())
			{
				// Border
				ELEMENT_STATE state{ getElementState(type) };
				math::RECTANGLE<size_t> radiuses{ m_aElements[type].BorderRadius, m_aElements[type].BorderRadius, m_aElements[type].BorderRadius, m_aElements[type].BorderRadius };
				math::RECTANGLE<size_t> borders{ m_aElements[type].BorderWidth, m_aElements[type].BorderWidth, m_aElements[type].BorderWidth, m_aElements[type].BorderWidth };
				if (m_aElements[type].BorderWidth > 0 && m_aElements[type].State[state].BorderColor.getAlpha() > 0)
				{
					getForm()->getPresenter()->RenderBorder(graphics::bplLeft, m_aElements[type].State[state].BorderColor, clip, rect, borders, radiuses,
						m_aElements[type].BorderAntiAliazing, nullptr, nullptr, true);
					getForm()->getPresenter()->RenderBorder(graphics::bplTop, m_aElements[type].State[state].BorderColor, clip, rect, borders, radiuses,
						m_aElements[type].BorderAntiAliazing, nullptr, nullptr, true);
					getForm()->getPresenter()->RenderBorder(graphics::bplRight, m_aElements[type].State[state].BorderColor, clip, rect, borders, radiuses,
						m_aElements[type].BorderAntiAliazing, nullptr, nullptr, true);
					getForm()->getPresenter()->RenderBorder(graphics::bplBottom, m_aElements[type].State[state].BorderColor, clip, rect, borders, radiuses,
						m_aElements[type].BorderAntiAliazing, nullptr, nullptr, true);
				}
				// Background
				if (m_aElements[type].State[state].GradientPointCount > 1)
				{
					m_aElements[type].State[state].SortGradientPoints();
					getForm()->getPresenter()->RenderGradient(m_aElements[type].State[state].GradientType, m_aElements[type].State[state].GradientPointCount,
						m_aElements[type].State[state].GradientPoints, graphics::bplInside, clip, rect, rect, borders, radiuses, m_aElements[type].BorderAntiAliazing,
						nullptr, nullptr, true);
				}
				else if (m_aElements[type].State[state].BackgroundColor.getAlpha() > 0)
					getForm()->getPresenter()->FillRect(m_aElements[type].State[state].BackgroundColor, clip, rect, rect, borders, radiuses,
						m_aElements[type].BorderAntiAliazing, graphics::bplInside, nullptr, nullptr, true);
				// Image
				APP_IMAGE *image;
				APP_RECT image_rect;
				if (SearchElementImage(type, &image, image_rect, false) && rect.Width() >= image_rect.Width() && rect.Height() >= image_rect.Height())
				{
					IImage *img{ getForm()->getImageManager()->getImage(image) };
					if (img)
					{
						int x{ rect.Left + (rect.Width() - image_rect.Width()) / 2 };
						int y{ rect.Top + (rect.Height() - image_rect.Height()) / 2 };
						getForm()->getPresenter()->RenderImage(img, image_rect, x, y, 0, 1, 1, false, false, false, rect, rect, borders, radiuses, m_aElements[type].BorderAntiAliazing,
							graphics::bplInside, nullptr, nullptr, true);
					}
				}
			}
		}

		void CBaseScrollBar::Paint(APP_RECT clip)
		{
			if (m_bVisible)
			{
				PaintBackground(clip);
				PaintElement(etStartArrow, clip, ClientToForm(CalculateStartArrowRect()));
				PaintElement(etEndArrow, clip, ClientToForm(CalculateEndArrowRect()));
				PaintElement(etScroller, clip, ClientToForm(CalculateScrollerRect()));
			}
		}
	#pragma endregion

	#pragma region Process events
		bool CBaseScrollBar::ProcessDownOnStartArrow(const int x, const int y)
		{
			APP_RECT rect = ClientToForm(CalculateStartArrowRect());
			if (x < rect.Left || x >= rect.Right || y < rect.Top || y >= rect.Bottom)
				return false;
			m_bMouseDownOnStartArrow = true;
			m_bMouseDownOnEndArrow = false;
			m_bMouseDownOnScroller = false;
			m_bMouseDownBeforeScroller = false;
			m_bMouseDownAfterScroller = false;
			if (m_iScroll > m_iMin)
				m_iScroll--;
			return true;
		}

		bool CBaseScrollBar::ProcessDownOnEndArrow(const int x, const int y)
		{
			APP_RECT rect = ClientToForm(CalculateEndArrowRect());
			if (x < rect.Left || x >= rect.Right || y < rect.Top || y >= rect.Bottom)
				return false;
			m_bMouseDownOnStartArrow = false;
			m_bMouseDownOnEndArrow = true;
			m_bMouseDownOnScroller = false;
			m_bMouseDownBeforeScroller = false;
			m_bMouseDownAfterScroller = false;
			if (m_iScroll < m_iMax)
				m_iScroll++;
			return true;
		}

		bool CBaseScrollBar::ProcessDownOnScroller(const int x, const int y)
		{
			APP_RECT rect = ClientToForm(CalculateScrollerRect());
			if (x < rect.Left || x >= rect.Right || y < rect.Top || y >= rect.Bottom)
				return false;
			m_bMouseDownOnStartArrow = false;
			m_bMouseDownOnEndArrow = false;
			m_bMouseDownOnScroller = true;
			m_bMouseDownBeforeScroller = false;
			m_bMouseDownAfterScroller = false;
			m_iMouseDownScrollDelta = MouseToScroll(x, y) - m_iScroll;
			return true;
		}

		bool CBaseScrollBar::ProcessDownBeforeScroller(const int x, const int y)
		{
			APP_RECT rect = ClientToForm(CalculateBeforeScrollerRect());
			if (x < rect.Left || x >= rect.Right || y < rect.Top || y >= rect.Bottom)
				return false;
			m_bMouseDownOnStartArrow = false;
			m_bMouseDownOnEndArrow = false;
			m_bMouseDownOnScroller = false;
			m_bMouseDownBeforeScroller = true;
			m_bMouseDownAfterScroller = false;
			if (m_iScroll > m_iMin)
				m_iScroll = std::max(m_iMin, m_iScroll - (int)m_iPageSize);
			return true;
		}

		bool CBaseScrollBar::ProcessDownAfterScroller(const int x, const int y)
		{
			APP_RECT rect = ClientToForm(CalculateAfterScrollerRect());
			if (x < rect.Left || x >= rect.Right || y < rect.Top || y >= rect.Bottom)
				return false;
			m_bMouseDownOnStartArrow = false;
			m_bMouseDownOnEndArrow = false;
			m_bMouseDownOnScroller = false;
			m_bMouseDownBeforeScroller = false;
			m_bMouseDownAfterScroller = true;
			if (m_iScroll < m_iMax)
				m_iScroll = std::min(m_iMax, m_iScroll + (int)m_iPageSize);
			return true;
		}

		bool CBaseScrollBar::ProcessMoveScroller(const int x, const int y)
		{
			if (!m_bMouseDownOnScroller)
				return false;
			int pos{ MouseToScroll(x, y) - m_iMouseDownScrollDelta };
			if (pos < m_iMin)
				pos = m_iMin;
			else if (pos > m_iMax)
				pos = m_iMax;
			if (pos != m_iScroll)
				m_iScroll = pos;
			return true;
		}

		bool CBaseScrollBar::ProcessMoveOverStartArrow(const int x, const int y)
		{
			APP_RECT rect = ClientToForm(CalculateStartArrowRect());
			if (x >= rect.Left && x < rect.Right && y >= rect.Top && y < rect.Bottom)
			{
				m_bMouseOverEndArrow = false;
				m_bMouseOverScroller = false;
				if (!m_bMouseOverStartArrow)
					m_bMouseOverStartArrow = true;
				return true;
			}
			return false;
		}

		bool CBaseScrollBar::ProcessMoveOverEndArrow(const int x, const int y)
		{
			APP_RECT rect = ClientToForm(CalculateEndArrowRect());
			if (x >= rect.Left && x < rect.Right && y >= rect.Top && y < rect.Bottom)
			{
				m_bMouseOverStartArrow = false;
				m_bMouseOverScroller = false;
				if (!m_bMouseOverEndArrow)
					m_bMouseOverEndArrow = true;
				return true;
			}
			return false;
		}

		bool CBaseScrollBar::ProcessMoveOverScroller(const int x, const int y)
		{
			APP_RECT rect = ClientToForm(CalculateScrollerRect());
			if (x >= rect.Left && x < rect.Right && y >= rect.Top && y < rect.Bottom)
			{
				m_bMouseOverStartArrow = false;
				m_bMouseOverEndArrow = false;
				if (!m_bMouseOverScroller)
					m_bMouseOverScroller = true;
				return true;
			}
			return false;
		}

		bool CBaseScrollBar::ProcessMoveOverOther()
		{
			if (m_bMouseOverStartArrow || m_bMouseOverEndArrow || m_bMouseOverScroller)
			{
				m_bMouseOverStartArrow = false;
				m_bMouseOverEndArrow = false;
				m_bMouseOverScroller = false;
				return true;
			}
			return false;
		}

		bool CBaseScrollBar::ProcessMouseDown(const int x, const int y)
		{
			if (m_bEnabled && (ProcessDownOnStartArrow(x, y) || ProcessDownOnEndArrow(x, y) || ProcessDownOnScroller(x, y) || ProcessDownBeforeScroller(x, y) || ProcessDownAfterScroller(x, y)))
			{
				m_hTimer = getForm()->AddTimer(TimerCallback, this, SCROLL_TIMER_INTERVAL);
				return true;
			}
			return false;
		}

		bool CBaseScrollBar::ProcessMouseUp()
		{
			if (m_bCancellingDown)
				return false;
			m_bCancellingDown = true;
			if (!m_bMouseDownOnStartArrow && !m_bMouseDownOnEndArrow && !m_bMouseDownOnScroller && !m_bMouseDownBeforeScroller && !m_bMouseDownAfterScroller && !m_hTimer)
			{
				m_bCancellingDown = false;
				return false;
			}
			m_bMouseDownOnStartArrow = false;
			m_bMouseDownOnEndArrow = false;
			m_bMouseDownOnScroller = false;
			m_bMouseDownBeforeScroller = false;
			m_bMouseDownAfterScroller = false;
			if (m_hTimer)
			{
				getForm()->DeleteTimer(m_hTimer);
				m_hTimer = 0;
			}
			m_bCancellingDown = false;
			return true;
		}

		bool CBaseScrollBar::ProcessMouseHover(const int x, const int y)
		{
			if (!m_bEnabled)
				return false;
			m_bHovered = true;
			if (!ProcessMoveOverStartArrow(x, y) && !ProcessMoveOverEndArrow(x, y) && !ProcessMoveOverScroller(x, y))
				ProcessMoveOverOther();
			return true;
		}

		bool CBaseScrollBar::ProcessMouseLeave()
		{
			if (m_bHovered)
			{
				m_bHovered = false;
				m_bMouseOverStartArrow = m_bMouseOverEndArrow = m_bMouseOverScroller = false;
				return true;
			}
			return false;
		}

		bool CBaseScrollBar::ProcessMouseMove(const int x, const int y, bool &repaint_required)
		{
			if (m_bEnabled)
			{
				bool start{ m_bMouseOverStartArrow }, end{ m_bMouseOverEndArrow }, scroller{ m_bMouseOverScroller };
				int scroll{ m_iScroll };
				bool moved{ ProcessMoveScroller(x, y) };
				if (moved || ProcessMoveOverStartArrow(x, y) || ProcessMoveOverEndArrow(x, y) || ProcessMoveOverScroller(x, y) || ProcessMoveOverOther())
				{
					repaint_required = (moved && m_iScroll != scroll) || start != m_bMouseOverStartArrow || end != m_bMouseOverEndArrow || scroller != m_bMouseOverScroller;
					return true;
				}
			}
			return false;
		}

		bool CBaseScrollBar::ProcessMouseWheel(const int x, const int y, const int delta)
		{
			if (m_bEnabled)
				if (delta > 0)
				{
					if (m_iScroll > m_iMin)
					{
						m_iScroll = std::max(m_iMin, m_iScroll - (int)m_iDeltaWheel);
						return true;
					}
				}
				else
				{
					if (m_iScroll < m_iMax)
					{
						m_iScroll = std::min(m_iMax, m_iScroll + (int)m_iDeltaWheel);
						return true;
					}
				}
			return false;
		}
	#pragma endregion

	#pragma region Getters
		APP_RECT CBaseScrollBar::getRect()
		{
			return m_sRect;
		}

		bool CBaseScrollBar::getEnabled() const
		{
			return m_bEnabled;
		}

		bool CBaseScrollBar::getVisible() const
		{
			return m_bVisible;
		}

		int CBaseScrollBar::getMin() const
		{
			return m_iMin;
		}

		int CBaseScrollBar::getMax() const
		{
			return m_iMax;
		}

		int CBaseScrollBar::getScroll() const
		{
			return m_iScroll;
		}

		size_t CBaseScrollBar::getPageSize() const
		{
			return m_iPageSize;
		}

		size_t CBaseScrollBar::getDeltaArrow() const
		{
			return m_iDeltaArrow;
		}

		size_t CBaseScrollBar::getDeltaWheel() const
		{
			return m_iDeltaWheel;
		}

		CBaseScrollBar::TYPE CBaseScrollBar::getType() const
		{
			return m_eType;
		}

		CBaseScrollBar::STATE CBaseScrollBar::getState() const
		{
			if (!m_bEnabled)
				return stDisabled;
			if (m_bMouseDownOnStartArrow || m_bMouseDownOnEndArrow || m_bMouseDownOnScroller || m_bMouseDownBeforeScroller || m_bMouseDownAfterScroller)
				return stActive;
			if (m_bHovered)
				return stHovered;
			return stNormal;
		}

		CBaseScrollBar::ELEMENT_STATE CBaseScrollBar::getElementState(const ELEMENT_TYPE type) const
		{
			if (!m_bEnabled)
				return estDisabled;
			switch (type)
			{
			case etStartArrow:
				if (m_bMouseDownOnStartArrow)
					return estActive;
				if (m_bMouseDownOnEndArrow || m_bMouseDownOnScroller || m_bMouseDownBeforeScroller || m_bMouseDownAfterScroller)
					return estNormal;
				if (m_bMouseOverStartArrow)
					return estOver;
				break;
			case etEndArrow:
				if (m_bMouseDownOnEndArrow)
					return estActive;
				if (m_bMouseDownOnStartArrow || m_bMouseDownOnScroller || m_bMouseDownBeforeScroller || m_bMouseDownAfterScroller)
					return estNormal;
				if (m_bMouseOverEndArrow)
					return estOver;
				break;
			case etScroller:
				if (m_bMouseDownOnScroller)
					return estActive;
				if (m_bMouseDownOnStartArrow || m_bMouseDownOnEndArrow || m_bMouseDownBeforeScroller || m_bMouseDownAfterScroller)
					return estNormal;
				if (m_bMouseOverScroller)
					return estOver;
				break;
			}
			if (m_bHovered)
				return estHovered;
			return estNormal;
		}

		size_t CBaseScrollBar::getScrollerSize() const
		{
			return m_iScrollerSize;
		}

		size_t CBaseScrollBar::getBorderWidth() const
		{
			return m_iBorderWidth;
		}

		bool CBaseScrollBar::getBoxShadow() const
		{
			return m_bBoxShadow;
		}

		APP_POINT CBaseScrollBar::getBoxShadowShift() const
		{
			return m_sBoxShadowShift;
		}

		int CBaseScrollBar::getBoxShadowShiftX() const
		{
			return m_sBoxShadowShift.X;
		}

		int CBaseScrollBar::getBoxShadowShiftY() const
		{
			return m_sBoxShadowShift.Y;
		}

		size_t CBaseScrollBar::getBoxShadowRadius() const
		{
			return m_iBoxShadowRadius;
		}

		APP_COLOR CBaseScrollBar::getBackgroundColor(const STATE state) const
		{
			return m_aBackground[state].BackgroundColor;
		}

		APP_COLOR CBaseScrollBar::getBorderColor(const STATE state) const
		{
			return m_aBackground[state].BorderColor;
		}

		APP_COLOR CBaseScrollBar::getBoxShadowColor(const STATE state) const
		{
			return m_aBackground[state].BoxShadowColor;
		}

		IImage::GRADIENT_TYPE CBaseScrollBar::getGradientType(const STATE state) const
		{
			return m_aBackground[state].GradientType;
		}

		size_t CBaseScrollBar::getGradientPointCount(const STATE state) const
		{
			return m_aBackground[state].GradientPointCount;
		}

		double CBaseScrollBar::getGradientPointPosition(const STATE state, const size_t index) const
		{
			if (index < m_aBackground[state].GradientPointCount)
				return m_aBackground[state].GradientPoints[index].Position;
			return 0;
		}

		APP_COLOR CBaseScrollBar::getGradientPointColor(const STATE state, const size_t index) const
		{
			if (index < m_aBackground[state].GradientPointCount)
				return m_aBackground[state].GradientPoints[index].Color;
			return{ 0, 0, 0, 0 };
		}

		size_t CBaseScrollBar::getElementBorderWidth(const ELEMENT_TYPE element) const
		{
			return m_aElements[element].BorderWidth;
		}

		size_t CBaseScrollBar::getElementBorderRadius(const ELEMENT_TYPE element) const
		{
			return m_aElements[element].BorderRadius;
		}

		size_t CBaseScrollBar::getElementBorderAntiAliazing(const ELEMENT_TYPE element) const
		{
			return m_aElements[element].BorderAntiAliazing;
		}

		APP_COLOR CBaseScrollBar::getElementBackgroundColor(const ELEMENT_TYPE element, const ELEMENT_STATE state) const
		{
			return m_aElements[element].State[state].BackgroundColor;
		}

		APP_COLOR CBaseScrollBar::getElementBorderColor(const ELEMENT_TYPE element, const ELEMENT_STATE state) const
		{
			return m_aElements[element].State[state].BorderColor;
		}

		IImage::GRADIENT_TYPE CBaseScrollBar::getElementGradientType(const ELEMENT_TYPE element, const ELEMENT_STATE state) const
		{
			return m_aElements[element].State[state].GradientType;
		}

		size_t CBaseScrollBar::getElementGradientPointCount(const ELEMENT_TYPE element, const ELEMENT_STATE state) const
		{
			return m_aElements[element].State[state].GradientPointCount;
		}

		double CBaseScrollBar::getElementGradientPointPosition(const ELEMENT_TYPE element, const ELEMENT_STATE state, const size_t index) const
		{
			if (index < m_aElements[element].State[state].GradientPointCount)
				return m_aElements[element].State[state].GradientPoints[index].Position;
			return 0;
		}

		APP_COLOR CBaseScrollBar::getElementGradientPointColor(const ELEMENT_TYPE element, const ELEMENT_STATE state, const size_t index) const
		{
			if (index < m_aElements[element].State[state].GradientPointCount)
				return m_aElements[element].State[state].GradientPoints[index].Color;
			return{ 0, 0, 0, 0 };
		}

		bool CBaseScrollBar::getHovered() const
		{
			return m_bHovered;
		}
	#pragma endregion

	#pragma region Setters
		bool CBaseScrollBar::setEnabled(const bool value)
		{
			if (value != m_bEnabled)
			{
				m_bEnabled = value;
				if (!m_bEnabled)
				{
					m_bHovered = m_bMouseOverStartArrow = m_bMouseOverEndArrow = m_bMouseOverScroller = false;
					ProcessMouseUp();
				}
				return true;
			}
			return false;
		}

		bool CBaseScrollBar::setVisible(const bool value)
		{
			if (value != m_bVisible)
			{
				m_bVisible = value;
				if (!m_bVisible)
				{
					m_bHovered = m_bMouseOverStartArrow = m_bMouseOverEndArrow = m_bMouseOverScroller = false;
					ProcessMouseUp();
				}
				return true;
			}
			return false;
		}

		bool CBaseScrollBar::setMin(const int value)
		{
			if (value != m_iMin)
			{
				m_iMin = value;
				if (m_iMax <= m_iMin)
					m_iMax = m_iMin + 1;
				if (m_iScroll < m_iMin)
					m_iScroll = m_iMin;
				else if (m_iScroll > m_iMax)
					m_iScroll = m_iMax;
				return true;
			}
			return false;
		}

		bool CBaseScrollBar::setMax(const int value)
		{
			if (value != m_iMax)
			{
				m_iMax = value;
				if (m_iMin >= m_iMax)
					m_iMin = m_iMax - 1;
				if (m_iScroll < m_iMin)
					m_iScroll = m_iMin;
				else if (m_iScroll > m_iMax)
					m_iScroll = m_iMax;
				return true;
			}
			return false;
		}

		bool CBaseScrollBar::setScroll(int value)
		{
			if (value < m_iMin)
				value = m_iMin;
			else if (value > m_iMax)
				value = m_iMax;
			if (value != m_iScroll)
			{
				m_iScroll = value;
				return true;
			}
			return false;
		}

		bool CBaseScrollBar::setPageSize(size_t value)
		{
			if (value < 1)
				value = 1;
			if (value != m_iPageSize)
			{
				m_iPageSize = value;
				return true;
			}
			return false;
		}

		bool CBaseScrollBar::setDeltaArrow(size_t value)
		{
			if (value < 1)
				value = 1;
			if (value != m_iDeltaArrow)
			{
				m_iDeltaArrow = value;
				return true;
			}
			return false;
		}

		bool CBaseScrollBar::setDeltaWheel(size_t value)
		{
			if (value < 1)
				value = 1;
			if (value != m_iDeltaWheel)
			{
				m_iDeltaWheel = value;
				return true;
			}
			return false;
		}

		bool CBaseScrollBar::setRect(const APP_RECT &rect)
		{
			bool result{ rect.Width() != m_sRect.Width() || rect.Height() != m_sRect.Height() };
			m_sRect = rect;
			return result;
		}

		bool CBaseScrollBar::setType(const TYPE value)
		{
			if (value != m_eType)
			{
				m_eType = value;
				if (m_eType == sbHorizontal)
				{
					for (int i = 0; i <= stDisabled; i++)
						if (m_aBackground[i].GradientType == IImage::gtHorizontal)
							m_aBackground[i].GradientType = IImage::gtVertical;
					for (int i = 0; i <= etScroller; i++)
						for (int j = 0; j <= estDisabled; j++)
							if (m_aElements[i].State[j].GradientType == IImage::gtHorizontal)
								m_aElements[i].State[j].GradientType = IImage::gtVertical;
				}
				else
				{
					for (int i = 0; i <= stDisabled; i++)
						if (m_aBackground[i].GradientType == IImage::gtVertical)
							m_aBackground[i].GradientType = IImage::gtHorizontal;
					for (int i = 0; i <= etScroller; i++)
						for (int j = 0; j <= estDisabled; j++)
							if (m_aElements[i].State[j].GradientType == IImage::gtVertical)
								m_aElements[i].State[j].GradientType = IImage::gtHorizontal;
				}
				return true;
			}
			return false;
		}

		bool CBaseScrollBar::setScrollerSize(const size_t value)
		{
			if (value != m_iScrollerSize)
			{
				m_iScrollerSize = value;
				return true;
			}
			return false;
		}

		bool CBaseScrollBar::setBorderWidth(const size_t value)
		{
			if (value != m_iBorderWidth)
			{
				m_iBorderWidth = value;
				return true;
			}
			return false;
		}

		bool CBaseScrollBar::setBoxShadow(const bool value)
		{
			if (value != m_bBoxShadow)
			{
				m_bBoxShadow = value;
				return true;
			}
			return false;
		}

		bool CBaseScrollBar::setBoxShadowShift(const APP_POINT &value)
		{
			if (value != m_sBoxShadowShift)
			{
				m_sBoxShadowShift = value;
				if (m_bBoxShadow)
					return true;
			}
			return false;
		}

		bool CBaseScrollBar::setBoxShadowShiftX(const int value)
		{
			return setBoxShadowShift({ value, m_sBoxShadowShift.Y });
		}

		bool CBaseScrollBar::setBoxShadowShiftY(const int value)
		{
			return setBoxShadowShift({ m_sBoxShadowShift.X, value });
		}

		bool CBaseScrollBar::setBoxShadowRadius(const size_t value)
		{
			if (value != m_iBoxShadowRadius)
			{
				m_iBoxShadowRadius = value;
				if (m_bBoxShadow)
					return true;
			}
			return false;
		}

		bool CBaseScrollBar::setBackgroundColor(const STATE state, const APP_COLOR &value)
		{
			if (value != m_aBackground[state].BackgroundColor)
			{
				m_aBackground[state].BackgroundColor = value;
				if (getState() == state)
					return true;
			}
			return false;
		}

		bool CBaseScrollBar::setBorderColor(const STATE state, const APP_COLOR &value)
		{
			if (value != m_aBackground[state].BorderColor)
			{
				m_aBackground[state].BorderColor = value;
				if (getState() == state && m_iBorderWidth > 0)
					return true;
			}
			return false;
		}

		bool CBaseScrollBar::setBoxShadowColor(const STATE state, const APP_COLOR &value)
		{
			if (value != m_aBackground[state].BoxShadowColor)
			{
				m_aBackground[state].BoxShadowColor = value;
				if (m_bBoxShadow && getState() == state)
					return true;
			}
			return false;
		}

		bool CBaseScrollBar::setGradientType(const STATE state, const IImage::GRADIENT_TYPE value)
		{
			if (value != m_aBackground[state].GradientType)
			{
				m_aBackground[state].GradientType = value;
				if (m_aBackground[state].GradientPointCount > 0 && getState() == state)
					return true;
			}
			return false;
		}

		bool CBaseScrollBar::setGradientPointCount(const STATE state, const size_t value)
		{
			if (value != m_aBackground[state].GradientPointCount)
			{
				m_aBackground[state].setGradientPointCount(value);
				if (getState() == state)
					return true;
			}
			return false;
		}

		bool CBaseScrollBar::setGradientPointPosition(const STATE state, const size_t index, const double value)
		{
			if (index < m_aBackground[state].GradientPointCount && value != m_aBackground[state].GradientPoints[index].Position)
			{
				m_aBackground[state].GradientPoints[index].Position = value;
				m_aBackground[state].GradientPointsSorted = false;
				if (getState() == state)
					return true;
			}
			return false;
		}

		bool CBaseScrollBar::setGradientPointColor(const STATE state, const size_t index, const APP_COLOR &value)
		{
			if (index < m_aBackground[state].GradientPointCount && value != m_aBackground[state].GradientPoints[index].Color)
			{
				m_aBackground[state].GradientPoints[index].Color = value;
				if (getState() == state)
					return true;
			}
			return false;
		}

		bool CBaseScrollBar::setGradientPoints(const STATE state, const size_t count, IImage::GRADIENT_POINT *points)
		{
			m_aBackground[state].setGradientPointCount(count);
			for (size_t i = 0; i < m_aBackground[state].GradientPointCount; i++)
				m_aBackground[state].GradientPoints[i] = points[i];
			m_aBackground[state].GradientPointsSorted = false;
			return getState() == state;
		}

		bool CBaseScrollBar::setElementBorderWidth(const ELEMENT_TYPE element, const size_t value)
		{
			if (value != m_aElements[element].BorderWidth)
			{
				m_aElements[element].BorderWidth = value;
				return true;
			}
			return false;
		}

		bool CBaseScrollBar::setElementBorderRadius(const ELEMENT_TYPE element, const size_t value)
		{
			if (value != m_aElements[element].BorderRadius)
			{
				m_aElements[element].BorderRadius = value;
				return true;
			}
			return false;
		}

		bool CBaseScrollBar::setElementBorderAntiAliazing(const ELEMENT_TYPE element, const size_t value)
		{
			if (value != m_aElements[element].BorderAntiAliazing)
			{
				m_aElements[element].BorderAntiAliazing = value;
				return true;
			}
			return false;
		}

		bool CBaseScrollBar::setElementBackgroundColor(const ELEMENT_TYPE element, const ELEMENT_STATE state, const APP_COLOR &value)
		{
			if (value != m_aElements[element].State[state].BackgroundColor)
			{
				m_aElements[element].State[state].BackgroundColor = value;
				if (getState() == state)
					return true;
			}
			return false;
		}

		bool CBaseScrollBar::setElementBorderColor(const ELEMENT_TYPE element, const ELEMENT_STATE state, const APP_COLOR &value)
		{
			if (value != m_aElements[element].State[state].BorderColor)
			{
				m_aElements[element].State[state].BorderColor = value;
				if (getState() == state && m_aElements[element].BorderWidth > 0)
					return true;
			}
			return false;
		}

		bool CBaseScrollBar::setElementGradientType(const ELEMENT_TYPE element, const ELEMENT_STATE state, const IImage::GRADIENT_TYPE value)
		{
			if (value != m_aElements[element].State[state].GradientType)
			{
				m_aElements[element].State[state].GradientType = value;
				if (getState() == state)
					return true;
			}
			return false;
		}

		bool CBaseScrollBar::setElementGradientPointCount(const ELEMENT_TYPE element, const ELEMENT_STATE state, const size_t value)
		{
			if (value != m_aElements[element].State[state].GradientPointCount)
			{
				m_aElements[element].State[state].setGradientPointCount(value);
				if (getState() == state)
					return true;
			}
			return false;
		}

		bool CBaseScrollBar::setElementGradientPointPosition(const ELEMENT_TYPE element, const ELEMENT_STATE state, const size_t index, const double value)
		{
			if (index < m_aElements[element].State[state].GradientPointCount && value != m_aElements[element].State[state].GradientPoints[index].Position)
			{
				m_aElements[element].State[state].GradientPoints[index].Position = value;
				m_aElements[element].State[state].GradientPointsSorted = false;
				if (getState() == state)
					return true;
			}
			return false;
		}

		bool CBaseScrollBar::setElementGradientPointColor(const ELEMENT_TYPE element, const ELEMENT_STATE state, const size_t index, const APP_COLOR &value)
		{
			if (index < m_aElements[element].State[state].GradientPointCount && value != m_aElements[element].State[state].GradientPoints[index].Color)
			{
				m_aElements[element].State[state].GradientPoints[index].Color = value;
				if (getState() == state)
					return true;
			}
			return false;
		}

		bool CBaseScrollBar::setElementGradientPoints(const ELEMENT_TYPE element, const ELEMENT_STATE state, const size_t count, IImage::GRADIENT_POINT *points)
		{
			m_aElements[element].State[state].setGradientPointCount(count);
			for (size_t i = 0; i < m_aElements[element].State[state].GradientPointCount; i++)
				m_aElements[element].State[state].GradientPoints[i] = points[i];
			m_aElements[element].State[state].GradientPointsSorted = false;
			return getState() == state;
		}
	#pragma endregion
	}
}