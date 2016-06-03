// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#pragma once

#include <vector>
#include "..\Strings\Strings.h"
#include "Types.h"
#include "Font.h"
#include "Window.h"

namespace licui
{
	namespace application
	{
		class CForm
		{
			friend CComponent;
			friend CControl;
		public:
			struct SHORTCUT
			{
				IWindow::KEY Key;
				bool Control;
				bool Alt;
				bool Shift;

				static String GetKeyName(const IWindow::KEY key);
			};
		private:
			struct TIMER
			{
				void(*Callback)(void *param);
				void *Param;
				unsigned int Id;
			};

			struct HOTKEY
			{
				CComponent *Component;
				IWindow::KEY Key;
				bool Ctrl;
				bool Alt;
				bool Shift;
				bool IsDown; // Whether down or up event
			};
		private:
			static void WindowOnCreate(void *param);
			static void WindowOnDestroy(void *param);
			static void WindowOnMove(const int x, const int y, void *param);
			static void WindowOnRestore(const int width, const int height, void *param);
			static void WindowOnMinimize(const int width, const int height, void *param);
			static void WindowOnMaximize(const int width, const int height, void *param);
			static void WindowOnActivate(const bool byclick, void *param);
			static void WindowOnDeactivate(void *param);
			static void WindowOnSetFocus(void *param);
			static void WindowOnKillFocus(void *param);
			static void WindowOnEnable(void *param);
			static void WindowOnDisable(void *param);
			static void WindowOnPaint(const int left, const int top, const int right, const int bottom, void *param);
			static void WindowOnClose(IWindow::CLOSE_ACTION &action, void *param);
			static bool WindowOnQueryEndSession(void *param);
			static bool WindowOnQueryOpen(void *param);
			static void WindowOnEndSession(const bool ending, void *param);
			static void WindowOnShow(void *param);
			static void WindowOnHide(void *param);
			static void WindowOnDeviceModeChange(void *param);
			static void WindowOnActivateApp(void *param);
			static void WindowOnDeactivateApp(void *param);
			static void WindowOnTimeChange(void *param);
			static bool WindowOnInputLanguageChangeRequest(void *param);
			static void WindowOnInputLanguageChange(void *param);
			static bool WindowOnContextMenu(const int x, const int y, void *param);
			static void WindowOnDisplayChange(const int width, const int height, void *param);
			static void WindowOnKeyDown(const IWindow::KEY key, void *param);
			static void WindowOnKeyUp(const IWindow::KEY key, void *param);
			static void WindowOnChar(const wchar_t chr, void *param);
			static void WindowOnDeadChar(const wchar_t chr, void *param);
			static void WindowOnSysKeyDown(const IWindow::KEY key, void *param);
			static void WindowOnSysKeyUp(const IWindow::KEY key, void *param);
			static void WindowOnSysChar(const wchar_t chr, void *param);
			static void WindowOnSysDeadChar(const wchar_t chr, void *param);
			static bool WindowOnInitDialog(void *param);
			static void WindowOnSysCommand(const IWindow::SYSTEM_COMMAND_TYPE type, const int x, const int y, void *param);
			static void WindowOnHScroll(const IWindow::SCROLL_TYPE type, const int pos, void *param);
			static void WindowOnVScroll(const IWindow::SCROLL_TYPE type, const int pos, void *param);
			static void WindowOnGestureZoom(const int x, const int y, void *param);
			static void WindowOnGesturePan(const int x, const int y, void *param);
			static void WindowOnGestureRotate(const int x, const int y, void *param);
			static void WindowOnGestureTwoFingerTap(const int x, const int y, void *param);
			static void WindowOnGesturePressAndTap(const int x, const int y, void *param);
			static void WindowOnGestureNotify(void *param);
			static void WindowOnEnterIdleDialog(void *param);
			static void WindowOnEnterIdleMenu(void *param);
			static void WindowOnMouseMove(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift, void *param);
			static void WindowOnLeftMouseButtonDown(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift, void *param);
			static void WindowOnLeftMouseButtonUp(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift, void *param);
			static void WindowOnLeftMouseButtonDoubleClick(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift, void *param);
			static void WindowOnRightMouseButtonDown(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift, void *param);
			static void WindowOnRightMouseButtonUp(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift, void *param);
			static void WindowOnRightMouseButtonDoubleClick(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift, void *param);
			static void WindowOnMiddleMouseButtonDown(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift, void *param);
			static void WindowOnMiddleMouseButtonUp(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift, void *param);
			static void WindowOnMiddleMouseButtonDoubleClick(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift, void *param);
			static void WindowOnMouseVerticalWheel(const int x, const int y, const int delta, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift, void *param);
			static void WindowOnMouseHorizontalWheel(const int x, const int y, const int delta, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift, void *param);
			static void WindowOnResizing(const IWindow::EDGE edge, const int left, const int top, const int right, const int bottom, void *param);
			static void WindowOnLoseCapture(void *param);
			static void WindowOnMoving(const int left, const int top, const int right, const int bottom, void *param);
			static void WindowOnEnterSizeMove(void *param);
			static void WindowOnExitSizeMove(void *param);
			static void WindowOnMouseHover(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift, void *param);
			static void WindowOnMouseLeave(void *param);
			static void WindowOnHotKey(const bool is_desktop, const IWindow::KEY key, const bool alt, const bool ctrl, const bool shift, const bool win, void *param);
			static void WindowOnThemeChanged(void *param);
			static void WindowOnClipboardUpdate(void *param);
			static void WindowOnTimer(const unsigned int id, void *param);
			static void WindowOnNonClientMouseMove(const int x, const int y, void *param);
			static void WindowOnNonClientLeftMouseButtonDown(const int x, const int y, void *param);
			static void WindowOnNonClientLeftMouseButtonUp(const int x, const int y, void *param);
			static void WindowOnNonClientLeftMouseButtonDoubleClick(const int x, const int y, void *param);
			static void WindowOnNonClientRightMouseButtonDown(const int x, const int y, void *param);
			static void WindowOnNonClientRightMouseButtonUp(const int x, const int y, void *param);
			static void WindowOnNonClientRightMouseButtonDoubleClick(const int x, const int y, void *param);
			static void WindowOnNonClientMiddleMouseButtonDown(const int x, const int y, void *param);
			static void WindowOnNonClientMiddleMouseButtonUp(const int x, const int y, void *param);
			static void WindowOnNonClientMiddleMouseButtonDoubleClick(const int x, const int y, void *param);
			static void WindowOnEnterMenuLoop(const bool track_popup_menu_used, void *param);
			static void WindowOnExitMenuLoop(const bool is_shortcut, void *param);
			static void WindowOnNonClientMouseHover(const int x, const int y, void *param);
			static void WindowOnNonClientMouseLeave(void *param);

