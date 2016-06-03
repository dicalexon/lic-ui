// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#include "Window.h"

namespace licui
{
	namespace application
	{
#pragma region Construction/Destruction
		IWindow::IWindow() :
			m_pCallbackParam{ nullptr },
			m_fOnCreate{ nullptr },
			m_fOnDestroy{ nullptr },
			m_fOnMove{ nullptr },
			m_fOnRestore{ nullptr },
			m_fOnMinimize{ nullptr },
			m_fOnMaximize{ nullptr },
			m_fOnActivate{ nullptr },
			m_fOnDeactivate{ nullptr },
			m_fOnSetFocus{ nullptr },
			m_fOnKillFocus{ nullptr },
			m_fOnEnable{ nullptr },
			m_fOnDisable{ nullptr },
			m_fOnPaint{ nullptr },
			m_fOnClose{ nullptr },
			m_fOnQueryEndSession{ nullptr },
			m_fOnQueryOpen{ nullptr },
			m_fOnEndSession{ nullptr },
			m_fOnShow{ nullptr },
			m_fOnHide{ nullptr },
			m_fOnDeviceModeChange{ nullptr },
			m_fOnActivateApp{ nullptr },
			m_fOnDeactivateApp{ nullptr },
			m_fOnTimeChange{ nullptr },
			m_fOnInputLanguageChangeRequest{ nullptr },
			m_fOnInputLanguageChange{ nullptr },
			m_fOnContextMenu{ nullptr },
			m_fOnDisplayChange{ nullptr },
			m_fOnKeyDown{ nullptr },
			m_fOnKeyUp{ nullptr },
			m_fOnChar{ nullptr },
			m_fOnDeadChar{ nullptr },
			m_fOnSysKeyDown{ nullptr },
			m_fOnSysKeyUp{ nullptr },
			m_fOnSysChar{ nullptr },
			m_fOnSysDeadChar{ nullptr },
			m_fOnInitDialog{ nullptr },
			m_fOnSysCommand{ nullptr },
			m_fOnHScroll{ nullptr },
			m_fOnVScroll{ nullptr },
			m_fOnGestureZoom{ nullptr },
			m_fOnGesturePan{ nullptr },
			m_fOnGestureRotate{ nullptr },
			m_fOnGestureTwoFingerTap{ nullptr },
			m_fOnGesturePressAndTap{ nullptr },
			m_fOnGestureNotify{ nullptr },
			m_fOnEnterIdleDialog{ nullptr },
			m_fOnEnterIdleMenu{ nullptr },
			m_fOnMouseMove{ nullptr },
			m_fOnLeftMouseButtonDown{ nullptr },
			m_fOnLeftMouseButtonUp{ nullptr },
			m_fOnLeftMouseButtonDoubleClick{ nullptr },
			m_fOnRightMouseButtonDown{ nullptr },
			m_fOnRightMouseButtonUp{ nullptr },
			m_fOnRightMouseButtonDoubleClick{ nullptr },
			m_fOnMiddleMouseButtonDown{ nullptr },
			m_fOnMiddleMouseButtonUp{ nullptr },
			m_fOnMiddleMouseButtonDoubleClick{ nullptr },
			m_fOnMouseVerticalWheel{ nullptr },
			m_fOnMouseHorizontalWheel{ nullptr },
			m_fOnResizing{ nullptr },
			m_fOnLoseCapture{ nullptr },
			m_fOnMoving{ nullptr },
			m_fOnEnterSizeMove{ nullptr },
			m_fOnExitSizeMove{ nullptr },
			m_fOnMouseHover{ nullptr },
			m_fOnMouseLeave{ nullptr },
			m_fOnHotKey{ nullptr },
			m_fOnThemeChanged{ nullptr },
			m_fOnClipboardUpdate{ nullptr },
			m_fOnTimer{ nullptr },
			m_fOnNonClientMouseMove{ nullptr },
			m_fOnNonClientLeftMouseButtonDown{ nullptr },
			m_fOnNonClientLeftMouseButtonUp{ nullptr },
			m_fOnNonClientLeftMouseButtonDoubleClick{ nullptr },
			m_fOnNonClientRightMouseButtonDown{ nullptr },
			m_fOnNonClientRightMouseButtonUp{ nullptr },
			m_fOnNonClientRightMouseButtonDoubleClick{ nullptr },
			m_fOnNonClientMiddleMouseButtonDown{ nullptr },
			m_fOnNonClientMiddleMouseButtonUp{ nullptr },
			m_fOnNonClientMiddleMouseButtonDoubleClick{ nullptr },
			m_fOnEnterMenuLoop{ nullptr },
			m_fOnExitMenuLoop{ nullptr },
			m_fOnNonClientMouseHover{ nullptr },
			m_fOnNonClientMouseLeave{ nullptr }
		{

		}
#pragma endregion

#pragma region Getters
		void *IWindow::getCallbackParam() const
		{
			return m_pCallbackParam;
		}

