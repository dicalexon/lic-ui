// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#include "CApplication.h"
#include "CWindow.h"
#include "..\..\Style.h"
#include "..\..\DefaultStyle.h"

namespace licui
{
	namespace application
	{
		CApplication Application;
		wchar_t *DefaultWindowClassName = L"dsdk_application_form_default_wndclassex";
		EXTERN_C IMAGE_DOS_HEADER __ImageBase;

		CApplication::CApplication() :
			m_hWindowClassHandle{ 0 },
			m_hMainWindow{ 0 },
			m_hInstance{ (HINSTANCE)&__ImageBase },
			m_pOnIdleParam{ nullptr },
			m_fOnIdle{ nullptr }
		{
			WindowClassRegister();
			m_aStyles.push_back(GetDefaultStyle());
		}

		CApplication::~CApplication()
		{
			WindowClassUnregister();
			for (auto pos = m_aStyles.begin(); pos != m_aStyles.end(); pos++)
				delete (*pos);
		}

		void CApplication::WindowClassRegister()
		{
			m_sWindowClassInfo.cbClsExtra = 0;
			m_sWindowClassInfo.cbSize = sizeof(WNDCLASSEX);
			m_sWindowClassInfo.cbWndExtra = 0;
			m_sWindowClassInfo.hbrBackground = 0;// (HBRUSH)COLOR_WINDOW;
			m_sWindowClassInfo.hCursor = LoadCursorW(0, IDC_ARROW);
			m_sWindowClassInfo.hIcon = 0;
			m_sWindowClassInfo.hIconSm = 0;
			m_sWindowClassInfo.hInstance = m_hInstance;
			m_sWindowClassInfo.lpfnWndProc = WindowProc;
			m_sWindowClassInfo.lpszClassName = DefaultWindowClassName;
			m_sWindowClassInfo.lpszMenuName = 0;
			m_sWindowClassInfo.style = CS_CLASSDC | CS_DBLCLKS;
			m_hWindowClassHandle = RegisterClassExW(&m_sWindowClassInfo);
		}

		void CApplication::WindowClassUnregister()
		{
			if (m_hWindowClassHandle)
			{
				UnregisterClassW(DefaultWindowClassName, (HINSTANCE)&__ImageBase);
				m_hWindowClassHandle = 0;
			}
		}

		void CApplication::Run()
		{
			m_bTerminated = false;
			do
			{
				if (!ProcessMessage())
					if (m_fOnIdle)
						m_fOnIdle(m_pOnIdleParam);
			} while (!m_bTerminated);
		}

		bool CApplication::ProcessMessage()
		{
			MSG msg;
			if (!PeekMessageW(&msg, 0, 0, 0, PM_NOREMOVE))
			{
				Sleep(1);
				return false;
			}
			bool exists = PeekMessageW(&msg, 0, 0, 0, PM_REMOVE) ? true : false;
			if (!exists)
				return false;
			if (msg.message != WM_QUIT)
			{
				TranslateMessage(&msg);
				DispatchMessageW(&msg);
			}
			else
				m_bTerminated = true;
			return true;
		}

		BOOL CALLBACK CApplication::DestroyApplicationWindows(HWND hWnd, LPARAM lParam)
		{
			if (((DESTROY_WINDOWS_PARAM*)lParam)->Exclude != hWnd)
			{
				DWORD process_id;
				GetWindowThreadProcessId(hWnd, &process_id);
				if (process_id == ((DESTROY_WINDOWS_PARAM*)lParam)->ProcessId)
					DestroyWindow(hWnd);
			}
			return TRUE;
		}

		LRESULT CALLBACK CApplication::WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
		{
			if (uMsg == WM_NCCREATE)
			{
				CWindow *window = (CWindow*)((CREATESTRUCT*)(lParam))->lpCreateParams;
				window->setHandle(hWnd);
				SetWindowLongW(hWnd, GWLP_USERDATA, LONG_PTR(window));
				if (!Application.m_hMainWindow)
					Application.m_hMainWindow = hWnd;
			}
			else
			{
				CWindow *window = (CWindow*)GetWindowLongW(hWnd, GWLP_USERDATA);
				if (uMsg == WM_NCDESTROY)
				{
					if (hWnd == Application.m_hMainWindow)
					{
						DESTROY_WINDOWS_PARAM params{ hWnd, 0 };
						GetWindowThreadProcessId(hWnd, &params.ProcessId);
						EnumWindows(DestroyApplicationWindows, (LPARAM)&params);
						PostQuitMessage(0);
						Application.m_hMainWindow = 0;
					}
					return DefWindowProcW(hWnd, uMsg, wParam, lParam);
				}
				if (window)
					return window->WindowProc(hWnd, uMsg, wParam, lParam);
			}
			return DefWindowProcW(hWnd, uMsg, wParam, lParam);
		}

		void CApplication::ProcessMessages()
		{
			while (ProcessMessage());
		}

		void CApplication::AddStyle(CStyle *style)
		{
			if (style)
				m_aStyles.push_back(style);
		}

		ATOM CApplication::getWindowClassHandle() const
		{
			return m_hWindowClassHandle;
		}

		HINSTANCE CApplication::getInstance() const
		{
			return m_hInstance;
		}

		HWND CApplication::getMainWindow() const
		{
			return m_hMainWindow;
		}

		size_t CApplication::getStyleCount() const
		{
			return m_aStyles.size();
		}

		CStyle *CApplication::getStyle(const size_t index)
		{
			if (index < m_aStyles.size())
				return m_aStyles[index];
			return nullptr;
		}

		void *CApplication::getOnIdleParam() const
		{
			return m_pOnIdleParam;
		}

		FOnApplicationIdle CApplication::getOnIdle() const
		{
			return m_fOnIdle;
		}

		CApplication *CApplication::setOnIdleParam(void *param)
		{
			m_pOnIdleParam = param;
			return this;
		}

		CApplication *CApplication::setOnIdle(FOnApplicationIdle value)
		{
			m_fOnIdle = value;
			return this;
		}
	}
}