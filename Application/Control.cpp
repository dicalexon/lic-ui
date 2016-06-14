// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#include "Control.h"
#include "Form.h"
#include "StyleFont.h"
#include "Style.h"
#include "Presenter.h"

namespace licui
{
	namespace application
	{
#pragma region Construction/Destruction/Initialization
		CControl::CControl() :
			CComponent(),
			m_fOnKeyDown{ nullptr },
			m_fOnKeyUp{ nullptr },
			m_fOnChar{ nullptr },
			m_fOnDeadChar{ nullptr },
			m_fOnSysKeyDown{ nullptr },
			m_fOnSysKeyUp{ nullptr },
			m_fOnSysChar{ nullptr },
			m_fOnSysDeadChar{ nullptr },
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
			m_fOnChangeUseParentFont{ nullptr },
			m_fOnParentFontChangeName{ nullptr },
			m_fOnParentFontChangeHeight{ nullptr },
			m_fOnParentFontChangeWeight{ nullptr },
			m_fOnParentFontChangeItalic{ nullptr },
			m_fOnParentFontChangeUnderline{ nullptr },
			m_fOnParentFontChangeStrikeOut{ nullptr },
			m_fOnParentFontChangeWidth{ nullptr },
			m_fOnParentFontChangeCharSet{ nullptr },
			m_fOnParentFontChangeQuality{ nullptr },
			m_fOnParentFontChangePitchAndFamily{ nullptr },
			m_fOnParentFontChangeOrientation{ nullptr },
			m_fOnParentFontChangeDistance{ nullptr },
			m_fOnParentFontChangeShadow{ nullptr },
			m_fOnParentFontChangeShadowShift{ nullptr },
			m_fOnParentFontChangeShadowBlur{ nullptr },
			m_fOnParentFontChangeShadowColor{ nullptr },
			m_fOnParentFontChangeColor{ nullptr },
			m_fOnParentFontChangeInterpolate{ nullptr },
			m_fOnParentFontBeginChange{ nullptr },
			m_fOnParentFontEndChange{ nullptr },
			m_fOnParentFontChangeSize{ nullptr },
			m_fOnParentFontChangeStyle{ nullptr },
			m_fOnFontChangeName{ nullptr },
			m_fOnFontChangeHeight{ nullptr },
			m_fOnFontChangeWeight{ nullptr },
			m_fOnFontChangeItalic{ nullptr },
			m_fOnFontChangeUnderline{ nullptr },
			m_fOnFontChangeStrikeOut{ nullptr },
			m_fOnFontChangeWidth{ nullptr },
			m_fOnFontChangeCharSet{ nullptr },
			m_fOnFontChangeQuality{ nullptr },
			m_fOnFontChangePitchAndFamily{ nullptr },
			m_fOnFontChangeOrientation{ nullptr },
			m_fOnFontChangeDistance{ nullptr },
			m_fOnFontChangeShadow{ nullptr },
			m_fOnFontChangeShadowShift{ nullptr },
			m_fOnFontChangeShadowBlur{ nullptr },
			m_fOnFontChangeShadowColor{ nullptr },
			m_fOnFontChangeColor{ nullptr },
			m_fOnFontChangeInterpolate{ nullptr },
			m_fOnFontBeginChange{ nullptr },
			m_fOnFontEndChange{ nullptr },
			m_fOnFontChangeSize{ nullptr },
			m_fOnFontChangeStyle{ nullptr },
			m_fOnMouseHover{ nullptr },
			m_fOnMouseLeave{ nullptr },
			m_fOnKillFocus{ nullptr },
			m_fOnSetFocus{ nullptr },
			m_fOnResetFocus{ nullptr },
			m_fOnKillCaptureKeyboard{ nullptr },
			m_fOnKillCaptureMouse{ nullptr },
			m_fOnSetCaptureKeyboard{ nullptr },
			m_fOnSetCaptureMouse{ nullptr },
			m_fOnChangeParentStyle{ nullptr },
			m_fOnChangeStyle{ nullptr },
			m_fOnShow{ nullptr },
			m_fOnBeforeHide{ nullptr },
			m_fOnHide{ nullptr },
			m_fOnEnable{ nullptr },
			m_fOnDisable{ nullptr },
			m_fOnAttachControl{ nullptr },
			m_fOnBeforeDetachControl{ nullptr },
			m_fOnDetachControl{ nullptr },
			m_fOnPaint{ nullptr },
			m_fOnParentResize{ nullptr },
			m_fOnParentMove{ nullptr },
			m_fOnBeforeResize{ nullptr },
			m_fOnResize{ nullptr },
			m_fOnBeforeMove{ nullptr },
			m_fOnMove{ nullptr },
			m_fOnChildControlResize{ nullptr },
			m_fOnChildControlMove{ nullptr },
			m_fOnBeforeDetachFromControl{ nullptr },
			m_fOnDetachFromControl{ nullptr },
			m_fOnAttachToControl{ nullptr },
			m_pParent{ nullptr },
			m_iTabOrder{ 0 },
			m_pStyle{ nullptr },
			m_pFont{ nullptr },
			m_bIsFontChanging{ false },
			m_bIsFontSizeChanged{ false },
			m_bIsFontStyleChanged{ false },
			m_sRect{ 0, 0, 0, 0 },
			m_bAcceptFocus{ false },
			m_bAcceptForm{ false },
			m_bAcceptControls{ false },
			m_bAcceptParent{ false },
			m_bSupportText{ false },
			m_bVisible{ true },
			m_bTabStop{ false },
			m_bUseStyle{ true },
			m_bUseParentFont{ true },
			m_bEnabled{ true },
			m_sInitialRect{ 0, 0, 0, 0 },
			m_sConstraints{ 0, 0, 0, 0 },
			m_eAlign{ alNone },
			m_eCursor{ ctArrow },
			m_iZIndex{ 0 }
		{
			m_sClassName = L"CControl";
		}

		CControl::~CControl()
		{
			CForm *form{ m_pForm };
			if (form)
				form->LockRepaint();
			setForm(nullptr);
			setParent(nullptr);
			DeleteControls();
			if (form)
				form->UnlockRepaint();
		}
#pragma endregion

#pragma region Font callbacks
		void CControl::FontOnChangeName(void *param)
		{
			CControl *control{ (CControl*)param };
			control->m_bIsFontSizeChanged = true;
			if (!control->m_bIsFontChanging)
			{
				if (control->m_pForm)
					control->m_pForm->LockRepaint();
				control->NotifyOnFontChangeName();
				control->NotifyOnFontChangeSize();
				if (control->m_pForm)
					control->m_pForm->UnlockRepaint();
			}
		}

		void CControl::FontOnChangeHeight(void *param)
		{
			CControl *control{ (CControl*)param };
			control->m_bIsFontSizeChanged = true;
			if (!control->m_bIsFontChanging)
			{
				if (control->m_pForm)
					control->m_pForm->LockRepaint();
				control->NotifyOnFontChangeHeight();
				control->NotifyOnFontChangeSize();
				if (control->m_pForm)
					control->m_pForm->UnlockRepaint();
			}
		}

		void CControl::FontOnChangeWeight(void *param)
		{
			CControl *control{ (CControl*)param };
			control->m_bIsFontSizeChanged = true;
			if (!control->m_bIsFontChanging)
			{
				if (control->m_pForm)
					control->m_pForm->LockRepaint();
				control->NotifyOnFontChangeWeight();
				control->NotifyOnFontChangeSize();
				if (control->m_pForm)
					control->m_pForm->UnlockRepaint();
			}
		}

		void CControl::FontOnChangeItalic(void *param)
		{
			CControl *control{ (CControl*)param };
			control->m_bIsFontSizeChanged = true;
			if (!control->m_bIsFontChanging)
			{
				if (control->m_pForm)
					control->m_pForm->LockRepaint();
				control->NotifyOnFontChangeItalic();
				control->NotifyOnFontChangeSize();
				if (control->m_pForm)
					control->m_pForm->UnlockRepaint();
			}
		}

		void CControl::FontOnChangeUnderline(void *param)
		{
			CControl *control{ (CControl*)param };
			control->m_bIsFontSizeChanged = true;
			if (!control->m_bIsFontChanging)
			{
				if (control->m_pForm)
					control->m_pForm->LockRepaint();
				control->NotifyOnFontChangeUnderline();
				control->NotifyOnFontChangeSize();
				if (control->m_pForm)
					control->m_pForm->UnlockRepaint();
			}
		}

		void CControl::FontOnChangeStrikeOut(void *param)
		{
			CControl *control{ (CControl*)param };
			control->m_bIsFontSizeChanged = true;
			if (!control->m_bIsFontChanging)
			{
				if (control->m_pForm)
					control->m_pForm->LockRepaint();
				control->NotifyOnFontChangeStrikeOut();
				control->NotifyOnFontChangeSize();
				if (control->m_pForm)
					control->m_pForm->UnlockRepaint();
			}
		}

		void CControl::FontOnChangeWidth(void *param)
		{
			CControl *control{ (CControl*)param };
			control->m_bIsFontSizeChanged = true;
			if (!control->m_bIsFontChanging)
			{
				if (control->m_pForm)
					control->m_pForm->LockRepaint();
				control->NotifyOnFontChangeWidth();
				control->NotifyOnFontChangeSize();
				if (control->m_pForm)
					control->m_pForm->UnlockRepaint();
			}
		}

		void CControl::FontOnChangeCharSet(void *param)
		{
			CControl *control{ (CControl*)param };
			control->m_bIsFontSizeChanged = true;
			if (!control->m_bIsFontChanging)
			{
				if (control->m_pForm)
					control->m_pForm->LockRepaint();
				control->NotifyOnFontChangeCharSet();
				control->NotifyOnFontChangeSize();
				if (control->m_pForm)
					control->m_pForm->UnlockRepaint();
			}
		}

		void CControl::FontOnChangeQuality(void *param)
		{
			CControl *control{ (CControl*)param };
			control->m_bIsFontSizeChanged = true;
			if (!control->m_bIsFontChanging)
			{
				if (control->m_pForm)
					control->m_pForm->LockRepaint();
				control->NotifyOnFontChangeQuality();
				control->NotifyOnFontChangeSize();
				if (control->m_pForm)
					control->m_pForm->UnlockRepaint();
			}
		}

		void CControl::FontOnChangePitchAndFamily(void *param)
		{
			CControl *control{ (CControl*)param };
			control->m_bIsFontSizeChanged = true;
			if (!control->m_bIsFontChanging)
			{
				if (control->m_pForm)
					control->m_pForm->LockRepaint();
				control->NotifyOnFontChangePitchAndFamily();
				control->NotifyOnFontChangeSize();
				if (control->m_pForm)
					control->m_pForm->UnlockRepaint();
			}
		}

		void CControl::FontOnChangeOrientation(void *param)
		{
			CControl *control{ (CControl*)param };
			control->m_bIsFontSizeChanged = true;
			if (!control->m_bIsFontChanging)
			{
				if (control->m_pForm)
					control->m_pForm->LockRepaint();
				control->NotifyOnFontChangeOrientation();
				control->NotifyOnFontChangeSize();
				if (control->m_pForm)
					control->m_pForm->UnlockRepaint();
			}
		}

		void CControl::FontOnChangeDistance(void *param)
		{
			CControl *control{ (CControl*)param };
			control->m_bIsFontSizeChanged = true;
			if (!control->m_bIsFontChanging)
			{
				if (control->m_pForm)
					control->m_pForm->LockRepaint();
				control->NotifyOnFontChangeDistance();
				control->NotifyOnFontChangeSize();
				if (control->m_pForm)
					control->m_pForm->UnlockRepaint();
			}
		}

		void CControl::FontOnChangeShadow(void *param)
		{
			CControl *control{ (CControl*)param };
			control->m_bIsFontSizeChanged = true;
			if (!control->m_bIsFontChanging)
			{
				if (control->m_pForm)
					control->m_pForm->LockRepaint();
				control->NotifyOnFontChangeShadow();
				control->NotifyOnFontChangeSize();
				if (control->m_pForm)
					control->m_pForm->UnlockRepaint();
			}
		}

		void CControl::FontOnChangeShadowShift(void *param)
		{
			CControl *control{ (CControl*)param };
			if (!control->m_bIsFontChanging)
			{
				control->m_bIsFontSizeChanged = true;
				if (control->m_pForm)
					control->m_pForm->LockRepaint();
				control->NotifyOnFontChangeShadowShift();
				control->NotifyOnFontChangeSize();
				if (control->m_pForm)
					control->m_pForm->UnlockRepaint();
			}
		}

		void CControl::FontOnChangeShadowBlur(void *param)
		{
			CControl *control{ (CControl*)param };
			if (!control->m_bIsFontChanging)
			{
				control->m_bIsFontSizeChanged = true;
				if (control->m_pForm)
					control->m_pForm->LockRepaint();
				control->NotifyOnFontChangeShadowBlur();
				control->NotifyOnFontChangeSize();
				if (control->m_pForm)
					control->m_pForm->UnlockRepaint();
			}
		}

		void CControl::FontOnChangeShadowColor(void *param)
		{
			CControl *control{ (CControl*)param };
			if (!control->m_bIsFontChanging)
			{
				control->m_bIsFontStyleChanged = true;
				if (control->m_pForm)
					control->m_pForm->LockRepaint();
				control->NotifyOnFontChangeShadowColor();
				control->NotifyOnFontChangeStyle();
				if (control->m_pForm)
					control->m_pForm->UnlockRepaint();
			}
		}

		void CControl::FontOnChangeColor(void *param)
		{
			CControl *control{ (CControl*)param };
			control->m_bIsFontStyleChanged = true;
			if (!control->m_bIsFontChanging)
			{
				if (control->m_pForm)
					control->m_pForm->LockRepaint();
				control->NotifyOnFontChangeColor();
				control->NotifyOnFontChangeStyle();
				if (control->m_pForm)
					control->m_pForm->UnlockRepaint();
			}
		}

		void CControl::FontOnChangeInterpolate(void *param)
		{
			CControl *control{ (CControl*)param };
			control->m_bIsFontStyleChanged = true;
			if (!control->m_bIsFontChanging)
			{
				if (control->m_pForm)
					control->m_pForm->LockRepaint();
				control->NotifyOnFontChangeInterpolate();
				control->NotifyOnFontChangeStyle();
				if (control->m_pForm)
					control->m_pForm->UnlockRepaint();
			}
		}

		void CControl::FontOnBeginChange(void *param)
		{
			CControl *control{ (CControl*)param };
			control->m_bIsFontChanging = true;
			control->m_bIsFontSizeChanged = false;
			control->m_bIsFontStyleChanged = false;
			if (control->m_pForm)
				control->m_pForm->LockRepaint();
			control->NotifyOnFontBeginChange();
		}