		IWindow::FOnCreate IWindow::getOnCreate() const
		{
			return m_fOnCreate;
		}

		IWindow::FOnDestroy IWindow::getOnDestroy() const
		{
			return m_fOnDestroy;
		}

		IWindow::FOnMove IWindow::getOnMove() const
		{
			return m_fOnMove;
		}

		IWindow::FOnRestore IWindow::getOnRestore() const
		{
			return m_fOnRestore;
		}

		IWindow::FOnMinimize IWindow::getOnMinimize() const
		{
			return m_fOnMinimize;
		}

		IWindow::FOnMaximize IWindow::getOnMaximize() const
		{
			return m_fOnMaximize;
		}

		IWindow::FOnActivate IWindow::getOnActivate() const
		{
			return m_fOnActivate;
		}

		IWindow::FOnDeactivate IWindow::getOnDeactivate() const
		{
			return m_fOnDeactivate;
		}

		IWindow::FOnSetFocus IWindow::getOnSetFocus() const
		{
			return m_fOnSetFocus;
		}

		IWindow::FOnKillFocus IWindow::getOnKillFocus() const
		{
			return m_fOnKillFocus;
		}

		IWindow::FOnEnable IWindow::getOnEnable() const
		{
			return m_fOnEnable;
		}

		IWindow::FOnDisable IWindow::getOnDisable() const
		{
			return m_fOnDisable;
		}

		IWindow::FOnPaint IWindow::getOnPaint() const
		{
			return m_fOnPaint;
		}

		IWindow::FOnClose IWindow::getOnClose() const
		{
			return m_fOnClose;
		}

		IWindow::FOnQueryEndSession IWindow::getOnQueryEndSession() const
		{
			return m_fOnQueryEndSession;
		}

		IWindow::FOnQueryOpen IWindow::getOnQueryOpen() const
		{
			return m_fOnQueryOpen;
		}

		IWindow::FOnEndSession IWindow::getOnEndSession() const
		{
			return m_fOnEndSession;
		}

		IWindow::FOnShow IWindow::getOnShow() const
		{
			return m_fOnShow;
		}

		IWindow::FOnHide IWindow::getOnHide() const
		{
			return m_fOnHide;
		}

		IWindow::FOnDeviceModeChange IWindow::getOnDeviceModeChange() const
		{
			return m_fOnDeviceModeChange;
		}

		IWindow::FOnActivateApp IWindow::getOnActivateApp() const
		{
			return m_fOnActivateApp;
		}

		IWindow::FOnDeactivateApp IWindow::getOnDeactivateApp() const
		{
			return m_fOnDeactivateApp;
		}

		IWindow::FOnTimeChange IWindow::getOnTimeChange() const
		{
			return m_fOnTimeChange;
		}

		IWindow::FOnInputLanguageChangeRequest IWindow::getOnInputLanguageChangeRequest() const
		{
			return m_fOnInputLanguageChangeRequest;
		}

		IWindow::FOnInputLanguageChange IWindow::getOnInputLanguageChange() const
		{
			return m_fOnInputLanguageChange;
		}

		IWindow::FOnContextMenu IWindow::getOnContextMenu() const
		{
			return m_fOnContextMenu;
		}

		IWindow::FOnDisplayChange IWindow::getOnDisplayChange() const
		{
			return m_fOnDisplayChange;
		}

