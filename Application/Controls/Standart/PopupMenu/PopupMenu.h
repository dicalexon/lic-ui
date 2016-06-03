// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#pragma once

#include "..\..\..\..\Strings\Strings.h"
#include "..\..\..\Types.h"
#include "..\..\..\Control.h"
#include "..\..\..\Window.h"
#include "..\..\..\Form.h"
#include "..\..\..\Components\ImageList\ImageList.h"
#include ".\..\..\Base\BaseBlock.h"

namespace licui
{
	namespace application
	{
		class CPopupMenuItem;
		class CPopupMenu;

		// Delegates all size change events to parent menu
		class CPopupMenuItem : public CControl
		{
			friend CPopupMenu;
		public:
			enum ITEM_TYPE
			{
				mitNormal,
				mitCheckBox,
				mitRadioButton
			};

			enum ITEM_STATE
			{
				misNormal,
				misChecked,
				misGrayed
			};

			typedef void(*FOnClick)(CPopupMenuItem *sender, void *param);
		private:
			struct STATE
			{
				int ImageIndex;
			};

			struct MENU_ITEM_SIZE
			{
				size_t Height;
				size_t WidthCaption;
				size_t WidthShortcut;
			};

			ITEM_TYPE m_eType;
			ITEM_STATE m_eState;
			CForm::SHORTCUT m_sShortcut;
			String m_sShortcutName;
			String m_sCaption;
			size_t m_iGroup;
			math::RECTANGLE<size_t> m_sMarginImage;
			math::RECTANGLE<size_t> m_sMarginCaptionImage;
			math::RECTANGLE<size_t> m_sMarginCaption;
			math::RECTANGLE<size_t> m_sMarginShortcut;
			math::RECTANGLE<size_t> m_sMarginArrow;
			bool m_bIsSeparator;
			size_t m_iSeparatorHeight;
			APP_COLOR m_sSeparatorColor;
			STATE m_sState[mitRadioButton + 1][misGrayed + 1][2][2];
			FOnClick m_fOnClick;
			APP_COLOR m_sDisabledTextColor;
			APP_COLOR m_sDisabledShadowColor;
			APP_COLOR m_sActiveBackgroundColor;
			APP_COLOR m_sActiveTextColor;
			APP_COLOR m_sActiveShadowColor;

			void FillStates();
			bool UpdateState();
			void BeforeChange(const bool hide_menu);
			void AfterChange();
			void ClearActiveMenuItemIndex();
			MENU_ITEM_SIZE CalculateSize();
			APP_RECT CalculateRectImage();
			APP_RECT CalculateRectCaptionImage();
			APP_RECT CalculateRectCaption();
			APP_RECT CalculateRectShortcut();
			APP_RECT CalculateRectArrow();
			APP_POINT CalculateCaptionImageSize();
			void SelectImage(APP_IMAGE **img, APP_RECT &rect);

			void RenderImage(APP_RECT clip, const APP_RECT &rect_image);
			void RenderArrow(APP_RECT clip, const APP_RECT &rect_arrow);
			void RenderSeparator(APP_RECT clip);
			void RenderControl(APP_RECT clip);
		protected:
			void NotifyOnUpdateComponent(CComponent *component) override;

			void NotifyOnChangeUseParentFont() override;
			void NotifyOnParentFontChangeSize() override;

			void NotifyOnFontChangeSize() override;

			void NotifyOnChangeParentStyle() override;
			void NotifyOnChangeStyle() override;

			void NotifyOnMouseHover() override;
			bool NotifyOnLeftMouseButtonDown(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift) override;
			bool NotifyOnLeftMouseButtonUp(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift) override;
			void NotifyOnPaint(APP_RECT clip) override;

			virtual String GetKeyName(const IWindow::KEY key);
		public:
			APP_RECT getVisibleRect() override;

