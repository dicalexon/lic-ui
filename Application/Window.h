// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#pragma once

#include "..\Strings\Strings.h"
#include "Types.h"

namespace licui
{
	namespace application
	{
		class IWindow
		{
		public:
			enum EDGE
			{
				edgeNone,
				edgeBottom,
				edgeBottomLeft,
				edgeBottomRight,
				edgeLeft,
				edgeRight,
				edgeTop,
				edgeTopLeft,
				edgeTopRight
			};

			enum SYSTEM_COMMAND_TYPE
			{
				syscmdNone,
				syscmdClose,
				syscmdContextHelp,
				syscmdDefault,
				syscmdHotKey,
				syscmdHScroll,
				syscmdIsSecure,
				syscmdKeyMenu,
				syscmdMaximize,
				syscmdMinimize,
				syscmdMonitorPower,
				syscmdMouseMenu,
				syscmdMove,
				syscmdNextWindow,
				syscmdPrevWindow,
				syscmdRestore,
				syscmdScreenSave,
				syscmdSize,
				syscmdTaskList,
				syscmdVScroll
			};

			enum SCROLL_TYPE
			{
				scrollNone,
				scrollEndScroll,
				scrollLeft,
				scrollRight,
				scrollLineLeft,
				scrollLineRight,
				scrollPageLeft,
				scrollPageRight,
				scrollThumbPosition,
				scrollThumbTrack
			};

			enum CLOSE_ACTION
			{
				caNone,
				caHide,
				caFree,
				caMinimize
			};

			enum WINDOW_STATE
			{
				wsNormal,
				wsMaximized,
				wsMinimized,
				wsHidden
			};

			enum KEY
			{
				keyLButton,
				keyRButton,
				keyCancel,
				keyMButton,
				keyXButton1,
				keyXButton2,
				keyBack,
				keyTab,
				keyClear,
				keyReturn,
				keyShift,
				keyControl,
				keyMenu,
				keyPause,
				keyCapital,
				keyKana,
				keyJunja,
				keyFinal,
				keyHanja,
				keyEscape,
				keyConvert,
				keyNonConvert,
				keyAccept,
				keyModeChange,
				keySpace,
				keyPrior,
				keyNext,
				keyEnd,
				keyHome,
				keyLeft,
				keyUp,
				keyRight,
				keyDown,
				keySelect,
				keyPrint,
				keyExecute,
				keySnapshot,
				keyInsert,
				keyDelete,
				keyHelp,
				key0,
				key1,
				key2,
				key3,
				key4,
				key5,
				key6,
				key7,
				key8,
				key9,
				keyA,
				keyB,
				keyC,
				keyD,
				keyE,
				keyF,
				keyG,
				keyH,
				keyI,
				keyJ,
				keyK,
				keyL,
				keyM,
				keyN,
				keyO,
				keyP,
				keyQ,
				keyR,
				keyS,
				keyT,
				keyU,
				keyV,
				keyW,
				keyX,
				keyY,
				keyZ,
				keyLWin,
				keyRWin,
				keyApps,
				keySleep,
				keyNumpad0,
				keyNumpad1,
				keyNumpad2,
				keyNumpad3,
				keyNumpad4,
				keyNumpad5,
				keyNumpad6,
				keyNumpad7,
				keyNumpad8,
				keyNumpad9,
				keyMultiply,
				keyAdd,
				keySeparator,
				keySubtract,
				keyDecimal,
				keyDivide,
				keyF1,
				keyF2,
				keyF3,
				keyF4,
				keyF5,
				keyF6,
				keyF7,
				keyF8,
				keyF9,
				keyF10,
				keyF11,
				keyF12,
				keyF13,
				keyF14,
				keyF15,
				keyF16,
				keyF17,
				keyF18,
				keyF19,
				keyF20,
				keyF21,
				keyF22,
				keyF23,
				keyF24,
				keyNumLock,
				keyScroll,
				keyLShift,
				keyRShift,
				keyLControl,
				keyRControl,
				keyLMenu,
				keyRMenu,
				keyBrowserBack,
				keyBrowserForward,
				keyBrowserRefresh,
				keyBrowserStop,
				keyBrowserSearch,
				keyBrowserFavorites,
				keyBrowserHome,
				keyVolumeMute,
				keyVolumeDown,
				keyVolumeUp,
				keyMediaNextTrack,
				keyMediaPrevTrack,
				keyMediaStop,
				keyMediaPlayPause,
				keyLaunchMail,
				keyLaunchMediaSelect,
				keyLaunchApp1,
				keyLaunchApp2,
				keyOem1,
				keyOemPlus,
				keyOemComma,
				keyOemMinus,
				keyOemPeriod,
				keyOem2,
				keyOem3,
				keyOem4,
				keyOem5,
				keyOem6,
				keyOem7,
				keyOem8,
				keyOem102,
				keyProcessKey,
				keyPacket,
				keyAttn,
				keyCrSel,
				keyExSel,
				keyErEOF,
				keyPlay,
				keyZoom,
				keyPA1,
				keyOemClear,
				keyUnknown
			};

