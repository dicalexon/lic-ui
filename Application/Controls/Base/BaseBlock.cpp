// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#include "BaseBlock.h"
#include "..\..\..\Graphics\ClassifyPoint.h"
#include "..\..\..\Math\Consts.h"
#include "..\..\..\Math\Utils.h"
#include "..\..\Form.h"
#include "..\..\ImageManager.h"
#include "..\..\Presenter.h"
#include "..\..\Style.h"
#include "..\..\StyleSkin.h"
#include "..\..\StyleImage.h"
#include <algorithm>

namespace licui
{
	namespace application
	{
#pragma region BLOCK
		CBaseBlock::BLOCK::BLOCK() :
			BorderAntiAliazing{ 0 },
			BorderWidth{ 0, 0, 0, 0 },
			BorderRadius{ 0, 0, 0, 0 },
			BorderColor{ {0, 0, 0, 255}, {0, 0, 0, 255}, {0, 0, 0, 255}, {0, 0, 0, 255} },
			BorderInterpolate{ false, false, false, false },
			Padding{ 0, 0, 0, 0 },
			CaptionHorizontalAlign{ taLeft },
			CaptionVerticalAlign{ vaTop },
			CaptionAntiAliazing{ 0 },
			CaptionText{ true },
			CaptionShadow{ true },
			CaptionColorsOverwrite{ false },
			CaptionTextColor{ 0, 0, 0, 255 },
			CaptionShadowColor{ 0, 0, 0, 255 },
			CaptionOrientationOverwrite{ false },
			CaptionOrientation{ 0 },
			CaptionScale{ 1, 1 },
			CaptionShift{ 0, 0 },
			BackgroundColor{ 0, 0, 0, 255 },
			BackgroundRepeat{ false, false },
			BackgroundPosition{ 500, 500 },
			BackgroundPositionPercentage{ true, true },
			BackgroundSize{ 0, 0 },
			BackgroundInterpolate{ false },
			BackgroundRotation{ 0 },
			BoxShadow{ false },
			BoxShadowColor{ 0, 0, 0, 255 },
			BoxShadowShift{ 0, 0 },
			BoxShadowRadius{ 0 }
		{

		}
#pragma endregion

#pragma region Helpers
		bool CBaseBlock::FindImage(APP_IMAGE &def, const String &style, APP_IMAGE **img, APP_RECT &rect, double &angle)
		{
			*img = &def;
			rect = { 0, 0, (int)def.getWidth(), (int)def.getHeight() };
			if (def.getWidth() == 0 && getStyle())
			{
				CStyleSkin *skin{ getStyle()->getSkinByName(style) };
				if (skin && skin->getImage())
				{
					*img = skin->getImage()->getImage();
					rect = skin->getRect();
					angle = 0;
				}
			}
			return (*img)->getWidth() > 0 && rect.IsValid() && !rect.IsEmpty();
		}

		bool CBaseBlock::CalculateBackgroundImagePositionAndScaling(const APP_RECT &rect, const int width, const int height, double &x, double &y, double &sx, double &sy)
		{
			int w{ std::max(0, width - (int)getBlock()->BorderWidth[2] - (int)getBlock()->BorderWidth[0]) }; // Client area width
			int h{ std::max(0, height - (int)getBlock()->BorderWidth[3] - (int)getBlock()->BorderWidth[1]) }; // Client area height
			if (w == 0 || h == 0) // Client area is empty, no background image part can be visible
				return false;
			// Calculate image final size and scalings
			math::POINT<double> size;
			if (getBlock()->BackgroundSize[0] == 0)
			{
				size.X = rect.Width();
				sx = 1;
			}
			else if (getBlock()->BackgroundSize[0] > 0)
			{
				size.X = getBlock()->BackgroundSize[0] * 0.1;
				sx = getBlock()->BackgroundSize[0] * 0.1 / rect.Width();
			}
			else
			{
				size.X = - rect.Width() * getBlock()->BackgroundSize[0] * 0.001;
				sx = -getBlock()->BackgroundSize[0] * 0.001;
			}
			if (getBlock()->BackgroundSize[1] == 0)
			{
				size.Y = rect.Height();
				sy = 1;
			}
			else if (getBlock()->BackgroundSize[1] > 0)
			{
				size.Y = getBlock()->BackgroundSize[1] * 0.1;
				sy = getBlock()->BackgroundSize[1] * 0.1 / rect.Height();
			}
			else
			{
				size.Y = - rect.Height() * getBlock()->BackgroundSize[1] * 0.001;
				sy = -getBlock()->BackgroundSize[1] * 0.001;
			}
			size = math::RotatedRectangleSize(size, getBlock()->BackgroundRotation);
			// Calculate image position
			if (getBlock()->BackgroundPositionPercentage[0])
				x = (int)getBlock()->BorderWidth[0] + getBlock()->BackgroundPosition[0] * 0.001 * w - size.X * 0.5;
			else
				x = (int)getBlock()->BorderWidth[0] + (int)(getBlock()->BackgroundPosition[0] * 0.1) - size.X * 0.5;
			if (getBlock()->BackgroundPositionPercentage[1])
				y = (int)(getBlock()->BorderWidth[1] + getBlock()->BackgroundPosition[1] * 0.001 * h) - size.Y * 0.5;
			else
				y = (int)getBlock()->BorderWidth[1] + (int)(getBlock()->BackgroundPosition[1] * 0.1) - size.Y * 0.5;
			return true;
		}

		void CBaseBlock::FillBorderImagesData(BORDER_IMAGE_DATA *images, const int width, const int height)
		{
			double angle;
			// Left
			images[0].Renderable = FindImage(getBlock()->BorderImage[0], getClassName() + getBlock()->StyleName + L".border.left", &images[0].Image, images[0].Rect, angle);
			images[0].RepeatX = false;
			images[0].RepeatY = true;
			images[0].Clip = { 0, 0, (int)std::max(std::max(getBlock()->BorderRadius[3], getBlock()->BorderRadius[0]), getBlock()->BorderWidth[0]) };
			images[0].X = 0;
			images[0].Y = 0;
			images[0].Sx = getBlock()->BorderWidth[0] / (double)images[0].Clip.Width();
			images[0].Sy = 1;
			images[0].Location = graphics::bplLeft;
			// Top
			images[1].Renderable = FindImage(getBlock()->BorderImage[1], getClassName() + getBlock()->StyleName + L".border.top", &images[1].Image, images[1].Rect, angle);
			images[1].RepeatX = true;
			images[1].RepeatY = false;
			images[1].Clip = { 0, 0, width, (int)std::max(std::max(getBlock()->BorderRadius[0], getBlock()->BorderRadius[1]), getBlock()->BorderWidth[1]) };
			images[1].X = 0;
			images[1].Y = 0;
			images[1].Sx = 1;
			images[1].Sy = getBlock()->BorderWidth[1] / (double)images[1].Clip.Height();
			images[1].Location = graphics::bplTop;
			// Right
			images[2].Renderable = FindImage(getBlock()->BorderImage[2], getClassName() + getBlock()->StyleName + L".border.right", &images[2].Image, images[2].Rect, angle);
			images[2].RepeatX = false;
			images[2].RepeatY = true;
			images[2].Clip = { (int)std::min(std::min(width - getBlock()->BorderRadius[1], width - getBlock()->BorderRadius[2]), width - getBlock()->BorderWidth[2]), 0, width, height };
			images[2].X = images[2].Clip.Left;
			images[2].Y = 0;
			images[2].Sx = getBlock()->BorderWidth[2] / (double)images[2].Clip.Width();
			images[2].Sy = 1;
			images[2].Location = graphics::bplRight;
			// Bottom
			images[3].Renderable = FindImage(getBlock()->BorderImage[3], getClassName() + getBlock()->StyleName + L".border.bottom", &images[3].Image, images[3].Rect, angle);
			images[3].RepeatX = true;
			images[3].RepeatY = false;
			images[3].Clip = { 0, (int)std::min(std::min(height - getBlock()->BorderRadius[2], height - getBlock()->BorderRadius[3]), height - getBlock()->BorderWidth[3]), width, height };
			images[3].X = 0;
			images[3].Y = images[3].Clip.Top;
			images[3].Sx = 1;
			images[3].Sy = getBlock()->BorderWidth[3] / (double)images[3].Clip.Height();
			images[3].Location = graphics::bplBottom;
		}

