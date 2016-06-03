// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#pragma once

#include "..\..\..\Form.h"
#include "..\..\Base\BaseBlock.h"
#include "..\..\..\Components\ImageList\ImageList.h"

namespace licui
{
	namespace application
	{
		class CMenuItem;
		class CMenu;
		class CMainMenuItem;
		class CMainMenu;

		class CMenuItem :public CControl
		{
			friend CMenu;
		public:
			enum TYPE
			{
				mitNormal,
				mitSeparator,
				mitCheckBox,
				mitRadioButton
			};

			enum STATE
			{
				misNormal,
				misChecked,
				misGrayed
			};

			typedef void(*FOnClick)(CControl *sender, void *param);
		private:
			struct SIZE
			{
				size_t Height;
				size_t WidthImage;
				size_t WidthCaptionImage;
				size_t WidthCaption;
				size_t WidthShortcut;
				size_t WidthArrow;
			};

			TYPE m_eType;
			STATE m_eState;
			math::RECTANGLE<size_t> m_sMarginImage;
			math::RECTANGLE<size_t> m_sMarginCaptionImage;
			math::RECTANGLE<size_t> m_sMarginCaption;
			math::RECTANGLE<size_t> m_sMarginShortcut;
			math::RECTANGLE<size_t> m_sMarginArrow;
			int m_iImageIndex;
			size_t m_iGroupIndex;
			String m_sCaption;
			CForm::SHORTCUT m_sShortcut;
			String m_sShortcutName;
			size_t m_iSeparatorHeight;
			APP_COLOR m_sSeparatorColor;
			APP_COLOR m_sDisabledTextColor;
			APP_COLOR m_sDisabledShadowColor;
			APP_COLOR m_sActiveBackgroundColor;
			APP_COLOR m_sActiveTextColor;
			APP_COLOR m_sActiveShadowColor;
			FOnClick m_fOnClick;
			APP_POINT m_sMenuShift;

			bool UpdateState();
			bool SearchImage(APP_IMAGE **image, APP_RECT &rect);
			bool SearchCaptionImage(APP_IMAGE **image, APP_RECT &rect, const bool ignore_state);
			bool SearchArrowImage(APP_IMAGE **image, APP_RECT &rect, const bool ignore_state);
			SIZE CalculateSize();
			APP_RECT CalculateRectSeparator();
			APP_RECT CalculateRectImage();
			APP_RECT CalculateRectCaptionImage();
			APP_RECT CalculateRectCaption();
			APP_RECT CalculateRectShortcut();
			APP_RECT CalculateRectArrow();
			void Paint(APP_RECT clip);
			void PaintSeparator(APP_RECT clip);
			void PaintControl(APP_RECT clip);
		protected:
			virtual String GetKeyName(const IWindow::KEY key);

			void NotifyOnAttachToForm() override;

			bool NotifyOnLeftMouseButtonDown(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift) override;
			bool NotifyOnLeftMouseButtonUp(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift) override;

			void NotifyOnChangeUseParentFont() override;
			void NotifyOnParentFontChangeSize() override;

			void NotifyOnFontChangeSize() override;

			void NotifyOnMouseHover() override;
			void NotifyOnChangeParentStyle() override;
			void NotifyOnChangeStyle() override;
			void NotifyOnDisable() override;
			void NotifyOnDetachControl(CControl *control) override;
			void NotifyOnPaint(APP_RECT clip) override;
			void NotifyOnHotkey(const IWindow::KEY key, const bool ctrl, const bool alt, const bool shift, const bool is_down) override;

			virtual void NotifyOnClick();

			bool UpdateFromStyle() override;
		public:
			CMenuItem();
			CMenuItem(CMenu *menu);

			APP_RECT getVisibleRect() override;