		IWindow::FOnKeyDown IWindow::getOnKeyDown() const
		{
			return m_fOnKeyDown;
		}

		IWindow::FOnKeyUp IWindow::getOnKeyUp() const
		{
			return m_fOnKeyUp;
		}

		IWindow::FOnChar IWindow::getOnChar() const
		{
			return m_fOnChar;
		}

		IWindow::FOnDeadChar IWindow::getOnDeadChar() const
		{
			return m_fOnDeadChar;
		}

		IWindow::FOnSysKeyDown IWindow::getOnSysKeyDown() const
		{
			return m_fOnSysKeyDown;
		}

		IWindow::FOnSysKeyUp IWindow::getOnSysKeyUp() const
		{
			return m_fOnSysKeyUp;
		}

		IWindow::FOnSysChar IWindow::getOnSysChar() const
		{
			return m_fOnSysChar;
		}

		IWindow::FOnSysDeadChar IWindow::getOnSysDeadChar() const
		{
			return m_fOnSysDeadChar;
		}

		IWindow::FOnInitDialog IWindow::getOnInitDialog() const
		{
			return m_fOnInitDialog;
		}

		IWindow::FOnSysCommand IWindow::getOnSysCommand() const
		{
			return m_fOnSysCommand;
		}

		IWindow::FOnHScroll IWindow::getOnHScroll() const
		{
			return m_fOnHScroll;
		}

		IWindow::FOnVScroll IWindow::getOnVScroll() const
		{
			return m_fOnVScroll;
		}

		IWindow::FOnGestureZoom IWindow::getOnGestureZoom() const
		{
			return m_fOnGestureZoom;
		}

		IWindow::FOnGesturePan IWindow::getOnGesturePan() const
		{
			return m_fOnGesturePan;
		}

		IWindow::FOnGestureRotate IWindow::getOnGestureRotate() const
		{
			return m_fOnGestureRotate;
		}

		IWindow::FOnGestureTwoFingerTap IWindow::getOnGestureTwoFingerTap() const
		{
			return m_fOnGestureTwoFingerTap;
		}

		IWindow::FOnGesturePressAndTap IWindow::getOnGesturePressAndTap() const
		{
			return m_fOnGesturePressAndTap;
		}

		IWindow::FOnGestureNotify IWindow::getOnGestureNotify() const
		{
			return m_fOnGestureNotify;
		}

		IWindow::FOnEnterIdleDialog IWindow::getOnEnterIdleDialog() const
		{
			return m_fOnEnterIdleDialog;
		}

		IWindow::FOnEnterIdleMenu IWindow::getOnEnterIdleMenu() const
		{
			return m_fOnEnterIdleMenu;
		}

		IWindow::FOnMouseMove IWindow::getOnMouseMove() const
		{
			return m_fOnMouseMove;
		}

		IWindow::FOnLeftMouseButtonDown IWindow::getOnLeftMouseButtonDown() const
		{
			return m_fOnLeftMouseButtonDown;
		}

		IWindow::FOnLeftMouseButtonUp IWindow::getOnLeftMouseButtonUp() const
		{
			return m_fOnLeftMouseButtonUp;
		}

		IWindow::FOnLeftMouseButtonDoubleClick IWindow::getOnLeftMouseButtonDoubleClick() const
		{
			return m_fOnLeftMouseButtonDoubleClick;
		}

		IWindow::FOnRightMouseButtonDown IWindow::getOnRightMouseButtonDown() const
		{
			return m_fOnRightMouseButtonDown;
		}

		IWindow::FOnRightMouseButtonUp IWindow::getOnRightMouseButtonUp() const
		{
			return m_fOnRightMouseButtonUp;
		}

		IWindow::FOnRightMouseButtonDoubleClick IWindow::getOnRightMouseButtonDoubleClick() const
		{
			return m_fOnRightMouseButtonDoubleClick;
		}

		IWindow::FOnMiddleMouseButtonDown IWindow::getOnMiddleMouseButtonDown() const
		{
			return m_fOnMiddleMouseButtonDown;
		}

		IWindow::FOnMiddleMouseButtonUp IWindow::getOnMiddleMouseButtonUp() const
		{
			return m_fOnMiddleMouseButtonUp;
		}