			virtual ITEM_TYPE getType() const;
			virtual ITEM_STATE getState() const;
			virtual CForm::SHORTCUT getShortcut() const;
			virtual String getShortcutName() const;
			virtual String getCaption() const;
			virtual size_t getGroup() const;
			virtual CPopupMenu *getParentMenu();
			virtual CPopupMenu *getRootMenu();
			virtual CPopupMenu *getMenu();
			virtual math::RECTANGLE<size_t> getMarginImage() const;
			virtual size_t getMarginImageLeft() const;
			virtual size_t getMarginImageTop() const;
			virtual size_t getMarginImageRight() const;
			virtual size_t getMarginImageBottom() const;
			virtual math::RECTANGLE<size_t> getMarginCaptionImage() const;
			virtual size_t getMarginCaptionImageLeft() const;
			virtual size_t getMarginCaptionImageTop() const;
			virtual size_t getMarginCaptionImageRight() const;
			virtual size_t getMarginCaptionImageBottom() const;
			virtual math::RECTANGLE<size_t> getMarginCaption() const;
			virtual size_t getMarginCaptionLeft() const;
			virtual size_t getMarginCaptionTop() const;
			virtual size_t getMarginCaptionRight() const;
			virtual size_t getMarginCaptionBottom() const;
			virtual math::RECTANGLE<size_t> getMarginShortcut() const;
			virtual size_t getMarginShortcutLeft() const;
			virtual size_t getMarginShortcutTop() const;
			virtual size_t getMarginShortcutRight() const;
			virtual size_t getMarginShortcutBottom() const;
			virtual math::RECTANGLE<size_t> getMarginArrow() const;
			virtual size_t getMarginArrowLeft() const;
			virtual size_t getMarginArrowTop() const;
			virtual size_t getMarginArrowRight() const;
			virtual size_t getMarginArrowBottom() const;
			virtual bool getIsSeparator() const;
			virtual int getImageIndex(const ITEM_TYPE type, const ITEM_STATE state, const bool active, const bool enabled);
			virtual bool getIsActive();
			virtual FOnClick getOnClick();
			virtual APP_COLOR getDisabledTextColor() const;
			virtual APP_COLOR getDisabledShadowColor() const;
			virtual APP_COLOR getActiveBackgroundColor() const;
			virtual APP_COLOR getActiveTextColor() const;
			virtual APP_COLOR getActiveShadowColor() const;

			virtual CPopupMenuItem *setType(const ITEM_TYPE value);
			virtual CPopupMenuItem *setState(const ITEM_STATE value);
			virtual CPopupMenuItem *setShortcut(const IWindow::KEY key, const bool control, const bool alt, const bool shift);
			virtual CPopupMenuItem *setCaption(const String &value);
			virtual CPopupMenuItem *setGroup(const size_t value);
			virtual CPopupMenuItem *setMarginImage(const math::RECTANGLE<size_t> &value);
			virtual CPopupMenuItem *setMarginImageLeft(const size_t value);
			virtual CPopupMenuItem *setMarginImageTop(const size_t value);
			virtual CPopupMenuItem *setMarginImageRight(const size_t value);
			virtual CPopupMenuItem *setMarginImageBottom(const size_t value);
			virtual CPopupMenuItem *setMarginCaptionImage(const math::RECTANGLE<size_t> &value);
			virtual CPopupMenuItem *setMarginCaptionImageLeft(const size_t value);
			virtual CPopupMenuItem *setMarginCaptionImageTop(const size_t value);
			virtual CPopupMenuItem *setMarginCaptionImageRight(const size_t value);
			virtual CPopupMenuItem *setMarginCaptionImageBottom(const size_t value);
			virtual CPopupMenuItem *setMarginCaption(const math::RECTANGLE<size_t> &value);
			virtual CPopupMenuItem *setMarginCaptionLeft(const size_t value);
			virtual CPopupMenuItem *setMarginCaptionTop(const size_t value);
			virtual CPopupMenuItem *setMarginCaptionRight(const size_t value);
			virtual CPopupMenuItem *setMarginCaptionBottom(const size_t value);
			virtual CPopupMenuItem *setMarginShortcut(const math::RECTANGLE<size_t> &value);
			virtual CPopupMenuItem *setMarginShortcutLeft(const size_t value);
			virtual CPopupMenuItem *setMarginShortcutTop(const size_t value);
			virtual CPopupMenuItem *setMarginShortcutRight(const size_t value);
			virtual CPopupMenuItem *setMarginShortcutBottom(const size_t value);
			virtual CPopupMenuItem *setMarginArrow(const math::RECTANGLE<size_t> &value);
			virtual CPopupMenuItem *setMarginArrowLeft(const size_t value);
			virtual CPopupMenuItem *setMarginArrowTop(const size_t value);
			virtual CPopupMenuItem *setMarginArrowRight(const size_t value);
			virtual CPopupMenuItem *setMarginArrowBottom(const size_t value);
			virtual CPopupMenuItem *setIsSeparator(const bool value);
			virtual CPopupMenuItem *setImageIndex(int value);
			virtual CPopupMenuItem *setImageIndex(const ITEM_TYPE type, const ITEM_STATE state, const bool active, const bool enabled, int value);
			virtual CPopupMenuItem *setOnClick(FOnClick value);
			virtual CPopupMenuItem *setMenu(CPopupMenu *value);
			virtual CPopupMenuItem *setDisabledTextColor(const APP_COLOR &value);
			virtual CPopupMenuItem *setDisabledShadowColor(const APP_COLOR &value);
			virtual CPopupMenuItem *setActiveBackgroundColor(const APP_COLOR &value);
			virtual CPopupMenuItem *setActiveTextColor(const APP_COLOR &value);
			virtual CPopupMenuItem *setActiveShadowColor(const APP_COLOR &value);

