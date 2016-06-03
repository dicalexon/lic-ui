// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#pragma once

#include "..\..\..\..\Strings\Strings.h"
#include "..\..\..\Types.h"
#include "..\..\..\History.h"
#include "..\..\Base\BaseBlock.h"
#include "..\PopupMenu\PopupMenu.h"

namespace licui
{
	namespace application
	{
		class CEdit :public CBaseBlock
		{
		public:
			enum STATE
			{
				stNormal,
				stNormalHovered,
				stActive,
				stActiveHovered,
				stDisabled,
				stDisabledHovered
			};
			typedef void(*FOnChange)(CEdit *sender, void *param);
		private:
			struct BLOCK_EDIT :public BLOCK
			{
				APP_COLOR SelectionBackground;
				APP_COLOR SelectionTextColor;
				APP_COLOR SelectionShadowColor;
			};

			struct HISTORY
			{
				String Text;
				size_t CaretPosition;
				int Scroll;
			};
		private:
			String m_sText;
			int m_iScroll;
			APP_POINT m_sSelection;
			bool m_bIsReplacing;
			size_t m_iMaxLength;
			size_t m_iCaretPosition;
			bool m_bIsMouseDown;
			bool m_bIsMoveSelection;
			bool m_bDeselectMovedSubstring;
			size_t m_iMouseDownCaretPosition;
			CHistory<HISTORY> m_cHistory;
			bool m_bReadOnly;
			CPopupMenu *m_pPopupMenu;
			FOnChange m_fOnChange;

			void FillBlocks();
			void CalculateTextPosition(APP_POINT &pos, APP_POINT &char_size);
			bool CalculateCaretPosition(const APP_POINT &text_pos, const APP_RECT &text_rect, APP_POINT &pos);
			bool CalculateSelectionRectangle(APP_RECT &rect, int &shift);
			size_t CursorToCaret(const int x);
			void RenderSelection(APP_RECT clip);

			void ProcessKeyLeft();
			void ProcessKeyRight();
			void ProcessKeyHome();
			void ProcessKeyEnd();
			void ProcessKeyDelete();
			void ProcessKeyInsert();
			void ProcessKeyBack();
			void ProcessMouseDown(const int x, const int y, const bool shift);
			void ProcessMouseUp(const bool ctrl);
			void ProcessMouseMove(const int x, const int y);
			void ProcessMouseDoubleClick();
		protected:
			BLOCK_EDIT m_sBlock[stDisabledHovered + 1];

			void NotifyOnChangeUseParentFont() override;
			void NotifyOnParentFontChangeSize() override;

			void NotifyOnFontChangeSize() override;

			bool NotifyOnKeyDown(const IWindow::KEY key) override;
			bool NotifyOnKeyUp(const IWindow::KEY key) override;
			bool NotifyOnChar(const wchar_t chr) override;
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
			void NotifyOnSetFocus(CControl *old) override;
			void NotifyOnResetFocus() override;
			void NotifyOnParentResize() override;
			void NotifyOnParentMove() override;
			void NotifyOnResize(const APP_POINT &old_size, const APP_POINT &new_size) override;
			void NotifyOnMove(const APP_POINT &old_position, const APP_POINT &new_position) override;
			void NotifyOnPaint(APP_RECT clip) override;
			void NotifyOnSetCaptureMouse() override;
			void NotifyOnKillCaptureMouse() override;

			virtual void NotifyOnChange();

			BLOCK *getBlock() override;
		public:
			CURSOR_TYPE getCursor() const override;

			virtual STATE getState();
			virtual String getText() const;
			virtual int getScroll() const;
			virtual APP_POINT getSelection() const;
			virtual int getSelectionStart() const;
			virtual int getSelectionEnd() const;
			virtual bool getIsReplacing() const;
			virtual size_t getMaxLength() const;
			virtual size_t getCaretPosition() const;
			virtual bool getDeselectMovedSubstring() const;
			virtual size_t getHistoryLimitCount() const;
			virtual size_t getHistoryLimitSize() const;
			virtual bool getReadOnly() const;
			virtual CPopupMenu *getPopupMenu();
			virtual FOnChange getOnChange() const;

