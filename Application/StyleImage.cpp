// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#include "StyleImage.h"

namespace licui
{
	namespace application
	{
		CStyleImage::CStyleImage(const String &name):
			m_sClassName{ name }
		{

		}

		String CStyleImage::getClassName() const
		{
			return m_sClassName;
		}

		APP_IMAGE *CStyleImage::getImage()
		{
			return &m_sImage;
		}
	}
}