			typedef void(*FOnCreate)(void *param);
			typedef void(*FOnDestroy)(void *param);
			typedef void(*FOnMove)(const int x, const int y, void *param);
			typedef void(*FOnRestore)(const int width, const int height, void *param);
			typedef void(*FOnMinimize)(const int width, const int height, void *param);
			typedef void(*FOnMaximize)(const int width, const int height, void *param);
			typedef void(*FOnActivate)(const bool byclick, void *param);
			typedef void(*FOnDeactivate)(void *param);
			typedef void(*FOnSetFocus)(void *param);
			typedef void(*FOnKillFocus)(void *param);
			typedef void(*FOnEnable)(void *param);
			typedef void(*FOnDisable)(void *param);
			typedef void(*FOnPaint)(const int left, const int top, const int right, const int bottom, void *param);
			typedef void(*FOnClose)(CLOSE_ACTION &action, void *param);
			typedef bool(*FOnQueryEndSession)(void *param);
			typedef bool(*FOnQueryOpen)(void *param);
			typedef void(*FOnEndSession)(const bool ending, void *param);
			typedef void(*FOnShow)(void *param);
			typedef void(*FOnHide)(void *param);
			typedef void(*FOnDeviceModeChange)(void *param);
			typedef void(*FOnActivateApp)(void *param);
			typedef void(*FOnDeactivateApp)(void *param);
			typedef void(*FOnTimeChange)(void *param);
			typedef bool(*FOnInputLanguageChangeRequest)(void *param);
			typedef void(*FOnInputLanguageChange)(void *param);
			typedef bool(*FOnContextMenu)(const int x, const int y, void *param);
			typedef void(*FOnDisplayChange)(const int width, const int height, void *param);
			typedef void(*FOnKeyDown)(const KEY key, void *param);
			typedef void(*FOnKeyUp)(const KEY key, void *param);
			typedef void(*FOnChar)(const wchar_t chr, void *param);
			typedef void(*FOnDeadChar)(const wchar_t chr, void *param);
			typedef void(*FOnSysKeyDown)(const KEY key, void *param);
			typedef void(*FOnSysKeyUp)(const KEY key, void *param);
			typedef void(*FOnSysChar)(const wchar_t chr, void *param);
			typedef void(*FOnSysDeadChar)(const wchar_t chr, void *param);
			typedef bool(*FOnInitDialog)(void *param);
			typedef void(*FOnSysCommand)(const SYSTEM_COMMAND_TYPE type, const int x, const int y, void *param);
			typedef void(*FOnHScroll)(const SCROLL_TYPE type, const int pos, void *param);
			typedef void(*FOnVScroll)(const SCROLL_TYPE type, const int pos, void *param);
			typedef void(*FOnGestureZoom)(const int x, const int y, void *param);
			typedef void(*FOnGesturePan)(const int x, const int y, void *param);
			typedef void(*FOnGestureRotate)(const int x, const int y, void *param);
			typedef void(*FOnGestureTwoFingerTap)(const int x, const int y, void *param);
			typedef void(*FOnGesturePressAndTap)(const int x, const int y, void *param);
			typedef void(*FOnGestureNotify)(void *param);
			typedef void(*FOnEnterIdleDialog)(void *param);
			typedef void(*FOnEnterIdleMenu)(void *param);
			typedef void(*FOnMouseMove)(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift, void *param);
			typedef void(*FOnLeftMouseButtonDown)(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift, void *param);
			typedef void(*FOnLeftMouseButtonUp)(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift, void *param);
			typedef void(*FOnLeftMouseButtonDoubleClick)(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift, void *param);
			typedef void(*FOnRightMouseButtonDown)(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift, void *param);
			typedef void(*FOnRightMouseButtonUp)(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift, void *param);
			typedef void(*FOnRightMouseButtonDoubleClick)(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift, void *param);
			typedef void(*FOnMiddleMouseButtonDown)(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift, void *param);
			typedef void(*FOnMiddleMouseButtonUp)(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift, void *param);
			typedef void(*FOnMiddleMouseButtonDoubleClick)(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift, void *param);
			typedef void(*FOnMouseVerticalWheel)(const int x, const int y, const int delta, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift, void *param);
			typedef void(*FOnMouseHorizontalWheel)(const int x, const int y, const int delta, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift, void *param);
			typedef void(*FOnResizing)(const EDGE edge, const int left, const int top, const int right, const int bottom, void *param);
			typedef void(*FOnLoseCapture)(void *param);
			typedef void(*FOnMoving)(const int left, const int top, const int right, const int bottom, void *param);
			typedef void(*FOnEnterSizeMove)(void *param);
			typedef void(*FOnExitSizeMove)(void *param);
			typedef void(*FOnMouseHover)(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift, void *param);
			typedef void(*FOnMouseLeave)(void *param);
			typedef void(*FOnHotKey)(const bool is_desktop, const KEY key, const bool alt, const bool ctrl, const bool shift, const bool win, void *param);
			typedef void(*FOnThemeChanged)(void *param);
			typedef void(*FOnClipboardUpdate)(void *param);
			typedef void(*FOnTimer)(const unsigned int id, void *param);
			typedef void(*FOnNonClientMouseMove)(const int x, const int y, void *param);
			typedef void(*FOnNonClientLeftMouseButtonDown)(const int x, const int y, void *param);
			typedef void(*FOnNonClientLeftMouseButtonUp)(const int x, const int y, void *param);
			typedef void(*FOnNonClientLeftMouseButtonDoubleClick)(const int x, const int y, void *param);
			typedef void(*FOnNonClientRightMouseButtonDown)(const int x, const int y, void *param);
			typedef void(*FOnNonClientRightMouseButtonUp)(const int x, const int y, void *param);
			typedef void(*FOnNonClientRightMouseButtonDoubleClick)(const int x, const int y, void *param);
			typedef void(*FOnNonClientMiddleMouseButtonDown)(const int x, const int y, void *param);
			typedef void(*FOnNonClientMiddleMouseButtonUp)(const int x, const int y, void *param);
			typedef void(*FOnNonClientMiddleMouseButtonDoubleClick)(const int x, const int y, void *param);
			typedef void(*FOnEnterMenuLoop)(const bool track_popup_menu_used, void *param);
			typedef void(*FOnExitMenuLoop)(const bool is_shortcut, void *param);
			typedef void(*FOnNonClientMouseHover)(const int x, const int y, void *param);
			typedef void(*FOnNonClientMouseLeave)(void *param);
		protected:
			void *m_pCallbackParam;
			FOnCreate m_fOnCreate;
			FOnDestroy m_fOnDestroy;
			FOnMove m_fOnMove;
			FOnRestore m_fOnRestore;
			FOnMinimize m_fOnMinimize;
			FOnMaximize m_fOnMaximize;
			FOnActivate m_fOnActivate;
			FOnDeactivate m_fOnDeactivate;
			FOnSetFocus m_fOnSetFocus;
			FOnKillFocus m_fOnKillFocus;
			FOnEnable m_fOnEnable;
			FOnDisable m_fOnDisable;
			FOnPaint m_fOnPaint;
			FOnClose m_fOnClose;
			FOnQueryEndSession m_fOnQueryEndSession;
			FOnQueryOpen m_fOnQueryOpen;
			FOnEndSession m_fOnEndSession;
			FOnShow m_fOnShow;
			FOnHide m_fOnHide;
			FOnDeviceModeChange m_fOnDeviceModeChange;
			FOnActivateApp m_fOnActivateApp;
			FOnDeactivateApp m_fOnDeactivateApp;
			FOnTimeChange m_fOnTimeChange;
			FOnInputLanguageChangeRequest m_fOnInputLanguageChangeRequest;
			FOnInputLanguageChange m_fOnInputLanguageChange;
			FOnContextMenu m_fOnContextMenu;
			FOnDisplayChange m_fOnDisplayChange;
			FOnKeyDown m_fOnKeyDown;
			FOnKeyUp m_fOnKeyUp;
			FOnChar m_fOnChar;
			FOnDeadChar m_fOnDeadChar;
			FOnSysKeyDown m_fOnSysKeyDown;
			FOnSysKeyUp m_fOnSysKeyUp;
			FOnSysChar m_fOnSysChar;
			FOnSysDeadChar m_fOnSysDeadChar;
			FOnInitDialog m_fOnInitDialog;
			FOnSysCommand m_fOnSysCommand;
			FOnHScroll m_fOnHScroll;
			FOnVScroll m_fOnVScroll;
			FOnGestureZoom m_fOnGestureZoom;
			FOnGesturePan m_fOnGesturePan;
			FOnGestureRotate m_fOnGestureRotate;
			FOnGestureTwoFingerTap m_fOnGestureTwoFingerTap;
			FOnGesturePressAndTap m_fOnGesturePressAndTap;
			FOnGestureNotify m_fOnGestureNotify;
			FOnEnterIdleDialog m_fOnEnterIdleDialog;
			FOnEnterIdleMenu m_fOnEnterIdleMenu;
			FOnMouseMove m_fOnMouseMove;
			FOnLeftMouseButtonDown m_fOnLeftMouseButtonDown;
			FOnLeftMouseButtonUp m_fOnLeftMouseButtonUp;
			FOnLeftMouseButtonDoubleClick m_fOnLeftMouseButtonDoubleClick;
			FOnRightMouseButtonDown m_fOnRightMouseButtonDown;
			FOnRightMouseButtonUp m_fOnRightMouseButtonUp;
			FOnRightMouseButtonDoubleClick m_fOnRightMouseButtonDoubleClick;
			FOnMiddleMouseButtonDown m_fOnMiddleMouseButtonDown;
			FOnMiddleMouseButtonUp m_fOnMiddleMouseButtonUp;
			FOnMiddleMouseButtonDoubleClick m_fOnMiddleMouseButtonDoubleClick;
			FOnMouseVerticalWheel m_fOnMouseVerticalWheel;
			FOnMouseHorizontalWheel m_fOnMouseHorizontalWheel;
			FOnResizing m_fOnResizing;
			FOnLoseCapture m_fOnLoseCapture;
			FOnMoving m_fOnMoving;
			FOnEnterSizeMove m_fOnEnterSizeMove;
			FOnExitSizeMove m_fOnExitSizeMove;
			FOnMouseHover m_fOnMouseHover;
			FOnMouseLeave m_fOnMouseLeave;
			FOnHotKey m_fOnHotKey;
			FOnThemeChanged m_fOnThemeChanged;
			FOnClipboardUpdate m_fOnClipboardUpdate;
			FOnTimer m_fOnTimer;
			FOnNonClientMouseMove m_fOnNonClientMouseMove;
			FOnNonClientLeftMouseButtonDown m_fOnNonClientLeftMouseButtonDown;
			FOnNonClientLeftMouseButtonUp m_fOnNonClientLeftMouseButtonUp;
			FOnNonClientLeftMouseButtonDoubleClick m_fOnNonClientLeftMouseButtonDoubleClick;
			FOnNonClientRightMouseButtonDown m_fOnNonClientRightMouseButtonDown;
			FOnNonClientRightMouseButtonUp m_fOnNonClientRightMouseButtonUp;
			FOnNonClientRightMouseButtonDoubleClick m_fOnNonClientRightMouseButtonDoubleClick;
			FOnNonClientMiddleMouseButtonDown m_fOnNonClientMiddleMouseButtonDown;
			FOnNonClientMiddleMouseButtonUp m_fOnNonClientMiddleMouseButtonUp;
			FOnNonClientMiddleMouseButtonDoubleClick m_fOnNonClientMiddleMouseButtonDoubleClick;
			FOnEnterMenuLoop m_fOnEnterMenuLoop;
			FOnExitMenuLoop m_fOnExitMenuLoop;
			FOnNonClientMouseHover m_fOnNonClientMouseHover;
			FOnNonClientMouseLeave m_fOnNonClientMouseLeave;

