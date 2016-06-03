// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#pragma once

#include "Types.h"
#include <vector>

namespace licui
{
	namespace application
	{
		class CImageManager
		{
		private:
			class CItem
			{
			public:
				APP_IMAGE *AppImage;
				IImage *Image;

				CItem();
				CItem(APP_IMAGE *app_image, IImage *image);
				~CItem();
			};
		private:
			CForm *m_pForm;
			std::vector<CItem*> m_aItems;
			bool m_bItemsSorted;
		public:
			IImage *getImage(APP_IMAGE *app_image);

			CImageManager(CForm &form);
			~CImageManager();

			void FreeImage(APP_IMAGE *app_image);
			void FreeImages();
		};
	}
}