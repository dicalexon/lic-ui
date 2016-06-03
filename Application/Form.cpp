// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#include <algorithm>
#include "Form.h"
#include "Presenter.h"
#include "Component.h"
#include "Control.h"
#include "Style.h"
#include "StyleFont.h"
#include "ImageManager.h"

namespace licui
{
	namespace application
	{
	#pragma region SHORTCUT
		String CForm::SHORTCUT::GetKeyName(const IWindow::KEY key)
		{
			switch (key)
			{
			case IWindow::keyLButton: return L"Left Mouse Button";
			case IWindow::keyRButton: return L"Right Mouse Button";
			case IWindow::keyCancel: return L"Cancel";
			case IWindow::keyMButton: return L"Middle Mouse Button";
			case IWindow::keyXButton1: return L"X1 Mouse Button";
			case IWindow::keyXButton2: return L"X2 Mouse Button";
			case IWindow::keyBack: return L"Backspace";
			case IWindow::keyTab: return L"Tab";
			case IWindow::keyClear: return L"Clear";
			case IWindow::keyReturn: return L"Enter";
			case IWindow::keyShift: return L"Shift";
			case IWindow::keyControl: return L"Ctrl";
			case IWindow::keyMenu: return L"Alt";
			case IWindow::keyPause: return L"Pause";
			case IWindow::keyCapital: return L"CapsLock";
			case IWindow::keyKana: return L"Kana";
			case IWindow::keyJunja: return L"Junja";
			case IWindow::keyFinal: return L"Final";
			case IWindow::keyHanja: return L"Hanja";
			case IWindow::keyEscape: return L"Esc";
			case IWindow::keyConvert: return L"Convert";
			case IWindow::keyNonConvert: return L"Non Convert";
			case IWindow::keyAccept: return L"Accept";
			case IWindow::keyModeChange: return L"Change Mode";
			case IWindow::keySpace: return L"Space";
			case IWindow::keyPrior: return L"PageUp";
			case IWindow::keyNext: return L"PageDown";
			case IWindow::keyEnd: return L"End";
			case IWindow::keyHome: return L"Home";
			case IWindow::keyLeft: return L"Left";
			case IWindow::keyUp: return L"Up";
			case IWindow::keyRight: return L"Right";
			case IWindow::keyDown: return L"Down";
			case IWindow::keySelect: return L"Select";
			case IWindow::keyPrint: return L"Print";
			case IWindow::keyExecute: return L"Execute";
			case IWindow::keySnapshot: return L"PrtScn";
			case IWindow::keyInsert: return L"Ins";
			case IWindow::keyDelete: return L"Del";
			case IWindow::keyHelp: return L"Help";
			case IWindow::key0: return L"0";
			case IWindow::key1: return L"1";
			case IWindow::key2: return L"2";
			case IWindow::key3: return L"3";
			case IWindow::key4: return L"4";
			case IWindow::key5: return L"5";
			case IWindow::key6: return L"6";
			case IWindow::key7: return L"7";
			case IWindow::key8: return L"8";
			case IWindow::key9: return L"9";
			case IWindow::keyA: return L"A";
			case IWindow::keyB: return L"B";
			case IWindow::keyC: return L"C";
			case IWindow::keyD: return L"D";
			case IWindow::keyE: return L"E";
			case IWindow::keyF: return L"F";
			case IWindow::keyG: return L"G";
			case IWindow::keyH: return L"H";
			case IWindow::keyI: return L"I";
			case IWindow::keyJ: return L"J";
			case IWindow::keyK: return L"K";
			case IWindow::keyL: return L"L";
			case IWindow::keyM: return L"M";
			case IWindow::keyN: return L"N";
			case IWindow::keyO: return L"O";
			case IWindow::keyP: return L"P";
			case IWindow::keyQ: return L"Q";
			case IWindow::keyR: return L"R";
			case IWindow::keyS: return L"S";
			case IWindow::keyT: return L"T";
			case IWindow::keyU: return L"U";
			case IWindow::keyV: return L"V";
			case IWindow::keyW: return L"W";
			case IWindow::keyX: return L"X";
			case IWindow::keyY: return L"Y";
			case IWindow::keyZ: return L"Z";
			case IWindow::keyLWin: return L"Left Win";
			case IWindow::keyRWin: return L"Right Win";
			case IWindow::keyApps: return L"Apps";
			case IWindow::keySleep: return L"Sleep";
			case IWindow::keyNumpad0: return L"Num0";
			case IWindow::keyNumpad1: return L"Num1";
			case IWindow::keyNumpad2: return L"Num2";
			case IWindow::keyNumpad3: return L"Num3";
			case IWindow::keyNumpad4: return L"Num4";
			case IWindow::keyNumpad5: return L"Num5";
			case IWindow::keyNumpad6: return L"Num6";
			case IWindow::keyNumpad7: return L"Num7";
			case IWindow::keyNumpad8: return L"Num8";
			case IWindow::keyNumpad9: return L"Num9";
			case IWindow::keyMultiply: return L"Num*";
			case IWindow::keyAdd: return L"Num+";
			case IWindow::keySeparator: return L"Num Enter";
			case IWindow::keySubtract: return L"Num-";
			case IWindow::keyDecimal: return L"Num.";
			case IWindow::keyDivide: return L"Num/";
			case IWindow::keyF1: return L"F1";
			case IWindow::keyF2: return L"F2";
			case IWindow::keyF3: return L"F3";
			case IWindow::keyF4: return L"F4";
			case IWindow::keyF5: return L"F5";
			case IWindow::keyF6: return L"F6";
			case IWindow::keyF7: return L"F7";
			case IWindow::keyF8: return L"F8";
			case IWindow::keyF9: return L"F9";
			case IWindow::keyF10: return L"F10";
			case IWindow::keyF11: return L"F11";
			case IWindow::keyF12: return L"F12";
			case IWindow::keyF13: return L"F13";
			case IWindow::keyF14: return L"F14";
			case IWindow::keyF15: return L"F15";
			case IWindow::keyF16: return L"F16";
			case IWindow::keyF17: return L"F17";
			case IWindow::keyF18: return L"F18";
			case IWindow::keyF19: return L"F19";
			case IWindow::keyF20: return L"F20";
			case IWindow::keyF21: return L"F21";
			case IWindow::keyF22: return L"F22";
			case IWindow::keyF23: return L"F23";
			case IWindow::keyF24: return L"F24";
			case IWindow::keyNumLock: return L"NumLock";
			case IWindow::keyScroll: return L"ScrollLock";
			case IWindow::keyLShift: return L"Left Shift";
			case IWindow::keyRShift: return L"Right Shift";
			case IWindow::keyLControl: return L"Left Ctrl";
			case IWindow::keyRControl: return L"Right Ctrl";
			case IWindow::keyLMenu: return L"Left Alt";
			case IWindow::keyRMenu: return L"Right Alt";
			case IWindow::keyBrowserBack: return L"Browser Back";
			case IWindow::keyBrowserForward: return L"Browser Forward";
			case IWindow::keyBrowserRefresh: return L"Browser Refresh";
			case IWindow::keyBrowserStop: return L"Browser Stop";
			case IWindow::keyBrowserSearch: return L"Browser Search";
			case IWindow::keyBrowserFavorites: return L"Browser Favorites";
			case IWindow::keyBrowserHome: return L"Browser Home";
			case IWindow::keyVolumeMute: return L"Volume Mute";
			case IWindow::keyVolumeDown: return L"Volume Down";
			case IWindow::keyVolumeUp: return L"Volume Up";
			case IWindow::keyMediaNextTrack: return L"Next Media Track";
			case IWindow::keyMediaPrevTrack: return L"Prev Media Track";
			case IWindow::keyMediaStop: return L"Media Stop";
			case IWindow::keyMediaPlayPause: return L"Media Play/Pause";
			case IWindow::keyLaunchMail: return L"Launch Mail";
			case IWindow::keyLaunchMediaSelect: return L"Launch Media Select";
			case IWindow::keyLaunchApp1: return L"Launch App1";
			case IWindow::keyLaunchApp2: return L"Launch App2";
			case IWindow::keyOem1: return L";";
			case IWindow::keyOemPlus: return L"+";
			case IWindow::keyOemComma: return L",";
			case IWindow::keyOemMinus: return L"-";
			case IWindow::keyOemPeriod: return L".";
			case IWindow::keyOem2: return L"/";
			case IWindow::keyOem3: return L"~";
			case IWindow::keyOem4: return L"[";
			case IWindow::keyOem5: return L"\\";
			case IWindow::keyOem6: return L"]";
			case IWindow::keyOem7: return L"'";
			case IWindow::keyOem8: return L"Oem8";
			case IWindow::keyOem102: return L"Oem102";
			case IWindow::keyProcessKey: return L"Process";
			case IWindow::keyPacket: return L"Packet";
			case IWindow::keyAttn: return L"Attn";
			case IWindow::keyCrSel: return L"CrSel";
			case IWindow::keyExSel: return L"ExSel";
			case IWindow::keyErEOF: return L"ErEOF";
			case IWindow::keyPlay: return L"Play";
			case IWindow::keyZoom: return L"Zoom";
			case IWindow::keyPA1: return L"PA1";
			case IWindow::keyOemClear: return L"Clear";
			}
			return L"";
		}
	#pragma endregion

	#pragma region Construction/Destruction/Initialization
		CForm::CForm() :
			m_sClassName{ L"CForm" },
			m_pWindow{ nullptr },
			m_pPresenter{ nullptr },
			m_pFont{ nullptr },
			m_pStyle{ nullptr },
			m_bIsComponentsSorted{ true },
			m_bIsControlsSorted{ true },
			m_pActiveControl{ nullptr },
			m_pOldActiveControl{ nullptr },
			m_pCaptureKeyboardControl{ nullptr },
			m_pCaptureMouseControl{ nullptr },
			m_pHoveredControl{ nullptr },
			m_bIsTrackingMouseLeave{ false },
			m_bIsFontChanging{ false },
			m_bIsFontSizeChanged{ false },
			m_bIsFontStyleChanged{ false },
			m_sBackgroundColor{ 240, 240, 240, 255 },
			m_eCursor{ ctArrow },
			m_bSpecialKeyProcessed{ false }
		{
			m_pControlForSearch = new CControl();
			m_pImageManager = new CImageManager(*this);
		}

		CForm::~CForm()
		{
			LockRepaint();
			m_aCaptureMouseControls.clear();
			m_aCaptureKeyboardControls.clear();
			DeleteComponents();
			DeleteControls();
			delete m_pControlForSearch;
			delete m_pImageManager;
			if (m_pPresenter)
				delete m_pPresenter;
			if (m_pWindow)
				delete m_pWindow;
		}

		bool CForm::Initialize(IWindow *window, IPresenter *presenter)
		{
			m_pWindow = window;
			m_pPresenter = presenter;
			// Check all required components exists
			if (!m_pWindow || !m_pPresenter)
				return false;
			if (!InitializeWindow())
				return false;
			m_pPresenter->setWindow(m_pWindow);
			if (!InitializeFont())
				return false;
			return true;
		}

		bool CForm::InitializeWindow()
		{
			// Set window callbacks
			m_pWindow
				->setCallbackParam(this)
				->setOnCreate(WindowOnCreate)
				->setOnDestroy(WindowOnDestroy)
				->setOnMove(WindowOnMove)
				->setOnRestore(WindowOnRestore)
				->setOnMinimize(WindowOnMinimize)
				->setOnMaximize(WindowOnMaximize)
				->setOnActivate(WindowOnActivate)
				->setOnDeactivate(WindowOnDeactivate)
				->setOnSetFocus(WindowOnSetFocus)
				->setOnKillFocus(WindowOnKillFocus)
				->setOnEnable(WindowOnEnable)
				->setOnDisable(WindowOnDisable)
				->setOnPaint(WindowOnPaint)
				->setOnClose(WindowOnClose)
				->setOnQueryEndSession(WindowOnQueryEndSession)
				->setOnQueryOpen(WindowOnQueryOpen)
				->setOnEndSession(WindowOnEndSession)
				->setOnShow(WindowOnShow)
				->setOnHide(WindowOnHide)
				->setOnDeviceModeChange(WindowOnDeviceModeChange)
				->setOnActivateApp(WindowOnActivateApp)
				->setOnDeactivateApp(WindowOnDeactivateApp)
				->setOnTimeChange(WindowOnTimeChange)
				->setOnInputLanguageChangeRequest(WindowOnInputLanguageChangeRequest)
				->setOnInputLanguageChange(WindowOnInputLanguageChange)
				->setOnContextMenu(WindowOnContextMenu)
				->setOnDisplayChange(WindowOnDisplayChange)
				->setOnKeyDown(WindowOnKeyDown)
				->setOnKeyUp(WindowOnKeyUp)
				->setOnChar(WindowOnChar)
				->setOnDeadChar(WindowOnDeadChar)
				->setOnSysKeyDown(WindowOnSysKeyDown)
				->setOnSysKeyUp(WindowOnSysKeyUp)
				->setOnSysChar(WindowOnSysChar)
				->setOnSysDeadChar(WindowOnSysDeadChar)
				->setOnInitDialog(WindowOnInitDialog)
				->setOnSysCommand(WindowOnSysCommand)
				->setOnHScroll(WindowOnHScroll)
				->setOnVScroll(WindowOnVScroll)
				->setOnGestureZoom(WindowOnGestureZoom)
				->setOnGesturePan(WindowOnGesturePan)
				->setOnGestureRotate(WindowOnGestureRotate)
				->setOnGestureTwoFingerTap(WindowOnGestureTwoFingerTap)
				->setOnGesturePressAndTap(WindowOnGesturePressAndTap)
				->setOnGestureNotify(WindowOnGestureNotify)
				->setOnEnterIdleDialog(WindowOnEnterIdleDialog)
				->setOnEnterIdleMenu(WindowOnEnterIdleMenu)
				->setOnMouseMove(WindowOnMouseMove)
				->setOnLeftMouseButtonDown(WindowOnLeftMouseButtonDown)
				->setOnLeftMouseButtonUp(WindowOnLeftMouseButtonUp)
				->setOnLeftMouseButtonDoubleClick(WindowOnLeftMouseButtonDoubleClick)
				->setOnRightMouseButtonDown(WindowOnRightMouseButtonDown)
				->setOnRightMouseButtonUp(WindowOnRightMouseButtonUp)
				->setOnRightMouseButtonDoubleClick(WindowOnRightMouseButtonDoubleClick)
				->setOnMiddleMouseButtonDown(WindowOnMiddleMouseButtonDown)
				->setOnMiddleMouseButtonUp(WindowOnMiddleMouseButtonUp)
				->setOnMiddleMouseButtonDoubleClick(WindowOnMiddleMouseButtonDoubleClick)
				->setOnMouseVerticalWheel(WindowOnMouseVerticalWheel)
				->setOnMouseHorizontalWheel(WindowOnMouseHorizontalWheel)
				->setOnResizing(WindowOnResizing)
				->setOnLoseCapture(WindowOnLoseCapture)
				->setOnMoving(WindowOnMoving)
				->setOnEnterSizeMove(WindowOnEnterSizeMove)
				->setOnExitSizeMove(WindowOnExitSizeMove)
				->setOnMouseHover(WindowOnMouseHover)
				->setOnMouseLeave(WindowOnMouseLeave)
				->setOnHotKey(WindowOnHotKey)
				->setOnThemeChanged(WindowOnThemeChanged)
				->setOnClipboardUpdate(WindowOnClipboardUpdate)
				->setOnTimer(WindowOnTimer)
				->setOnNonClientMouseMove(WindowOnNonClientMouseMove)
				->setOnNonClientLeftMouseButtonDown(WindowOnNonClientLeftMouseButtonDown)
				->setOnNonClientLeftMouseButtonUp(WindowOnNonClientLeftMouseButtonUp)
				->setOnNonClientLeftMouseButtonDoubleClick(WindowOnNonClientLeftMouseButtonDoubleClick)
				->setOnNonClientRightMouseButtonDown(WindowOnNonClientRightMouseButtonDown)
				->setOnNonClientRightMouseButtonUp(WindowOnNonClientRightMouseButtonUp)
				->setOnNonClientRightMouseButtonDoubleClick(WindowOnNonClientRightMouseButtonDoubleClick)
				->setOnNonClientMiddleMouseButtonDown(WindowOnNonClientMiddleMouseButtonDown)
				->setOnNonClientMiddleMouseButtonUp(WindowOnNonClientMiddleMouseButtonUp)
				->setOnNonClientMiddleMouseButtonDoubleClick(WindowOnNonClientMiddleMouseButtonDoubleClick)
				->setOnEnterMenuLoop(WindowOnEnterMenuLoop)
				->setOnExitMenuLoop(WindowOnExitMenuLoop)
				->setOnNonClientMouseHover(WindowOnNonClientMouseHover)
				->setOnNonClientMouseLeave(WindowOnNonClientMouseLeave);
			// If window is not created yet, try to create it
			if (!m_pWindow->getIsCreated())
				if (!m_pWindow->Create())
					return false;
			m_pWindow->setCursor(m_eCursor);
			return true;
		}