		bool CBaseBlock::CalculateCaptionParams(const String &caption, const int width, const int height, double &x, double &y, double &angle, APP_COLOR &text, APP_COLOR &shadow, APP_POINT &size)
		{
			if (caption.empty())
				return false;
			if ((getBlock()->BorderWidth[0] + getBlock()->BorderWidth[2] >= (size_t)width) || (getBlock()->BorderWidth[1] + getBlock()->BorderWidth[3] >= (size_t)height)) // Check there is space between block borders
				return false;
			angle = { -(getBlock()->CaptionOrientationOverwrite ? getBlock()->CaptionOrientation : getFont()->getOrientation()) * math::PI / 1800.0 };
			size = getFont()->getStringSize(caption);
			size.X = (int)(0.5 + size.X * getBlock()->CaptionScale[0]);
			size.Y = (int)(0.5 + size.Y * getBlock()->CaptionScale[1]);
			size = math::RotatedRectangleSize(size, angle);
			switch (getBlock()->CaptionHorizontalAlign)
			{
			case taRight:
				x = width - (int)getBlock()->BorderWidth[2] - (int)getBlock()->Padding[2] - size.X - 1;
				break;
			case taCenter:
				x = (width - (int)getBlock()->BorderWidth[2] - (int)getBlock()->Padding[2] + (int)getBlock()->BorderWidth[0] + (int)getBlock()->Padding[0] - size.X) * 0.5;
				break;
			default:
				x = getBlock()->BorderWidth[0] + getBlock()->Padding[0];
				break;
			}
			switch (getBlock()->CaptionVerticalAlign)
			{
			case vaMiddle:
				y = (height - (int)getBlock()->BorderWidth[3] - (int)getBlock()->Padding[3] + (int)getBlock()->BorderWidth[1] + (int)getBlock()->Padding[1] - size.Y) * 0.5;
				break;
			case vaBottom:
				y = height - (int)getBlock()->BorderWidth[3] - (int)getBlock()->Padding[3] - size.Y - 1;
				break;
			default:
				y = getBlock()->BorderWidth[1] + getBlock()->Padding[1];
				break;
			}
			if (getBlock()->CaptionColorsOverwrite)
			{
				text = getBlock()->CaptionTextColor;
				shadow = getBlock()->CaptionShadowColor;
			}
			else
			{
				text = getFont()->getColor();
				shadow = getFont()->getShadowColor();
			}
			return true;
		}

		bool CBaseBlock::UpdateFromStyle()
		{
			if (!getStyle())
				return false;
			if (getBlock())
			{
				getBlock()->BorderAntiAliazing = getStyle()->getParameterByName(m_sClassName + L".BorderAntiAliazing", getBlock()->BorderAntiAliazing);
				getBlock()->BorderWidth = getStyle()->getParameterByName(m_sClassName + L".BorderWidth", getBlock()->BorderWidth);
				getBlock()->BorderRadius = getStyle()->getParameterByName(m_sClassName + L".BorderRadius", getBlock()->BorderRadius);
				getBlock()->BorderColor[0] = getStyle()->getParameterByName(m_sClassName + L".BorderColor[0]", getBlock()->BorderColor[0]);
				getBlock()->BorderColor[1] = getStyle()->getParameterByName(m_sClassName + L".BorderColor[1]", getBlock()->BorderColor[1]);
				getBlock()->BorderColor[2] = getStyle()->getParameterByName(m_sClassName + L".BorderColor[2]", getBlock()->BorderColor[2]);
				getBlock()->BorderColor[3] = getStyle()->getParameterByName(m_sClassName + L".BorderColor[3]", getBlock()->BorderColor[3]);
				getBlock()->BorderInterpolate = getStyle()->getParameterByName(m_sClassName + L".BorderInterpolate", getBlock()->BorderInterpolate);
				getBlock()->Padding = getStyle()->getParameterByName(m_sClassName + L".Padding", getBlock()->Padding);
				getBlock()->CaptionHorizontalAlign = (TEXT_ALIGN)getStyle()->getParameterByName(m_sClassName + L".CaptionHorizontalAlign", (int)getBlock()->CaptionHorizontalAlign);
				getBlock()->CaptionVerticalAlign = (VERTICAL_ALIGN)getStyle()->getParameterByName(m_sClassName + L".CaptionVerticalAlign", (int)getBlock()->CaptionVerticalAlign);
				getBlock()->CaptionAntiAliazing = getStyle()->getParameterByName(m_sClassName + L".CaptionAntiAliazing", getBlock()->CaptionAntiAliazing);
				getBlock()->CaptionText = getStyle()->getParameterByName(m_sClassName + L".CaptionText", getBlock()->CaptionText);
				getBlock()->CaptionShadow = getStyle()->getParameterByName(m_sClassName + L".CaptionShadow", getBlock()->CaptionShadow);
				getBlock()->CaptionColorsOverwrite = getStyle()->getParameterByName(m_sClassName + L".CaptionColorsOverwrite", getBlock()->CaptionColorsOverwrite);
				getBlock()->CaptionTextColor = getStyle()->getParameterByName(m_sClassName + L".CaptionTextColor", getBlock()->CaptionTextColor);
				getBlock()->CaptionShadowColor = getStyle()->getParameterByName(m_sClassName + L".CaptionShadowColor", getBlock()->CaptionShadowColor);
				getBlock()->CaptionOrientationOverwrite = getStyle()->getParameterByName(m_sClassName + L".CaptionOrientationOverwrite", getBlock()->CaptionOrientationOverwrite);
				getBlock()->CaptionOrientation = getStyle()->getParameterByName(m_sClassName + L".CaptionOrientation", getBlock()->CaptionOrientation);
				getBlock()->CaptionScale = getStyle()->getParameterByName(m_sClassName + L".CaptionScale", getBlock()->CaptionScale);
				getBlock()->CaptionShift = getStyle()->getParameterByName(m_sClassName + L".CaptionShift", getBlock()->CaptionShift);
				getBlock()->BackgroundColor = getStyle()->getParameterByName(m_sClassName + L".BackgroundColor", getBlock()->BackgroundColor);
				getBlock()->BackgroundRepeat = getStyle()->getParameterByName(m_sClassName + L".BackgroundRepeat", getBlock()->BackgroundRepeat);
				getBlock()->BackgroundPosition = getStyle()->getParameterByName(m_sClassName + L".BackgroundPosition", getBlock()->BackgroundPosition);
				getBlock()->BackgroundPositionPercentage = getStyle()->getParameterByName(m_sClassName + L".BackgroundPositionPercentage", getBlock()->BackgroundPositionPercentage);
				getBlock()->BackgroundSize = getStyle()->getParameterByName(m_sClassName + L".BackgroundSize", getBlock()->BackgroundSize);
				getBlock()->BackgroundInterpolate = getStyle()->getParameterByName(m_sClassName + L".BackgroundInterpolate", getBlock()->BackgroundInterpolate);
				getBlock()->BackgroundRotation = getStyle()->getParameterByName(m_sClassName + L".BackgroundRotation", getBlock()->BackgroundRotation);
				getBlock()->BoxShadow = getStyle()->getParameterByName(m_sClassName + L".BoxShadow", getBlock()->BoxShadow);
				getBlock()->BoxShadowColor = getStyle()->getParameterByName(m_sClassName + L".BoxShadowColor", getBlock()->BoxShadowColor);
				getBlock()->BoxShadowShift = getStyle()->getParameterByName(m_sClassName + L".BoxShadowShift", getBlock()->BoxShadowShift);
				getBlock()->BoxShadowRadius = getStyle()->getParameterByName(m_sClassName + L".BoxShadowRadius", getBlock()->BoxShadowRadius);
			}
			return true;
		}
#pragma endregion

#pragma region Rendering
		void CBaseBlock::DoRender(const String &caption, APP_RECT clip)
		{
			if (getBlock() && m_pForm && m_pForm->getPresenter())
			{
				clip *= getVisibleRect();
				DoRenderBoxShadow(clip);
				DoRenderBlock(clip);
				DoRenderBackgroundImage(clip);
				DoRenderBorderImages(clip);
				DoRenderCaption(caption, clip);
			}
		}