			virtual CMainMenu *getMainMenu();
			virtual CMenu *getParentMenu();
			virtual CMenu *getMenu();
			virtual bool getIsActive();
			virtual TYPE getType() const;
			virtual STATE getState() const;
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
			virtual int getImageIndex() const;
			virtual CImageList *getImageList();
			virtual size_t getGroupIndex() const;
			virtual String getCaption() const;
			virtual CForm::SHORTCUT getShortcut() const;
			virtual String getShortcutName() const;
			virtual size_t getSeparatorHeight() const;
			virtual APP_COLOR getSeparatorColor() const;
			virtual APP_COLOR getDisabledTextColor() const;
			virtual APP_COLOR getDisabledShadowColor() const;
			virtual APP_COLOR getActiveBackgroundColor() const;
			virtual APP_COLOR getActiveTextColor() const;
			virtual APP_COLOR getActiveShadowColor() const;
			virtual FOnClick getOnClick() const;
			virtual APP_POINT getMenuShift() const;
			virtual int getMenuShiftX() const;
			virtual int getMenuShiftY() const;

			virtual CMenuItem *setParentMenu(CMenu *value);
			virtual CMenuItem *setMenu(CMenu *value);
			virtual CMenuItem *setType(const TYPE value);
			virtual CMenuItem *setState(const STATE value);
			virtual CMenuItem *setMarginImage(const math::RECTANGLE<size_t> &value);
			virtual CMenuItem *setMarginImageLeft(const size_t value);
			virtual CMenuItem *setMarginImageTop(const size_t value);
			virtual CMenuItem *setMarginImageRight(const size_t value);
			virtual CMenuItem *setMarginImageBottom(const size_t value);
			virtual CMenuItem *setMarginCaptionImage(const math::RECTANGLE<size_t> &value);
			virtual CMenuItem *setMarginCaptionImageLeft(const size_t value);
			virtual CMenuItem *setMarginCaptionImageTop(const size_t value);
			virtual CMenuItem *setMarginCaptionImageRight(const size_t value);
			virtual CMenuItem *setMarginCaptionImageBottom(const size_t value);
			virtual CMenuItem *setMarginCaption(const math::RECTANGLE<size_t> &value);
			virtual CMenuItem *setMarginCaptionLeft(const size_t value);
			virtual CMenuItem *setMarginCaptionTop(const size_t value);
			virtual CMenuItem *setMarginCaptionRight(const size_t value);
			virtual CMenuItem *setMarginCaptionBottom(const size_t value);
			virtual CMenuItem *setMarginShortcut(const math::RECTANGLE<size_t> &value);
			virtual CMenuItem *setMarginShortcutLeft(const size_t value);
			virtual CMenuItem *setMarginShortcutTop(const size_t value);
			virtual CMenuItem *setMarginShortcutRight(const size_t value);
			virtual CMenuItem *setMarginShortcutBottom(const size_t value);
			virtual CMenuItem *setMarginArrow(const math::RECTANGLE<size_t> &value);
			virtual CMenuItem *setMarginArrowLeft(const size_t value);
			virtual CMenuItem *setMarginArrowTop(const size_t value);
			virtual CMenuItem *setMarginArrowRight(const size_t value);
			virtual CMenuItem *setMarginArrowBottom(const size_t value);
			virtual CMenuItem *setImageIndex(int value);
			virtual CMenuItem *setGroupIndex(const size_t value);
			virtual CMenuItem *setCaption(const String &value);
			virtual CMenuItem *setShortcut(const IWindow::KEY key, const bool control, const bool alt, const bool shift);
			virtual CMenuItem *setSeparatorHeight(size_t value);
			virtual CMenuItem *setSeparatorColor(const APP_COLOR &value);
			virtual CMenuItem *setDisabledTextColor(const APP_COLOR &value);
			virtual CMenuItem *setDisabledShadowColor(const APP_COLOR &value);
			virtual CMenuItem *setActiveBackgroundColor(const APP_COLOR &value);
			virtual CMenuItem *setActiveTextColor(const APP_COLOR &value);
			virtual CMenuItem *setActiveShadowColor(const APP_COLOR &value);
			virtual CMenuItem *setOnClick(FOnClick value);
			virtual CMenuItem *setMenuShift(const APP_POINT &value);
			virtual CMenuItem *setMenuShiftX(const int value);
			virtual CMenuItem *setMenuShiftY(const int value);
		public:
			using CControl::getOnMouseMove;
			using CControl::getOnLeftMouseButtonDown;
			using CControl::getOnLeftMouseButtonUp;
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
			using CControl::setOnMouseMove;
			using CControl::setOnLeftMouseButtonDown;
			using CControl::setOnLeftMouseButtonUp;
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
			using CControl::getControlStyle;
			using CControl::getStyle;
			using CControl::getUseStyle;
			using CControl::getControlFont;
			using CControl::getParentFont;
			using CControl::getFont;
			using CControl::getUseParentFont;
			using CControl::setEnabled;
			using CControl::setStyle;
			using CControl::setUseStyle;
			using CControl::setControlFont;
			using CControl::setFont;
			using CControl::setUseParentFont;
			using CControl::setCursor;
		};

