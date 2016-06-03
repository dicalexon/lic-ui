// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#include "CWindow.h"
#include "CApplication.h"
#include <windowsx.h>

namespace licui
{
	namespace application
	{
#pragma region Contstructor/Destructor
		CWindow::CWindow() : IWindow(),
			m_hHandle{ 0 },
			m_fOnHelp{ nullptr },
			m_fOnNonClientPaint{ nullptr },
			m_fOnInitMenu{ nullptr },
			m_fOnInitMenuPopup{ nullptr },
			m_fOnMenuClose{ nullptr },
			m_fOnMenuSelect{ nullptr },
			m_fOnMenuRightMouseButtonUp{ nullptr },
			m_fOnMenuDrag{ nullptr },
			m_fOnUninitMenuPopup{ nullptr },
			m_fOnMenuCommand{ nullptr },
			m_fOnNextMenu{ nullptr },
			m_fOnDropFiles{ nullptr },
			m_fOnTouch{ nullptr },
			m_fOnPrint{ nullptr },
			m_fOnPrintClient{ nullptr },
			m_fOnCopyData{ nullptr },
			m_eCurrentCursor{ ctNone },
			m_bIsCaretCreated{ false },
			m_bIsCaretVisible{ false },
			m_sCaretSize{ -1, -1 },
			m_sCaretPosition{ -1000000, -1000000 }
		{
			m_sDefaultClass = DefaultWindowClassName;
			m_sDefaultCaption = L"Window";
			m_iDefaultX = CW_USEDEFAULT;
			m_iDefaultY = CW_USEDEFAULT;
			m_iDefaultWidth = CW_USEDEFAULT;
			m_iDefaultHeight = 0;
			m_iDefaultStyle = WS_OVERLAPPEDWINDOW;
			m_iDefaultStyleEx = WS_EX_OVERLAPPEDWINDOW;
			m_eDefaultState = wsNormal;
		}

		CWindow::~CWindow()
		{
			if (m_hHandle)
			{
				// Remove from window link to the class object
				SetWindowLongW(m_hHandle, GWLP_USERDATA, 0);
				DestroyWindow(m_hHandle);
				m_hHandle = 0;
			}
		}
#pragma endregion

#pragma region Helper methods
		bool CWindow::Create()
		{
			if (m_hHandle)
				return false;
			if (m_hHandle = CreateWindowExW(m_iDefaultStyleEx, m_sDefaultClass.c_str(), m_sDefaultCaption.c_str(), m_iDefaultStyle, m_iDefaultX, m_iDefaultY, m_iDefaultWidth, m_iDefaultHeight, 0, 0, Application.getInstance(), LPVOID(this)))
			{
				switch (m_eDefaultState)
				{
				case wsNormal:
					ShowWindow(m_hHandle, SW_SHOW);
					break;
				case wsMaximized:
					ShowWindow(m_hHandle, SW_MAXIMIZE);
					break;
				case wsMinimized:
					ShowWindow(m_hHandle, SW_MINIMIZE);
					break;
				}
				SetWindowLongW(m_hHandle, GWLP_USERDATA, (LONG)this);
				return true;
			}
			return false;
		}

		IWindow *CWindow::Show() const
		{
			if (m_hHandle)
				ShowWindow(m_hHandle, SW_SHOWNORMAL);
			return (IWindow*)this;
		}

		IWindow *CWindow::Hide() const
		{
			if (m_hHandle)
				ShowWindow(m_hHandle, SW_HIDE);
			return (IWindow*)this;
		}

		void CWindow::StartTrackMouseLeave()
		{
			TRACKMOUSEEVENT e;
			e.cbSize = sizeof(TRACKMOUSEEVENT);
			e.dwFlags = TME_LEAVE;
			e.hwndTrack = m_hHandle;
			e.dwHoverTime = HOVER_DEFAULT;
			TrackMouseEvent(&e);
		}

		unsigned int CWindow::CreateTimer(unsigned int id, unsigned int interval)
		{
			if (!m_hHandle)
				return 0;
			return SetTimer(m_hHandle, id, interval, nullptr);
		}

		void CWindow::DeleteTimer(unsigned int id)
		{
			KillTimer(m_hHandle, id);
		}

		bool CWindow::CaptureMouse()
		{
			if (!m_hHandle)
				return false;
			SetCapture(m_hHandle);
			return true;
		}

		void CWindow::ReleaseMouseCapture()
		{
			ReleaseCapture();
		}

		APP_POINT CWindow::ClientToScreen(const APP_POINT &value)
		{
			::POINT p{ value.X, value.Y };
			if (m_hHandle && ::ClientToScreen(m_hHandle, &p))
				return{ p.x, p.y };
			return value;
		}

		APP_POINT CWindow::ScreenToClient(const APP_POINT &value)
		{
			::POINT p{ value.X, value.Y };
			if (m_hHandle && ::ScreenToClient(m_hHandle, &p))
				return{ p.x, p.y };
			return value;
		}

		void CWindow::Maximize()
		{
			if (m_hHandle)
				ShowWindow(m_hHandle, SW_MAXIMIZE);
		}

		void CWindow::Minimize()
		{
			if (m_hHandle)
				ShowWindow(m_hHandle, SW_MINIMIZE);
		}

		void CWindow::Restore()
		{
			if (m_hHandle)
				ShowWindow(m_hHandle, SW_RESTORE);
		}

		bool CWindow::CreateCaret(const int width, const int height)
		{
			if (!m_hHandle)
				return false;
			if (m_bIsCaretCreated)
			{
				if (width == m_sCaretSize.X && height == m_sCaretSize.Y)
					return true;
				DestroyCaret();
			}
			if (width < 0 || height < 0)
				return false;
			if (m_bIsCaretCreated = ::CreateCaret(m_hHandle, 0, width, height) ? true : false)
				m_sCaretSize = { width, height };
			return m_bIsCaretCreated;
		}

		bool CWindow::DestroyCaret()
		{
			if (!m_hHandle)
				return false;
			m_bIsCaretVisible = false;
			m_sCaretSize = { -1, -1 };
			m_sCaretPosition = { -1000000, -1000000 };
			return ::DestroyCaret() ? true : false;
		}

		bool CWindow::ShowCaret()
		{
			if (!m_hHandle || !m_bIsCaretCreated)
				return false;
			if (::ShowCaret(m_hHandle))
				m_bIsCaretVisible = true;
			return m_bIsCaretVisible;
		}

		bool CWindow::HideCaret()
		{
			if (!m_hHandle || !m_bIsCaretCreated)
				return false;
			if (::HideCaret(m_hHandle))
				m_bIsCaretVisible = false;
			return !m_bIsCaretVisible;
		}

		bool CWindow::SetCaretPosition(const int x, const int y)
		{
			if (!m_hHandle || !m_bIsCaretCreated)
				return false;
			if (x != m_sCaretPosition.X || y != m_sCaretPosition.Y)
			{
				m_sCaretPosition = { x, y };
				return SetCaretPos(x, y) ? true : false;
			}
			return true;
		}

		bool CWindow::IsCaretVisible()
		{
			return m_bIsCaretVisible;
		}

		bool CWindow::CopyStringToClipboard(const String &str)
		{
			if (str.length() == 0)
				return true;
			if (!m_hHandle)
				return false;
			if (!OpenClipboard(m_hHandle))
				return false;
			if (!EmptyClipboard())
			{
				CloseClipboard();
				return false;
			}
			HGLOBAL hmem = GlobalAlloc(GMEM_MOVEABLE, (str.length() + 1) * sizeof(wchar_t));
			if (!hmem)
			{
				CloseClipboard();
				return false;
			}
			LPVOID mem = GlobalLock(hmem);
			if (!mem)
			{
				GlobalFree(hmem);
				CloseClipboard();
				return false;
			}
			memcpy(mem, str.c_str(), (str.length() + 1) * sizeof(wchar_t));
			if (GlobalUnlock(hmem))
			{
				GlobalFree(hmem);
				CloseClipboard();
				return false;
			}
			if (!SetClipboardData(CF_UNICODETEXT, hmem))
			{
				GlobalFree(hmem);
				CloseClipboard();
				return false;
			}
			return CloseClipboard() ? true : false;
		}