			static void FontOnChangeName(void *param);
			static void FontOnChangeHeight(void *param);
			static void FontOnChangeWeight(void *param);
			static void FontOnChangeItalic(void *param);
			static void FontOnChangeUnderline(void *param);
			static void FontOnChangeStrikeOut(void *param);
			static void FontOnChangeWidth(void *param);
			static void FontOnChangeCharSet(void *param);
			static void FontOnChangeQuality(void *param);
			static void FontOnChangePitchAndFamily(void *param);
			static void FontOnChangeOrientation(void *param);
			static void FontOnChangeDistance(void *param);
			static void FontOnChangeShadow(void *param);
			static void FontOnChangeShadowShift(void *param);
			static void FontOnChangeShadowBlur(void *param);
			static void FontOnChangeShadowColor(void *param);
			static void FontOnChangeColor(void *param);
			static void FontOnChangeInterpolate(void *param);
			static void FontOnBeginChange(void *param);
			static void FontOnEndChange(void *param);

			int m_iRepaintLockCount;
			APP_RECT m_sRepaintRect;
			bool m_bRepaintRequired;

			bool InitializeWindow();
			bool InitializeFont();

			std::vector<CComponent*> m_aComponents;
			bool m_bIsComponentsSorted;

			void SortComponents();
			int FindComponentIndex(const String &name);
			bool ValidateComponentName(const String &name, CComponent *exclude);

