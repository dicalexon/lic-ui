// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#pragma once

#include "..\..\..\Strings\Strings.h"
#include "..\..\..\Graphics\ClassifyPoint.h"
#include "..\..\Types.h"
#include "..\..\Control.h"

namespace licui
{
	namespace application
	{
		class CBaseBlock :public CControl
		{
		public:
			struct BLOCK
			{
				size_t BorderAntiAliazing;
				math::RECTANGLE<size_t> BorderWidth;
				math::RECTANGLE<size_t> BorderRadius;
				APP_COLOR BorderColor[4];
				APP_IMAGE BorderImage[4];
				math::RECTANGLE<bool> BorderInterpolate;
				math::RECTANGLE<size_t> Padding;
				TEXT_ALIGN CaptionHorizontalAlign;
				VERTICAL_ALIGN CaptionVerticalAlign;
				size_t CaptionAntiAliazing;
				bool CaptionText;
				bool CaptionShadow;
				bool CaptionColorsOverwrite;
				APP_COLOR CaptionTextColor;
				APP_COLOR CaptionShadowColor;
				bool CaptionOrientationOverwrite;
				int CaptionOrientation;
				math::POINT<double> CaptionScale;
				math::POINT<double> CaptionShift;
				APP_COLOR BackgroundColor;
				APP_IMAGE BackgroundImage;
				math::POINT<bool> BackgroundRepeat;
				APP_POINT BackgroundPosition;
				math::POINT<bool> BackgroundPositionPercentage;
				APP_POINT BackgroundSize;
				bool BackgroundInterpolate;
				double BackgroundRotation;
				String StyleName;
				bool BoxShadow;
				APP_COLOR BoxShadowColor;
				APP_POINT BoxShadowShift;
				size_t BoxShadowRadius;

				BLOCK();
			};
		private:
			struct BORDER_IMAGE_DATA
			{
				bool Renderable;
				APP_IMAGE *Image;
				APP_RECT Rect;
				bool RepeatX;
				bool RepeatY;
				APP_RECT Clip;
				double X;
				double Y;
				double Sx;
				double Sy;
				graphics::BLOCK_POINT_LOCATION Location;
			};

			bool FindImage(APP_IMAGE &def, const String &style, APP_IMAGE **img, APP_RECT &rect, double &angle);
			bool CalculateBackgroundImagePositionAndScaling(const APP_RECT &rect, const int width, const int height, double &x, double &y, double &sx, double &sy);
			void FillBorderImagesData(BORDER_IMAGE_DATA *images, const int width, const int height);
			bool CalculateCaptionParams(const String &caption, const int width, const int height, double &x, double &y, double &angle, APP_COLOR &text, APP_COLOR &shadow, APP_POINT &size);
		protected:
			virtual void DoRenderBlock(const APP_RECT &clip);
			virtual void DoRenderBackgroundImage(const APP_RECT &clip);
			virtual void DoRenderBorderImages(const APP_RECT &clip);
			virtual void DoRenderCaption(const String &caption, const APP_RECT &clip);
			virtual void DoRenderRect(const APP_COLOR &color, const APP_RECT &rect, const APP_RECT &clip);
			virtual void DoRenderBoxShadow(const APP_RECT &clip);
			virtual void DoRender(const String &m_sCaption, APP_RECT clip);

			bool UpdateFromStyle() override;