			CPopupMenuItem();
			CPopupMenuItem(CPopupMenu *menu);
		public:
			using CControl::getOnMouseMove;
			using CControl::getOnLeftMouseButtonDown;
			using CControl::getOnLeftMouseButtonUp;
			using CControl::getOnLeftMouseButtonDoubleClick;
			using CControl::getOnRightMouseButtonDown;
			using CControl::getOnRightMouseButtonUp;
			using CControl::getOnRightMouseButtonDoubleClick;
			using CControl::getOnMiddleMouseButtonDown;
			using CControl::getOnMiddleMouseButtonUp;
			using CControl::getOnMiddleMouseButtonDoubleClick;
			using CControl::getOnMouseVerticalWheel;
			using CControl::getOnMouseHorizontalWheel;
			using CControl::getOnChangeUseParentFont;
			using CControl::getOnParentFontChangeName;
			using CControl::getOnParentFontChangeHeight;
			using CControl::getOnParentFontChangeWeight;
			using CControl::getOnParentFontChangeItalic;
			using CControl::getOnParentFontChangeUnderline;
			using CControl::getOnParentFontChangeStrikeOut;
			using CControl::getOnParentFontChangeWidth;
			using CControl::getOnParentFontChangeCharSet;
			using CControl::getOnParentFontChangeQuality;
			using CControl::getOnParentFontChangePitchAndFamily;
			using CControl::getOnParentFontChangeOrientation;
			using CControl::getOnParentFontChangeDistance;
			using CControl::getOnParentFontChangeShadow;
			using CControl::getOnParentFontChangeShadowShift;
			using CControl::getOnParentFontChangeShadowBlur;
			using CControl::getOnParentFontChangeShadowColor;
			using CControl::getOnParentFontChangeColor;
			using CControl::getOnParentFontChangeInterpolate;
			using CControl::getOnParentFontBeginChange;
			using CControl::getOnParentFontEndChange;
			using CControl::getOnParentFontChangeSize;
			using CControl::getOnParentFontChangeStyle;
			using CControl::getOnFontChangeName;
			using CControl::getOnFontChangeHeight;
			using CControl::getOnFontChangeWeight;
			using CControl::getOnFontChangeItalic;
			using CControl::getOnFontChangeUnderline;
			using CControl::getOnFontChangeStrikeOut;
			using CControl::getOnFontChangeWidth;
			using CControl::getOnFontChangeCharSet;
			using CControl::getOnFontChangeQuality;
			using CControl::getOnFontChangePitchAndFamily;
			using CControl::getOnFontChangeOrientation;
			using CControl::getOnFontChangeDistance;
			using CControl::getOnFontChangeShadow;
			using CControl::getOnFontChangeShadowShift;
			using CControl::getOnFontChangeShadowBlur;
			using CControl::getOnFontChangeShadowColor;
			using CControl::getOnFontChangeColor;
			using CControl::getOnFontChangeInterpolate;
			using CControl::getOnFontBeginChange;
			using CControl::getOnFontEndChange;
			using CControl::getOnFontChangeSize;
			using CControl::getOnFontChangeStyle;
			using CControl::getOnMouseHover;
			using CControl::getOnMouseLeave;
			using CControl::getOnChangeParentStyle;
			using CControl::getOnChangeStyle;
			using CControl::getOnEnable;
			using CControl::getOnDisable;
			using CControl::getOnPaint;
			using CControl::getOnBeforeResize;
			using CControl::getOnResize;
			using CControl::getOnBeforeMove;
			using CControl::getOnMove;
			using CControl::setOnMouseMove;
			using CControl::setOnLeftMouseButtonDown;
			using CControl::setOnLeftMouseButtonUp;
			using CControl::setOnLeftMouseButtonDoubleClick;
			using CControl::setOnRightMouseButtonDown;
			using CControl::setOnRightMouseButtonUp;
			using CControl::setOnRightMouseButtonDoubleClick;
			using CControl::setOnMiddleMouseButtonDown;
			using CControl::setOnMiddleMouseButtonUp;
			using CControl::setOnMiddleMouseButtonDoubleClick;
			using CControl::setOnMouseVerticalWheel;
			using CControl::setOnMouseHorizontalWheel;
			using CControl::setOnChangeUseParentFont;
			using CControl::setOnParentFontChangeName;
			using CControl::setOnParentFontChangeHeight;
			using CControl::setOnParentFontChangeWeight;
			using CControl::setOnParentFontChangeItalic;
			using CControl::setOnParentFontChangeUnderline;
			using CControl::setOnParentFontChangeStrikeOut;
			using CControl::setOnParentFontChangeWidth;
			using CControl::setOnParentFontChangeCharSet;
			using CControl::setOnParentFontChangeQuality;
			using CControl::setOnParentFontChangePitchAndFamily;
			using CControl::setOnParentFontChangeOrientation;
			using CControl::setOnParentFontChangeDistance;
			using CControl::setOnParentFontChangeShadow;
			using CControl::setOnParentFontChangeShadowShift;
			using CControl::setOnParentFontChangeShadowBlur;
			using CControl::setOnParentFontChangeShadowColor;
			using CControl::setOnParentFontChangeColor;
			using CControl::setOnParentFontChangeInterpolate;
			using CControl::setOnParentFontBeginChange;
			using CControl::setOnParentFontEndChange;
			using CControl::setOnParentFontChangeSize;
			using CControl::setOnParentFontChangeStyle;
			using CControl::setOnFontChangeName;
			using CControl::setOnFontChangeHeight;
			using CControl::setOnFontChangeWeight;
			using CControl::setOnFontChangeItalic;
			using CControl::setOnFontChangeUnderline;
			using CControl::setOnFontChangeStrikeOut;
			using CControl::setOnFontChangeWidth;
			using CControl::setOnFontChangeCharSet;
			using CControl::setOnFontChangeQuality;
			using CControl::setOnFontChangePitchAndFamily;
			using CControl::setOnFontChangeOrientation;
			using CControl::setOnFontChangeDistance;
			using CControl::setOnFontChangeShadow;
			using CControl::setOnFontChangeShadowShift;
			using CControl::setOnFontChangeShadowBlur;
			using CControl::setOnFontChangeShadowColor;
			using CControl::setOnFontChangeColor;
			using CControl::setOnFontChangeInterpolate;
			using CControl::setOnFontBeginChange;
			using CControl::setOnFontEndChange;
			using CControl::setOnFontChangeSize;
			using CControl::setOnFontChangeStyle;
			using CControl::setOnMouseHover;
			using CControl::setOnMouseLeave;
			using CControl::setOnChangeParentStyle;
			using CControl::setOnChangeStyle;
			using CControl::setOnEnable;
			using CControl::setOnDisable;
			using CControl::setOnPaint;
			using CControl::setOnBeforeResize;
			using CControl::setOnResize;
			using CControl::setOnBeforeMove;
			using CControl::setOnMove;
			using CControl::getControlStyle;
			using CControl::getStyle;
			using CControl::getUseStyle;
			using CControl::getControlFont;
			using CControl::getParentFont;
			using CControl::getFont;
			using CControl::getUseParentFont;
			using CControl::setEnabled;
			using CControl::setVisible;
			using CControl::setStyle;
			using CControl::setUseStyle;
			using CControl::setControlFont;
			using CControl::setFont;
			using CControl::setUseParentFont;
			using CControl::setCursor;
		};

