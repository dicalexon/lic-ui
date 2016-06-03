// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#include "Component.h"
#include "Form.h"
#include "Control.h"

namespace licui
{
	namespace application
	{
		CComponent::CComponent() :
			m_sClassName{ L"CComponent" },
			m_pForm{ nullptr },
			m_pCallbackParam{ nullptr },
			m_fOnBeforeDetachComponentFromForm{ nullptr },
			m_fOnBeforeDetachControlFromForm{ nullptr },
			m_fOnBeforeDetachFromForm{ nullptr },
			m_fOnDetachFromForm{ nullptr },
			m_fOnAttachToForm{ nullptr },
			m_fOnUpdateComponent{ nullptr },
			m_fOnUpdateControl{ nullptr },
			m_fOnUpdate{ nullptr },
			m_fOnHotkey{ nullptr }
		{

		}

		CComponent::CComponent(CForm *form) : CComponent()
		{
			setForm(form);
		}

		CComponent::~CComponent()
		{
			setForm(nullptr);
		}

		void CComponent::RemoveFromForm()
		{
			NotifyOnBeforeDetachFromForm();
			for (auto pos = m_pForm->m_aComponents.begin(); pos != m_pForm->m_aComponents.end(); pos++)
				if ((*pos) != this)
					(*pos)->NotifyOnBeforeDetachComponentFromForm(this);
			for (auto pos = m_pForm->m_aControlsRoot.begin(); pos != m_pForm->m_aControlsRoot.end(); pos++)
				((CComponent*)(*pos))->NotifyOnBeforeDetachComponentFromForm(this);
			for (auto pos = m_pForm->m_aComponents.begin(); pos != m_pForm->m_aComponents.end(); pos++)
				if ((*pos) == this)
				{
					m_pForm->m_aComponents.erase(pos);
					break;
				}
			m_pForm->UnregisterHotkeys(this);
			m_pForm = nullptr;
			NotifyOnDetachFromForm();
		}

		void CComponent::AddToForm(CForm *form)
		{
			String name{ m_sName };
			if (name.empty())
				name = m_sClassName + L"1";
			if (!form->ValidateComponentName(name, nullptr))
			{
				int index = 1;
				do
				{
					name = m_sClassName + ToString(index++);
				} while (!form->ValidateComponentName(name, nullptr));
			}
			m_sName = name;
			// Add links to component
			form->m_aComponents.push_back(this);
			form->m_bIsComponentsSorted = false;
			// Add to form
			m_pForm = form;
			NotifyOnAttachToForm();
		}

		String CComponent::getClassName() const
		{
			return m_sClassName;
		}

		String CComponent::getName() const
		{
			return m_sName;
		}

		CForm *CComponent::getForm()
		{
			return m_pForm;
		}

		void *CComponent::getCallbackParam() const
		{
			return m_pCallbackParam;
		}

		CComponent::FOnBeforeDetachComponentFromForm CComponent::getOnBeforeDetachComponentFromForm() const
		{
			return m_fOnBeforeDetachComponentFromForm;
		}

		CComponent::FOnBeforeDetachControlFromForm CComponent::getOnBeforeDetachControlFromForm() const
		{
			return m_fOnBeforeDetachControlFromForm;
		}

		CComponent::FOnBeforeDetachFromForm CComponent::getOnBeforeDetachFromForm() const
		{
			return m_fOnBeforeDetachFromForm;
		}

		CComponent::FOnDetachFromForm CComponent::getOnDetachFromForm() const
		{
			return m_fOnDetachFromForm;
		}

		CComponent::FOnAttachToForm CComponent::getOnAttachToForm() const
		{
			return m_fOnAttachToForm;
		}

		CComponent::FOnUpdateComponent CComponent::getOnUpdateComponent() const
		{
			return m_fOnUpdateComponent;
		}

		CComponent::FOnUpdateControl CComponent::getOnUpdateControl() const
		{
			return m_fOnUpdateControl;
		}

		CComponent::FOnUpdate CComponent::getOnUpdate() const
		{
			return m_fOnUpdate;
		}

		CComponent::FOnHotkey CComponent::getOnHotkey() const
		{
			return m_fOnHotkey;
		}