			virtual BLOCK *getBlock();
			virtual size_t getBorderAntiAliazing();
			virtual APP_RECT getBorderWidth();
			virtual size_t getLeftBorderWidth();
			virtual size_t getTopBorderWidth();
			virtual size_t getRightBorderWidth();
			virtual size_t getBottomBorderWidth();
			virtual APP_RECT getBorderRadius();
			virtual size_t getLeftTopRadius();
			virtual size_t getRightTopRadius();
			virtual size_t getRightBottomRadius();
			virtual size_t getLeftBottomRadius();
			virtual APP_COLOR getLeftBorderColor();
			virtual APP_COLOR getTopBorderColor();
			virtual APP_COLOR getRightBorderColor();
			virtual APP_COLOR getBottomBorderColor();
			virtual APP_IMAGE *getLeftBorderImage();
			virtual APP_IMAGE *getTopBorderImage();
			virtual APP_IMAGE *getRightBorderImage();
			virtual APP_IMAGE *getBottomBorderImage();
			virtual bool getLeftBorderInterpolate();
			virtual bool getTopBorderInterpolate();
			virtual bool getRightBorderInterpolate();
			virtual bool getBottomBorderInterpolate();
			virtual APP_RECT getPadding();
			virtual size_t getPaddingLeft();
			virtual size_t getPaddingTop();
			virtual size_t getPaddingRight();
			virtual size_t getPaddingBottom();
			virtual TEXT_ALIGN getCaptionHorizontalAlign();
			virtual bool getCaptionText();
			virtual bool getCaptionShadow();
			virtual bool getCaptionColorsOverwrite();
			virtual APP_COLOR getCaptionTextColor();
			virtual APP_COLOR getCaptionShadowColor();
			virtual VERTICAL_ALIGN getCaptionVerticalAlign();
			virtual size_t getCaptionAntiAliazing();
			virtual bool getCaptionOrientationOverwrite();
			virtual int getCaptionOrientation();
			virtual math::POINT<double> getCaptionScale();
			virtual double getCaptionScaleX();
			virtual double getCaptionScaleY();
			virtual math::POINT<double> getCaptionShift();
			virtual double getCaptionShiftX();
			virtual double getCaptionShiftY();
			virtual APP_COLOR getBackgrondColor();
			virtual APP_IMAGE *getBackgroundImage();
			virtual bool getBackgroundRepeatX();
			virtual bool getBackgroundRepeatY();
			virtual APP_POINT getBackgroundPosition();
			virtual int getBackgroundPositionX();
			virtual int getBackgroundPositionY();
			virtual bool getBackgroundPositionPercentageX();
			virtual bool getBackgroundPositionPercentageY();
			virtual APP_POINT getBackgroundSize();
			virtual int getBackgroundSizeX();
			virtual int getBackgroundSizeY();
			virtual bool getBackgroundInterpolate();
			virtual double getBackgroundRotation();
			virtual bool getBoxShadow();
			virtual APP_COLOR getBoxShadowColor();
			virtual APP_POINT getBoxShadowShift();
			virtual size_t getBoxShadowRadius();