			String m_sDefaultClass;
			String m_sDefaultCaption;
			int m_iDefaultX;
			int m_iDefaultY;
			int m_iDefaultWidth;
			int m_iDefaultHeight;
			unsigned int m_iDefaultStyle;
			unsigned int m_iDefaultStyleEx;
			WINDOW_STATE m_eDefaultState;
		public:
			void *getCallbackParam() const;
			FOnCreate getOnCreate() const;
			FOnDestroy getOnDestroy() const;
			FOnMove getOnMove() const;
			FOnRestore getOnRestore() const;
			FOnMinimize getOnMinimize() const;
			FOnMaximize getOnMaximize() const;
			FOnActivate getOnActivate() const;
			FOnDeactivate getOnDeactivate() const;
			FOnSetFocus getOnSetFocus() const;
			FOnKillFocus getOnKillFocus() const;
			FOnEnable getOnEnable() const;
			FOnDisable getOnDisable() const;
			FOnPaint getOnPaint() const;
			FOnClose getOnClose() const;
			FOnQueryEndSession getOnQueryEndSession() const;
			FOnQueryOpen getOnQueryOpen() const;
			FOnEndSession getOnEndSession() const;
			FOnShow getOnShow() const;
			FOnHide getOnHide() const;
			FOnDeviceModeChange getOnDeviceModeChange() const;
			FOnActivateApp getOnActivateApp() const;
			FOnDeactivateApp getOnDeactivateApp() const;
			FOnTimeChange getOnTimeChange() const;
			FOnInputLanguageChangeRequest getOnInputLanguageChangeRequest() const;
			FOnInputLanguageChange getOnInputLanguageChange() const;
			FOnContextMenu getOnContextMenu() const;
			FOnDisplayChange getOnDisplayChange() const;
			FOnKeyDown getOnKeyDown() const;
			FOnKeyUp getOnKeyUp() const;
			FOnChar getOnChar() const;
			FOnDeadChar getOnDeadChar() const;
			FOnSysKeyDown getOnSysKeyDown() const;
			FOnSysKeyUp getOnSysKeyUp() const;
			FOnSysChar getOnSysChar() const;
			FOnSysDeadChar getOnSysDeadChar() const;
			FOnInitDialog getOnInitDialog() const;
			FOnSysCommand getOnSysCommand() const;
			FOnHScroll getOnHScroll() const;
			FOnVScroll getOnVScroll() const;
			FOnGestureZoom getOnGestureZoom() const;
			FOnGesturePan getOnGesturePan() const;
			FOnGestureRotate getOnGestureRotate() const;
			FOnGestureTwoFingerTap getOnGestureTwoFingerTap() const;
			FOnGesturePressAndTap getOnGesturePressAndTap() const;
			FOnGestureNotify getOnGestureNotify() const;
			FOnEnterIdleDialog getOnEnterIdleDialog() const;
			FOnEnterIdleMenu getOnEnterIdleMenu() const;
			FOnMouseMove getOnMouseMove() const;
			FOnLeftMouseButtonDown getOnLeftMouseButtonDown() const;
			FOnLeftMouseButtonUp getOnLeftMouseButtonUp() const;
			FOnLeftMouseButtonDoubleClick getOnLeftMouseButtonDoubleClick() const;
			FOnRightMouseButtonDown getOnRightMouseButtonDown() const;
			FOnRightMouseButtonUp getOnRightMouseButtonUp() const;
			FOnRightMouseButtonDoubleClick getOnRightMouseButtonDoubleClick() const;
			FOnMiddleMouseButtonDown getOnMiddleMouseButtonDown() const;
			FOnMiddleMouseButtonUp getOnMiddleMouseButtonUp() const;
			FOnMiddleMouseButtonDoubleClick getOnMiddleMouseButtonDoubleClick() const;
			FOnMouseVerticalWheel getOnMouseVerticalWheel() const;
			FOnMouseHorizontalWheel getOnMouseHorizontalWheel() const;
			FOnResizing getOnResizing() const;
			FOnLoseCapture getOnLoseCapture() const;
			FOnMoving getOnMoving() const;
			FOnEnterSizeMove getOnEnterSizeMove() const;
			FOnExitSizeMove getOnExitSizeMove() const;
			FOnMouseHover getOnMouseHover() const;
			FOnMouseLeave getOnMouseLeave() const;
			FOnHotKey getOnHotKey() const;
			FOnThemeChanged getOnThemeChanged() const;
			FOnClipboardUpdate getOnClipboardUpdate() const;
			FOnTimer getOnTimer() const;
			FOnNonClientMouseMove getOnNonClientMouseMove() const;
			FOnNonClientLeftMouseButtonDown getOnNonClientLeftMouseButtonDown() const;
			FOnNonClientLeftMouseButtonUp getOnNonClientLeftMouseButtonUp() const;
			FOnNonClientLeftMouseButtonDoubleClick getOnNonClientLeftMouseButtonDoubleClick() const;
			FOnNonClientRightMouseButtonDown getOnNonClientRightMouseButtonDown() const;
			FOnNonClientRightMouseButtonUp getOnNonClientRightMouseButtonUp() const;
			FOnNonClientRightMouseButtonDoubleClick getOnNonClientRightMouseButtonDoubleClick() const;
			FOnNonClientMiddleMouseButtonDown getOnNonClientMiddleMouseButtonDown() const;
			FOnNonClientMiddleMouseButtonUp getOnNonClientMiddleMouseButtonUp() const;
			FOnNonClientMiddleMouseButtonDoubleClick getOnNonClientMiddleMouseButtonDoubleClick() const;
			FOnEnterMenuLoop getOnEnterMenuLoop() const;
			FOnExitMenuLoop getOnExitMenuLoop() const;
			FOnNonClientMouseHover getOnNonClientMouseHover() const;
			FOnNonClientMouseLeave getOnNonClientMouseLeave() const;

