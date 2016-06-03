// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#include "Presenter.h"

namespace licui
{
	namespace application
	{
		IPresenter::IPresenter(IWindow *window) :m_pWindow{ window }
		{

		}

		IWindow *IPresenter::getWindow()
		{
			return m_pWindow;
		}
	}
}