// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#include "StyleSkin.h"

namespace licui
{
	namespace application
	{
		CStyleSkin::CStyleSkin(const String &name, CStyleImage *image):
			m_sClassName{ name },
			m_sRect{ 0, 0, 0, 0 },
			m_pImage{ image }
		{

		}

		String CStyleSkin::getClassName() const
		{
			return m_sClassName;
		}

		APP_RECT &CStyleSkin::getRect()
		{
			return m_sRect;
		}

		CStyleImage *CStyleSkin::getImage()
		{
			return m_pImage;
		}
	}
}