			virtual CEdit *setText(String value);
			virtual CEdit *setScroll(int value);
			virtual CEdit *setSelection(APP_POINT value);
			virtual CEdit *setSelectionStart(size_t value);
			virtual CEdit *setSelectionEnd(size_t value);
			virtual CEdit *setMaxLength(const size_t value);
			virtual CEdit *setCaretPosition(size_t value);
			virtual CEdit *setDeselectMovedSubstring(const bool value);
			virtual CEdit *setHistoryLimitCount(const size_t value);
			virtual CEdit *setHistoryLimitSize(const size_t value);
			virtual CEdit *setReadOnly(const bool value);
			virtual CEdit *setPopupMenu(CPopupMenu *value);
			virtual CEdit *setOnChange(FOnChange value);

			APP_RECT getBorderWidth() override;
			size_t getLeftBorderWidth() override;
			size_t getTopBorderWidth() override;
			size_t getRightBorderWidth() override;
			size_t getBottomBorderWidth() override;
			APP_RECT getBorderRadius() override;
			size_t getLeftTopRadius() override;
			size_t getRightTopRadius() override;
			size_t getRightBottomRadius() override;
			size_t getLeftBottomRadius() override;
			APP_RECT getPadding() override;
			size_t getPaddingLeft() override;
			size_t getPaddingTop() override;
			size_t getPaddingRight() override;
			size_t getPaddingBottom() override;
			TEXT_ALIGN getCaptionHorizontalAlign() override;
			bool getCaptionText() override;
			bool getCaptionShadow() override;
			math::POINT<double> getCaptionScale() override;
			double getCaptionScaleX() override;
			double getCaptionScaleY() override;
			virtual size_t getBorderAntiAliazing(const STATE state);
			virtual APP_COLOR getLeftBorderColor(const STATE state);
			virtual APP_COLOR getTopBorderColor(const STATE state);
			virtual APP_COLOR getRightBorderColor(const STATE state);
			virtual APP_COLOR getBottomBorderColor(const STATE state);
			virtual APP_IMAGE *getLeftBorderImage(const STATE state);
			virtual APP_IMAGE *getTopBorderImage(const STATE state);
			virtual APP_IMAGE *getRightBorderImage(const STATE state);
			virtual APP_IMAGE *getBottomBorderImage(const STATE state);
			virtual bool getLeftBorderInterpolate(const STATE state);
			virtual bool getTopBorderInterpolate(const STATE state);
			virtual bool getRightBorderInterpolate(const STATE state);
			virtual bool getBottomBorderInterpolate(const STATE state);
			virtual APP_COLOR getCaptionTextColor(const STATE state);
			virtual APP_COLOR getCaptionShadowColor(const STATE state);
			virtual size_t getCaptionAntiAliazing(const STATE state);
			virtual APP_COLOR getBackgrondColor(const STATE state);
			virtual APP_IMAGE *getBackgroundImage(const STATE state);
			virtual bool getBackgroundRepeatX(const STATE state);
			virtual bool getBackgroundRepeatY(const STATE state);
			virtual APP_POINT getBackgroundPosition(const STATE state);
			virtual int getBackgroundPositionX(const STATE state);
			virtual int getBackgroundPositionY(const STATE state);
			virtual bool getBackgroundPositionPercentageX(const STATE state);
			virtual bool getBackgroundPositionPercentageY(const STATE state);
			virtual APP_POINT getBackgroundSize(const STATE state);
			virtual int getBackgroundSizeX(const STATE state);
			virtual int getBackgroundSizeY(const STATE state);
			virtual bool getBackgroundInterpolate(const STATE state);
			virtual double getBackgroundRotation(const STATE state);
			virtual APP_COLOR getSelectionBackground(const STATE state);
			virtual APP_COLOR getSelectionTextColor(const STATE state);
			virtual APP_COLOR getSelectionShadowColor(const STATE state);
			virtual bool getBoxShadow(const STATE state);
			virtual APP_COLOR getBoxShadowColor(const STATE state);
			virtual APP_POINT getBoxShadowShift(const STATE state);
			virtual size_t getBoxShadowRadius(const STATE state);