		class CMenu :public CBaseBlock
		{
			friend CMenuItem;
			friend CMainMenuItem;
			friend CMainMenu;
		private:
			struct SIZE
			{
				size_t WidthImage;
				size_t WidthCaption;
				size_t WidthShortcut;
				size_t WidthArrow;
				math::POINT<size_t> SizeRequired;
				math::POINT<size_t> SizeActual;
				bool ScrollExists;
				size_t ScrollMax;
				size_t ScrollDelta;
				size_t ScrollValue;
			};

			BLOCK m_sBlock;
			SIZE m_sSize;
			int m_iActiveMenuItemIndex;
			unsigned int m_hScrollTimer;
			CImageList *m_pImageList;
			bool m_bShowImages;
			CMenuItem::FOnClick m_fOnClick;
			math::POINT<size_t> m_sMarginTopScrollArrow;
			math::POINT<size_t> m_sMarginBottomScrollArrow;
			bool m_bMouseOverTopScrollArrow;
			bool m_bMouseOverBottomScrollArrow;
			bool m_bMouseDownOnTopScrollArrow;
			bool m_bMouseDownOnBottomScrollArrow;

			void FillBlock();
			bool SearchTopScrollArrow(APP_IMAGE **image, APP_RECT &rect, const bool ignore_state);
			bool SearchBottomScrollArrow(APP_IMAGE **image, APP_RECT &rect, const bool ignore_state);
			void ClearActiveMenuItem();
			void CalculateSize();
			APP_RECT CalculateTopScrollArrowRect();
			APP_RECT CalculateBottomScrollArrowRect();
			void Update();
			void UpdateControls();
			void StopScrollTimer();
			static void TimerCallback(void *param);
			void ActivateSubmenu();
			bool HitTest(const int x, const int y);
			void RenderTopScrollArrow(APP_RECT clip);
			void RenderBottomScrollArrow(APP_RECT clip);

			void ProcessKeyUp();
			void ProcessKeyDown();
			void ProcessKeyHome();
			void ProcessKeyEnd();
			void ProcessKeyLeft();
			void ProcessKeyRight();
			void ProcessKeySpace();
			void ProcessKeyEnter();
			void ProcessKeyEscape();
			void ProcessKeyTab();
			void ProcessMouseUp(); // Stop scroll timer
			bool ProcessMouseWheel(const int x, const int y, const int delta);
		protected:
			void NotifyOnBeforeDetachComponentFromForm(CComponent *component) override; // Handle image list removal
			void NotifyOnBeforeDetachFromForm() override; // Free scroll timer
			void NotifyOnUpdateComponent(CComponent *component) override;

			bool NotifyOnMouseMove(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift) override; // Repaint scroll arrows if required
			bool NotifyOnLeftMouseButtonDown(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift) override; // Handle start scrolling

			void NotifyOnMouseHover() override; // Repaint scroll arrows if required
			void NotifyOnMouseLeave() override; // Repaint scroll arrows if required
			void NotifyOnChangeParentStyle() override; // Update params and repaint
			void NotifyOnChangeStyle() override; // Update params and repaint
			void NotifyOnHide() override; // Clear active menu item and hide all submenus
			void NotifyOnDetachControl(CControl *control) override; // Update on remove menu item
			void NotifyOnPaint(APP_RECT clip) override;

			virtual void NotifyOnClick(CControl *sender);
			