		IWindow::FOnMiddleMouseButtonDoubleClick IWindow::getOnMiddleMouseButtonDoubleClick() const
		{
			return m_fOnMiddleMouseButtonDoubleClick;
		}

		IWindow::FOnMouseVerticalWheel IWindow::getOnMouseVerticalWheel() const
		{
			return m_fOnMouseVerticalWheel;
		}

		IWindow::FOnMouseHorizontalWheel IWindow::getOnMouseHorizontalWheel() const
		{
			return m_fOnMouseHorizontalWheel;
		}

		IWindow::FOnResizing IWindow::getOnResizing() const
		{
			return m_fOnResizing;
		}

		IWindow::FOnLoseCapture IWindow::getOnLoseCapture() const
		{
			return m_fOnLoseCapture;
		}

		IWindow::FOnMoving IWindow::getOnMoving() const
		{
			return m_fOnMoving;
		}

		IWindow::FOnEnterSizeMove IWindow::getOnEnterSizeMove() const
		{
			return m_fOnEnterSizeMove;
		}

		IWindow::FOnExitSizeMove IWindow::getOnExitSizeMove() const
		{
			return m_fOnExitSizeMove;
		}

		IWindow::FOnMouseHover IWindow::getOnMouseHover() const
		{
			return m_fOnMouseHover;
		}

		IWindow::FOnMouseLeave IWindow::getOnMouseLeave() const
		{
			return m_fOnMouseLeave;
		}

		IWindow::FOnHotKey IWindow::getOnHotKey() const
		{
			return m_fOnHotKey;
		}

		IWindow::FOnThemeChanged IWindow::getOnThemeChanged() const
		{
			return m_fOnThemeChanged;
		}

		IWindow::FOnClipboardUpdate IWindow::getOnClipboardUpdate() const
		{
			return m_fOnClipboardUpdate;
		}

		IWindow::FOnTimer IWindow::getOnTimer() const
		{
			return m_fOnTimer;
		}

		IWindow::FOnNonClientMouseMove IWindow::getOnNonClientMouseMove() const
		{
			return m_fOnNonClientMouseMove;
		}

		IWindow::FOnNonClientLeftMouseButtonDown IWindow::getOnNonClientLeftMouseButtonDown() const
		{
			return m_fOnNonClientLeftMouseButtonDown;
		}

		IWindow::FOnNonClientLeftMouseButtonUp IWindow::getOnNonClientLeftMouseButtonUp() const
		{
			return m_fOnNonClientLeftMouseButtonUp;
		}

		IWindow::FOnNonClientLeftMouseButtonDoubleClick IWindow::getOnNonClientLeftMouseButtonDoubleClick() const
		{
			return m_fOnNonClientLeftMouseButtonDoubleClick;
		}

		IWindow::FOnNonClientRightMouseButtonDown IWindow::getOnNonClientRightMouseButtonDown() const
		{
			return m_fOnNonClientRightMouseButtonDown;
		}

		IWindow::FOnNonClientRightMouseButtonUp IWindow::getOnNonClientRightMouseButtonUp() const
		{
			return m_fOnNonClientRightMouseButtonUp;
		}

		IWindow::FOnNonClientRightMouseButtonDoubleClick IWindow::getOnNonClientRightMouseButtonDoubleClick() const
		{
			return m_fOnNonClientRightMouseButtonDoubleClick;
		}

		IWindow::FOnNonClientMiddleMouseButtonDown IWindow::getOnNonClientMiddleMouseButtonDown() const
		{
			return m_fOnNonClientMiddleMouseButtonDown;
		}

		IWindow::FOnNonClientMiddleMouseButtonUp IWindow::getOnNonClientMiddleMouseButtonUp() const
		{
			return m_fOnNonClientMiddleMouseButtonUp;
		}

		IWindow::FOnNonClientMiddleMouseButtonDoubleClick IWindow::getOnNonClientMiddleMouseButtonDoubleClick() const
		{
			return m_fOnNonClientMiddleMouseButtonDoubleClick;
		}

		IWindow::FOnEnterMenuLoop IWindow::getOnEnterMenuLoop() const
		{
			return m_fOnEnterMenuLoop;
		}