			virtual CEdit *setBorderAntiAliazing(const STATE state, size_t value);
			virtual CEdit *setBorderWidth(const size_t value);
			virtual CEdit *setBorderWidth(const size_t left, const size_t top, const size_t right, const size_t bottom);
			virtual CEdit *setLeftBorderWidth(const size_t value);
			virtual CEdit *setTopBorderWidth(const size_t value);
			virtual CEdit *setRightBorderWidth(const size_t value);
			virtual CEdit *setBottomBorderWidth(const size_t value);
			virtual CEdit *setBorderRadius(const size_t value);
			virtual CEdit *setBorderRadius(const size_t left_top, const size_t right_top, const size_t right_bottom, const size_t left_bottom);
			virtual CEdit *setLeftTopRadius(const size_t value);
			virtual CEdit *setRightTopRadius(const size_t value);
			virtual CEdit *setRightBottomRadius(const size_t value);
			virtual CEdit *setLeftBottomRadius(const size_t value);
			virtual CEdit *setBorderColor(const STATE state, const APP_COLOR &value);
			virtual CEdit *setBorderColor(const STATE state, const APP_COLOR &left, const APP_COLOR &top, const APP_COLOR &right, const APP_COLOR &bottom);
			virtual CEdit *setLeftBorderColor(const STATE state, const APP_COLOR &value);
			virtual CEdit *setTopBorderColor(const STATE state, const APP_COLOR &value);
			virtual CEdit *setRightBorderColor(const STATE state, const APP_COLOR &value);
			virtual CEdit *setBottomBorderColor(const STATE state, const APP_COLOR &value);
			virtual CEdit *setBorderInterpolate(const STATE state, const bool value);
			virtual CEdit *setBorderInterpolate(const STATE state, const bool left, const bool top, const bool right, const bool bottom);
			virtual CEdit *setLeftBorderInterpolate(const STATE state, const bool value);
			virtual CEdit *setTopBorderInterpolate(const STATE state, const bool value);
			virtual CEdit *setRightBorderInterpolate(const STATE state, const bool value);
			virtual CEdit *setBottomBorderInterpolate(const STATE state, const bool value);
			virtual CEdit *setPadding(const math::RECTANGLE<size_t> &value);
			virtual CEdit *setPadding(const size_t value);
			virtual CEdit *setPaddingLeft(const size_t value);
			virtual CEdit *setPaddingTop(const size_t value);
			virtual CEdit *setPaddingRight(const size_t value);
			virtual CEdit *setPaddingBottom(const size_t value);
			virtual CEdit *setCaptionText(const bool value);
			virtual CEdit *setCaptionShadow(const bool value);
			virtual CEdit *setCaptionTextColor(const STATE state, const APP_COLOR &value);
			virtual CEdit *setCaptionShadowColor(const STATE state, const APP_COLOR &value);
			virtual CEdit *setCaptionHorizontalAlign(const TEXT_ALIGN value);
			virtual CEdit *setCaptionAntiAliazing(const STATE state, size_t value);
			virtual CEdit *setCaptionScale(const math::POINT<double> &value);
			virtual CEdit *setCaptionScaleX(const double value);
			virtual CEdit *setCaptionScaleY(const double value);
			virtual CEdit *setBackgroundColor(const STATE state, const APP_COLOR &value);
			virtual CEdit *setBackgroundRepeat(const STATE state, const bool value);
			virtual CEdit *setBackgroundRepeat(const STATE state, const bool x, const bool y);
			virtual CEdit *setBackgroundRepeatX(const STATE state, const bool value);
			virtual CEdit *setBackgroundRepeatY(const STATE state, const bool value);
			virtual CEdit *setBackgroundPosition(const STATE state, const APP_POINT &value);
			virtual CEdit *setBackgroundPositionX(const STATE state, const int value);
			virtual CEdit *setBackgroundPositionY(const STATE state, const int value);
			virtual CEdit *setBackgroundPositionPercentage(const STATE state, const bool value);
			virtual CEdit *setBackgroundPositionPercentage(const STATE state, const bool x, const bool y);
			virtual CEdit *setBackgroundPositionPercentageX(const STATE state, const bool value);
			virtual CEdit *setBackgroundPositionPercentageY(const STATE state, const bool value);
			virtual CEdit *setBackgroundSize(const STATE state, const APP_POINT &value);
			virtual CEdit *setBackgroundSizeX(const STATE state, const int value);
			virtual CEdit *setBackgroundSizeY(const STATE state, const int value);
			virtual CEdit *setBackgroundInterpolate(const STATE state, const bool value);
			virtual CEdit *setBackgroundRotation(const STATE state, const double value);
			virtual CEdit *setSelectionBackground(const STATE state, const APP_COLOR &value);
			virtual CEdit *setSelectionTextColor(const STATE state, const APP_COLOR &value);
			virtual CEdit *setSelectionShadowColor(const STATE state, const APP_COLOR &value);
			virtual CEdit *setBoxShadow(const STATE state, const bool value);
			virtual CEdit *setBoxShadowColor(const STATE state, const APP_COLOR &value);
			virtual CEdit *setBoxShadowShift(const STATE state, const APP_POINT &value);
			virtual CEdit *setBoxShadowRadius(const STATE state, const size_t value);