		void CBaseBlock::DoRenderBlock(const APP_RECT &clip)
		{
			if (getBlock() && m_pForm && m_pForm->getPresenter())
			{
				APP_COLOR colors[graphics::bplBottom + 1]{
					{ 0, 0, 0, 0 },
					{ getBlock()->BackgroundColor },
					{ getBlock()->BorderColor[0] },
					{ getBlock()->BorderColor[1] },
					{ getBlock()->BorderColor[2] },
					{ getBlock()->BorderColor[3] }
				};
				m_pForm->getPresenter()->MultiFillRect(colors, clip, ClientToForm(getRect()), getBlock()->BorderWidth, getBlock()->BorderRadius, getBlock()->BorderAntiAliazing, nullptr, nullptr, true);
			}
		}

		void CBaseBlock::DoRenderRect(const APP_COLOR &color, const APP_RECT &rect, const APP_RECT &clip)
		{
			if (getBlock() && m_pForm && m_pForm->getPresenter())
			{
				APP_RECT r{ rect.Left + getRect().Left, rect.Top + getRect().Top, rect.Right + getRect().Left, rect.Bottom + getRect().Top };
				m_pForm->getPresenter()->FillRect(color, clip, ClientToForm(r), ClientToForm(getRect()), getBlock()->BorderWidth, getBlock()->BorderRadius, getBlock()->BorderAntiAliazing,
					graphics::bplInside, nullptr, nullptr, true);
			}
		}

		void CBaseBlock::DoRenderBackgroundImage(const APP_RECT &clip)
		{
			if (getBlock() && m_pForm && m_pForm->getPresenter())
			{
				APP_IMAGE *bg;
				APP_RECT rect;
				double x, y, sx, sy, angle{ getBlock()->BackgroundRotation };
				if (
					FindImage(getBlock()->BackgroundImage, getClassName() + getBlock()->StyleName + L".background.image", &bg, rect, angle) &&
					CalculateBackgroundImagePositionAndScaling(rect, getRect().Width(), getRect().Height(), x, y, sx, sy))
				{
					IImage *image{ m_pForm->getImageManager()->getImage(bg) };
					if (image)
						m_pForm->getPresenter()->RenderImage(
							image, rect,
							x + getRect().Left, y + getRect().Top, angle, sx, sy,
							getBlock()->BackgroundRepeat[0], getBlock()->BackgroundRepeat[1], getBlock()->BackgroundInterpolate,
							clip,
							ClientToForm(getRect()), getBlock()->BorderWidth, getBlock()->BorderRadius, getBlock()->BorderAntiAliazing, graphics::bplInside,
							nullptr, nullptr, true);
				}
			}
		}

		void CBaseBlock::DoRenderBorderImages(const APP_RECT &clip)
		{
			if (getBlock() && m_pForm && m_pForm->getPresenter())
			{
				BORDER_IMAGE_DATA images[4];
				FillBorderImagesData(&images[0], getRect().Width(), getRect().Height());
				APP_RECT r = ClientToForm(getRect()), c;
				for (int i = 0; i < 4; i++)
					if (images[i].Renderable)
					{
						IImage *image{ m_pForm->getImageManager()->getImage(images[i].Image) };
						if (image)
						{
							c.Left = images[i].Clip.Left + r.Left;
							c.Top = images[i].Clip.Top + r.Top;
							c.Right = images[i].Clip.Right + r.Left;
							c.Bottom = images[i].Clip.Bottom + r.Top;
							m_pForm->getPresenter()->RenderImage(
								image, images[i].Rect,
								images[i].X + r.Left, images[i].Y + r.Top, 0, images[i].Sx, images[i].Sy, images[i].RepeatX, images[i].RepeatY, getBlock()->BorderInterpolate[i],
								clip * ClientToForm(c), r, getBlock()->BorderWidth, getBlock()->BorderRadius, getBlock()->BorderAntiAliazing, images[i].Location,
								nullptr, nullptr, true);
						}
					}
			}
		}

		void CBaseBlock::DoRenderCaption(const String &caption, const APP_RECT &clip)
		{
			if (getBlock() && m_pForm && m_pForm->getPresenter())
			{
				double x, y, angle;
				APP_COLOR text, shadow;
				APP_POINT size;
				if (CalculateCaptionParams(caption, getRect().Width(), getRect().Height(), x, y, angle, text, shadow, size))
				{
					APP_RECT text_clip{ // Block client area
						getRect().Left + (int)getBlock()->BorderWidth[0] + (int)getBlock()->Padding[0],
						getRect().Top + (int)getBlock()->BorderWidth[1] + (int)getBlock()->Padding[1],
						getRect().Right - (int)getBlock()->BorderWidth[2] - (int)getBlock()->Padding[2],
						getRect().Bottom - (int)getBlock()->BorderWidth[3] - (int)getBlock()->Padding[3]
					};
					if (text_clip.IsValid() && !text_clip.IsEmpty())
					{
						text_clip *= {
							(int)(x + getBlock()->CaptionShift[0] + getRect().Left + 0.5),
							(int)(y + getBlock()->CaptionShift[1] + getRect().Top + 0.5),
							(int)(x + getBlock()->CaptionShift[0] + getRect().Left + size.X + 1.5),
							(int)(y + getBlock()->CaptionShift[1] + getRect().Top + size.Y + 1.5)
						}; // Block client area * text area
						text_clip = ClientToForm(text_clip);
						APP_RECT r = ClientToForm(getRect());
						m_pForm->getPresenter()->RenderString(
							caption, getFont(), x + getBlock()->CaptionShift[0] + r.Left, y + getBlock()->CaptionShift[1] + r.Top, angle, getBlock()->CaptionScale[0], getBlock()->CaptionScale[1],
							clip * text_clip, getBlock()->CaptionAntiAliazing, r, getBlock()->BorderWidth, getBlock()->BorderRadius, getBlock()->BorderAntiAliazing, graphics::bplInside,
							getBlock()->CaptionText, getBlock()->CaptionShadow, text, shadow, nullptr, nullptr, true);
					}
				}
			}
		}

		void CBaseBlock::DoRenderBoxShadow(const APP_RECT &clip)
		{
			if (getBlock() && m_pForm && m_pForm->getPresenter() && getBlock()->BoxShadow && getBlock()->BoxShadowColor.getAlpha() > 0)
				m_pForm->getPresenter()->BoxBlur(getBlock()->BoxShadowColor, getBlock()->BoxShadowShift.X, getBlock()->BoxShadowShift.Y, getBlock()->BoxShadowRadius, clip, ClientToForm(getRect()),
					getBlock()->BorderRadius, getBlock()->BorderAntiAliazing, nullptr, nullptr, true);
		}
#pragma endregion

#pragma region Getters
		CBaseBlock::BLOCK *CBaseBlock::getBlock()
		{
			return nullptr;
		}

		size_t CBaseBlock::getBorderAntiAliazing()
		{
			if (getBlock())
				return getBlock()->BorderAntiAliazing;
			return 0;
		}

		APP_RECT CBaseBlock::getBorderWidth()
		{
			if (getBlock())
				return{ (int)getBlock()->BorderWidth[0], (int)getBlock()->BorderWidth[1], (int)getBlock()->BorderWidth[2], (int)getBlock()->BorderWidth[3] };
			return{ 0, 0, 0, 0 };
		}

		size_t CBaseBlock::getLeftBorderWidth()
		{
			if (getBlock())
				return getBlock()->BorderWidth[0];
			return 0;
		}

		size_t CBaseBlock::getTopBorderWidth()
		{
			if (getBlock())
				return getBlock()->BorderWidth[1];
			return 0;
		}

		size_t CBaseBlock::getRightBorderWidth()
		{
			if (getBlock())
				return getBlock()->BorderWidth[2];
			return 0;
		}

		size_t CBaseBlock::getBottomBorderWidth()
		{
			if (getBlock())
				return getBlock()->BorderWidth[3];
			return 0;
		}

		APP_RECT CBaseBlock::getBorderRadius()
		{
			if (getBlock())
				return{ (int)getBlock()->BorderRadius[0], (int)getBlock()->BorderRadius[1], (int)getBlock()->BorderRadius[2], (int)getBlock()->BorderRadius[3] };
			return{ 0, 0, 0, 0 };
		}