		String CWindow::CopyStringFromClipboard()
		{
			if (!m_hHandle)
				return L"";
			if (IsClipboardFormatAvailable(CF_UNICODETEXT))
			{
				if (!OpenClipboard(m_hHandle))
					return L"";
				HANDLE hmem = GetClipboardData(CF_UNICODETEXT);
				if (!hmem)
				{
					CloseClipboard();
					return L"";
				}
				LPVOID mem = GlobalLock(hmem);
				if (!mem)
				{
					CloseClipboard();
					return L"";
				}
				String result{ (wchar_t*)mem };
				GlobalUnlock(hmem);
				CloseClipboard();
				return result;
			}
			if (IsClipboardFormatAvailable(CF_TEXT))
			{
				if (!OpenClipboard(m_hHandle))
					return L"";
				HANDLE hmem = GetClipboardData(CF_TEXT);
				if (!hmem)
				{
					CloseClipboard();
					return L"";
				}
				LPVOID mem = GlobalLock(hmem);
				if (!mem)
				{
					CloseClipboard();
					return L"";
				}
				AnsiString result{ (char*)mem };
				GlobalUnlock(hmem);
				CloseClipboard();
				return AnsiToString(result);
			}
			return L"";
		}
#pragma endregion

#pragma region Window proc
		LRESULT CWindow::WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
		{
			switch (uMsg)
			{
			case WM_CREATE:
				if (m_fOnCreate)
					m_fOnCreate(m_pCallbackParam);
				return 0;
			case WM_DESTROY:
				if (m_fOnDestroy)
					m_fOnDestroy(m_pCallbackParam);
				m_hHandle = 0;
				return 0;
			case WM_MOVE:
				if (m_fOnMove)
					m_fOnMove(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), m_pCallbackParam);
				return 0;
			case WM_SIZE:
				switch (wParam)
				{
				case SIZE_RESTORED:
					if (m_fOnRestore)
						m_fOnRestore(LOWORD(lParam), HIWORD(lParam), m_pCallbackParam);
					return 0;
				case SIZE_MINIMIZED:
					if (m_fOnMinimize)
						m_fOnMinimize(LOWORD(lParam), HIWORD(lParam), m_pCallbackParam);
					return 0;
				case SIZE_MAXIMIZED:
					if (m_fOnMaximize)
						m_fOnMaximize(LOWORD(lParam), HIWORD(lParam), m_pCallbackParam);
					return 0;
				}
				break;
			case WM_ACTIVATE:
				switch (LOWORD(wParam))
				{
				case WA_ACTIVE:
					if (m_fOnActivate)
						m_fOnActivate(false, m_pCallbackParam);
					break;
				case WA_CLICKACTIVE:
					if (m_fOnActivate)
						m_fOnActivate(true, m_pCallbackParam);
					break;
				default:
					if (m_fOnDeactivate)
						m_fOnDeactivate(m_pCallbackParam);
				}
				return 0;
			case WM_SETFOCUS:
				if (m_fOnSetFocus)
					m_fOnSetFocus(m_pCallbackParam);
				return 0;
			case WM_KILLFOCUS:
				if (m_fOnKillFocus)
					m_fOnKillFocus(m_pCallbackParam);
				return 0;
			case WM_ENABLE:
				if (wParam == TRUE)
				{
					if (m_fOnEnable)
						m_fOnEnable(m_pCallbackParam);
				}
				else
					if (m_fOnDisable)
						m_fOnDisable(m_pCallbackParam);
				return 0;
			case WM_PAINT:
			{
				PAINTSTRUCT ps;
				HDC dc = BeginPaint(hWnd, &ps);
				if (m_fOnPaint)
					m_fOnPaint(ps.rcPaint.left, ps.rcPaint.top, ps.rcPaint.right, ps.rcPaint.bottom, m_pCallbackParam);
				EndPaint(hWnd, &ps);
				return 0;
			}
			case WM_CLOSE:
			{
				CLOSE_ACTION action = caFree;
				if (m_fOnClose)
					m_fOnClose(action, m_pCallbackParam);
				switch (action)
				{
				case caNone:
					return 0;
				case caHide:
					ShowWindow(hWnd, SW_HIDE);
					return 0;
				case caMinimize:
					ShowWindow(hWnd, SW_MINIMIZE);
					return 0;
				}
			}
			return DefWindowProcW(hWnd, uMsg, wParam, lParam);
			case WM_QUERYENDSESSION:
				return m_fOnQueryEndSession && !m_fOnQueryEndSession(m_pCallbackParam) ? FALSE : TRUE;
			case WM_QUERYOPEN:
				return m_fOnQueryOpen && !m_fOnQueryOpen(m_pCallbackParam) ? FALSE : TRUE;
			case WM_ENDSESSION:
				if (m_fOnEndSession)
					m_fOnEndSession(wParam ? true : false, m_pCallbackParam);
				return DefWindowProcW(hWnd, uMsg, wParam, lParam);
			case WM_SHOWWINDOW:
				if (wParam)
				{
					if (m_fOnShow)
						m_fOnShow(m_pCallbackParam);
				}
				else
					if (m_fOnHide)
						m_fOnHide(m_pCallbackParam);
				return DefWindowProcW(hWnd, uMsg, wParam, lParam);
			case WM_DEVMODECHANGE:
				if (m_fOnDeviceModeChange)
					m_fOnDeviceModeChange(m_pCallbackParam);
				return DefWindowProcW(hWnd, uMsg, wParam, lParam);
			case WM_ACTIVATEAPP:
				if (wParam)
				{
					if (m_fOnActivateApp)
						m_fOnActivateApp(m_pCallbackParam);
				}
				else
					if (m_fOnDeactivateApp)
						m_fOnDeactivateApp(m_pCallbackParam);
				return DefWindowProcW(hWnd, uMsg, wParam, lParam);
			case WM_TIMECHANGE:
				if (m_fOnTimeChange)
					m_fOnTimeChange(m_pCallbackParam);
				return DefWindowProcW(hWnd, uMsg, wParam, lParam);
			case WM_INPUTLANGCHANGEREQUEST:
				return m_fOnInputLanguageChangeRequest && !m_fOnInputLanguageChangeRequest(m_pCallbackParam) ? 0 : DefWindowProcW(hWnd, uMsg, wParam, lParam);
			case WM_INPUTLANGCHANGE:
				if (m_fOnInputLanguageChange)
					m_fOnInputLanguageChange(m_pCallbackParam);
				return DefWindowProcW(hWnd, uMsg, wParam, lParam);
			case WM_HELP:
				return m_fOnHelp && m_fOnHelp((HELPINFO*)lParam, m_pCallbackParam) ? 0 : DefWindowProcW(hWnd, uMsg, wParam, lParam);
			case WM_CONTEXTMENU:
				return m_fOnContextMenu && m_fOnContextMenu(LOWORD(lParam), HIWORD(lParam), m_pCallbackParam) ? 0 : DefWindowProcW(hWnd, uMsg, wParam, lParam);
			case WM_DISPLAYCHANGE:
				if (m_fOnDisplayChange)
					m_fOnDisplayChange(LOWORD(lParam), HIWORD(lParam), m_pCallbackParam);
				return DefWindowProcW(hWnd, uMsg, wParam, lParam);
			case WM_NCPAINT:
				return m_fOnNonClientPaint && m_fOnNonClientPaint((HRGN)wParam, m_pCallbackParam) ? 0 : DefWindowProcW(hWnd, uMsg, wParam, lParam);
			case WM_NCMOUSEMOVE:
				if (m_fOnNonClientMouseMove)
					m_fOnNonClientMouseMove(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), m_pCallbackParam);
				return DefWindowProcW(hWnd, uMsg, wParam, lParam);
			case WM_NCLBUTTONDOWN:
				if (m_fOnNonClientLeftMouseButtonDown)
					m_fOnNonClientLeftMouseButtonDown(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), m_pCallbackParam);
				return DefWindowProcW(hWnd, uMsg, wParam, lParam);
			case WM_NCLBUTTONUP:
				if (m_fOnNonClientLeftMouseButtonUp)
					m_fOnNonClientLeftMouseButtonUp(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), m_pCallbackParam);
				return DefWindowProcW(hWnd, uMsg, wParam, lParam);
			case WM_NCLBUTTONDBLCLK:
				if (m_fOnNonClientLeftMouseButtonUp)
					m_fOnNonClientLeftMouseButtonDoubleClick(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), m_pCallbackParam);
				return DefWindowProcW(hWnd, uMsg, wParam, lParam);
			case WM_NCRBUTTONDOWN:
				if (m_fOnNonClientRightMouseButtonDown)
					m_fOnNonClientRightMouseButtonDown(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), m_pCallbackParam);
				return DefWindowProcW(hWnd, uMsg, wParam, lParam);
			case WM_NCRBUTTONUP:
				if (m_fOnNonClientRightMouseButtonUp)
					m_fOnNonClientRightMouseButtonUp(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), m_pCallbackParam);
				return DefWindowProcW(hWnd, uMsg, wParam, lParam);
			case WM_NCRBUTTONDBLCLK:
				if (m_fOnNonClientRightMouseButtonDoubleClick)
					m_fOnNonClientRightMouseButtonDoubleClick(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), m_pCallbackParam);
				return DefWindowProcW(hWnd, uMsg, wParam, lParam);
			case WM_NCMBUTTONDOWN:
				if (m_fOnNonClientMiddleMouseButtonDown)
					m_fOnNonClientMiddleMouseButtonDown(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), m_pCallbackParam);
				return DefWindowProcW(hWnd, uMsg, wParam, lParam);
			case WM_NCMBUTTONUP:
				if (m_fOnNonClientMiddleMouseButtonUp)
					m_fOnNonClientMiddleMouseButtonUp(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), m_pCallbackParam);
				return DefWindowProcW(hWnd, uMsg, wParam, lParam);
			case WM_NCMBUTTONDBLCLK:
				if (m_fOnNonClientMiddleMouseButtonDoubleClick)
					m_fOnNonClientMiddleMouseButtonDoubleClick(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), m_pCallbackParam);
				return DefWindowProcW(hWnd, uMsg, wParam, lParam);
			case WM_KEYDOWN:
				if (m_fOnKeyDown)
					m_fOnKeyDown(VirtualToKey(wParam), m_pCallbackParam);
				return DefWindowProcW(hWnd, uMsg, wParam, lParam);
			case WM_KEYUP:
				if (m_fOnKeyUp)
					m_fOnKeyUp(VirtualToKey(wParam), m_pCallbackParam);
				return DefWindowProcW(hWnd, uMsg, wParam, lParam);
			case WM_CHAR:
				if (m_fOnChar)
					m_fOnChar(wParam, m_pCallbackParam);
				return DefWindowProcW(hWnd, uMsg, wParam, lParam);
			case WM_DEADCHAR:
				if (m_fOnDeadChar)
					m_fOnDeadChar(wParam, m_pCallbackParam);
				return DefWindowProcW(hWnd, uMsg, wParam, lParam);
			case WM_SYSKEYDOWN:
				if (m_fOnSysKeyDown)
					m_fOnSysKeyDown(VirtualToKey(wParam), m_pCallbackParam);
				return DefWindowProcW(hWnd, uMsg, wParam, lParam);
			case WM_SYSKEYUP:
				if (m_fOnSysKeyUp)
					m_fOnSysKeyUp(VirtualToKey(wParam), m_pCallbackParam);
				return DefWindowProcW(hWnd, uMsg, wParam, lParam);
			case WM_SYSCHAR:
				if (m_fOnSysChar)
					m_fOnSysChar(wParam, m_pCallbackParam);
				return DefWindowProcW(hWnd, uMsg, wParam, lParam);
			case WM_SYSDEADCHAR:
				if (m_fOnSysDeadChar)
					m_fOnSysDeadChar(wParam, m_pCallbackParam);
				return DefWindowProcW(hWnd, uMsg, wParam, lParam);
			case WM_INITDIALOG:
				return m_fOnInitDialog && !m_fOnInitDialog(m_pCallbackParam) ? FALSE : TRUE;
			case WM_SYSCOMMAND:
				if (m_fOnSysCommand)
				{
					SYSTEM_COMMAND_TYPE type{ syscmdNone };
					switch (wParam)
					{
					case SC_CLOSE:
						type = syscmdClose;
						break;
					case SC_CONTEXTHELP:
						type = syscmdContextHelp;
						break;
					case SC_DEFAULT:
						type = syscmdDefault;
						break;
					case SC_HOTKEY:
						type = syscmdHotKey;
						break;
					case SC_HSCROLL:
						type = syscmdHScroll;
						break;
					case SCF_ISSECURE:
						type = syscmdIsSecure;
						break;
					case SC_KEYMENU:
						type = syscmdKeyMenu;
						break;
					case SC_MAXIMIZE:
						type = syscmdMaximize;
						break;
					case SC_MINIMIZE:
						type = syscmdMinimize;
						break;
					case SC_MONITORPOWER:
						type = syscmdMonitorPower;
						break;
					case SC_MOUSEMENU:
						type = syscmdMouseMenu;
						break;
					case SC_MOVE:
						type = syscmdMove;
						break;
					case SC_NEXTWINDOW:
						type = syscmdNextWindow;
						break;
					case SC_PREVWINDOW:
						type = syscmdPrevWindow;
						break;
					case SC_RESTORE:
						type = syscmdRestore;
						break;
					case SC_SCREENSAVE:
						type = syscmdScreenSave;
						break;
					case SC_SIZE:
						type = syscmdSize;
						break;
					case SC_TASKLIST:
						type = syscmdTaskList;
						break;
					case SC_VSCROLL:
						type = syscmdVScroll;
						break;
					}
					m_fOnSysCommand(type, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), m_pCallbackParam);
				}
				return DefWindowProcW(hWnd, uMsg, wParam, lParam);
			case WM_HSCROLL:
				if (m_fOnHScroll)
				{
					SCROLL_TYPE type{ scrollNone };
					switch (LOWORD(wParam))
					{
					case SB_ENDSCROLL:
						type = scrollEndScroll;
						break;
					case SB_LEFT:
						type = scrollLeft;
						break;
					case SB_RIGHT:
						type = scrollRight;
						break;
					case SB_LINELEFT:
						type = scrollLineLeft;
						break;
					case SB_LINERIGHT:
						type = scrollLineRight;
						break;
					case SB_PAGELEFT:
						type = scrollPageLeft;
						break;
					case SB_PAGERIGHT:
						type = scrollPageRight;
						break;
					case SB_THUMBPOSITION:
						type = scrollThumbPosition;
						break;
					case SB_THUMBTRACK:
						type = scrollThumbTrack;
						break;
					}
					m_fOnHScroll(type, HIWORD(wParam), m_pCallbackParam);
				}
				return DefWindowProcW(hWnd, uMsg, wParam, lParam);
			case WM_VSCROLL:
				if (m_fOnVScroll)
				{
					SCROLL_TYPE type{ scrollNone };
					switch (LOWORD(wParam))
					{
					case SB_ENDSCROLL:
						type = scrollEndScroll;
						break;
					case SB_LEFT:
						type = scrollLeft;
						break;
					case SB_RIGHT:
						type = scrollRight;
						break;
					case SB_LINELEFT:
						type = scrollLineLeft;
						break;
					case SB_LINERIGHT:
						type = scrollLineRight;
						break;
					case SB_PAGELEFT:
						type = scrollPageLeft;
						break;
					case SB_PAGERIGHT:
						type = scrollPageRight;
						break;
					case SB_THUMBPOSITION:
						type = scrollThumbPosition;
						break;
					case SB_THUMBTRACK:
						type = scrollThumbTrack;
						break;
					}
					m_fOnVScroll(type, HIWORD(wParam), m_pCallbackParam);
				}
				return DefWindowProcW(hWnd, uMsg, wParam, lParam);
			case WM_INITMENU:
				if (m_fOnInitMenu)
					m_fOnInitMenu((HMENU)wParam, m_pCallbackParam);
				return DefWindowProcW(hWnd, uMsg, wParam, lParam);
			case WM_INITMENUPOPUP:
				if (m_fOnInitMenuPopup)
					m_fOnInitMenuPopup((HMENU)wParam, LOWORD(lParam), HIWORD(lParam) ? true : false, m_pCallbackParam);
				return DefWindowProcW(hWnd, uMsg, wParam, lParam);
			case WM_GESTURE:
				GESTUREINFO gesture;
				ZeroMemory(&gesture, sizeof(GESTUREINFO));
				gesture.cbSize = sizeof(GESTUREINFO);
				if (GetGestureInfo((HGESTUREINFO)lParam, &gesture))
					switch (gesture.dwID)
					{
					case GID_ZOOM:
						if (m_fOnGestureZoom)
							m_fOnGestureZoom(gesture.ptsLocation.x, gesture.ptsLocation.y, m_pCallbackParam);
						return 0;
					case GID_PAN:
						if (m_fOnGesturePan)
							m_fOnGesturePan(gesture.ptsLocation.x, gesture.ptsLocation.y, m_pCallbackParam);
						return 0;
					case GID_ROTATE:
						if (m_fOnGestureRotate)
							m_fOnGestureRotate(gesture.ptsLocation.x, gesture.ptsLocation.y, m_pCallbackParam);
						return 0;
					case GID_TWOFINGERTAP:
						if (m_fOnGestureTwoFingerTap)
							m_fOnGestureTwoFingerTap(gesture.ptsLocation.x, gesture.ptsLocation.y, m_pCallbackParam);
						return 0;
					case GID_PRESSANDTAP:
						if (m_fOnGesturePressAndTap)
							m_fOnGesturePressAndTap(gesture.ptsLocation.x, gesture.ptsLocation.y, m_pCallbackParam);
						return 0;
					}
				return DefWindowProcW(hWnd, uMsg, wParam, lParam);
			case WM_GESTURENOTIFY:
				if (m_fOnGestureNotify)
					m_fOnGestureNotify(m_pCallbackParam);
				return DefWindowProcW(hWnd, uMsg, wParam, lParam);
			case WM_MENUSELECT:
				if (HIWORD(wParam) == 0xFFFF && !lParam)
				{
					if (m_fOnMenuClose)
						m_fOnMenuClose(m_pCallbackParam);
				}
				else
					if (m_fOnMenuSelect)
						m_fOnMenuSelect(LOWORD(wParam), HIWORD(wParam), (HMENU)lParam, m_pCallbackParam);
				return DefWindowProcW(hWnd, uMsg, wParam, lParam);
			case WM_ENTERIDLE:
				if (wParam == MSGF_DIALOGBOX)
				{
					if (m_fOnEnterIdleDialog)
						m_fOnEnterIdleDialog(m_pCallbackParam);
				}
				else if (wParam == MSGF_MENU)
				{
					if (m_fOnEnterIdleMenu)
						m_fOnEnterIdleMenu(m_pCallbackParam);
				}
				return DefWindowProcW(hWnd, uMsg, wParam, lParam);
			case WM_MENURBUTTONUP:
				if (m_fOnMenuRightMouseButtonUp)
					m_fOnMenuRightMouseButtonUp(wParam, (HMENU)lParam, m_pCallbackParam);
				return DefWindowProcW(hWnd, uMsg, wParam, lParam);
			case WM_MENUDRAG:
			{
				LRESULT result = 2;
				if (m_fOnMenuDrag)
					m_fOnMenuDrag(wParam, (HMENU)lParam, result, m_pCallbackParam);
				if (result == MND_CONTINUE || result == MND_ENDMENU)
					return result;
			}
			return DefWindowProcW(hWnd, uMsg, wParam, lParam);
			case WM_UNINITMENUPOPUP:
				if (m_fOnUninitMenuPopup)
					m_fOnUninitMenuPopup((HMENU)wParam, m_pCallbackParam);
				return DefWindowProcW(hWnd, uMsg, wParam, lParam);
			case WM_MENUCOMMAND:
				if (m_fOnMenuCommand)
					m_fOnMenuCommand(wParam, (HMENU)lParam, m_pCallbackParam);
				return DefWindowProcW(hWnd, uMsg, wParam, lParam);
			case WM_ENTERMENULOOP:
				if (m_fOnEnterMenuLoop)
					m_fOnEnterMenuLoop(wParam ? true : false, m_pCallbackParam);
				return DefWindowProcW(hWnd, uMsg, wParam, lParam);
			case WM_EXITMENULOOP:
				if (m_fOnExitMenuLoop)
					m_fOnExitMenuLoop(wParam ? true : false, m_pCallbackParam);
				return DefWindowProcW(hWnd, uMsg, wParam, lParam);
			case WM_NEXTMENU:
				if (m_fOnNextMenu && m_fOnNextMenu(wParam, (MDINEXTMENU*)lParam, m_pCallbackParam))
					return 0;
				return DefWindowProcW(hWnd, uMsg, wParam, lParam);
			case WM_MOUSEMOVE:
				if (m_fOnMouseMove)
					m_fOnMouseMove(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), (wParam & MK_CONTROL) ? true : false, (wParam & MK_LBUTTON) ? true : false, (wParam & MK_MBUTTON) ? true : false, (wParam & MK_RBUTTON) ? true : false, (wParam & MK_SHIFT) ? true : false, m_pCallbackParam);
				return 0;
			case WM_LBUTTONDOWN:
				if (m_fOnLeftMouseButtonDown)
					m_fOnLeftMouseButtonDown(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), (wParam & MK_CONTROL) ? true : false, (wParam & MK_LBUTTON) ? true : false, (wParam & MK_MBUTTON) ? true : false, (wParam & MK_RBUTTON) ? true : false, (wParam & MK_SHIFT) ? true : false, m_pCallbackParam);
				return 0;
			case WM_LBUTTONUP:
				if (m_fOnLeftMouseButtonUp)
					m_fOnLeftMouseButtonUp(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), (wParam & MK_CONTROL) ? true : false, (wParam & MK_LBUTTON) ? true : false, (wParam & MK_MBUTTON) ? true : false, (wParam & MK_RBUTTON) ? true : false, (wParam & MK_SHIFT) ? true : false, m_pCallbackParam);
				return 0;
			case WM_LBUTTONDBLCLK:
				if (m_fOnLeftMouseButtonDoubleClick)
					m_fOnLeftMouseButtonDoubleClick(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), (wParam & MK_CONTROL) ? true : false, (wParam & MK_LBUTTON) ? true : false, (wParam & MK_MBUTTON) ? true : false, (wParam & MK_RBUTTON) ? true : false, (wParam & MK_SHIFT) ? true : false, m_pCallbackParam);
				return 0;
			case WM_RBUTTONDOWN:
				if (m_fOnRightMouseButtonDown)
					m_fOnRightMouseButtonDown(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), (wParam & MK_CONTROL) ? true : false, (wParam & MK_LBUTTON) ? true : false, (wParam & MK_MBUTTON) ? true : false, (wParam & MK_RBUTTON) ? true : false, (wParam & MK_SHIFT) ? true : false, m_pCallbackParam);
				return 0;
			case WM_RBUTTONUP:
				if (m_fOnRightMouseButtonUp)
					m_fOnRightMouseButtonUp(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), (wParam & MK_CONTROL) ? true : false, (wParam & MK_LBUTTON) ? true : false, (wParam & MK_MBUTTON) ? true : false, (wParam & MK_RBUTTON) ? true : false, (wParam & MK_SHIFT) ? true : false, m_pCallbackParam);
				return 0;
			case WM_RBUTTONDBLCLK:
				if (m_fOnRightMouseButtonDoubleClick)
					m_fOnRightMouseButtonDoubleClick(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), (wParam & MK_CONTROL) ? true : false, (wParam & MK_LBUTTON) ? true : false, (wParam & MK_MBUTTON) ? true : false, (wParam & MK_RBUTTON) ? true : false, (wParam & MK_SHIFT) ? true : false, m_pCallbackParam);
				return 0;
			case WM_MBUTTONDOWN:
				if (m_fOnMiddleMouseButtonDown)
					m_fOnMiddleMouseButtonDown(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), (wParam & MK_CONTROL) ? true : false, (wParam & MK_LBUTTON) ? true : false, (wParam & MK_MBUTTON) ? true : false, (wParam & MK_RBUTTON) ? true : false, (wParam & MK_SHIFT) ? true : false, m_pCallbackParam);
				return 0;
			case WM_MBUTTONUP:
				if (m_fOnMiddleMouseButtonUp)
					m_fOnMiddleMouseButtonUp(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), (wParam & MK_CONTROL) ? true : false, (wParam & MK_LBUTTON) ? true : false, (wParam & MK_MBUTTON) ? true : false, (wParam & MK_RBUTTON) ? true : false, (wParam & MK_SHIFT) ? true : false, m_pCallbackParam);
				return 0;
			case WM_MBUTTONDBLCLK:
				if (m_fOnMiddleMouseButtonDoubleClick)
					m_fOnMiddleMouseButtonDoubleClick(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), (wParam & MK_CONTROL) ? true : false, (wParam & MK_LBUTTON) ? true : false, (wParam & MK_MBUTTON) ? true : false, (wParam & MK_RBUTTON) ? true : false, (wParam & MK_SHIFT) ? true : false, m_pCallbackParam);
				return 0;
			case WM_MOUSEWHEEL:
			{
				int keys = GET_KEYSTATE_WPARAM(wParam), delta = GET_WHEEL_DELTA_WPARAM(wParam);
				if (m_fOnMouseVerticalWheel)
				{
					APP_POINT p = ScreenToClient({ GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) });
					m_fOnMouseVerticalWheel(p.X, p.Y, delta, (keys & MK_CONTROL) ? true : false, (keys & MK_LBUTTON) ? true : false, (keys & MK_MBUTTON) ? true : false, (keys & MK_RBUTTON) ? true : false, (keys & MK_SHIFT) ? true : false, m_pCallbackParam);
				}
			}
			return 0;
			case WM_MOUSEHWHEEL:
			{
				int keys = GET_KEYSTATE_WPARAM(wParam), delta = GET_WHEEL_DELTA_WPARAM(wParam);
				if (m_fOnMouseHorizontalWheel)
				{
					APP_POINT p = ScreenToClient({ GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) });
					m_fOnMouseHorizontalWheel(p.X, p.Y, delta, (keys & MK_CONTROL) ? true : false, (keys & MK_LBUTTON) ? true : false, (keys & MK_MBUTTON) ? true : false, (keys & MK_RBUTTON) ? true : false, (keys & MK_SHIFT) ? true : false, m_pCallbackParam);
				}
			}
			return 0;
			case WM_SIZING:
				if (m_fOnResizing)
				{
					EDGE edge{ edgeNone };
					switch (wParam)
					{
					case WMSZ_BOTTOM:
						edge = edgeBottom;
						break;
					case WMSZ_BOTTOMLEFT:
						edge = edgeBottomLeft;
						break;
					case WMSZ_BOTTOMRIGHT:
						edge = edgeBottomRight;
						break;
					case WMSZ_LEFT:
						edge = edgeLeft;
						break;
					case WMSZ_RIGHT:
						edge = edgeRight;
						break;
					case WMSZ_TOP:
						edge = edgeTop;
						break;
					case WMSZ_TOPLEFT:
						edge = edgeTopLeft;
						break;
					case WMSZ_TOPRIGHT:
						edge = edgeTopRight;
						break;
					}
					m_fOnResizing(edge, ((RECT*)lParam)->left, ((RECT*)lParam)->top, ((RECT*)lParam)->right, ((RECT*)lParam)->bottom, m_pCallbackParam);
				}
				return TRUE;
			case WM_CAPTURECHANGED:
				if (m_fOnLoseCapture)
					m_fOnLoseCapture(m_pCallbackParam);
				return DefWindowProcW(hWnd, uMsg, wParam, lParam);
			case WM_MOVING:
				if (m_fOnMoving)
					m_fOnMoving(((RECT*)lParam)->left, ((RECT*)lParam)->top, ((RECT*)lParam)->right, ((RECT*)lParam)->bottom, m_pCallbackParam);
				return TRUE;
			case WM_ENTERSIZEMOVE:
				if (m_fOnEnterSizeMove)
					m_fOnEnterSizeMove(m_pCallbackParam);
				return DefWindowProcW(hWnd, uMsg, wParam, lParam);
			case WM_EXITSIZEMOVE:
				if (m_fOnExitSizeMove)
					m_fOnExitSizeMove(m_pCallbackParam);
				return DefWindowProcW(hWnd, uMsg, wParam, lParam);
			case WM_DROPFILES:
				if (m_fOnDropFiles)
					m_fOnDropFiles((HDROP)wParam, m_pCallbackParam);
				return DefWindowProcW(hWnd, uMsg, wParam, lParam);
			case WM_TOUCH:
			{
				int count = LOWORD(wParam);
				if (count > 0)
				{
					TOUCHINPUT *inputs = new TOUCHINPUT[count];
					if (GetTouchInputInfo((HTOUCHINPUT)lParam, count, inputs, sizeof(TOUCHINPUT)))
					{
						if (m_fOnTouch)
							m_fOnTouch(count, inputs, m_pCallbackParam);
						delete[] inputs;
						CloseTouchInputHandle((HTOUCHINPUT)lParam);
						return 0;
					}
					delete[] inputs;
				}
			}
			return DefWindowProcW(hWnd, uMsg, wParam, lParam);
			case WM_MOUSEHOVER:
				if (m_fOnMouseHover)
					m_fOnMouseHover(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), (wParam & MK_CONTROL) ? true : false, (wParam & MK_LBUTTON) ? true : false, (wParam & MK_MBUTTON) ? true : false, (wParam & MK_RBUTTON) ? true : false, (wParam & MK_SHIFT) ? true : false, m_pCallbackParam);
				return DefWindowProcW(hWnd, uMsg, wParam, lParam);
			case WM_MOUSELEAVE:
				if (m_fOnMouseLeave)
					m_fOnMouseLeave(m_pCallbackParam);
				return DefWindowProcW(hWnd, uMsg, wParam, lParam);
			case WM_NCMOUSEHOVER:
				if (m_fOnNonClientMouseHover)
					m_fOnNonClientMouseHover(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), m_pCallbackParam);
				return DefWindowProcW(hWnd, uMsg, wParam, lParam);
			case WM_NCMOUSELEAVE:
				if (m_fOnNonClientMouseLeave)
					m_fOnNonClientMouseLeave(m_pCallbackParam);
				return DefWindowProcW(hWnd, uMsg, wParam, lParam);
			case WM_HOTKEY:
				if (m_fOnHotKey)
					m_fOnHotKey(wParam == IDHOT_SNAPDESKTOP, VirtualToKey(HIWORD(lParam)), (LOWORD(lParam) & MOD_ALT) ? true : false, (LOWORD(lParam) & MOD_CONTROL) ? true : false, (LOWORD(lParam) & MOD_SHIFT) ? true : false, (LOWORD(lParam) & MOD_WIN) ? true : false, m_pCallbackParam);
				return DefWindowProcW(hWnd, uMsg, wParam, lParam);
			case WM_PRINT:
				if (m_fOnPrint)
					m_fOnPrint((HDC)wParam, lParam, m_pCallbackParam);
				return DefWindowProcW(hWnd, uMsg, wParam, lParam);
			case WM_PRINTCLIENT:
				if (m_fOnPrintClient)
					m_fOnPrintClient((HDC)wParam, lParam, m_pCallbackParam);
				return DefWindowProcW(hWnd, uMsg, wParam, lParam);
			case WM_THEMECHANGED:
				if (m_fOnThemeChanged)
					m_fOnThemeChanged(m_pCallbackParam);
				return DefWindowProcW(hWnd, uMsg, wParam, lParam);
			case WM_CLIPBOARDUPDATE:
				if (m_fOnClipboardUpdate)
					m_fOnClipboardUpdate(m_pCallbackParam);
				return DefWindowProcW(hWnd, uMsg, wParam, lParam);
			case WM_COPYDATA:
				if (m_fOnCopyData)
					m_fOnCopyData((HWND)wParam, (COPYDATASTRUCT*)lParam, m_pCallbackParam);
				return DefWindowProcW(hWnd, uMsg, wParam, lParam);
			case WM_TIMER:
				if (m_fOnTimer)
					m_fOnTimer(wParam, m_pCallbackParam);
				return 0;
			case WM_SETCURSOR:
				if (LOWORD(lParam) == HTCLIENT)
				{
					CURSOR_TYPE type{ ctNone };
					HCURSOR h{ GetCursor() };
					if (h == LoadCursor(0, IDC_APPSTARTING))
						type = ctAppStarting;
					else if (h == LoadCursor(0, IDC_ARROW))
						type = ctArrow;
					else if (h == LoadCursor(0, IDC_CROSS))
						type = ctCross;
					else if (h == LoadCursor(0, IDC_HAND))
						type = ctHand;
					else if (h == LoadCursor(0, IDC_HELP))
						type = ctHelp;
					else if (h == LoadCursor(0, IDC_IBEAM))
						type = ctIBeam;
					else if (h == LoadCursor(0, IDC_NO))
						type = ctNo;
					else if (h == LoadCursor(0, IDC_SIZEALL))
						type = ctSizeAll;
					else if (h == LoadCursor(0, IDC_SIZENESW))
						type = ctSizeNortheastSouthwest;
					else if (h == LoadCursor(0, IDC_SIZENS))
						type = ctSizeNorthSouth;
					else if (h == LoadCursor(0, IDC_SIZENWSE))
						type = ctSizeNorthwestSoutheast;
					else if (h == LoadCursor(0, IDC_SIZEWE))
						type = ctSizeWestEast;
					else if (h == LoadCursor(0, IDC_UPARROW))
						type = ctUpArrow;
					else if (h == LoadCursor(0, IDC_WAIT))
						type = ctWait;
					if (type != m_eCurrentCursor)
					{
						CURSOR_TYPE old{ m_eCurrentCursor };
						m_eCurrentCursor = type;
						setCursor(old);
					}
					return TRUE;
				}
			}
			LRESULT result;
			if (!HandleMessage(hWnd, uMsg, wParam, lParam, result))
				result = DefWindowProcW(hWnd, uMsg, wParam, lParam);
			return result;
		}