		bool CForm::InitializeFont()
		{
			// Create font
			CStyleFont *font{ nullptr };
			if (m_pStyle && (font = m_pStyle->getFontByName(m_sClassName)))
				m_pFont = m_pPresenter->FontCreate(font);
			else
				m_pFont = m_pPresenter->FontCreate(&m_cDefaultFont);
			if (m_pFont)
			{
				// Set font callbacks
				m_pFont
					->setCallbackParam(this)
					->setOnChangeName(FontOnChangeName)
					->setOnChangeHeight(FontOnChangeHeight)
					->setOnChangeWeight(FontOnChangeWeight)
					->setOnChangeItalic(FontOnChangeItalic)
					->setOnChangeUnderline(FontOnChangeUnderline)
					->setOnChangeStrikeOut(FontOnChangeStrikeOut)
					->setOnChangeWidth(FontOnChangeWidth)
					->setOnChangeCharSet(FontOnChangeCharSet)
					->setOnChangeQuality(FontOnChangeQuality)
					->setOnChangePitchAndFamily(FontOnChangePitchAndFamily)
					->setOnChangeOrientation(FontOnChangeOrientation)
					->setOnChangeDistance(FontOnChangeDistance)
					->setOnChangeShadow(FontOnChangeShadow)
					->setOnChangeShadowShift(FontOnChangeShadowShift)
					->setOnChangeShadowBlur(FontOnChangeShadowBlur)
					->setOnChangeShadowColor(FontOnChangeShadowColor)
					->setOnChangeColor(FontOnChangeColor)
					->setOnChangeInterpolate(FontOnChangeInterpolate)
					->setOnBeginChange(FontOnBeginChange)
					->setOnEndChange(FontOnEndChange);
			}
			return m_pFont != nullptr;
		}
	#pragma endregion

	#pragma region Window callbacks
		void CForm::WindowOnCreate(void *param)
		{
			CForm *form{ (CForm*)param };
			form->LockRepaint();
			form->NotifyOnCreate();
			form->UpdateHoveredControl();
			form->UnlockRepaint();
		}

		void CForm::WindowOnDestroy(void *param)
		{
			CForm *form{ (CForm*)param };
			form->LockRepaint();
			form->DeleteTimers();
			form->NotifyOnDestroy();
			form->UpdateHoveredControl();
			form->UnlockRepaint();
		}

		void CForm::WindowOnMove(const int x, const int y, void *param)
		{
			CForm *form{ (CForm*)param };
			form->LockRepaint();
			form->NotifyOnMove(x, y);
			form->UpdateHoveredControl();
			form->UnlockRepaint();
		}

		void CForm::WindowOnRestore(const int width, const int height, void *param)
		{
			CForm *form{ (CForm*)param };
			form->LockRepaint();
			form->SendNotify_ParentResize();
			form->NotifyOnRestore(width, height);
			form->UpdateHoveredControl();
			form->UnlockRepaint();
		}

		void CForm::WindowOnMinimize(const int width, const int height, void *param)
		{
			CForm *form{ (CForm*)param };
			form->LockRepaint();
			form->NotifyOnMinimize(width, height);
			form->UpdateHoveredControl();
			form->UnlockRepaint();
		}

		void CForm::WindowOnMaximize(const int width, const int height, void *param)
		{
			CForm *form{ (CForm*)param };
			form->LockRepaint();
			form->SendNotify_ParentResize();
			form->NotifyOnMaximize(width, height);
			form->UpdateHoveredControl();
			form->UnlockRepaint();
		}

		void CForm::WindowOnActivate(const bool byclick, void *param)
		{
			CForm *form{ (CForm*)param };
			form->LockRepaint();
			form->NotifyOnActivate(byclick);
			form->UpdateHoveredControl();
			form->UnlockRepaint();
		}

		void CForm::WindowOnDeactivate(void *param)
		{
			CForm *form{ (CForm*)param };
			form->LockRepaint();
			form->NotifyOnDeactivate();
			form->UpdateHoveredControl();
			form->UnlockRepaint();
		}

		void CForm::WindowOnSetFocus(void *param)
		{
			CForm *form{ (CForm*)param };
			form->LockRepaint();
			form->m_pActiveControl = form->m_pOldActiveControl;
			form->m_pOldActiveControl = nullptr;
			if (form->m_pActiveControl)
				form->m_pActiveControl->NotifyOnResetFocus();
			form->NotifyOnSetFocus();
			form->UpdateHoveredControl();
			form->UnlockRepaint();
		}

		void CForm::WindowOnKillFocus(void *param)
		{
			CForm *form{ (CForm*)param };
			form->LockRepaint();
			if (form->m_pActiveControl)
				form->m_pActiveControl->NotifyOnKillFocus();
			form->m_pOldActiveControl = form->m_pActiveControl;
			form->m_pActiveControl = nullptr;
			form->NotifyOnKillFocus();
			form->UpdateHoveredControl();
			form->UnlockRepaint();
		}
		void CForm::WindowOnEnable(void *param)
		{
			CForm *form{ (CForm*)param };
			form->LockRepaint();
			form->NotifyOnEnable();
			form->UpdateHoveredControl();
			form->UnlockRepaint();
		}

		void CForm::WindowOnDisable(void *param)
		{
			CForm *form{ (CForm*)param };
			form->LockRepaint();
			form->NotifyOnDisable();
			form->UpdateHoveredControl();
			form->UnlockRepaint();
		}

		void CForm::WindowOnPaint(const int left, const int top, const int right, const int bottom, void *param)
		{
			CForm *form{ (CForm*)param };
			form->LockRepaint();
			form->NotifyOnPaint(left, top, right, bottom);
			form->UpdateHoveredControl();
			form->UnlockRepaint();
		}

		void CForm::WindowOnClose(IWindow::CLOSE_ACTION &action, void *param)
		{
			CForm *form{ (CForm*)param };
			form->LockRepaint();
			form->NotifyOnClose(action);
			form->UpdateHoveredControl();
			form->UnlockRepaint();
		}

		bool CForm::WindowOnQueryEndSession(void *param)
		{
			CForm *form{ (CForm*)param };
			form->LockRepaint();
			bool result{ form->NotifyOnQueryEndSession() };
			form->UpdateHoveredControl();
			form->UnlockRepaint();
			return result;
		}

		bool CForm::WindowOnQueryOpen(void *param)
		{
			CForm *form{ (CForm*)param };
			form->LockRepaint();
			bool result{ form->NotifyOnQueryOpen() };
			form->UpdateHoveredControl();
			form->UnlockRepaint();
			return result;
		}

		void CForm::WindowOnEndSession(const bool ending, void *param)
		{
			CForm *form{ (CForm*)param };
			form->LockRepaint();
			form->NotifyOnEndSession(ending);
			form->UpdateHoveredControl();
			form->UnlockRepaint();
		}

		void CForm::WindowOnShow(void *param)
		{
			CForm *form{ (CForm*)param };
			form->LockRepaint();
			form->NotifyOnShow();
			form->UpdateHoveredControl();
			form->UnlockRepaint();
		}

		void CForm::WindowOnHide(void *param)
		{
			CForm *form{ (CForm*)param };
			form->LockRepaint();
			form->NotifyOnHide();
			form->UpdateHoveredControl();
			form->UnlockRepaint();
		}

		void CForm::WindowOnDeviceModeChange(void *param)
		{
			CForm *form{ (CForm*)param };
			form->LockRepaint();
			form->NotifyOnDeviceModeChange();
			form->UpdateHoveredControl();
			form->UnlockRepaint();
		}

		void CForm::WindowOnActivateApp(void *param)
		{
			CForm *form{ (CForm*)param };
			form->LockRepaint();
			form->NotifyOnActivateApp();
			form->UpdateHoveredControl();
			form->UnlockRepaint();
		}

		void CForm::WindowOnDeactivateApp(void *param)
		{
			CForm *form{ (CForm*)param };
			form->LockRepaint();
			form->NotifyOnDeactivateApp();
			form->UpdateHoveredControl();
			form->UnlockRepaint();
		}

		void CForm::WindowOnTimeChange(void *param)
		{
			CForm *form{ (CForm*)param };
			form->LockRepaint();
			form->NotifyOnTimeChange();
			form->UpdateHoveredControl();
			form->UnlockRepaint();
		}

		bool CForm::WindowOnInputLanguageChangeRequest(void *param)
		{
			CForm *form{ (CForm*)param };
			form->LockRepaint();
			bool result{ form->NotifyOnInputLanguageChangeRequest() };
			form->UpdateHoveredControl();
			form->UnlockRepaint();
			return result;
		}

		void CForm::WindowOnInputLanguageChange(void *param)
		{
			CForm *form{ (CForm*)param };
			form->LockRepaint();
			form->NotifyOnInputLanguageChange();
			form->UpdateHoveredControl();
			form->UnlockRepaint();
		}

		bool CForm::WindowOnContextMenu(const int x, const int y, void *param)
		{
			CForm *form{ (CForm*)param };
			form->LockRepaint();
			bool result{ form->NotifyOnContextMenu(x, y) };
			form->UpdateHoveredControl();
			form->UnlockRepaint();
			return result;
		}

		void CForm::WindowOnDisplayChange(const int width, const int height, void *param)
		{
			CForm *form{ (CForm*)param };
			form->LockRepaint();
			form->NotifyOnDisplayChange(width, height);
			form->UpdateHoveredControl();
			form->UnlockRepaint();
		}

		void CForm::WindowOnKeyDown(const IWindow::KEY key, void *param)
		{
			CForm *form{ (CForm*)param };
			form->LockRepaint();
			form->m_bSpecialKeyProcessed = false;
			if (!form->m_pCaptureKeyboardControl || !form->m_pCaptureKeyboardControl->NotifyOnKeyDown(key))
				if (!form->ProcessSpecialKeyDown(key))
					if (form->m_pActiveControl && form->m_pActiveControl != form->m_pCaptureKeyboardControl)
						form->m_pActiveControl->NotifyOnKeyDown(key);
			form->ProcessDownHotkeys(key);
			form->NotifyOnKeyDown(key);
			form->UpdateHoveredControl();
			form->UnlockRepaint();
		}

		void CForm::WindowOnKeyUp(const IWindow::KEY key, void *param)
		{
			CForm *form{ (CForm*)param };
			if (!form->m_bSpecialKeyProcessed)
			{
				form->LockRepaint();

				if (!form->m_pCaptureKeyboardControl || !form->m_pCaptureKeyboardControl->NotifyOnKeyUp(key))
					if (form->m_pActiveControl && form->m_pActiveControl != form->m_pCaptureKeyboardControl)
						form->m_pActiveControl->NotifyOnKeyUp(key);
				form->ProcessUpHotkeys(key);
				form->NotifyOnKeyUp(key);
				form->UpdateHoveredControl();
				form->UnlockRepaint();
			}
		}

		void CForm::WindowOnChar(const wchar_t chr, void *param)
		{
			CForm *form{ (CForm*)param };
			if (!form->m_bSpecialKeyProcessed)
			{
				form->LockRepaint();
				if (!form->m_pCaptureKeyboardControl || !form->m_pCaptureKeyboardControl->NotifyOnChar(chr))
					if (form->m_pActiveControl && form->m_pActiveControl != form->m_pCaptureKeyboardControl)
						form->m_pActiveControl->NotifyOnChar(chr);
				form->NotifyOnChar(chr);
				form->UpdateHoveredControl();
				form->UnlockRepaint();
			}
		}