		size_t CBaseBlock::getLeftTopRadius()
		{
			if (getBlock())
				return getBlock()->BorderRadius[0];
			return 0;
		}

		size_t CBaseBlock::getRightTopRadius()
		{
			if (getBlock())
				return getBlock()->BorderRadius[1];
			return 0;
		}

		size_t CBaseBlock::getRightBottomRadius()
		{
			if (getBlock())
				return getBlock()->BorderRadius[2];
			return 0;
		}

		size_t CBaseBlock::getLeftBottomRadius()
		{
			if (getBlock())
				return getBlock()->BorderRadius[3];
			return 0;
		}

		APP_COLOR CBaseBlock::getLeftBorderColor()
		{
			if (getBlock())
				return getBlock()->BorderColor[0];
			return{ 0, 0, 0, 0 };
		}

		APP_COLOR CBaseBlock::getTopBorderColor()
		{
			if (getBlock())
				return getBlock()->BorderColor[1];
			return{ 0, 0, 0, 0 };
		}

		APP_COLOR CBaseBlock::getRightBorderColor()
		{
			if (getBlock())
				return getBlock()->BorderColor[2];
			return{ 0, 0, 0, 0 };
		}

		APP_COLOR CBaseBlock::getBottomBorderColor()
		{
			if (getBlock())
				return getBlock()->BorderColor[3];
			return{ 0, 0, 0, 0 };
		}

		APP_IMAGE *CBaseBlock::getLeftBorderImage()
		{
			if (getBlock())
			{
				if (m_pForm)
					m_pForm->getImageManager()->FreeImage(&getBlock()->BorderImage[0]);
				return &getBlock()->BorderImage[0];
			}
			return nullptr;
		}

		APP_IMAGE *CBaseBlock::getTopBorderImage()
		{
			if (getBlock())
			{
				if (m_pForm)
					m_pForm->getImageManager()->FreeImage(&getBlock()->BorderImage[1]);
				return &getBlock()->BorderImage[1];
			}
			return nullptr;
		}

		APP_IMAGE *CBaseBlock::getRightBorderImage()
		{
			if (getBlock())
			{
				if (m_pForm)
					m_pForm->getImageManager()->FreeImage(&getBlock()->BorderImage[2]);
				return &getBlock()->BorderImage[2];
			}
			return nullptr;
		}

		APP_IMAGE *CBaseBlock::getBottomBorderImage()
		{
			if (getBlock())
			{
				if (m_pForm)
					m_pForm->getImageManager()->FreeImage(&getBlock()->BorderImage[3]);
				return &getBlock()->BorderImage[3];
			}
			return nullptr;
		}

		bool CBaseBlock::getLeftBorderInterpolate()
		{
			if (getBlock())
				return getBlock()->BorderInterpolate[0];
			return false;
		}

		bool CBaseBlock::getTopBorderInterpolate()
		{
			if (getBlock())
				return getBlock()->BorderInterpolate[1];
			return false;
		}

		bool CBaseBlock::getRightBorderInterpolate()
		{
			if (getBlock())
				return getBlock()->BorderInterpolate[2];
			return false;
		}

		bool CBaseBlock::getBottomBorderInterpolate()
		{
			if (getBlock())
				return getBlock()->BorderInterpolate[3];
			return false;
		}

		APP_RECT CBaseBlock::getPadding()
		{
			if (getBlock())
				return{ (int)getBlock()->Padding[0], (int)getBlock()->Padding[1], (int)getBlock()->Padding[2], (int)getBlock()->Padding[3] };
			return{ 0, 0, 0, 0 };
		}

		size_t CBaseBlock::getPaddingLeft()
		{
			if (getBlock())
				return getBlock()->Padding[0];
			return 0;
		}

		size_t CBaseBlock::getPaddingTop()
		{
			if (getBlock())
				return getBlock()->Padding[1];
			return 0;
		}

		size_t CBaseBlock::getPaddingRight()
		{
			if (getBlock())
				return getBlock()->Padding[2];
			return 0;
		}

		size_t CBaseBlock::getPaddingBottom()
		{
			if (getBlock())
				return getBlock()->Padding[3];
			return 0;
		}

		TEXT_ALIGN CBaseBlock::getCaptionHorizontalAlign()
		{
			if (getBlock())
				return getBlock()->CaptionHorizontalAlign;
			return taLeft;
		}

		VERTICAL_ALIGN CBaseBlock::getCaptionVerticalAlign()
		{
			if (getBlock())
				return getBlock()->CaptionVerticalAlign;
			return vaTop;
		}

		size_t CBaseBlock::getCaptionAntiAliazing()
		{
			if (getBlock())
				return getBlock()->CaptionAntiAliazing;
			return 0;
		}

		bool CBaseBlock::getCaptionText()
		{
			if (getBlock())
				return getBlock()->CaptionText;
			return false;
		}

		bool CBaseBlock::getCaptionShadow()
		{
			if (getBlock())
				return getBlock()->CaptionShadow;
			return false;
		}

		bool CBaseBlock::getCaptionColorsOverwrite()
		{
			if (getBlock())
				return getBlock()->CaptionColorsOverwrite;
			return false;
		}

		APP_COLOR CBaseBlock::getCaptionTextColor()
		{
			if (getBlock())
				return getBlock()->CaptionTextColor;
			return{ 0, 0, 0, 0 };
		}

		APP_COLOR CBaseBlock::getCaptionShadowColor()
		{
			if (getBlock())
				return getBlock()->CaptionShadowColor;
			return{ 0, 0, 0, 0 };
		}

		bool CBaseBlock::getCaptionOrientationOverwrite()
		{
			if (getBlock())
				return getBlock()->CaptionOrientationOverwrite;
			return false;
		}

		int CBaseBlock::getCaptionOrientation()
		{
			if (getBlock())
				return getBlock()->CaptionOrientation;
			return 0;
		}

		math::POINT<double> CBaseBlock::getCaptionScale()
		{
			if (getBlock())
				return{ getBlock()->CaptionScale[0], getBlock()->CaptionScale[1] };
			return{ 1, 1 };
		}

		double CBaseBlock::getCaptionScaleX()
		{
			if (getBlock())
				return getBlock()->CaptionScale[0];
			return 1;
		}

		double CBaseBlock::getCaptionScaleY()
		{
			if (getBlock())
				return getBlock()->CaptionScale[1];
			return 1;
		}

		math::POINT<double> CBaseBlock::getCaptionShift()
		{
			if (getBlock())
				return{ getBlock()->CaptionShift[0], getBlock()->CaptionShift[1] };
			return{ 0, 0 };
		}

		double CBaseBlock::getCaptionShiftX()
		{
			if (getBlock())
				return getBlock()->CaptionShift[0];
			return 0;
		}

		double CBaseBlock::getCaptionShiftY()
		{
			if (getBlock())
				return getBlock()->CaptionShift[1];
			return 0;
		}

		APP_COLOR CBaseBlock::getBackgrondColor()
		{
			if (getBlock())
				return getBlock()->BackgroundColor;
			return{ 0, 0, 0, 0 };
		}

		APP_IMAGE *CBaseBlock::getBackgroundImage()
		{
			if (getBlock())
			{
				if (m_pForm)
					m_pForm->getImageManager()->FreeImage(&getBlock()->BackgroundImage);
				return &getBlock()->BackgroundImage;
			}
			return nullptr;
		}

		bool CBaseBlock::getBackgroundRepeatX()
		{
			if (getBlock())
				return getBlock()->BackgroundRepeat[0];
			return false;
		}

		bool CBaseBlock::getBackgroundRepeatY()
		{
			if (getBlock())
				return getBlock()->BackgroundRepeat[1];
			return false;
		}

		APP_POINT CBaseBlock::getBackgroundPosition()
		{
			if (getBlock())
				return{ getBlock()->BackgroundPosition[0], getBlock()->BackgroundPosition[1] };
			return{ 0, 0 };
		}

		int CBaseBlock::getBackgroundPositionX()
		{
			if (getBlock())
				return getBlock()->BackgroundPosition[0];
			return 0;
		}

		int CBaseBlock::getBackgroundPositionY()
		{
			if (getBlock())
				return getBlock()->BackgroundPosition[1];
			return 0;
		}

