// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#pragma once

#include "..\..\..\strings\Strings.h"
#include "..\..\Window.h"

#include <Windows.h>

namespace licui
{
	namespace application
	{
		class CWindow : public IWindow
		{
		public:
			typedef bool(*FOnHelp)(HELPINFO *info, void *param);
			typedef bool(*FOnNonClientPaint)(HRGN region, void *param);
			typedef void(*FOnInitMenu)(HMENU handle, void *param);
			typedef void(*FOnInitMenuPopup)(HMENU handle, int order, const bool is_window_menu, void *param);
			typedef void(*FOnMenuClose)(void *param);
			typedef void(*FOnMenuSelect)(int index, int flags, HMENU handle, void *param);
			typedef void(*FOnMenuRightMouseButtonUp)(int index, HMENU handle, void *param);
			typedef void(*FOnMenuDrag)(int position, HMENU handle, LRESULT &result, void *param);
			typedef void(*FOnUninitMenuPopup)(HMENU handle, void *param);
			typedef void(*FOnMenuCommand)(int index, HMENU handle, void *param);
			typedef bool(*FOnNextMenu)(int typedef_key, MDINEXTMENU *next_menu, void *param);
			typedef void(*FOnDropFiles)(HDROP drop, void *param);
			typedef void(*FOnTouch)(int count, TOUCHINPUT *inputs, void *param);
			typedef void(*FOnPrint)(HDC dc, int options, void *param);
			typedef void(*FOnPrintClient)(HDC dc, int options, void *param);
			typedef void(*FOnCopyData)(HWND src, COPYDATASTRUCT *data, void *param);
		private:
			CURSOR_TYPE m_eCurrentCursor;
			bool m_bCursorSet;
			bool m_bIsCaretCreated;
			bool m_bIsCaretVisible;
			APP_POINT m_sCaretSize;
			APP_POINT m_sCaretPosition;

			KEY VirtualToKey(const int value);
			int KeyToVirtual(const KEY value);
		protected:
			FOnHelp m_fOnHelp;
			FOnNonClientPaint m_fOnNonClientPaint;
			FOnInitMenu m_fOnInitMenu;
			FOnInitMenuPopup m_fOnInitMenuPopup;
			FOnMenuClose m_fOnMenuClose;
			FOnMenuSelect m_fOnMenuSelect;
			FOnMenuRightMouseButtonUp m_fOnMenuRightMouseButtonUp;
			FOnMenuDrag m_fOnMenuDrag;
			FOnUninitMenuPopup m_fOnUninitMenuPopup;
			FOnMenuCommand m_fOnMenuCommand;
			FOnNextMenu m_fOnNextMenu;
			FOnDropFiles m_fOnDropFiles;
			FOnTouch m_fOnTouch;
			FOnPrint m_fOnPrint;
			FOnPrintClient m_fOnPrintClient;
			FOnCopyData m_fOnCopyData;
			HWND m_hHandle;

			virtual bool HandleMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT &Result) { return false; }
		public:
			FOnHelp getOnHelp() const;
			FOnNonClientPaint getOnNonClientPaint() const;
			FOnInitMenu getOnInitMenu() const;
			FOnInitMenuPopup getOnInitMenuPopup() const;
			FOnMenuClose getOnMenuClose() const;
			FOnMenuSelect getOnMenuSelect() const;
			FOnMenuRightMouseButtonUp getOnMenuRightMouseButtonUp() const;
			FOnMenuDrag getOnMenuDrag() const;
			FOnUninitMenuPopup getOnUninitMenuPopup() const;
			FOnMenuCommand getOnMenuCommand() const;
			FOnNextMenu getOnNextMenu() const;
			FOnDropFiles getOnDropFiles() const;
			FOnTouch getOnTouch() const;
			FOnPrint getOnPrint() const;
			FOnPrintClient getOnPrintClient() const;
			FOnCopyData getOnCopyData() const;

			CWindow *setOnHelp(const FOnHelp value);
			CWindow *setOnNonClientPaint(const FOnNonClientPaint value);
			CWindow *setOnInitMenu(const FOnInitMenu value);
			CWindow *setOnInitMenuPopup(const FOnInitMenuPopup value);
			CWindow *setOnMenuClose(const FOnMenuClose value);
			CWindow *setOnMenuSelect(const FOnMenuSelect value);
			CWindow *setOnMenuRightMouseButtonUp(const FOnMenuRightMouseButtonUp value);
			CWindow *setOnMenuDrag(const FOnMenuDrag value);
			CWindow *setOnUninitMenuPopup(const FOnUninitMenuPopup value);
			CWindow *setOnMenuCommand(const FOnMenuCommand value);
			CWindow *setOnNextMenu(const FOnNextMenu value);
			CWindow *setOnDropFiles(const FOnDropFiles value);
			CWindow *setOnTouch(const FOnTouch value);
			CWindow *setOnPrint(const FOnPrint value);
			CWindow *setOnPrintClient(const FOnPrintClient value);
			CWindow *setOnCopyData(const FOnCopyData value);

			virtual String getCaption() const;
			virtual APP_RECT getRect() const;
			virtual APP_RECT getClientRect() const;
			virtual APP_POINT getSize() const;
			virtual APP_POINT getPosition() const;
			virtual int getLeft() const;
			virtual int getTop() const;
			virtual int getWidth() const;
			virtual int getHeight() const;
			virtual bool getVisible() const;
			virtual bool getEnabled() const;
			virtual int getClientWidth() const;
			virtual int getClientHeight() const;
			virtual bool getIsCreated() const;
			virtual bool getCursorPosition(int &x, int &y) const;
			virtual void *getHandle() const;
			virtual void getControlKeys(bool &ctrl, bool &shift, bool &alt) const;
			virtual WINDOW_STATE getWindowState();
			virtual bool getKeyIsDown(KEY key);
			virtual bool getKeyIsToggled(KEY key);

			IWindow *setHandle(const HWND value);
			virtual IWindow *setCaption(const String &value) const;
			virtual IWindow *setRect(const APP_RECT &value) const;
			virtual IWindow *setSize(const APP_POINT &value) const;
			virtual IWindow *setPosition(const APP_POINT &value) const;
			virtual IWindow *setLeft(const int value) const;
			virtual IWindow *setTop(const int value) const;
			virtual IWindow *setWidth(const int value) const;
			virtual IWindow *setHeight(const int value) const;
			virtual IWindow *setVisible(const bool value) const;
			virtual IWindow *setEnabled(const bool value) const;
			virtual IWindow *setCursor(const CURSOR_TYPE value);

			CWindow();
			virtual ~CWindow();

			virtual IWindow *Show() const;
			virtual IWindow *Hide() const;
			virtual bool Create();
			virtual unsigned int CreateTimer(unsigned int id, unsigned int interval);
			virtual void DeleteTimer(unsigned int id);
			virtual void StartTrackMouseLeave();
			virtual bool CaptureMouse();
			virtual void ReleaseMouseCapture();
			virtual APP_POINT ClientToScreen(const APP_POINT &value);
			virtual APP_POINT ScreenToClient(const APP_POINT &value);
			virtual void Maximize();
			virtual void Minimize();
			virtual void Restore();
			virtual bool CreateCaret(const int width, const int height);
			virtual bool DestroyCaret();
			virtual bool ShowCaret();
			virtual bool HideCaret();
			virtual bool SetCaretPosition(const int x, const int y);
			virtual bool IsCaretVisible();
			virtual bool CopyStringToClipboard(const String &str);
			virtual String CopyStringFromClipboard();

			LRESULT WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		};
	}
}