			std::vector<CControl*> m_aControls;
			std::vector<CControl*> m_aControlsRoot;
			std::vector<CControl*> m_aCaptureMouseControls;
			std::vector<CControl*> m_aCaptureKeyboardControls;
			bool m_bIsControlsSorted;
			CControl *m_pControlForSearch;
			CControl *m_pActiveControl;
			CControl *m_pOldActiveControl;
			CControl *m_pCaptureKeyboardControl;
			CControl *m_pCaptureMouseControl;
			CControl *m_pHoveredControl;

			void SortControls();
			int FindControlIndex(const String &name);
			bool ValidateControlName(const String &name, CControl *exclude);
			void ActivateControlAtClick(const int x, const int y);
			size_t CalculateTotalControlCount(CControl *control);
			size_t CalculateTotalControlCount();
			void UpdateTabOrders(CControl *control, const size_t old_order, const size_t new_order);
			void UpdateTabOrders(const size_t old_order, const size_t new_order);
			CControl *SearchPrevControl(CControl *control, const int order, CControl *best, const bool tab_stop);
			CControl *SearchPrevControl(const int order, const bool tab_stop);
			CControl *SearchNextControl(CControl *control, const int order, CControl *best, const bool tab_stop);
			CControl *SearchNextControl(const int order, const bool tab_stop);

			std::vector<TIMER> m_aTimers;
			bool m_bIsTrackingMouseLeave;
			APP_RECT m_sOldClientRect;
			bool m_bIsFontChanging;
			bool m_bIsFontSizeChanged;
			bool m_bIsFontStyleChanged;
			IFont *m_pFont;
			CStyle *m_pStyle;
			IWindow *m_pWindow;
			IPresenter *m_pPresenter;
			CImageManager *m_pImageManager;
			bool m_bSpecialKeyProcessed;
			std::vector<HOTKEY> m_aHotkeys;