		bool CBaseBlock::getBackgroundPositionPercentageX()
		{
			if (getBlock())
				return getBlock()->BackgroundPositionPercentage[0];
			return false;
		}

		bool CBaseBlock::getBackgroundPositionPercentageY()
		{
			if (getBlock())
				return getBlock()->BackgroundPositionPercentage[1];
			return false;
		}

		APP_POINT CBaseBlock::getBackgroundSize()
		{
			if (getBlock())
				return{ getBlock()->BackgroundSize[0], getBlock()->BackgroundSize[1] };
			return{ 0, 0 };
		}

		int CBaseBlock::getBackgroundSizeX()
		{
			if (getBlock())
				return getBlock()->BackgroundSize[0];
			return 0;
		}

		int CBaseBlock::getBackgroundSizeY()
		{
			if (getBlock())
				return getBlock()->BackgroundSize[1];
			return 0;
		}

		bool CBaseBlock::getBackgroundInterpolate()
		{
			if (getBlock())
				return getBlock()->BackgroundInterpolate;
			return false;
		}

		double CBaseBlock::getBackgroundRotation()
		{
			if (getBlock())
				return getBlock()->BackgroundRotation;
			return 0;
		}

		bool CBaseBlock::getBoxShadow()
		{
			if (getBlock())
				return getBlock()->BoxShadow;
			return false;
		}

		APP_COLOR CBaseBlock::getBoxShadowColor()
		{
			if (getBlock())
				return getBlock()->BoxShadowColor;
			return{ 0, 0, 0, 0 };
		}

		APP_POINT CBaseBlock::getBoxShadowShift()
		{
			if (getBlock())
				return getBlock()->BoxShadowShift;
			return{ 0, 0 };
		}

		size_t CBaseBlock::getBoxShadowRadius()
		{
			if (getBlock())
				return getBlock()->BoxShadowRadius;
			return 0;
		}
#pragma endregion

#pragma region Setters
		CBaseBlock *CBaseBlock::setBorderAntiAliazing(size_t value)
		{
			if (getBlock())
			{
				if (value == 1)
					value = 0;
				if (value != getBlock()->BorderAntiAliazing)
				{
					getBlock()->BorderAntiAliazing = value;
					if (getBlock()->BorderWidth[0] > 0 || getBlock()->BorderWidth[1] > 0 || getBlock()->BorderWidth[2] > 0 || getBlock()->BorderWidth[3] > 0 ||
						getBlock()->BorderRadius[0] > 0 || getBlock()->BorderRadius[1] > 0 || getBlock()->BorderRadius[2] > 0 || getBlock()->BorderRadius[3] > 0)
						Repaint(false);
				}
			}
			return this;
		}

		CBaseBlock *CBaseBlock::setBorderWidth(const size_t value)
		{
			if (getBlock() && (getBlock()->BorderWidth[0] != value || getBlock()->BorderWidth[1] != value || getBlock()->BorderWidth[2] != value || getBlock()->BorderWidth[3] != value))
			{
				getBlock()->BorderWidth[0] = getBlock()->BorderWidth[1] = getBlock()->BorderWidth[2] = getBlock()->BorderWidth[3] = value;
				if (m_pForm)
					m_pForm->LockRepaint();
				for (size_t index = 0; index < getControlCount(); index++)
					getControl(index)->UpdateRect();
				Repaint(false);
				if (m_pForm)
					m_pForm->UnlockRepaint();
			}
			return this;
		}

		CBaseBlock *CBaseBlock::setBorderWidth(const size_t left, const size_t top, const size_t right, const size_t bottom)
		{
			if (getBlock() && (getBlock()->BorderWidth[0] != left || getBlock()->BorderWidth[1] != top || getBlock()->BorderWidth[2] != right || getBlock()->BorderWidth[3] != bottom))
			{
				getBlock()->BorderWidth[0] = left;
				getBlock()->BorderWidth[1] = top;
				getBlock()->BorderWidth[2] = right;
				getBlock()->BorderWidth[3] = bottom;
				if (m_pForm)
					m_pForm->LockRepaint();
				for (size_t index = 0; index < getControlCount(); index++)
					getControl(index)->UpdateRect();
				Repaint(false);
				if (m_pForm)
					m_pForm->UnlockRepaint();
			}
			return this;
		}

		CBaseBlock *CBaseBlock::setLeftBorderWidth(const size_t value)
		{
			if (getBlock() && getBlock()->BorderWidth[0] != value)
			{
				getBlock()->BorderWidth[0] = value;
				if (m_pForm)
					m_pForm->LockRepaint();
				for (size_t index = 0; index < getControlCount(); index++)
					getControl(index)->UpdateRect();
				Repaint(false);
				if (m_pForm)
					m_pForm->UnlockRepaint();
			}
			return this;
		}

		CBaseBlock *CBaseBlock::setTopBorderWidth(const size_t value)
		{
			if (getBlock() && getBlock()->BorderWidth[1] != value)
			{
				getBlock()->BorderWidth[1] = value;
				if (m_pForm)
					m_pForm->LockRepaint();
				for (size_t index = 0; index < getControlCount(); index++)
					getControl(index)->UpdateRect();
				Repaint(false);
				if (m_pForm)
					m_pForm->UnlockRepaint();
			}
			return this;
		}

		CBaseBlock *CBaseBlock::setRightBorderWidth(const size_t value)
		{
			if (getBlock() && getBlock()->BorderWidth[2] != value)
			{
				getBlock()->BorderWidth[2] = value;
				if (m_pForm)
					m_pForm->LockRepaint();
				for (size_t index = 0; index < getControlCount(); index++)
					getControl(index)->UpdateRect();
				Repaint(false);
				if (m_pForm)
					m_pForm->UnlockRepaint();
			}
			return this;
		}

		CBaseBlock *CBaseBlock::setBottomBorderWidth(const size_t value)
		{
			if (getBlock() && getBlock()->BorderWidth[3] != value)
			{
				getBlock()->BorderWidth[3] = value;
				if (m_pForm)
					m_pForm->LockRepaint();
				for (size_t index = 0; index < getControlCount(); index++)
					getControl(index)->UpdateRect();
				Repaint(false);
				if (m_pForm)
					m_pForm->UnlockRepaint();
			}
			return this;
		}

		CBaseBlock *CBaseBlock::setBorderRadius(const size_t value)
		{
			if (getBlock() && (getBlock()->BorderRadius[0] != value || getBlock()->BorderRadius[1] != value || getBlock()->BorderRadius[2] != value || getBlock()->BorderRadius[3] != value))
			{
				getBlock()->BorderRadius[0] = getBlock()->BorderRadius[1] = getBlock()->BorderRadius[2] = getBlock()->BorderRadius[3] = value;
				Repaint(false);
			}
			return this;
		}

		CBaseBlock *CBaseBlock::setBorderRadius(const size_t left_top, const size_t right_top, const size_t right_bottom, const size_t left_bottom)
		{
			if (getBlock() && (getBlock()->BorderRadius[0] != left_top || getBlock()->BorderRadius[1] != right_top || getBlock()->BorderRadius[2] != right_bottom || getBlock()->BorderRadius[3] != left_bottom))
			{
				getBlock()->BorderRadius[0] = left_top;
				getBlock()->BorderRadius[1] = right_top;
				getBlock()->BorderRadius[2] = right_bottom;
				getBlock()->BorderRadius[3] = left_bottom;
				Repaint(false);
			}
			return this;
		}

		CBaseBlock *CBaseBlock::setLeftTopRadius(const size_t value)
		{
			if (getBlock() && getBlock()->BorderRadius[0] != value)
			{
				getBlock()->BorderRadius[0] = value;
				Repaint(false);
			}
			return this;
		}

		CBaseBlock *CBaseBlock::setRightTopRadius(const size_t value)
		{
			if (getBlock() && getBlock()->BorderRadius[1] != value)
			{
				getBlock()->BorderRadius[1] = value;
				Repaint(false);
			}
			return this;
		}

		CBaseBlock *CBaseBlock::setRightBottomRadius(const size_t value)
		{
			if (getBlock() && getBlock()->BorderRadius[2] != value)
			{
				getBlock()->BorderRadius[2] = value;
				Repaint(false);
			}
			return this;
		}

