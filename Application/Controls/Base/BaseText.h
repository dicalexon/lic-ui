// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#pragma once

#include "..\..\Types.h"
#include "..\..\Window.h"
#include "..\..\History.h"

namespace licui
{
	namespace application
	{
		class CBaseText
		{
		public:
			enum STATE
			{
				stNormal,
				stHovered,
				stActive,
				stActiveHovered,
				stDisabled
			};
		private:
			struct LINE
			{
				size_t Start;
				size_t End;
				size_t Width;
				bool Empty;
			};

			struct HISTORY
			{
				String Text;
				size_t CaretPosition;
				math::POINT<size_t> Selection;
			};

			enum MOUSE_MODE
			{
				mmNone,
				mmSelect,
				mmMove,
				mmCopy
			};

			APP_RECT m_sRect;
			size_t m_iVerticalScroll;
			size_t m_iHorizontalScroll;
			String m_sText;
			math::POINT<size_t> m_sTextSize;
			size_t m_iLineHeight; // Height with margins
			math::POINT<size_t> m_sSelection;
			size_t m_iCaretPosition; // in range [0..m_sText.length()]
			bool m_bInserting;

			bool m_bHovered;
			std::vector<LINE> m_aLines; // At least one line exists event if text is empty
			unsigned int m_hTimer;
			MOUSE_MODE m_eMouseMode;
			size_t m_iSpaceWidth;
			size_t m_iMouseDownCaretPosition;
			CHistory<HISTORY> m_cHistory;

			size_t CursorToCaret(const int x, const int y, const APP_RECT &rect);
			static void TimerCallback(void *param);
			bool StartMouseModeSelect(size_t caret, const bool ctrl, const bool shift);
			APP_POINT CaretToForm(const size_t caret);
			size_t getCaretLine(const size_t caret);
			size_t CalculateLineHeight();
			size_t CalculateSpaceWidth();
			void UpdateLines();
			void UpdateTextSize();
			void UpdateScrolls();
			void DeleteSelectionInternal();
			void CutLength();
			String getStateName(const STATE state);

			bool ProcessInsert();
			bool ProcessInsertChar(const wchar_t chr);
			bool ProcessReplaceChar(const wchar_t chr);
			bool ProcessMoveFinish(const int x, const int y);
			bool ProcessCopyFinish(const int x, const int y);
		protected:
			APP_COLOR m_aTextColor[stDisabled + 1];
			APP_COLOR m_aShadowColor[stDisabled + 1];
			APP_COLOR m_aSelectionBackgroundColor[stDisabled + 1];
			APP_COLOR m_aSelectionTextColor[stDisabled + 1];
			APP_COLOR m_aSelectionShadowColor[stDisabled + 1];
			size_t m_iMaxWidth;
			size_t m_iMaxLength; // Max text length, 0 for unlimited
			bool m_bReadOnly;
			size_t m_iDeltaWheelVertical;
			size_t m_iDeltaWheelHorizontal;
			math::POINT<size_t> m_sLineMargin;

			virtual size_t getVerticalScroll() const;
			virtual size_t getHorizontalScroll() const;
			virtual APP_RECT getRect();
			virtual math::POINT<size_t> getTextSize();
			virtual size_t getLineHeight();
			virtual STATE getState();
			virtual size_t getMaxWidth() const; // Max virtual width, 0 - unlimited
			virtual math::POINT<size_t> getLineMargin() const; // Top and bottom
			virtual size_t getLineMarginTop() const;
			virtual size_t getLineMarginBottom() const;
			virtual const String &getText() const;
			virtual APP_COLOR getTextColor(const STATE state) const;
			virtual APP_COLOR getShadowColor(const STATE state) const;
			virtual APP_COLOR getSelectionBackgroundColor(const STATE state) const;
			virtual APP_COLOR getSelectionTextColor(const STATE state) const;
			virtual APP_COLOR getSelectionShadowColor(const STATE state) const;
			virtual size_t getMaxLength() const;
			virtual bool getReadOnly() const;
			virtual bool getInserting() const;
			virtual math::POINT<size_t> getSelection() const;
			virtual size_t getCaretPosition() const;
			virtual size_t getDeltaWheelVertical() const;
			virtual size_t getDeltaWheelHorizontal() const;
			virtual bool getVerticalScrollRequired(const size_t max_width, const size_t height);
			virtual bool getHorizontalScrollRequired(const size_t max_width);
			virtual size_t getHistoryLimitCount() const;
			virtual size_t getHistoryLimitSize() const;