			BLOCK *getBlock() override;
			bool UpdateFromStyle() override; // Copy params from new style. Return false is no new style exists
		public:
			CMenu();
			CMenu(CMainMenuItem *item);
			CMenu(CMenuItem *item);

			APP_RECT getVisibleRect() override;
			APP_RECT getClientRect() override;
			CControl *setConstraints(const math::RECTANGLE<size_t> &value) override;

			CBaseBlock *setBorderWidth(const size_t value) override;
			CBaseBlock *setBorderWidth(const size_t left, const size_t top, const size_t right, const size_t bottom) override;
			CBaseBlock *setLeftBorderWidth(const size_t value) override;
			CBaseBlock *setTopBorderWidth(const size_t value) override;
			CBaseBlock *setRightBorderWidth(const size_t value) override;
			CBaseBlock *setBottomBorderWidth(const size_t value) override;
			CBaseBlock *setBorderRadius(const size_t value) override;
			CBaseBlock *setBorderRadius(const size_t left_top, const size_t right_top, const size_t right_bottom, const size_t left_bottom) override;
			CBaseBlock *setLeftTopRadius(const size_t value) override;
			CBaseBlock *setRightTopRadius(const size_t value) override;
			CBaseBlock *setRightBottomRadius(const size_t value) override;
			CBaseBlock *setLeftBottomRadius(const size_t value) override;
			CBaseBlock *setPadding(const math::RECTANGLE<size_t> &value) override;
			CBaseBlock *setPadding(const size_t value) override;
			CBaseBlock *setPaddingLeft(const size_t value) override;
			CBaseBlock *setPaddingTop(const size_t value) override;
			CBaseBlock *setPaddingRight(const size_t value) override;
			CBaseBlock *setPaddingBottom(const size_t value) override;

			virtual CMainMenu *getMainMenu();
			virtual CMainMenuItem *getMainMenuItem();
			virtual CMenuItem *getParentMenuItem();
			virtual size_t getMenuItemCount() const;
			virtual CMenuItem *getMenuItem(const int index);
			virtual bool getHaveScroll() const;
			virtual size_t getScrollMax() const;
			virtual size_t getScrollDelta() const;
			virtual size_t getScroll() const;
			virtual int getActiveMenuItemIndex() const;
			virtual CMenuItem *getActiveMenuItem();
			virtual CImageList *getImageList();
			virtual bool getShowImages();
			virtual CMenuItem::FOnClick getOnClick() const;
			virtual math::POINT<size_t> getMarginTopScrollArrow() const;
			virtual size_t getMarginTopScrollArrowTop() const;
			virtual size_t getMarginTopScrollArrowBottom() const;
			virtual math::POINT<size_t> getMarginBottomScrollArrow() const;
			virtual size_t getMarginBottomScrollArrowTop() const;
			virtual size_t getMarginBottomScrollArrowBottom() const;

			virtual CMenu *setMainMenuItem(CMainMenuItem *value);
			virtual CMenu *setParentMenuItem(CMenuItem *value);
			virtual CMenu *setScrollDelta(const size_t value);
			virtual CMenu *setScroll(size_t value);
			virtual CMenu *setActiveMenuItemIndex(int value);
			virtual CMenu *setActiveMenuItem(CMenuItem *value);
			virtual CMenu *setImageList(CImageList *value);
			virtual CMenu *setShowImages(const bool value);
			virtual CMenu *setOnClick(CMenuItem::FOnClick value);
			virtual CMenu *setMarginTopScrollArrow(const math::POINT<size_t> &value);
			virtual CMenu *setMarginTopScrollArrowTop(const size_t value);
			virtual CMenu *setMarginTopScrollArrowBottom(const size_t value);
			virtual CMenu *setMarginBottomScrollArrow(const math::POINT<size_t> &value);
			virtual CMenu *setMarginBottomScrollArrowTop(const size_t value);
			virtual CMenu *setMarginBottomScrollArrowBottom(const size_t value);

			virtual void Show(const int x, const int y);
			virtual void Hide();