		void CForm::WindowOnDeadChar(const wchar_t chr, void *param)
		{
			CForm *form{ (CForm*)param };
			if (!form->m_bSpecialKeyProcessed)
			{
				form->LockRepaint();
				if (!form->m_pCaptureKeyboardControl || !form->m_pCaptureKeyboardControl->NotifyOnDeadChar(chr))
					if (form->m_pActiveControl && form->m_pActiveControl != form->m_pCaptureKeyboardControl)
						form->m_pActiveControl->NotifyOnDeadChar(chr);
				form->NotifyOnDeadChar(chr);
				form->UpdateHoveredControl();
				form->UnlockRepaint();
			}
		}

		void CForm::WindowOnSysKeyDown(const IWindow::KEY key, void *param)
		{
			CForm *form{ (CForm*)param };
			form->LockRepaint();
			if (!form->m_pCaptureKeyboardControl || !form->m_pCaptureKeyboardControl->NotifyOnSysKeyDown(key))
				if (form->m_pActiveControl && form->m_pActiveControl != form->m_pCaptureKeyboardControl)
					form->m_pActiveControl->NotifyOnSysKeyDown(key);
			form->ProcessDownHotkeys(key);
			form->NotifyOnSysKeyDown(key);
			form->UpdateHoveredControl();
			form->UnlockRepaint();
		}

		void CForm::WindowOnSysKeyUp(const IWindow::KEY key, void *param)
		{
			CForm *form{ (CForm*)param };
			form->LockRepaint();
			if (!form->m_pCaptureKeyboardControl || !form->m_pCaptureKeyboardControl->NotifyOnSysKeyUp(key))
				if (form->m_pActiveControl && form->m_pActiveControl != form->m_pCaptureKeyboardControl)
					form->m_pActiveControl->NotifyOnSysKeyUp(key);
			form->ProcessUpHotkeys(key);
			form->NotifyOnSysKeyUp(key);
			form->UpdateHoveredControl();
			form->UnlockRepaint();
		}

		void CForm::WindowOnSysChar(const wchar_t chr, void *param)
		{
			CForm *form{ (CForm*)param };
			form->LockRepaint();
			if (!form->m_pCaptureKeyboardControl || !form->m_pCaptureKeyboardControl->NotifyOnSysChar(chr))
				if (form->m_pActiveControl && form->m_pActiveControl != form->m_pCaptureKeyboardControl)
					form->m_pActiveControl->NotifyOnSysChar(chr);
			form->NotifyOnSysChar(chr);
			form->UpdateHoveredControl();
			form->UnlockRepaint();
		}

		void CForm::WindowOnSysDeadChar(const wchar_t chr, void *param)
		{
			CForm *form{ (CForm*)param };
			form->LockRepaint();
			if (!form->m_pCaptureKeyboardControl || !form->m_pCaptureKeyboardControl->NotifyOnSysDeadChar(chr))
				if (form->m_pActiveControl && form->m_pActiveControl != form->m_pCaptureKeyboardControl)
					form->m_pActiveControl->NotifyOnSysDeadChar(chr);
			form->NotifyOnSysDeadChar(chr);
			form->UpdateHoveredControl();
			form->UnlockRepaint();
		}

		bool CForm::WindowOnInitDialog(void *param)
		{
			CForm *form{ (CForm*)param };
			form->LockRepaint();
			bool result{ form->NotifyOnInitDialog() };
			form->UpdateHoveredControl();
			form->UnlockRepaint();
			return result;
		}

		void CForm::WindowOnSysCommand(const IWindow::SYSTEM_COMMAND_TYPE type, const int x, const int y, void *param)
		{
			CForm *form{ (CForm*)param };
			form->LockRepaint();
			form->NotifyOnSysCommand(type, x, y);
			form->UpdateHoveredControl();
			form->UnlockRepaint();
		}

		void CForm::WindowOnHScroll(const IWindow::SCROLL_TYPE type, const int pos, void *param)
		{
			CForm *form{ (CForm*)param };
			form->LockRepaint();
			form->NotifyOnHScroll(type, pos);
			form->UpdateHoveredControl();
			form->UnlockRepaint();
		}

		void CForm::WindowOnVScroll(const IWindow::SCROLL_TYPE type, const int pos, void *param)
		{
			CForm *form{ (CForm*)param };
			form->LockRepaint();
			form->NotifyOnVScroll(type, pos);
			form->UpdateHoveredControl();
			form->UnlockRepaint();
		}

		void CForm::WindowOnGestureZoom(const int x, const int y, void *param)
		{
			CForm *form{ (CForm*)param };
			form->LockRepaint();
			form->NotifyOnGestureZoom(x, y);
			form->UpdateHoveredControl();
			form->UnlockRepaint();
		}

		void CForm::WindowOnGesturePan(const int x, const int y, void *param)
		{
			CForm *form{ (CForm*)param };
			form->LockRepaint();
			form->NotifyOnGesturePan(x, y);
			form->UpdateHoveredControl();
			form->UnlockRepaint();
		}

		void CForm::WindowOnGestureRotate(const int x, const int y, void *param)
		{
			CForm *form{ (CForm*)param };
			form->LockRepaint();
			form->NotifyOnGestureRotate(x, y);
			form->UpdateHoveredControl();
			form->UnlockRepaint();
		}

		void CForm::WindowOnGestureTwoFingerTap(const int x, const int y, void *param)
		{
			CForm *form{ (CForm*)param };
			form->LockRepaint();
			form->NotifyOnGestureTwoFingerTap(x, y);
			form->UpdateHoveredControl();
			form->UnlockRepaint();
		}

		void CForm::WindowOnGesturePressAndTap(const int x, const int y, void *param)
		{
			CForm *form{ (CForm*)param };
			form->LockRepaint();
			form->NotifyOnGesturePressAndTap(x, y);
			form->UpdateHoveredControl();
			form->UnlockRepaint();
		}

		void CForm::WindowOnGestureNotify(void *param)
		{
			CForm *form{ (CForm*)param };
			form->LockRepaint();
			form->NotifyOnGestureNotify();
			form->UpdateHoveredControl();
			form->UnlockRepaint();
		}

		void CForm::WindowOnEnterIdleDialog(void *param)
		{
			CForm *form{ (CForm*)param };
			form->LockRepaint();
			form->NotifyOnEnterIdleDialog();
			form->UpdateHoveredControl();
			form->UnlockRepaint();
		}

		void CForm::WindowOnEnterIdleMenu(void *param)
		{
			CForm *form{ (CForm*)param };
			form->LockRepaint();
			form->NotifyOnEnterIdleMenu();
			form->UpdateHoveredControl();
			form->UnlockRepaint();
		}

		void CForm::WindowOnMouseMove(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift, void *param)
		{
			CForm *form{ (CForm*)param };
			form->LockRepaint();
			if (!form->m_bIsTrackingMouseLeave)
			{
				form->m_pWindow->StartTrackMouseLeave();
				form->m_bIsTrackingMouseLeave = true;
			}
			if (!form->m_pCaptureMouseControl || !form->m_pCaptureMouseControl->NotifyOnMouseMove(x, y, ctrl, left, middle, right, shift))
			{
				form->UpdateHoveredControl();
				if (form->m_pHoveredControl && form->m_pHoveredControl != form->m_pCaptureMouseControl)
					form->m_pHoveredControl->NotifyOnMouseMove(x, y, ctrl, left, middle, right, shift);
			}
			form->NotifyOnMouseMove(x, y, ctrl, left, middle, right, shift);
			form->UpdateHoveredControl();
			form->UnlockRepaint();
		}

		void CForm::WindowOnLeftMouseButtonDown(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift, void *param)
		{
			CForm *form{ (CForm*)param };
			form->LockRepaint();
			if (!form->m_pCaptureMouseControl || !form->m_pCaptureMouseControl->NotifyOnLeftMouseButtonDown(x, y, ctrl, left, middle, right, shift))
			{
				CControl *control = form->getControlAtPosition(x, y);
				form->ActivateControlAtClick(x, y);
				if (control && control != form->m_pCaptureMouseControl)
					control->NotifyOnLeftMouseButtonDown(x, y, ctrl, left, middle, right, shift);
			}
			form->NotifyOnLeftMouseButtonDown(x, y, ctrl, left, middle, right, shift);
			form->UpdateHoveredControl();
			form->UnlockRepaint();
		}

		void CForm::WindowOnLeftMouseButtonUp(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift, void *param)
		{
			CForm *form{ (CForm*)param };
			form->LockRepaint();
			if (!form->m_pCaptureMouseControl || !form->m_pCaptureMouseControl->NotifyOnLeftMouseButtonUp(x, y, ctrl, left, middle, right, shift))
			{
				CControl *control = form->getControlAtPosition(x, y);
				if (control && control != form->m_pCaptureMouseControl)
					control->NotifyOnLeftMouseButtonUp(x, y, ctrl, left, middle, right, shift);
			}
			form->NotifyOnLeftMouseButtonUp(x, y, ctrl, left, middle, right, shift);
			form->UpdateHoveredControl();
			form->UnlockRepaint();
		}

		void CForm::WindowOnLeftMouseButtonDoubleClick(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift, void *param)
		{
			CForm *form{ (CForm*)param };
			form->LockRepaint();
			if (!form->m_pCaptureMouseControl || !form->m_pCaptureMouseControl->NotifyOnLeftMouseButtonDoubleClick(x, y, ctrl, left, middle, right, shift))
			{
				CControl *control = form->getControlAtPosition(x, y);
				if (control && control != form->m_pCaptureMouseControl)
					control->NotifyOnLeftMouseButtonDoubleClick(x, y, ctrl, left, middle, right, shift);
			}
			form->NotifyOnLeftMouseButtonDoubleClick(x, y, ctrl, left, middle, right, shift);
			form->UpdateHoveredControl();
			form->UnlockRepaint();
		}

		void CForm::WindowOnRightMouseButtonDown(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift, void *param)
		{
			CForm *form{ (CForm*)param };
			form->LockRepaint();
			if (!form->m_pCaptureMouseControl || !form->m_pCaptureMouseControl->NotifyOnRightMouseButtonDown(x, y, ctrl, left, middle, right, shift))
			{
				CControl *control = form->getControlAtPosition(x, y);
				if (control && control != form->m_pCaptureMouseControl)
					control->NotifyOnRightMouseButtonDown(x, y, ctrl, left, middle, right, shift);
				form->ActivateControlAtClick(x, y);
			}
			form->NotifyOnRightMouseButtonDown(x, y, ctrl, left, middle, right, shift);
			form->UpdateHoveredControl();
			form->UnlockRepaint();
		}

		void CForm::WindowOnRightMouseButtonUp(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift, void *param)
		{
			CForm *form{ (CForm*)param };
			form->LockRepaint();
			if (!form->m_pCaptureMouseControl || !form->m_pCaptureMouseControl->NotifyOnRightMouseButtonUp(x, y, ctrl, left, middle, right, shift))
			{
				CControl *control = form->getControlAtPosition(x, y);
				if (control && control != form->m_pCaptureMouseControl)
					control->NotifyOnRightMouseButtonUp(x, y, ctrl, left, middle, right, shift);
			}
			form->NotifyOnRightMouseButtonUp(x, y, ctrl, left, middle, right, shift);
			form->UpdateHoveredControl();
			form->UnlockRepaint();
		}

		void CForm::WindowOnRightMouseButtonDoubleClick(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift, void *param)
		{
			CForm *form{ (CForm*)param };
			form->LockRepaint();
			if (!form->m_pCaptureMouseControl || !form->m_pCaptureMouseControl->NotifyOnRightMouseButtonDoubleClick(x, y, ctrl, left, middle, right, shift))
			{
				CControl *control = form->getControlAtPosition(x, y);
				if (control && control != form->m_pCaptureMouseControl)
					control->NotifyOnRightMouseButtonDoubleClick(x, y, ctrl, left, middle, right, shift);
			}
			form->NotifyOnRightMouseButtonDoubleClick(x, y, ctrl, left, middle, right, shift);
			form->UpdateHoveredControl();
			form->UnlockRepaint();
		}

		void CForm::WindowOnMiddleMouseButtonDown(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift, void *param)
		{
			CForm *form{ (CForm*)param };
			form->LockRepaint();
			if (!form->m_pCaptureMouseControl || !form->m_pCaptureMouseControl->NotifyOnMiddleMouseButtonDown(x, y, ctrl, left, middle, right, shift))
			{
				CControl *control = form->getControlAtPosition(x, y);
				if (control && control != form->m_pCaptureMouseControl)
					control->NotifyOnMiddleMouseButtonDown(x, y, ctrl, left, middle, right, shift);
				form->ActivateControlAtClick(x, y);
			}
			form->NotifyOnMiddleMouseButtonDown(x, y, ctrl, left, middle, right, shift);
			form->UpdateHoveredControl();
			form->UnlockRepaint();
		}

		void CForm::WindowOnMiddleMouseButtonUp(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift, void *param)
		{
			CForm *form{ (CForm*)param };
			form->LockRepaint();
			if (!form->m_pCaptureMouseControl || !form->m_pCaptureMouseControl->NotifyOnMiddleMouseButtonUp(x, y, ctrl, left, middle, right, shift))
			{
				CControl *control = form->getControlAtPosition(x, y);
				if (control && control != form->m_pCaptureMouseControl)
					control->NotifyOnMiddleMouseButtonUp(x, y, ctrl, left, middle, right, shift);
			}
			form->NotifyOnMiddleMouseButtonUp(x, y, ctrl, left, middle, right, shift);
			form->UpdateHoveredControl();
			form->UnlockRepaint();
		}