			bool ProcessSpecialKeyDown(const IWindow::KEY key);
			void ProcessDownHotkeys(const IWindow::KEY key);
			void ProcessUpHotkeys(const IWindow::KEY key);
			void CleanCaptureKeyboardHistory();
			void CleanCaptureMouseHistory();
		protected:
			virtual void NotifyOnCreate();
			virtual void NotifyOnDestroy();
			virtual void NotifyOnMove(const int x, const int y);
			virtual void NotifyOnRestore(const int width, const int height);
			virtual void NotifyOnMinimize(const int width, const int height);
			virtual void NotifyOnMaximize(const int width, const int height);
			virtual void NotifyOnActivate(const bool byclick);
			virtual void NotifyOnDeactivate();
			virtual void NotifyOnSetFocus();
			virtual void NotifyOnKillFocus();
			virtual void NotifyOnEnable();
			virtual void NotifyOnDisable();
			virtual void NotifyOnPaint(const int left, const int top, const int right, const int bottom);
			virtual void NotifyOnClose(IWindow::CLOSE_ACTION &action);
			virtual bool NotifyOnQueryEndSession();
			virtual bool NotifyOnQueryOpen();
			virtual void NotifyOnEndSession(const bool ending);
			virtual void NotifyOnShow();
			virtual void NotifyOnHide();
			virtual void NotifyOnDeviceModeChange();
			virtual void NotifyOnActivateApp();
			virtual void NotifyOnDeactivateApp();
			virtual void NotifyOnTimeChange();
			virtual bool NotifyOnInputLanguageChangeRequest();
			virtual void NotifyOnInputLanguageChange();
			virtual bool NotifyOnContextMenu(const int x, const int y);
			virtual void NotifyOnDisplayChange(const int width, const int height);
			virtual void NotifyOnKeyDown(const IWindow::KEY key);
			virtual void NotifyOnKeyUp(const IWindow::KEY key);
			virtual void NotifyOnChar(const wchar_t chr);
			virtual void NotifyOnDeadChar(const wchar_t chr);
			virtual void NotifyOnSysKeyDown(const IWindow::KEY key);
			virtual void NotifyOnSysKeyUp(const IWindow::KEY key);
			virtual void NotifyOnSysChar(const wchar_t chr);
			virtual void NotifyOnSysDeadChar(const wchar_t chr);
			virtual bool NotifyOnInitDialog();
			virtual void NotifyOnSysCommand(const IWindow::SYSTEM_COMMAND_TYPE type, const int x, const int y);
			virtual void NotifyOnHScroll(const IWindow::SCROLL_TYPE type, const int pos);
			virtual void NotifyOnVScroll(const IWindow::SCROLL_TYPE type, const int pos);
			virtual void NotifyOnGestureZoom(const int x, const int y);
			virtual void NotifyOnGesturePan(const int x, const int y);
			virtual void NotifyOnGestureRotate(const int x, const int y);
			virtual void NotifyOnGestureTwoFingerTap(const int x, const int y);
			virtual void NotifyOnGesturePressAndTap(const int x, const int y);
			virtual void NotifyOnGestureNotify();
			virtual void NotifyOnEnterIdleDialog();
			virtual void NotifyOnEnterIdleMenu();
			virtual void NotifyOnMouseMove(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift);
			virtual void NotifyOnLeftMouseButtonDown(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift);
			virtual void NotifyOnLeftMouseButtonUp(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift);
			virtual void NotifyOnLeftMouseButtonDoubleClick(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift);
			virtual void NotifyOnRightMouseButtonDown(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift);
			virtual void NotifyOnRightMouseButtonUp(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift);
			virtual void NotifyOnRightMouseButtonDoubleClick(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift);
			virtual void NotifyOnMiddleMouseButtonDown(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift);
			virtual void NotifyOnMiddleMouseButtonUp(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift);
			virtual void NotifyOnMiddleMouseButtonDoubleClick(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift);
			virtual void NotifyOnMouseVerticalWheel(const int x, const int y, const int delta, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift);
			virtual void NotifyOnMouseHorizontalWheel(const int x, const int y, const int delta, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift);
			virtual void NotifyOnResizing(const IWindow::EDGE edge, const int left, const int top, const int right, const int bottom);
			virtual void NotifyOnLoseCapture();
			virtual void NotifyOnMoving(const int left, const int top, const int right, const int bottom);
			virtual void NotifyOnEnterSizeMove();
			virtual void NotifyOnExitSizeMove();
			virtual void NotifyOnMouseHover(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift);
			virtual void NotifyOnMouseLeave();
			virtual void NotifyOnHotKey(const bool is_desktop, const IWindow::KEY key, const bool alt, const bool ctrl, const bool shift, const bool win);
			virtual void NotifyOnThemeChanged();
			virtual void NotifyOnClipboardUpdate();
			virtual void NotifyOnTimer(const unsigned int id);
			virtual void NotifyOnNonClientMouseMove(const int x, const int y);
			virtual void NotifyOnNonClientLeftMouseButtonDown(const int x, const int y);
			virtual void NotifyOnNonClientLeftMouseButtonUp(const int x, const int y);
			virtual void NotifyOnNonClientLeftMouseButtonDoubleClick(const int x, const int y);
			virtual void NotifyOnNonClientRightMouseButtonDown(const int x, const int y);
			virtual void NotifyOnNonClientRightMouseButtonUp(const int x, const int y);
			virtual void NotifyOnNonClientRightMouseButtonDoubleClick(const int x, const int y);
			virtual void NotifyOnNonClientMiddleMouseButtonDown(const int x, const int y);
			virtual void NotifyOnNonClientMiddleMouseButtonUp(const int x, const int y);
			virtual void NotifyOnNonClientMiddleMouseButtonDoubleClick(const int x, const int y);
			virtual void NotifyOnEnterMenuLoop(const bool track_popup_menu_used);
			virtual void NotifyOnExitMenuLoop(const bool is_shortcut);
			virtual void NotifyOnNonClientMouseHover(const int x, const int y);
			virtual void NotifyOnNonClientMouseLeave();