		class CPopupMenu :public CBaseBlock
		{
			friend CPopupMenuItem;
		public:
			typedef void(*FOnClick)(void *param, CPopupMenuItem *sender);
		private:
			struct SIZE
			{
				APP_POINT RequiredSize;
				APP_POINT Size;
				size_t WidthImages;
				size_t WidthCaptions;
				size_t WidthShortcuts;
				size_t WidthArrows;
				bool HaveScroll;
				size_t ScrollMax;
			};

			size_t m_iScroll;
			size_t m_iScrollHeight;
			size_t m_iScrollDelta;
			CImageList *m_pImageList;
			size_t m_iRightArrowWidth;
			bool m_bUpdating;
			bool m_bMouseOverUpArrow;
			bool m_bMouseOverDownArrow;
			bool m_bMouseDownOnUpArrow;
			bool m_bMouseDownOnDownArrow;
			unsigned int m_hScrollTimer;
			APP_POINT m_sSubmenuShift;
			bool m_bCaretVisibleOnShow;
			FOnClick m_fOnClick;
			SIZE m_sSize;
			int m_iActiveItemIndex;
			BLOCK m_sBlock;
			bool m_bShowImages;

			void FillBlock();
			bool HaveMenuItem(CPopupMenuItem *item);
			void CalculateSize();
			APP_RECT CalculateScrollUpRect();
			APP_RECT CalculateScrollDownRect();
			static void DoOnScrollTimer(void *param);
			bool TestMenuRect(const int x, const int y);
			bool ProcessMenuItemOnHover(CPopupMenuItem *item);
			void ClearActiveMenuItemIndex();
			void ActivateSubmenu();
			void UpdateControls();

