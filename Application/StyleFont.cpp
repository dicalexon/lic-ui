// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#include "StyleFont.h"

namespace licui
{
	namespace application
	{
		CStyleFont::CStyleFont(const String &name) :
			CFontData(),
			m_sClassName{ name }
		{

		}

		String CStyleFont::getClassName() const
		{
			return m_sClassName;
		}
	}
}