		void CForm::WindowOnMiddleMouseButtonDoubleClick(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift, void *param)
		{
			CForm *form{ (CForm*)param };
			form->LockRepaint();
			if (!form->m_pCaptureMouseControl || !form->m_pCaptureMouseControl->NotifyOnMiddleMouseButtonDoubleClick(x, y, ctrl, left, middle, right, shift))
			{
				CControl *control = form->getControlAtPosition(x, y);
				if (control && control != form->m_pCaptureMouseControl)
					control->NotifyOnMiddleMouseButtonDoubleClick(x, y, ctrl, left, middle, right, shift);
			}
			form->NotifyOnMiddleMouseButtonDoubleClick(x, y, ctrl, left, middle, right, shift);
			form->UpdateHoveredControl();
			form->UnlockRepaint();
		}

		void CForm::WindowOnMouseVerticalWheel(const int x, const int y, const int delta, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift, void *param)
		{
			CForm *form{ (CForm*)param };
			form->LockRepaint();
			if (!form->m_pCaptureMouseControl || !form->m_pCaptureMouseControl->NotifyOnMouseVerticalWheel(x, y, delta, ctrl, left, middle, right, shift))
			{
				CControl *control = form->getControlAtPosition(x, y);
				if (control && control != form->m_pCaptureMouseControl)
					control->NotifyOnMouseVerticalWheel(x, y, delta, ctrl, left, middle, right, shift);
			}
			form->NotifyOnMouseVerticalWheel(x, y, delta, ctrl, left, middle, right, shift);
			form->UpdateHoveredControl();
			form->UnlockRepaint();
		}

		void CForm::WindowOnMouseHorizontalWheel(const int x, const int y, const int delta, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift, void *param)
		{
			CForm *form{ (CForm*)param };
			form->LockRepaint();
			if (!form->m_pCaptureMouseControl || !form->m_pCaptureMouseControl->NotifyOnMouseHorizontalWheel(x, y, delta, ctrl, left, middle, right, shift))
			{
				CControl *control = form->getControlAtPosition(x, y);
				if (control && control != form->m_pCaptureMouseControl)
					control->NotifyOnMouseHorizontalWheel(x, y, delta, ctrl, left, middle, right, shift);
			}
			form->NotifyOnMouseHorizontalWheel(x, y, delta, ctrl, left, middle, right, shift);
			form->UpdateHoveredControl();
			form->UnlockRepaint();
		}

		void CForm::WindowOnResizing(const IWindow::EDGE edge, const int left, const int top, const int right, const int bottom, void *param)
		{
			CForm *form{ (CForm*)param };
			form->LockRepaint();
			for (auto pos = form->m_aControlsRoot.begin(); pos != form->m_aControlsRoot.end(); pos++)
				(*pos)->NotifyOnParentResize();
			form->NotifyOnResizing(edge, left, top, right, bottom);
			form->UpdateHoveredControl();
			form->UnlockRepaint();
		}

		void CForm::WindowOnLoseCapture(void *param)
		{
			CForm *form{ (CForm*)param };
			form->LockRepaint();
			form->NotifyOnLoseCapture();
			form->UpdateHoveredControl();
			form->UnlockRepaint();
		}

		void CForm::WindowOnMoving(const int left, const int top, const int right, const int bottom, void *param)
		{
			CForm *form{ (CForm*)param };
			form->LockRepaint();
			form->NotifyOnMoving(left, top, right, bottom);
			form->UpdateHoveredControl();
			form->UnlockRepaint();
		}

		void CForm::WindowOnEnterSizeMove(void *param)
		{
			CForm *form{ (CForm*)param };
			form->LockRepaint();
			form->m_sOldClientRect = form->m_pWindow->getClientRect();
			form->NotifyOnEnterSizeMove();
			form->UpdateHoveredControl();
			form->UnlockRepaint();
		}

		void CForm::WindowOnExitSizeMove(void *param)
		{
			CForm *form{ (CForm*)param };
			form->LockRepaint();
			if (form->m_sOldClientRect != form->m_pWindow->getClientRect())
			{
				form->SendNotify_ParentResize();
				form->NotifyOnResizing(IWindow::edgeNone, 0, 0, 0, 0);
			}
			form->NotifyOnExitSizeMove();
			form->UpdateHoveredControl();
			form->UnlockRepaint();
		}

		void CForm::WindowOnMouseHover(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift, void *param)
		{
			CForm *form{ (CForm*)param };
			form->LockRepaint();
			form->NotifyOnMouseHover(x, y, ctrl, left, middle, right, shift);
			form->UpdateHoveredControl();
			form->UnlockRepaint();
		}

		void CForm::WindowOnMouseLeave(void *param)
		{
			CForm *form{ (CForm*)param };
			form->LockRepaint();
			form->UpdateHoveredControl();
			form->m_bIsTrackingMouseLeave = false;
			form->NotifyOnMouseLeave();
			form->UpdateHoveredControl();
			form->UnlockRepaint();
		}

		void CForm::WindowOnHotKey(const bool is_desktop, const IWindow::KEY key, const bool alt, const bool ctrl, const bool shift, const bool win, void *param)
		{
			CForm *form{ (CForm*)param };
			form->LockRepaint();
			form->NotifyOnHotKey(is_desktop, key, alt, ctrl, shift, win);
			form->UpdateHoveredControl();
			form->UnlockRepaint();
		}

		void CForm::WindowOnThemeChanged(void *param)
		{
			CForm *form{ (CForm*)param };
			form->LockRepaint();
			form->NotifyOnThemeChanged();
			form->UpdateHoveredControl();
			form->UnlockRepaint();
		}

		void CForm::WindowOnClipboardUpdate(void *param)
		{
			CForm *form{ (CForm*)param };
			form->LockRepaint();
			form->NotifyOnClipboardUpdate();
			form->UpdateHoveredControl();
			form->UnlockRepaint();
		}

		void CForm::WindowOnTimer(const unsigned int id, void *param)
		{
			CForm *form{ (CForm*)param };
			form->LockRepaint();
			for (auto pos = form->m_aTimers.begin(); pos != form->m_aTimers.end(); pos++)
				if ((*pos).Id == id)
				{
					(*pos).Callback((*pos).Param);
					break;
				}
			form->NotifyOnTimer(id);
			form->UpdateHoveredControl();
			form->UnlockRepaint();
		}

		void CForm::WindowOnNonClientMouseMove(const int x, const int y, void *param)
		{
			CForm *form{ (CForm*)param };
			form->LockRepaint();
			form->NotifyOnNonClientMouseMove(x, y);
			form->UpdateHoveredControl();
			form->UnlockRepaint();
		}

		void CForm::WindowOnNonClientLeftMouseButtonDown(const int x, const int y, void *param)
		{
			CForm *form{ (CForm*)param };
			form->LockRepaint();
			form->NotifyOnNonClientLeftMouseButtonDown(x, y);
			form->UpdateHoveredControl();
			form->UnlockRepaint();
		}

		void CForm::WindowOnNonClientLeftMouseButtonUp(const int x, const int y, void *param)
		{
			CForm *form{ (CForm*)param };
			form->LockRepaint();
			form->NotifyOnNonClientLeftMouseButtonUp(x, y);
			form->UpdateHoveredControl();
			form->UnlockRepaint();
		}

		void CForm::WindowOnNonClientLeftMouseButtonDoubleClick(const int x, const int y, void *param)
		{
			CForm *form{ (CForm*)param };
			form->LockRepaint();
			form->NotifyOnNonClientLeftMouseButtonDoubleClick(x, y);
			form->UpdateHoveredControl();
			form->UnlockRepaint();
		}

		void CForm::WindowOnNonClientRightMouseButtonDown(const int x, const int y, void *param)
		{
			CForm *form{ (CForm*)param };
			form->LockRepaint();
			form->NotifyOnNonClientRightMouseButtonDown(x, y);
			form->UpdateHoveredControl();
			form->UnlockRepaint();
		}

		void CForm::WindowOnNonClientRightMouseButtonUp(const int x, const int y, void *param)
		{
			CForm *form{ (CForm*)param };
			form->LockRepaint();
			form->NotifyOnNonClientRightMouseButtonUp(x, y);
			form->UpdateHoveredControl();
			form->UnlockRepaint();
		}

		void CForm::WindowOnNonClientRightMouseButtonDoubleClick(const int x, const int y, void *param)
		{
			CForm *form{ (CForm*)param };
			form->LockRepaint();
			form->NotifyOnNonClientRightMouseButtonDoubleClick(x, y);
			form->UpdateHoveredControl();
			form->UnlockRepaint();
		}

		void CForm::WindowOnNonClientMiddleMouseButtonDown(const int x, const int y, void *param)
		{
			CForm *form{ (CForm*)param };
			form->LockRepaint();
			form->NotifyOnNonClientMiddleMouseButtonDown(x, y);
			form->UpdateHoveredControl();
			form->UnlockRepaint();
		}

		void CForm::WindowOnNonClientMiddleMouseButtonUp(const int x, const int y, void *param)
		{
			CForm *form{ (CForm*)param };
			form->LockRepaint();
			form->NotifyOnNonClientMiddleMouseButtonUp(x, y);
			form->UpdateHoveredControl();
			form->UnlockRepaint();
		}

		void CForm::WindowOnNonClientMiddleMouseButtonDoubleClick(const int x, const int y, void *param)
		{
			CForm *form{ (CForm*)param };
			form->LockRepaint();
			form->NotifyOnNonClientMiddleMouseButtonDoubleClick(x, y);
			form->UpdateHoveredControl();
			form->UnlockRepaint();
		}

		void CForm::WindowOnEnterMenuLoop(const bool track_popup_menu_used, void *param)
		{
			CForm *form{ (CForm*)param };
			form->LockRepaint();
			form->NotifyOnEnterMenuLoop(track_popup_menu_used);
			form->UpdateHoveredControl();
			form->UnlockRepaint();
		}

		void CForm::WindowOnExitMenuLoop(const bool is_shortcut, void *param)
		{
			CForm *form{ (CForm*)param };
			form->LockRepaint();
			form->NotifyOnExitMenuLoop(is_shortcut);
			form->UpdateHoveredControl();
			form->UnlockRepaint();
		}

		void CForm::WindowOnNonClientMouseHover(const int x, const int y, void *param)
		{
			CForm *form{ (CForm*)param };
			form->LockRepaint();
			form->NotifyOnNonClientMouseHover(x, y);
			form->UpdateHoveredControl();
			form->UnlockRepaint();
		}

		void CForm::WindowOnNonClientMouseLeave(void *param)
		{
			CForm *form{ (CForm*)param };
			form->LockRepaint();
			form->NotifyOnNonClientMouseLeave();
			form->UpdateHoveredControl();
			form->UnlockRepaint();
		}
	#pragma endregion

	#pragma region Font callbacks
		void CForm::FontOnChangeName(void *param)
		{
			CForm *form{ (CForm*)param };
			form->m_bIsFontSizeChanged = true;
			if (!form->m_bIsFontChanging)
			{
				form->LockRepaint();
				for (auto pos = form->m_aControlsRoot.begin(); pos != form->m_aControlsRoot.end(); pos++)
					if ((*pos)->m_bUseParentFont)
					{
						(*pos)->NotifyOnParentFontChangeName();
						(*pos)->NotifyOnParentFontChangeSize();
					}
				form->NotifyOnFontChangeName();
				form->NotifyOnFontChangeSize();
				form->UpdateHoveredControl();
				form->UnlockRepaint();
			}
		}

		void CForm::FontOnChangeHeight(void *param)
		{
			CForm *form{ (CForm*)param };
			form->m_bIsFontSizeChanged = true;
			if (!form->m_bIsFontChanging)
			{
				form->LockRepaint();
				for (auto pos = form->m_aControlsRoot.begin(); pos != form->m_aControlsRoot.end(); pos++)
					if ((*pos)->m_bUseParentFont)
					{
						(*pos)->NotifyOnParentFontChangeHeight();
						(*pos)->NotifyOnParentFontChangeSize();
					}
				form->NotifyOnFontChangeHeight();
				form->NotifyOnFontChangeSize();
				form->UpdateHoveredControl();
				form->UnlockRepaint();
			}
		}

		void CForm::FontOnChangeWeight(void *param)
		{
			CForm *form{ (CForm*)param };
			form->m_bIsFontSizeChanged = true;
			if (!form->m_bIsFontChanging)
			{
				form->LockRepaint();
				for (auto pos = form->m_aControlsRoot.begin(); pos != form->m_aControlsRoot.end(); pos++)
					if ((*pos)->m_bUseParentFont)
					{
						(*pos)->NotifyOnParentFontChangeWeight();
						(*pos)->NotifyOnParentFontChangeSize();
					}
				form->NotifyOnFontChangeWeight();
				form->NotifyOnFontChangeSize();
				form->UpdateHoveredControl();
				form->UnlockRepaint();
			}
		}

		void CForm::FontOnChangeItalic(void *param)
		{
			CForm *form{ (CForm*)param };
			form->m_bIsFontSizeChanged = true;
			if (!form->m_bIsFontChanging)
			{
				form->LockRepaint();
				for (auto pos = form->m_aControlsRoot.begin(); pos != form->m_aControlsRoot.end(); pos++)
					if ((*pos)->m_bUseParentFont)
					{
						(*pos)->NotifyOnParentFontChangeItalic();
						(*pos)->NotifyOnParentFontChangeSize();
					}
				form->NotifyOnFontChangeItalic();
				form->NotifyOnFontChangeSize();
				form->UpdateHoveredControl();
				form->UnlockRepaint();
			}
		}

		void CForm::FontOnChangeUnderline(void *param)
		{
			CForm *form{ (CForm*)param };
			form->m_bIsFontSizeChanged = true;
			if (!form->m_bIsFontChanging)
			{
				form->LockRepaint();
				for (auto pos = form->m_aControlsRoot.begin(); pos != form->m_aControlsRoot.end(); pos++)
					if ((*pos)->m_bUseParentFont)
					{
						(*pos)->NotifyOnParentFontChangeUnderline();
						(*pos)->NotifyOnParentFontChangeSize();
					}
				form->NotifyOnFontChangeUnderline();
				form->NotifyOnFontChangeSize();
				form->UpdateHoveredControl();
				form->UnlockRepaint();
			}
		}