		void CControl::FontOnEndChange(void *param)
		{
			CControl *control{ (CControl*)param };
			control->m_bIsFontChanging = false;
			control->NotifyOnFontEndChange();
			if (control->m_bIsFontSizeChanged)
				control->NotifyOnFontChangeSize();
			else if (control->m_bIsFontStyleChanged)
				control->NotifyOnFontChangeStyle();
			if (control->m_pForm)
				control->m_pForm->UnlockRepaint();
		}
#pragma endregion

#pragma region Component overwritten notifications
		void CControl::NotifyOnBeforeDetachComponentFromForm(CComponent *component)
		{
			// Send same notification to children
			for (auto pos = m_aControls.begin(); pos != m_aControls.end(); pos++)
				(*pos)->NotifyOnBeforeDetachComponentFromForm(component);
			CComponent::NotifyOnBeforeDetachComponentFromForm(component);
		}

		void CControl::NotifyOnBeforeDetachControlFromForm(CControl *control)
		{
			// Send same notification to children
			for (auto pos = m_aControls.begin(); pos != m_aControls.end(); pos++)
				(*pos)->NotifyOnBeforeDetachControlFromForm(control);
			CComponent::NotifyOnBeforeDetachControlFromForm(control);
		}

		void CControl::NotifyOnUpdateComponent(CComponent *component)
		{
			// Send same notification to children
			for (auto pos = m_aControls.begin(); pos != m_aControls.end(); pos++)
				(*pos)->NotifyOnUpdateComponent(component);
			CComponent::NotifyOnUpdateComponent(component);
		}

		void CControl::NotifyOnUpdateControl(CControl *control)
		{
			// Send same notification to children
			for (auto pos = m_aControls.begin(); pos != m_aControls.end(); pos++)
				(*pos)->NotifyOnUpdateControl(control);
			CComponent::NotifyOnUpdateControl(control);
		}

		void CControl::NotifyOnUpdate()
		{
			if (m_pForm)
			{
				m_pForm->LockRepaint();
				m_pForm->NotifyOnUpdateControl(this);
				if (m_fOnUpdate)
					m_fOnUpdate(m_pCallbackParam);
				m_pForm->UnlockRepaint();
			}
		}
	#pragma endregion

	#pragma region Input(keyboard and mouse) notifications
		bool CControl::NotifyOnKeyDown(const IWindow::KEY key)
		{
			if (m_fOnKeyDown)
				m_fOnKeyDown(this, key, m_pCallbackParam);
			return false;
		}

		bool CControl::NotifyOnKeyUp(const IWindow::KEY key)
		{
			if (m_fOnKeyUp)
				m_fOnKeyUp(this, key, m_pCallbackParam);
			return false;
		}

		bool CControl::NotifyOnChar(const wchar_t chr)
		{
			if (m_fOnChar)
				m_fOnChar(this, chr, m_pCallbackParam);
			return false;
		}

		bool CControl::NotifyOnDeadChar(const wchar_t chr)
		{
			if (m_fOnDeadChar)
				m_fOnDeadChar(this, chr, m_pCallbackParam);
			return false;
		}

		bool CControl::NotifyOnSysKeyDown(const IWindow::KEY key)
		{
			if (m_fOnSysKeyDown)
				m_fOnSysKeyDown(this, key, m_pCallbackParam);
			return false;
		}

		bool CControl::NotifyOnSysKeyUp(const IWindow::KEY key)
		{
			if (m_fOnSysKeyUp)
				m_fOnSysKeyUp(this, key, m_pCallbackParam);
			return false;
		}

		bool CControl::NotifyOnSysChar(const wchar_t chr)
		{
			if (m_fOnSysChar)
				m_fOnSysChar(this, chr, m_pCallbackParam);
			return false;
		}

		bool CControl::NotifyOnSysDeadChar(const wchar_t chr)
		{
			if (m_fOnSysDeadChar)
				m_fOnSysDeadChar(this, chr, m_pCallbackParam);
			return false;
		}

		bool CControl::NotifyOnMouseMove(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			if (m_fOnMouseMove)
				m_fOnMouseMove(this, x, y, ctrl, left, middle, right, shift, m_pCallbackParam);
			return false;
		}

		bool CControl::NotifyOnLeftMouseButtonDown(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			if (m_fOnLeftMouseButtonDown)
				m_fOnLeftMouseButtonDown(this, x, y, ctrl, left, middle, right, shift, m_pCallbackParam);
			return false;
		}

		bool CControl::NotifyOnLeftMouseButtonUp(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			if (m_fOnLeftMouseButtonUp)
				m_fOnLeftMouseButtonUp(this, x, y, ctrl, left, middle, right, shift, m_pCallbackParam);
			return false;
		}

		bool CControl::NotifyOnLeftMouseButtonDoubleClick(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			if (m_fOnLeftMouseButtonDoubleClick)
				m_fOnLeftMouseButtonDoubleClick(this, x, y, ctrl, left, middle, right, shift, m_pCallbackParam);
			return false;
		}

		bool CControl::NotifyOnRightMouseButtonDown(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			if (m_fOnRightMouseButtonDown)
				m_fOnRightMouseButtonDown(this, x, y, ctrl, left, middle, right, shift, m_pCallbackParam);
			return false;
		}

		bool CControl::NotifyOnRightMouseButtonUp(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			if (m_fOnRightMouseButtonUp)
				m_fOnRightMouseButtonUp(this, x, y, ctrl, left, middle, right, shift, m_pCallbackParam);
			return false;
		}

		bool CControl::NotifyOnRightMouseButtonDoubleClick(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			if (m_fOnRightMouseButtonDoubleClick)
				m_fOnRightMouseButtonDoubleClick(this, x, y, ctrl, left, middle, right, shift, m_pCallbackParam);
			return false;
		}

		bool CControl::NotifyOnMiddleMouseButtonDown(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			if (m_fOnMiddleMouseButtonDown)
				m_fOnMiddleMouseButtonDown(this, x, y, ctrl, left, middle, right, shift, m_pCallbackParam);
			return false;
		}

		bool CControl::NotifyOnMiddleMouseButtonUp(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			if (m_fOnMiddleMouseButtonUp)
				m_fOnMiddleMouseButtonUp(this, x, y, ctrl, left, middle, right, shift, m_pCallbackParam);
			return false;
		}

		bool CControl::NotifyOnMiddleMouseButtonDoubleClick(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			if (m_fOnMiddleMouseButtonDoubleClick)
				m_fOnMiddleMouseButtonDoubleClick(this, x, y, ctrl, left, middle, right, shift, m_pCallbackParam);
			return false;
		}

		bool CControl::NotifyOnMouseVerticalWheel(const int x, const int y, const int delta, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			if (m_fOnMouseVerticalWheel)
				m_fOnMouseVerticalWheel(this, x, y, delta, ctrl, left, middle, right, shift, m_pCallbackParam);
			return false;
		}

		bool CControl::NotifyOnMouseHorizontalWheel(const int x, const int y, const int delta, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			if (m_fOnMouseHorizontalWheel)
				m_fOnMouseHorizontalWheel(this, x, y, delta, ctrl, left, middle, right, shift, m_pCallbackParam);
			return false;
		}
	#pragma endregion

	#pragma region Parent font change notifications
		void CControl::NotifyOnChangeUseParentFont()
		{
			if (m_bSupportText)
			{
				UpdateRect();
				Repaint(false);
			}
			for (auto pos = m_aControls.begin(); pos != m_aControls.end(); pos++)
				if ((*pos)->m_bUseParentFont)
					(*pos)->NotifyOnChangeUseParentFont();
			if (m_fOnChangeUseParentFont)
				m_fOnChangeUseParentFont(this, m_pCallbackParam);
		}

		void CControl::NotifyOnParentFontChangeName()
		{
			for (auto pos = m_aControls.begin(); pos != m_aControls.end(); pos++)
				if ((*pos)->m_bUseParentFont)
					(*pos)->NotifyOnParentFontChangeName();
			if (m_fOnParentFontChangeName)
				m_fOnParentFontChangeName(this, m_pCallbackParam);
		}

		void CControl::NotifyOnParentFontChangeHeight()
		{
			for (auto pos = m_aControls.begin(); pos != m_aControls.end(); pos++)
				if ((*pos)->m_bUseParentFont)
					(*pos)->NotifyOnParentFontChangeHeight();
			if (m_fOnParentFontChangeHeight)
				m_fOnParentFontChangeHeight(this, m_pCallbackParam);
		}

		void CControl::NotifyOnParentFontChangeWeight()
		{
			for (auto pos = m_aControls.begin(); pos != m_aControls.end(); pos++)
				if ((*pos)->m_bUseParentFont)
					(*pos)->NotifyOnParentFontChangeWeight();
			if (m_fOnParentFontChangeWeight)
				m_fOnParentFontChangeWeight(this, m_pCallbackParam);
		}

		void CControl::NotifyOnParentFontChangeItalic()
		{
			for (auto pos = m_aControls.begin(); pos != m_aControls.end(); pos++)
				if ((*pos)->m_bUseParentFont)
					(*pos)->NotifyOnParentFontChangeItalic();
			if (m_fOnParentFontChangeItalic)
				m_fOnParentFontChangeItalic(this, m_pCallbackParam);
		}

		void CControl::NotifyOnParentFontChangeUnderline()
		{
			for (auto pos = m_aControls.begin(); pos != m_aControls.end(); pos++)
				if ((*pos)->m_bUseParentFont)
					(*pos)->NotifyOnParentFontChangeUnderline();
			if (m_fOnParentFontChangeUnderline)
				m_fOnParentFontChangeUnderline(this, m_pCallbackParam);
		}

		void CControl::NotifyOnParentFontChangeStrikeOut()
		{
			for (auto pos = m_aControls.begin(); pos != m_aControls.end(); pos++)
				if ((*pos)->m_bUseParentFont)
					(*pos)->NotifyOnParentFontChangeStrikeOut();
			if (m_fOnParentFontChangeStrikeOut)
				m_fOnParentFontChangeStrikeOut(this, m_pCallbackParam);
		}

		void CControl::NotifyOnParentFontChangeWidth()
		{
			for (auto pos = m_aControls.begin(); pos != m_aControls.end(); pos++)
				if ((*pos)->m_bUseParentFont)
					(*pos)->NotifyOnParentFontChangeWidth();
			if (m_fOnParentFontChangeWidth)
				m_fOnParentFontChangeWidth(this, m_pCallbackParam);
		}

		void CControl::NotifyOnParentFontChangeCharSet()
		{
			for (auto pos = m_aControls.begin(); pos != m_aControls.end(); pos++)
				if ((*pos)->m_bUseParentFont)
					(*pos)->NotifyOnParentFontChangeCharSet();
			if (m_fOnParentFontChangeCharSet)
				m_fOnParentFontChangeCharSet(this, m_pCallbackParam);
		}

		void CControl::NotifyOnParentFontChangeQuality()
		{
			for (auto pos = m_aControls.begin(); pos != m_aControls.end(); pos++)
				if ((*pos)->m_bUseParentFont)
					(*pos)->NotifyOnParentFontChangeQuality();
			if (m_fOnParentFontChangeQuality)
				m_fOnParentFontChangeQuality(this, m_pCallbackParam);
		}

		void CControl::NotifyOnParentFontChangePitchAndFamily()
		{
			for (auto pos = m_aControls.begin(); pos != m_aControls.end(); pos++)
				if ((*pos)->m_bUseParentFont)
					(*pos)->NotifyOnParentFontChangePitchAndFamily();
			if (m_fOnParentFontChangePitchAndFamily)
				m_fOnParentFontChangePitchAndFamily(this, m_pCallbackParam);
		}

		void CControl::NotifyOnParentFontChangeOrientation()
		{
			for (auto pos = m_aControls.begin(); pos != m_aControls.end(); pos++)
				if ((*pos)->m_bUseParentFont)
					(*pos)->NotifyOnParentFontChangeOrientation();
			if (m_fOnParentFontChangeOrientation)
				m_fOnParentFontChangeOrientation(this, m_pCallbackParam);
		}

		void CControl::NotifyOnParentFontChangeDistance()
		{
			for (auto pos = m_aControls.begin(); pos != m_aControls.end(); pos++)
				if ((*pos)->m_bUseParentFont)
					(*pos)->NotifyOnParentFontChangeDistance();
			if (m_fOnParentFontChangeDistance)
				m_fOnParentFontChangeDistance(this, m_pCallbackParam);
		}

		void CControl::NotifyOnParentFontChangeShadow()
		{
			for (auto pos = m_aControls.begin(); pos != m_aControls.end(); pos++)
				if ((*pos)->m_bUseParentFont)
					(*pos)->NotifyOnParentFontChangeShadow();
			if (m_fOnParentFontChangeShadow)
				m_fOnParentFontChangeShadow(this, m_pCallbackParam);
		}

		void CControl::NotifyOnParentFontChangeShadowShift()
		{
			for (auto pos = m_aControls.begin(); pos != m_aControls.end(); pos++)
				if ((*pos)->m_bUseParentFont)
					(*pos)->NotifyOnParentFontChangeShadowShift();
			if (m_fOnParentFontChangeShadowShift)
				m_fOnParentFontChangeShadowShift(this, m_pCallbackParam);
		}

		void CControl::NotifyOnParentFontChangeShadowBlur()
		{
			for (auto pos = m_aControls.begin(); pos != m_aControls.end(); pos++)
				if ((*pos)->m_bUseParentFont)
					(*pos)->NotifyOnParentFontChangeShadowBlur();
			if (m_fOnParentFontChangeShadowBlur)
				m_fOnParentFontChangeShadowBlur(this, m_pCallbackParam);
		}

		void CControl::NotifyOnParentFontChangeShadowColor()
		{
			for (auto pos = m_aControls.begin(); pos != m_aControls.end(); pos++)
				if ((*pos)->m_bUseParentFont)
					(*pos)->NotifyOnParentFontChangeShadowColor();
			if (m_fOnParentFontChangeShadowColor)
				m_fOnParentFontChangeShadowColor(this, m_pCallbackParam);
		}

		void CControl::NotifyOnParentFontChangeColor()
		{
			for (auto pos = m_aControls.begin(); pos != m_aControls.end(); pos++)
				if ((*pos)->m_bUseParentFont)
					(*pos)->NotifyOnParentFontChangeColor();
			if (m_fOnParentFontChangeColor)
				m_fOnParentFontChangeColor(this, m_pCallbackParam);
		}