		IWindow::FOnExitMenuLoop IWindow::getOnExitMenuLoop() const
		{
			return m_fOnExitMenuLoop;
		}

		IWindow::FOnNonClientMouseHover IWindow::getOnNonClientMouseHover() const
		{
			return m_fOnNonClientMouseHover;
		}

		IWindow::FOnNonClientMouseLeave IWindow::getOnNonClientMouseLeave() const
		{
			return m_fOnNonClientMouseLeave;
		}

		String IWindow::getDefaultClass() const
		{
			return m_sDefaultClass;
		}

		String IWindow::getDefaultCaption() const
		{
			return m_sDefaultCaption;
		}

		int IWindow::getDefaultX() const
		{
			return m_iDefaultX;
		}

		int IWindow::getDefaultY() const
		{
			return m_iDefaultY;
		}

		int IWindow::getDefaultWidth() const
		{
			return m_iDefaultWidth;
		}

		int IWindow::getDefaultHeight() const
		{
			return m_iDefaultHeight;
		}

		unsigned int IWindow::getDefaultStyle() const
		{
			return m_iDefaultStyle;
		}

		unsigned int IWindow::getDefaultStyleEx() const
		{
			return m_iDefaultStyleEx;
		}

		IWindow::WINDOW_STATE IWindow::getDefaultState() const
		{
			return m_eDefaultState;
		}
#pragma endregion

#pragma region Setters
		IWindow *IWindow::setCallbackParam(void *value)
		{
			m_pCallbackParam = value;
			return this;
		}

		IWindow *IWindow::setOnCreate(const FOnCreate value)
		{
			m_fOnCreate = value;
			return this;
		}

		IWindow *IWindow::setOnDestroy(const FOnDestroy value)
		{
			m_fOnDestroy = value;
			return this;
		}

		IWindow *IWindow::setOnMove(const FOnMove value)
		{
			m_fOnMove = value;
			return this;
		}

		IWindow *IWindow::setOnRestore(const FOnRestore value)
		{
			m_fOnRestore = value;
			return this;
		}

		IWindow *IWindow::setOnMinimize(const FOnMinimize value)
		{
			m_fOnMinimize = value;
			return this;
		}

		IWindow *IWindow::setOnMaximize(const FOnMaximize value)
		{
			m_fOnMaximize = value;
			return this;
		}

		IWindow *IWindow::setOnActivate(const FOnActivate value)
		{
			m_fOnActivate = value;
			return this;
		}

		IWindow *IWindow::setOnDeactivate(const FOnDeactivate value)
		{
			m_fOnDeactivate = value;
			return this;
		}

		IWindow *IWindow::setOnSetFocus(const FOnSetFocus value)
		{
			m_fOnSetFocus = value;
			return this;
		}

		IWindow *IWindow::setOnKillFocus(const FOnKillFocus value)
		{
			m_fOnKillFocus = value;
			return this;
		}

		IWindow *IWindow::setOnEnable(const FOnEnable value)
		{
			m_fOnEnable = value;
			return this;
		}

		IWindow *IWindow::setOnDisable(const FOnDisable value)
		{
			m_fOnDisable = value;
			return this;
		}

		IWindow *IWindow::setOnPaint(const FOnPaint value)
		{
			m_fOnPaint = value;
			return this;
		}

		IWindow *IWindow::setOnClose(const FOnClose value)
		{
			m_fOnClose = value;
			return this;
		}

		IWindow *IWindow::setOnQueryEndSession(const FOnQueryEndSession value)
		{
			m_fOnQueryEndSession = value;
			return this;
		}

		IWindow *IWindow::setOnQueryOpen(const FOnQueryOpen value)
		{
			m_fOnQueryOpen = value;
			return this;
		}

		IWindow *IWindow::setOnEndSession(const FOnEndSession value)
		{
			m_fOnEndSession = value;
			return this;
		}

		IWindow *IWindow::setOnShow(const FOnShow value)
		{
			m_fOnShow = value;
			return this;
		}

		IWindow *IWindow::setOnHide(const FOnHide value)
		{
			m_fOnHide = value;
			return this;
		}

