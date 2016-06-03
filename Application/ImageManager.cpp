// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#include "ImageManager.h"
#include "Image.h"
#include "Form.h"
#include "Presenter.h"

namespace licui
{
	namespace application
	{
#pragma region CItem
		CImageManager::CItem::CItem() :
			AppImage{ nullptr },
			Image{ nullptr }
		{

		}

		CImageManager::CItem::CItem(APP_IMAGE *app_image, IImage *image) :
			AppImage{ app_image },
			Image{ image }
		{

		}

		CImageManager::CItem::~CItem()
		{
			if (Image)
				Image->Release();
		}
#pragma endregion

#pragma region CImageManager
		CImageManager::CImageManager(CForm &form) :
			m_pForm{ &form },
			m_bItemsSorted{ true }
		{

		}

		CImageManager::~CImageManager()
		{
			FreeImages();
		}

		IImage *CImageManager::getImage(APP_IMAGE *app_image)
		{
			if (!app_image)
				return nullptr;
			if (!m_bItemsSorted)
			{
				std::sort(m_aItems.begin(), m_aItems.end(), [](const CItem *a, const CItem *b) { return a->AppImage < b->AppImage; });
				m_bItemsSorted = true;
			}
			CItem search{ app_image, nullptr };
			auto pos = std::lower_bound(m_aItems.begin(), m_aItems.end(), &search, [](const CItem *a, const CItem *b) { return a->AppImage < b->AppImage; });
			if (pos == m_aItems.end() || (*pos)->AppImage != app_image)
			{
				IImage *img = m_pForm->getPresenter()->ImageCreate(*app_image, L"", nullptr, { "RGBA" });
				if (img)
				{
					m_aItems.push_back(new CItem(app_image, img));
					m_bItemsSorted = false;
					return img;
				}
				return nullptr;
			}
			if (!(*pos)->Image || !(*pos)->Image->getIsValid())
			{
				(*pos)->Image = m_pForm->getPresenter()->ImageCreate(*app_image, L"", nullptr, { "RGBA" });
				if ((*pos)->Image)
					return (*pos)->Image;
				delete (*pos);
				m_aItems.erase(pos);
				return nullptr;
			}
			return (*pos)->Image;
		}

		void CImageManager::FreeImage(APP_IMAGE *app_image)
		{
			if (!app_image)
				return;
			if (!m_bItemsSorted)
			{
				std::sort(m_aItems.begin(), m_aItems.end(), [](const CItem *a, const CItem *b) { return a->AppImage < b->AppImage; });
				m_bItemsSorted = true;
			}
			CItem search{ app_image, nullptr };
			auto pos = std::lower_bound(m_aItems.begin(), m_aItems.end(), &search, [](const CItem *a, const CItem *b) { return a->AppImage < b->AppImage; });
			if (pos != m_aItems.end() && (*pos)->AppImage == app_image)
			{
				delete (*pos);
				m_aItems.erase(pos);
			}
		}

		void CImageManager::FreeImages()
		{
			for (auto pos = m_aItems.begin(); pos != m_aItems.end(); pos++)
				delete (*pos);
			m_aItems.clear();
			m_bItemsSorted = true;
		}
#pragma endregion
	}
}