			virtual CMenu *AddMenuItem(CMenuItem *item);
			virtual CMenu *DeleteMenuItem(const size_t index);
			virtual CMenu *DeleteMenuItem(CMenuItem *item);
			virtual CMenu *DeleteMenuItems();
		public:
			using CBaseBlock::getOnMouseMove;
			using CBaseBlock::getOnLeftMouseButtonDown;
			using CBaseBlock::getOnMouseVerticalWheel;
			using CBaseBlock::getOnMouseHorizontalWheel;
			using CBaseBlock::getOnMouseHover;
			using CBaseBlock::getOnMouseLeave;
			using CBaseBlock::getOnChangeParentStyle;
			using CBaseBlock::getOnChangeStyle;
			using CBaseBlock::getOnShow;
			using CBaseBlock::getOnBeforeHide;
			using CBaseBlock::getOnHide;
			using CBaseBlock::getOnPaint;
			using CBaseBlock::setOnMouseMove;
			using CBaseBlock::setOnLeftMouseButtonDown;
			using CBaseBlock::setOnMouseHover;
			using CBaseBlock::setOnMouseLeave;
			using CBaseBlock::setOnChangeParentStyle;
			using CBaseBlock::setOnChangeStyle;
			using CBaseBlock::setOnShow;
			using CBaseBlock::setOnBeforeHide;
			using CBaseBlock::setOnHide;
			using CBaseBlock::setOnPaint;
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
			using CBaseBlock::getControlFont;
			using CBaseBlock::getParentFont;
			using CBaseBlock::getFont;
			using CBaseBlock::getUseParentFont;
			using CBaseBlock::setStyle;
			using CBaseBlock::setUseStyle;
			using CBaseBlock::setMinConstraints;
			using CBaseBlock::setMinWidth;
			using CBaseBlock::setMinHeight;
			using CBaseBlock::setMaxWidth;
			using CBaseBlock::setMaxHeight;
			using CBaseBlock::setControlFont;
			using CBaseBlock::setFont;
			using CBaseBlock::setUseParentFont;
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

		class CMainMenuItem :public CControl
		{
			friend CMenu;
			friend CMainMenu;
		public:
			enum ALIGN
			{
				ialLeft,
				ialRight
			};
		private:
			String m_sCaption;
			math::RECTANGLE<size_t> m_sMarginCaption;
			APP_POINT m_sMenuShift;
			APP_COLOR m_sActiveBackgroundColor;
			APP_COLOR m_sActiveTextColor;
			APP_COLOR m_sActiveShadowColor;
			APP_COLOR m_sHoverBackgroundColor;
			APP_COLOR m_sHoverTextColor;
			APP_COLOR m_sHoverShadowColor;
			APP_COLOR m_sDisabledTextColor;
			APP_COLOR m_sDisabledShadowColor;
			ALIGN m_eAlign;
			bool m_bImageVisible;
			int m_iImageIndex;
			ALIGN m_eImageAlign; // From caption
			math::RECTANGLE<size_t> m_sImageMargin;
			bool m_bArrowVisible;
			ALIGN m_eArrowAlign; // From caption
			math::RECTANGLE<size_t> m_sArrowMargin;
			CMenuItem::FOnClick m_fOnClick;

			math::POINT<size_t> CalculateSize();
			APP_RECT CalculateRectImage();
			APP_RECT CalculateRectCaptionWithArrow();
			APP_RECT CalculateRectArrow();
			APP_RECT CalculateRectCaption();
			bool SearchImage(APP_IMAGE **image, APP_RECT &rect);
			bool SearchArrowImage(APP_IMAGE **image, APP_RECT &rect, const bool ignore_state);
			void Paint(APP_RECT clip);
		protected:
			bool UpdateFromStyle() override;

			bool NotifyOnLeftMouseButtonDown(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift) override;
			bool NotifyOnLeftMouseButtonUp(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift) override;

			void NotifyOnChangeUseParentFont() override;
			void NotifyOnParentFontChangeSize() override;

			void NotifyOnFontChangeSize() override;