		void CControl::NotifyOnParentFontChangeInterpolate()
		{
			for (auto pos = m_aControls.begin(); pos != m_aControls.end(); pos++)
				if ((*pos)->m_bUseParentFont)
					(*pos)->NotifyOnParentFontChangeInterpolate();
			if (m_fOnParentFontChangeInterpolate)
				m_fOnParentFontChangeInterpolate(this, m_pCallbackParam);
		}

		void CControl::NotifyOnParentFontBeginChange()
		{
			for (auto pos = m_aControls.begin(); pos != m_aControls.end(); pos++)
				if ((*pos)->m_bUseParentFont)
					(*pos)->NotifyOnParentFontBeginChange();
			if (m_fOnParentFontBeginChange)
				m_fOnParentFontBeginChange(this, m_pCallbackParam);
		}

		void CControl::NotifyOnParentFontEndChange()
		{
			for (auto pos = m_aControls.begin(); pos != m_aControls.end(); pos++)
				if ((*pos)->m_bUseParentFont)
					(*pos)->NotifyOnParentFontEndChange();
			if (m_fOnParentFontEndChange)
				m_fOnParentFontEndChange(this, m_pCallbackParam);
		}

		void CControl::NotifyOnParentFontChangeSize()
		{
			if (m_bSupportText)
			{
				UpdateRect();
				Repaint(false);
			}
			for (auto pos = m_aControls.begin(); pos != m_aControls.end(); pos++)
				if ((*pos)->m_bUseParentFont)
					(*pos)->NotifyOnParentFontChangeSize();
			if (m_fOnParentFontChangeSize)
				m_fOnParentFontChangeSize(this, m_pCallbackParam);
		}

		void CControl::NotifyOnParentFontChangeStyle()
		{
			if (m_bSupportText)
				Repaint(false);
			for (auto pos = m_aControls.begin(); pos != m_aControls.end(); pos++)
				if ((*pos)->m_bUseParentFont)
					(*pos)->NotifyOnParentFontChangeStyle();
			if (m_fOnParentFontChangeStyle)
				m_fOnParentFontChangeStyle(this, m_pCallbackParam);
		}
	#pragma endregion

	#pragma region Font change notifications
		void CControl::NotifyOnFontChangeName()
		{
			m_bUseParentFont = false;
			for (auto pos = m_aControls.begin(); pos != m_aControls.end(); pos++)
				if ((*pos)->m_bUseParentFont)
					(*pos)->NotifyOnParentFontChangeName();
			if (m_fOnFontChangeName)
				m_fOnFontChangeName(this, m_pCallbackParam);
		}

		void CControl::NotifyOnFontChangeHeight()
		{
			m_bUseParentFont = false;
			for (auto pos = m_aControls.begin(); pos != m_aControls.end(); pos++)
				if ((*pos)->m_bUseParentFont)
					(*pos)->NotifyOnParentFontChangeHeight();
			if (m_fOnFontChangeHeight)
				m_fOnFontChangeHeight(this, m_pCallbackParam);
		}

		void CControl::NotifyOnFontChangeWeight()
		{
			m_bUseParentFont = false;
			for (auto pos = m_aControls.begin(); pos != m_aControls.end(); pos++)
				if ((*pos)->m_bUseParentFont)
					(*pos)->NotifyOnParentFontChangeWeight();
			if (m_fOnFontChangeWeight)
				m_fOnFontChangeWeight(this, m_pCallbackParam);
		}

		void CControl::NotifyOnFontChangeItalic()
		{
			m_bUseParentFont = false;
			for (auto pos = m_aControls.begin(); pos != m_aControls.end(); pos++)
				if ((*pos)->m_bUseParentFont)
					(*pos)->NotifyOnParentFontChangeItalic();
			if (m_fOnFontChangeItalic)
				m_fOnFontChangeItalic(this, m_pCallbackParam);
		}

		void CControl::NotifyOnFontChangeUnderline()
		{
			m_bUseParentFont = false;
			for (auto pos = m_aControls.begin(); pos != m_aControls.end(); pos++)
				if ((*pos)->m_bUseParentFont)
					(*pos)->NotifyOnParentFontChangeUnderline();
			if (m_fOnFontChangeUnderline)
				m_fOnFontChangeUnderline(this, m_pCallbackParam);
		}

		void CControl::NotifyOnFontChangeStrikeOut()
		{
			m_bUseParentFont = false;
			for (auto pos = m_aControls.begin(); pos != m_aControls.end(); pos++)
				if ((*pos)->m_bUseParentFont)
					(*pos)->NotifyOnParentFontChangeStrikeOut();
			if (m_fOnFontChangeStrikeOut)
				m_fOnFontChangeStrikeOut(this, m_pCallbackParam);
		}

		void CControl::NotifyOnFontChangeWidth()
		{
			m_bUseParentFont = false;
			for (auto pos = m_aControls.begin(); pos != m_aControls.end(); pos++)
				if ((*pos)->m_bUseParentFont)
					(*pos)->NotifyOnParentFontChangeWidth();
			if (m_fOnFontChangeWidth)
				m_fOnFontChangeWidth(this, m_pCallbackParam);
		}

		void CControl::NotifyOnFontChangeCharSet()
		{
			m_bUseParentFont = false;
			for (auto pos = m_aControls.begin(); pos != m_aControls.end(); pos++)
				if ((*pos)->m_bUseParentFont)
					(*pos)->NotifyOnParentFontChangeCharSet();
			if (m_fOnFontChangeCharSet)
				m_fOnFontChangeCharSet(this, m_pCallbackParam);
		}

		void CControl::NotifyOnFontChangeQuality()
		{
			m_bUseParentFont = false;
			for (auto pos = m_aControls.begin(); pos != m_aControls.end(); pos++)
				if ((*pos)->m_bUseParentFont)
					(*pos)->NotifyOnParentFontChangeQuality();
			if (m_fOnFontChangeQuality)
				m_fOnFontChangeQuality(this, m_pCallbackParam);
		}

		void CControl::NotifyOnFontChangePitchAndFamily()
		{
			m_bUseParentFont = false;
			for (auto pos = m_aControls.begin(); pos != m_aControls.end(); pos++)
				if ((*pos)->m_bUseParentFont)
					(*pos)->NotifyOnParentFontChangePitchAndFamily();
			if (m_fOnFontChangePitchAndFamily)
				m_fOnFontChangePitchAndFamily(this, m_pCallbackParam);
		}

		void CControl::NotifyOnFontChangeOrientation()
		{
			m_bUseParentFont = false;
			for (auto pos = m_aControls.begin(); pos != m_aControls.end(); pos++)
				if ((*pos)->m_bUseParentFont)
					(*pos)->NotifyOnParentFontChangeOrientation();
			if (m_fOnFontChangeOrientation)
				m_fOnFontChangeOrientation(this, m_pCallbackParam);
		}

		void CControl::NotifyOnFontChangeDistance()
		{
			m_bUseParentFont = false;
			for (auto pos = m_aControls.begin(); pos != m_aControls.end(); pos++)
				if ((*pos)->m_bUseParentFont)
					(*pos)->NotifyOnParentFontChangeDistance();
			if (m_fOnFontChangeDistance)
				m_fOnFontChangeDistance(this, m_pCallbackParam);
		}

		void CControl::NotifyOnFontChangeShadow()
		{
			m_bUseParentFont = false;
			for (auto pos = m_aControls.begin(); pos != m_aControls.end(); pos++)
				if ((*pos)->m_bUseParentFont)
					(*pos)->NotifyOnParentFontChangeShadow();
			if (m_fOnFontChangeShadow)
				m_fOnFontChangeShadow(this, m_pCallbackParam);
		}

		void CControl::NotifyOnFontChangeShadowShift()
		{
			m_bUseParentFont = false;
			for (auto pos = m_aControls.begin(); pos != m_aControls.end(); pos++)
				if ((*pos)->m_bUseParentFont)
					(*pos)->NotifyOnParentFontChangeShadowShift();
			if (m_fOnFontChangeShadowShift)
				m_fOnFontChangeShadowShift(this, m_pCallbackParam);
		}

		void CControl::NotifyOnFontChangeShadowBlur()
		{
			m_bUseParentFont = false;
			for (auto pos = m_aControls.begin(); pos != m_aControls.end(); pos++)
				if ((*pos)->m_bUseParentFont)
					(*pos)->NotifyOnParentFontChangeShadowBlur();
			if (m_fOnFontChangeShadowBlur)
				m_fOnFontChangeShadowBlur(this, m_pCallbackParam);
		}

		void CControl::NotifyOnFontChangeShadowColor()
		{
			m_bUseParentFont = false;
			for (auto pos = m_aControls.begin(); pos != m_aControls.end(); pos++)
				if ((*pos)->m_bUseParentFont)
					(*pos)->NotifyOnParentFontChangeShadowColor();
			if (m_fOnFontChangeShadowColor)
				m_fOnFontChangeShadowColor(this, m_pCallbackParam);
		}

		void CControl::NotifyOnFontChangeColor()
		{
			m_bUseParentFont = false;
			for (auto pos = m_aControls.begin(); pos != m_aControls.end(); pos++)
				if ((*pos)->m_bUseParentFont)
					(*pos)->NotifyOnParentFontChangeColor();
			if (m_fOnFontChangeColor)
				m_fOnFontChangeColor(this, m_pCallbackParam);
		}

		void CControl::NotifyOnFontChangeInterpolate()
		{
			m_bUseParentFont = false;
			for (auto pos = m_aControls.begin(); pos != m_aControls.end(); pos++)
				if ((*pos)->m_bUseParentFont)
					(*pos)->NotifyOnParentFontChangeInterpolate();
			if (m_fOnFontChangeInterpolate)
				m_fOnFontChangeInterpolate(this, m_pCallbackParam);
		}

		void CControl::NotifyOnFontBeginChange()
		{
			m_bUseParentFont = false;
			for (auto pos = m_aControls.begin(); pos != m_aControls.end(); pos++)
				if ((*pos)->m_bUseParentFont)
					(*pos)->NotifyOnParentFontBeginChange();
			if (m_fOnFontBeginChange)
				m_fOnFontBeginChange(this, m_pCallbackParam);
		}

		void CControl::NotifyOnFontEndChange()
		{
			m_bUseParentFont = false;
			for (auto pos = m_aControls.begin(); pos != m_aControls.end(); pos++)
				if ((*pos)->m_bUseParentFont)
					(*pos)->NotifyOnParentFontEndChange();
			if (m_fOnFontEndChange)
				m_fOnFontEndChange(this, m_pCallbackParam);
		}

		void CControl::NotifyOnFontChangeSize()
		{
			m_bUseParentFont = false;
			if (m_bSupportText)
			{
				UpdateRect();
				Repaint(false);
			}
			for (auto pos = m_aControls.begin(); pos != m_aControls.end(); pos++)
				if ((*pos)->m_bUseParentFont)
					(*pos)->NotifyOnParentFontChangeSize();
			if (m_fOnFontChangeSize)
				m_fOnFontChangeSize(this, m_pCallbackParam);
		}

		void CControl::NotifyOnFontChangeStyle()
		{
			m_bUseParentFont = false;
			if (m_bSupportText)
				Repaint(false);
			for (auto pos = m_aControls.begin(); pos != m_aControls.end(); pos++)
				if ((*pos)->m_bUseParentFont)
					(*pos)->NotifyOnParentFontChangeStyle();
			if (m_fOnFontChangeStyle)
				m_fOnFontChangeStyle(this, m_pCallbackParam);
		}
	#pragma endregion

	#pragma region Notifications
		void CControl::NotifyOnMouseHover()
		{
			if(m_fOnMouseHover)
				m_fOnMouseHover(this, m_pCallbackParam);
		}

		void CControl::NotifyOnMouseLeave()
		{
			if (m_fOnMouseLeave)
				m_fOnMouseLeave(this, m_pCallbackParam);
		}

		void CControl::NotifyOnKillFocus()
		{
			if (m_fOnKillFocus)
				m_fOnKillFocus(this, m_pCallbackParam);
		}

		void CControl::NotifyOnSetFocus(CControl *old)
		{
			if (m_fOnSetFocus)
				m_fOnSetFocus(this, old, m_pCallbackParam);
		}

		void CControl::NotifyOnResetFocus()
		{
			if (m_fOnResetFocus)
				m_fOnResetFocus(this, m_pCallbackParam);
		}

		void CControl::NotifyOnKillCaptureKeyboard()
		{
			if (m_fOnKillCaptureKeyboard)
				m_fOnKillCaptureKeyboard(this, m_pCallbackParam);
		}

		void CControl::NotifyOnKillCaptureMouse()
		{
			if (m_fOnKillCaptureMouse)
				m_fOnKillCaptureMouse(this, m_pCallbackParam);
		}

		void CControl::NotifyOnSetCaptureKeyboard()
		{
			if (m_fOnSetCaptureKeyboard)
				m_fOnSetCaptureKeyboard(this, m_pCallbackParam);
		}

		void CControl::NotifyOnSetCaptureMouse()
		{
			if (m_fOnSetCaptureMouse)
				m_fOnSetCaptureMouse(this, m_pCallbackParam);
		}

		void CControl::NotifyOnChangeParentStyle()
		{
			if (UpdateFromStyle())
			{
				UpdateRect();
				Repaint(false);
			}
			for (auto pos = m_aControls.begin(); pos != m_aControls.end(); pos++)
				if ((*pos)->m_bUseStyle && !(*pos)->m_pStyle)
					(*pos)->NotifyOnChangeParentStyle();
			if (m_fOnChangeParentStyle)
				m_fOnChangeParentStyle(this, m_pCallbackParam);
		}

		void CControl::NotifyOnChangeStyle()
		{
			if (UpdateFromStyle())
			{
				UpdateRect();
				Repaint(false);
			}
			for (auto pos = m_aControls.begin(); pos != m_aControls.end(); pos++)
				if ((*pos)->m_bUseStyle && !(*pos)->m_pStyle)
					(*pos)->NotifyOnChangeParentStyle();
			if (m_fOnChangeStyle)
				m_fOnChangeStyle(this, m_pCallbackParam);
		}

		void CControl::NotifyOnShow()
		{
			UpdateRect();
			UpdateRectOfNextParentControl();
			Repaint(true);
			if (m_fOnShow)
				m_fOnShow(this, m_pCallbackParam);
		}

		void CControl::NotifyOnBeforeHide()
		{
			Repaint(true);
			if (m_fOnBeforeHide)
				m_fOnBeforeHide(this, m_pCallbackParam);
		}