#pragma endregion

#pragma region Getters
		String CWindow::getCaption() const
		{
			String result;
			if (m_hHandle)
			{
				int len = GetWindowTextLengthW(m_hHandle);
				if (len > 0)
				{
					wchar_t *buffer = new wchar_t[len + 1];
					if (GetWindowTextW(m_hHandle, buffer, len + 1))
						result = buffer;
					delete[] buffer;
				}
			}
			return result;
		}

		APP_RECT CWindow::getRect() const
		{
			RECT result = { 0, 0, 0, 0 };
			if (m_hHandle)
				GetWindowRect(m_hHandle, &result);
			return{ result.left, result.top, result.right, result.bottom };
		}

		APP_RECT CWindow::getClientRect() const
		{
			RECT result = { 0, 0, 0, 0 };
			if (m_hHandle)
				GetClientRect(m_hHandle, &result);
			return{ result.left, result.top, result.right, result.bottom };
		}

		APP_POINT CWindow::getSize() const
		{
			APP_RECT r = getRect();
			return{ r.Width(), r.Height() };
		}

		void *CWindow::getHandle() const
		{
			return (void*)m_hHandle;
		}

		APP_POINT CWindow::getPosition() const
		{
			return getRect().LeftTop();
		}

		int CWindow::getLeft() const
		{
			return getRect().Left;
		}

		int CWindow::getTop() const
		{
			return getRect().Top;
		}

		int CWindow::getWidth() const
		{
			return getRect().Width();
		}

		int CWindow::getHeight() const
		{
			return getRect().Height();
		}

		bool CWindow::getVisible() const
		{
			return m_hHandle && IsWindowVisible(m_hHandle);
		}

		bool CWindow::getEnabled() const
		{
			return m_hHandle && IsWindowEnabled(m_hHandle);
		}

		int CWindow::getClientWidth() const
		{
			return getClientRect().Width();
		}

		int CWindow::getClientHeight() const
		{
			return getClientRect().Height();
		}

		bool CWindow::getIsCreated() const
		{
			return m_hHandle > 0;
		}

		bool CWindow::getCursorPosition(int &x, int &y) const
		{
			if (!m_hHandle)
				return false;
			::POINT pos;
			if (!GetCursorPos(&pos))
				return false;
			if (!::ScreenToClient(m_hHandle, &pos))
				return false;
			x = pos.x;
			y = pos.y;
			return true;
		}

		void CWindow::getControlKeys(bool &ctrl, bool &shift, bool &alt) const
		{
			ctrl = (GetKeyState(VK_CONTROL) & 0x8000) > 0;
			shift = (GetKeyState(VK_SHIFT) & 0x8000) > 0;
			alt = (GetKeyState(VK_MENU) & 0x8000) > 0;
		}

		IWindow::WINDOW_STATE CWindow::getWindowState()
		{
			WINDOW_STATE result{ m_eDefaultState };
			if (m_hHandle)
			{
				WINDOWPLACEMENT p;
				p.length = sizeof(WINDOWPLACEMENT);
				if (GetWindowPlacement(m_hHandle, &p))
					switch (p.showCmd)
					{
					case SW_HIDE:
						result = wsHidden;
						break;
					case SW_MAXIMIZE:
						result = wsMaximized;
						break;
					case SW_MINIMIZE:
					case SW_SHOWMINIMIZED:
					case SW_SHOWMINNOACTIVE:
						result = wsMinimized;
						break;
					case SW_RESTORE:
					case SW_SHOW:
					case SW_SHOWNA:
					case SW_SHOWNOACTIVATE:
					case SW_SHOWNORMAL:
						result = wsNormal;
						break;
					}
			}
			return result;
		}

		bool CWindow::getKeyIsDown(KEY key)
		{
			if (m_hHandle)
				return (GetKeyState(KeyToVirtual(key)) & 0x8000) > 0;
			return false;
		}

		bool CWindow::getKeyIsToggled(KEY key)
		{
			if (m_hHandle)
				return (GetKeyState(KeyToVirtual(key)) & 0x0001) > 0;
			return false;
		}

		CWindow::FOnHelp CWindow::getOnHelp() const
		{
			return m_fOnHelp;
		}

		CWindow::FOnNonClientPaint CWindow::getOnNonClientPaint() const
		{
			return m_fOnNonClientPaint;
		}

		CWindow::FOnInitMenu CWindow::getOnInitMenu() const
		{
			return m_fOnInitMenu;
		}

		CWindow::FOnInitMenuPopup CWindow::getOnInitMenuPopup() const
		{
			return m_fOnInitMenuPopup;
		}

		CWindow::FOnMenuClose CWindow::getOnMenuClose() const
		{
			return m_fOnMenuClose;
		}

		CWindow::FOnMenuSelect CWindow::getOnMenuSelect() const
		{
			return m_fOnMenuSelect;
		}

		CWindow::FOnMenuRightMouseButtonUp CWindow::getOnMenuRightMouseButtonUp() const
		{
			return m_fOnMenuRightMouseButtonUp;
		}

		CWindow::FOnMenuDrag CWindow::getOnMenuDrag() const
		{
			return m_fOnMenuDrag;
		}

		CWindow::FOnUninitMenuPopup CWindow::getOnUninitMenuPopup() const
		{
			return m_fOnUninitMenuPopup;
		}

		CWindow::FOnMenuCommand CWindow::getOnMenuCommand() const
		{
			return m_fOnMenuCommand;
		}

		CWindow::FOnNextMenu CWindow::getOnNextMenu() const
		{
			return m_fOnNextMenu;
		}

		CWindow::FOnDropFiles CWindow::getOnDropFiles() const
		{
			return m_fOnDropFiles;
		}

		CWindow::FOnTouch CWindow::getOnTouch() const
		{
			return m_fOnTouch;
		}

		CWindow::FOnPrint CWindow::getOnPrint() const
		{
			return m_fOnPrint;
		}

		CWindow::FOnPrintClient CWindow::getOnPrintClient() const
		{
			return m_fOnPrintClient;
		}

		CWindow::FOnCopyData CWindow::getOnCopyData() const
		{
			return m_fOnCopyData;
		}
