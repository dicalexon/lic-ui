// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#pragma once

#include <vector>
#include "..\..\..\Strings\Strings.h"
#include "..\..\Types.h"
#include <Windows.h>

namespace licui
{
	namespace application
	{
		typedef void(*FOnApplicationIdle)(void *param);

		class CApplication final
		{
		private:
			struct DESTROY_WINDOWS_PARAM
			{
				HWND Exclude;
				DWORD ProcessId;
			};

			WNDCLASSEX m_sWindowClassInfo;
			ATOM m_hWindowClassHandle;
			HWND m_hMainWindow;
			bool m_bTerminated;
			HINSTANCE m_hInstance;
			std::vector<CStyle*> m_aStyles;
			void *m_pOnIdleParam;
			FOnApplicationIdle m_fOnIdle;

			void WindowClassRegister();
			void WindowClassUnregister();
			static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
			static BOOL CALLBACK DestroyApplicationWindows(HWND hWnd, LPARAM lParam);
			bool ProcessMessage();
		public:
			ATOM getWindowClassHandle() const;
			HINSTANCE getInstance() const;
			HWND getMainWindow() const;
			size_t getStyleCount() const;
			CStyle *getStyle(const size_t index);
			void *getOnIdleParam() const;
			FOnApplicationIdle getOnIdle() const;

			CApplication* setOnIdleParam(void *param);
			CApplication* setOnIdle(FOnApplicationIdle value);

			CApplication();
			~CApplication();

			void Run();
			void ProcessMessages();
			void AddStyle(CStyle *style);
		};

		extern CApplication Application;
		extern wchar_t *DefaultWindowClassName;
	}
}