			void NotifyOnMouseHover() override; // Repaint and open submenu
			void NotifyOnMouseLeave() override; // Repaint
			void NotifyOnChangeParentStyle() override; // Update from style and call parent update
			void NotifyOnChangeStyle() override; // Update from style and call parent update
			void NotifyOnDisable() override; // Hide menu. Deactivate mainmenu if it is active item
			void NotifyOnPaint(APP_RECT clip) override;

			virtual void NotifyOnClick();
		public:
			CMainMenuItem();
			CMainMenuItem(CMainMenu *menu);

			virtual bool getIsActive();
			virtual CMainMenu *getMainMenu();
			virtual CMenu* getMenu();
			virtual String getCaption() const;
			virtual math::RECTANGLE<size_t> getMarginCaption() const;
			virtual size_t getMarginCaptionLeft() const;
			virtual size_t getMarginCaptionTop() const;
			virtual size_t getMarginCaptionRight() const;
			virtual size_t getMarginCaptionBottom() const;
			virtual APP_POINT getMenuShift() const;
			virtual int getMenuShiftX() const;
			virtual int getMenuShiftY() const;
			virtual APP_COLOR getActiveBackgroundColor() const;
			virtual APP_COLOR getActiveTextColor() const;
			virtual APP_COLOR getActiveShadowColor() const;
			virtual APP_COLOR getHoverBackgroundColor() const;
			virtual APP_COLOR getHoverTextColor() const;
			virtual APP_COLOR getHoverShadowColor() const;
			virtual APP_COLOR getDisabledTextColor() const;
			virtual APP_COLOR getDisabledShadowColor() const;
			virtual ALIGN getAlignment() const;
			virtual bool getImageVisible() const;
			virtual int getImageIndex() const;
			virtual ALIGN getImageAlign() const;
			virtual math::RECTANGLE<size_t> getImageMargin() const;
			virtual size_t getImageMarginLeft() const;
			virtual size_t getImageMarginTop() const;
			virtual size_t getImageMarginRight() const;
			virtual size_t getImageMarginBottom() const;
			virtual bool getArrowVisible() const;
			virtual ALIGN getArrowAlign() const;
			virtual math::RECTANGLE<size_t> getArrowMargin() const;
			virtual size_t getArrowMarginLeft() const;
			virtual size_t getArrowMarginTop() const;
			virtual size_t getArrowMarginRight() const;
			virtual size_t getArrowMarginBottom() const;
			virtual CMenuItem::FOnClick getOnClick() const;