			void ProcessKeyUp();
			void ProcessKeyDown();
			void ProcessKeyLeft();
			void ProcessKeyRight();
			void ProcessKeyEscape();
			void ProcessKeyHome();
			void ProcessKeyEnd();
			void ProcessKeyReturn();
			void ProcessKeySpace();
			bool ProcessShortcut(const IWindow::KEY key, const bool ctrl, const bool alt, const bool shift);

			void RenderArrowRight(APP_RECT clip, const APP_RECT &arrow_rect, const bool enabled, const bool active);
			void RenderUpArrow(APP_RECT clip);
			void RenderDownArrow(APP_RECT clip);
		protected:
			BLOCK *getBlock() override;

			void NotifyOnBeforeDetachComponentFromForm(CComponent *component) override; // Handle remove image list
			void NotifyOnBeforeDetachFromForm() override;

			bool NotifyOnKeyDown(const IWindow::KEY key) override;
			bool NotifyOnKeyUp(const IWindow::KEY key) override;
			bool NotifyOnChar(const wchar_t chr) override;
			bool NotifyOnDeadChar(const wchar_t chr) override;
			bool NotifyOnSysKeyDown(const IWindow::KEY key) override;
			bool NotifyOnSysKeyUp(const IWindow::KEY key) override;
			bool NotifyOnSysChar(const wchar_t chr) override;
			bool NotifyOnSysDeadChar(const wchar_t chr) override;
			bool NotifyOnMouseMove(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift) override;
			bool NotifyOnLeftMouseButtonDown(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift) override;
			bool NotifyOnLeftMouseButtonUp(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift) override;
			bool NotifyOnLeftMouseButtonDoubleClick(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift) override;
			bool NotifyOnRightMouseButtonDown(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift) override;
			bool NotifyOnRightMouseButtonUp(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift) override;
			bool NotifyOnRightMouseButtonDoubleClick(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift) override;
			bool NotifyOnMiddleMouseButtonDown(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift) override;
			bool NotifyOnMiddleMouseButtonUp(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift) override;
			bool NotifyOnMiddleMouseButtonDoubleClick(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift) override;
			bool NotifyOnMouseVerticalWheel(const int x, const int y, const int delta, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift) override;
			bool NotifyOnMouseHorizontalWheel(const int x, const int y, const int delta, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift) override;
			
			void NotifyOnMouseHover() override;
			void NotifyOnMouseLeave() override;
			void NotifyOnKillFocus() override;
			void NotifyOnKillCaptureKeyboard() override;
			void NotifyOnKillCaptureMouse() override;
			void NotifyOnSetCaptureMouse() override;
			void NotifyOnPaint(APP_RECT clip) override;
			void NotifyOnDetachControl(CControl *control) override;
			void NotifyOnHide() override;