		void CControl::NotifyOnHide()
		{
			if (m_fOnHide)
				m_fOnHide(this, m_pCallbackParam);
		}

		void CControl::NotifyOnEnable()
		{
			Repaint(true);
			if (m_fOnEnable)
				m_fOnEnable(this, m_pCallbackParam);
		}

		void CControl::NotifyOnDisable()
		{
			Repaint(true);
			if (m_fOnDisable)
				m_fOnDisable(this, m_pCallbackParam);
		}

		void CControl::NotifyOnAttachControl(CControl *control)
		{
			control->UpdateRect();
			control->UpdateRectOfNextParentControl();
			control->Repaint(true);
			if (m_fOnAttachControl)
				m_fOnAttachControl(this, control, m_pCallbackParam);
		}

		void CControl::NotifyOnBeforeDetachControl(CControl *control)
		{
			m_pControlToUpdateAfterDetach = control->FindNextAlignedControl();
			Repaint(true);
			if (m_fOnBeforeDetachControl)
				m_fOnBeforeDetachControl(this, control, m_pCallbackParam);
		}

		void CControl::NotifyOnDetachControl(CControl *control)
		{
			if (m_pControlToUpdateAfterDetach)
				m_pControlToUpdateAfterDetach->UpdateRect();
			if (m_fOnDetachControl)
				m_fOnDetachControl(this, control, m_pCallbackParam);
		}

		void CControl::NotifyOnPaint(APP_RECT clip)
		{
			if (m_fOnPaint)
				m_fOnPaint(this, clip, m_pCallbackParam);
		}

		void CControl::NotifyOnParentResize()
		{
			UpdateRect();
			Repaint(true);
			if (m_fOnParentResize)
				m_fOnParentResize(this, m_pCallbackParam);
		}

		void CControl::NotifyOnParentMove()
		{
			if (m_fOnParentResize)
				m_fOnParentResize(this, m_pCallbackParam);
		}

		void CControl::NotifyOnBeforeResize()
		{
			Repaint(true);
			if (m_fOnBeforeResize)
				m_fOnBeforeResize(this, m_pCallbackParam);
		}

		void CControl::NotifyOnResize(const APP_POINT &old_size, const APP_POINT &new_size)
		{
			if (m_pParent)
				m_pParent->NotifyOnChildControlResize(this, old_size, new_size);
			else if (m_pForm)
				m_pForm->NotifyOnChildControlResize(this, old_size, new_size);
			for (auto pos = m_aControls.begin(); pos != m_aControls.end(); pos++)
				(*pos)->NotifyOnParentResize();
			Repaint(true);
			if (m_fOnResize)
				m_fOnResize(this, old_size, new_size, m_pCallbackParam);
		}

		void CControl::NotifyOnBeforeMove()
		{
			Repaint(true);
			if (m_fOnBeforeMove)
				m_fOnBeforeMove(this, m_pCallbackParam);
		}

		void CControl::NotifyOnMove(const APP_POINT &old_position, const APP_POINT &new_position)
		{
			if (m_pParent)
				m_pParent->NotifyOnChildControlMove(this, old_position, new_position);
			else if (m_pForm)
				m_pForm->NotifyOnChildControlMove(this, old_position, new_position);
			for (auto pos = m_aControls.begin(); pos != m_aControls.end(); pos++)
				(*pos)->NotifyOnParentMove();
			Repaint(true);
			if (m_fOnMove)
				m_fOnMove(this, old_position, new_position, m_pCallbackParam);
		}

		void CControl::NotifyOnChildControlResize(CControl *control, const APP_POINT &old_size, const APP_POINT &new_size)
		{
			if (m_fOnChildControlResize)
				m_fOnChildControlResize(this, control, old_size, new_size, m_pCallbackParam);
		}

		void CControl::NotifyOnChildControlMove(CControl *control, const APP_POINT &old_position, const APP_POINT &new_position)
		{
			if (m_fOnChildControlResize)
				m_fOnChildControlResize(this, control, old_position, new_position, m_pCallbackParam);
		}

		void CControl::NotifyOnBeforeDetachFromControl(CControl *control)
		{
			if (m_fOnBeforeDetachFromControl)
				m_fOnBeforeDetachFromControl(control, m_pCallbackParam);
		}

		void CControl::NotifyOnDetachFromControl(CControl *control)
		{
			if (m_fOnDetachFromControl)
				m_fOnDetachFromControl(control, m_pCallbackParam);
		}

		void CControl::NotifyOnAttachToControl(CControl *control)
		{
			if (m_fOnAttachToControl)
				m_fOnAttachToControl(control, m_pCallbackParam);
		}
#pragma endregion

#pragma region Helpers
		bool CControl::getHaveChild(CControl *control)
		{
			for (auto pos = m_aControls.begin(); pos != m_aControls.end(); pos++)
				if ((*pos) == control || (*pos)->getHaveChild(control))
					return true;
			return false;
		}

		bool CControl::getIsFontChanging() const
		{
			return m_bIsFontChanging;
		}

		bool CControl::getIsFontSizeChanged() const
		{
			return m_bIsFontSizeChanged;
		}

		bool CControl::getIsFontStyleChanged() const
		{
			return m_bIsFontStyleChanged;
		}

		void CControl::RemoveFromForm()
		{
			NotifyOnBeforeDetachFromForm();
			// Notify all form controls and components about this control is about to be removed from form
			for (auto pos = m_pForm->m_aComponents.begin(); pos != m_pForm->m_aComponents.end(); pos++)
				(*pos)->NotifyOnBeforeDetachControlFromForm(this);
			for (auto pos = m_pForm->m_aControlsRoot.begin(); pos != m_pForm->m_aControlsRoot.end(); pos++)
				(*pos)->NotifyOnBeforeDetachControlFromForm(this);
			// Remove control from all control lists of form
			for (auto pos = m_pForm->m_aControls.begin(); pos != m_pForm->m_aControls.end(); pos++)
				if (*pos == this)
				{
					m_pForm->m_aControls.erase(pos);
					break;
				}
			for (auto pos = m_pForm->m_aControlsRoot.begin(); pos != m_pForm->m_aControlsRoot.end(); pos++)
				if (*pos == this)
				{
					m_pForm->m_aControlsRoot.erase(pos);
					break;
				}
			// Remove active control if controls was active, release captures and update tab orders
			if (this == m_pForm->m_pActiveControl)
				m_pForm->setActiveControl(nullptr);
			if (this == m_pForm->m_pOldActiveControl)
				m_pForm->m_pOldActiveControl = nullptr;
			if (this == m_pForm->m_pCaptureKeyboardControl)
				m_pForm->ReleaseCaptureKeyboard();
			if (this == m_pForm->m_pCaptureMouseControl)
				m_pForm->ReleaseCaptureMouse();
			m_pForm->UpdateTabOrders(m_iTabOrder, m_pForm->CalculateTotalControlCount());
			// Remove children from form as well
			for (auto pos = m_aControls.begin(); pos != m_aControls.end(); pos++)
				(*pos)->RemoveFromForm();
			m_pForm->UnregisterHotkeys(this);
			m_pForm = nullptr;
			NotifyOnDetachFromForm();
		}

		void CControl::AddToForm(CForm *form, const bool to_root)
		{
			if (getAcceptFormWithParents())
			{
				// If name already exists, generate new one based on class name
				String name = m_sName;
				if (name.empty())
					name = m_sClassName + L"1";
				if (!form->ValidateControlName(name, nullptr))
				{
					int index = 1;
					do
					{
						name = m_sClassName + ToString(index++);
					} while (!form->ValidateControlName(name, nullptr));
				}
				m_sName = name;
				// Add links to control
				form->m_aControls.push_back(this);
				if (to_root)
					form->m_aControlsRoot.push_back(this);
				form->m_bIsControlsSorted = false;
				m_iTabOrder = form->CalculateTotalControlCount() - 1;
			}
			m_pForm = form;
			// Add sub-controls
			for (auto pos = m_aControls.begin(); pos != m_aControls.end(); pos++)
				(*pos)->AddToForm(form, false);
			NotifyOnAttachToForm();
		}

		void CControl::UpdateRect()
		{
			APP_RECT new_rect = m_sInitialRect;
			// Update rect only if control is aligned and have parent
			if (m_eAlign != alNone && (m_pForm || m_pParent) && getVisibleWithParents())
			{
				APP_RECT clip = m_pParent ? m_pParent->getClientRect() : m_pForm->getWindow()->getClientRect();
				APP_POINT parent_pos = { 0, 0 };
				if (m_pParent) 
					parent_pos = m_pParent->getPosition();
				clip.Right -= parent_pos.X;
				clip.Bottom -= parent_pos.Y;
				clip.Left -= parent_pos.X;
				clip.Top -= parent_pos.Y;
				ALIGN align{ m_eAlign };
				CControl *self{ this };
				auto check = [self, align, &clip](CControl *control, const APP_RECT &rect, APP_RECT &result) {
					if (control == self) // If control is this one, calc it rect and break loop
					{
						switch (align)
						{
						case alLeft:
							result = { clip.Left, clip.Top, (std::min)(clip.Right, clip.Left + rect.Width()), clip.Bottom };
							break;
						case alTop:
							result = { clip.Left, clip.Top, clip.Right, (std::min)(clip.Bottom, clip.Top + rect.Height()) };
							break;
						case alRight:
							result = { (std::max)(clip.Left, clip.Right - rect.Width()), clip.Top, clip.Right, clip.Bottom };
							break;
						case alBottom:
							result = { clip.Left, (std::max)(clip.Top, clip.Bottom - rect.Height()), clip.Right, clip.Bottom };
							break;
						case alClient:
							result = clip;
							break;
						}
						return true;
					}
					if (control->m_bVisible) // Invisible control does not affect clip rect
					{
						switch (control->m_eAlign) // Reduce clip rect by control if it is aligned somehow
						{
						case alLeft:
							clip.Left += control->getWidth();
							break;
						case alTop:
							clip.Top += control->getHeight();
							break;
						case alRight:
							clip.Right -= control->getWidth();
							break;
						case alBottom:
							clip.Bottom -= control->getHeight();
							break;
						case alClient:
							clip = { 0, 0, 0, 0 };
							break;
						}
						if (!clip.IsValid()) // If after reducing clip rect becomes invalid, it means this control rect is empty
						{
							result = { 0, 0, 0, 0 };
							return true;
						}
						if (clip.IsEmpty())
							return true;
					}
					return false;
				};
				if (m_pParent)
				{
					for (auto pos = m_pParent->m_aControls.begin(); pos != m_pParent->m_aControls.end(); pos++) // Process all controls on parent which was created before this one
						if (check(*pos, m_sInitialRect, new_rect))
							break;
				}
				else
				{
					for (size_t i = 0; i < m_pForm->getRootControlCount(); i++) // Process all controls on parent which was created before this one
						if (check(m_pForm->getRootControl(i), m_sInitialRect, new_rect))
							break;
				}
				if (!new_rect.IsValid()) // If rect is invalid, control is invisible
					new_rect = { 0, 0, 0, 0 };
			}
			if (new_rect != m_sRect)
			{
				if (m_pForm)
					m_pForm->LockRepaint();
				bool is_move{ m_sRect.Left != new_rect.Left || m_sRect.Top != new_rect.Top };
				bool is_resize{ m_sRect.Width() != new_rect.Width() || m_sRect.Height() != new_rect.Height() };
				APP_RECT old = m_sRect;
				m_sRect = new_rect;
				if (is_move)
					NotifyOnMove(old.LeftTop(), m_sRect.LeftTop());
				if (is_resize)
					NotifyOnResize({ old.Width(), old.Height() }, { m_sRect.Width(), m_sRect.Height() });
				UpdateRectOfNextParentControl();
				if (m_pForm)
					m_pForm->UnlockRepaint();
			}
		}

		void CControl::Repaint(const bool repaint_children)
		{
			if (m_pForm && getVisibleWithParents())
			{
				m_pForm->LockRepaint();
				m_pForm->Repaint(ClientToForm(getRenderRect()));
				if (repaint_children)
					for (auto pos = m_aControls.begin(); pos != m_aControls.end(); pos++)
						(*pos)->Repaint(true);
				m_pForm->UnlockRepaint();
			}
		}

		void CControl::BringToFront()
		{
			if (m_pParent)
			{
				if (m_pParent->m_aControls[m_pParent->m_aControls.size() - 1] != this)
					BringBefore(m_pParent->getControlCount() + 1);
			}
			else if (m_pForm)
				if (m_pForm->m_aControlsRoot[m_pForm->m_aControlsRoot.size() - 1] != this)
					BringBefore(m_pForm->getRootControlCount() + 1);
		}

		void CControl::BringUp()
		{
			if (m_pParent)
			{
				if (m_pParent->m_aControls[0] != this)
				{
					for (size_t i = 0; i < m_pParent->m_aControls.size(); i++)
						if (m_pParent->m_aControls[i] == this)
						{
							BringBefore(i - 1);
							break;
						}
				}
			}
			else if (m_pForm)
				if (m_pForm->m_aControlsRoot[0] != this)
				{
					for (size_t i = 0; i < m_pForm->m_aControlsRoot.size(); i++)
						if (m_pForm->m_aControlsRoot[i] == this)
						{
							BringBefore(i - 1);
							break;
						}
				}
		}

		void CControl::BringDown()
		{
			if (m_pParent)
			{
				if (m_pParent->m_aControls[m_pParent->m_aControls.size() - 1] != this)
				{
					for (size_t i = 0; i < m_pParent->m_aControls.size(); i++)
						if (m_pParent->m_aControls[i] == this)
						{
							BringBefore(i + 2);
							break;
						}
				}
			}
			else if (m_pForm)
				if (m_pForm->m_aControlsRoot[m_pForm->m_aControlsRoot.size() - 1] != this)
				{
					for (size_t i = 0; i < m_pForm->m_aControlsRoot.size(); i++)
						if (m_pForm->m_aControlsRoot[i] == this)
						{
							BringBefore(i + 2);
							break;
						}
				}
		}

		void CControl::BringBefore(CControl *control)
		{
			if (control && control != this && control->m_pParent == m_pParent && control->m_pForm == m_pForm)
			{
				if (m_pParent)
				{
					for (size_t i = 0; i < m_pParent->m_aControls.size(); i++)
						if (m_pParent->m_aControls[i] == control)
						{
							BringBefore(i);
							break;
						}
				}
				else if (m_pForm)
					for (size_t i = 0; i < m_pForm->m_aControlsRoot.size(); i++)
						if (m_pForm->m_aControlsRoot[i] == control)
						{
							BringBefore(i);
							break;
						}
			}
		}