			virtual bool setVerticalScroll(size_t value);
			virtual bool setHorizontalScroll(size_t value);
			virtual bool setRect(APP_RECT &rect);
			virtual bool setMaxWidth(const size_t value);
			virtual bool setLineMargin(const math::POINT<size_t> &value);
			virtual bool setLineMarginTop(const size_t value);
			virtual bool setLineMarginBottom(const size_t value);
			virtual bool setText(const String &value);
			virtual bool setTextColor(const STATE state, const APP_COLOR &value);
			virtual bool setShadowColor(const STATE state, const APP_COLOR &value);
			virtual bool setSelectionBackgroundColor(const STATE state, const APP_COLOR &value);
			virtual bool setSelectionTextColor(const STATE state, const APP_COLOR &value);
			virtual bool setSelectionShadowColor(const STATE state, const APP_COLOR &value);
			virtual bool setMaxLength(const size_t value);
			virtual bool setReadOnly(const bool value);
			virtual bool setInserting(const bool value);
			virtual bool setSelection(math::POINT<size_t> value);
			virtual bool setCaretPosition(size_t value);
			virtual bool setDeltaWheelVertical(size_t value);
			virtual bool setDeltaWheelHorizontal(size_t value);
			virtual bool setHistoryLimitCount(const size_t value);
			virtual bool setHistoryLimitSize(const size_t value);

			virtual bool ProcessMouseDown(const int x, const int y, const bool ctrl, const bool alt, const bool shift);
			virtual bool ProcessMouseUp(const int x, const int y, const bool ctrl, const bool shift);
			virtual bool ProcessMouseHover(const int x, const int y);
			virtual bool ProcessMouseLeave();
			virtual bool ProcessMouseMove(const int x, const int y);
			virtual bool ProcessMouseVerticalWheel(const int x, const int y, const int delta);
			virtual bool ProcessMouseHorizontalWheel(const int x, const int y, const int delta);
			virtual bool ProcessMouseDoubleClick(const int x, const int y);
			virtual bool ProcessKeyDown(const IWindow::KEY key, const bool ctrl, const bool alt, const bool shift, bool &text_changed, bool &caret_moved);
			virtual bool ProcessChar(const wchar_t chr);
			virtual bool ProcessSetFocus();
			virtual bool ProcessKillFocus();

			virtual void Update();
			virtual void Paint(APP_RECT clip);
			virtual bool UpdateFromStyle();
			virtual void UpdateCaret(); // Update caret visibility and position on form
			virtual bool ScrollToCaret();
			virtual bool CanUndo();
			virtual bool CanRedo();
			virtual bool Undo();
			virtual bool Redo();
			virtual bool ScrollLineUp();
			virtual bool MoveCaretLineUpAndSelect();
			virtual bool MoveCaretLineUp();
			virtual bool ScrollLineDown();
			virtual bool MoveCaretLineDownAndSelect();
			virtual bool MoveCaretLineDown();
			virtual bool MoveCaretWordStartAndSelect();
			virtual bool MoveCaretWordStart();
			virtual bool MoveCaretLeftAndSelect();
			virtual bool MoveCaretLeft();
			virtual bool MoveCaretWordEndAndSelect();
			virtual bool MoveCaretWordEnd();
			virtual bool MoveCaretRightAndSelect();
			virtual bool MoveCaretRight();
			virtual bool DeleteSelection();
			virtual bool DeleteLeft();
			virtual bool DeleteRight();
			virtual bool MoveCaretTextStartAndSelect();
			virtual bool MoveCaretTextStart();
			virtual bool MoveCaretLineStartAndSelect();
			virtual bool MoveCaretLineStart();
			virtual bool MoveCaretTextEndAndSelect();
			virtual bool MoveCaretTextEnd();
			virtual bool MoveCaretLineEndAndSelect();
			virtual bool MoveCaretLineEnd();
			virtual bool MoveCaretPageStartAndSelect();
			virtual bool MoveCaretPageStart();
			virtual bool MoveCaretPageUpAndSelect();
			virtual bool MoveCaretPageUp();
			virtual bool MoveCaretPageEndAndSelect();
			virtual bool MoveCaretPageEnd();
			virtual bool MoveCaretPageDownAndSelect();
			virtual bool MoveCaretPageDown();
			virtual bool SelectAll();
			virtual bool Paste();
			virtual bool Copy();
			virtual bool Cut();
			virtual bool ClearHistory();

			virtual void NotifyOnChange() = 0; // By timer
			virtual APP_RECT ClientToForm(APP_RECT rect) = 0;
			virtual CForm *getForm() = 0;
			virtual bool getEnabled() = 0;
			virtual bool getFocused() = 0;
			virtual IFont *getFont() = 0;
			virtual CStyle *getStyle() = 0;
			virtual String getClassName() = 0;
		public:
			CBaseText();
		};
	}
}