			virtual void NotifyOnFontChangeName();
			virtual void NotifyOnFontChangeHeight();
			virtual void NotifyOnFontChangeWeight();
			virtual void NotifyOnFontChangeItalic();
			virtual void NotifyOnFontChangeUnderline();
			virtual void NotifyOnFontChangeStrikeOut();
			virtual void NotifyOnFontChangeWidth();
			virtual void NotifyOnFontChangeCharSet();
			virtual void NotifyOnFontChangeQuality();
			virtual void NotifyOnFontChangePitchAndFamily();
			virtual void NotifyOnFontChangeOrientation();
			virtual void NotifyOnFontChangeDistance();
			virtual void NotifyOnFontChangeShadow();
			virtual void NotifyOnFontChangeShadowShift();
			virtual void NotifyOnFontChangeShadowBlur();
			virtual void NotifyOnFontChangeShadowColor();
			virtual void NotifyOnFontChangeColor();
			virtual void NotifyOnFontChangeInterpolate();
			virtual void NotifyOnFontBeginChange();
			virtual void NotifyOnFontEndChange();
			virtual void NotifyOnFontChangeSize();
			virtual void NotifyOnFontChangeStyle();

			virtual void NotifyOnChangeActiveControl(CControl *old_control, CControl *new_control);
			virtual void NotifyOnChangeStyle();
			virtual void NotifyOnChangeBackgroundColor();
			virtual void NotifyOnBeforeDetachControl(CControl *control);
			virtual void NotifyOnDetachControl(CControl *control);
			virtual void NotifyOnAttachControl(CControl *control);
			virtual void NotifyOnChildControlResize(CControl *control, const APP_POINT &old_size, const APP_POINT &new_size);
			virtual void NotifyOnChildControlMove(CControl *control, const APP_POINT &old_position, const APP_POINT &new_position);
			virtual void NotifyOnMouseLeaveControl(CControl *control);
			virtual void NotifyOnMouseHoverControl(CControl *control);
			virtual void NotifyOnUpdateComponent(CComponent *component);
			virtual void NotifyOnUpdateControl(CControl *control);