		bool CComponent::setName(const String &value)
		{
			if (value.empty())
				return false;
			if (value == m_sName)
				return true;
			if (m_pForm)
			{
				if (m_pForm->ValidateComponentName(value, this))
				{
					m_sName = value;
					m_pForm->m_bIsComponentsSorted = false;
					return true;
				}
				return false;
			}
			m_sName = value;
			return true;
		}

		bool CComponent::setForm(CForm *value)
		{
			if (value != m_pForm)
			{
				if (m_pForm)
					RemoveFromForm();
				if (value)
					AddToForm(value);
			}
			return true;
		}

		CComponent *CComponent::setCallbackParam(void *value)
		{
			m_pCallbackParam = value;
			return this;
		}

		CComponent *CComponent::setOnBeforeDetachComponentFromForm(FOnBeforeDetachComponentFromForm value)
		{
			m_fOnBeforeDetachComponentFromForm = value;
			return this;
		}

		CComponent *CComponent::setOnBeforeDetachControlFromForm(FOnBeforeDetachControlFromForm value)
		{
			m_fOnBeforeDetachControlFromForm = value;
			return this;
		}

		CComponent *CComponent::setOnBeforeDetachFromForm(FOnBeforeDetachFromForm value)
		{
			m_fOnBeforeDetachFromForm = value;
			return this;
		}

		CComponent *CComponent::setOnDetachFromForm(FOnDetachFromForm value)
		{
			m_fOnDetachFromForm = value;
			return this;
		}

		CComponent *CComponent::setOnAttachToForm(FOnAttachToForm value)
		{
			m_fOnAttachToForm = value;
			return this;
		}

		CComponent *CComponent::setOnUpdateComponent(FOnUpdateComponent value)
		{
			m_fOnUpdateComponent = value;
			return this;
		}

		CComponent *CComponent::setOnUpdateControl(FOnUpdateControl value)
		{
			m_fOnUpdateControl = value;
			return this;
		}

		CComponent *CComponent::setOnUpdate(FOnUpdate value)
		{
			m_fOnUpdate = value;
			return this;
		}

		CComponent *CComponent::setOnHotkey(FOnHotkey value)
		{
			m_fOnHotkey = value;
			return this;
		}

		void CComponent::NotifyOnBeforeDetachComponentFromForm(CComponent *component)
		{
			if (m_fOnBeforeDetachComponentFromForm)
				m_fOnBeforeDetachComponentFromForm(component, m_pCallbackParam);
		}

		void CComponent::NotifyOnBeforeDetachControlFromForm(CControl *control)
		{
			if (m_fOnBeforeDetachControlFromForm)
				m_fOnBeforeDetachControlFromForm(control, m_pCallbackParam);
		}

		void CComponent::NotifyOnBeforeDetachFromForm()
		{
			if (m_fOnBeforeDetachFromForm)
				m_fOnBeforeDetachFromForm(m_pCallbackParam);
		}

		void CComponent::NotifyOnDetachFromForm()
		{
			if (m_fOnDetachFromForm)
				m_fOnDetachFromForm(m_pCallbackParam);
		}

		void CComponent::NotifyOnAttachToForm()
		{
			if (m_fOnAttachToForm)
				m_fOnAttachToForm(m_pCallbackParam);
		}

		void CComponent::NotifyOnUpdateComponent(CComponent *component)
		{
			if (m_fOnUpdateComponent)
				m_fOnUpdateComponent(component, m_pCallbackParam);
		}

		void CComponent::NotifyOnUpdateControl(CControl *control)
		{
			if (m_fOnUpdateControl)
				m_fOnUpdateControl(control, m_pCallbackParam);
		}

		void CComponent::NotifyOnUpdate()
		{
			if (m_pForm)
			{
				m_pForm->LockRepaint();
				m_pForm->NotifyOnUpdateComponent(this);
				if (m_fOnUpdate)
					m_fOnUpdate(m_pCallbackParam);
				m_pForm->UnlockRepaint();
			}
		}

		void CComponent::NotifyOnHotkey(const IWindow::KEY key, const bool ctrl, const bool alt, const bool shift, const bool is_down)
		{
			if (m_fOnHotkey)
				m_fOnHotkey(this, key, ctrl, alt, shift, is_down, m_pCallbackParam);
		}
	}
}