		IWindow *IWindow::setOnDeviceModeChange(const FOnDeviceModeChange value)
		{
			m_fOnDeviceModeChange = value;
			return this;
		}

		IWindow *IWindow::setOnActivateApp(const FOnActivateApp value)
		{
			m_fOnActivateApp = value;
			return this;
		}

		IWindow *IWindow::setOnDeactivateApp(const FOnDeactivateApp value)
		{
			m_fOnDeactivateApp = value;
			return this;
		}

		IWindow *IWindow::setOnTimeChange(const FOnTimeChange value)
		{
			m_fOnTimeChange = value;
			return this;
		}

		IWindow *IWindow::setOnInputLanguageChangeRequest(const FOnInputLanguageChangeRequest value)
		{
			m_fOnInputLanguageChangeRequest = value;
			return this;
		}

		IWindow *IWindow::setOnInputLanguageChange(const FOnInputLanguageChange value)
		{
			m_fOnInputLanguageChange = value;
			return this;
		}

		IWindow *IWindow::setOnContextMenu(const FOnContextMenu value)
		{
			m_fOnContextMenu = value;
			return this;
		}

		IWindow *IWindow::setOnDisplayChange(const FOnDisplayChange value)
		{
			m_fOnDisplayChange = value;
			return this;
		}

		IWindow *IWindow::setOnKeyDown(const FOnKeyDown value)
		{
			m_fOnKeyDown = value;
			return this;
		}

		IWindow *IWindow::setOnKeyUp(const FOnKeyUp value)
		{
			m_fOnKeyUp = value;
			return this;
		}

		IWindow *IWindow::setOnChar(const FOnChar value)
		{
			m_fOnChar = value;
			return this;
		}

		IWindow *IWindow::setOnDeadChar(const FOnDeadChar value)
		{
			m_fOnDeadChar = value;
			return this;
		}

		IWindow *IWindow::setOnSysKeyDown(const FOnSysKeyDown value)
		{
			m_fOnSysKeyDown = value;
			return this;
		}

		IWindow *IWindow::setOnSysKeyUp(const FOnSysKeyUp value)
		{
			m_fOnSysKeyUp = value;
			return this;
		}

		IWindow *IWindow::setOnSysChar(const FOnSysChar value)
		{
			m_fOnSysChar = value;
			return this;
		}

		IWindow *IWindow::setOnSysDeadChar(const FOnSysDeadChar value)
		{
			m_fOnSysDeadChar = value;
			return this;
		}

		IWindow *IWindow::setOnInitDialog(const FOnInitDialog value)
		{
			m_fOnInitDialog = value;
			return this;
		}

		IWindow *IWindow::setOnSysCommand(const FOnSysCommand value)
		{
			m_fOnSysCommand = value;
			return this;
		}

		IWindow *IWindow::setOnHScroll(const FOnHScroll value)
		{
			m_fOnHScroll = value;
			return this;
		}

		IWindow *IWindow::setOnVScroll(const FOnVScroll value)
		{
			m_fOnVScroll = value;
			return this;
		}

		IWindow *IWindow::setOnGestureZoom(const FOnGestureZoom value)
		{
			m_fOnGestureZoom = value;
			return this;
		}

		IWindow *IWindow::setOnGesturePan(const FOnGesturePan value)
		{
			m_fOnGesturePan = value;
			return this;
		}

		IWindow *IWindow::setOnGestureRotate(const FOnGestureRotate value)
		{
			m_fOnGestureRotate = value;
			return this;
		}

		IWindow *IWindow::setOnGestureTwoFingerTap(const FOnGestureTwoFingerTap value)
		{
			m_fOnGestureTwoFingerTap = value;
			return this;
		}

		IWindow *IWindow::setOnGesturePressAndTap(const FOnGesturePressAndTap value)
		{
			m_fOnGesturePressAndTap = value;
			return this;
		}

		IWindow *IWindow::setOnGestureNotify(const FOnGestureNotify value)
		{
			m_fOnGestureNotify = value;
			return this;
		}

		IWindow *IWindow::setOnEnterIdleDialog(const FOnEnterIdleDialog value)
		{
			m_fOnEnterIdleDialog = value;
			return this;
		}