		void CForm::FontOnChangeStrikeOut(void *param)
		{
			CForm *form{ (CForm*)param };
			form->m_bIsFontSizeChanged = true;
			if (!form->m_bIsFontChanging)
			{
				form->LockRepaint();
				for (auto pos = form->m_aControlsRoot.begin(); pos != form->m_aControlsRoot.end(); pos++)
					if ((*pos)->m_bUseParentFont)
					{
						(*pos)->NotifyOnParentFontChangeStrikeOut();
						(*pos)->NotifyOnParentFontChangeSize();
					}
				form->NotifyOnFontChangeStrikeOut();
				form->NotifyOnFontChangeSize();
				form->UpdateHoveredControl();
				form->UnlockRepaint();
			}
		}

		void CForm::FontOnChangeWidth(void *param)
		{
			CForm *form{ (CForm*)param };
			form->m_bIsFontSizeChanged = true;
			if (!form->m_bIsFontChanging)
			{
				form->LockRepaint();
				for (auto pos = form->m_aControlsRoot.begin(); pos != form->m_aControlsRoot.end(); pos++)
					if ((*pos)->m_bUseParentFont)
					{
						(*pos)->NotifyOnParentFontChangeWidth();
						(*pos)->NotifyOnParentFontChangeSize();
					}
				form->NotifyOnFontChangeWidth();
				form->NotifyOnFontChangeSize();
				form->UpdateHoveredControl();
				form->UnlockRepaint();
			}
		}

		void CForm::FontOnChangeCharSet(void *param)
		{
			CForm *form{ (CForm*)param };
			form->m_bIsFontSizeChanged = true;
			if (!form->m_bIsFontChanging)
			{
				form->LockRepaint();
				for (auto pos = form->m_aControlsRoot.begin(); pos != form->m_aControlsRoot.end(); pos++)
					if ((*pos)->m_bUseParentFont)
					{
						(*pos)->NotifyOnParentFontChangeCharSet();
						(*pos)->NotifyOnParentFontChangeSize();
					}
				form->NotifyOnFontChangeCharSet();
				form->NotifyOnFontChangeSize();
				form->UpdateHoveredControl();
				form->UnlockRepaint();
			}
		}

		void CForm::FontOnChangeQuality(void *param)
		{
			CForm *form{ (CForm*)param };
			form->m_bIsFontSizeChanged = true;
			if (!form->m_bIsFontChanging)
			{
				form->LockRepaint();
				for (auto pos = form->m_aControlsRoot.begin(); pos != form->m_aControlsRoot.end(); pos++)
					if ((*pos)->m_bUseParentFont)
					{
						(*pos)->NotifyOnParentFontChangeQuality();
						(*pos)->NotifyOnParentFontChangeSize();
					}
				form->NotifyOnFontChangeQuality();
				form->NotifyOnFontChangeSize();
				form->UpdateHoveredControl();
				form->UnlockRepaint();
			}
		}

		void CForm::FontOnChangePitchAndFamily(void *param)
		{
			CForm *form{ (CForm*)param };
			form->m_bIsFontSizeChanged = true;
			if (!form->m_bIsFontChanging)
			{
				form->LockRepaint();
				for (auto pos = form->m_aControlsRoot.begin(); pos != form->m_aControlsRoot.end(); pos++)
					if ((*pos)->m_bUseParentFont)
					{
						(*pos)->NotifyOnParentFontChangePitchAndFamily();
						(*pos)->NotifyOnParentFontChangeSize();
					}
				form->NotifyOnFontChangePitchAndFamily();
				form->NotifyOnFontChangeSize();
				form->UpdateHoveredControl();
				form->UnlockRepaint();
			}
		}

		void CForm::FontOnChangeOrientation(void *param)
		{
			CForm *form{ (CForm*)param };
			form->m_bIsFontSizeChanged = true;
			if (!form->m_bIsFontChanging)
			{
				form->LockRepaint();
				for (auto pos = form->m_aControlsRoot.begin(); pos != form->m_aControlsRoot.end(); pos++)
					if ((*pos)->m_bUseParentFont)
					{
						(*pos)->NotifyOnParentFontChangeOrientation();
						(*pos)->NotifyOnParentFontChangeSize();
					}
				form->NotifyOnFontChangeOrientation();
				form->NotifyOnFontChangeSize();
				form->UpdateHoveredControl();
				form->UnlockRepaint();
			}
		}

		void CForm::FontOnChangeDistance(void *param)
		{
			CForm *form{ (CForm*)param };
			form->m_bIsFontSizeChanged = true;
			if (!form->m_bIsFontChanging)
			{
				form->LockRepaint();
				for (auto pos = form->m_aControlsRoot.begin(); pos != form->m_aControlsRoot.end(); pos++)
					if ((*pos)->m_bUseParentFont)
					{
						(*pos)->NotifyOnParentFontChangeDistance();
						(*pos)->NotifyOnParentFontChangeSize();
					}
				form->NotifyOnFontChangeDistance();
				form->NotifyOnFontChangeSize();
				form->UpdateHoveredControl();
				form->UnlockRepaint();
			}
		}

		void CForm::FontOnChangeShadow(void *param)
		{
			CForm *form{ (CForm*)param };
			form->m_bIsFontSizeChanged = true;
			if (!form->m_bIsFontChanging)
			{
				form->LockRepaint();
				for (auto pos = form->m_aControlsRoot.begin(); pos != form->m_aControlsRoot.end(); pos++)
					if ((*pos)->m_bUseParentFont)
					{
						(*pos)->NotifyOnParentFontChangeShadow();
						(*pos)->NotifyOnParentFontChangeSize();
					}
				form->NotifyOnFontChangeShadow();
				form->NotifyOnFontChangeSize();
				form->UpdateHoveredControl();
				form->UnlockRepaint();
			}
		}

		void CForm::FontOnChangeShadowShift(void *param)
		{
			CForm *form{ (CForm*)param };
			form->m_bIsFontSizeChanged = true;
			if (!form->m_bIsFontChanging)
			{
				form->LockRepaint();
				for (auto pos = form->m_aControlsRoot.begin(); pos != form->m_aControlsRoot.end(); pos++)
					if ((*pos)->m_bUseParentFont)
					{
						(*pos)->NotifyOnParentFontChangeShadowShift();
						(*pos)->NotifyOnParentFontChangeSize();
					}
				form->NotifyOnFontChangeShadowShift();
				form->NotifyOnFontChangeSize();
				form->UpdateHoveredControl();
				form->UnlockRepaint();
			}
		}

		void CForm::FontOnChangeShadowBlur(void *param)
		{
			CForm *form{ (CForm*)param };
			form->m_bIsFontSizeChanged = true;
			if (!form->m_bIsFontChanging)
			{
				form->LockRepaint();
				for (auto pos = form->m_aControlsRoot.begin(); pos != form->m_aControlsRoot.end(); pos++)
					if ((*pos)->m_bUseParentFont)
					{
						(*pos)->NotifyOnParentFontChangeShadowBlur();
						(*pos)->NotifyOnParentFontChangeSize();
					}
				form->NotifyOnFontChangeShadowBlur();
				form->NotifyOnFontChangeSize();
				form->UpdateHoveredControl();
				form->UnlockRepaint();
			}
		}

		void CForm::FontOnChangeShadowColor(void *param)
		{
			CForm *form{ (CForm*)param };
			form->m_bIsFontStyleChanged = true;
			if (!form->m_bIsFontChanging)
			{
				form->LockRepaint();
				for (auto pos = form->m_aControlsRoot.begin(); pos != form->m_aControlsRoot.end(); pos++)
					if ((*pos)->m_bUseParentFont)
					{
						(*pos)->NotifyOnParentFontChangeShadowColor();
						(*pos)->NotifyOnParentFontChangeStyle();
					}
				form->NotifyOnFontChangeShadowColor();
				form->NotifyOnFontChangeStyle();
				form->UpdateHoveredControl();
				form->UnlockRepaint();
			}
		}

		void CForm::FontOnChangeColor(void *param)
		{
			CForm *form{ (CForm*)param };
			form->m_bIsFontStyleChanged = true;
			if (!form->m_bIsFontChanging)
			{
				form->LockRepaint();
				for (auto pos = form->m_aControlsRoot.begin(); pos != form->m_aControlsRoot.end(); pos++)
					if ((*pos)->m_bUseParentFont)
					{
						(*pos)->NotifyOnParentFontChangeColor();
						(*pos)->NotifyOnParentFontChangeStyle();
					}
				form->NotifyOnFontChangeColor();
				form->NotifyOnFontChangeStyle();
				form->UpdateHoveredControl();
				form->UnlockRepaint();
			}
		}

		void CForm::FontOnChangeInterpolate(void *param)
		{
			CForm *form{ (CForm*)param };
			form->m_bIsFontStyleChanged = true;
			if (!form->m_bIsFontChanging)
			{
				form->LockRepaint();
				for (auto pos = form->m_aControlsRoot.begin(); pos != form->m_aControlsRoot.end(); pos++)
					if ((*pos)->m_bUseParentFont)
					{
						(*pos)->NotifyOnParentFontChangeInterpolate();
						(*pos)->NotifyOnParentFontChangeStyle();
					}
				form->NotifyOnFontChangeInterpolate();
				form->NotifyOnFontChangeStyle();
				form->UpdateHoveredControl();
				form->UnlockRepaint();
			}
		}

		void CForm::FontOnBeginChange(void *param)
		{
			CForm *form{ (CForm*)param };
			form->LockRepaint();
			form->m_bIsFontChanging = true;
			form->m_bIsFontSizeChanged = false;
			form->m_bIsFontStyleChanged = false;
			for (auto pos = form->m_aControlsRoot.begin(); pos != form->m_aControlsRoot.end(); pos++)
				if ((*pos)->m_bUseParentFont)
					(*pos)->NotifyOnParentFontBeginChange();
			form->NotifyOnFontBeginChange();
		}

		void CForm::FontOnEndChange(void *param)
		{
			CForm *form{ (CForm*)param };
			form->m_bIsFontChanging = false;
			for (auto pos = form->m_aControlsRoot.begin(); pos != form->m_aControlsRoot.end(); pos++)
				if ((*pos)->m_bUseParentFont)
				{
					(*pos)->NotifyOnParentFontEndChange();
					if (form->m_bIsFontSizeChanged)
						(*pos)->NotifyOnParentFontChangeSize();
					else if (form->m_bIsFontStyleChanged)
						(*pos)->NotifyOnParentFontChangeStyle();
				}
			form->NotifyOnFontEndChange();
			if (form->m_bIsFontSizeChanged)
				form->NotifyOnFontChangeSize();
			else if (form->m_bIsFontStyleChanged)
				form->NotifyOnFontChangeStyle();
			form->UpdateHoveredControl();
			form->UnlockRepaint();
		}
	#pragma endregion

	#pragma region Notifications
		void CForm::NotifyOnCreate()
		{
			OnCreate();
		}

		void CForm::NotifyOnDestroy()
		{
			OnDestroy();
		}

		void CForm::NotifyOnMove(const int x, const int y)
		{
			OnMove(x, y);
		}

		void CForm::NotifyOnRestore(const int width, const int height)
		{
			OnRestore(width, height);
		}

		void CForm::NotifyOnMinimize(const int width, const int height)
		{
			OnMinimize(width, height);
		}

		void CForm::NotifyOnMaximize(const int width, const int height)
		{
			OnMaximize(width, height);
		}

		void CForm::NotifyOnActivate(const bool byclick)
		{
			OnActivate(byclick);
		}

		void CForm::NotifyOnDeactivate()
		{
			OnDeactivate();
		}

		void CForm::NotifyOnSetFocus()
		{
			OnSetFocus();
		}

		void CForm::NotifyOnKillFocus()
		{
			OnKillFocus();
		}

		void CForm::NotifyOnEnable()
		{
			OnEnable();
		}

		void CForm::NotifyOnDisable()
		{
			OnDisable();
		}

		void CForm::NotifyOnPaint(const int left, const int top, const int right, const int bottom)
		{
			if (!m_pWindow || !m_pPresenter)
				return;
			OnPaint(left, top, right, bottom);
			if (!m_bRepaintRequired && m_pPresenter->ValidateBufferSize()) // If repaint was not really done and backbuffer size is same as window client area size
			{
				// Just present already rendered buffer data and exit
				APP_RECT clip{ left, top, right, bottom };
				m_pPresenter->Present(&clip);
				return;
			}
			Repaint(left, top, right, bottom);
		}

		void CForm::NotifyOnClose(IWindow::CLOSE_ACTION &action)
		{
			OnClose(action);
		}

		bool CForm::NotifyOnQueryEndSession()
		{

			return OnQueryEndSession();
		}

		bool CForm::NotifyOnQueryOpen()
		{

			return OnQueryOpen();
		}

		void CForm::NotifyOnEndSession(const bool ending)
		{
			OnEndSession(ending);
		}

		void CForm::NotifyOnShow()
		{
			OnShow();
		}

		void CForm::NotifyOnHide()
		{
			OnHide();
		}

		void CForm::NotifyOnDeviceModeChange()
		{
			OnDeviceModeChange();
		}

		void CForm::NotifyOnActivateApp()
		{
			OnActivateApp();
		}

		void CForm::NotifyOnDeactivateApp()
		{
			OnDeactivateApp();
		}

		void CForm::NotifyOnTimeChange()
		{
			OnTimeChange();
		}

		bool CForm::NotifyOnInputLanguageChangeRequest()
		{
			return OnInputLanguageChangeRequest();
		}

		void CForm::NotifyOnInputLanguageChange()
		{
			OnInputLanguageChange();
		}

		bool CForm::NotifyOnContextMenu(const int x, const int y)
		{
			return OnContextMenu(x, y);
		}

		void CForm::NotifyOnDisplayChange(const int width, const int height)
		{
			OnDisplayChange(width, height);
		}

		void CForm::NotifyOnKeyDown(const IWindow::KEY key)
		{
			OnKeyDown(key);
		}

		void CForm::NotifyOnKeyUp(const IWindow::KEY key)
		{
			OnKeyUp(key);
		}

		void CForm::NotifyOnChar(const wchar_t chr)
		{
			OnChar(chr);
		}

		void CForm::NotifyOnDeadChar(const wchar_t chr)
		{
			OnDeadChar(chr);
		}

		void CForm::NotifyOnSysKeyDown(const IWindow::KEY key)
		{
			OnSysKeyDown(key);
		}