#pragma endregion

#pragma region Setters
		IWindow *CWindow::setHandle(const HWND value)
		{
			m_hHandle = value;
			return this;
		}

		IWindow *CWindow::setCaption(const String &value) const
		{
			if (m_hHandle)
				SetWindowTextW(m_hHandle, value.c_str());
			return (IWindow*)this;
		}

		IWindow *CWindow::setRect(const APP_RECT &value) const
		{
			if (m_hHandle)
				SetWindowPos(m_hHandle, 0, value.Left, value.Right, value.Width(), value.Height(), SWP_NOZORDER);
			return (IWindow*)this;
		}

		IWindow *CWindow::setSize(const APP_POINT &value) const
		{
			if (m_hHandle)
				SetWindowPos(m_hHandle, 0, 0, 0, value.X, value.Y, SWP_NOZORDER | SWP_NOMOVE);
			return (IWindow*)this;
		}

		IWindow *CWindow::setPosition(const APP_POINT &value) const
		{
			if (m_hHandle)
				SetWindowPos(m_hHandle, 0, value.X, value.Y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
			return (IWindow*)this;
		}

		IWindow *CWindow::setLeft(const int value) const
		{
			if (m_hHandle)
				SetWindowPos(m_hHandle, 0, value, getTop(), 0, 0, SWP_NOZORDER | SWP_NOSIZE);
			return (IWindow*)this;
		}

		IWindow *CWindow::setTop(const int value) const
		{
			if (m_hHandle)
				SetWindowPos(m_hHandle, 0, getLeft(), value, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
			return (IWindow*)this;
		}

		IWindow *CWindow::setWidth(const int value) const
		{
			if (m_hHandle)
				SetWindowPos(m_hHandle, 0, 0, 0, value, getHeight(), SWP_NOZORDER | SWP_NOMOVE);
			return (IWindow*)this;
		}

		IWindow *CWindow::setHeight(const int value) const
		{
			if (m_hHandle)
				SetWindowPos(m_hHandle, 0, 0, 0, getWidth(), value, SWP_NOZORDER | SWP_NOMOVE);
			return (IWindow*)this;
		}

		IWindow *CWindow::setVisible(const bool value) const
		{
			value ? Show() : Hide();
			return (IWindow*)this;
		}

		IWindow *CWindow::setEnabled(const bool value) const
		{
			if (m_hHandle)
				EnableWindow(m_hHandle, value ? TRUE : FALSE);
			return (IWindow*)this;
		}

		IWindow *CWindow::setCursor(const CURSOR_TYPE value)
		{
			if (m_hHandle && (value != m_eCurrentCursor || !m_bCursorSet))
			{
				HCURSOR h{ 0 };
				switch (value)
				{
				case ctAppStarting:
					h = LoadCursor(0, IDC_APPSTARTING);
					break;
				case ctArrow:
					h = LoadCursor(0, IDC_ARROW);
					break;
				case ctCross:
					h = LoadCursor(0, IDC_CROSS);
					break;
				case ctHand:
					h = LoadCursor(0, IDC_HAND);
					break;
				case ctHelp:
					h = LoadCursor(0, IDC_HELP);
					break;
				case ctIBeam:
					h = LoadCursor(0, IDC_IBEAM);
					break;
				case ctNo:
					h = LoadCursor(0, IDC_NO);
					break;
				case ctSizeAll:
					h = LoadCursor(0, IDC_SIZEALL);
					break;
				case ctSizeNortheastSouthwest:
					h = LoadCursor(0, IDC_SIZENESW);
					break;
				case ctSizeNorthSouth:
					h = LoadCursor(0, IDC_SIZENS);
					break;
				case ctSizeNorthwestSoutheast:
					h = LoadCursor(0, IDC_SIZENWSE);
					break;
				case ctSizeWestEast:
					h = LoadCursor(0, IDC_SIZEWE);
					break;
				case ctUpArrow:
					h = LoadCursor(0, IDC_UPARROW);
					break;
				case ctWait:
					h = LoadCursor(0, IDC_WAIT);
					break;
				}
				if (h)
					SetCursor(h);
				if (value == ctNone)
					SetCursor(0);
				m_eCurrentCursor = value;
				m_bCursorSet = true;
			}
			return (IWindow*)this;
		}

		CWindow *CWindow::setOnHelp(const FOnHelp value)
		{
			m_fOnHelp = value;
			return this;
		}

		CWindow *CWindow::setOnNonClientPaint(const FOnNonClientPaint value)
		{
			m_fOnNonClientPaint = value;
			return this;
		}

		CWindow *CWindow::setOnInitMenu(const FOnInitMenu value)
		{
			m_fOnInitMenu = value;
			return this;
		}

		CWindow *CWindow::setOnInitMenuPopup(const FOnInitMenuPopup value)
		{
			m_fOnInitMenuPopup = value;
			return this;
		}

		CWindow *CWindow::setOnMenuClose(const FOnMenuClose value)
		{
			m_fOnMenuClose = value;
			return this;
		}

		CWindow *CWindow::setOnMenuSelect(const FOnMenuSelect value)
		{
			m_fOnMenuSelect = value;
			return this;
		}

		CWindow *CWindow::setOnMenuRightMouseButtonUp(const FOnMenuRightMouseButtonUp value)
		{
			m_fOnMenuRightMouseButtonUp = value;
			return this;
		}

		CWindow *CWindow::setOnMenuDrag(const FOnMenuDrag value)
		{
			m_fOnMenuDrag = value;
			return this;
		}

		CWindow *CWindow::setOnUninitMenuPopup(const FOnUninitMenuPopup value)
		{
			m_fOnUninitMenuPopup = value;
			return this;
		}

		CWindow *CWindow::setOnMenuCommand(const FOnMenuCommand value)
		{
			m_fOnMenuCommand = value;
			return this;
		}

		CWindow *CWindow::setOnNextMenu(const FOnNextMenu value)
		{
			m_fOnNextMenu = value;
			return this;
		}

		CWindow *CWindow::setOnDropFiles(const FOnDropFiles value)
		{
			m_fOnDropFiles = value;
			return this;
		}

		CWindow *CWindow::setOnTouch(const FOnTouch value)
		{
			m_fOnTouch = value;
			return this;
		}

		CWindow *CWindow::setOnPrint(const FOnPrint value)
		{
			m_fOnPrint = value;
			return this;
		}

		CWindow *CWindow::setOnPrintClient(const FOnPrintClient value)
		{
			m_fOnPrintClient = value;
			return this;
		}

		CWindow *CWindow::setOnCopyData(const FOnCopyData value)
		{
			m_fOnCopyData = value;
			return this;
		}
#pragma endregion

		IWindow::KEY CWindow::VirtualToKey(const int value)
		{
			switch (value)
			{
			case VK_LBUTTON: return keyLButton;
			case VK_RBUTTON: return keyRButton;
			case VK_CANCEL: return keyCancel;
			case VK_MBUTTON: return keyMButton;
			case VK_XBUTTON1: return keyXButton1;
			case VK_XBUTTON2: return keyXButton2;
			case VK_BACK: return keyBack;
			case VK_TAB: return keyTab;
			case VK_CLEAR: return keyClear;
			case VK_RETURN: return keyReturn;
			case VK_SHIFT: return keyShift;
			case VK_CONTROL: return keyControl;
			case VK_MENU: return keyMenu;
			case VK_PAUSE: return keyPause;
			case VK_CAPITAL: return keyCapital;
			case VK_KANA: return keyKana;
			case VK_JUNJA: return keyJunja;
			case VK_FINAL: return keyFinal;
			case VK_HANJA: return keyHanja;
			case VK_ESCAPE: return keyEscape;
			case VK_CONVERT: return keyConvert;
			case VK_NONCONVERT: return keyNonConvert;
			case VK_ACCEPT: return keyAccept;
			case VK_MODECHANGE: return keyModeChange;
			case VK_SPACE: return keySpace;
			case VK_PRIOR: return keyPrior;
			case VK_NEXT: return keyNext;
			case VK_END: return keyEnd;
			case VK_HOME: return keyHome;
			case VK_LEFT: return keyLeft;
			case VK_UP: return keyUp;
			case VK_RIGHT: return keyRight;
			case VK_DOWN: return keyDown;
			case VK_SELECT: return keySelect;
			case VK_PRINT: return keyPrint;
			case VK_EXECUTE: return keyExecute;
			case VK_SNAPSHOT: return keySnapshot;
			case VK_INSERT: return keyInsert;
			case VK_DELETE: return keyDelete;
			case VK_HELP: return keyHelp;
			case 0x30: return key0;
			case 0x31: return key1;
			case 0x32: return key2;
			case 0x33: return key3;
			case 0x34: return key4;
			case 0x35: return key5;
			case 0x36: return key6;
			case 0x37: return key7;
			case 0x38: return key8;
			case 0x39: return key9;
			case 0x41: return keyA;
			case 0x42: return keyB;
			case 0x43: return keyC;
			case 0x44: return keyD;
			case 0x45: return keyE;
			case 0x46: return keyF;
			case 0x47: return keyG;
			case 0x48: return keyH;
			case 0x49: return keyI;
			case 0x4A: return keyJ;
			case 0x4B: return keyK;
			case 0x4C: return keyL;
			case 0x4D: return keyM;
			case 0x4E: return keyN;
			case 0x4F: return keyO;
			case 0x50: return keyP;
			case 0x51: return keyQ;
			case 0x52: return keyR;
			case 0x53: return keyS;
			case 0x54: return keyT;
			case 0x55: return keyU;
			case 0x56: return keyV;
			case 0x57: return keyW;
			case 0x58: return keyX;
			case 0x59: return keyY;
			case 0x5A: return keyZ;
			case VK_LWIN: return keyLWin;
			case VK_RWIN: return keyRWin;
			case VK_APPS: return keyApps;
			case VK_SLEEP: return keySleep;
			case VK_NUMPAD0: return keyNumpad0;
			case VK_NUMPAD1: return keyNumpad1;
			case VK_NUMPAD2: return keyNumpad2;
			case VK_NUMPAD3: return keyNumpad3;
			case VK_NUMPAD4: return keyNumpad4;
			case VK_NUMPAD5: return keyNumpad5;
			case VK_NUMPAD6: return keyNumpad6;
			case VK_NUMPAD7: return keyNumpad7;
			case VK_NUMPAD8: return keyNumpad8;
			case VK_NUMPAD9: return keyNumpad9;
			case VK_MULTIPLY: return keyMultiply;
			case VK_ADD: return keyAdd;
			case VK_SEPARATOR: return keySeparator;
			case VK_SUBTRACT: return keySubtract;
			case VK_DECIMAL: return keyDecimal;
			case VK_DIVIDE: return keyDivide;
			case VK_F1: return keyF1;
			case VK_F2: return keyF2;
			case VK_F3: return keyF3;
			case VK_F4: return keyF4;
			case VK_F5: return keyF5;
			case VK_F6: return keyF6;
			case VK_F7: return keyF7;
			case VK_F8: return keyF8;
			case VK_F9: return keyF9;
			case VK_F10: return keyF10;
			case VK_F11: return keyF11;
			case VK_F12: return keyF12;
			case VK_F13: return keyF13;
			case VK_F14: return keyF14;
			case VK_F15: return keyF15;
			case VK_F16: return keyF16;
			case VK_F17: return keyF17;
			case VK_F18: return keyF18;
			case VK_F19: return keyF19;
			case VK_F20: return keyF20;
			case VK_F21: return keyF21;
			case VK_F22: return keyF22;
			case VK_F23: return keyF23;
			case VK_F24: return keyF24;
			case VK_NUMLOCK: return keyNumLock;
			case VK_SCROLL: return keyScroll;
			case VK_LSHIFT: return keyLShift;
			case VK_RSHIFT: return keyRShift;
			case VK_LCONTROL: return keyLControl;
			case VK_RCONTROL: return keyRControl;
			case VK_LMENU: return keyLMenu;
			case VK_RMENU: return keyRMenu;
			case VK_BROWSER_BACK: return keyBrowserBack;
			case VK_BROWSER_FORWARD: return keyBrowserForward;
			case VK_BROWSER_REFRESH: return keyBrowserRefresh;
			case VK_BROWSER_STOP: return keyBrowserStop;
			case VK_BROWSER_SEARCH: return keyBrowserSearch;
			case VK_BROWSER_FAVORITES: return keyBrowserFavorites;
			case VK_BROWSER_HOME: return keyBrowserHome;
			case VK_VOLUME_MUTE: return keyVolumeMute;
			case VK_VOLUME_DOWN: return keyVolumeDown;
			case VK_VOLUME_UP: return keyVolumeUp;
			case VK_MEDIA_NEXT_TRACK: return keyMediaNextTrack;
			case VK_MEDIA_PREV_TRACK: return keyMediaPrevTrack;
			case VK_MEDIA_STOP: return keyMediaStop;
			case VK_MEDIA_PLAY_PAUSE: return keyMediaPlayPause;
			case VK_LAUNCH_MAIL: return keyLaunchMail;
			case VK_LAUNCH_MEDIA_SELECT: return keyLaunchMediaSelect;
			case VK_LAUNCH_APP1: return keyLaunchApp1;
			case VK_LAUNCH_APP2: return keyLaunchApp2;
			case VK_OEM_1: return keyOem1;
			case VK_OEM_PLUS: return keyOemPlus;
			case VK_OEM_COMMA: return keyOemComma;
			case VK_OEM_MINUS: return keyOemMinus;
			case VK_OEM_PERIOD: return keyOemPeriod;
			case VK_OEM_2: return keyOem2;
			case VK_OEM_3: return keyOem3;
			case VK_OEM_4: return keyOem4;
			case VK_OEM_5: return keyOem5;
			case VK_OEM_6: return keyOem6;
			case VK_OEM_7: return keyOem7;
			case VK_OEM_8: return keyOem8;
			case VK_OEM_102: return keyOem102;
			case VK_PROCESSKEY: return keyProcessKey;
			case VK_PACKET: return keyPacket;
			case VK_ATTN: return keyAttn;
			case VK_CRSEL: return keyCrSel;
			case VK_EXSEL: return keyExSel;
			case VK_EREOF: return keyErEOF;
			case VK_PLAY: return keyPlay;
			case VK_ZOOM: return keyZoom;
			case VK_PA1: return keyPA1;
			case VK_OEM_CLEAR: return keyOemClear;
			default: return keyUnknown;
			}
		}

		int CWindow::KeyToVirtual(const KEY value)
		{
			switch (value)
			{
			case keyLButton: return VK_LBUTTON;
			case keyRButton: return VK_RBUTTON;
			case keyCancel: return VK_CANCEL;
			case keyMButton: return VK_MBUTTON;
			case keyXButton1: return VK_XBUTTON1;
			case keyXButton2: return VK_XBUTTON2;
			case keyBack: return VK_BACK;
			case keyTab: return VK_TAB;
			case keyClear: return VK_CLEAR;
			case keyReturn: return VK_RETURN;
			case keyShift: return VK_SHIFT;
			case keyControl: return VK_CONTROL;
			case keyMenu: return VK_MENU;
			case keyPause: return VK_PAUSE;
			case keyCapital: return VK_CAPITAL;
			case keyKana: return VK_KANA;
			case keyJunja: return VK_JUNJA;
			case keyFinal: return VK_FINAL;
			case keyHanja: return VK_HANJA;
			case keyEscape: return VK_ESCAPE;
			case keyConvert: return VK_CONVERT;
			case keyNonConvert: return VK_NONCONVERT;
			case keyAccept: return VK_ACCEPT;
			case keyModeChange: return VK_MODECHANGE;
			case keySpace: return VK_SPACE;
			case keyPrior: return VK_PRIOR;
			case keyNext: return VK_NEXT;
			case keyEnd: return VK_END;
			case keyHome: return VK_HOME;
			case keyLeft: return VK_LEFT;
			case keyUp: return VK_UP;
			case keyRight: return VK_RIGHT;
			case keyDown: return VK_DOWN;
			case keySelect: return VK_SELECT;
			case keyPrint: return VK_PRINT;
			case keyExecute: return VK_EXECUTE;
			case keySnapshot: return VK_SNAPSHOT;
			case keyInsert: return VK_INSERT;
			case keyDelete: return VK_DELETE;
			case keyHelp: return VK_HELP;
			case key0: return 0x30;
			case key1: return 0x31;
			case key2: return 0x32;
			case key3: return 0x33;
			case key4: return 0x34;
			case key5: return 0x35;
			case key6: return 0x36;
			case key7: return 0x37;
			case key8: return 0x38;
			case key9: return 0x39;
			case keyA: return 0x41;
			case keyB: return 0x42;
			case keyC: return 0x43;
			case keyD: return 0x44;
			case keyE: return 0x45;
			case keyF: return 0x46;
			case keyG: return 0x47;
			case keyH: return 0x48;
			case keyI: return 0x49;
			case keyJ: return 0x4A;
			case keyK: return 0x4B;
			case keyL: return 0x4C;
			case keyM: return 0x4D;
			case keyN: return 0x4E;
			case keyO: return 0x4F;
			case keyP: return 0x50;
			case keyQ: return 0x51;
			case keyR: return 0x52;
			case keyS: return 0x53;
			case keyT: return 0x54;
			case keyU: return 0x55;
			case keyV: return 0x56;
			case keyW: return 0x57;
			case keyX: return 0x58;
			case keyY: return 0x59;
			case keyZ: return 0x5A;
			case keyLWin: return VK_LWIN;
			case keyRWin: return VK_RWIN;
			case keyApps: return VK_APPS;
			case keySleep: return VK_SLEEP;
			case keyNumpad0: return VK_NUMPAD0;
			case keyNumpad1: return VK_NUMPAD1;
			case keyNumpad2: return VK_NUMPAD2;
			case keyNumpad3: return VK_NUMPAD3;
			case keyNumpad4: return VK_NUMPAD4;
			case keyNumpad5: return VK_NUMPAD5;
			case keyNumpad6: return VK_NUMPAD6;
			case keyNumpad7: return VK_NUMPAD7;
			case keyNumpad8: return VK_NUMPAD8;
			case keyNumpad9: return VK_NUMPAD9;
			case keyMultiply: return VK_MULTIPLY;
			case keyAdd: return VK_ADD;
			case keySeparator: return VK_SEPARATOR;
			case keySubtract: return VK_SUBTRACT;
			case keyDecimal: return VK_DECIMAL;
			case keyDivide: return VK_DIVIDE;
			case keyF1: return VK_F1;
			case keyF2: return VK_F2;
			case keyF3: return VK_F3;
			case keyF4: return VK_F4;
			case keyF5: return VK_F5;
			case keyF6: return VK_F6;
			case keyF7: return VK_F7;
			case keyF8: return VK_F8;
			case keyF9: return VK_F9;
			case keyF10: return VK_F10;
			case keyF11: return VK_F11;
			case keyF12: return VK_F12;
			case keyF13: return VK_F13;
			case keyF14: return VK_F14;
			case keyF15: return VK_F15;
			case keyF16: return VK_F16;
			case keyF17: return VK_F17;
			case keyF18: return VK_F18;
			case keyF19: return VK_F19;
			case keyF20: return VK_F20;
			case keyF21: return VK_F21;
			case keyF22: return VK_F22;
			case keyF23: return VK_F23;
			case keyF24: return VK_F24;
			case keyNumLock: return VK_NUMLOCK;
			case keyScroll: return VK_SCROLL;
			case keyLShift: return VK_LSHIFT;
			case keyRShift: return VK_RSHIFT;
			case keyLControl: return VK_LCONTROL;
			case keyRControl: return VK_RCONTROL;
			case keyLMenu: return VK_LMENU;
			case keyRMenu: return VK_RMENU;
			case keyBrowserBack: return VK_BROWSER_BACK;
			case keyBrowserForward: return VK_BROWSER_FORWARD;
			case keyBrowserRefresh: return VK_BROWSER_REFRESH;
			case keyBrowserStop: return VK_BROWSER_STOP;
			case keyBrowserSearch: return VK_BROWSER_SEARCH;
			case keyBrowserFavorites: return VK_BROWSER_FAVORITES;
			case keyBrowserHome: return VK_BROWSER_HOME;
			case keyVolumeMute: return VK_VOLUME_MUTE;
			case keyVolumeDown: return VK_VOLUME_DOWN;
			case keyVolumeUp: return VK_VOLUME_UP;
			case keyMediaNextTrack: return VK_MEDIA_NEXT_TRACK;
			case keyMediaPrevTrack: return VK_MEDIA_PREV_TRACK;
			case keyMediaStop: return VK_MEDIA_STOP;
			case keyMediaPlayPause: return VK_MEDIA_PLAY_PAUSE;
			case keyLaunchMail: return VK_LAUNCH_MAIL;
			case keyLaunchMediaSelect: return VK_LAUNCH_MEDIA_SELECT;
			case keyLaunchApp1: return VK_LAUNCH_APP1;
			case keyLaunchApp2: return VK_LAUNCH_APP2;
			case keyOem1: return VK_OEM_1;
			case keyOemPlus: return VK_OEM_PLUS;
			case keyOemComma: return VK_OEM_COMMA;
			case keyOemMinus: return VK_OEM_MINUS;
			case keyOemPeriod: return VK_OEM_PERIOD;
			case keyOem2: return VK_OEM_2;
			case keyOem3: return VK_OEM_3;
			case keyOem4: return VK_OEM_4;
			case keyOem5: return VK_OEM_5;
			case keyOem6: return VK_OEM_6;
			case keyOem7: return VK_OEM_7;
			case keyOem8: return VK_OEM_8;
			case keyOem102: return VK_OEM_102;
			case keyProcessKey: return VK_PROCESSKEY;
			case keyPacket: return VK_PACKET;
			case keyAttn: return VK_ATTN;
			case keyCrSel: return VK_CRSEL;
			case keyExSel: return VK_EXSEL;
			case keyErEOF: return VK_EREOF;
			case keyPlay: return VK_PLAY;
			case keyZoom: return VK_ZOOM;
			case keyPA1: return VK_PA1;
			case keyOemClear: return VK_OEM_CLEAR;
			default: return 0;
			}
		}
	}
}