			virtual void OnCreate() {};
			virtual void OnDestroy() {};
			virtual void OnMove(const int x, const int y) {};
			virtual void OnRestore(const int width, const int height) {};
			virtual void OnMinimize(const int width, const int height) {};
			virtual void OnMaximize(const int width, const int height) {};
			virtual void OnActivate(const bool byclick) {};
			virtual void OnDeactivate() {};
			virtual void OnSetFocus() {};
			virtual void OnKillFocus() {};
			virtual void OnEnable() {};
			virtual void OnDisable() {};
			virtual void OnPaint(const int left, const int top, const int right, const int bottom) {};
			virtual void OnClose(IWindow::CLOSE_ACTION &action) {};
			virtual bool OnQueryEndSession() { return true; };
			virtual bool OnQueryOpen() { return true; };
			virtual void OnEndSession(const bool ending) {};
			virtual void OnShow() {};
			virtual void OnHide() {};
			virtual void OnDeviceModeChange() {};
			virtual void OnActivateApp() {};
			virtual void OnDeactivateApp() {};
			virtual void OnTimeChange() {};
			virtual bool OnInputLanguageChangeRequest() { return true; };
			virtual void OnInputLanguageChange() {};
			virtual bool OnContextMenu(const int x, const int y) { return false; };
			virtual void OnDisplayChange(const int width, const int height) {};
			virtual void OnKeyDown(const IWindow::KEY key) {};
			virtual void OnKeyUp(const IWindow::KEY key) {};
			virtual void OnChar(const wchar_t chr) {};
			virtual void OnDeadChar(const wchar_t chr) {};
			virtual void OnSysKeyDown(const IWindow::KEY key) {};
			virtual void OnSysKeyUp(const IWindow::KEY key) {};
			virtual void OnSysChar(const wchar_t chr) {};
			virtual void OnSysDeadChar(const wchar_t chr) {};
			virtual bool OnInitDialog() { return false; };
			virtual void OnSysCommand(const IWindow::SYSTEM_COMMAND_TYPE type, const int x, const int y) {};
			virtual void OnHScroll(const IWindow::SCROLL_TYPE type, const int pos) {};
			virtual void OnVScroll(const IWindow::SCROLL_TYPE type, const int pos) {};
			virtual void OnGestureZoom(const int x, const int y) {};
			virtual void OnGesturePan(const int x, const int y) {};
			virtual void OnGestureRotate(const int x, const int y) {};
			virtual void OnGestureTwoFingerTap(const int x, const int y) {};
			virtual void OnGesturePressAndTap(const int x, const int y) {};
			virtual void OnGestureNotify() {};
			virtual void OnEnterIdleDialog() {};
			virtual void OnEnterIdleMenu() {};
			virtual void OnMouseMove(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift) {};
			virtual void OnLeftMouseButtonDown(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift) {};
			virtual void OnLeftMouseButtonUp(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift) {};
			virtual void OnLeftMouseButtonDoubleClick(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift) {};
			virtual void OnRightMouseButtonDown(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift) {};
			virtual void OnRightMouseButtonUp(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift) {};
			virtual void OnRightMouseButtonDoubleClick(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift) {};
			virtual void OnMiddleMouseButtonDown(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift) {};
			virtual void OnMiddleMouseButtonUp(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift) {};
			virtual void OnMiddleMouseButtonDoubleClick(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift) {};
			virtual void OnMouseVerticalWheel(const int x, const int y, const int delta, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift) {};
			virtual void OnMouseHorizontalWheel(const int x, const int y, const int delta, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift) {};
			virtual void OnResizing(const IWindow::EDGE edge, const int left, const int top, const int right, const int bottom) {};
			virtual void OnLoseCapture() {};
			virtual void OnMoving(const int left, const int top, const int right, const int bottom) {};
			virtual void OnEnterSizeMove() {};
			virtual void OnExitSizeMove() {};
			virtual void OnMouseHover(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift) {};
			virtual void OnMouseLeave() {};
			virtual void OnHotKey(const bool is_desktop, const IWindow::KEY key, const bool alt, const bool ctrl, const bool shift, const bool win) {};
			virtual void OnThemeChanged() {};
			virtual void OnClipboardUpdate() {};
			virtual void OnTimer(const unsigned int id) {};
			virtual void OnNonClientMouseMove(const int x, const int y) {};
			virtual void OnNonClientLeftMouseButtonDown(const int x, const int y) {};
			virtual void OnNonClientLeftMouseButtonUp(const int x, const int y) {};
			virtual void OnNonClientLeftMouseButtonDoubleClick(const int x, const int y) {};
			virtual void OnNonClientRightMouseButtonDown(const int x, const int y) {};
			virtual void OnNonClientRightMouseButtonUp(const int x, const int y) {};
			virtual void OnNonClientRightMouseButtonDoubleClick(const int x, const int y) {};
			virtual void OnNonClientMiddleMouseButtonDown(const int x, const int y) {};
			virtual void OnNonClientMiddleMouseButtonUp(const int x, const int y) {};
			virtual void OnNonClientMiddleMouseButtonDoubleClick(const int x, const int y) {};
			virtual void OnEnterMenuLoop(const bool track_popup_menu_used) {};
			virtual void OnExitMenuLoop(const bool is_shortcut) {};
			virtual void OnNonClientMouseHover(const int x, const int y) {};
			virtual void OnNonClientMouseLeave() {};

			virtual void OnFontChangeName() {};
			virtual void OnFontChangeHeight() {};
			virtual void OnFontChangeWeight() {};
			virtual void OnFontChangeItalic() {};
			virtual void OnFontChangeUnderline() {};
			virtual void OnFontChangeStrikeOut() {};
			virtual void OnFontChangeWidth() {};
			virtual void OnFontChangeCharSet() {};
			virtual void OnFontChangeQuality() {};
			virtual void OnFontChangePitchAndFamily() {};
			virtual void OnFontChangeOrientation() {};
			virtual void OnFontChangeDistance() {};
			virtual void OnFontChangeShadow() {};
			virtual void OnFontChangeShadowShift() {};
			virtual void OnFontChangeShadowBlur() {};
			virtual void OnFontChangeShadowColor() {};
			virtual void OnFontChangeColor() {};
			virtual void OnFontChangeInterpolate() {};
			virtual void OnFontBeginChange() {};
			virtual void OnFontEndChange() {};
			virtual void OnFontChangeSize() {};
			virtual void OnFontChangeStyle() {};