			CEdit();
			CEdit(CControl *parent);
			CEdit(CForm *form);

			virtual CEdit *Select(int start, int end);
			virtual CEdit *SelectAll();
			virtual CEdit *DeselectAll();
			virtual CEdit *Clear();
			virtual CEdit *UpdateCaret();
			virtual CEdit *UpdateScroll();
			virtual bool CanUndo();
			virtual bool CanRedo();
			virtual CEdit *Undo();
			virtual CEdit *Redo();
			virtual bool Copy();
			virtual bool Cut();
			virtual CEdit *Paste();
			virtual CEdit *ClearHistory();
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
			using CBaseBlock::getOnChangeUseParentFont;
			using CBaseBlock::getOnParentFontChangeName;
			using CBaseBlock::getOnParentFontChangeHeight;
			using CBaseBlock::getOnParentFontChangeWeight;
			using CBaseBlock::getOnParentFontChangeItalic;
			using CBaseBlock::getOnParentFontChangeUnderline;
			using CBaseBlock::getOnParentFontChangeStrikeOut;
			using CBaseBlock::getOnParentFontChangeWidth;
			using CBaseBlock::getOnParentFontChangeCharSet;
			using CBaseBlock::getOnParentFontChangeQuality;
			using CBaseBlock::getOnParentFontChangePitchAndFamily;
			using CBaseBlock::getOnParentFontChangeOrientation;
			using CBaseBlock::getOnParentFontChangeDistance;
			using CBaseBlock::getOnParentFontChangeShadow;
			using CBaseBlock::getOnParentFontChangeShadowShift;
			using CBaseBlock::getOnParentFontChangeShadowBlur;
			using CBaseBlock::getOnParentFontChangeShadowColor;
			using CBaseBlock::getOnParentFontChangeColor;
			using CBaseBlock::getOnParentFontChangeInterpolate;
			using CBaseBlock::getOnParentFontBeginChange;
			using CBaseBlock::getOnParentFontEndChange;
			using CBaseBlock::getOnParentFontChangeSize;
			using CBaseBlock::getOnParentFontChangeStyle;
			using CBaseBlock::getOnFontChangeName;
			using CBaseBlock::getOnFontChangeHeight;
			using CBaseBlock::getOnFontChangeWeight;
			using CBaseBlock::getOnFontChangeItalic;
			using CBaseBlock::getOnFontChangeUnderline;
			using CBaseBlock::getOnFontChangeStrikeOut;
			using CBaseBlock::getOnFontChangeWidth;
			using CBaseBlock::getOnFontChangeCharSet;
			using CBaseBlock::getOnFontChangeQuality;
			using CBaseBlock::getOnFontChangePitchAndFamily;
			using CBaseBlock::getOnFontChangeOrientation;
			using CBaseBlock::getOnFontChangeDistance;
			using CBaseBlock::getOnFontChangeShadow;
			using CBaseBlock::getOnFontChangeShadowShift;
			using CBaseBlock::getOnFontChangeShadowBlur;
			using CBaseBlock::getOnFontChangeShadowColor;
			using CBaseBlock::getOnFontChangeColor;
			using CBaseBlock::getOnFontChangeInterpolate;
			using CBaseBlock::getOnFontBeginChange;
			using CBaseBlock::getOnFontEndChange;
			using CBaseBlock::getOnFontChangeSize;
			using CBaseBlock::getOnFontChangeStyle;
			using CBaseBlock::getOnMouseHover;
			using CBaseBlock::getOnMouseLeave;
			using CBaseBlock::getOnKillFocus;
			using CBaseBlock::getOnSetFocus;
			using CBaseBlock::getOnResetFocus;
			using CBaseBlock::getOnChangeParentStyle;
			using CBaseBlock::getOnChangeStyle;
			using CBaseBlock::getOnShow;
			using CBaseBlock::getOnBeforeHide;
			using CBaseBlock::getOnHide;
			using CBaseBlock::getOnEnable;
			using CBaseBlock::getOnDisable;
			using CBaseBlock::getOnPaint;
			using CBaseBlock::getOnParentResize;
			using CBaseBlock::getOnParentMove;
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
			using CBaseBlock::setOnChangeUseParentFont;
			using CBaseBlock::setOnParentFontChangeName;
			using CBaseBlock::setOnParentFontChangeHeight;
			using CBaseBlock::setOnParentFontChangeWeight;
			using CBaseBlock::setOnParentFontChangeItalic;
			using CBaseBlock::setOnParentFontChangeUnderline;
			using CBaseBlock::setOnParentFontChangeStrikeOut;
			using CBaseBlock::setOnParentFontChangeWidth;
			using CBaseBlock::setOnParentFontChangeCharSet;
			using CBaseBlock::setOnParentFontChangeQuality;
			using CBaseBlock::setOnParentFontChangePitchAndFamily;
			using CBaseBlock::setOnParentFontChangeOrientation;
			using CBaseBlock::setOnParentFontChangeDistance;
			using CBaseBlock::setOnParentFontChangeShadow;
			using CBaseBlock::setOnParentFontChangeShadowShift;
			using CBaseBlock::setOnParentFontChangeShadowBlur;
			using CBaseBlock::setOnParentFontChangeShadowColor;
			using CBaseBlock::setOnParentFontChangeColor;
			using CBaseBlock::setOnParentFontChangeInterpolate;
			using CBaseBlock::setOnParentFontBeginChange;
			using CBaseBlock::setOnParentFontEndChange;
			using CBaseBlock::setOnParentFontChangeSize;
			using CBaseBlock::setOnParentFontChangeStyle;
			using CBaseBlock::setOnFontChangeName;
			using CBaseBlock::setOnFontChangeHeight;
			using CBaseBlock::setOnFontChangeWeight;
			using CBaseBlock::setOnFontChangeItalic;
			using CBaseBlock::setOnFontChangeUnderline;
			using CBaseBlock::setOnFontChangeStrikeOut;
			using CBaseBlock::setOnFontChangeWidth;
			using CBaseBlock::setOnFontChangeCharSet;
			using CBaseBlock::setOnFontChangeQuality;
			using CBaseBlock::setOnFontChangePitchAndFamily;
			using CBaseBlock::setOnFontChangeOrientation;
			using CBaseBlock::setOnFontChangeDistance;
			using CBaseBlock::setOnFontChangeShadow;
			using CBaseBlock::setOnFontChangeShadowShift;
			using CBaseBlock::setOnFontChangeShadowBlur;
			using CBaseBlock::setOnFontChangeShadowColor;
			using CBaseBlock::setOnFontChangeColor;
			using CBaseBlock::setOnFontChangeInterpolate;
			using CBaseBlock::setOnFontBeginChange;
			using CBaseBlock::setOnFontEndChange;
			using CBaseBlock::setOnFontChangeSize;
			using CBaseBlock::setOnFontChangeStyle;
			using CBaseBlock::setOnMouseHover;
			using CBaseBlock::setOnMouseLeave;
			using CBaseBlock::setOnKillFocus;
			using CBaseBlock::setOnSetFocus;
			using CBaseBlock::setOnResetFocus;
			using CBaseBlock::setOnChangeParentStyle;
			using CBaseBlock::setOnChangeStyle;
			using CBaseBlock::setOnShow;
			using CBaseBlock::setOnBeforeHide;
			using CBaseBlock::setOnHide;
			using CBaseBlock::setOnEnable;
			using CBaseBlock::setOnDisable;
			using CBaseBlock::setOnPaint;
			using CBaseBlock::setOnParentResize;
			using CBaseBlock::setOnParentMove;
			using CBaseBlock::setOnBeforeResize;
			using CBaseBlock::setOnResize;
			using CBaseBlock::setOnBeforeMove;
			using CBaseBlock::setOnMove;
			using CBaseBlock::getTabStop;
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
			using CBaseBlock::getZIndex;
			using CBaseBlock::setParent;
			using CBaseBlock::setEnabled;
			using CBaseBlock::setVisible;
			using CBaseBlock::setAlign;
			using CBaseBlock::setTabStop;
			using CBaseBlock::setStyle;
			using CBaseBlock::setUseStyle;
			using CBaseBlock::setConstraints;
			using CBaseBlock::setMinConstraints;
			using CBaseBlock::setMinWidth;
			using CBaseBlock::setMinHeight;
			using CBaseBlock::setMaxWidth;
			using CBaseBlock::setMaxHeight;
			using CBaseBlock::setControlFont;
			using CBaseBlock::setFont;
			using CBaseBlock::setUseParentFont;
			using CBaseBlock::setFocus;
			using CBaseBlock::setRect;
			using CBaseBlock::setPosition;
			using CBaseBlock::setLeft;
			using CBaseBlock::setTop;
			using CBaseBlock::setSize;
			using CBaseBlock::setWidth;
			using CBaseBlock::setHeight;
			using CBaseBlock::setTabOrder;
			using CBaseBlock::setCursor;
			using CBaseBlock::setZIndex;
		};
	}
}