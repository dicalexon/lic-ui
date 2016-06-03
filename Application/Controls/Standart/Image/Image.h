// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#pragma once

#include "..\..\..\Types.h"
#include "..\..\Base\BaseBlock.h"

namespace licui
{
	namespace application
	{
		class CImage :public CBaseBlock
		{
		private:
			BLOCK m_sBlock;
			bool m_bAutoSize;
		protected:
			void NotifyOnPaint(APP_RECT clip) override;

			BLOCK *getBlock() override;
		public:
			virtual bool getAutoSize() const;

			virtual CImage *setAutoSize(const bool value);

			CImage();
			CImage(CControl *parent);
			CImage(CForm *form);

			void UpdateRect() override;

			CControl *setAlign(const ALIGN value) override;
			CControl *setRect(APP_RECT value) override;
		public:
			using CBaseBlock::getOnMouseMove;
			using CBaseBlock::getOnLeftMouseButtonDown;
			using CBaseBlock::getOnLeftMouseButtonUp;
			using CBaseBlock::getOnLeftMouseButtonDoubleClick;
			using CBaseBlock::getOnRightMouseButtonDown;
			using CBaseBlock::getOnRightMouseButtonUp;
			using CBaseBlock::getOnRightMouseButtonDoubleClick;
			using CBaseBlock::getOnMiddleMouseButtonDown;
			using CBaseBlock::getOnMiddleMouseButtonUp;
			using CBaseBlock::getOnMiddleMouseButtonDoubleClick;
			using CBaseBlock::getOnMouseVerticalWheel;
			using CBaseBlock::getOnMouseHorizontalWheel;
			using CBaseBlock::getOnMouseHover;
			using CBaseBlock::getOnMouseLeave;
			using CBaseBlock::getOnChangeParentStyle;
			using CBaseBlock::getOnChangeStyle;
			using CBaseBlock::getOnShow;
			using CBaseBlock::getOnBeforeHide;
			using CBaseBlock::getOnHide;
			using CBaseBlock::getOnPaint;
			using CBaseBlock::getOnParentResize;
			using CBaseBlock::getOnParentMove;
			using CBaseBlock::getOnBeforeResize;
			using CBaseBlock::getOnResize;
			using CBaseBlock::getOnBeforeMove;
			using CBaseBlock::getOnMove;
			using CBaseBlock::setOnMouseMove;
			using CBaseBlock::setOnLeftMouseButtonDown;
			using CBaseBlock::setOnLeftMouseButtonUp;
			using CBaseBlock::setOnLeftMouseButtonDoubleClick;
			using CBaseBlock::setOnRightMouseButtonDown;
			using CBaseBlock::setOnRightMouseButtonUp;
			using CBaseBlock::setOnRightMouseButtonDoubleClick;
			using CBaseBlock::setOnMiddleMouseButtonDown;
			using CBaseBlock::setOnMiddleMouseButtonUp;
			using CBaseBlock::setOnMiddleMouseButtonDoubleClick;
			using CBaseBlock::setOnMouseVerticalWheel;
			using CBaseBlock::setOnMouseHorizontalWheel;
			using CBaseBlock::setOnMouseHover;
			using CBaseBlock::setOnMouseLeave;
			using CBaseBlock::setOnChangeParentStyle;
			using CBaseBlock::setOnChangeStyle;
			using CBaseBlock::setOnShow;
			using CBaseBlock::setOnBeforeHide;
			using CBaseBlock::setOnHide;
			using CBaseBlock::setOnPaint;
			using CBaseBlock::setOnParentResize;
			using CBaseBlock::setOnParentMove;
			using CBaseBlock::setOnBeforeResize;
			using CBaseBlock::setOnResize;
			using CBaseBlock::setOnBeforeMove;
			using CBaseBlock::setOnMove;
			using CBaseBlock::getControlStyle;
			using CBaseBlock::getStyle;
			using CBaseBlock::getUseStyle;
			using CBaseBlock::getConstraints;
			using CBaseBlock::getMinConstraints;
			using CBaseBlock::getMaxConstraints;
			using CBaseBlock::getMinWidth;
			using CBaseBlock::getMinHeight;
			using CBaseBlock::getMaxWidth;
			using CBaseBlock::getMaxHeight;
			using CBaseBlock::getZIndex;
			using CBaseBlock::setParent;
			using CBaseBlock::setStyle;
			using CBaseBlock::setUseStyle;
			using CBaseBlock::setConstraints;
			using CBaseBlock::setMinConstraints;
			using CBaseBlock::setMinWidth;
			using CBaseBlock::setMinHeight;
			using CBaseBlock::setMaxWidth;
			using CBaseBlock::setMaxHeight;
			using CBaseBlock::setPosition;
			using CBaseBlock::setLeft;
			using CBaseBlock::setTop;
			using CBaseBlock::setSize;
			using CBaseBlock::setWidth;
			using CBaseBlock::setHeight;
			using CBaseBlock::setCursor;
			using CBaseBlock::setZIndex;
			using CBaseBlock::getBorderAntiAliazing;
			using CBaseBlock::getBorderWidth;
			using CBaseBlock::getLeftBorderWidth;
			using CBaseBlock::getTopBorderWidth;
			using CBaseBlock::getRightBorderWidth;
			using CBaseBlock::getBottomBorderWidth;
			using CBaseBlock::getBorderRadius;
			using CBaseBlock::getLeftTopRadius;
			using CBaseBlock::getRightTopRadius;
			using CBaseBlock::getRightBottomRadius;
			using CBaseBlock::getLeftBottomRadius;
			using CBaseBlock::getLeftBorderColor;
			using CBaseBlock::getTopBorderColor;
			using CBaseBlock::getRightBorderColor;
			using CBaseBlock::getBottomBorderColor;
			using CBaseBlock::getLeftBorderImage;
			using CBaseBlock::getTopBorderImage;
			using CBaseBlock::getRightBorderImage;
			using CBaseBlock::getBottomBorderImage;
			using CBaseBlock::getLeftBorderInterpolate;
			using CBaseBlock::getTopBorderInterpolate;
			using CBaseBlock::getRightBorderInterpolate;
			using CBaseBlock::getBottomBorderInterpolate;
			using CBaseBlock::getPadding;
			using CBaseBlock::getPaddingLeft;
			using CBaseBlock::getPaddingTop;
			using CBaseBlock::getPaddingRight;
			using CBaseBlock::getPaddingBottom;
			using CBaseBlock::getBackgrondColor;
			using CBaseBlock::getBackgroundImage;
			using CBaseBlock::getBackgroundRepeatX;
			using CBaseBlock::getBackgroundRepeatY;
			using CBaseBlock::getBackgroundPosition;
			using CBaseBlock::getBackgroundPositionX;
			using CBaseBlock::getBackgroundPositionY;
			using CBaseBlock::getBackgroundPositionPercentageX;
			using CBaseBlock::getBackgroundPositionPercentageY;
			using CBaseBlock::getBackgroundSize;
			using CBaseBlock::getBackgroundSizeX;
			using CBaseBlock::getBackgroundSizeY;
			using CBaseBlock::getBackgroundInterpolate;
			using CBaseBlock::getBackgroundRotation;
			using CBaseBlock::getBoxShadow;
			using CBaseBlock::getBoxShadowColor;
			using CBaseBlock::getBoxShadowShift;
			using CBaseBlock::getBoxShadowRadius;
			using CBaseBlock::setBorderAntiAliazing;
			using CBaseBlock::setBorderWidth;
			using CBaseBlock::setLeftBorderWidth;
			using CBaseBlock::setTopBorderWidth;
			using CBaseBlock::setRightBorderWidth;
			using CBaseBlock::setBottomBorderWidth;
			using CBaseBlock::setBorderRadius;
			using CBaseBlock::setLeftTopRadius;
			using CBaseBlock::setRightTopRadius;
			using CBaseBlock::setRightBottomRadius;
			using CBaseBlock::setLeftBottomRadius;
			using CBaseBlock::setBorderColor;
			using CBaseBlock::setLeftBorderColor;
			using CBaseBlock::setTopBorderColor;
			using CBaseBlock::setRightBorderColor;
			using CBaseBlock::setBottomBorderColor;
			using CBaseBlock::setBorderInterpolate;
			using CBaseBlock::setLeftBorderInterpolate;
			using CBaseBlock::setTopBorderInterpolate;
			using CBaseBlock::setRightBorderInterpolate;
			using CBaseBlock::setBottomBorderInterpolate;
			using CBaseBlock::setPadding;
			using CBaseBlock::setPaddingLeft;
			using CBaseBlock::setPaddingTop;
			using CBaseBlock::setPaddingRight;
			using CBaseBlock::setPaddingBottom;
			using CBaseBlock::setBackgroundColor;
			using CBaseBlock::setBackgroundRepeat;
			using CBaseBlock::setBackgroundRepeatX;
			using CBaseBlock::setBackgroundRepeatY;
			using CBaseBlock::setBackgroundPosition;
			using CBaseBlock::setBackgroundPositionX;
			using CBaseBlock::setBackgroundPositionY;
			using CBaseBlock::setBackgroundPositionPercentage;
			using CBaseBlock::setBackgroundPositionPercentageX;
			using CBaseBlock::setBackgroundPositionPercentageY;
			using CBaseBlock::setBackgroundSize;
			using CBaseBlock::setBackgroundSizeX;
			using CBaseBlock::setBackgroundSizeY;
			using CBaseBlock::setBackgroundInterpolate;
			using CBaseBlock::setBackgroundRotation;
			using CBaseBlock::setBoxShadow;
			using CBaseBlock::setBoxShadowColor;
			using CBaseBlock::setBoxShadowShift;
			using CBaseBlock::setBoxShadowRadius;
		};
	}
}