			virtual void OnChangeActiveControl(CControl *old_control, CControl *new_control) {};
			virtual void OnChangeStyle() {};
			virtual void OnChangeBackgroundColor() {};
			virtual void OnBeforeDetachControl(CControl *control) {};
			virtual void OnDetachControl(CControl *control) {};
			virtual void OnAttachControl(CControl *control) {};
			virtual void OnChildControlResize(CControl *control, const APP_POINT &old_size, const APP_POINT &new_size) {};
			virtual void OnChildControlMove(CControl *control, const APP_POINT &old_position, const APP_POINT &new_position) {};
			virtual void OnMouseLeaveControl(CControl *control) {};
			virtual void OnMouseHoverControl(CControl *control) {};
			virtual void OnUpdateComponent(CComponent *component) {};
			virtual void OnUpdateControl(CControl *control) {};

			String m_sClassName;
			CFontData m_cDefaultFont;
			APP_COLOR m_sBackgroundColor;
			CURSOR_TYPE m_eCursor;

			bool getRepaintRequired() const;
			void SendNotify_ParentResize();

			virtual bool Initialize(IWindow *window, IPresenter *presenter);
			virtual void Render();
		public:
			CForm();
			virtual ~CForm();

			virtual String getClassName() const;
			virtual IWindow *getWindow();
			virtual IPresenter *getPresenter();
			virtual CImageManager *getImageManager();
			virtual IFont *getFont();
			virtual CStyle *getStyle();
			virtual size_t getComponentCount() const;
			virtual CComponent *getComponent(const int index);
			virtual CComponent *getComponentByName(const String &name);
			virtual size_t getControlCount() const;
			virtual CControl *getControl(const int index);
			virtual CControl *getControlByName(const String &name);
			virtual CControl *getControlAtPosition(const int x, const int y);
			virtual size_t getRootControlCount() const;
			virtual CControl *getRootControl(const int index);
			virtual CControl *getActiveControl() const;
			virtual CControl *getCaptureKeyboardControl() const;
			virtual CControl *getCaptureMouseControl() const;
			virtual CControl *getHoveredControl();
			virtual APP_COLOR getBackgroundColor() const;
			virtual CURSOR_TYPE getCursor() const;

			virtual CForm *setStyle(CStyle *value);
			virtual CForm *setFont(IFont *value);
			virtual CForm *setActiveControl(CControl *value);
			virtual CForm *setCursor(const CURSOR_TYPE value);
			virtual CForm *setBackgroundColor(const APP_COLOR &value);

			virtual void LockRepaint();
			virtual void UnlockRepaint();
			virtual void Repaint();
			virtual void Repaint(const int left, const int top, const int right, const int bottom);
			virtual void Repaint(const APP_RECT &rect);

			virtual void AttachComponent(CComponent *component);
			virtual void DeleteComponent(const size_t index);
			virtual void DeleteComponent(CComponent *component);
			virtual void DeleteComponents();
			virtual void DetachComponent(CComponent *component);

			virtual void AttachControl(CControl *control);
			virtual void DeleteControl(const size_t index);
			virtual void DeleteControl(CControl *control);
			virtual void DeleteControls();
			virtual void DetachControl(CControl *control);
			virtual void ActivatePrevControl();
			virtual void ActivateNextControl();
			virtual void CaptureKeyboard(CControl *control);
			virtual void CaptureMouse(CControl *control);
			virtual void ReleaseCaptureKeyboard();
			virtual void ReleaseCaptureMouse();
			virtual void UpdateHoveredControl();
			virtual size_t FindMaxZIndex(const CControl *exclude = nullptr) const;

			virtual unsigned int AddTimer(void(*callback)(void *param), void *param, const unsigned int interval);
			virtual bool DeleteTimer(const unsigned int id);
			virtual void DeleteTimers();
			virtual bool ResetTimer(const unsigned int id, const unsigned int interval);

			virtual bool RegisterHotkey(CComponent *component, const IWindow::KEY key, const bool ctrl, const bool alt, const bool shift, const bool is_down);
			virtual void UnregisterHotkey(CComponent *component, const IWindow::KEY key, const bool ctrl, const bool alt, const bool shift, const bool is_down);
			virtual void UnregisterHotkeys(CComponent *component); // Called automatically when control is removing from form
		};
	}
}