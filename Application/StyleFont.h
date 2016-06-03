// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#pragma once

#include "..\strings\Strings.h"
#include "Types.h"
#include "Font.h"

namespace licui
{
	namespace application
	{
		class CStyleFont : public CFontData
		{
		protected:
			String m_sClassName;
		public:
			String getClassName() const;

			CStyleFont(const String &name);
		};
	}
}