		void CControl::BringBefore(const size_t index)
		{
			if (m_pParent)
			{
				if (m_pParent->getControl(index) != this)
				{
					if (m_pForm)
						m_pForm->LockRepaint();
					CControl *control{ m_pParent->getControl(index) };
					size_t old_index{ 0 }, new_index{ 0 };
					if (control)
					{
						for (auto pos = m_pParent->m_aControls.begin(); pos != m_pParent->m_aControls.end(); pos++)
							if ((*pos) == this)
							{
								m_pParent->m_aControls.erase(pos);
								break;
							}
							else
								old_index++;
						for (auto pos = m_pParent->m_aControls.begin(); pos != m_pParent->m_aControls.end(); pos++)
							if ((*pos) == control)
							{
								m_pParent->m_aControls.insert(pos - 1, this);
								break;
							}
							else
								new_index++;
					}
					else
						m_pParent->m_aControls.push_back(this);
					if (new_index > old_index)
						m_pParent->m_aControls[old_index]->UpdateRect();
					else
						UpdateRect();
					Repaint(true);
					if (m_pForm)
						m_pForm->UnlockRepaint();
				}
			}
			else if (m_pForm)
			{
				if (m_pForm->getRootControl(index) != this)
				{
					m_pForm->LockRepaint();
					CControl *control{ m_pForm->getRootControl(index) };
					size_t old_index{ 0 }, new_index{ 0 };
					if (control)
					{
						for (auto pos = m_pForm->m_aControlsRoot.begin(); pos != m_pForm->m_aControlsRoot.end(); pos++)
							if ((*pos) == this)
							{
								m_pForm->m_aControlsRoot.erase(pos);
								break;
							}
							else
								old_index++;
						for (auto pos = m_pForm->m_aControlsRoot.begin(); pos != m_pForm->m_aControlsRoot.end(); pos++)
							if ((*pos) == control)
							{
								m_pForm->m_aControlsRoot.insert(pos - 1, this);
								break;
							}
							else
								new_index++;
					}
					else
						m_pForm->m_aControlsRoot.push_back(this);
					if (new_index > old_index)
						m_pForm->m_aControlsRoot[old_index]->UpdateRect();
					else
						UpdateRect();
					Repaint(true);
					m_pForm->UnlockRepaint();
				}
			}
		}

		void CControl::BringAfter(CControl *control)
		{
			if (control && control != this && control->m_pParent == m_pParent && control->m_pForm == m_pForm)
			{
				if (m_pParent)
				{
					for (size_t i = 0; i < m_pParent->m_aControls.size(); i++)
						if (m_pParent->m_aControls[i] == control)
						{
							BringBefore(i + 1);
							break;
						}
				}
				else if (m_pForm)
					for (size_t i = 0; i < m_pForm->m_aControlsRoot.size(); i++)
						if (m_pForm->m_aControlsRoot[i] == control)
						{
							BringBefore(i + 1);
							break;
						}
			}
		}

		void CControl::BringAfter(const size_t index)
		{
			if (m_pParent)
			{
				if (m_pParent->m_aControls[index] != this)
					BringBefore(index + 1);
			}
			else if (m_pForm)
				if (m_pForm->m_aControlsRoot[index] != this)
					BringBefore(index + 1);
		}

		CControl *CControl::FindNextAlignedControl()
		{
			CControl *control{ nullptr };
			if (m_eAlign != alNone && getVisibleWithParents())
			{
				bool found{ false };
				if (getParent())
				{
					for (size_t i = 0; i < getParent()->getControlCount(); i++)
						if (getParent()->getControl(i) == this)
							found = true;
						else if (found && getParent()->getControl(i)->m_bVisible && getParent()->getControl(i)->m_eAlign != alNone)
						{
							control = getParent()->getControl(i);
							break;
						}
				}
				else if (m_pForm)
				{
					for (size_t i = 0; i < m_pForm->getRootControlCount(); i++)
						if (m_pForm->getRootControl(i) == this)
							found = true;
						else if (found && m_pForm->getRootControl(i)->m_bVisible && m_pForm->getRootControl(i)->m_eAlign != alNone)
						{
							control = m_pForm->getRootControl(i);
							break;
						}
				}
			}
			return control;
		}

		void CControl::UpdateRectOfNextParentControl()
		{
			CControl *control{ FindNextAlignedControl() };
			if (control)
				control->UpdateRect();
		}

		bool CControl::UpdateFromStyle()
		{
			return false;
		}
#pragma endregion

#pragma region Render
		void CControl::Render(APP_RECT clip)
		{
			if (!m_bVisible)
				return;
			NotifyOnPaint(clip);
			// Multipass render controls
			size_t z_current, z_next{ 0 };
			do
			{
				z_current = z_next;
				for (auto pos = m_aControls.begin(); pos != m_aControls.end(); pos++)
					if ((*pos)->m_iZIndex == z_current)
					{
						if (std::find(m_pForm->m_aCaptureMouseControls.begin(), m_pForm->m_aCaptureMouseControls.end(), *pos) == m_pForm->m_aCaptureMouseControls.end())
							(*pos)->Render(clip);
					}
					else if ((*pos)->m_iZIndex > z_current)
						if (z_next == z_current)
							z_next = (*pos)->m_iZIndex;
						else
							z_next = std::min(z_next, (*pos)->m_iZIndex);
			} while (z_next != z_current);
		}
#pragma endregion

#pragma region Controls
		CControl *CControl::AddControl(CControl *control)
		{
			// Check control can be added
			if (!control || control == this || control->m_pParent == this || control->getHaveChild(this) || !control->m_bAcceptParent)
				return this;
			CForm *form{ control->m_pForm };
			if (form)
				form->LockRepaint();
			if (m_pForm)
				m_pForm->LockRepaint();
			if (control->m_pParent)
				control->m_pParent->DetachControl(control);
			else
				if (form && form != m_pForm)
					control->setForm(nullptr);
			control->m_pParent = this;
			m_aControls.push_back(control);
			if (m_pForm && m_pForm != form)
				control->AddToForm(m_pForm, false);
			NotifyOnAttachControl(control);
			control->NotifyOnAttachToControl(this);
			if (m_pForm)
				m_pForm->UnlockRepaint();
			if (form)
				form->UnlockRepaint();
			return this;
		}

		CControl *CControl::InsertControl(CControl *control, const size_t before)
		{
			if (before >= m_aControls.size())
				return AddControl(control);
			// Check control can be added
			if (!control || control == this || control->m_pParent == this || control->getHaveChild(this) || !control->m_bAcceptParent)
				return this;
			CForm *form{ control->m_pForm };
			if (form)
				form->LockRepaint();
			if (m_pForm)
				m_pForm->LockRepaint();
			if (control->m_pParent)
				control->m_pParent->DetachControl(control);
			else
				if (form && form != m_pForm)
					control->setForm(nullptr);
			control->m_pParent = this;
			auto pos = m_aControls.begin();
			m_aControls.insert(pos + before, control);
			if (m_pForm && m_pForm != form)
				control->AddToForm(m_pForm, false);
			NotifyOnAttachControl(control);
			control->NotifyOnAttachToControl(this);
			if (m_pForm)
				m_pForm->UnlockRepaint();
			if (form)
				form->UnlockRepaint();
			return this;
		}

		CControl *CControl::DeleteControl(const size_t index)
		{
			if (index < m_aControls.size())
				delete m_aControls[index];
			return this;
		}

		CControl *CControl::DeleteControl(CControl *control)
		{
			for (auto pos = m_aControls.begin(); pos != m_aControls.end(); pos++)
				if ((*pos) == control)
				{
					delete (*pos);
					break;
				}
			return this;
		}

		CControl *CControl::DetachControl(const size_t index)
		{
			if (index < m_aControls.size())
			{
				CControl *control{ m_aControls[index] };
				if (m_pForm)
					m_pForm->LockRepaint();
				control->NotifyOnBeforeDetachFromControl(this);
				NotifyOnBeforeDetachControl(control);
				for (auto pos = m_aControls.begin(); pos != m_aControls.end(); pos++)
					if ((*pos) == control)
					{
						m_aControls.erase(pos);
						break;
					}
				control->m_pParent = nullptr;
				if (control->m_pForm)
					control->RemoveFromForm(); // This will remove links between form and control(with sub-controls)
				NotifyOnDetachControl(control);
				control->NotifyOnDetachFromControl(this);
				if (m_pForm)
					m_pForm->UnlockRepaint();
			}
			return this;
		}

		CControl *CControl::DetachControl(CControl *control)
		{
			for (size_t pos = 0; pos < m_aControls.size(); pos++)
				if (m_aControls[pos] == control)
				{
					DetachControl(pos);
					break;
				}
			return this;
		}

		CControl *CControl::DeleteControls()
		{
			if (m_pForm)
				m_pForm->LockRepaint();
			while (m_aControls.size() > 0)
				DeleteControl((size_t)0);
			if (m_pForm)
				m_pForm->UnlockRepaint();
			return this;
		}
#pragma endregion

#pragma region Coordinates conversions
		APP_RECT CControl::ClientToForm(const APP_RECT &rect)
		{
			APP_RECT result = rect;
			if (m_pParent)
			{
				APP_POINT pos = m_pParent->ClientToForm(m_pParent->getPosition());
				result.Left += pos.X;
				result.Top += pos.Y;
				result.Right += pos.X;
				result.Bottom += pos.Y;
			}
			return result;
		}

		APP_POINT CControl::ClientToForm(const APP_POINT &pos)
		{
			APP_POINT result = pos;
			if (m_pParent)
			{
				APP_POINT pp = m_pParent->ClientToForm(m_pParent->getPosition());
				result.X += pp.X;
				result.Y += pp.Y;
			}
			return result;
		}

		math::POINT<double> CControl::ClientToForm(const math::POINT<double> &pos)
		{
			math::POINT<double> result = pos;
			if (m_pParent)
			{
				APP_POINT pp = m_pParent->ClientToForm(m_pParent->getPosition());
				result.X += pp.X;
				result.Y += pp.Y;
			}
			return result;
		}

		APP_RECT CControl::FormToClient(const APP_RECT &rect)
		{
			APP_RECT result = rect;
			if (m_pParent)
			{
				APP_POINT pos = m_pParent->ClientToForm(m_pParent->getPosition());
				result.Left -= pos.X;
				result.Top -= pos.Y;
				result.Right -= pos.X;
				result.Bottom -= pos.Y;
			}
			return result;
		}

		APP_POINT CControl::FormToClient(const APP_POINT &pos)
		{
			APP_POINT result = pos;
			if (m_pParent)
			{
				APP_POINT pp = m_pParent->ClientToForm(m_pParent->getPosition());
				result.X -= pp.X;
				result.Y -= pp.Y;
			}
			return result;
		}
#pragma endregion

#pragma region Getters
		APP_RECT CControl::getRect()
		{
			return m_sRect;
		}

		APP_RECT CControl::getClientRect()
		{
			return getRect();
		}

		APP_RECT CControl::getRenderRect()
		{
			return getCustomRenderRect(getRect());
		}

		APP_RECT CControl::getCustomRenderRect(const APP_RECT &rect)
		{
			return rect;
		}

		APP_POINT CControl::getPosition()
		{
			return getRect().LeftTop();
		}

		APP_POINT CControl::getSize()
		{
			APP_RECT rect = getRect();
			return{ rect.Width(), rect.Height() };
		}

		int CControl::getLeft()
		{
			return getRect().Left;
		}

		int CControl::getTop()
		{
			return getRect().Top;
		}

		int CControl::getWidth()
		{
			return getRect().Width();
		}

		int CControl::getHeight()
		{
			return getRect().Height();
		}

		size_t CControl::getControlCount() const
		{
			return m_aControls.size();
		}

		CControl *CControl::getControl(const int index)
		{
			if (index >=0 && index < (int)m_aControls.size())
				return m_aControls[index];
			return nullptr;
		}

		CControl *CControl::getControlAtPosition(const int x, const int y)
		{
			if (!m_bVisible)
				return nullptr;
			APP_RECT rect = getVisibleRect();
			CControl *control;
			for (int index = (int)m_aControls.size() - 1; index >= 0; index--)
			{
				control = m_aControls[index]->getControlAtPosition(x, y);
				if (control)
					return control;
			}
			if (x < rect.Left || x >= rect.Right || y < rect.Top || y >= rect.Bottom)
				return nullptr;
			return this;
		}

		CControl *CControl::getParent()
		{
			return m_pParent;
		}

		bool CControl::getEnabled() const
		{
			return m_bEnabled;
		}

		bool CControl::getVisible() const
		{
			return m_bVisible;
		}

		ALIGN CControl::getAlign() const
		{
			return m_eAlign;
		}

		bool CControl::getTabStop() const
		{
			return m_bTabStop;
		}

		size_t CControl::getTabOrder() const
		{
			return m_iTabOrder;
		}

		CStyle *CControl::getControlStyle()
		{
			return m_pStyle;
		}

		CStyle *CControl::getStyle()
		{
			if (!m_bUseStyle)
				return nullptr;
			if (m_pStyle)
				return m_pStyle;
			CControl *parent{ m_pParent };
			while (parent)
			{
				if (parent->m_pStyle)
					return parent->m_pStyle;
				parent = parent->m_pParent;
			}
			if (m_pForm)
				return m_pForm->getStyle();
			return nullptr;
		}

		bool CControl::getUseStyle() const
		{
			return m_bUseStyle;
		}

		math::RECTANGLE<size_t> CControl::getConstraints() const
		{
			return m_sConstraints;
		}

		math::POINT<size_t> CControl::getMinConstraints() const
		{
			return getConstraints().LeftTop();
		}

		math::POINT<size_t> CControl::getMaxConstraints() const
		{
			return getConstraints().RightBottom();
		}

		size_t CControl::getMinWidth() const
		{
			return getConstraints().Left;
		}

		size_t CControl::getMinHeight() const
		{
			return getConstraints().Top;
		}

		size_t CControl::getMaxWidth() const
		{
			return getConstraints().Right;
		}

		size_t CControl::getMaxHeight() const
		{
			return getConstraints().Bottom;
		}

		bool CControl::getAcceptFocus() const
		{
			return m_bAcceptFocus;
		}

		bool CControl::getAcceptForm() const
		{
			return m_bAcceptForm;
		}

		bool CControl::getAcceptFormWithParents() const
		{
			if (m_pParent)
				return m_bAcceptForm && m_pParent->getAcceptFormWithParents();
			return m_bAcceptForm;
		}

		bool CControl::getAcceptControls() const
		{
			return m_bAcceptControls;
		}

		bool CControl::getAcceptParent() const
		{
			return false;
		}