			virtual CMainMenuItem *setMainMenu(CMainMenu *value);
			virtual CMainMenuItem *setMenu(CMenu *value);
			virtual CMainMenuItem *setCaption(const String &value);
			virtual CMainMenuItem *setMarginCaption(const math::RECTANGLE<size_t> &value);
			virtual CMainMenuItem *setMarginCaptionLeft(const size_t value);
			virtual CMainMenuItem *setMarginCaptionTop(const size_t value);
			virtual CMainMenuItem *setMarginCaptionRight(const size_t value);
			virtual CMainMenuItem *setMarginCaptionBottom(const size_t value);
			virtual CMainMenuItem *setMenuShift(const APP_POINT &value);
			virtual CMainMenuItem *setMenuShiftX(const int value);
			virtual CMainMenuItem *setMenuShiftY(const int value);
			virtual CMainMenuItem *setActiveBackgroundColor(const APP_COLOR &value);
			virtual CMainMenuItem *setActiveTextColor(const APP_COLOR &value);
			virtual CMainMenuItem *setActiveShadowColor(const APP_COLOR &value);
			virtual CMainMenuItem *setHoverBackgroundColor(const APP_COLOR &value);
			virtual CMainMenuItem *setHoverTextColor(const APP_COLOR &value);
			virtual CMainMenuItem *setHoverShadowColor(const APP_COLOR &value);
			virtual CMainMenuItem *setDisabledTextColor(const APP_COLOR &value);
			virtual CMainMenuItem *setDisabledShadowColor(const APP_COLOR &value);
			virtual CMainMenuItem *setAlignment(const ALIGN value);
			virtual CMainMenuItem *setImageVisible(const bool value);
			virtual CMainMenuItem *setImageIndex(int value);
			virtual CMainMenuItem *setImageAlign(const ALIGN value);
			virtual CMainMenuItem *setImageMargin(const math::RECTANGLE<size_t> &value);
			virtual CMainMenuItem *setImageMarginLeft(const size_t value);
			virtual CMainMenuItem *setImageMarginTop(const size_t value);
			virtual CMainMenuItem *setImageMarginRight(const size_t value);
			virtual CMainMenuItem *setImageMarginBottom(const size_t value);
			virtual CMainMenuItem *setArrowVisible(const bool value);
			virtual CMainMenuItem *setArrowAlign(const ALIGN value);
			virtual CMainMenuItem *setArrowMargin(const math::RECTANGLE<size_t> &value);
			virtual CMainMenuItem *setArrowMarginLeft(const size_t value);
			virtual CMainMenuItem *setArrowMarginTop(const size_t value);
			virtual CMainMenuItem *setArrowMarginRight(const size_t value);
			virtual CMainMenuItem *setArrowMarginBottom(const size_t value);
			virtual CMainMenuItem *setOnClick(CMenuItem::FOnClick value);
		public:
			using CControl::getOnMouseMove;
			using CControl::getOnLeftMouseButtonDown;
			using CControl::getOnLeftMouseButtonUp;
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
			using CControl::setOnMouseMove;
			using CControl::setOnLeftMouseButtonDown;
			using CControl::setOnLeftMouseButtonUp;
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
			using CControl::getControlStyle;
			using CControl::getStyle;
			using CControl::getUseStyle;
			using CControl::getControlFont;
			using CControl::getParentFont;
			using CControl::getFont;
			using CControl::getUseParentFont;
			using CControl::setEnabled;
			using CControl::setStyle;
			using CControl::setUseStyle;
			using CControl::setControlFont;
			using CControl::setFont;
			using CControl::setUseParentFont;
			using CControl::setCursor;
		};

		class CMainMenu :public CControl
		{
			friend CMenuItem;
			friend CMainMenuItem;
		private:
			int m_iActiveMenuItemIndex;
			CImageList *m_pImageList;
			APP_COLOR m_sBackgroundColor;
			CMenuItem::FOnClick m_fOnClick;
			bool m_bDeactivating;
			bool m_bActivating;
			bool m_bCaretVisible;

			void Update();
			void UpdateControls(size_t width_right);
			bool HitTest(const int x, const int y);

			void ProcessKeyLeft();
			void ProcessKeyRight();
			void ProcessKeyHome();
			void ProcessKeyEnd();
			void ProcessKeyUp();
			void ProcessKeyDown();
			void ProcessKeyEnter();
			void ProcessKeySpace();
			void ProcessKeyEscape();
			void ProcessKeyTab();
		protected:
			bool UpdateFromStyle() override;

			void NotifyOnBeforeDetachComponentFromForm(CComponent *component) override;
			void NotifyOnUpdateComponent(CComponent *component) override;

			bool NotifyOnKeyDown(const IWindow::KEY key) override;
			bool NotifyOnKeyUp(const IWindow::KEY key) override;
			bool NotifyOnChar(const wchar_t chr) override;
			bool NotifyOnDeadChar(const wchar_t chr) override;
			bool NotifyOnSysKeyDown(const IWindow::KEY key) override;
			bool NotifyOnSysKeyUp(const IWindow::KEY key) override;
			bool NotifyOnSysChar(const wchar_t chr) override;
			bool NotifyOnSysDeadChar(const wchar_t chr) override;
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

			void NotifyOnKillCaptureKeyboard() override;
			void NotifyOnKillCaptureMouse() override;
			void NotifyOnSetCaptureMouse() override;
			void NotifyOnShow() override;
			void NotifyOnDetachControl(CControl *control) override;
			void NotifyOnPaint(APP_RECT clip) override;

			// Should Call ProcessMouseUp of childs and return false on MouseUp
			virtual void NotifyOnClick(CControl *sender);
		public:
			CMainMenu();
			CMainMenu(CForm *form);