		void CForm::NotifyOnSysKeyUp(const IWindow::KEY key)
		{
			OnSysKeyUp(key);
		}

		void CForm::NotifyOnSysChar(const wchar_t chr)
		{
			OnSysChar(chr);
		}

		void CForm::NotifyOnSysDeadChar(const wchar_t chr)
		{
			OnSysDeadChar(chr);
		}

		bool CForm::NotifyOnInitDialog()
		{
			return OnInitDialog();
		}

		void CForm::NotifyOnSysCommand(const IWindow::SYSTEM_COMMAND_TYPE type, const int x, const int y)
		{
			OnSysCommand(type, x, y);
		}

		void CForm::NotifyOnHScroll(const IWindow::SCROLL_TYPE type, const int pos)
		{
			OnHScroll(type, pos);
		}

		void CForm::NotifyOnVScroll(const IWindow::SCROLL_TYPE type, const int pos)
		{
			OnVScroll(type, pos);
		}

		void CForm::NotifyOnGestureZoom(const int x, const int y)
		{
			OnGestureZoom(x, y);
		}

		void CForm::NotifyOnGesturePan(const int x, const int y)
		{
			OnGesturePan(x, y);
		}

		void CForm::NotifyOnGestureRotate(const int x, const int y)
		{
			OnGestureRotate(x, y);
		}

		void CForm::NotifyOnGestureTwoFingerTap(const int x, const int y)
		{
			OnGestureTwoFingerTap(x, y);
		}

		void CForm::NotifyOnGesturePressAndTap(const int x, const int y)
		{
			OnGesturePressAndTap(x, y);
		}

		void CForm::NotifyOnGestureNotify()
		{
			OnGestureNotify();
		}

		void CForm::NotifyOnEnterIdleDialog()
		{
			OnEnterIdleDialog();
		}

		void CForm::NotifyOnEnterIdleMenu()
		{
			OnEnterIdleMenu();
		}

		void CForm::NotifyOnMouseMove(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			OnMouseMove(x, y, ctrl, left, middle, right, shift);
		}

		void CForm::NotifyOnLeftMouseButtonDown(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			OnLeftMouseButtonDown(x, y, ctrl, left, middle, right, shift);
		}

		void CForm::NotifyOnLeftMouseButtonUp(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			OnLeftMouseButtonUp(x, y, ctrl, left, middle, right, shift);
		}

		void CForm::NotifyOnLeftMouseButtonDoubleClick(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			OnLeftMouseButtonDoubleClick(x, y, ctrl, left, middle, right, shift);
		}

		void CForm::NotifyOnRightMouseButtonDown(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			OnRightMouseButtonDown(x, y, ctrl, left, middle, right, shift);
		}

		void CForm::NotifyOnRightMouseButtonUp(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			OnRightMouseButtonUp(x, y, ctrl, left, middle, right, shift);
		}

		void CForm::NotifyOnRightMouseButtonDoubleClick(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			OnRightMouseButtonDoubleClick(x, y, ctrl, left, middle, right, shift);
		}

		void CForm::NotifyOnMiddleMouseButtonDown(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			OnMiddleMouseButtonDown(x, y, ctrl, left, middle, right, shift);
		}

		void CForm::NotifyOnMiddleMouseButtonUp(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			OnMiddleMouseButtonUp(x, y, ctrl, left, middle, right, shift);
		}

		void CForm::NotifyOnMiddleMouseButtonDoubleClick(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			OnMiddleMouseButtonDoubleClick(x, y, ctrl, left, middle, right, shift);
		}

		void CForm::NotifyOnMouseVerticalWheel(const int x, const int y, const int delta, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			OnMouseVerticalWheel(x, y, delta, ctrl, left, middle, right, shift);
		}

		void CForm::NotifyOnMouseHorizontalWheel(const int x, const int y, const int delta, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			OnMouseHorizontalWheel(x, y, delta, ctrl, left, middle, right, shift);
		}

		void CForm::NotifyOnResizing(const IWindow::EDGE edge, const int left, const int top, const int right, const int bottom)
		{
			OnResizing(edge, left, top, right, bottom);
		}

		void CForm::NotifyOnLoseCapture()
		{
			OnLoseCapture();
		}

		void CForm::NotifyOnMoving(const int left, const int top, const int right, const int bottom)
		{
			OnMoving(left, top, right, bottom);
		}

		void CForm::NotifyOnEnterSizeMove()
		{
			OnEnterSizeMove();
		}

		void CForm::NotifyOnExitSizeMove()
		{
			if (m_sOldClientRect != m_pWindow->getClientRect())
				Repaint();
			OnExitSizeMove();
		}

		void CForm::NotifyOnMouseHover(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			OnMouseHover(x, y, ctrl, left, middle, right, shift);
		}

		void CForm::NotifyOnMouseLeave()
		{
			OnMouseLeave();
		}

		void CForm::NotifyOnHotKey(const bool is_desktop, const IWindow::KEY key, const bool alt, const bool ctrl, const bool shift, const bool win)
		{
			OnHotKey(is_desktop, key, alt, ctrl, shift, win);
		}

		void CForm::NotifyOnThemeChanged()
		{
			OnThemeChanged();
		}

		void CForm::NotifyOnClipboardUpdate()
		{
			OnClipboardUpdate();
		}

		void CForm::NotifyOnTimer(const unsigned int id)
		{
			OnTimer(id);
		}

		void CForm::NotifyOnNonClientMouseMove(const int x, const int y)
		{
			OnNonClientMouseMove(x, y);
		}

		void CForm::NotifyOnNonClientLeftMouseButtonDown(const int x, const int y)
		{
			OnNonClientLeftMouseButtonDown(x, y);
		}

		void CForm::NotifyOnNonClientLeftMouseButtonUp(const int x, const int y)
		{
			OnNonClientLeftMouseButtonUp(x, y);
		}

		void CForm::NotifyOnNonClientLeftMouseButtonDoubleClick(const int x, const int y)
		{
			OnNonClientLeftMouseButtonDoubleClick(x, y);
		}

		void CForm::NotifyOnNonClientRightMouseButtonDown(const int x, const int y)
		{
			OnNonClientRightMouseButtonDown(x, y);
		}

		void CForm::NotifyOnNonClientRightMouseButtonUp(const int x, const int y)
		{
			OnNonClientRightMouseButtonUp(x, y);
		}

		void CForm::NotifyOnNonClientRightMouseButtonDoubleClick(const int x, const int y)
		{
			OnNonClientRightMouseButtonDoubleClick(x, y);
		}

		void CForm::NotifyOnNonClientMiddleMouseButtonDown(const int x, const int y)
		{
			OnNonClientMiddleMouseButtonDown(x, y);
		}

		void CForm::NotifyOnNonClientMiddleMouseButtonUp(const int x, const int y)
		{
			OnNonClientMiddleMouseButtonUp(x, y);
		}

		void CForm::NotifyOnNonClientMiddleMouseButtonDoubleClick(const int x, const int y)
		{
			OnNonClientMiddleMouseButtonDoubleClick(x, y);
		}

		void CForm::NotifyOnEnterMenuLoop(const bool track_popup_menu_used)
		{
			OnEnterMenuLoop(track_popup_menu_used);
		}

		void CForm::NotifyOnExitMenuLoop(const bool is_shortcut)
		{
			OnExitMenuLoop(is_shortcut);
		}

		void CForm::NotifyOnNonClientMouseHover(const int x, const int y)
		{
			OnNonClientMouseHover(x, y);
		}

		void CForm::NotifyOnNonClientMouseLeave()
		{
			OnNonClientMouseLeave();
		}

		void CForm::NotifyOnChangeActiveControl(CControl *old_control, CControl *new_control)
		{
			OnChangeActiveControl(old_control, new_control);
		}

		void CForm::NotifyOnChangeStyle()
		{
			Repaint();
			for (auto pos = m_aControlsRoot.begin(); pos != m_aControlsRoot.end(); pos++)
				if ((*pos)->m_bUseStyle && !(*pos)->m_pStyle)
					(*pos)->NotifyOnChangeParentStyle();
			OnChangeStyle();
		}

		void CForm::NotifyOnChangeBackgroundColor()
		{
			Repaint();
			OnChangeBackgroundColor();
		}

		void CForm::NotifyOnBeforeDetachControl(CControl *control)
		{
			control->Repaint(true);
			OnBeforeDetachControl(control);
		}

		void CForm::NotifyOnDetachControl(CControl *control)
		{
			CleanCaptureKeyboardHistory();
			CleanCaptureMouseHistory();
			OnDetachControl(control);
		}

		void CForm::NotifyOnAttachControl(CControl *control)
		{
			control->UpdateRect();
			control->UpdateRectOfNextParentControl();
			control->Repaint(true);
			OnAttachControl(control);
			UpdateHoveredControl();
		}

		void CForm::NotifyOnChildControlResize(CControl *control, const APP_POINT &old_size, const APP_POINT &new_size)
		{
			OnChildControlResize(control, old_size, new_size);
			UpdateHoveredControl();
		}

		void CForm::NotifyOnChildControlMove(CControl *control, const APP_POINT &old_position, const APP_POINT &new_position)
		{
			OnChildControlMove(control, old_position, new_position);
			UpdateHoveredControl();
		}

		void CForm::NotifyOnMouseLeaveControl(CControl *control)
		{
			OnMouseLeaveControl(control);
			if (control->getCursor() != m_eCursor)
				m_pWindow->setCursor(m_eCursor);
			// TODO: Hinting
		}

		void CForm::NotifyOnMouseHoverControl(CControl *control)
		{
			OnMouseHoverControl(control);
			if (control->getCursor() != m_eCursor)
				m_pWindow->setCursor(control->m_eCursor);
			// TODO: Hinting
		}

		void CForm::NotifyOnUpdateComponent(CComponent *component)
		{
			LockRepaint();
			for (auto pos = m_aComponents.begin(); pos != m_aComponents.end(); pos++)
				(*pos)->NotifyOnUpdateComponent(component);
			for (auto pos = m_aControlsRoot.begin(); pos != m_aControlsRoot.end(); pos++)
				(*pos)->NotifyOnUpdateComponent(component);
			OnUpdateComponent(component);
			UnlockRepaint();
		}

		void CForm::NotifyOnUpdateControl(CControl *control)
		{
			LockRepaint();
			for (auto pos = m_aComponents.begin(); pos != m_aComponents.end(); pos++)
				(*pos)->NotifyOnUpdateControl(control);
			for (auto pos = m_aControlsRoot.begin(); pos != m_aControlsRoot.end(); pos++)
				(*pos)->NotifyOnUpdateControl(control);
			OnUpdateControl(control);
			UnlockRepaint();
		}

		void CForm::NotifyOnFontChangeName()
		{
			OnFontChangeName();
		}

		void CForm::NotifyOnFontChangeHeight()
		{
			OnFontChangeHeight();
		}

		void CForm::NotifyOnFontChangeWeight()
		{
			OnFontChangeWeight();
		}

		void CForm::NotifyOnFontChangeItalic()
		{
			OnFontChangeItalic();
		}

		void CForm::NotifyOnFontChangeUnderline()
		{
			OnFontChangeUnderline();
		}

		void CForm::NotifyOnFontChangeStrikeOut()
		{
			OnFontChangeStrikeOut();
		}

		void CForm::NotifyOnFontChangeWidth()
		{
			OnFontChangeWidth();
		}

		void CForm::NotifyOnFontChangeCharSet()
		{
			OnFontChangeCharSet();
		}

		void CForm::NotifyOnFontChangeQuality()
		{
			OnFontChangeQuality();
		}

		void CForm::NotifyOnFontChangePitchAndFamily()
		{
			OnFontChangePitchAndFamily();
		}

		void CForm::NotifyOnFontChangeOrientation()
		{
			OnFontChangeOrientation();
		}

		void CForm::NotifyOnFontChangeDistance()
		{
			OnFontChangeDistance();
		}

		void CForm::NotifyOnFontChangeShadow()
		{
			OnFontChangeShadow();
		}

		void CForm::NotifyOnFontChangeShadowShift()
		{
			OnFontChangeShadowShift();
		}

		void CForm::NotifyOnFontChangeShadowBlur()
		{
			OnFontChangeShadowBlur();
		}

		void CForm::NotifyOnFontChangeShadowColor()
		{
			OnFontChangeShadowColor();
		}

		void CForm::NotifyOnFontChangeColor()
		{
			OnFontChangeColor();
		}

		void CForm::NotifyOnFontChangeInterpolate()
		{
			OnFontChangeInterpolate();
		}

		void CForm::NotifyOnFontBeginChange()
		{
			OnFontBeginChange();
		}

		void CForm::NotifyOnFontEndChange()
		{
			OnFontEndChange();
		}

		void CForm::NotifyOnFontChangeSize()
		{
			OnFontChangeSize();
		}

		void CForm::NotifyOnFontChangeStyle()
		{
			OnFontChangeStyle();
		}
	#pragma endregion

	#pragma region Helpers
		bool CForm::ProcessSpecialKeyDown(const IWindow::KEY key)
		{
			if (key == IWindow::keyTab)
			{
				bool ctrl, shift, alt;
				m_pWindow->getControlKeys(ctrl, shift, alt);
				if (!ctrl && !alt)
				{
					if (shift)
					{
						CControl *control = SearchPrevControl(m_pActiveControl ? m_pActiveControl->m_iTabOrder : CalculateTotalControlCount(), true);
						if (!control)
							control = SearchPrevControl(CalculateTotalControlCount(), true);
						if (control && m_pActiveControl != control)
						{
							setActiveControl(control);
							m_bSpecialKeyProcessed = true;
						}
					}
					else
					{
						CControl *control = SearchNextControl(m_pActiveControl ? m_pActiveControl->m_iTabOrder : -1, true);
						if (!control)
							control = SearchNextControl(-1, true);
						if (control && m_pActiveControl != control)
						{
							setActiveControl(control);
							m_bSpecialKeyProcessed = true;
						}
					}
					return true;
				}
			}
			return false;
		}