		bool CControl::getSupportText() const
		{
			return m_bSupportText;
		}

		IFont *CControl::getControlFont()
		{
			if (!m_pFont && m_pForm && m_pForm->getPresenter())
			{
				// Create font
				CStyleFont *font{ nullptr };
				CStyle *style{ getStyle() };
				if (style && (font = style->getFontByName(m_sClassName)))
					m_pFont = m_pForm->getPresenter()->FontCreate(font);
				else
					m_pFont = m_pForm->getPresenter()->FontCreate(&m_cDefaultFont);
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
			}
			return m_pFont;
		}

		IFont *CControl::getParentFont()
		{
			CControl *parent{ m_pParent };
			while (parent)
			{
				if (!parent->m_bUseParentFont)
					return parent->getControlFont();
				parent = parent->m_pParent;
			}
			if (m_pForm)
				return m_pForm->getFont();
			return nullptr;
		}

		IFont *CControl::getFont()
		{
			return m_bUseParentFont ? getParentFont() : getControlFont();
		}

		bool CControl::getUseParentFont() const
		{
			return m_bUseParentFont;
		}

		CURSOR_TYPE CControl::getCursor() const
		{
			return m_eCursor;
		}

		bool CControl::getVisibleWithParents() const
		{
			if (!m_bVisible)
				return false;
			CControl *parent = m_pParent;
			while (parent)
			{
				if (!m_pParent->m_bVisible)
					return false;
				parent = parent->m_pParent;
			}
			return true;
		}

		bool CControl::getEnabledWithParents() const
		{
			if (!m_bEnabled)
				return false;
			CControl *parent = m_pParent;
			while (parent)
			{
				if (!m_pParent->m_bEnabled)
					return false;
				parent = parent->m_pParent;
			}
			return true;
		}

		APP_RECT CControl::getVisibleRect()
		{
			APP_RECT result = ClientToForm(getRenderRect());
			if (m_pParent)
			{
				result *= m_pParent->ClientToForm(m_pParent->getClientRect());
				result *= m_pParent->getVisibleRect();
			}
			if (m_pForm && m_pForm->getWindow())
				result *= m_pForm->getWindow()->getClientRect();
			return result;
		}

		size_t CControl::getZIndex() const
		{
			return m_iZIndex;
		}
#pragma endregion

#pragma region Calbacks getters
		CControl::FOnMouseHover CControl::getOnMouseHover() const
		{
			return m_fOnMouseHover;
		}

		CControl::FOnMouseLeave CControl::getOnMouseLeave() const
		{
			return m_fOnMouseLeave;
		}

		CControl::FOnKillFocus CControl::getOnKillFocus() const
		{
			return m_fOnKillFocus;
		}

		CControl::FOnSetFocus CControl::getOnSetFocus() const
		{
			return m_fOnSetFocus;
		}

		CControl::FOnResetFocus CControl::getOnResetFocus() const
		{
			return m_fOnResetFocus;
		}

		CControl::FOnKillCaptureKeyboard CControl::getOnKillCaptureKeyboard() const
		{
			return m_fOnKillCaptureKeyboard;
		}

		CControl::FOnKillCaptureMouse CControl::getOnKillCaptureMouse() const
		{
			return m_fOnKillCaptureMouse;
		}

		CControl::FOnSetCaptureKeyboard CControl::getOnSetCaptureKeyboard() const
		{
			return m_fOnSetCaptureKeyboard;
		}

		CControl::FOnSetCaptureMouse CControl::getOnSetCaptureMouse() const
		{
			return m_fOnSetCaptureMouse;
		}

		CControl::FOnKeyDown CControl::getOnKeyDown() const
		{
			return m_fOnKeyDown;
		}

		CControl::FOnKeyUp CControl::getOnKeyUp() const
		{
			return m_fOnKeyUp;
		}

		CControl::FOnChar CControl::getOnChar() const
		{
			return m_fOnChar;
		}

		CControl::FOnDeadChar CControl::getOnDeadChar() const
		{
			return m_fOnDeadChar;
		}

		CControl::FOnSysKeyDown CControl::getOnSysKeyDown() const
		{
			return m_fOnSysKeyDown;
		}

		CControl::FOnSysKeyUp CControl::getOnSysKeyUp() const
		{
			return m_fOnSysKeyUp;
		}

		CControl::FOnSysChar CControl::getOnSysChar() const
		{
			return m_fOnSysChar;
		}

		CControl::FOnSysDeadChar CControl::getOnSysDeadChar() const
		{
			return m_fOnSysDeadChar;
		}

		CControl::FOnMouseMove CControl::getOnMouseMove() const
		{
			return m_fOnMouseMove;
		}

		CControl::FOnLeftMouseButtonDown CControl::getOnLeftMouseButtonDown() const
		{
			return m_fOnLeftMouseButtonDown;
		}

		CControl::FOnLeftMouseButtonUp CControl::getOnLeftMouseButtonUp() const
		{
			return m_fOnLeftMouseButtonUp;
		}

		CControl::FOnLeftMouseButtonDoubleClick CControl::getOnLeftMouseButtonDoubleClick() const
		{
			return m_fOnLeftMouseButtonDoubleClick;
		}

		CControl::FOnRightMouseButtonDown CControl::getOnRightMouseButtonDown() const
		{
			return m_fOnRightMouseButtonDown;
		}

		CControl::FOnRightMouseButtonUp CControl::getOnRightMouseButtonUp() const
		{
			return m_fOnRightMouseButtonUp;
		}

		CControl::FOnRightMouseButtonDoubleClick CControl::getOnRightMouseButtonDoubleClick() const
		{
			return m_fOnRightMouseButtonDoubleClick;
		}

		CControl::FOnMiddleMouseButtonDown CControl::getOnMiddleMouseButtonDown() const
		{
			return m_fOnMiddleMouseButtonDown;
		}

		CControl::FOnMiddleMouseButtonUp CControl::getOnMiddleMouseButtonUp() const
		{
			return m_fOnMiddleMouseButtonUp;
		}

		CControl::FOnMiddleMouseButtonDoubleClick CControl::getOnMiddleMouseButtonDoubleClick() const
		{
			return m_fOnMiddleMouseButtonDoubleClick;
		}

		CControl::FOnMouseVerticalWheel CControl::getOnMouseVerticalWheel() const
		{
			return m_fOnMouseVerticalWheel;
		}

		CControl::FOnMouseHorizontalWheel CControl::getOnMouseHorizontalWheel() const
		{
			return m_fOnMouseHorizontalWheel;
		}

		CControl::FOnChangeParentStyle CControl::getOnChangeParentStyle() const
		{
			return m_fOnChangeParentStyle;
		}

		CControl::FOnParentFontChangeName CControl::getOnParentFontChangeName() const
		{
			return m_fOnParentFontChangeName;
		}

		CControl::FOnParentFontChangeHeight CControl::getOnParentFontChangeHeight() const
		{
			return m_fOnParentFontChangeHeight;
		}

		CControl::FOnParentFontChangeWeight CControl::getOnParentFontChangeWeight() const
		{
			return m_fOnParentFontChangeWeight;
		}

		CControl::FOnParentFontChangeItalic CControl::getOnParentFontChangeItalic() const
		{
			return m_fOnParentFontChangeItalic;
		}

		CControl::FOnParentFontChangeUnderline CControl::getOnParentFontChangeUnderline() const
		{
			return m_fOnParentFontChangeUnderline;
		}

		CControl::FOnParentFontChangeStrikeOut CControl::getOnParentFontChangeStrikeOut() const
		{
			return m_fOnParentFontChangeStrikeOut;
		}

		CControl::FOnParentFontChangeWidth CControl::getOnParentFontChangeWidth() const
		{
			return m_fOnParentFontChangeWidth;
		}

		CControl::FOnParentFontChangeCharSet CControl::getOnParentFontChangeCharSet() const
		{
			return m_fOnParentFontChangeCharSet;
		}

		CControl::FOnParentFontChangeQuality CControl::getOnParentFontChangeQuality() const
		{
			return m_fOnParentFontChangeQuality;
		}

		CControl::FOnParentFontChangePitchAndFamily CControl::getOnParentFontChangePitchAndFamily() const
		{
			return m_fOnParentFontChangePitchAndFamily;
		}

		CControl::FOnParentFontChangeOrientation CControl::getOnParentFontChangeOrientation() const
		{
			return m_fOnParentFontChangeOrientation;
		}

		CControl::FOnParentFontChangeDistance CControl::getOnParentFontChangeDistance() const
		{
			return m_fOnParentFontChangeDistance;
		}

		CControl::FOnParentFontChangeShadow CControl::getOnParentFontChangeShadow() const
		{
			return m_fOnParentFontChangeShadow;
		}

		CControl::FOnParentFontChangeShadowShift CControl::getOnParentFontChangeShadowShift() const
		{
			return m_fOnParentFontChangeShadowShift;
		}

		CControl::FOnParentFontChangeShadowBlur CControl::getOnParentFontChangeShadowBlur() const
		{
			return m_fOnParentFontChangeShadowBlur;
		}

		CControl::FOnParentFontChangeShadowColor CControl::getOnParentFontChangeShadowColor() const
		{
			return m_fOnParentFontChangeShadowColor;
		}

		CControl::FOnParentFontChangeColor CControl::getOnParentFontChangeColor() const
		{
			return m_fOnParentFontChangeColor;
		}

		CControl::FOnParentFontChangeInterpolate CControl::getOnParentFontChangeInterpolate() const
		{
			return m_fOnParentFontChangeInterpolate;
		}

		CControl::FOnParentFontBeginChange CControl::getOnParentFontBeginChange() const
		{
			return m_fOnParentFontBeginChange;
		}

		CControl::FOnParentFontEndChange CControl::getOnParentFontEndChange() const
		{
			return m_fOnParentFontEndChange;
		}

		CControl::FOnParentFontChangeSize CControl::getOnParentFontChangeSize() const
		{
			return m_fOnParentFontChangeSize;
		}

		CControl::FOnParentFontChangeStyle CControl::getOnParentFontChangeStyle() const
		{
			return m_fOnParentFontChangeColor;
		}

		CControl::FOnChangeUseParentFont CControl::getOnChangeUseParentFont() const
		{
			return m_fOnChangeUseParentFont;
		}

		CControl::FOnFontChangeName CControl::getOnFontChangeName() const
		{
			return m_fOnFontChangeName;
		}

		CControl::FOnFontChangeHeight CControl::getOnFontChangeHeight() const
		{
			return m_fOnFontChangeHeight;
		}

		CControl::FOnFontChangeWeight CControl::getOnFontChangeWeight() const
		{
			return m_fOnFontChangeWeight;
		}

		CControl::FOnFontChangeItalic CControl::getOnFontChangeItalic() const
		{
			return m_fOnFontChangeItalic;
		}

		CControl::FOnFontChangeUnderline CControl::getOnFontChangeUnderline() const
		{
			return m_fOnFontChangeUnderline;
		}

		CControl::FOnFontChangeStrikeOut CControl::getOnFontChangeStrikeOut() const
		{
			return m_fOnFontChangeStrikeOut;
		}

		CControl::FOnFontChangeWidth CControl::getOnFontChangeWidth() const
		{
			return m_fOnFontChangeWidth;
		}

		CControl::FOnFontChangeCharSet CControl::getOnFontChangeCharSet() const
		{
			return m_fOnFontChangeCharSet;
		}

		CControl::FOnFontChangeQuality CControl::getOnFontChangeQuality() const
		{
			return m_fOnFontChangeQuality;
		}

		CControl::FOnFontChangePitchAndFamily CControl::getOnFontChangePitchAndFamily() const
		{
			return m_fOnFontChangePitchAndFamily;
		}

		CControl::FOnFontChangeOrientation CControl::getOnFontChangeOrientation() const
		{
			return m_fOnFontChangeOrientation;
		}

		CControl::FOnFontChangeDistance CControl::getOnFontChangeDistance() const
		{
			return m_fOnFontChangeDistance;
		}

		CControl::FOnFontChangeShadow CControl::getOnFontChangeShadow() const
		{
			return m_fOnFontChangeShadow;
		}

		CControl::FOnFontChangeShadowShift CControl::getOnFontChangeShadowShift() const
		{
			return m_fOnFontChangeShadowShift;
		}

		CControl::FOnFontChangeShadowBlur CControl::getOnFontChangeShadowBlur() const
		{
			return m_fOnFontChangeShadowBlur;
		}

		CControl::FOnFontChangeShadowColor CControl::getOnFontChangeShadowColor() const
		{
			return m_fOnFontChangeShadowColor;
		}

		CControl::FOnFontChangeColor CControl::getOnFontChangeColor() const
		{
			return m_fOnFontChangeColor;
		}

		CControl::FOnFontChangeInterpolate CControl::getOnFontChangeInterpolate() const
		{
			return m_fOnFontChangeInterpolate;
		}

		CControl::FOnFontBeginChange CControl::getOnFontBeginChange() const
		{
			return m_fOnFontBeginChange;
		}

		CControl::FOnFontEndChange CControl::getOnFontEndChange() const
		{
			return m_fOnFontEndChange;
		}

		CControl::FOnFontChangeSize CControl::getOnFontChangeSize() const
		{
			return m_fOnFontChangeSize;
		}

		CControl::FOnFontChangeStyle CControl::getOnFontChangeStyle() const
		{
			return m_fOnFontChangeStyle;
		}

		CControl::FOnChildControlResize CControl::getOnChildControlResize() const
		{
			return m_fOnChildControlResize;
		}

		CControl::FOnChildControlMove CControl::getOnChildControlMove() const
		{
			return m_fOnChildControlMove;
		}

		CControl::FOnParentResize CControl::getOnParentResize() const
		{
			return m_fOnParentResize;
		}

		CControl::FOnParentMove CControl::getOnParentMove() const
		{
			return m_fOnParentMove;
		}

		CControl::FOnChangeStyle CControl::getOnChangeStyle() const
		{
			return m_fOnChangeStyle;
		}

		CControl::FOnShow CControl::getOnShow() const
		{
			return m_fOnShow;
		}

		CControl::FOnBeforeHide CControl::getOnBeforeHide() const
		{
			return m_fOnBeforeHide;
		}

		CControl::FOnHide CControl::getOnHide() const
		{
			return m_fOnHide;
		}

		CControl::FOnEnable CControl::getOnEnable() const
		{
			return m_fOnEnable;
		}

		CControl::FOnDisable CControl::getOnDisable() const
		{
			return m_fOnDisable;
		}

		CControl::FOnAttachControl CControl::getOnAttachControl() const
		{
			return m_fOnAttachControl;
		}