		IWindow *IWindow::setOnEnterIdleMenu(const FOnEnterIdleMenu value)
		{
			m_fOnEnterIdleMenu = value;
			return this;
		}

		IWindow *IWindow::setOnMouseMove(const FOnMouseMove value)
		{
			m_fOnMouseMove = value;
			return this;
		}

		IWindow *IWindow::setOnLeftMouseButtonDown(const FOnLeftMouseButtonDown value)
		{
			m_fOnLeftMouseButtonDown = value;
			return this;
		}

		IWindow *IWindow::setOnLeftMouseButtonUp(const FOnLeftMouseButtonUp value)
		{
			m_fOnLeftMouseButtonUp = value;
			return this;
		}

		IWindow *IWindow::setOnLeftMouseButtonDoubleClick(const FOnLeftMouseButtonDoubleClick value)
		{
			m_fOnLeftMouseButtonDoubleClick = value;
			return this;
		}

		IWindow *IWindow::setOnRightMouseButtonDown(const FOnRightMouseButtonDown value)
		{
			m_fOnRightMouseButtonDown = value;
			return this;
		}

		IWindow *IWindow::setOnRightMouseButtonUp(const FOnRightMouseButtonUp value)
		{
			m_fOnRightMouseButtonUp = value;
			return this;
		}

		IWindow *IWindow::setOnRightMouseButtonDoubleClick(const FOnRightMouseButtonDoubleClick value)
		{
			m_fOnRightMouseButtonDoubleClick = value;
			return this;
		}

		IWindow *IWindow::setOnMiddleMouseButtonDown(const FOnMiddleMouseButtonDown value)
		{
			m_fOnMiddleMouseButtonDown = value;
			return this;
		}

		IWindow *IWindow::setOnMiddleMouseButtonUp(const FOnMiddleMouseButtonUp value)
		{
			m_fOnMiddleMouseButtonUp = value;
			return this;
		}

		IWindow *IWindow::setOnMiddleMouseButtonDoubleClick(const FOnMiddleMouseButtonDoubleClick value)
		{
			m_fOnMiddleMouseButtonDoubleClick = value;
			return this;
		}

		IWindow *IWindow::setOnMouseVerticalWheel(const FOnMouseVerticalWheel value)
		{
			m_fOnMouseVerticalWheel = value;
			return this;
		}

		IWindow *IWindow::setOnMouseHorizontalWheel(const FOnMouseHorizontalWheel value)
		{
			m_fOnMouseHorizontalWheel = value;
			return this;
		}

		IWindow *IWindow::setOnResizing(const FOnResizing value)
		{
			m_fOnResizing = value;
			return this;
		}

		IWindow *IWindow::setOnLoseCapture(const FOnLoseCapture value)
		{
			m_fOnLoseCapture = value;
			return this;
		}

		IWindow *IWindow::setOnMoving(const FOnMoving value)
		{
			m_fOnMoving = value;
			return this;
		}

		IWindow *IWindow::setOnEnterSizeMove(const FOnEnterSizeMove value)
		{
			m_fOnEnterSizeMove = value;
			return this;
		}

		IWindow *IWindow::setOnExitSizeMove(const FOnExitSizeMove value)
		{
			m_fOnExitSizeMove = value;
			return this;
		}

		IWindow *IWindow::setOnMouseHover(const FOnMouseHover value)
		{
			m_fOnMouseHover = value;
			return this;
		}

		IWindow *IWindow::setOnMouseLeave(const FOnMouseLeave value)
		{
			m_fOnMouseLeave = value;
			return this;
		}

		IWindow *IWindow::setOnHotKey(const FOnHotKey value)
		{
			m_fOnHotKey = value;
			return this;
		}

		IWindow *IWindow::setOnThemeChanged(const FOnThemeChanged value)
		{
			m_fOnThemeChanged = value;
			return this;
		}

		IWindow *IWindow::setOnClipboardUpdate(const FOnClipboardUpdate value)
		{
			m_fOnClipboardUpdate = value;
			return this;
		}

		IWindow *IWindow::setOnTimer(const FOnTimer value)
		{
			m_fOnTimer = value;
			return this;
		}