		CBaseBlock *CBaseBlock::setLeftBottomRadius(const size_t value)
		{
			if (getBlock() && getBlock()->BorderRadius[3] != value)
			{
				getBlock()->BorderRadius[3] = value;
				Repaint(false);
			}
			return this;
		}

		CBaseBlock *CBaseBlock::setBorderColor(const APP_COLOR &value)
		{
			if (getBlock() && (getBlock()->BorderColor[0] != value || getBlock()->BorderColor[1] != value || getBlock()->BorderColor[2] != value || getBlock()->BorderColor[3] != value))
			{
				getBlock()->BorderColor[0] = getBlock()->BorderColor[1] = getBlock()->BorderColor[2] = getBlock()->BorderColor[3] = value;
				if (getBlock()->BorderWidth[0] > 0 || getBlock()->BorderWidth[1] > 0 || getBlock()->BorderWidth[2] > 0 || getBlock()->BorderWidth[3] > 0)
					Repaint(false);
			}
			return this;
		}

		CBaseBlock *CBaseBlock::setBorderColor(const APP_COLOR &left, const APP_COLOR &top, const APP_COLOR &right, const APP_COLOR &bottom)
		{
			if (getBlock() && (getBlock()->BorderColor[0] != left || getBlock()->BorderColor[1] != top || getBlock()->BorderColor[2] != right || getBlock()->BorderColor[3] != bottom))
			{
				getBlock()->BorderColor[0] = left;
				getBlock()->BorderColor[1] = top;
				getBlock()->BorderColor[2] = right;
				getBlock()->BorderColor[3] = bottom;
				if (getBlock()->BorderWidth[0] > 0 || getBlock()->BorderWidth[1] > 0 || getBlock()->BorderWidth[2] > 0 || getBlock()->BorderWidth[3] > 0)
					Repaint(false);
			}
			return this;
		}

		CBaseBlock *CBaseBlock::setLeftBorderColor(const APP_COLOR &value)
		{
			if (getBlock() && getBlock()->BorderColor[0] != value)
			{
				getBlock()->BorderColor[0] = value;
				if (getBlock()->BorderWidth[0] > 0)
					Repaint(false);
			}
			return this;
		}

		CBaseBlock *CBaseBlock::setTopBorderColor(const APP_COLOR &value)
		{
			if (getBlock() && getBlock()->BorderColor[1] != value)
			{
				getBlock()->BorderColor[1] = value;
				if (getBlock()->BorderWidth[1] > 0)
					Repaint(false);
			}
			return this;
		}

		CBaseBlock *CBaseBlock::setRightBorderColor(const APP_COLOR &value)
		{
			if (getBlock() && getBlock()->BorderColor[2] != value)
			{
				getBlock()->BorderColor[2] = value;
				if (getBlock()->BorderWidth[2] > 0)
					Repaint(false);
			}
			return this;
		}

		CBaseBlock *CBaseBlock::setBottomBorderColor(const APP_COLOR &value)
		{
			if (getBlock() && getBlock()->BorderColor[3] != value)
			{
				getBlock()->BorderColor[3] = value;
				if (getBlock()->BorderWidth[3] > 0)
					Repaint(false);
			}
			return this;
		}

		CBaseBlock *CBaseBlock::setBorderInterpolate(const bool value)
		{
			if (getBlock() && (getBlock()->BorderInterpolate[0] != value || getBlock()->BorderInterpolate[1] != value || getBlock()->BorderInterpolate[2] != value || getBlock()->BorderInterpolate[3] != value))
			{
				getBlock()->BorderInterpolate[0] = getBlock()->BorderInterpolate[1] = getBlock()->BorderInterpolate[2] = getBlock()->BorderInterpolate[3] = value;
				if (getBlock()->BorderImage[0].getWidth() > 0 || getBlock()->BorderImage[1].getWidth() > 0 || getBlock()->BorderImage[2].getWidth() > 0 || getBlock()->BorderImage[3].getWidth() > 0)
					Repaint(false);
			}
			return this;
		}

		CBaseBlock *CBaseBlock::setBorderInterpolate(const bool left, const bool top, const bool right, const bool bottom)
		{
			if (getBlock() && (getBlock()->BorderInterpolate[0] != left || getBlock()->BorderInterpolate[1] != top || getBlock()->BorderInterpolate[2] != right || getBlock()->BorderInterpolate[3] != bottom))
			{
				getBlock()->BorderInterpolate[0] = left;
				getBlock()->BorderInterpolate[1] = top;
				getBlock()->BorderInterpolate[2] = right;
				getBlock()->BorderInterpolate[3] = bottom;
				if (getBlock()->BorderImage[0].getWidth() > 0 || getBlock()->BorderImage[1].getWidth() > 0 || getBlock()->BorderImage[2].getWidth() > 0 || getBlock()->BorderImage[3].getWidth() > 0)
					Repaint(false);
			}
			return this;
		}

		CBaseBlock *CBaseBlock::setLeftBorderInterpolate(const bool value)
		{
			if (getBlock() && getBlock()->BorderInterpolate[0] != value)
			{
				getBlock()->BorderInterpolate[0] = value;
				if (getBlock()->BorderImage[0].getWidth() > 0)
					Repaint(false);
			}
			return this;
		}

		CBaseBlock *CBaseBlock::setTopBorderInterpolate(const bool value)
		{
			if (getBlock() && getBlock()->BorderInterpolate[1] != value)
			{
				getBlock()->BorderInterpolate[1] = value;
				if (getBlock()->BorderImage[1].getWidth() > 0)
					Repaint(false);
			}
			return this;
		}

		CBaseBlock *CBaseBlock::setRightBorderInterpolate(const bool value)
		{
			if (getBlock() && getBlock()->BorderInterpolate[2] != value)
			{
				getBlock()->BorderInterpolate[2] = value;
				if (getBlock()->BorderImage[2].getWidth() > 0)
					Repaint(false);
			}
			return this;
		}

		CBaseBlock *CBaseBlock::setBottomBorderInterpolate(const bool value)
		{
			if (getBlock() && getBlock()->BorderInterpolate[3] != value)
			{
				getBlock()->BorderInterpolate[3] = value;
				if (getBlock()->BorderImage[3].getWidth() > 0)
					Repaint(false);
			}
			return this;
		}

		CBaseBlock *CBaseBlock::setPadding(const math::RECTANGLE<size_t> &value)
		{
			if (getBlock() && value != getBlock()->Padding)
			{
				getBlock()->Padding = value;
				if (m_pForm)
					m_pForm->LockRepaint();
				for (size_t index = 0; index < getControlCount(); index++)
					getControl(index)->UpdateRect();
				Repaint(false);
				if (m_pForm)
					m_pForm->UnlockRepaint();
			}
			return this;
		}

		CBaseBlock *CBaseBlock::setPadding(const size_t value)
		{
			if (getBlock() && (getBlock()->Padding[0] != value || getBlock()->Padding[1] != value || getBlock()->Padding[2] != value || getBlock()->Padding[3] != value))
			{
				getBlock()->Padding[0] = getBlock()->Padding[1] = getBlock()->Padding[2] = getBlock()->Padding[3] = value;
				if (m_pForm)
					m_pForm->LockRepaint();
				for (size_t index = 0; index < getControlCount(); index++)
					getControl(index)->UpdateRect();
				Repaint(false);
				if (m_pForm)
					m_pForm->UnlockRepaint();
			}
			return this;
		}

		CBaseBlock *CBaseBlock::setPaddingLeft(const size_t value)
		{
			if (getBlock() && getBlock()->Padding[0] != value)
			{
				getBlock()->Padding[0] = value;
				if (m_pForm)
					m_pForm->LockRepaint();
				for (size_t index = 0; index < getControlCount(); index++)
					getControl(index)->UpdateRect();
				Repaint(false);
				if (m_pForm)
					m_pForm->UnlockRepaint();
			}
			return this;
		}

		CBaseBlock *CBaseBlock::setPaddingTop(const size_t value)
		{
			if (getBlock() && getBlock()->Padding[1] != value)
			{
				getBlock()->Padding[1] = value;
				if (m_pForm)
					m_pForm->LockRepaint();
				for (size_t index = 0; index < getControlCount(); index++)
					getControl(index)->UpdateRect();
				Repaint(false);
				if (m_pForm)
					m_pForm->UnlockRepaint();
			}
			return this;
		}