		CControl::FOnBeforeDetachControl CControl::getOnBeforeDetachControl() const
		{
			return m_fOnBeforeDetachControl;
		}

		CControl::FOnDetachControl CControl::getOnDetachControl() const
		{
			return m_fOnDetachControl;
		}

		CControl::FOnPaint CControl::getOnPaint() const
		{
			return m_fOnPaint;
		}

		CControl::FOnBeforeResize CControl::getOnBeforeResize() const
		{
			return m_fOnBeforeResize;
		}

		CControl::FOnResize CControl::getOnResize() const
		{
			return m_fOnResize;
		}

		CControl::FOnBeforeMove CControl::getOnBeforeMove() const
		{
			return m_fOnBeforeMove;
		}

		CControl::FOnMove CControl::getOnMove() const
		{
			return m_fOnMove;
		}

		CControl::FOnBeforeDetachFromControl CControl::getOnBeforeDetachFromControl() const
		{
			return m_fOnBeforeDetachFromControl;
		}

		CControl::FOnDetachFromControl CControl::getOnDetachFromControl() const
		{
			return m_fOnDetachFromControl;
		}

		CControl::FOnAttachToControl CControl::getOnAttachToControl() const
		{
			return m_fOnAttachToControl;
		}
#pragma endregion

#pragma region Setters
		bool CControl::setForm(CForm *value)
		{
			if (value != m_pForm)
			{
				if (!m_bAcceptForm)
					return false;
				// Remove control from parent & form
				if (m_pParent)
					m_pParent->DetachControl(this);
				else
				{
					CForm *form{ m_pForm };
					if (form)
					{
						CControl *after{ FindNextAlignedControl() };
						form->LockRepaint();
						form->NotifyOnBeforeDetachControl(this);
						RemoveFromForm();
						form->NotifyOnDetachControl(this);
						if (after)
							after->UpdateRect();
						form->UpdateHoveredControl();
						form->UnlockRepaint();
					}
				}
				// Add control to controls list and rename
				if (value)
				{
					value->LockRepaint();
					AddToForm(value, true); // Add to form controls list will be done only if it is allowed
					if (m_bUseStyle && !m_pStyle)
						NotifyOnChangeParentStyle();
					if (m_bUseParentFont && m_bSupportText)
						NotifyOnParentFontChangeSize();
					UpdateRect();
					value->NotifyOnAttachControl(this);
					value->UnlockRepaint();
				}
			}
			return true;
		}

		bool CControl::setName(const String &value)
		{
			// Name should not be empty, should differ from already set, form(if assigned) should not have component with same name
			if (value.empty())
				return false;
			if (value == m_sName)
				return true;
			if (m_pForm)
			{
				if (m_pForm->ValidateControlName(value, this))
				{
					m_sName = value;
					m_pForm->m_bIsControlsSorted = false;
					return true;
				}
				return false;
			}
			m_sName == value;
			return true;
		}

		CControl *CControl::setRect(APP_RECT value)
		{
			if (!value.IsValid())
				return this;
			// Check change is required
			if (value == m_sRect && m_eAlign == alNone)
				return this;
			// Adjust size to constraints
			if (value.Width() < (int)m_sConstraints.Left)
				value.Right = value.Left + m_sConstraints.Left;
			else if (m_sConstraints.Right > 0 && value.Width() > (int)m_sConstraints.Right)
				value.Right = value.Left + m_sConstraints.Right;
			if (value.Height() < (int)m_sConstraints.Top)
				value.Bottom = value.Top + m_sConstraints.Top;
			else if (m_sConstraints.Bottom > 0 && value.Height() > (int)m_sConstraints.Bottom)
				value.Bottom = value.Top + m_sConstraints.Bottom;
			// Check change is required
			if (value == m_sRect && m_eAlign == alNone)
				return this;
			m_eAlign = alNone;
			m_sInitialRect = value;
			if (m_pForm)
				m_pForm->LockRepaint();
			UpdateRect();
			if (m_pForm)
			{
				m_pForm->UpdateHoveredControl();
				m_pForm->UnlockRepaint();
			}
			return this;
		}

		CControl *CControl::setPosition(const APP_POINT &value)
		{
			APP_RECT rect = getRect();
			return setRect({ value.X, value.Y, value.X + rect.Width(), value.Y + rect.Height() });
		}

		CControl *CControl::setLeft(const int value)
		{
			APP_RECT rect = getRect();
			return setRect({ value, rect.Top, value + rect.Width(), rect.Bottom });
		}

		CControl *CControl::setTop(const int value)
		{
			APP_RECT rect = getRect();
			return setRect({ rect.Left, value, rect.Right, value + rect.Height() });
		}

		CControl *CControl::setSize(const size_t width, const size_t height)
		{
			APP_RECT rect = getRect();
			return setRect({ rect.Left, rect.Top, rect.Left + (int)width, rect.Top + (int)height });
		}

		CControl *CControl::setWidth(const int value)
		{
			APP_RECT rect = getRect();
			return setRect({ rect.Left, rect.Top, rect.Left + value, rect.Bottom });
		}

		CControl *CControl::setHeight(const int value)
		{
			APP_RECT rect = getRect();
			return setRect({ rect.Left, rect.Top, rect.Right, rect.Top + value });
		}

		CControl *CControl::setParent(CControl *control)
		{
			if (!control && m_pParent)
				m_pParent->DetachControl(this);
			else if (control && control != m_pParent && control->m_bAcceptControls && !getHaveChild(control))
				control->AddControl(this);
			return this;
		}

		CControl *CControl::setEnabled(const bool value)
		{
			if (value != m_bEnabled)
			{
				if (m_pForm)
					m_pForm->LockRepaint();
				m_bEnabled = value;
				m_bEnabled ? NotifyOnEnable() : NotifyOnDisable();
				if (m_pForm) // Disabled controls(or it's childs) cannot have focus or capture keyboard/mouse events
				{
					if (!m_bEnabled)
					{
						if (m_pForm->m_pActiveControl && !m_pForm->m_pActiveControl->getEnabledWithParents())
							m_pForm->setActiveControl(nullptr);
						if (m_pForm->m_pCaptureKeyboardControl && !m_pForm->m_pCaptureKeyboardControl->getEnabledWithParents())
							m_pForm->ReleaseCaptureKeyboard();
						if (m_pForm->m_pCaptureMouseControl && !m_pForm->m_pCaptureMouseControl->getEnabledWithParents())
							m_pForm->ReleaseCaptureMouse();
					}
					m_pForm->UpdateHoveredControl();
					m_pForm->UnlockRepaint();
				}
			}
			return this;
		}

		CControl *CControl::setVisible(const bool value)
		{
			if (value != m_bVisible)
			{
				if (m_pForm)
					m_pForm->LockRepaint();
				if (!value)
					NotifyOnBeforeHide();
				m_bVisible = value;
				UpdateRect();
				m_bVisible ? NotifyOnShow() : NotifyOnHide();
				if (m_pForm)
				{
					if (!m_bVisible) // Invisible controls(or it's childs) cannot have focus or capture keyboard/mouse events
					{
						if (m_pForm->m_pActiveControl && !m_pForm->m_pActiveControl->getVisibleWithParents())
							m_pForm->setActiveControl(nullptr);
						if (m_pForm->m_pCaptureKeyboardControl && !m_pForm->m_pCaptureKeyboardControl->getVisibleWithParents())
							m_pForm->ReleaseCaptureKeyboard();
						if (m_pForm->m_pCaptureMouseControl && !m_pForm->m_pCaptureMouseControl->getVisibleWithParents())
							m_pForm->ReleaseCaptureMouse();
					}
					m_pForm->UpdateHoveredControl();
					m_pForm->UnlockRepaint();
				}
			}
			return this;
		}

		CControl *CControl::setAlign(const ALIGN value)
		{
			if (value != m_eAlign)
			{
				if (m_pForm)
					m_pForm->LockRepaint();
				m_eAlign = value;
				UpdateRect();
				if (m_pForm)
				{
					m_pForm->UpdateHoveredControl();
					m_pForm->UnlockRepaint();
				}
			}
			return this;
		}

		CControl *CControl::setTabStop(const bool value)
		{
			m_bTabStop = value;
			return this;
		}

		CControl *CControl::setTabOrder(const size_t value)
		{
			if (value == m_iTabOrder)
				return this;
			if (m_pForm)
			{
				size_t max = m_pForm->CalculateTotalControlCount(), new_order = value;
				if (new_order > max)
					new_order = max;
				if (m_iTabOrder != new_order)
				{
					m_pForm->UpdateTabOrders(m_iTabOrder, new_order);
					m_iTabOrder = new_order;
				}
			}
			else
				m_iTabOrder = value;
			return this;
		}