			IWindow *setCallbackParam(void *value);
			IWindow *setOnCreate(const FOnCreate value);
			IWindow *setOnDestroy(const FOnDestroy value);
			IWindow *setOnMove(const FOnMove value);
			IWindow *setOnRestore(const FOnRestore value);
			IWindow *setOnMinimize(const FOnMinimize value);
			IWindow *setOnMaximize(const FOnMaximize value);
			IWindow *setOnActivate(const FOnActivate value);
			IWindow *setOnDeactivate(const FOnDeactivate value);
			IWindow *setOnSetFocus(const FOnSetFocus value);
			IWindow *setOnKillFocus(const FOnKillFocus value);
			IWindow *setOnEnable(const FOnEnable value);
			IWindow *setOnDisable(const FOnDisable value);
			IWindow *setOnPaint(const FOnPaint value);
			IWindow *setOnClose(const FOnClose value);
			IWindow *setOnQueryEndSession(const FOnQueryEndSession value);
			IWindow *setOnQueryOpen(const FOnQueryOpen value);
			IWindow *setOnEndSession(const FOnEndSession value);
			IWindow *setOnShow(const FOnShow value);
			IWindow *setOnHide(const FOnHide value);
			IWindow *setOnDeviceModeChange(const FOnDeviceModeChange value);
			IWindow *setOnActivateApp(const FOnActivateApp value);
			IWindow *setOnDeactivateApp(const FOnDeactivateApp value);
			IWindow *setOnTimeChange(const FOnTimeChange value);
			IWindow *setOnInputLanguageChangeRequest(const FOnInputLanguageChangeRequest value);
			IWindow *setOnInputLanguageChange(const FOnInputLanguageChange value);
			IWindow *setOnContextMenu(const FOnContextMenu value);
			IWindow *setOnDisplayChange(const FOnDisplayChange value);
			IWindow *setOnKeyDown(const FOnKeyDown value);
			IWindow *setOnKeyUp(const FOnKeyUp value);
			IWindow *setOnChar(const FOnChar value);
			IWindow *setOnDeadChar(const FOnDeadChar value);
			IWindow *setOnSysKeyDown(const FOnSysKeyDown value);
			IWindow *setOnSysKeyUp(const FOnSysKeyUp value);
			IWindow *setOnSysChar(const FOnSysChar value);
			IWindow *setOnSysDeadChar(const FOnSysDeadChar value);
			IWindow *setOnInitDialog(const FOnInitDialog value);
			IWindow *setOnSysCommand(const FOnSysCommand value);
			IWindow *setOnHScroll(const FOnHScroll value);
			IWindow *setOnVScroll(const FOnVScroll value);
			IWindow *setOnGestureZoom(const FOnGestureZoom value);
			IWindow *setOnGesturePan(const FOnGesturePan value);
			IWindow *setOnGestureRotate(const FOnGestureRotate value);
			IWindow *setOnGestureTwoFingerTap(const FOnGestureTwoFingerTap value);
			IWindow *setOnGesturePressAndTap(const FOnGesturePressAndTap value);
			IWindow *setOnGestureNotify(const FOnGestureNotify value);
			IWindow *setOnEnterIdleDialog(const FOnEnterIdleDialog value);
			IWindow *setOnEnterIdleMenu(const FOnEnterIdleMenu value);
			IWindow *setOnMouseMove(const FOnMouseMove value);
			IWindow *setOnLeftMouseButtonDown(const FOnLeftMouseButtonDown value);
			IWindow *setOnLeftMouseButtonUp(const FOnLeftMouseButtonUp value);
			IWindow *setOnLeftMouseButtonDoubleClick(const FOnLeftMouseButtonDoubleClick value);
			IWindow *setOnRightMouseButtonDown(const FOnRightMouseButtonDown value);
			IWindow *setOnRightMouseButtonUp(const FOnRightMouseButtonUp value);
			IWindow *setOnRightMouseButtonDoubleClick(const FOnRightMouseButtonDoubleClick value);
			IWindow *setOnMiddleMouseButtonDown(const FOnMiddleMouseButtonDown value);
			IWindow *setOnMiddleMouseButtonUp(const FOnMiddleMouseButtonUp value);
			IWindow *setOnMiddleMouseButtonDoubleClick(const FOnMiddleMouseButtonDoubleClick value);
			IWindow *setOnMouseVerticalWheel(const FOnMouseVerticalWheel value);
			IWindow *setOnMouseHorizontalWheel(const FOnMouseHorizontalWheel value);
			IWindow *setOnResizing(const FOnResizing value);
			IWindow *setOnLoseCapture(const FOnLoseCapture value);
			IWindow *setOnMoving(const FOnMoving value);
			IWindow *setOnEnterSizeMove(const FOnEnterSizeMove value);
			IWindow *setOnExitSizeMove(const FOnExitSizeMove value);
			IWindow *setOnMouseHover(const FOnMouseHover value);
			IWindow *setOnMouseLeave(const FOnMouseLeave value);
			IWindow *setOnHotKey(const FOnHotKey value);
			IWindow *setOnThemeChanged(const FOnThemeChanged value);
			IWindow *setOnClipboardUpdate(const FOnClipboardUpdate value);
			IWindow *setOnTimer(const FOnTimer value);
			IWindow *setOnNonClientMouseMove(const FOnNonClientMouseMove value);
			IWindow *setOnNonClientLeftMouseButtonDown(const FOnNonClientLeftMouseButtonDown value);
			IWindow *setOnNonClientLeftMouseButtonUp(const FOnNonClientLeftMouseButtonUp value);
			IWindow *setOnNonClientLeftMouseButtonDoubleClick(const FOnNonClientLeftMouseButtonDoubleClick value);
			IWindow *setOnNonClientRightMouseButtonDown(const FOnNonClientRightMouseButtonDown value);
			IWindow *setOnNonClientRightMouseButtonUp(const FOnNonClientRightMouseButtonUp value);
			IWindow *setOnNonClientRightMouseButtonDoubleClick(const FOnNonClientRightMouseButtonDoubleClick value);
			IWindow *setOnNonClientMiddleMouseButtonDown(const FOnNonClientMiddleMouseButtonDown value);
			IWindow *setOnNonClientMiddleMouseButtonUp(const FOnNonClientMiddleMouseButtonUp value);
			IWindow *setOnNonClientMiddleMouseButtonDoubleClick(const FOnNonClientMiddleMouseButtonDoubleClick value);
			IWindow *setOnEnterMenuLoop(const FOnEnterMenuLoop value);
			IWindow *setOnExitMenuLoop(const FOnExitMenuLoop value);
			IWindow *setOnNonClientMouseHover(const FOnNonClientMouseHover value);
			IWindow *setOnNonClientMouseLeave(const FOnNonClientMouseLeave value);