		void CForm::ProcessDownHotkeys(const IWindow::KEY key)
		{
			if (m_aHotkeys.size() > 0)
			{
				bool ctrl, alt, shift;
				m_pWindow->getControlKeys(ctrl, shift, alt);
				for (auto pos = m_aHotkeys.begin(); pos != m_aHotkeys.end(); pos++)
					if ((*pos).IsDown && (*pos).Key == key && (*pos).Ctrl == ctrl && (*pos).Alt == alt && (*pos).Shift == shift)
						(*pos).Component->NotifyOnHotkey(key, ctrl, alt, shift, true);
			}
		}

		void CForm::ProcessUpHotkeys(const IWindow::KEY key)
		{
			if (m_aHotkeys.size() > 0)
			{
				bool ctrl, alt, shift;
				m_pWindow->getControlKeys(ctrl, shift, alt);
				for (auto pos = m_aHotkeys.begin(); pos != m_aHotkeys.end(); pos++)
					if (!(*pos).IsDown && (*pos).Key == key && (*pos).Ctrl == ctrl && (*pos).Alt == alt && (*pos).Shift == shift)
						(*pos).Component->NotifyOnHotkey(key, ctrl, alt, shift, false);
			}
		}

		void CForm::SendNotify_ParentResize()
		{
			for (auto pos = m_aControlsRoot.begin(); pos != m_aControlsRoot.end(); pos++)
				(*pos)->NotifyOnParentResize();
		}

		void CForm::CleanCaptureKeyboardHistory()
		{
			if (m_aCaptureKeyboardControls.size() > 0)
			{
				size_t pos{ m_aCaptureKeyboardControls.size() };
				do
				{
					pos--;
					if (m_aCaptureKeyboardControls[pos]->m_pForm != this || !m_aCaptureKeyboardControls[pos]->getVisibleWithParents() || !m_aCaptureKeyboardControls[pos]->getEnabledWithParents())
						m_aCaptureKeyboardControls.erase(m_aCaptureKeyboardControls.begin() + pos);
				} while (pos > 0);
			}
		}

		void CForm::CleanCaptureMouseHistory()
		{
			if (m_aCaptureMouseControls.size() > 0)
			{
				size_t pos{ m_aCaptureMouseControls.size() };
				do
				{
					pos--;
					if (m_aCaptureMouseControls[pos]->m_pForm != this || !m_aCaptureMouseControls[pos]->getVisibleWithParents() || !m_aCaptureMouseControls[pos]->getEnabledWithParents())
						m_aCaptureMouseControls.erase(m_aCaptureMouseControls.begin() + pos);
				} while (pos > 0);
			}
		}
	#pragma endregion

	#pragma region Getters
		String CForm::getClassName() const
		{
			return m_sClassName;
		}

		IWindow *CForm::getWindow()
		{
			return m_pWindow;
		}

		IPresenter *CForm::getPresenter()
		{
			return m_pPresenter;
		}

		CImageManager *CForm::getImageManager()
		{
			return m_pImageManager;
		}

		IFont *CForm::getFont()
		{
			return m_pFont;
		}

		CStyle *CForm::getStyle()
		{
			return m_pStyle;
		}

		size_t CForm::getComponentCount() const
		{
			return m_aComponents.size();
		}

		CComponent *CForm::getComponent(const int index)
		{
			if (index >=0 && index < (int)m_aComponents.size())
			{
				SortComponents();
				return m_aComponents[index];
			}
			return nullptr;
		}

		CComponent *CForm::getComponentByName(const String &name)
		{
			return getComponent(FindComponentIndex(name));
		}

		size_t CForm::getControlCount() const
		{
			return m_aControls.size();
		}

		CControl *CForm::getControl(const int index)
		{
			if (index >= 0 && index < (int)m_aControls.size())
			{
				SortControls();
				return m_aControls[index];
			}
			return nullptr;
		}

		CControl *CForm::getControlByName(const String &name)
		{
			return getControl(FindControlIndex(name));
		}

		CControl *CForm::getControlAtPosition(const int x, const int y)
		{
			CControl *control;
			if (m_pCaptureMouseControl)
				if (control = m_pCaptureMouseControl->getControlAtPosition(x, y))
					return control;
			for (int index = m_aControlsRoot.size() - 1; index >= 0; index--)
			{
				control = m_aControlsRoot[index]->getControlAtPosition(x, y);
				if (control)
					return control;
			}
			return nullptr;
		}

		size_t CForm::getRootControlCount() const
		{
			return m_aControlsRoot.size();
		}

		CControl *CForm::getRootControl(const int index)
		{
			if (index >= 0 && index < (int)m_aControlsRoot.size())
				return m_aControlsRoot[index];
			return nullptr;
		}

		CControl *CForm::getActiveControl() const
		{
			return m_pActiveControl;
		}

		CControl *CForm::getCaptureKeyboardControl() const
		{
			return m_pCaptureKeyboardControl;
		}

		CControl *CForm::getCaptureMouseControl() const
		{
			return m_pCaptureMouseControl;
		}

		CControl *CForm::getHoveredControl()
		{
			return m_pHoveredControl;
		}

		APP_COLOR CForm::getBackgroundColor() const
		{
			return m_sBackgroundColor;
		}

		bool CForm::getRepaintRequired() const
		{
			return m_bRepaintRequired;
		}

		CURSOR_TYPE CForm::getCursor() const
		{
			return m_eCursor;
		}
	#pragma endregion

	#pragma region Setters
		CForm *CForm::setStyle(CStyle *style)
		{
			if (style != m_pStyle)
			{
				LockRepaint();
				m_pStyle = style;
				if (m_pStyle && m_pFont)
				{
					CStyleFont *font{ m_pStyle->getFontByName(m_sClassName) };
					if (font)
					{
						m_pFont
							->BeginChange()
							->setName(font->getName())
							->setHeight(font->getHeight())
							->setWeight(font->getWeight())
							->setItalic(font->getItalic())
							->setUnderline(font->getUnderline())
							->setStrikeOut(font->getStrikeOut())
							->setWidth(font->getWidth())
							->setCharSet(font->getCharSet())
							->setQuality(font->getQuality())
							->setPitchAndFamily(font->getPitchAndFamily())
							->setOrientation(font->getOrientation())
							->setDistance(font->getDistance())
							->setShadow(font->getShadow())
							->setShadowShift(font->getShadowShift())
							->setShadowBlur(font->getShadowBlur())
							->setShadowColor(font->getShadowColor())
							->setColor(font->getColor())
							->setInterpolate(font->getInterpolate())
							->EndChange();
					}
				}
				NotifyOnChangeStyle();
				UpdateHoveredControl();
				UnlockRepaint();
			}
			return this;
		}

		CForm *CForm::setFont(IFont *value)
		{
			if (m_pFont && value)
			{
				LockRepaint();
				m_pFont
					->BeginChange()
					->setName(value->getName())
					->setHeight(value->getHeight())
					->setWeight(value->getWeight())
					->setItalic(value->getItalic())
					->setUnderline(value->getUnderline())
					->setStrikeOut(value->getStrikeOut())
					->setWidth(value->getWidth())
					->setCharSet(value->getCharSet())
					->setQuality(value->getQuality())
					->setPitchAndFamily(value->getPitchAndFamily())
					->setOrientation(value->getOrientation())
					->setDistance(value->getDistance())
					->setShadow(value->getShadow())
					->setShadowShift(value->getShadowShift())
					->setShadowBlur(value->getShadowBlur())
					->setShadowColor(value->getShadowColor())
					->setColor(value->getColor())
					->setInterpolate(value->getInterpolate())
					->EndChange();
				UpdateHoveredControl();
				UnlockRepaint();
			}
			return this;
		}

		CForm *CForm::setActiveControl(CControl *value)
		{
			// Check control already active
			if (value == m_pActiveControl)
				return this;
			// Check control can be focused
			if (value && (!value->m_bAcceptFocus || value->m_pForm != this || !value->getVisibleWithParents() || !value->getEnabledWithParents()))
				return this;
			// Start repaint with repainting of control's current rects
			LockRepaint();
			// Notify controls about changes
			NotifyOnChangeActiveControl(m_pActiveControl, value);
			CControl *ctrl{ m_pActiveControl };
			if (m_pActiveControl)
			{
				m_pActiveControl->NotifyOnKillFocus();
				m_pActiveControl = nullptr;
			}
			if (value)
			{
				m_pActiveControl = value;
				m_pActiveControl->NotifyOnSetFocus(ctrl);
			}
			// Set active control
			m_pOldActiveControl = nullptr;
			// Finish repaint
			UpdateHoveredControl();
			UnlockRepaint();
			return this;
		}

		CForm *CForm::setCursor(const CURSOR_TYPE value)
		{
			if (value != m_eCursor)
			{
				m_eCursor = value;
				if (m_pWindow)
					m_pWindow->setCursor(m_eCursor);
			}
			return this;
		}

		CForm *CForm::setBackgroundColor(const APP_COLOR &value)
		{
			if (value != m_sBackgroundColor)
			{
				m_sBackgroundColor = value;
				NotifyOnChangeBackgroundColor();
			}
			return this;
		}
	#pragma endregion

	#pragma region Components
		void CForm::SortComponents()
		{
			if (!m_bIsComponentsSorted)
			{
				std::sort(m_aComponents.begin(), m_aComponents.end(), [](const CComponent *a, const CComponent *b) { return a->m_sName < b->m_sName; });
				m_bIsComponentsSorted = true;
			}
		}

		int CForm::FindComponentIndex(const String &name)
		{
			SortComponents();
			m_pControlForSearch->m_sName = name;
			auto pos = std::lower_bound(m_aComponents.begin(), m_aComponents.end(), m_pControlForSearch, [](const CComponent *a, const CComponent *b) { return a->m_sName < b->m_sName; });
			if (pos == m_aComponents.end())
				return -1;
			if ((*pos)->m_sName != name)
				return -1;
			return pos - m_aComponents.begin();
		}

		bool CForm::ValidateComponentName(const String &name, CComponent *exclude)
		{
			int index = FindComponentIndex(name);
			if (index < 0)
				return true;
			if (m_aComponents[index] == exclude)
				return true;
			return false;
		}

		void CForm::AttachComponent(CComponent *component)
		{
			// Check component already on form
			if (!component || component->m_pForm == this)
				return;
			component->setForm(this);
		}

		void CForm::DeleteComponent(const size_t index)
		{
			if (index < m_aComponents.size())
			{
				SortComponents();
				delete m_aComponents[index];
			}
		}

		void CForm::DeleteComponent(CComponent *component)
		{
			if (!component || component->m_pForm != this)
				return;
			delete component;
		}

		void CForm::DetachComponent(CComponent *component)
		{
			// Component should belongs to the form
			if (!component || component->m_pForm != this)
				return;
			component->setForm(nullptr);
		}

		void CForm::DeleteComponents()
		{
			while (m_aComponents.size() > 0)
				DeleteComponent((size_t)0);
		}
	#pragma endregion

	#pragma region Controls
		void CForm::SortControls()
		{
			if (!m_bIsControlsSorted)
			{
				std::sort(m_aControls.begin(), m_aControls.end(), [](const CControl *a, const CControl *b) { return a->m_sName < b->m_sName; });
				m_bIsControlsSorted = true;
			}
		}

		int CForm::FindControlIndex(const String &name)
		{
			SortControls();
			m_pControlForSearch->m_sName = name;
			auto pos = std::lower_bound(m_aControls.begin(), m_aControls.end(), m_pControlForSearch, [](const CControl *a, const CControl *b) { return a->m_sName < b->m_sName; });
			if (pos == m_aControls.end())
				return -1;
			if ((*pos)->m_sName != name)
				return -1;
			return pos - m_aControls.begin();
		}

		bool CForm::ValidateControlName(const String &name, CControl *exclude)
		{
			int index = FindControlIndex(name);
			if (index < 0)
				return true;
			if (m_aControls[index] == exclude)
				return true;
			return false;
		}

		void CForm::UpdateHoveredControl()
		{
			int x, y;
			// Check if position can be get and get successfully
			if (!m_pWindow || !m_pWindow->getCursorPosition(x, y))
			{
				if (m_pHoveredControl)
				{
					NotifyOnMouseLeaveControl(m_pHoveredControl);
					m_pHoveredControl->NotifyOnMouseLeave();
					m_pHoveredControl = nullptr;
				}
				return;
			}
			// Check position is out of window client rect
			APP_RECT client = m_pWindow->getClientRect();
			if (x < client.Left || x >= client.Right || y < client.Top || y >= client.Bottom)
			{
				if (m_pHoveredControl)
				{
					NotifyOnMouseLeaveControl(m_pHoveredControl);
					m_pHoveredControl->NotifyOnMouseLeave();
					m_pHoveredControl = nullptr;
				}
				return;
			}
			// Update hover
			CControl *control = getControlAtPosition(x, y);
			if (control != m_pHoveredControl)
			{
				if (m_pHoveredControl)
				{
					NotifyOnMouseLeaveControl(m_pHoveredControl);
					m_pHoveredControl->NotifyOnMouseLeave();
				}
				m_pHoveredControl = control;
				if (m_pHoveredControl)
				{
					NotifyOnMouseHoverControl(m_pHoveredControl);
					m_pHoveredControl->NotifyOnMouseHover();
				}
			}
		}

		void CForm::ActivateControlAtClick(const int x, const int y)
		{
			// Get control at position and check it can have focus
			CControl *control = getControlAtPosition(x, y), *parent;
			while (true)
			{
				if (!control)
					break;
				if (!control->m_bEnabled)
				{
					control = control->m_pParent;
					continue;
				}
				if (!control->m_bAcceptFocus)
				{
					control = control->m_pParent;
					continue;
				}
				parent = control->m_pParent;
				while (parent && parent->m_bEnabled)
					parent = parent->m_pParent;
				if (parent && !parent->m_bEnabled)
					control = nullptr;
				break;
			}
			// Set focus to control if it exists and accept focus and focus is on another control
			if (control)
				setActiveControl(control);
		}

		size_t CForm::CalculateTotalControlCount(CControl *control)
		{
			size_t result{ 1 };
			for (auto pos = control->m_aControls.begin(); pos != control->m_aControls.end(); pos++)
				result += CalculateTotalControlCount(*pos);
			return result;
		}