			virtual void NotifyOnClick(CPopupMenuItem *sender);
		public:
			APP_RECT getClientRect() override;
			void UpdateRect() override;
			APP_RECT getVisibleRect() override;

			CBaseBlock *setBorderWidth(const size_t value) override;
			CBaseBlock *setBorderWidth(const size_t left, const size_t top, const size_t right, const size_t bottom) override;
			CBaseBlock *setLeftBorderWidth(const size_t value) override;
			CBaseBlock *setTopBorderWidth(const size_t value) override;
			CBaseBlock *setRightBorderWidth(const size_t value) override;
			CBaseBlock *setBottomBorderWidth(const size_t value) override;
			CBaseBlock *setPadding(const math::RECTANGLE<size_t> &value) override;
			CBaseBlock *setPadding(const size_t value) override;
			CBaseBlock *setPaddingLeft(const size_t value) override;
			CBaseBlock *setPaddingTop(const size_t value) override;
			CBaseBlock *setPaddingRight(const size_t value) override;
			CBaseBlock *setPaddingBottom(const size_t value) override;

			virtual CPopupMenuItem *getParentMenuItem();
			virtual size_t getMenuItemCount() const;
			virtual CPopupMenuItem *getMenuItem(const int index);
			virtual bool getHaveScroll() const;
			virtual size_t getScroll() const;
			virtual size_t getScrollMax() const;
			virtual size_t getScrollHeight() const;
			virtual size_t getScrollDelta() const;
			virtual CImageList *getImageList();
			virtual int getActiveMenuItemIndex() const;
			virtual CPopupMenuItem *getActiveMenuItem();
			virtual bool getShowImages() const;
			virtual size_t getRightArrowWidth() const;
			virtual APP_POINT getSubmenuShift() const;
			virtual int getSubmenuShiftX() const;
			virtual int getSubmenuShiftY() const;
			virtual CPopupMenu *getRootMenu();
			virtual FOnClick getOnClick() const;

			virtual CPopupMenu *setParentMenuItem(CPopupMenuItem *value);
			virtual CPopupMenu *setScroll(const size_t value);
			virtual CPopupMenu *setScrollHeight(const size_t value);
			virtual CPopupMenu *setScrollDelta(size_t value);
			virtual CPopupMenu *setImageList(CImageList *value);
			virtual CPopupMenu *setActiveMenuItemIndex(int value);
			virtual CPopupMenu *setShowImages(const bool value);
			virtual CPopupMenu *setRightArrowWidth(const size_t value);
			virtual CPopupMenu *setSubmenuShift(const APP_POINT &value);
			virtual CPopupMenu *setSubmenuShiftX(const int value);
			virtual CPopupMenu *setSubmenuShiftY(const int value);
			virtual CPopupMenu *setOnClick(FOnClick value);

			virtual void Show(const int x, const int y);
			virtual void Hide();
			virtual void Update();

			virtual void AddMenuItem(CPopupMenuItem *item);
			virtual void InsertMenuItem(CPopupMenuItem *item, const size_t before);
			virtual void DeleteMenuItem(CPopupMenuItem *item);
			virtual void DeleteMenuItem(const size_t index);
			virtual void ClearMenuItems();