			virtual String getCaption() const = 0;
			virtual APP_RECT getRect() const = 0;
			virtual APP_RECT getClientRect() const = 0;
			virtual APP_POINT getSize() const = 0;
			virtual APP_POINT getPosition() const = 0;
			virtual int getLeft() const = 0;
			virtual int getTop() const = 0;
			virtual int getWidth() const = 0;
			virtual int getHeight() const = 0;
			virtual bool getVisible() const = 0;
			virtual bool getEnabled() const = 0;
			virtual int getClientWidth() const = 0;
			virtual int getClientHeight() const = 0;
			virtual bool getIsCreated() const = 0;
			virtual bool getCursorPosition(int &x, int &y) const = 0;
			virtual void *getHandle() const = 0;
			virtual void getControlKeys(bool &ctrl, bool &shift, bool &alt) const = 0;
			virtual bool getKeyIsDown(KEY key) = 0;
			virtual bool getKeyIsToggled(KEY key) = 0;
			virtual WINDOW_STATE getWindowState() = 0;
			virtual String getDefaultClass() const;
			virtual String getDefaultCaption() const;
			virtual int getDefaultX() const;
			virtual int getDefaultY() const;
			virtual int getDefaultWidth() const;
			virtual int getDefaultHeight() const;
			virtual unsigned int getDefaultStyle() const;
			virtual unsigned int getDefaultStyleEx() const;
			virtual WINDOW_STATE getDefaultState() const;