		size_t CForm::CalculateTotalControlCount()
		{
			size_t result{ 0 };
			for (auto pos = m_aControlsRoot.begin(); pos != m_aControlsRoot.end(); pos++)
				result += CalculateTotalControlCount(*pos);
			return result;
		}

		void CForm::UpdateTabOrders(CControl *control, const size_t old_order, const size_t new_order)
		{
			if (new_order < old_order)
			{
				if (control->m_iTabOrder >= new_order && control->m_iTabOrder < old_order)
					control->m_iTabOrder++;
			}
			else
				if (control->m_iTabOrder > old_order && control->m_iTabOrder <= new_order)
					control->m_iTabOrder--;
			for (auto pos = control->m_aControls.begin(); pos != control->m_aControls.end(); pos++)
				UpdateTabOrders(*pos, old_order, new_order);
		}

		void CForm::UpdateTabOrders(const size_t old_order, const size_t new_order)
		{
			for (auto pos = m_aControlsRoot.begin(); pos != m_aControlsRoot.end(); pos++)
				UpdateTabOrders(*pos, old_order, new_order);
		}

		CControl *CForm::SearchPrevControl(CControl *control, const int order, CControl *best, const bool tab_stop)
		{
			if (!control->m_bVisible || !control->m_bEnabled || !control->m_bAcceptFocus)
				return best;
			if (!tab_stop || control->m_bTabStop)
				if ((int)control->m_iTabOrder < order)
					if (!best || best->m_iTabOrder < control->m_iTabOrder)
						best = control;
			for (auto pos = control->m_aControls.begin(); pos != control->m_aControls.end(); pos++)
				best = SearchPrevControl(*pos, order, best, tab_stop);
			return best;
		}

		CControl *CForm::SearchPrevControl(const int order, const bool tab_stop)
		{
			CControl *best = nullptr;
			for (auto pos = m_aControlsRoot.begin(); pos != m_aControlsRoot.end(); pos++)
				best = SearchPrevControl(*pos, order, best, tab_stop);
			return best;
		}

		CControl *CForm::SearchNextControl(CControl *control, const int order, CControl *best, const bool tab_stop)
		{
			if (!control->m_bVisible || !control->m_bEnabled || !control->m_bAcceptFocus)
				return best;
			if (!tab_stop || control->m_bTabStop)
				if ((int)control->m_iTabOrder > order)
					if (!best || best->m_iTabOrder > control->m_iTabOrder)
						best = control;
			for (auto pos = control->m_aControls.begin(); pos != control->m_aControls.end(); pos++)
				best = SearchNextControl(*pos, order, best, tab_stop);
			return best;
		}

		CControl *CForm::SearchNextControl(const int order, const bool tab_stop)
		{
			CControl *best = nullptr;
			for (auto pos = m_aControlsRoot.begin(); pos != m_aControlsRoot.end(); pos++)
				best = SearchNextControl(*pos, order, best, tab_stop);
			return best;
		}

		void CForm::AttachControl(CControl *control)
		{
			// Check if control is on form already or it cannot be on any form
			if (!control || control->m_pForm == this || !control->m_bAcceptForm)
				return;
			control->setForm(this);
		}

		void CForm::DeleteControl(const size_t index)
		{
			if (index < m_aControls.size())
			{
				SortControls();
				delete m_aControls[index];
			}
		}

		void CForm::DeleteControl(CControl *control)
		{
			if (!control || control->m_pForm != this)
				return;
			delete control;
		}

		void CForm::DeleteControls()
		{
			LockRepaint();
			while (m_aControlsRoot.size() > 0)
				DeleteControl((size_t)0);
			UnlockRepaint();
		}

		void CForm::DetachControl(CControl *control)
		{
			// Control should belongs to the form
			if (!control || control->m_pForm != this)
				return;
			control->setForm(nullptr);
		}

		void CForm::ActivatePrevControl()
		{
			CControl *control = SearchPrevControl(m_pActiveControl ? m_pActiveControl->m_iTabOrder : CalculateTotalControlCount(), false);
			if (control)
				setActiveControl(control);
		}

		void CForm::ActivateNextControl()
		{
			CControl *control = SearchNextControl(m_pActiveControl ? m_pActiveControl->m_iTabOrder : -1, false);
			if (control)
				setActiveControl(control);
		}

		void CForm::CaptureKeyboard(CControl *control)
		{
			// Check control is really changing and if new control exists it should be on this form
			if (control == m_pCaptureKeyboardControl || (control && control->m_pForm != this))
				return;
			// Change control
			LockRepaint();
			if (m_pCaptureKeyboardControl)
				m_pCaptureKeyboardControl->NotifyOnKillCaptureKeyboard();
			m_pCaptureKeyboardControl = control;
			if (m_pCaptureKeyboardControl)
			{
				m_aCaptureKeyboardControls.push_back(m_pCaptureKeyboardControl);
				m_pCaptureKeyboardControl->NotifyOnSetCaptureKeyboard();
			}
			else
				m_aCaptureKeyboardControls.clear();
			UpdateHoveredControl();
			UnlockRepaint();
		}

		void CForm::CaptureMouse(CControl *control)
		{
			// Check control is really changing and if new control exists it should be on this form
			if (control == m_pCaptureMouseControl || (control && control->m_pForm != this))
				return;
			// Change control
			LockRepaint();
			if (m_pCaptureMouseControl)
				m_pCaptureMouseControl->NotifyOnKillCaptureMouse();
			m_pCaptureMouseControl = control;
			if (m_pCaptureMouseControl)
			{
				m_aCaptureMouseControls.push_back(m_pCaptureMouseControl);
				m_pCaptureMouseControl->NotifyOnSetCaptureMouse();
			}
			else
				m_aCaptureMouseControls.clear();
			UpdateHoveredControl();
			UnlockRepaint();
		}

		void CForm::ReleaseCaptureKeyboard()
		{
			if (m_pCaptureKeyboardControl)
			{
				LockRepaint();
				if (m_aCaptureKeyboardControls.size() > 0)
					m_aCaptureKeyboardControls.erase(m_aCaptureKeyboardControls.end() - 1);
				CleanCaptureKeyboardHistory();
				m_pCaptureKeyboardControl->NotifyOnKillCaptureKeyboard();
				if (m_aCaptureKeyboardControls.size() > 0)
				{
					m_pCaptureKeyboardControl = m_aCaptureKeyboardControls[m_aCaptureKeyboardControls.size() - 1];
					m_pCaptureKeyboardControl->NotifyOnSetCaptureKeyboard();
				}
				else
					m_pCaptureKeyboardControl = nullptr;
				UnlockRepaint();
			}
		}

		void CForm::ReleaseCaptureMouse()
		{
			if (m_pCaptureMouseControl)
			{
				LockRepaint();
				if (m_aCaptureMouseControls.size() > 0)
					m_aCaptureMouseControls.erase(m_aCaptureMouseControls.end() - 1);
				CleanCaptureMouseHistory();
				m_pCaptureMouseControl->NotifyOnKillCaptureMouse();
				if (m_aCaptureMouseControls.size() > 0)
				{
					m_pCaptureMouseControl = m_aCaptureMouseControls[m_aCaptureMouseControls.size() - 1];
					m_pCaptureMouseControl->NotifyOnSetCaptureMouse();
				}
				else
					m_pCaptureMouseControl = nullptr;
				UnlockRepaint();
			}
		}

		size_t CForm::FindMaxZIndex(const CControl *exclude) const
		{
			size_t result{ 0 };
			for (auto pos = m_aControlsRoot.begin(); pos != m_aControlsRoot.end(); pos++)
				if ((*pos) != exclude && (*pos)->m_iZIndex > result)
					result = (*pos)->m_iZIndex;
			return result + 1;
		}
	#pragma endregion

	#pragma region Timers
		unsigned int CForm::AddTimer(void(*callback)(void *param), void *param, const unsigned int interval)
		{
			if (!m_pWindow || !callback)
				return 0;
			TIMER result{ callback, param, m_aTimers.size() > 0 ? m_aTimers[m_aTimers.size() - 1].Id : 1 };
			result.Id = m_pWindow->CreateTimer(result.Id, interval);
			if (result.Id)
				m_aTimers.push_back(result);
			return result.Id;
		}

		bool CForm::DeleteTimer(const unsigned int id)
		{
			if (!m_pWindow)
				return false;
			for (auto pos = m_aTimers.begin(); pos != m_aTimers.end(); pos++)
				if ((*pos).Id == id)
				{
					m_pWindow->DeleteTimer((*pos).Id);
					m_aTimers.erase(pos);
					return true;
				}
			return false;
		}

		void CForm::DeleteTimers()
		{
			if (m_pWindow)
			{
				for (auto pos = m_aTimers.begin(); pos != m_aTimers.end(); pos++)
					m_pWindow->DeleteTimer((*pos).Id);
				m_aTimers.clear();
			}
		}

		bool CForm::ResetTimer(const unsigned int id, const unsigned int interval)
		{
			if (!m_pWindow)
				return false;
			for (auto pos = m_aTimers.begin(); pos != m_aTimers.end(); pos++)
				if ((*pos).Id == id)
				{
					if (!m_pWindow->CreateTimer((*pos).Id, interval))
						return false;
					return true;
				}
			return false;
		}
	#pragma endregion

	#pragma region Render
		void CForm::LockRepaint()
		{
			if (m_iRepaintLockCount == 0)
			{
				m_sRepaintRect = { 0, 0, 0, 0 }; // Repaint area is empty
				m_bRepaintRequired = false;
			}
			m_iRepaintLockCount++;
		}

		void CForm::UnlockRepaint()
		{
			if (!m_iRepaintLockCount)
				return;
			m_iRepaintLockCount--;
			if (!m_iRepaintLockCount && m_bRepaintRequired)
				Repaint(m_sRepaintRect);
		}

		void CForm::Repaint()
		{
			Repaint({ 0, 0, -1, -1 });
		}

		void CForm::Repaint(const int left, const int top, const int right, const int bottom)
		{
			Repaint({ left, top, right, bottom });
		}

		void CForm::Repaint(const APP_RECT &rect)
		{
			if (m_sRepaintRect.IsValid()) // If repaint area is not valid, it means all buffer should be repainter. Otherwise perform another checks
			{
				if (!rect.IsValid()) // Repaint all client area if clip rect is not valid
					m_sRepaintRect = { 0, 0, -1, -1 };
				else if (m_sRepaintRect.IsEmpty()) // If current clip rect is empty, use specified clip rect
					m_sRepaintRect = rect;
				else // Extend current clip rect to include specified clip rect
					m_sRepaintRect += rect;
			}
			if (m_iRepaintLockCount)
			{
				m_bRepaintRequired = true;
				return;
			}
			Render();
		}

		void CForm::Render()
		{
			if (!m_pWindow || !m_pPresenter)
				return;
			// Setup
			APP_RECT rect = m_pWindow->getClientRect();
			if (!m_pPresenter->ValidateBufferSize())
				m_sRepaintRect = { 0, 0, -1, -1 };
			// Calculate repaint rect
			APP_RECT clip{ 0, 0, rect.Width(), rect.Height() };
			if (m_sRepaintRect.IsValid())
				if (m_sRepaintRect.IsEmpty()) // Repaint is not required
					return;
				else
					clip *= m_sRepaintRect; // Repain rect is intersection of repain rect and actual buffer size
			// Clear
			m_pPresenter->FillRect(m_sBackgroundColor, clip, clip, clip, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, 0, graphics::bplInside, nullptr, nullptr, false);
			// Multipass render controls
			size_t z_current, z_next{ 0 };
			do
			{
				z_current = z_next;
				for (auto pos = m_aControlsRoot.begin(); pos != m_aControlsRoot.end(); pos++)
					if ((*pos)->m_iZIndex == z_current)
					{
						if (std::find(m_aCaptureMouseControls.begin(), m_aCaptureMouseControls.end(), *pos) == m_aCaptureMouseControls.end())
							(*pos)->Render(clip);
					}
					else if ((*pos)->m_iZIndex > z_current)
						if (z_next == z_current)
							z_next = (*pos)->m_iZIndex;
						else
							z_next = std::min(z_next, (*pos)->m_iZIndex);
			} while (z_next != z_current);
			for (auto pos = m_aCaptureMouseControls.begin(); pos != m_aCaptureMouseControls.end(); pos++)
				(*pos)->Render(clip);
			// Present
			if (m_pWindow->IsCaretVisible())
			{
				m_pWindow->HideCaret();
				m_pPresenter->Present(&clip);
				m_pWindow->ShowCaret();
			}
			else
				m_pPresenter->Present(&clip);
			// Reset repaint area
			m_sRepaintRect = { 0, 0, 0, 0 };
		}
	#pragma endregion

	#pragma region Hotkeys
		bool CForm::RegisterHotkey(CComponent *component, const IWindow::KEY key, const bool ctrl, const bool alt, const bool shift, const bool is_down)
		{
			if (!component || component->m_pForm != this)
				return false;
			for (auto pos = m_aHotkeys.begin(); pos != m_aHotkeys.end(); pos++)
				if ((*pos).Component == component && (*pos).Key == key && (*pos).Ctrl == ctrl && (*pos).Alt == alt && (*pos).Shift == shift && (*pos).IsDown == is_down)
					return true;
			m_aHotkeys.push_back({ component, key, ctrl, alt, shift, is_down });
			return true;
		}

		void CForm::UnregisterHotkey(CComponent *component, const IWindow::KEY key, const bool ctrl, const bool alt, const bool shift, const bool is_down)
		{
			if (!component)
				return;
			for (auto pos = m_aHotkeys.begin(); pos != m_aHotkeys.end(); pos++)
				if ((*pos).Component == component && (*pos).Key == key && (*pos).Ctrl == ctrl && (*pos).Alt == alt && (*pos).Shift == shift && (*pos).IsDown == is_down)
				{
					m_aHotkeys.erase(pos);
					return;
				}
		}

		void CForm::UnregisterHotkeys(CComponent *component)
		{
			if (!component)
				return;
			auto pos{ m_aHotkeys.begin() };
			while (pos != m_aHotkeys.end())
				if ((*pos).Component == component)
					pos = m_aHotkeys.erase(pos);
				else
					pos++;
		}
	#pragma endregion
	}
}