			virtual bool getIsActive() const;
			virtual CImageList *getImageList();
			virtual int getActiveMenuItemIndex();
			virtual CMainMenuItem *getActiveMenuItem();
			virtual size_t getMenuItemCount();
			virtual CMainMenuItem *getMenuItem(const int index);
			virtual APP_COLOR getBackgroundColor() const;
			virtual CMenuItem::FOnClick getOnClick() const;

			virtual CMainMenu *setImageList(CImageList *value);
			virtual CMainMenu *setActiveMenuItemIndex(int value); // Hide old and show new
			virtual CMainMenu *setActiveMenuItem(CMainMenuItem *value); // Hide old and show new
			virtual CMainMenu *setBackgroundColor(const APP_COLOR &value);
			virtual CMainMenu *setOnClick(CMenuItem::FOnClick value);

			virtual CMainMenu *Activate();
			virtual CMainMenu *Deactivate();

			virtual CMainMenu *AddMenuItem(CMainMenuItem *item);
			virtual CMainMenu *DeleteMenuItem(const size_t index);
			virtual CMainMenu *DeleteMenuItem(CMainMenuItem *item);
			virtual CMainMenu *DeleteMenuItems();
		public:
			using CControl::getOnKeyDown;
			using CControl::getOnKeyUp;
			using CControl::getOnChar;
			using CControl::getOnDeadChar;
			using CControl::getOnSysKeyDown;
			using CControl::getOnSysKeyUp;
			using CControl::getOnSysChar;
			using CControl::getOnSysDeadChar;
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
			using CControl::getOnMouseHover;
			using CControl::getOnMouseLeave;
			using CControl::getOnKillFocus;
			using CControl::getOnSetFocus;
			using CControl::getOnResetFocus;
			using CControl::getOnKillCaptureKeyboard;
			using CControl::getOnKillCaptureMouse;
			using CControl::getOnSetCaptureKeyboard;
			using CControl::getOnSetCaptureMouse;
			using CControl::getOnChangeParentStyle;
			using CControl::getOnChangeStyle;
			using CControl::getOnShow;
			using CControl::getOnBeforeHide;
			using CControl::getOnHide;
			using CControl::getOnPaint;
			using CControl::getOnParentResize;
			using CControl::getOnParentMove;
			using CControl::getOnBeforeResize;
			using CControl::getOnResize;
			using CControl::getOnBeforeMove;
			using CControl::getOnMove;
			using CControl::setOnKeyDown;
			using CControl::setOnKeyUp;
			using CControl::setOnChar;
			using CControl::setOnDeadChar;
			using CControl::setOnSysKeyDown;
			using CControl::setOnSysKeyUp;
			using CControl::setOnSysChar;
			using CControl::setOnSysDeadChar;
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
			using CControl::setOnMouseHover;
			using CControl::setOnMouseLeave;
			using CControl::setOnKillFocus;
			using CControl::setOnSetFocus;
			using CControl::setOnResetFocus;
			using CControl::setOnKillCaptureKeyboard;
			using CControl::setOnKillCaptureMouse;
			using CControl::setOnSetCaptureKeyboard;
			using CControl::setOnSetCaptureMouse;
			using CControl::setOnChangeParentStyle;
			using CControl::setOnChangeStyle;
			using CControl::setOnShow;
			using CControl::setOnBeforeHide;
			using CControl::setOnHide;
			using CControl::setOnPaint;
			using CControl::setOnParentResize;
			using CControl::setOnParentMove;
			using CControl::setOnBeforeResize;
			using CControl::setOnResize;
			using CControl::setOnBeforeMove;
			using CControl::setOnMove;
			using CControl::getTabStop;
			using CControl::getControlStyle;
			using CControl::getStyle;
			using CControl::getUseStyle;
			using CControl::getControlFont;
			using CControl::getParentFont;
			using CControl::getFont;
			using CControl::getUseParentFont;
			using CControl::setVisible;
			using CControl::setTabStop;
			using CControl::setStyle;
			using CControl::setUseStyle;
			using CControl::setControlFont;
			using CControl::setFont;
			using CControl::setUseParentFont;
			using CControl::setFocus;
			using CControl::setTabOrder;
			using CControl::setCursor;
		};
	}
}