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

			String getCaption() const override;
			APP_RECT getRect() const override;
			APP_RECT getClientRect() const override;
			APP_POINT getSize() const override;
			APP_POINT getPosition() const override;
			int getLeft() const override;
			int getTop() const override;
			int getWidth() const override;
			int getHeight() const override;
			bool getVisible() const override;
			bool getEnabled() const override;
			int getClientWidth() const override;
			int getClientHeight() const override;
			bool getIsCreated() const override;
			bool getCursorPosition(int &x, int &y) const override;
			void *getHandle() const override;
			void getControlKeys(bool &ctrl, bool &shift, bool &alt) const override;
			WINDOW_STATE getWindowState() override;
			bool getKeyIsDown(KEY key) override;
			bool getKeyIsToggled(KEY key) override;

			IWindow *setHandle(const HWND value);

			IWindow *setCaption(const String &value) const override;
			IWindow *setRect(const APP_RECT &value) const override;
			IWindow *setSize(const APP_POINT &value) const override;
			IWindow *setPosition(const APP_POINT &value) const override;
			IWindow *setLeft(const int value) const override;
			IWindow *setTop(const int value) const override;
			IWindow *setWidth(const int value) const override;
			IWindow *setHeight(const int value) const override;
			IWindow *setVisible(const bool value) const override;
			IWindow *setEnabled(const bool value) const override;
			IWindow *setCursor(const CURSOR_TYPE value) override;

			CWindow();
			virtual ~CWindow();

			IWindow *Show() const override;
			IWindow *Hide() const override;
			bool Create() override;
			unsigned int CreateTimer(unsigned int id, unsigned int interval) override;
			void DeleteTimer(unsigned int id) override;
			void StartTrackMouseLeave() override;
			bool CaptureMouse() override;
			void ReleaseMouseCapture() override;
			APP_POINT ClientToScreen(const APP_POINT &value) override;
			APP_POINT ScreenToClient(const APP_POINT &value) override;
			void Maximize() override;
			void Minimize() override;
			void Restore() override;
			bool CreateCaret(const int width, const int height) override;
			bool DestroyCaret() override;
			bool ShowCaret() override;
			bool HideCaret() override;
			bool SetCaretPosition(const int x, const int y) override;
			bool IsCaretVisible() override;
			bool CopyStringToClipboard(const String &str) override;
			String CopyStringFromClipboard() override;

			LRESULT WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		};
	}
}