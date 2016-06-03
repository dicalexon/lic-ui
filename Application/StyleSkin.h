// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#pragma once

#include "..\Strings\Strings.h"
#include "..\Math\Rectangle.h"
#include "Types.h"

namespace licui
{
	namespace application
	{
		class CStyleSkin
		{
		private:
			String m_sClassName;
			APP_RECT m_sRect;
			CStyleImage *m_pImage;
		public:
			String getClassName() const;
			APP_RECT &getRect();
			CStyleImage *getImage();

			CStyleSkin(const String &name, CStyleImage *image);
		};
	}
}