			virtual CBaseBlock *setBorderAntiAliazing(size_t value);
			virtual CBaseBlock *setBorderWidth(const size_t value);
			virtual CBaseBlock *setBorderWidth(const size_t left, const size_t top, const size_t right, const size_t bottom);
			virtual CBaseBlock *setLeftBorderWidth(const size_t value);
			virtual CBaseBlock *setTopBorderWidth(const size_t value);
			virtual CBaseBlock *setRightBorderWidth(const size_t value);
			virtual CBaseBlock *setBottomBorderWidth(const size_t value);
			virtual CBaseBlock *setBorderRadius(const size_t value);
			virtual CBaseBlock *setBorderRadius(const size_t left_top, const size_t right_top, const size_t right_bottom, const size_t left_bottom);
			virtual CBaseBlock *setLeftTopRadius(const size_t value);
			virtual CBaseBlock *setRightTopRadius(const size_t value);
			virtual CBaseBlock *setRightBottomRadius(const size_t value);
			virtual CBaseBlock *setLeftBottomRadius(const size_t value);
			virtual CBaseBlock *setBorderColor(const APP_COLOR &value);
			virtual CBaseBlock *setBorderColor(const APP_COLOR &left, const APP_COLOR &top, const APP_COLOR &right, const APP_COLOR &bottom);
			virtual CBaseBlock *setLeftBorderColor(const APP_COLOR &value);
			virtual CBaseBlock *setTopBorderColor(const APP_COLOR &value);
			virtual CBaseBlock *setRightBorderColor(const APP_COLOR &value);
			virtual CBaseBlock *setBottomBorderColor(const APP_COLOR &value);
			virtual CBaseBlock *setBorderInterpolate(const bool value);
			virtual CBaseBlock *setBorderInterpolate(const bool left, const bool top, const bool right, const bool bottom);
			virtual CBaseBlock *setLeftBorderInterpolate(const bool value);
			virtual CBaseBlock *setTopBorderInterpolate(const bool value);
			virtual CBaseBlock *setRightBorderInterpolate(const bool value);
			virtual CBaseBlock *setBottomBorderInterpolate(const bool value);
			virtual CBaseBlock *setPadding(const math::RECTANGLE<size_t> &value);
			virtual CBaseBlock *setPadding(const size_t value);
			virtual CBaseBlock *setPaddingLeft(const size_t value);
			virtual CBaseBlock *setPaddingTop(const size_t value);
			virtual CBaseBlock *setPaddingRight(const size_t value);
			virtual CBaseBlock *setPaddingBottom(const size_t value);
			virtual CBaseBlock *setCaptionText(const bool value);
			virtual CBaseBlock *setCaptionShadow(const bool value);
			virtual CBaseBlock *setCaptionColorsOverwrite(const bool value);
			virtual CBaseBlock *setCaptionTextColor(const APP_COLOR &value);
			virtual CBaseBlock *setCaptionShadowColor(const APP_COLOR &value);
			virtual CBaseBlock *setCaptionHorizontalAlign(const TEXT_ALIGN value);
			virtual CBaseBlock *setCaptionVerticalAlign(const VERTICAL_ALIGN value);
			virtual CBaseBlock *setCaptionAntiAliazing(size_t value);
			virtual CBaseBlock *setCaptionOrientationOverwrite(const bool value);
			virtual CBaseBlock *setCaptionOrientation(const int value);
			virtual CBaseBlock *setCaptionScale(const math::POINT<double> &value);
			virtual CBaseBlock *setCaptionScaleX(const double value);
			virtual CBaseBlock *setCaptionScaleY(const double value);
			virtual CBaseBlock *setCaptionShift(const math::POINT<double> &value);
			virtual CBaseBlock *setCaptionShiftX(const double value);
			virtual CBaseBlock *setCaptionShiftY(const double value);
			virtual CBaseBlock *setBackgroundColor(const APP_COLOR &value);
			virtual CBaseBlock *setBackgroundRepeat(const bool value);
			virtual CBaseBlock *setBackgroundRepeat(const bool x, const bool y);
			virtual CBaseBlock *setBackgroundRepeatX(const bool value);
			virtual CBaseBlock *setBackgroundRepeatY(const bool value);
			virtual CBaseBlock *setBackgroundPosition(const APP_POINT &value);
			virtual CBaseBlock *setBackgroundPositionX(const int value);
			virtual CBaseBlock *setBackgroundPositionY(const int value);
			virtual CBaseBlock *setBackgroundPositionPercentage(const bool value);
			virtual CBaseBlock *setBackgroundPositionPercentage(const bool x, const bool y);
			virtual CBaseBlock *setBackgroundPositionPercentageX(const bool value);
			virtual CBaseBlock *setBackgroundPositionPercentageY(const bool value);
			virtual CBaseBlock *setBackgroundSize(const APP_POINT &value);
			virtual CBaseBlock *setBackgroundSizeX(const int value);
			virtual CBaseBlock *setBackgroundSizeY(const int value);
			virtual CBaseBlock *setBackgroundInterpolate(const bool value);
			virtual CBaseBlock *setBackgroundRotation(const double value);
			virtual CBaseBlock *setBoxShadow(const bool value);
			virtual CBaseBlock *setBoxShadowColor(const APP_COLOR &value);
			virtual CBaseBlock *setBoxShadowShift(const APP_POINT &value);
			virtual CBaseBlock *setBoxShadowRadius(const size_t value);
		public:
			APP_RECT getClientRect() override;
			APP_RECT getRenderRect() override;
		};
		/*
		using C::getBorderAntiAliazing;
		using C::getBorderWidth;
		using C::getLeftBorderWidth;
		using C::getTopBorderWidth;
		using C::getRightBorderWidth;
		using C::getBottomBorderWidth;
		using C::getBorderRadius;
		using C::getLeftTopRadius;
		using C::getRightTopRadius;
		using C::getRightBottomRadius;
		using C::getLeftBottomRadius;
		using C::getLeftBorderColor;
		using C::getTopBorderColor;
		using C::getRightBorderColor;
		using C::getBottomBorderColor;
		using C::getLeftBorderImage;
		using C::getTopBorderImage;
		using C::getRightBorderImage;
		using C::getBottomBorderImage;
		using C::getLeftBorderInterpolate;
		using C::getTopBorderInterpolate;
		using C::getRightBorderInterpolate;
		using C::getBottomBorderInterpolate;
		using C::getPadding;
		using C::getPaddingLeft;
		using C::getPaddingTop;
		using C::getPaddingRight;
		using C::getPaddingBottom;
		using C::getCaptionHorizontalAlign;
		using C::getCaptionText;
		using C::getCaptionShadow;
		using C::getCaptionColorsOverwrite;
		using C::getCaptionTextColor;
		using C::getCaptionShadowColor;
		using C::getCaptionVerticalAlign;
		using C::getCaptionAntiAliazing;
		using C::getCaptionOrientationOverwrite;
		using C::getCaptionOrientation;
		using C::getCaptionScale;
		using C::getCaptionScaleX;
		using C::getCaptionScaleY;
		using C::getCaptionShift;
		using C::getCaptionShiftX;
		using C::getCaptionShiftY;
		using C::getBackgrondColor;
		using C::getBackgroundImage;
		using C::getBackgroundRepeatX;
		using C::getBackgroundRepeatY;
		using C::getBackgroundPosition;
		using C::getBackgroundPositionX;
		using C::getBackgroundPositionY;
		using C::getBackgroundPositionPercentageX;
		using C::getBackgroundPositionPercentageY;
		using C::getBackgroundSize;
		using C::getBackgroundSizeX;
		using C::getBackgroundSizeY;
		using C::getBackgroundInterpolate;
		using C::getBackgroundRotation;
		using C::getBoxShadow;
		using C::getBoxShadowColor;
		using C::getBoxShadowShift;
		using C::getBoxShadowRadius;
		using C::setBorderAntiAliazing;
		using C::setBorderWidth;
		using C::setLeftBorderWidth;
		using C::setTopBorderWidth;
		using C::setRightBorderWidth;
		using C::setBottomBorderWidth;
		using C::setBorderRadius;
		using C::setLeftTopRadius;
		using C::setRightTopRadius;
		using C::setRightBottomRadius;
		using C::setLeftBottomRadius;
		using C::setBorderColor;
		using C::setLeftBorderColor;
		using C::setTopBorderColor;
		using C::setRightBorderColor;
		using C::setBottomBorderColor;
		using C::setBorderInterpolate;
		using C::setLeftBorderInterpolate;
		using C::setTopBorderInterpolate;
		using C::setRightBorderInterpolate;
		using C::setBottomBorderInterpolate;
		using C::setPadding;
		using C::setPaddingLeft;
		using C::setPaddingTop;
		using C::setPaddingRight;
		using C::setPaddingBottom;
		using C::setCaptionText;
		using C::setCaptionShadow;
		using C::setCaptionColorsOverwrite;
		using C::setCaptionTextColor;
		using C::setCaptionShadowColor;
		using C::setCaptionHorizontalAlign;
		using C::setCaptionVerticalAlign;
		using C::setCaptionAntiAliazing;
		using C::setCaptionOrientationOverwrite;
		using C::setCaptionOrientation;
		using C::setCaptionScale;
		using C::setCaptionScaleX;
		using C::setCaptionScaleY;
		using C::setCaptionShift;
		using C::setCaptionShiftX;
		using C::setCaptionShiftY;
		using C::setBackgroundColor;
		using C::setBackgroundRepeat;
		using C::setBackgroundRepeatX;
		using C::setBackgroundRepeatY;
		using C::setBackgroundPosition;
		using C::setBackgroundPositionX;
		using C::setBackgroundPositionY;
		using C::setBackgroundPositionPercentage;
		using C::setBackgroundPositionPercentageX;
		using C::setBackgroundPositionPercentageY;
		using C::setBackgroundSize;
		using C::setBackgroundSizeX;
		using C::setBackgroundSizeY;
		using C::setBackgroundInterpolate;
		using C::setBackgroundRotation;
		using C::setBoxShadow;
		using C::setBoxShadowColor;
		using C::setBoxShadowShift;
		using C::setBoxShadowRadius;
		*/
	}
}