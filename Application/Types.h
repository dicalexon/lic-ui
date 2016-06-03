// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#pragma once

#include "..\Math\Point.h"
#include "..\Math\Rectangle.h"
#include "..\Math\Vector.h"
#include "..\Math\Matrix.h"
#include "..\Graphics\Pixel.h"
#include "..\Graphics\Image.h"
#include "..\Graphics\ClassifyPoint.h"

namespace licui
{
	namespace application
	{
		typedef math::POINT<int> APP_POINT;
		typedef math::RECTANGLE<int> APP_RECT;
		typedef math::VECTOR<double> APP_VECTOR;
		typedef math::MATRIX<double> APP_MATRIX;
		typedef graphics::PIXEL<unsigned char, 4> APP_COLOR;
		typedef graphics::IMAGE<unsigned char, 4> APP_IMAGE;
		typedef graphics::IMAGE<double, graphics::bplBottom + 1> APP_IMAGE_MAP;

		enum TEXT_ALIGN
		{
			taLeft,
			taRight,
			taCenter,
			taJustify
		};

		enum VERTICAL_ALIGN
		{
			vaTop,
			vaMiddle,
			vaBottom
		};

		enum ALIGN
		{
			alNone,
			alLeft,
			alTop,
			alRight,
			alBottom,
			alClient
		};

		enum CURSOR_TYPE
		{
			ctNone,
			ctAppStarting,
			ctArrow,
			ctCross,
			ctHand,
			ctHelp,
			ctIBeam,
			ctNo,
			ctSizeAll,
			ctSizeNortheastSouthwest,
			ctSizeNorthSouth,
			ctSizeNorthwestSoutheast,
			ctSizeWestEast,
			ctUpArrow,
			ctWait
		};

		class IWindow;
		class CFontData;
		class IFont;
		class IPresenter;
		class IImage;
		class CStyleFont;
		class CStyleImage;
		class CStyleSkin;
		class CStyle;
		class CComponent;
		class CControl;
		class CForm;
		class CForm;
		class CImageManager;
	}
}