		IWindow *IWindow::setOnNonClientMouseMove(const FOnNonClientMouseMove value)
		{
			m_fOnNonClientMouseMove = value;
			return this;
		}

		IWindow *IWindow::setOnNonClientLeftMouseButtonDown(const FOnNonClientLeftMouseButtonDown value)
		{
			m_fOnNonClientLeftMouseButtonDown = value;
			return this;
		}

		IWindow *IWindow::setOnNonClientLeftMouseButtonUp(const FOnNonClientLeftMouseButtonUp value)
		{
			m_fOnNonClientLeftMouseButtonUp = value;
			return this;
		}

		IWindow *IWindow::setOnNonClientLeftMouseButtonDoubleClick(const FOnNonClientLeftMouseButtonDoubleClick value)
		{
			m_fOnNonClientLeftMouseButtonDoubleClick = value;
			return this;
		}

		IWindow *IWindow::setOnNonClientRightMouseButtonDown(const FOnNonClientRightMouseButtonDown value)
		{
			m_fOnNonClientRightMouseButtonDown = value;
			return this;
		}

		IWindow *IWindow::setOnNonClientRightMouseButtonUp(const FOnNonClientRightMouseButtonUp value)
		{
			m_fOnNonClientRightMouseButtonUp = value;
			return this;
		}

		IWindow *IWindow::setOnNonClientRightMouseButtonDoubleClick(const FOnNonClientRightMouseButtonDoubleClick value)
		{
			m_fOnNonClientRightMouseButtonDoubleClick = value;
			return this;
		}

		IWindow *IWindow::setOnNonClientMiddleMouseButtonDown(const FOnNonClientMiddleMouseButtonDown value)
		{
			m_fOnNonClientMiddleMouseButtonDown = value;
			return this;
		}

		IWindow *IWindow::setOnNonClientMiddleMouseButtonUp(const FOnNonClientMiddleMouseButtonUp value)
		{
			m_fOnNonClientMiddleMouseButtonUp = value;
			return this;
		}

		IWindow *IWindow::setOnNonClientMiddleMouseButtonDoubleClick(const FOnNonClientMiddleMouseButtonDoubleClick value)
		{
			m_fOnNonClientMiddleMouseButtonDoubleClick = value;
			return this;
		}

		IWindow *IWindow::setOnEnterMenuLoop(const FOnEnterMenuLoop value)
		{
			m_fOnEnterMenuLoop = value;
			return this;
		}

		IWindow *IWindow::setOnExitMenuLoop(const FOnExitMenuLoop value)
		{
			m_fOnExitMenuLoop = value;
			return this;
		}

		IWindow *IWindow::setOnNonClientMouseHover(const FOnNonClientMouseHover value)
		{
			m_fOnNonClientMouseHover = value;
			return this;
		}

		IWindow *IWindow::setOnNonClientMouseLeave(const FOnNonClientMouseLeave value)
		{
			m_fOnNonClientMouseLeave = value;
			return this;
		}

		IWindow *IWindow::setDefaultClass(const String &value)
		{
			m_sDefaultClass = value;
			return this;
		}

		IWindow *IWindow::setDefaultCaption(const String &value)
		{
			m_sDefaultCaption = value;
			return this;
		}

		IWindow *IWindow::setDefaultX(const int value)
		{
			m_iDefaultX = value;
			return this;
		}

		IWindow *IWindow::setDefaultY(const int value)
		{
			m_iDefaultY = value;
			return this;
		}

		IWindow *IWindow::setDefaultWidth(const int value)
		{
			m_iDefaultWidth = value;
			return this;
		}

		IWindow *IWindow::setDefaultHeight(const int value)
		{
			m_iDefaultHeight = value;
			return this;
		}

		IWindow *IWindow::setDefaultStyle(const unsigned int value)
		{
			m_iDefaultStyle = value;
			return this;
		}

		IWindow *IWindow::setDefaultStyleEx(const unsigned int value)
		{
			m_iDefaultStyleEx = value;
			return this;
		}

		IWindow *IWindow::setDefaultState(const WINDOW_STATE value)
		{
			m_eDefaultState = value;
			return this;
		}
#pragma endregion
	}
}