			CPopupMenu();
			CPopupMenu(CForm *form);
		public:
			using CBaseBlock::getOnKeyDown;
			using CBaseBlock::getOnKeyUp;
			using CBaseBlock::getOnChar;
			using CBaseBlock::getOnDeadChar;
			using CBaseBlock::getOnSysKeyDown;
			using CBaseBlock::getOnSysKeyUp;
			using CBaseBlock::getOnSysChar;
			using CBaseBlock::getOnSysDeadChar;
			using CBaseBlock::getOnMouseMove;
			using CBaseBlock::getOnLeftMouseButtonDown;
			using CBaseBlock::getOnLeftMouseButtonUp;
			using CBaseBlock::getOnLeftMouseButtonDoubleClick;
			using CBaseBlock::getOnRightMouseButtonDown;
			using CBaseBlock::getOnRightMouseButtonUp;
			using CBaseBlock::getOnRightMouseButtonDoubleClick;
			using CBaseBlock::getOnMiddleMouseButtonDown;
			using CBaseBlock::getOnMiddleMouseButtonUp;
			using CBaseBlock::getOnMiddleMouseButtonDoubleClick;
			using CBaseBlock::getOnMouseVerticalWheel;
			using CBaseBlock::getOnMouseHorizontalWheel;
			using CBaseBlock::getOnMouseHover;
			using CBaseBlock::getOnMouseLeave;
			using CBaseBlock::getOnKillFocus;
			using CBaseBlock::getOnSetFocus;
			using CBaseBlock::getOnResetFocus;
			using CBaseBlock::getOnKillCaptureKeyboard;
			using CBaseBlock::getOnKillCaptureMouse;
			using CBaseBlock::getOnSetCaptureKeyboard;
			using CBaseBlock::getOnSetCaptureMouse;
			using CBaseBlock::getOnChangeParentStyle;
			using CBaseBlock::getOnChangeStyle;
			using CBaseBlock::getOnShow;
			using CBaseBlock::getOnBeforeHide;
			using CBaseBlock::getOnHide;
			using CBaseBlock::getOnPaint;
			using CBaseBlock::getOnBeforeResize;
			using CBaseBlock::getOnResize;
			using CBaseBlock::getOnBeforeMove;
			using CBaseBlock::getOnMove;
			using CBaseBlock::setOnKeyDown;
			using CBaseBlock::setOnKeyUp;
			using CBaseBlock::setOnChar;
			using CBaseBlock::setOnDeadChar;
			using CBaseBlock::setOnSysKeyDown;
			using CBaseBlock::setOnSysKeyUp;
			using CBaseBlock::setOnSysChar;
			using CBaseBlock::setOnSysDeadChar;
			using CBaseBlock::setOnMouseMove;
			using CBaseBlock::setOnLeftMouseButtonDown;
			using CBaseBlock::setOnLeftMouseButtonUp;
			using CBaseBlock::setOnLeftMouseButtonDoubleClick;
			using CBaseBlock::setOnRightMouseButtonDown;
			using CBaseBlock::setOnRightMouseButtonUp;
			using CBaseBlock::setOnRightMouseButtonDoubleClick;
			using CBaseBlock::setOnMiddleMouseButtonDown;
			using CBaseBlock::setOnMiddleMouseButtonUp;
			using CBaseBlock::setOnMiddleMouseButtonDoubleClick;
			using CBaseBlock::setOnMouseVerticalWheel;
			using CBaseBlock::setOnMouseHorizontalWheel;
			using CBaseBlock::setOnMouseHover;
			using CBaseBlock::setOnMouseLeave;
			using CBaseBlock::setOnKillFocus;
			using CBaseBlock::setOnSetFocus;
			using CBaseBlock::setOnResetFocus;
			using CBaseBlock::setOnKillCaptureKeyboard;
			using CBaseBlock::setOnKillCaptureMouse;
			using CBaseBlock::setOnSetCaptureKeyboard;
			using CBaseBlock::setOnSetCaptureMouse;
			using CBaseBlock::setOnChangeParentStyle;
			using CBaseBlock::setOnChangeStyle;
			using CBaseBlock::setOnShow;
			using CBaseBlock::setOnBeforeHide;
			using CBaseBlock::setOnHide;
			using CBaseBlock::setOnPaint;
			using CBaseBlock::setOnBeforeResize;
			using CBaseBlock::setOnResize;
			using CBaseBlock::setOnBeforeMove;
			using CBaseBlock::setOnMove;
			using CBaseBlock::getControlStyle;
			using CBaseBlock::getStyle;
			using CBaseBlock::getUseStyle;
			using CBaseBlock::getConstraints;
			using CBaseBlock::getMinConstraints;
			using CBaseBlock::getMaxConstraints;
			using CBaseBlock::getMinWidth;
			using CBaseBlock::getMinHeight;
			using CBaseBlock::getMaxWidth;
			using CBaseBlock::getMaxHeight;
			using CBaseBlock::setStyle;
			using CBaseBlock::setUseStyle;
			using CBaseBlock::setConstraints;
			using CBaseBlock::setMinConstraints;
			using CBaseBlock::setMinWidth;
			using CBaseBlock::setMinHeight;
			using CBaseBlock::setMaxWidth;
			using CBaseBlock::setMaxHeight;
			using CBaseBlock::setCursor;
			using CBaseBlock::getBorderAntiAliazing;
			using CBaseBlock::getBorderWidth;
			using CBaseBlock::getLeftBorderWidth;
			using CBaseBlock::getTopBorderWidth;
			using CBaseBlock::getRightBorderWidth;
			using CBaseBlock::getBottomBorderWidth;
			using CBaseBlock::getBorderRadius;
			using CBaseBlock::getLeftTopRadius;
			using CBaseBlock::getRightTopRadius;
			using CBaseBlock::getRightBottomRadius;
			using CBaseBlock::getLeftBottomRadius;
			using CBaseBlock::getLeftBorderColor;
			using CBaseBlock::getTopBorderColor;
			using CBaseBlock::getRightBorderColor;
			using CBaseBlock::getBottomBorderColor;
			using CBaseBlock::getLeftBorderImage;
			using CBaseBlock::getTopBorderImage;
			using CBaseBlock::getRightBorderImage;
			using CBaseBlock::getBottomBorderImage;
			using CBaseBlock::getLeftBorderInterpolate;
			using CBaseBlock::getTopBorderInterpolate;
			using CBaseBlock::getRightBorderInterpolate;
			using CBaseBlock::getBottomBorderInterpolate;
			using CBaseBlock::getPadding;
			using CBaseBlock::getPaddingLeft;
			using CBaseBlock::getPaddingTop;
			using CBaseBlock::getPaddingRight;
			using CBaseBlock::getPaddingBottom;
			using CBaseBlock::getBackgrondColor;
			using CBaseBlock::getBackgroundImage;
			using CBaseBlock::getBackgroundRepeatX;
			using CBaseBlock::getBackgroundRepeatY;
			using CBaseBlock::getBackgroundPosition;
			using CBaseBlock::getBackgroundPositionX;
			using CBaseBlock::getBackgroundPositionY;
			using CBaseBlock::getBackgroundPositionPercentageX;
			using CBaseBlock::getBackgroundPositionPercentageY;
			using CBaseBlock::getBackgroundSize;
			using CBaseBlock::getBackgroundSizeX;
			using CBaseBlock::getBackgroundSizeY;
			using CBaseBlock::getBackgroundInterpolate;
			using CBaseBlock::getBackgroundRotation;
			using CBaseBlock::getBoxShadow;
			using CBaseBlock::getBoxShadowColor;
			using CBaseBlock::getBoxShadowShift;
			using CBaseBlock::getBoxShadowRadius;
			using CBaseBlock::setBorderAntiAliazing;
			using CBaseBlock::setBorderRadius;
			using CBaseBlock::setLeftTopRadius;
			using CBaseBlock::setRightTopRadius;
			using CBaseBlock::setRightBottomRadius;
			using CBaseBlock::setLeftBottomRadius;
			using CBaseBlock::setBorderColor;
			using CBaseBlock::setLeftBorderColor;
			using CBaseBlock::setTopBorderColor;
			using CBaseBlock::setRightBorderColor;
			using CBaseBlock::setBottomBorderColor;
			using CBaseBlock::setBorderInterpolate;
			using CBaseBlock::setLeftBorderInterpolate;
			using CBaseBlock::setTopBorderInterpolate;
			using CBaseBlock::setRightBorderInterpolate;
			using CBaseBlock::setBottomBorderInterpolate;
			using CBaseBlock::setBackgroundColor;
			using CBaseBlock::setBackgroundRepeat;
			using CBaseBlock::setBackgroundRepeatX;
			using CBaseBlock::setBackgroundRepeatY;
			using CBaseBlock::setBackgroundPosition;
			using CBaseBlock::setBackgroundPositionX;
			using CBaseBlock::setBackgroundPositionY;
			using CBaseBlock::setBackgroundPositionPercentage;
			using CBaseBlock::setBackgroundPositionPercentageX;
			using CBaseBlock::setBackgroundPositionPercentageY;
			using CBaseBlock::setBackgroundSize;
			using CBaseBlock::setBackgroundSizeX;
			using CBaseBlock::setBackgroundSizeY;
			using CBaseBlock::setBackgroundInterpolate;
			using CBaseBlock::setBackgroundRotation;
			using CBaseBlock::setBoxShadow;
			using CBaseBlock::setBoxShadowColor;
			using CBaseBlock::setBoxShadowShift;
			using CBaseBlock::setBoxShadowRadius;
		};
	}
}