		CBaseBlock *CBaseBlock::setPaddingRight(const size_t value)
		{
			if (getBlock() && getBlock()->Padding[2] != value)
			{
				getBlock()->Padding[2] = value;
				if (m_pForm)
					m_pForm->LockRepaint();
				for (size_t index = 0; index < getControlCount(); index++)
					getControl(index)->UpdateRect();
				Repaint(false);
				if (m_pForm)
					m_pForm->UnlockRepaint();
			}
			return this;
		}

		CBaseBlock *CBaseBlock::setPaddingBottom(const size_t value)
		{
			if (getBlock() && getBlock()->Padding[3] != value)
			{
				getBlock()->Padding[3] = value;
				if (m_pForm)
					m_pForm->LockRepaint();
				for (size_t index = 0; index < getControlCount(); index++)
					getControl(index)->UpdateRect();
				Repaint(false);
				if (m_pForm)
					m_pForm->UnlockRepaint();
			}
			return this;
		}

		CBaseBlock *CBaseBlock::setCaptionText(const bool value)
		{
			if (getBlock() && getBlock()->CaptionText != value)
			{
				getBlock()->CaptionText = value;
				if (m_bSupportText)
					Repaint(false);
			}
			return this;
		}

		CBaseBlock *CBaseBlock::setCaptionShadow(const bool value)
		{
			if (getBlock() && getBlock()->CaptionShadow != value)
			{
				getBlock()->CaptionShadow = value;
				if (m_bSupportText)
					Repaint(false);
			}
			return this;
		}

		CBaseBlock *CBaseBlock::setCaptionColorsOverwrite(const bool value)
		{
			if (getBlock() && getBlock()->CaptionColorsOverwrite != value)
			{
				getBlock()->CaptionColorsOverwrite = value;
				if (m_bSupportText)
					Repaint(false);
			}
			return this;
		}

		CBaseBlock *CBaseBlock::setCaptionTextColor(const APP_COLOR &value)
		{
			if (getBlock() && getBlock()->CaptionTextColor != value)
			{
				getBlock()->CaptionTextColor = value;
				if (m_bSupportText)
					Repaint(false);
			}
			return this;
		}

		CBaseBlock *CBaseBlock::setCaptionShadowColor(const APP_COLOR &value)
		{
			if (getBlock() && getBlock()->CaptionShadowColor != value)
			{
				getBlock()->CaptionShadowColor = value;
				if (m_bSupportText)
					Repaint(false);
			}
			return this;
		}

		CBaseBlock *CBaseBlock::setCaptionHorizontalAlign(const TEXT_ALIGN value)
		{
			if (getBlock() && getBlock()->CaptionHorizontalAlign != value)
			{
				getBlock()->CaptionHorizontalAlign = value;
				if (m_bSupportText)
					Repaint(false);
			}
			return this;
		}

		CBaseBlock *CBaseBlock::setCaptionVerticalAlign(const VERTICAL_ALIGN value)
		{
			if (getBlock() && getBlock()->CaptionVerticalAlign != value)
			{
				getBlock()->CaptionVerticalAlign = value;
				if (m_bSupportText)
					Repaint(false);
			}
			return this;
		}

		CBaseBlock *CBaseBlock::setCaptionAntiAliazing(size_t value)
		{
			if (getBlock())
			{
				if (value == 1)
					value = 0;
				if (getBlock()->CaptionAntiAliazing != value)
				{
					getBlock()->CaptionAntiAliazing = value;
					if (m_bSupportText)
						Repaint(false);
				}
			}
			return this;
		}

		CBaseBlock *CBaseBlock::setCaptionOrientationOverwrite(const bool value)
		{
			if (getBlock() && value != getBlock()->CaptionOrientationOverwrite)
			{
				getBlock()->CaptionOrientationOverwrite = value;
				if (m_bSupportText)
					Repaint(false);
			}
			return this;
		}

		CBaseBlock *CBaseBlock::setCaptionOrientation(const int value)
		{
			if (getBlock() && (!getBlock()->CaptionOrientationOverwrite || value != getBlock()->CaptionOrientation))
			{
				getBlock()->CaptionOrientationOverwrite = true;
				getBlock()->CaptionOrientation = value;
				if (m_bSupportText)
					Repaint(false);
			}
			return this;
		}

		CBaseBlock *CBaseBlock::setCaptionScale(const math::POINT<double> &value)
		{
			if (getBlock() && (value.X != getBlock()->CaptionScale[0] || value.Y != getBlock()->CaptionScale[1]))
			{
				getBlock()->CaptionScale[0] = value.X;
				getBlock()->CaptionScale[1] = value.Y;
				if (m_bSupportText)
					Repaint(false);
			}
			return this;
		}

		CBaseBlock *CBaseBlock::setCaptionScaleX(const double value)
		{
			if (getBlock() && value != getBlock()->CaptionScale[0])
			{
				getBlock()->CaptionScale[0] = value;
				if (m_bSupportText)
					Repaint(false);
			}
			return this;
		}

		CBaseBlock *CBaseBlock::setCaptionScaleY(const double value)
		{
			if (getBlock() && value != getBlock()->CaptionScale[1])
			{
				getBlock()->CaptionScale[1] = value;
				if (m_bSupportText)
					Repaint(false);
			}
			return this;
		}

		CBaseBlock *CBaseBlock::setCaptionShift(const math::POINT<double> &value)
		{
			if (getBlock() && (value.X != getBlock()->CaptionShift[0] || value.Y != getBlock()->CaptionShift[1]))
			{
				getBlock()->CaptionShift[0] = value.X;
				getBlock()->CaptionShift[1] = value.Y;
				if (m_bSupportText)
					Repaint(false);
			}
			return this;
		}

		CBaseBlock *CBaseBlock::setCaptionShiftX(const double value)
		{
			if (getBlock() && value != getBlock()->CaptionShift[0])
			{
				getBlock()->CaptionShift[0] = value;
				if (m_bSupportText)
					Repaint(false);
			}
			return this;
		}

		CBaseBlock *CBaseBlock::setCaptionShiftY(const double value)
		{
			if (getBlock() && value != getBlock()->CaptionShift[1])
			{
				getBlock()->CaptionShift[1] = value;
				if (m_bSupportText)
					Repaint(false);
			}
			return this;
		}

		CBaseBlock *CBaseBlock::setBackgroundColor(const APP_COLOR &value)
		{
			if (getBlock() && getBlock()->BackgroundColor != value)
			{
				getBlock()->BackgroundColor = value;
				Repaint(false);
			}
			return this;
		}

		CBaseBlock *CBaseBlock::setBackgroundRepeat(const bool value)
		{
			if (getBlock() && (getBlock()->BackgroundRepeat[0] != value || getBlock()->BackgroundRepeat[1] != value))
			{
				getBlock()->BackgroundRepeat[0] = getBlock()->BackgroundRepeat[1] = value;
				if (getBlock()->BackgroundImage.getWidth() > 0)
					Repaint(false);
			}
			return this;
		}

		CBaseBlock *CBaseBlock::setBackgroundRepeat(const bool x, const bool y)
		{
			if (getBlock() && (getBlock()->BackgroundRepeat[0] != x || getBlock()->BackgroundRepeat[1] != y))
			{
				getBlock()->BackgroundRepeat[0] = x;
				getBlock()->BackgroundRepeat[1] = y;
				if (getBlock()->BackgroundImage.getWidth() > 0)
					Repaint(false);
			}
			return this;
		}

		CBaseBlock *CBaseBlock::setBackgroundRepeatX(const bool value)
		{
			if (getBlock() && getBlock()->BackgroundRepeat[0] != value)
			{
				getBlock()->BackgroundRepeat[0] = value;
				if (getBlock()->BackgroundImage.getWidth() > 0)
					Repaint(false);
			}
			return this;
		}

		CBaseBlock *CBaseBlock::setBackgroundRepeatY(const bool value)
		{
			if (getBlock() && getBlock()->BackgroundRepeat[1] != value)
			{
				getBlock()->BackgroundRepeat[1] = value;
				if (getBlock()->BackgroundImage.getWidth() > 0)
					Repaint(false);
			}
			return this;
		}

