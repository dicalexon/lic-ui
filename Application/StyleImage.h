// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#pragma once

#include "..\Strings\Strings.h"
#include "Types.h"

namespace licui
{
	namespace application
	{
		class CStyleImage
		{
		private:
			String m_sClassName;
			APP_IMAGE m_sImage;
		public:
			String getClassName() const;
			APP_IMAGE *getImage();

			CStyleImage(const String &name);
		};
	}
}