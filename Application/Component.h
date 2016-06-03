// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#pragma once

#include "..\Strings\Strings.h"
#include "Types.h"
#include "Window.h"

namespace licui
{
	namespace application
	{
		class CComponent
		{
			friend CForm;
			friend CControl;
		public:
			typedef void(*FOnBeforeDetachComponentFromForm)(CComponent *component, void *param);
			typedef void(*FOnBeforeDetachControlFromForm)(CControl *control, void *param);
			typedef void(*FOnBeforeDetachFromForm)(void *param);
			typedef void(*FOnDetachFromForm)(void *param);
			typedef void(*FOnAttachToForm)(void *param);
			typedef void(*FOnUpdateComponent)(CComponent *component, void *param);
			typedef void(*FOnUpdateControl)(CControl *control, void *param);
			typedef void(*FOnUpdate)(void *param);
			typedef void(*FOnHotkey)(CComponent *sender, const IWindow::KEY key, const bool ctrl, const bool alt, const bool shift, const bool is_down, void *param);
		private:
			void *m_pCallbackParam;
			FOnBeforeDetachComponentFromForm m_fOnBeforeDetachComponentFromForm;
			FOnBeforeDetachControlFromForm m_fOnBeforeDetachControlFromForm;
			FOnBeforeDetachFromForm m_fOnBeforeDetachFromForm;
			FOnDetachFromForm m_fOnDetachFromForm;
			FOnAttachToForm m_fOnAttachToForm;
			FOnUpdateComponent m_fOnUpdateComponent;
			FOnUpdateControl m_fOnUpdateControl;
			FOnUpdate m_fOnUpdate;
			FOnHotkey m_fOnHotkey;

			void RemoveFromForm();
			void AddToForm(CForm *form);
		protected:
			String m_sClassName;
			String m_sName;
			CForm *m_pForm;

			virtual void NotifyOnBeforeDetachComponentFromForm(CComponent *component);
			virtual void NotifyOnBeforeDetachControlFromForm(CControl *control);
			virtual void NotifyOnBeforeDetachFromForm();
			virtual void NotifyOnDetachFromForm();
			virtual void NotifyOnAttachToForm();
			virtual void NotifyOnUpdateComponent(CComponent *component);
			virtual void NotifyOnUpdateControl(CControl *control);
			virtual void NotifyOnUpdate(); // Call after update to send notification to all components and controls
			virtual void NotifyOnHotkey(const IWindow::KEY key, const bool ctrl, const bool alt, const bool shift, const bool is_down);
		public:
			CComponent();
			CComponent(CForm *form);
			virtual ~CComponent();

			virtual void *getCallbackParam() const;
			virtual FOnBeforeDetachComponentFromForm getOnBeforeDetachComponentFromForm() const;
			virtual FOnBeforeDetachControlFromForm getOnBeforeDetachControlFromForm() const;
			virtual FOnBeforeDetachFromForm getOnBeforeDetachFromForm() const;
			virtual FOnDetachFromForm getOnDetachFromForm() const;
			virtual FOnAttachToForm getOnAttachToForm() const;
			virtual FOnUpdateComponent getOnUpdateComponent() const;
			virtual FOnUpdateControl getOnUpdateControl() const;
			virtual FOnUpdate getOnUpdate() const;
			virtual FOnHotkey getOnHotkey() const;

			virtual CComponent *setCallbackParam(void *value);
			virtual CComponent *setOnBeforeDetachComponentFromForm(FOnBeforeDetachComponentFromForm value);
			virtual CComponent *setOnBeforeDetachControlFromForm(FOnBeforeDetachControlFromForm value);
			virtual CComponent *setOnBeforeDetachFromForm(FOnBeforeDetachFromForm value);
			virtual CComponent *setOnDetachFromForm(FOnDetachFromForm value);
			virtual CComponent *setOnAttachToForm(FOnAttachToForm value);
			virtual CComponent *setOnUpdateComponent(FOnUpdateComponent value);
			virtual CComponent *setOnUpdateControl(FOnUpdateControl value);
			virtual CComponent *setOnUpdate(FOnUpdate value);
			virtual CComponent *setOnHotkey(FOnHotkey value);

			virtual String getClassName() const;
			virtual String getName() const;
			virtual CForm *getForm();

			virtual bool setName(const String &value);
			virtual bool setForm(CForm *value);
		};
	}
}