		CBaseBlock *CBaseBlock::setBackgroundPosition(const APP_POINT &value)
		{
			if (getBlock() && (getBlock()->BackgroundPosition[0] != value.X || getBlock()->BackgroundPosition[1] != value.Y))
			{
				getBlock()->BackgroundPosition[0] = value.X;
				getBlock()->BackgroundPosition[1] = value.Y;
				if (getBlock()->BackgroundImage.getWidth() > 0)
					Repaint(false);
			}
			return this;
		}

		CBaseBlock *CBaseBlock::setBackgroundPositionX(const int value)
		{
			if (getBlock() && getBlock()->BackgroundPosition[0] != value)
			{
				getBlock()->BackgroundPosition[0] = value;
				if (getBlock()->BackgroundImage.getWidth() > 0)
					Repaint(false);
			}
			return this;
		}

		CBaseBlock *CBaseBlock::setBackgroundPositionY(const int value)
		{
			if (getBlock() && getBlock()->BackgroundPosition[1] != value)
			{
				getBlock()->BackgroundPosition[1] = value;
				if (getBlock()->BackgroundImage.getWidth() > 0)
					Repaint(false);
			}
			return this;
		}

		CBaseBlock *CBaseBlock::setBackgroundPositionPercentage(const bool value)
		{
			if (getBlock() && (getBlock()->BackgroundPositionPercentage[0] != value || getBlock()->BackgroundPositionPercentage[1] != value))
			{
				getBlock()->BackgroundPositionPercentage[0] = getBlock()->BackgroundPositionPercentage[1] = value;
				if (getBlock()->BackgroundImage.getWidth() > 0)
					Repaint(false);
			}
			return this;
		}

		CBaseBlock *CBaseBlock::setBackgroundPositionPercentage(const bool x, const bool y)
		{
			if (getBlock() && (getBlock()->BackgroundPositionPercentage[0] != x || getBlock()->BackgroundPositionPercentage[1] != y))
			{
				getBlock()->BackgroundPositionPercentage[0] = x;
				getBlock()->BackgroundPositionPercentage[1] = y;
				if (getBlock()->BackgroundImage.getWidth() > 0)
					Repaint(false);
			}
			return this;
		}

		CBaseBlock *CBaseBlock::setBackgroundPositionPercentageX(const bool value)
		{
			if (getBlock() && getBlock()->BackgroundPositionPercentage[0] != value)
			{
				getBlock()->BackgroundPositionPercentage[0] = value;
				if (getBlock()->BackgroundImage.getWidth() > 0)
					Repaint(false);
			}
			return this;
		}

		CBaseBlock *CBaseBlock::setBackgroundPositionPercentageY(const bool value)
		{
			if (getBlock() && getBlock()->BackgroundPositionPercentage[1] != value)
			{
				getBlock()->BackgroundPositionPercentage[1] = value;
				if (getBlock()->BackgroundImage.getWidth() > 0)
					Repaint(false);
			}
			return this;
		}

		CBaseBlock *CBaseBlock::setBackgroundSize(const APP_POINT &value)
		{
			if (getBlock() && (getBlock()->BackgroundSize[0] != value.X || getBlock()->BackgroundSize[1] != value.Y))
			{
				getBlock()->BackgroundSize[0] = value.X;
				getBlock()->BackgroundSize[1] = value.Y;
				if (getBlock()->BackgroundImage.getWidth() > 0)
					Repaint(false);
			}
			return this;
		}

		CBaseBlock *CBaseBlock::setBackgroundSizeX(const int value)
		{
			if (getBlock() && getBlock()->BackgroundSize[0] != value)
			{
				getBlock()->BackgroundSize[0] = value;
				if (getBlock()->BackgroundImage.getWidth() > 0)
					Repaint(false);
			}
			return this;
		}

		CBaseBlock *CBaseBlock::setBackgroundSizeY(const int value)
		{
			if (getBlock() && getBlock()->BackgroundSize[1] != value)
			{
				getBlock()->BackgroundSize[1] = value;
				if (getBlock()->BackgroundImage.getWidth() > 0)
					Repaint(false);
			}
			return this;
		}

		CBaseBlock *CBaseBlock::setBackgroundInterpolate(const bool value)
		{
			if (getBlock() && getBlock()->BackgroundInterpolate != value)
			{
				getBlock()->BackgroundInterpolate = value;
				if (getBlock()->BackgroundImage.getWidth() > 0)
					Repaint(false);
			}
			return this;
		}

		CBaseBlock *CBaseBlock::setBackgroundRotation(const double value)
		{
			if (getBlock() && value != getBlock()->BackgroundRotation)
			{
				getBlock()->BackgroundRotation = value;
				if (getBlock()->BackgroundImage.getWidth() > 0)
					Repaint(false);
			}
			return this;
		}

		CBaseBlock *CBaseBlock::setBoxShadow(const bool value)
		{
			if (getBlock() && value != getBlock()->BoxShadow)
			{
				if (m_pForm)
					m_pForm->LockRepaint();
				Repaint(false);
				getBlock()->BoxShadow = value;
				Repaint(false);
				if (m_pForm)
					m_pForm->UnlockRepaint();
			}
			return this;
		}

		CBaseBlock *CBaseBlock::setBoxShadowColor(const APP_COLOR &value)
		{
			if (getBlock() && value != getBlock()->BoxShadowColor)
			{
				getBlock()->BoxShadowColor = value;
				if (getBlock()->BoxShadow)
					Repaint(false);
			}
			return this;
		}

		CBaseBlock *CBaseBlock::setBoxShadowShift(const APP_POINT &value)
		{
			if (getBlock() && value != getBlock()->BoxShadowShift)
			{
				if (m_pForm)
					m_pForm->LockRepaint();
				if (getBlock()->BoxShadow)
					Repaint(false);
				getBlock()->BoxShadowShift = value;
				if (getBlock()->BoxShadow)
					Repaint(false);
				if (m_pForm)
					m_pForm->UnlockRepaint();
			}
			return this;
		}

		CBaseBlock *CBaseBlock::setBoxShadowRadius(const size_t value)
		{
			if (getBlock() && value != getBlock()->BoxShadowRadius)
			{
				getBlock()->BoxShadowRadius = value;
				if (getBlock()->BoxShadow && getBlock()->BoxShadowColor.getAlpha() > 0)
					Repaint(false);
			}
			return this;
		}
#pragma endregion

#pragma region Overwrite parent methods
		APP_RECT CBaseBlock::getClientRect()
		{
			if (getBlock())
			{
				APP_RECT result{
					getRect().Left + (int)getBlock()->BorderWidth[0] + (int)getBlock()->Padding[0],
					getRect().Top + (int)getBlock()->BorderWidth[1] + (int)getBlock()->Padding[1],
					getRect().Right - (int)getBlock()->BorderWidth[2] - (int)getBlock()->Padding[2],
					getRect().Bottom - (int)getBlock()->BorderWidth[3] - (int)getBlock()->Padding[3]
				};
				if (!result.IsValid())
				{
					result.Right = result.Left;
					result.Bottom = result.Top;
				}

				return result;
			}
			return getRect();
		}

		APP_RECT CBaseBlock::getRenderRect()
		{
			APP_RECT result = getRect();
			if (getBlock() && getBlock()->BoxShadow && getBlock()->BoxShadowColor.getAlpha() > 0)
			{
				if (getBlock()->BoxShadowShift.X > 0)
					result.Right += getBlock()->BoxShadowShift.X;
				else
					result.Left += getBlock()->BoxShadowShift.X;
				if (getBlock()->BoxShadowShift.Y > 0)
					result.Bottom += getBlock()->BoxShadowShift.Y;
				else
					result.Top += getBlock()->BoxShadowShift.Y;
				result.Left -= (int)getBlock()->BoxShadowRadius;
				result.Right += (int)getBlock()->BoxShadowRadius;
				result.Top -= (int)getBlock()->BoxShadowRadius;
				result.Bottom += (int)getBlock()->BoxShadowRadius;
				if (!result.IsValid())
				{
					result.Right = result.Left;
					result.Bottom = result.Top;
				}
			}
			return result;
		}
#pragma endregion
	}
}