// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#pragma once

namespace licui
{
	template<class DstType, class SrcType> DstType cast(SrcType value);

	template<class DstType, class SrcType> DstType cast(SrcType value)
	{
		DstType result{ nullptr };
		try
		{
			result = dynamic_cast<DstType>(value);
		}
		catch (...)
		{
			result = nullptr;
		}
		return result;
	}
}