			virtual IWindow *setCaption(const String &value) const = 0;
			virtual IWindow *setRect(const APP_RECT &value) const = 0;
			virtual IWindow *setSize(const APP_POINT &value) const = 0;
			virtual IWindow *setPosition(const APP_POINT &value) const = 0;
			virtual IWindow *setLeft(const int value) const = 0;
			virtual IWindow *setTop(const int value) const = 0;
			virtual IWindow *setWidth(const int value) const = 0;
			virtual IWindow *setHeight(const int value) const = 0;
			virtual IWindow *setVisible(const bool value) const = 0;
			virtual IWindow *setEnabled(const bool value) const = 0;
			virtual IWindow *setCursor(const CURSOR_TYPE value) = 0;
			virtual IWindow *setDefaultClass(const String &value);
			virtual IWindow *setDefaultCaption(const String &value);
			virtual IWindow *setDefaultX(const int value);
			virtual IWindow *setDefaultY(const int value);
			virtual IWindow *setDefaultWidth(const int value);
			virtual IWindow *setDefaultHeight(const int value);
			virtual IWindow *setDefaultStyle(const unsigned int value);
			virtual IWindow *setDefaultStyleEx(const unsigned int value);
			virtual IWindow *setDefaultState(const WINDOW_STATE value);

			IWindow();
			virtual ~IWindow() {};

			virtual IWindow *Show() const = 0;
			virtual IWindow *Hide() const = 0;
			virtual bool Create() = 0;
			virtual unsigned int CreateTimer(unsigned int id, unsigned int interval) = 0;
			virtual void DeleteTimer(unsigned int id) = 0;
			virtual void StartTrackMouseLeave() {};
			virtual bool CaptureMouse() = 0;
			virtual void ReleaseMouseCapture() = 0;
			virtual APP_POINT ClientToScreen(const APP_POINT &value) = 0;
			virtual APP_POINT ScreenToClient(const APP_POINT &value) = 0;
			virtual void Maximize() = 0;
			virtual void Minimize() = 0;
			virtual void Restore() = 0;
			virtual bool CreateCaret(const int width, const int height) = 0;
			virtual bool DestroyCaret() = 0;
			virtual bool ShowCaret() = 0;
			virtual bool HideCaret() = 0;
			virtual bool SetCaretPosition(const int x, const int y) = 0;
			virtual bool IsCaretVisible() = 0;
			virtual bool CopyStringToClipboard(const String &str) = 0;
			virtual String CopyStringFromClipboard() = 0;
		};
	}
}