		CControl *CControl::setStyle(CStyle *value)
		{
			if (value != m_pStyle || !m_bUseStyle)
			{
				if (m_pForm)
					m_pForm->LockRepaint();
				// Change style & font if required
				m_bUseStyle = value ? true : false;
				m_pStyle = value;
				if (!m_bUseParentFont)
				{
					CStyle *style{ getStyle() };
					CStyleFont *font;
					IFont *f;
					if (style && (f = getControlFont()) && (font = style->getFontByName(m_sClassName)))
					{
						
						f
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
				// Add new rect to repaint area
				if (m_pForm)
				{
					m_pForm->UpdateHoveredControl();
					m_pForm->UnlockRepaint();
				}
			}
			return this;
		}

		CControl *CControl::setUseStyle(const bool value)
		{
			if (value != m_bUseStyle)
			{
				if (m_pForm)
					m_pForm->LockRepaint();
				m_bUseStyle = value;
				NotifyOnChangeStyle();
				if (m_pForm)
				{
					m_pForm->UpdateHoveredControl();
					m_pForm->UnlockRepaint();
				}
			}
			return this;
		}

		CControl *CControl::setConstraints(const math::RECTANGLE<size_t> &value)
		{
			if (value != m_sConstraints)
			{
				m_sConstraints = value;
				// Check control size for new limits
				int w{ m_sInitialRect.Width() }, h{ m_sInitialRect.Height() };
				if (w < (int)m_sConstraints.Left || (m_sConstraints.Right > 0 && w > (int)m_sConstraints.Right) || h < (int)m_sConstraints.Top || (m_sConstraints.Bottom > 0 && h > (int)m_sConstraints.Bottom))
				{
					if (m_pForm)
						m_pForm->LockRepaint();
					if (w < (int)m_sConstraints.Left)
						m_sInitialRect.Right = m_sInitialRect.Left + m_sConstraints.Left;
					else if (m_sConstraints.Right > 0 && w > (int)m_sConstraints.Right)
						m_sInitialRect.Right = m_sInitialRect.Left + m_sConstraints.Right;
					if (h < (int)m_sConstraints.Top)
						m_sInitialRect.Bottom = m_sInitialRect.Top + m_sConstraints.Top;
					else if (m_sConstraints.Bottom > 0 && w > (int)m_sConstraints.Bottom)
						m_sInitialRect.Bottom = m_sInitialRect.Top + m_sConstraints.Bottom;
					UpdateRect();
					if (m_pForm)
					{
						m_pForm->UpdateHoveredControl();
						m_pForm->UnlockRepaint();
					}
				}
			}
			return this;
		}

		CControl *CControl::setMinConstraints(const math::POINT<size_t> &value)
		{
			return setConstraints({ value.X, value.Y, m_sConstraints.Right, m_sConstraints.Bottom });
		}

		CControl *CControl::setMaxConstraints(const math::POINT<size_t> &value)
		{
			return setConstraints({ m_sConstraints.Left, m_sConstraints.Top, value.X, value.Y });
		}

		CControl *CControl::setMinWidth(const size_t value)
		{
			return setConstraints({ value, m_sConstraints.Top, m_sConstraints.Right, m_sConstraints.Bottom });
		}

		CControl *CControl::setMinHeight(const size_t value)
		{
			return setConstraints({ m_sConstraints.Left, value, m_sConstraints.Right, m_sConstraints.Bottom });
		}

		CControl *CControl::setMaxWidth(const size_t value)
		{
			return setConstraints({ m_sConstraints.Left, m_sConstraints.Top, value, m_sConstraints.Bottom });
		}

		CControl *CControl::setMaxHeight(const size_t value)
		{
			return setConstraints({ m_sConstraints.Left, m_sConstraints.Top, m_sConstraints.Right, value });
		}

		CControl *CControl::setControlFont(const IFont* value)
		{
			IFont *font;
			if (value && (font = getControlFont()))
			{
				if (m_pForm)
					m_pForm->LockRepaint();
				font
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
				if (m_pForm)
					m_pForm->UnlockRepaint();
			}
			return this;
		}

		CControl *CControl::setFont(const IFont *value)
		{
			if (value)
			{
				if (m_pForm)
					m_pForm->LockRepaint();
				setUseParentFont(false);
				setControlFont(value);
				if (m_pForm)
					m_pForm->UnlockRepaint();
			}
			return this;
		}

		CControl *CControl::setUseParentFont(const bool value)
		{
			if (value != m_bUseParentFont)
			{
				if (m_pForm)
					m_pForm->LockRepaint();
				m_bUseParentFont = value;
				NotifyOnChangeUseParentFont();
				if (m_pForm)
					m_pForm->UnlockRepaint();
			}
			return this;
		}
		
		CControl *CControl::setFocus()
		{
			if (m_pForm)
				m_pForm->setActiveControl(this);
			return this;
		}

		CControl *CControl::setCursor(const CURSOR_TYPE value)
		{
			if (value != m_eCursor)
			{
				m_eCursor = value;
				if (m_pForm && m_pForm->getHoveredControl() == this)
					m_pForm->getWindow()->setCursor(m_eCursor);
			}
			return this;
		}

		CControl *CControl::setZIndex(const size_t value)
		{
			if (value != m_iZIndex)
			{
				m_iZIndex = value;
				Repaint(true);
			}
			return this;
		}
#pragma endregion

#pragma region Callbacks setters
		CControl *CControl::setOnMouseHover(FOnMouseHover value)
		{
			m_fOnMouseHover = value;
			return this;
		}

		CControl *CControl::setOnMouseLeave(FOnMouseLeave value)
		{
			m_fOnMouseLeave = value;
			return this;
		}

		CControl *CControl::setOnKillFocus(FOnKillFocus value)
		{
			m_fOnKillFocus = value;
			return this;
		}

		CControl *CControl::setOnSetFocus(FOnSetFocus value)
		{
			m_fOnSetFocus = value;
			return this;
		}

		CControl *CControl::setOnResetFocus(FOnResetFocus value)
		{
			m_fOnResetFocus = value;
			return this;
		}

		CControl *CControl::setOnKillCaptureKeyboard(FOnKillCaptureKeyboard value)
		{
			m_fOnKillCaptureKeyboard = value;
			return this;
		}

		CControl *CControl::setOnKillCaptureMouse(FOnKillCaptureMouse value)
		{
			m_fOnKillCaptureMouse = value;
			return this;
		}

		CControl *CControl::setOnSetCaptureKeyboard(FOnSetCaptureKeyboard value)
		{
			m_fOnSetCaptureKeyboard = value;
			return this;
		}

		CControl *CControl::setOnSetCaptureMouse(FOnSetCaptureMouse value)
		{
			m_fOnSetCaptureMouse = value;
			return this;
		}

		CControl *CControl::setOnKeyDown(FOnKeyDown value)
		{
			m_fOnKeyDown = value;
			return this;
		}

		CControl *CControl::setOnKeyUp(FOnKeyUp value)
		{
			m_fOnKeyUp = value;
			return this;
		}

		CControl *CControl::setOnChar(FOnChar value)
		{
			m_fOnChar = value;
			return this;
		}

		CControl *CControl::setOnDeadChar(FOnDeadChar value)
		{
			m_fOnDeadChar = value;
			return this;
		}

		CControl *CControl::setOnSysKeyDown(FOnSysKeyDown value)
		{
			m_fOnSysKeyDown = value;
			return this;
		}

		CControl *CControl::setOnSysKeyUp(FOnSysKeyUp value)
		{
			m_fOnSysKeyUp = value;
			return this;
		}

		CControl *CControl::setOnSysChar(FOnSysChar value)
		{
			m_fOnSysChar = value;
			return this;
		}

		CControl *CControl::setOnSysDeadChar(FOnSysDeadChar value)
		{
			m_fOnSysDeadChar = value;
			return this;
		}

		CControl *CControl::setOnMouseMove(FOnMouseMove value)
		{
			m_fOnMouseMove = value;
			return this;
		}

		CControl *CControl::setOnLeftMouseButtonDown(FOnLeftMouseButtonDown value)
		{
			m_fOnLeftMouseButtonDown = value;
			return this;
		}

		CControl *CControl::setOnLeftMouseButtonUp(FOnLeftMouseButtonUp value)
		{
			m_fOnLeftMouseButtonUp = value;
			return this;
		}

		CControl *CControl::setOnLeftMouseButtonDoubleClick(FOnLeftMouseButtonDoubleClick value)
		{
			m_fOnLeftMouseButtonDoubleClick = value;
			return this;
		}

		CControl *CControl::setOnRightMouseButtonDown(FOnRightMouseButtonDown value)
		{
			m_fOnRightMouseButtonDown = value;
			return this;
		}

		CControl *CControl::setOnRightMouseButtonUp(FOnRightMouseButtonUp value)
		{
			m_fOnRightMouseButtonUp = value;
			return this;
		}

		CControl *CControl::setOnRightMouseButtonDoubleClick(FOnRightMouseButtonDoubleClick value)
		{
			m_fOnRightMouseButtonDoubleClick = value;
			return this;
		}

		CControl *CControl::setOnMiddleMouseButtonDown(FOnMiddleMouseButtonDown value)
		{
			m_fOnMiddleMouseButtonDown = value;
			return this;
		}

		CControl *CControl::setOnMiddleMouseButtonUp(FOnMiddleMouseButtonUp value)
		{
			m_fOnMiddleMouseButtonUp = value;
			return this;
		}

		CControl *CControl::setOnMiddleMouseButtonDoubleClick(FOnMiddleMouseButtonDoubleClick value)
		{
			m_fOnMiddleMouseButtonDoubleClick = value;
			return this;
		}

		CControl *CControl::setOnMouseVerticalWheel(FOnMouseVerticalWheel value)
		{
			m_fOnMouseVerticalWheel = value;
			return this;
		}

		CControl *CControl::setOnMouseHorizontalWheel(FOnMouseHorizontalWheel value)
		{
			m_fOnMouseHorizontalWheel = value;
			return this;
		}

		CControl *CControl::setOnChangeParentStyle(FOnChangeParentStyle value)
		{
			m_fOnChangeParentStyle = value;
			return this;
		}

		CControl *CControl::setOnParentFontChangeName(FOnParentFontChangeName value)
		{
			m_fOnParentFontChangeName = value;
			return this;
		}

		CControl *CControl::setOnParentFontChangeHeight(FOnParentFontChangeHeight value)
		{
			m_fOnParentFontChangeHeight = value;
			return this;
		}

		CControl *CControl::setOnParentFontChangeWeight(FOnParentFontChangeWeight value)
		{
			m_fOnParentFontChangeWeight = value;
			return this;
		}

		CControl *CControl::setOnParentFontChangeItalic(FOnParentFontChangeItalic value)
		{
			m_fOnParentFontChangeItalic = value;
			return this;
		}

		CControl *CControl::setOnParentFontChangeUnderline(FOnParentFontChangeUnderline value)
		{
			m_fOnParentFontChangeUnderline = value;
			return this;
		}

		CControl *CControl::setOnParentFontChangeStrikeOut(FOnParentFontChangeStrikeOut value)
		{
			m_fOnParentFontChangeStrikeOut = value;
			return this;
		}

		CControl *CControl::setOnParentFontChangeWidth(FOnParentFontChangeWidth value)
		{
			m_fOnParentFontChangeWidth = value;
			return this;
		}

		CControl *CControl::setOnParentFontChangeCharSet(FOnParentFontChangeCharSet value)
		{
			m_fOnParentFontChangeCharSet = value;
			return this;
		}

		CControl *CControl::setOnParentFontChangeQuality(FOnParentFontChangeQuality value)
		{
			m_fOnParentFontChangeQuality = value;
			return this;
		}

		CControl *CControl::setOnParentFontChangePitchAndFamily(FOnParentFontChangePitchAndFamily value)
		{
			m_fOnParentFontChangePitchAndFamily = value;
			return this;
		}

		CControl *CControl::setOnParentFontChangeOrientation(FOnParentFontChangeOrientation value)
		{
			m_fOnParentFontChangeOrientation = value;
			return this;
		}

		CControl *CControl::setOnParentFontChangeDistance(FOnParentFontChangeDistance value)
		{
			m_fOnParentFontChangeDistance = value;
			return this;
		}

		CControl *CControl::setOnParentFontChangeShadow(FOnParentFontChangeShadow value)
		{
			m_fOnParentFontChangeShadow = value;
			return this;
		}

		CControl *CControl::setOnParentFontChangeShadowShift(FOnParentFontChangeShadowShift value)
		{
			m_fOnParentFontChangeShadowShift = value;
			return this;
		}

		CControl *CControl::setOnParentFontChangeShadowBlur(FOnParentFontChangeShadowBlur value)
		{
			m_fOnParentFontChangeShadowBlur = value;
			return this;
		}

		CControl *CControl::setOnParentFontChangeShadowColor(FOnParentFontChangeShadowColor value)
		{
			m_fOnParentFontChangeShadowColor = value;
			return this;
		}

		CControl *CControl::setOnParentFontChangeColor(FOnParentFontChangeColor value)
		{
			m_fOnParentFontChangeColor = value;
			return this;
		}

		CControl *CControl::setOnParentFontChangeInterpolate(FOnParentFontChangeInterpolate value)
		{
			m_fOnParentFontChangeInterpolate = value;
			return this;
		}

		CControl *CControl::setOnParentFontBeginChange(FOnParentFontBeginChange value)
		{
			m_fOnParentFontBeginChange = value;
			return this;
		}

		CControl *CControl::setOnParentFontEndChange(FOnParentFontEndChange value)
		{
			m_fOnParentFontEndChange = value;
			return this;
		}

		CControl *CControl::setOnParentFontChangeSize(FOnParentFontChangeSize value)
		{
			m_fOnParentFontChangeSize = value;
			return this;
		}

		CControl *CControl::setOnParentFontChangeStyle(FOnParentFontChangeStyle value)
		{
			m_fOnParentFontChangeStyle = value;
			return this;
		}

		CControl *CControl::setOnChangeUseParentFont(FOnChangeUseParentFont value)
		{
			m_fOnChangeUseParentFont = value;
			return this;
		}

		CControl *CControl::setOnFontChangeName(FOnFontChangeName value)
		{
			m_fOnFontChangeName = value;
			return this;
		}

		CControl *CControl::setOnFontChangeHeight(FOnFontChangeHeight value)
		{
			m_fOnFontChangeHeight = value;
			return this;
		}

		CControl *CControl::setOnFontChangeWeight(FOnFontChangeWeight value)
		{
			m_fOnFontChangeWeight = value;
			return this;
		}

		CControl *CControl::setOnFontChangeItalic(FOnFontChangeItalic value)
		{
			m_fOnFontChangeItalic = value;
			return this;
		}

		CControl *CControl::setOnFontChangeUnderline(FOnFontChangeUnderline value)
		{
			m_fOnFontChangeUnderline = value;
			return this;
		}

		CControl *CControl::setOnFontChangeStrikeOut(FOnFontChangeStrikeOut value)
		{
			m_fOnFontChangeStrikeOut = value;
			return this;
		}

		CControl *CControl::setOnFontChangeWidth(FOnFontChangeWidth value)
		{
			m_fOnFontChangeWidth = value;
			return this;
		}

		CControl *CControl::setOnFontChangeCharSet(FOnFontChangeCharSet value)
		{
			m_fOnFontChangeCharSet = value;
			return this;
		}

		CControl *CControl::setOnFontChangeQuality(FOnFontChangeQuality value)
		{
			m_fOnFontChangeQuality = value;
			return this;
		}

		CControl *CControl::setOnFontChangePitchAndFamily(FOnFontChangePitchAndFamily value)
		{
			m_fOnFontChangePitchAndFamily = value;
			return this;
		}

		CControl *CControl::setOnFontChangeOrientation(FOnFontChangeOrientation value)
		{
			m_fOnFontChangeOrientation = value;
			return this;
		}

		CControl *CControl::setOnFontChangeDistance(FOnFontChangeDistance value)
		{
			m_fOnFontChangeDistance = value;
			return this;
		}

		CControl *CControl::setOnFontChangeShadow(FOnFontChangeShadow value)
		{
			m_fOnFontChangeShadow = value;
			return this;
		}

		CControl *CControl::setOnFontChangeShadowShift(FOnFontChangeShadowShift value)
		{
			m_fOnFontChangeShadowShift = value;
			return this;
		}

		CControl *CControl::setOnFontChangeShadowBlur(FOnFontChangeShadowBlur value)
		{
			m_fOnFontChangeShadowBlur = value;
			return this;
		}

		CControl *CControl::setOnFontChangeShadowColor(FOnFontChangeShadowColor value)
		{
			m_fOnFontChangeShadowColor = value;
			return this;
		}

		CControl *CControl::setOnFontChangeColor(FOnFontChangeColor value)
		{
			m_fOnFontChangeColor = value;
			return this;
		}

		CControl *CControl::setOnFontChangeInterpolate(FOnFontChangeInterpolate value)
		{
			m_fOnFontChangeInterpolate = value;
			return this;
		}

		CControl *CControl::setOnFontBeginChange(FOnFontBeginChange value)
		{
			m_fOnFontBeginChange = value;
			return this;
		}

		CControl *CControl::setOnFontEndChange(FOnFontEndChange value)
		{
			m_fOnFontEndChange = value;
			return this;
		}

		CControl *CControl::setOnFontChangeSize(FOnFontChangeSize value)
		{
			m_fOnFontChangeSize = value;
			return this;
		}

		CControl *CControl::setOnFontChangeStyle(FOnFontChangeStyle value)
		{
			m_fOnFontChangeStyle = value;
			return this;
		}

		CControl *CControl::setOnChildControlResize(FOnChildControlResize value)
		{
			m_fOnChildControlResize = value;
			return this;
		}

		CControl *CControl::setOnChildControlMove(FOnChildControlMove value)
		{
			m_fOnChildControlMove = value;
			return this;
		}

		CControl *CControl::setOnParentResize(FOnParentResize value)
		{
			m_fOnParentResize = value;
			return this;
		}

		CControl *CControl::setOnParentMove(FOnParentMove value)
		{
			m_fOnParentMove = value;
			return this;
		}

		CControl *CControl::setOnChangeStyle(FOnChangeStyle value)
		{
			m_fOnChangeStyle = value;
			return this;
		}

		CControl *CControl::setOnShow(FOnShow value)
		{
			m_fOnShow = value;
			return this;
		}

		CControl *CControl::setOnBeforeHide(FOnBeforeHide value)
		{
			m_fOnBeforeHide = value;
			return this;
		}

		CControl *CControl::setOnHide(FOnHide value)
		{
			m_fOnHide = value;
			return this;
		}

		CControl *CControl::setOnEnable(FOnEnable value)
		{
			m_fOnEnable = value;
			return this;
		}

		CControl *CControl::setOnDisable(FOnDisable value)
		{
			m_fOnDisable = value;
			return this;
		}

		CControl *CControl::setOnAttachControl(FOnAttachControl value)
		{
			m_fOnAttachControl = value;
			return this;
		}

		CControl *CControl::setOnBeforeDetachControl(FOnBeforeDetachControl value)
		{
			m_fOnBeforeDetachControl = value;
			return this;
		}

		CControl *CControl::setOnDetachControl(FOnDetachControl value)
		{
			m_fOnDetachControl = value;
			return this;
		}

		CControl *CControl::setOnPaint(FOnPaint value)
		{
			m_fOnPaint = value;
			return this;
		}

		CControl *CControl::setOnBeforeResize(FOnBeforeResize value)
		{
			m_fOnBeforeResize = value;
			return this;
		}

		CControl *CControl::setOnResize(FOnResize value)
		{
			m_fOnResize = value;
			return this;
		}

		CControl *CControl::setOnBeforeMove(FOnBeforeMove value)
		{
			m_fOnBeforeMove = value;
			return this;
		}

		CControl *CControl::setOnMove(FOnMove value)
		{
			m_fOnMove = value;
			return this;
		}

		CControl *CControl::setOnBeforeDetachFromControl(FOnBeforeDetachFromControl value)
		{
			m_fOnBeforeDetachFromControl = value;
			return this;
		}

		CControl *CControl::setOnDetachFromControl(FOnDetachFromControl value)
		{
			m_fOnDetachFromControl = value;
			return this;
		}

		CControl *CControl::setOnAttachToControl(FOnAttachToControl value)
		{
			m_fOnAttachToControl = value;
			return this;
		}
#pragma endregion
	}
}