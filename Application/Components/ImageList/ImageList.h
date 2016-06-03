// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#pragma once

#include "..\..\Types.h"
#include "..\..\Component.h"
#include <vector>

namespace licui
{
	namespace application
	{
		class CImageList :public CComponent
		{
		private:
			std::vector<APP_IMAGE> m_aImages;
		public:
			CImageList();
			CImageList(CForm *form);

			virtual size_t getCount() const;
			virtual APP_IMAGE *getImage(const size_t index);

			virtual APP_IMAGE *Add();
			virtual void Delete(const size_t index);
			virtual void Clear();
			virtual void Update(); // Call to reflect updates after editing of image. The other way is to update control(s) using this image list
		};
	}
}