// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#include "Edit.h"
#include "..\..\..\Form.h"
#include "..\..\..\ImageManager.h"
#include "..\..\..\Presenter.h"

namespace licui
{
	namespace application
	{
#pragma region Constructors
		CEdit::CEdit() :CBaseBlock(),
			m_iScroll{ 0 },
			m_sSelection{ 0, 0 },
			m_bIsReplacing{ false },
			m_iMaxLength{ 0 },
			m_iCaretPosition{ 0 },
			m_bIsMouseDown{ false },
			m_bDeselectMovedSubstring{ true },
			m_bReadOnly{ false },
			m_pPopupMenu{ nullptr },
			m_fOnChange{ nullptr }
		{
			m_sClassName = L"CEdit";
			m_bAcceptFocus = true;
			m_bAcceptForm = true;
			m_bAcceptParent = true;
			m_bTabStop = true;
			m_sInitialRect = { 0, 0, 120, 20 };
			m_eCursor = ctIBeam;
			m_bSupportText = true;
			m_cHistory.setLimitCount(3);
			m_cHistory.Store({ m_sText, m_iCaretPosition, m_iScroll }, m_sText.length() * sizeof(wchar_t) + sizeof(size_t) * 2 + sizeof(m_sSelection));
			FillBlocks();
		}

		CEdit::CEdit(CControl *parent) :CEdit()
		{
			setParent(parent);
		}

		CEdit::CEdit(CForm *form) : CEdit()
		{
			setForm(form);
		}

		void CEdit::FillBlocks()
		{
			// Normal state
			m_sBlock[stNormal].BorderWidth[0] = 1;
			m_sBlock[stNormal].BorderWidth[1] = 1;
			m_sBlock[stNormal].BorderWidth[2] = 1;
			m_sBlock[stNormal].BorderWidth[3] = 1;
			m_sBlock[stNormal].BorderColor[0] = { 171, 173, 179, 255 };
			m_sBlock[stNormal].BorderColor[1] = { 171, 173, 179, 255 };
			m_sBlock[stNormal].BorderColor[2] = { 171, 173, 179, 255 };
			m_sBlock[stNormal].BorderColor[3] = { 171, 173, 179, 255 };
			m_sBlock[stNormal].Padding[0] = 2;
			m_sBlock[stNormal].Padding[1] = 0;
			m_sBlock[stNormal].Padding[2] = 2;
			m_sBlock[stNormal].Padding[3] = 0;
			m_sBlock[stNormal].CaptionHorizontalAlign = taLeft;
			m_sBlock[stNormal].CaptionVerticalAlign = vaMiddle;
			m_sBlock[stNormal].CaptionText = true;
			m_sBlock[stNormal].CaptionShadow = false;
			m_sBlock[stNormal].CaptionColorsOverwrite = true;
			m_sBlock[stNormal].CaptionTextColor = { 0, 0, 0, 255 };
			m_sBlock[stNormal].CaptionShadowColor = { 0, 0, 0, 255 };
			m_sBlock[stNormal].CaptionOrientationOverwrite = false;
			m_sBlock[stNormal].BackgroundColor = { 255, 255, 255, 255 };
			m_sBlock[stNormal].BackgroundRepeat[0] = true;
			m_sBlock[stNormal].BackgroundRepeat[1] = true;
			m_sBlock[stNormal].StyleName = L"";
			m_sBlock[stNormal].SelectionBackground = { 51, 153, 255, 200 };
			m_sBlock[stNormal].SelectionTextColor = { 255, 255, 255, 255 };
			m_sBlock[stNormal].SelectionShadowColor = { 255, 255, 255, 255 };
			// Normal hovered state
			m_sBlock[stNormalHovered].BorderWidth[0] = 1;
			m_sBlock[stNormalHovered].BorderWidth[1] = 1;
			m_sBlock[stNormalHovered].BorderWidth[2] = 1;
			m_sBlock[stNormalHovered].BorderWidth[3] = 1;
			m_sBlock[stNormalHovered].BorderColor[0] = { 126, 180, 234, 255 };
			m_sBlock[stNormalHovered].BorderColor[1] = { 126, 180, 234, 255 };
			m_sBlock[stNormalHovered].BorderColor[2] = { 126, 180, 234, 255 };
			m_sBlock[stNormalHovered].BorderColor[3] = { 126, 180, 234, 255 };
			m_sBlock[stNormalHovered].Padding[0] = 2;
			m_sBlock[stNormalHovered].Padding[1] = 0;
			m_sBlock[stNormalHovered].Padding[2] = 2;
			m_sBlock[stNormalHovered].Padding[3] = 0;
			m_sBlock[stNormalHovered].CaptionHorizontalAlign = taLeft;
			m_sBlock[stNormalHovered].CaptionVerticalAlign = vaMiddle;
			m_sBlock[stNormalHovered].CaptionText = true;
			m_sBlock[stNormalHovered].CaptionShadow = false;
			m_sBlock[stNormalHovered].CaptionColorsOverwrite = true;
			m_sBlock[stNormalHovered].CaptionTextColor = { 0, 0, 0, 255 };
			m_sBlock[stNormalHovered].CaptionShadowColor = { 0, 0, 0, 255 };
			m_sBlock[stNormalHovered].CaptionOrientationOverwrite = false;
			m_sBlock[stNormalHovered].BackgroundColor = { 255, 255, 255, 255 };
			m_sBlock[stNormalHovered].BackgroundRepeat[0] = true;
			m_sBlock[stNormalHovered].BackgroundRepeat[1] = true;
			m_sBlock[stNormalHovered].StyleName = L"";
			m_sBlock[stNormalHovered].SelectionBackground = { 51, 153, 255, 200 };
			m_sBlock[stNormalHovered].SelectionTextColor = { 255, 255, 255, 255 };
			m_sBlock[stNormalHovered].SelectionShadowColor = { 255, 255, 255, 255 };

			// Active state
			m_sBlock[stActive].BorderWidth[0] = 1;
			m_sBlock[stActive].BorderWidth[1] = 1;
			m_sBlock[stActive].BorderWidth[2] = 1;
			m_sBlock[stActive].BorderWidth[3] = 1;
			m_sBlock[stActive].BorderColor[0] = { 86, 157, 229, 255 };
			m_sBlock[stActive].BorderColor[1] = { 86, 157, 229, 255 };
			m_sBlock[stActive].BorderColor[2] = { 86, 157, 229, 255 };
			m_sBlock[stActive].BorderColor[3] = { 86, 157, 229, 255 };
			m_sBlock[stActive].Padding[0] = 2;
			m_sBlock[stActive].Padding[1] = 0;
			m_sBlock[stActive].Padding[2] = 2;
			m_sBlock[stActive].Padding[3] = 0;
			m_sBlock[stActive].CaptionHorizontalAlign = taLeft;
			m_sBlock[stActive].CaptionVerticalAlign = vaMiddle;
			m_sBlock[stActive].CaptionAntiAliazing = 2;
			m_sBlock[stActive].CaptionText = true;
			m_sBlock[stActive].CaptionShadow = false;
			m_sBlock[stActive].CaptionColorsOverwrite = true;
			m_sBlock[stActive].CaptionTextColor = { 0, 0, 0, 255 };
			m_sBlock[stActive].CaptionShadowColor = { 0, 0, 0, 255 };
			m_sBlock[stActive].CaptionOrientationOverwrite = false;
			m_sBlock[stActive].BackgroundColor = { 255, 255, 255, 255 };
			m_sBlock[stActive].BackgroundRepeat[0] = true;
			m_sBlock[stActive].BackgroundRepeat[1] = true;
			m_sBlock[stActive].StyleName = L"";
			m_sBlock[stActive].SelectionBackground = { 51, 153, 255, 255 };
			m_sBlock[stActive].SelectionTextColor = { 255, 255, 255, 255 };
			m_sBlock[stActive].SelectionShadowColor = { 255, 255, 255, 255 };
			// Active hovered state
			m_sBlock[stActiveHovered].BorderWidth[0] = 1;
			m_sBlock[stActiveHovered].BorderWidth[1] = 1;
			m_sBlock[stActiveHovered].BorderWidth[2] = 1;
			m_sBlock[stActiveHovered].BorderWidth[3] = 1;
			m_sBlock[stActiveHovered].BorderColor[0] = { 86, 157, 229, 255 };
			m_sBlock[stActiveHovered].BorderColor[1] = { 86, 157, 229, 255 };
			m_sBlock[stActiveHovered].BorderColor[2] = { 86, 157, 229, 255 };
			m_sBlock[stActiveHovered].BorderColor[3] = { 86, 157, 229, 255 };
			m_sBlock[stActiveHovered].Padding[0] = 2;
			m_sBlock[stActiveHovered].Padding[1] = 0;
			m_sBlock[stActiveHovered].Padding[2] = 2;
			m_sBlock[stActiveHovered].Padding[3] = 0;
			m_sBlock[stActiveHovered].CaptionHorizontalAlign = taLeft;
			m_sBlock[stActiveHovered].CaptionVerticalAlign = vaMiddle;
			m_sBlock[stActiveHovered].CaptionAntiAliazing = 2;
			m_sBlock[stActiveHovered].CaptionText = true;
			m_sBlock[stActiveHovered].CaptionShadow = false;
			m_sBlock[stActiveHovered].CaptionColorsOverwrite = true;
			m_sBlock[stActiveHovered].CaptionTextColor = { 0, 0, 0, 255 };
			m_sBlock[stActiveHovered].CaptionShadowColor = { 0, 0, 0, 255 };
			m_sBlock[stActiveHovered].CaptionOrientationOverwrite = false;
			m_sBlock[stActiveHovered].BackgroundColor = { 255, 255, 255, 255 };
			m_sBlock[stActiveHovered].BackgroundRepeat[0] = true;
			m_sBlock[stActiveHovered].BackgroundRepeat[1] = true;
			m_sBlock[stActiveHovered].StyleName = L"";
			m_sBlock[stActiveHovered].SelectionBackground = { 51, 153, 255, 255 };
			m_sBlock[stActiveHovered].SelectionTextColor = { 255, 255, 255, 255 };
			m_sBlock[stActiveHovered].SelectionShadowColor = { 255, 255, 255, 255 };

			// Disabled state
			m_sBlock[stDisabled].BorderAntiAliazing = 0;
			m_sBlock[stDisabled].BorderWidth[0] = 1;
			m_sBlock[stDisabled].BorderWidth[1] = 1;
			m_sBlock[stDisabled].BorderWidth[2] = 1;
			m_sBlock[stDisabled].BorderWidth[3] = 1;
			m_sBlock[stDisabled].BorderColor[0] = { 217, 217, 217, 255 };
			m_sBlock[stDisabled].BorderColor[1] = { 217, 217, 217, 255 };
			m_sBlock[stDisabled].BorderColor[2] = { 217, 217, 217, 255 };
			m_sBlock[stDisabled].BorderColor[3] = { 217, 217, 217, 255 };
			m_sBlock[stDisabled].Padding[0] = 2;
			m_sBlock[stDisabled].Padding[1] = 0;
			m_sBlock[stDisabled].Padding[2] = 2;
			m_sBlock[stDisabled].Padding[3] = 0;
			m_sBlock[stDisabled].CaptionHorizontalAlign = taLeft;
			m_sBlock[stDisabled].CaptionVerticalAlign = vaMiddle;
			m_sBlock[stDisabled].CaptionAntiAliazing = 2;
			m_sBlock[stDisabled].CaptionText = true;
			m_sBlock[stDisabled].CaptionShadow = false;
			m_sBlock[stDisabled].CaptionColorsOverwrite = true;
			m_sBlock[stDisabled].CaptionTextColor = { 109, 109, 109, 255 };
			m_sBlock[stDisabled].CaptionShadowColor = { 109, 109, 109, 255 };
			m_sBlock[stDisabled].CaptionOrientationOverwrite = false;
			m_sBlock[stDisabled].BackgroundColor = { 255, 255, 255, 255 };
			m_sBlock[stDisabled].BackgroundRepeat[0] = true;
			m_sBlock[stDisabled].BackgroundRepeat[1] = true;
			m_sBlock[stDisabled].StyleName = L"";
			m_sBlock[stDisabled].SelectionBackground = { 255, 255, 255, 255 };
			m_sBlock[stDisabled].SelectionTextColor = { 109, 109, 109, 255 };
			m_sBlock[stDisabled].SelectionShadowColor = { 109, 109, 109, 255 };
			// Disabled hovered state
			m_sBlock[stDisabledHovered].BorderWidth[0] = 1;
			m_sBlock[stDisabledHovered].BorderWidth[1] = 1;
			m_sBlock[stDisabledHovered].BorderWidth[2] = 1;
			m_sBlock[stDisabledHovered].BorderWidth[3] = 1;
			m_sBlock[stDisabledHovered].BorderColor[0] = { 217, 217, 217, 255 };
			m_sBlock[stDisabledHovered].BorderColor[1] = { 217, 217, 217, 255 };
			m_sBlock[stDisabledHovered].BorderColor[2] = { 217, 217, 217, 255 };
			m_sBlock[stDisabledHovered].BorderColor[3] = { 217, 217, 217, 255 };
			m_sBlock[stDisabledHovered].Padding[0] = 2;
			m_sBlock[stDisabledHovered].Padding[1] = 0;
			m_sBlock[stDisabledHovered].Padding[2] = 2;
			m_sBlock[stDisabledHovered].Padding[3] = 0;
			m_sBlock[stDisabledHovered].CaptionHorizontalAlign = taLeft;
			m_sBlock[stDisabledHovered].CaptionVerticalAlign = vaMiddle;
			m_sBlock[stDisabledHovered].CaptionAntiAliazing = 2;
			m_sBlock[stDisabledHovered].CaptionText = true;
			m_sBlock[stDisabledHovered].CaptionShadow = false;
			m_sBlock[stDisabledHovered].CaptionColorsOverwrite = true;
			m_sBlock[stDisabledHovered].CaptionTextColor = { 109, 109, 109, 255 };
			m_sBlock[stDisabledHovered].CaptionShadowColor = { 109, 109, 109, 255 };
			m_sBlock[stDisabledHovered].CaptionOrientationOverwrite = false;
			m_sBlock[stDisabledHovered].BackgroundColor = { 255, 255, 255, 255 };
			m_sBlock[stDisabledHovered].BackgroundRepeat[0] = true;
			m_sBlock[stDisabledHovered].BackgroundRepeat[1] = true;
			m_sBlock[stDisabledHovered].StyleName = L"";
			m_sBlock[stDisabledHovered].SelectionBackground = { 255, 255, 255, 255 };
			m_sBlock[stDisabledHovered].SelectionTextColor = { 109, 109, 109, 255 };
			m_sBlock[stDisabledHovered].SelectionShadowColor = { 109, 109, 109, 255 };
		}
#pragma endregion

#pragma region Helpers
		CEdit *CEdit::Select(int start, int end)
		{
			return setSelection({ start, end });
		}

		CEdit *CEdit::SelectAll()
		{
			return setSelection({ 0, (int)m_sText.length() });
		}

		CEdit *CEdit::DeselectAll()
		{
			return setSelection({ 0, -1 });
		}

		CEdit *CEdit::Clear()
		{
			return setText(L"");
		}

		void CEdit::CalculateTextPosition(APP_POINT &pos, APP_POINT &char_size)
		{
			char_size = getFont()->getStringSize(L"W");
			APP_POINT text_size = getFont()->getStringSize(m_sText);
			// Calc text drawing position in local coordinates
			pos.Y = ((int)m_sBlock[stNormal].BorderWidth[1] + (int)m_sBlock[stNormal].Padding[1] + getRect().Height() - (int)m_sBlock[stNormal].BorderWidth[3] - (int)m_sBlock[stNormal].Padding[3] - char_size.Y) / 2;
			pos.X = (int)m_sBlock[stNormal].BorderWidth[0] + (int)m_sBlock[stNormal].Padding[0];
			switch (m_sBlock[stNormal].CaptionHorizontalAlign)
			{
			case taRight:
				pos.X = getRect().Width() - (int)m_sBlock[stNormal].BorderWidth[2] - (int)m_sBlock[stNormal].Padding[2] - text_size.X;
				break;
			case taCenter:
				pos.X = ((int)m_sBlock[stNormal].BorderWidth[0] + (int)m_sBlock[stNormal].Padding[0] + getRect().Width() - (int)m_sBlock[stNormal].BorderWidth[2] - (int)m_sBlock[stNormal].Padding[2] - text_size.X) / 2;
				break;
			}
			pos.X += m_iScroll;
		}

		bool CEdit::CalculateCaretPosition(const APP_POINT &text_pos, const APP_RECT &text_rect, APP_POINT &pos)
		{
			pos = text_pos;
			// Find where cursor is
			IFont::GLYPH *glyph;
			for (size_t index = 0; index < m_iCaretPosition; index++)
			{
				if (!(glyph = getFont()->getChar(m_sText[index])))
					continue;
				pos.X += glyph->Width + getFont()->getDistance();
			}
			pos.Y = std::min(text_pos.Y, text_rect.Bottom - getRect().Top);
			return !text_rect.IsEmpty() && pos.X >= text_rect.Left - getRect().Left && pos.X < text_rect.Right - getRect().Left;
		}

		bool CEdit::CalculateSelectionRectangle(APP_RECT &rect, int &shift)
		{
			if (m_sSelection.X == m_sSelection.Y || m_sText.empty())
				return false;
			int x1{ std::min(m_sSelection.X, m_sSelection.Y) }, x2{ std::max(m_sSelection.X, m_sSelection.Y) };
			APP_POINT text_pos, char_size;
			CalculateTextPosition(text_pos, char_size);
			rect.Left = text_pos.X;
			rect.Top = text_pos.Y;
			rect.Bottom = rect.Top + char_size.Y + 1;
			shift = rect.Left;
			IFont::GLYPH *g;
			IFont *font = getFont();
			for (int i = 0; i < x1; i++)
				if (g = font->getChar(m_sText[i]))
					rect.Left += g->Width + font->getDistance();
			shift = rect.Left - shift;
			rect.Right = rect.Left;
			for (int i = x1; i < x2; i++)
				if (g = font->getChar(m_sText[i]))
					if (i == x2 - 1 && !std::isspace(m_sText[i], std::locale()))
						rect.Right += g->Image.getWidth();
					else
						rect.Right += g->Width + font->getDistance();
			rect.Right++;
			return true;
		}

		CEdit *CEdit::UpdateCaret()
		{
			if (!m_pForm)
				return this;
			if (m_pForm->getActiveControl() != this)
				return this;
			if (m_iCaretPosition > m_sText.length())
				m_iCaretPosition = m_sText.length();
			if (!getVisibleWithParents() || !getEnabledWithParents())
			{
				m_pForm->getWindow()->HideCaret();
				return this;
			}
			// Test text part rectangle
			APP_RECT text_rect = FormToClient(ClientToForm(getClientRect()) * getVisibleRect());
			if (text_rect.IsEmpty())
			{
				m_pForm->getWindow()->HideCaret();
				return this;
			}
			APP_POINT text_pos, char_size, caret_pos;
			CalculateTextPosition(text_pos, char_size);
			if (CalculateCaretPosition(text_pos, text_rect, caret_pos))
			{
				// Update caret sizes
				APP_POINT sym_size, caret_size;
				if (m_iCaretPosition >= m_sText.length() || !std::isgraph(m_sText[m_iCaretPosition], std::locale()))
					sym_size = getFont()->getStringSize(L" ");
				else
					sym_size = getFont()->getStringSize(m_sText.substr(m_iCaretPosition, 1));
				if (m_bIsReplacing)
					caret_size = { std::min(sym_size.X, text_rect.Width()), std::min(char_size.Y, text_rect.Height()) };
				else
					caret_size = { 1, std::min(char_size.Y, text_rect.Height()) };
				m_pForm->getWindow()->CreateCaret(caret_size.X, caret_size.Y);
				// Update caret visibility and position
				caret_pos = ClientToForm(APP_POINT{ caret_pos.X + getRect().Left, caret_pos.Y + getRect().Top });
				m_pForm->getWindow()->SetCaretPosition(caret_pos.X, caret_pos.Y);
				m_pForm->getWindow()->ShowCaret();
			}
			else
				m_pForm->getWindow()->HideCaret();
			return this;
		}

		CEdit *CEdit::UpdateScroll()
		{
			APP_RECT text_rect = getClientRect();
			if (text_rect.IsEmpty())
				return this;
			APP_POINT text_pos, char_size, caret_pos;
			CalculateTextPosition(text_pos, char_size);
			if (!CalculateCaretPosition(text_pos, text_rect, caret_pos))
			{
				if (caret_pos.X < text_rect.Left - getRect().Left)
					m_iScroll += (text_rect.Left - getRect().Left) - caret_pos.X;
				else
					m_iScroll -= caret_pos.X - (text_rect.Right - getRect().Left) + 1;
				for (int i = 0; i <= stDisabledHovered; i++)
					m_sBlock[i].CaptionShift[0] = m_iScroll;
			}
			return this;
		}

		size_t CEdit::CursorToCaret(const int x)
		{
			if (m_sText.length() == 0)
				return 0;
			APP_POINT text_pos, char_size;
			CalculateTextPosition(text_pos, char_size);
			if (x < text_pos.X)
				return 0;
			IFont::GLYPH *g;
			IFont *font{ getFont() };
			for (size_t index = 0; index < m_sText.length(); index++)
				if (g = font->getChar(m_sText[index]))
				{
					if (x <= text_pos.X + (int)g->Width / 2)
						return index;
					text_pos.X += g->Width + font->getDistance();
				}
			return m_sText.length();
		}

		bool CEdit::CanUndo()
		{
			return !m_bReadOnly && m_cHistory.getPosition() > 0;
		}

		bool CEdit::CanRedo()
		{
			return !m_bReadOnly && m_cHistory.getCount() > 0 && m_cHistory.getPosition() < m_cHistory.getCount() - 1;
		}

		CEdit *CEdit::Undo()
		{
			if (!m_bReadOnly && m_cHistory.getPosition() > 0)
			{
				HISTORY h = m_cHistory.getItem(m_cHistory.getPosition() - 1);
				m_sText = h.Text;
				m_iCaretPosition = h.CaretPosition;
				m_iScroll = h.Scroll;
				m_cHistory.setPosition(m_cHistory.getPosition() - 1);
				m_sSelection = { 0, 0 };
				UpdateScroll();
				UpdateCaret();
				if (m_pForm)
					m_pForm->LockRepaint();
				NotifyOnChange();
				Repaint(false);
				if (m_pForm)
					m_pForm->UnlockRepaint();
			}
			return this;
		}

		CEdit *CEdit::Redo()
		{
			if (!m_bReadOnly && m_cHistory.getPosition() < m_cHistory.getCount() - 1)
			{
				HISTORY h = m_cHistory.getItem(m_cHistory.getPosition() + 1);
				m_sText = h.Text;
				m_iCaretPosition = h.CaretPosition;
				m_iScroll = h.Scroll;
				m_cHistory.setPosition(m_cHistory.getPosition() + 1);
				m_sSelection = { 0, 0 };
				UpdateScroll();
				UpdateCaret();
				if (m_pForm)
					m_pForm->LockRepaint();
				NotifyOnChange();
				Repaint(false);
				if (m_pForm)
					m_pForm->UnlockRepaint();
			}
			return this;
		}

		bool CEdit::Copy()
		{
			if (m_sSelection.X != m_sSelection.Y)
				return m_pForm->getWindow()->CopyStringToClipboard(m_sText.substr(std::min(m_sSelection.X, m_sSelection.Y), std::max(m_sSelection.X, m_sSelection.Y) - std::min(m_sSelection.X, m_sSelection.Y)));
			return true;
		}

		bool CEdit::Cut()
		{
			if (m_sSelection.X != m_sSelection.Y)
			{
				m_iCaretPosition = std::min(m_sSelection.X, m_sSelection.Y);
				bool result{ m_pForm->getWindow()->CopyStringToClipboard(m_sText.substr(m_iCaretPosition, std::max(m_sSelection.X, m_sSelection.Y) - m_iCaretPosition)) };
				if (!m_bReadOnly)
				{
					m_sText.erase(m_iCaretPosition, std::abs(m_sSelection.Y - m_sSelection.X));
					m_sSelection = { 0, 0 };
					m_cHistory.Store({ m_sText, m_iCaretPosition, m_iScroll }, m_sText.length() * sizeof(wchar_t) + sizeof(size_t) * 2 + sizeof(m_sSelection));
					UpdateScroll();
					UpdateCaret();
					if (m_pForm)
						m_pForm->LockRepaint();
					NotifyOnChange();
					Repaint(false);
					if (m_pForm)
						m_pForm->UnlockRepaint();
				}
				return result;
			}
			return true;
		}

		CEdit *CEdit::Paste()
		{
			if (!m_bReadOnly)
			{
				String s = m_pForm->getWindow()->CopyStringFromClipboard();
				size_t i{ 0 };
				while (i < s.length())
					if (!std::isprint(s[i], std::locale()))
						s.erase(i, 1);
					else
						i++;
				if (s.length() > 0)
				{
					if (m_sSelection.X != m_sSelection.Y)
					{
						m_iCaretPosition = std::min(m_sSelection.X, m_sSelection.Y);
						m_sText.erase(m_iCaretPosition, std::abs(m_sSelection.Y - m_sSelection.X));
						m_sSelection = { 0, 0 };
					}
					m_sText.insert(m_iCaretPosition, s);
					m_iCaretPosition += s.length();
					if (m_iMaxLength > 0 && m_sText.length() > m_iMaxLength)
					{
						m_sText.erase(m_iMaxLength);
						if (m_iCaretPosition > m_sText.length())
							m_iCaretPosition = m_sText.length();
					}
					m_cHistory.Store({ m_sText, m_iCaretPosition, m_iScroll }, m_sText.length() * sizeof(wchar_t) + sizeof(size_t) * 2 + sizeof(m_sSelection));
					UpdateScroll();
					UpdateCaret();
					if (m_pForm)
						m_pForm->LockRepaint();
					NotifyOnChange();
					Repaint(false);
					if (m_pForm)
						m_pForm->UnlockRepaint();
				}
			}
			return this;
		}

		CEdit *CEdit::ClearHistory()
		{
			m_cHistory.Clear();
			return this;
		}

		void CEdit::RenderSelection(APP_RECT clip)
		{
			APP_RECT selection;
			int shift;
			if (CalculateSelectionRectangle(selection, shift))
			{
				clip *= getVisibleRect();
				STATE state{ getState() };
				// Render selection background
				APP_RECT client_rect = getClientRect();
				client_rect.Left -= getRect().Left;
				client_rect.Top -= getRect().Top;
				client_rect.Right -= getRect().Left;
				client_rect.Bottom -= getRect().Top;
				selection *= client_rect;
				DoRenderRect(m_sBlock[state].SelectionBackground, selection, clip);
				// Render selected text
				String s = m_sText.substr(std::min(m_sSelection.X, m_sSelection.Y), std::max(m_sSelection.X, m_sSelection.Y) - std::min(m_sSelection.X, m_sSelection.Y));
				APP_COLOR save_text_color{ m_sBlock[state].CaptionTextColor }, save_shadow_color{ m_sBlock[state].CaptionShadowColor };
				double save_shift{ m_sBlock[state].CaptionShift[0] };
				m_sBlock[state].CaptionShift[0] += shift;
				m_sBlock[state].CaptionTextColor = m_sBlock[state].SelectionTextColor;
				m_sBlock[state].CaptionShadowColor = m_sBlock[state].SelectionShadowColor;
				DoRenderCaption(s, clip);
				m_sBlock[state].CaptionShift[0] = save_shift;
				m_sBlock[state].CaptionTextColor = save_text_color;
				m_sBlock[state].CaptionShadowColor = save_shadow_color;
			}
		}
#pragma endregion

#pragma region Process special keys
		void CEdit::ProcessKeyLeft()
		{
			if (m_pForm->getWindow()->getKeyIsDown(IWindow::keyShift))
			{
				if (m_pForm->getWindow()->getKeyIsDown(IWindow::keyControl))
				{
					if (m_iCaretPosition > 0)
					{
						if (m_sSelection.Y == m_sSelection.X)
							m_sSelection.X = m_iCaretPosition;
						m_iCaretPosition = SearchPrevWord(m_sText, m_iCaretPosition, false);
						m_sSelection.Y = m_iCaretPosition;
						UpdateScroll();
						UpdateCaret();
						Repaint(false);
					}
				}
				else
				{
					if (m_iCaretPosition > 0)
					{
						if (m_sSelection.Y == m_sSelection.X)
							m_sSelection.X = m_iCaretPosition;
						m_iCaretPosition--;
						m_sSelection.Y = m_iCaretPosition;
						UpdateScroll();
						UpdateCaret();
						Repaint(false);
					}
				}
			}
			else
			{
				if (m_pForm->getWindow()->getKeyIsDown(IWindow::keyControl))
				{
					if (m_iCaretPosition > 0)
					{
						m_sSelection = { 0, 0 };
						m_iCaretPosition = SearchPrevWord(m_sText, m_iCaretPosition, false);
						UpdateScroll();
						UpdateCaret();
						Repaint(false);
					}
					else if (m_sSelection.X != m_sSelection.Y)
					{
						m_sSelection = { 0, 0 };
						Repaint(false);
					}
				}
				else
				{
					if (m_iCaretPosition > 0)
					{
						m_sSelection = { 0, 0 };
						m_iCaretPosition--;
						UpdateScroll();
						UpdateCaret();
						Repaint(false);
					}
					else if (m_sSelection.X != m_sSelection.Y)
					{
						m_sSelection = { 0, 0 };
						Repaint(false);
					}
				}
			}
		}

		void CEdit::ProcessKeyRight()
		{
			if (m_pForm->getWindow()->getKeyIsDown(IWindow::keyShift))
			{
				if (m_pForm->getWindow()->getKeyIsDown(IWindow::keyControl))
				{
					if (m_iCaretPosition < m_sText.length())
					{
						if (m_sSelection.Y == m_sSelection.X)
							m_sSelection.X = m_iCaretPosition;
						m_iCaretPosition = SearchNextWord(m_sText, m_iCaretPosition, false);
						m_sSelection.Y = m_iCaretPosition;
						UpdateScroll();
						UpdateCaret();
						Repaint(false);
					}
				}
				else
				{
					if (m_iCaretPosition < m_sText.length())
					{
						if (m_sSelection.Y == m_sSelection.X)
							m_sSelection.X = m_iCaretPosition;
						m_iCaretPosition++;
						m_sSelection.Y = m_iCaretPosition;
						UpdateScroll();
						UpdateCaret();
						Repaint(false);
					}
				}
			}
			else
			{
				if (m_pForm->getWindow()->getKeyIsDown(IWindow::keyControl))
				{
					if (m_iCaretPosition < m_sText.length())
					{
						m_sSelection = { 0, 0 };
						m_iCaretPosition = SearchNextWord(m_sText, m_iCaretPosition, false);
						UpdateScroll();
						UpdateCaret();
						Repaint(false);
					}
					else if (m_sSelection.X != m_sSelection.Y)
					{
						m_sSelection = { 0, 0 };
						Repaint(false);
					}
				}
				else
				{
					if (m_iCaretPosition < m_sText.length())
					{
						m_sSelection = { 0, 0 };
						m_iCaretPosition++;
						UpdateScroll();
						UpdateCaret();
						Repaint(false);
					}
					else if (m_sSelection.X != m_sSelection.Y)
					{
						m_sSelection = { 0, 0 };
						Repaint(false);
					}
				}
			}
		}

		void CEdit::ProcessKeyHome()
		{
			if (m_pForm->getWindow()->getKeyIsDown(IWindow::keyShift))
			{
				if (m_iCaretPosition > 0)
				{
					if (m_sSelection.Y == m_sSelection.X)
						m_sSelection.X = m_iCaretPosition;
					m_iCaretPosition = 0;
					m_sSelection.Y = m_iCaretPosition;
					UpdateScroll();
					UpdateCaret();
					Repaint(false);
				}
			}
			else
			{
				if (m_iCaretPosition > 0)
				{
					m_sSelection = { 0, 0 };
					m_iCaretPosition = 0;
					UpdateScroll();
					UpdateCaret();
					Repaint(false);
				}
				else if (m_sSelection.X != m_sSelection.Y)
				{
					m_sSelection = { 0, 0 };
					Repaint(false);
				}
			}
		}

		void CEdit::ProcessKeyEnd()
		{
			if (m_pForm->getWindow()->getKeyIsDown(IWindow::keyShift))
			{
				if (m_iCaretPosition < m_sText.length())
				{
					if (m_sSelection.Y == m_sSelection.X)
						m_sSelection.X = m_iCaretPosition;
					m_iCaretPosition = m_sText.length();
					m_sSelection.Y = m_iCaretPosition;
					UpdateScroll();
					UpdateCaret();
					Repaint(false);
				}
			}
			else
			{
				if (m_iCaretPosition < m_sText.length())
				{
					m_sSelection = { 0, 0 };
					m_iCaretPosition = m_sText.length();
					UpdateScroll();
					UpdateCaret();
					Repaint(false);
				}
				else if (m_sSelection.X != m_sSelection.Y)
				{
					m_sSelection = { 0, 0 };
					Repaint(false);
				}
			}
		}

		void CEdit::ProcessKeyDelete()
		{
			if (m_bReadOnly)
				return;
			if (m_pForm->getWindow()->getKeyIsDown(IWindow::keyControl))
			{
				if (m_sSelection.X != m_sSelection.Y)
				{
					m_iCaretPosition = std::min(m_sSelection.X, m_sSelection.Y);
					m_sText.erase(m_iCaretPosition);
					m_sSelection = { 0, 0 };
					m_cHistory.Store({ m_sText, m_iCaretPosition, m_iScroll }, m_sText.length() * sizeof(wchar_t) + sizeof(size_t) * 2 + sizeof(m_sSelection));
					UpdateScroll();
					UpdateCaret();
					NotifyOnChange();
					Repaint(false);
				}
				else if (m_iCaretPosition < m_sText.length())
				{
					m_sText.erase(m_iCaretPosition);
					m_cHistory.Store({ m_sText, m_iCaretPosition, m_iScroll }, m_sText.length() * sizeof(wchar_t) + sizeof(size_t) * 2 + sizeof(m_sSelection));
					UpdateScroll();
					UpdateCaret();
					NotifyOnChange();
					Repaint(false);
				}
			}
			else
			{
				if (m_sSelection.X != m_sSelection.Y)
				{
					m_iCaretPosition = std::min(m_sSelection.X, m_sSelection.Y);
					m_sText.erase(m_iCaretPosition, std::max(m_sSelection.X, m_sSelection.Y) - m_iCaretPosition);
					m_sSelection = { 0, 0 };
					m_cHistory.Store({ m_sText, m_iCaretPosition, m_iScroll }, m_sText.length() * sizeof(wchar_t) + sizeof(size_t) * 2 + sizeof(m_sSelection));
					UpdateScroll();
					UpdateCaret();
					NotifyOnChange();
					Repaint(false);
				}
				else if (m_iCaretPosition < m_sText.length())
				{
					m_sText.erase(m_iCaretPosition, 1);
					m_cHistory.Store({ m_sText, m_iCaretPosition, m_iScroll }, m_sText.length() * sizeof(wchar_t) + sizeof(size_t) * 2 + sizeof(m_sSelection));
					UpdateScroll();
					UpdateCaret();
					NotifyOnChange();
					Repaint(false);
				}
			}
		}

		void CEdit::ProcessKeyBack()
		{
			if (m_bReadOnly)
				return;
			if (m_pForm->getWindow()->getKeyIsDown(IWindow::keyControl))
			{
				if (m_sSelection.X != m_sSelection.Y)
				{
					m_iCaretPosition = 0;
					m_sText.erase(0, std::max(m_sSelection.X, m_sSelection.Y));
					m_sSelection = { 0, 0 };
					m_cHistory.Store({ m_sText, m_iCaretPosition, m_iScroll }, m_sText.length() * sizeof(wchar_t) + sizeof(size_t) * 2 + sizeof(m_sSelection));
					UpdateScroll();
					UpdateCaret();
					NotifyOnChange();
					Repaint(false);
				}
				else if (m_iCaretPosition > 0)
				{
					m_sText.erase(0, m_iCaretPosition);
					m_cHistory.Store({ m_sText, m_iCaretPosition, m_iScroll }, m_sText.length() * sizeof(wchar_t) + sizeof(size_t) * 2 + sizeof(m_sSelection));
					m_iCaretPosition = 0;
					UpdateScroll();
					UpdateCaret();
					NotifyOnChange();
					Repaint(false);
				}
			}
			else
			{
				if (m_sSelection.X != m_sSelection.Y)
				{
					m_iCaretPosition = std::min(m_sSelection.X, m_sSelection.Y);
					m_sText.erase(m_iCaretPosition, std::max(m_sSelection.X, m_sSelection.Y) - m_iCaretPosition);
					m_sSelection = { 0, 0 };
					m_cHistory.Store({ m_sText, m_iCaretPosition, m_iScroll }, m_sText.length() * sizeof(wchar_t) + sizeof(size_t) * 2 + sizeof(m_sSelection));
					UpdateScroll();
					UpdateCaret();
					NotifyOnChange();
					Repaint(false);
				}
				else if (m_iCaretPosition > 0)
				{
					m_sText.erase(m_iCaretPosition - 1, 1);
					m_iCaretPosition--;
					m_cHistory.Store({ m_sText, m_iCaretPosition, m_iScroll }, m_sText.length() * sizeof(wchar_t) + sizeof(size_t) * 2 + sizeof(m_sSelection));
					UpdateScroll();
					UpdateCaret();
					NotifyOnChange();
					Repaint(false);
				}
			}
		}

		void CEdit::ProcessKeyInsert()
		{
			if (!m_bReadOnly)
			{
				m_bIsReplacing = !m_bIsReplacing;
				UpdateCaret();
			}
		}

		void CEdit::ProcessMouseDown(const int x, const int y, const bool shift)
		{
			APP_POINT cursor_pos = FormToClient(x, y);
			APP_RECT r = getClientRect();
			if (cursor_pos.X >= r.Left && cursor_pos.X < r.Right && cursor_pos.Y >= r.Top && cursor_pos.Y < r.Bottom)
			{
				cursor_pos.X -= getRect().Left;
				cursor_pos.Y -= getRect().Top;
				size_t new_caret{ CursorToCaret(cursor_pos.X) };
				m_iMouseDownCaretPosition = new_caret;
				m_bIsMouseDown = true;
				m_bIsMoveSelection = (m_sSelection.X != m_sSelection.Y) && new_caret >= (size_t)std::min(m_sSelection.X, m_sSelection.Y) && new_caret < (size_t)std::max(m_sSelection.X, m_sSelection.Y);
				m_pForm->CaptureMouse(this);
				if (m_bIsMoveSelection)
				{
					if (new_caret != m_iCaretPosition)
					{
						m_iCaretPosition = new_caret;
						UpdateCaret();
						Repaint(false);
					}
				}
				else
				{
					if (new_caret != m_iCaretPosition || m_sSelection.X != m_sSelection.Y)
					{
						if (shift)
							if (m_sSelection.X == m_sSelection.Y)
								m_sSelection = { (int)m_iCaretPosition, (int)new_caret };
							else
								m_sSelection.Y = new_caret;
						else
							m_sSelection = { 0, 0 };
						m_iCaretPosition = new_caret;
						UpdateCaret();
						Repaint(false);
					}
				}
			}
		}

		void CEdit::ProcessMouseMove(const int x, const int y)
		{
			APP_POINT cursor_pos = FormToClient(x, y);
			APP_RECT client_rect = getClientRect();
			size_t new_caret{ CursorToCaret(cursor_pos.X - getRect().Left) };
			if (cursor_pos.X >= client_rect.Left && cursor_pos.X < client_rect.Right && cursor_pos.Y >= client_rect.Top && cursor_pos.Y < client_rect.Bottom)
			{
				if (m_bIsMoveSelection)
				{
					if (new_caret != m_iCaretPosition)
					{
						m_iCaretPosition = new_caret;
						UpdateCaret();
						Repaint(false);
					}
				}
				else
				{
					if (new_caret != m_iCaretPosition)
					{
						if (m_sSelection.X == m_sSelection.Y)
							m_sSelection.X = m_iCaretPosition;
						m_iCaretPosition = new_caret;
						m_sSelection.Y = m_iCaretPosition;
						UpdateCaret();
						Repaint(false);
					}
				}
			}
			else
			{
				if (new_caret != m_iCaretPosition)
				{
					if (new_caret > m_iCaretPosition)
						new_caret = m_iCaretPosition + 1;
					else
						new_caret = m_iCaretPosition - 1;
					if (!m_bIsMoveSelection)
					{
						if (m_sSelection.X == m_sSelection.Y)
							m_sSelection.X = m_iCaretPosition;
						m_sSelection.Y = new_caret;
					}
					m_iCaretPosition = new_caret;
					UpdateScroll();
					UpdateCaret();
					Repaint(false);
				}
			}
		}

		void CEdit::ProcessMouseUp(const bool ctrl)
		{
			if (m_pForm->getCaptureMouseControl() == this)
				m_pForm->ReleaseCaptureMouse();
			else
				m_bIsMouseDown = false;
			if (!m_bReadOnly && m_bIsMoveSelection)
			{
				if (m_iMouseDownCaretPosition != m_iCaretPosition)
				{
					int x1{ std::min(m_sSelection.X, m_sSelection.Y) }, x2{ std::max(m_sSelection.X, m_sSelection.Y) };
					if ((int)m_iCaretPosition < x1 || (int)m_iCaretPosition > x2)
					{
						if (ctrl)
						{
							String s = m_sText.substr(x1, x2 - x1);
							m_sText.insert(m_iCaretPosition, s);
							if (m_bDeselectMovedSubstring)
								m_sSelection = { 0, 0 };
							else
								m_sSelection = { (int)m_iCaretPosition, (int)m_iCaretPosition + x2 - x1 };
							m_iCaretPosition += x2 - x1;
							if (m_iMaxLength > 0 && m_sText.length() > m_iMaxLength)
							{
								m_sText.erase(m_iMaxLength);
								if (m_iCaretPosition > m_sText.length())
									m_iCaretPosition = m_sText.length();
							}
							UpdateScroll();
						}
						else
						{
							String s = m_sText.substr(x1, x2 - x1);
							m_sText.erase(x1, x2 - x1);
							if ((int)m_iCaretPosition >= x1)
								m_iCaretPosition -= x2 - x1;
							m_sText.insert((int)m_iCaretPosition, s);
							m_iCaretPosition += x2 - x1;
							if (m_bDeselectMovedSubstring)
								m_sSelection = { 0, 0 };
							else
								m_sSelection = { (int)m_iCaretPosition - (x2 - x1), (int)m_iCaretPosition };
						}
						m_cHistory.Store({ m_sText, m_iCaretPosition, m_iScroll }, m_sText.length() * sizeof(wchar_t) + sizeof(size_t) * 2 + sizeof(m_sSelection));
						UpdateCaret();
						NotifyOnChange();
						Repaint(false);
					}
				}
				else
				{
					m_sSelection = { 0, 0 };
					Repaint(false);
				}
			}
		}

		void CEdit::ProcessMouseDoubleClick()
		{
			if (m_iCaretPosition < m_sText.length() && std::isalnum(m_sText[m_iCaretPosition], std::locale()))
			{
				m_sSelection.X = m_iCaretPosition;
				while (m_sSelection.X > 0 && std::isalnum(m_sText[m_sSelection.X - 1], std::locale()))
					m_sSelection.X--;
				m_sSelection.Y = m_iCaretPosition + 1;
				while (m_sSelection.Y < (int)m_sText.length() && std::isalnum(m_sText[m_sSelection.Y], std::locale()))
					m_sSelection.Y++;
				UpdateScroll();
				UpdateCaret();
				Repaint(false);
			}
		}
#pragma endregion

#pragma region Notifications
		void CEdit::NotifyOnChangeUseParentFont()
		{
			CBaseBlock::NotifyOnChangeUseParentFont();
			UpdateCaret();
		}

		void CEdit::NotifyOnParentFontChangeSize()
		{
			CBaseBlock::NotifyOnParentFontChangeSize();
			UpdateCaret();
		}

		void CEdit::NotifyOnFontChangeSize()
		{
			CBaseBlock::NotifyOnFontChangeSize();
			UpdateCaret();
		}

		void CEdit::NotifyOnMouseHover()
		{
			Repaint(false);
			CControl::NotifyOnMouseHover();
		}

		void CEdit::NotifyOnMouseLeave()
		{
			Repaint(false);
			CControl::NotifyOnMouseHover();
		}

		void CEdit::NotifyOnKillFocus()
		{
			m_pForm->getWindow()->HideCaret();
			Repaint(false);
			CControl::NotifyOnKillFocus();
		}

		void CEdit::NotifyOnSetFocus(CControl *old)
		{
			UpdateCaret();
			Repaint(false);
			CControl::NotifyOnSetFocus(old);
		}

		void CEdit::NotifyOnResetFocus()
		{
			UpdateCaret();
			Repaint(false);
			CControl::NotifyOnResetFocus();
		}

		bool CEdit::NotifyOnKeyDown(const IWindow::KEY key)
		{
			bool ctrl, shift, alt;
			switch (key)
			{
			case IWindow::keyLeft:
			case IWindow::keyNumpad4:
				if (key == IWindow::keyLeft || (key == IWindow::keyNumpad4 && !m_pForm->getWindow()->getKeyIsToggled(IWindow::keyNumLock)))
					ProcessKeyLeft();
				break;
			case IWindow::keyRight:
			case IWindow::keyNumpad6:
				if (key == IWindow::keyRight || (key == IWindow::keyNumpad6 && !m_pForm->getWindow()->getKeyIsToggled(IWindow::keyNumLock)))
					ProcessKeyRight();
				break;
			case IWindow::keyHome:
			case IWindow::keyNumpad7:
				if (key == IWindow::keyHome || (key == IWindow::keyNumpad7 && !m_pForm->getWindow()->getKeyIsToggled(IWindow::keyNumLock)))
					ProcessKeyHome();
				break;
			case IWindow::keyEnd:
			case IWindow::keyNumpad1:
				if (key == IWindow::keyEnd || (key == IWindow::keyNumpad1 && !m_pForm->getWindow()->getKeyIsToggled(IWindow::keyNumLock)))
					ProcessKeyEnd();
				break;
			case IWindow::keyDelete:
			case IWindow::keyDecimal:
				if (key == IWindow::keyDelete || (key == IWindow::keyDecimal && !m_pForm->getWindow()->getKeyIsToggled(IWindow::keyNumLock)))
					ProcessKeyDelete();
				break;
			case IWindow::keyBack:
				ProcessKeyBack();
				break;
			case IWindow::keyA:
				m_pForm->getWindow()->getControlKeys(ctrl, shift, alt);
				if (ctrl && !shift && !alt)
					SelectAll();
				break;
			case IWindow::keyV:
				m_pForm->getWindow()->getControlKeys(ctrl, shift, alt);
				if (ctrl && !shift && !alt)
					Paste();
				break;
			case IWindow::keyC:
				m_pForm->getWindow()->getControlKeys(ctrl, shift, alt);
				if (ctrl && !shift && !alt)
					Copy();
				break;
			case IWindow::keyX:
				m_pForm->getWindow()->getControlKeys(ctrl, shift, alt);
				if (ctrl && !shift && !alt)
					Cut();
				break;
			case IWindow::keyZ:
				m_pForm->getWindow()->getControlKeys(ctrl, shift, alt);
				if (ctrl && !alt)
					shift ? Redo() : Undo();
				break;
			}
			return CBaseBlock::NotifyOnKeyDown(key);
		}

		bool CEdit::NotifyOnKeyUp(const IWindow::KEY key)
		{
			if (key == IWindow::keyInsert)
				ProcessKeyInsert();
			return CBaseBlock::NotifyOnKeyUp(key);
		}

		bool CEdit::NotifyOnChar(const wchar_t chr)
		{
			bool ctrl, shift, alt;
			m_pForm->getWindow()->getControlKeys(ctrl, shift, alt);
			if (!m_bReadOnly && !alt && !ctrl && std::isprint(chr, std::locale()))
			{
				if (m_iCaretPosition < m_sText.length())
				{
					bool was_selected{ false };
					if (m_sSelection.X != m_sSelection.Y)
					{
						m_iCaretPosition = std::min(m_sSelection.X, m_sSelection.Y);
						m_sText.erase(m_iCaretPosition, std::max(m_sSelection.X, m_sSelection.Y) - m_iCaretPosition);
						m_sSelection = { 0, 0 };
						was_selected = true;
					}
					String s;
					s += chr;
					if (m_bIsReplacing && !was_selected)
						m_sText[m_iCaretPosition] = chr;
					else
						m_sText.insert(m_iCaretPosition, s);
				}
				else
					m_sText += chr;
				m_iCaretPosition++;
				if (m_iMaxLength > 0 && m_sText.length() > m_iMaxLength)
				{
					m_sText.erase(m_iMaxLength);
					if (m_iCaretPosition > m_sText.length())
						m_iCaretPosition = m_sText.length();
				}
				m_cHistory.Store({ m_sText, m_iCaretPosition, m_iScroll }, m_sText.length() * sizeof(wchar_t) + sizeof(size_t) * 2 + sizeof(m_sSelection));
				UpdateScroll();
				UpdateCaret();
				NotifyOnChange();
				Repaint(false);
			}
			return CBaseBlock::NotifyOnChar(chr);
		}

		void CEdit::NotifyOnSetCaptureMouse()
		{
			m_pForm->getWindow()->CaptureMouse();
			CBaseBlock::NotifyOnSetCaptureMouse();
		}

		void CEdit::NotifyOnKillCaptureMouse()
		{
			m_bIsMouseDown = false;
			m_pForm->getWindow()->ReleaseMouseCapture();
			CBaseBlock::NotifyOnKillCaptureMouse();
		}

		bool CEdit::NotifyOnMouseMove(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			if (m_bIsMouseDown)
				ProcessMouseMove(x, y);
			CBaseBlock::NotifyOnMouseMove(x, y, ctrl, left, middle, right, shift);
			return true;
		}

		bool CEdit::NotifyOnLeftMouseButtonDown(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			if (!middle && !right)
				ProcessMouseDown(x, y, shift);
			CBaseBlock::NotifyOnLeftMouseButtonDown(x, y, ctrl, left, middle, right, shift);
			return true;
		}

		bool CEdit::NotifyOnLeftMouseButtonUp(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			if (m_bIsMouseDown)
				ProcessMouseUp(ctrl);
			CBaseBlock::NotifyOnLeftMouseButtonUp(x, y, ctrl, left, middle, right, shift);
			return true;
		}

		bool CEdit::NotifyOnLeftMouseButtonDoubleClick(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			ProcessMouseDoubleClick();
			CBaseBlock::NotifyOnLeftMouseButtonDoubleClick(x, y, ctrl, left, middle, right, shift);
			return true;
		}

		bool CEdit::NotifyOnRightMouseButtonDown(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			CBaseBlock::NotifyOnRightMouseButtonDown(x, y, ctrl, left, middle, right, shift);
			return true;
		}

		bool CEdit::NotifyOnRightMouseButtonUp(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			if (m_pPopupMenu)
				m_pPopupMenu->Show(x, y);
			CBaseBlock::NotifyOnRightMouseButtonUp(x, y, ctrl, left, middle, right, shift);
			return true;
		}

		bool CEdit::NotifyOnRightMouseButtonDoubleClick(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			CBaseBlock::NotifyOnRightMouseButtonDoubleClick(x, y, ctrl, left, middle, right, shift);
			return true;
		}

		bool CEdit::NotifyOnMiddleMouseButtonDown(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			CBaseBlock::NotifyOnMiddleMouseButtonDown(x, y, ctrl, left, middle, right, shift);
			return true;
		}

		bool CEdit::NotifyOnMiddleMouseButtonUp(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			CBaseBlock::NotifyOnMiddleMouseButtonUp(x, y, ctrl, left, middle, right, shift);
			return true;
		}

		bool CEdit::NotifyOnMiddleMouseButtonDoubleClick(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			CBaseBlock::NotifyOnMiddleMouseButtonDoubleClick(x, y, ctrl, left, middle, right, shift);
			return true;
		}

		bool CEdit::NotifyOnMouseVerticalWheel(const int x, const int y, const int delta, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			CBaseBlock::NotifyOnMouseVerticalWheel(x, y, delta, ctrl, left, middle, right, shift);
			return true;
		}

		bool CEdit::NotifyOnMouseHorizontalWheel(const int x, const int y, const int delta, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			CBaseBlock::NotifyOnMouseHorizontalWheel(x, y, delta, ctrl, left, middle, right, shift);
			return true;
		}

		void CEdit::NotifyOnParentResize()
		{
			CBaseBlock::NotifyOnParentResize();
			UpdateCaret();
		}

		void CEdit::NotifyOnParentMove()
		{
			CBaseBlock::NotifyOnParentMove();
			UpdateCaret();
		}

		void CEdit::NotifyOnResize(const APP_POINT &old_size, const APP_POINT &new_size)
		{
			CBaseBlock::NotifyOnResize(old_size, new_size);
			UpdateCaret();
		}

		void CEdit::NotifyOnMove(const APP_POINT &old_position, const APP_POINT &new_position)
		{
			CBaseBlock::NotifyOnMove(old_position, new_position);
			UpdateCaret();
		}

		void CEdit::NotifyOnPaint(APP_RECT clip)
		{
			if (getVisibleWithParents())
			{
				DoRender(m_sText, clip);
				RenderSelection(clip);
			}
			CBaseBlock::NotifyOnPaint(clip);
		}

		void CEdit::NotifyOnChange()
		{
			if (m_fOnChange)
				m_fOnChange(this, getCallbackParam());
		}
#pragma endregion

#pragma region Getters
		CBaseBlock::BLOCK *CEdit::getBlock()
		{
			return &m_sBlock[getState()];
		}

		CURSOR_TYPE CEdit::getCursor() const
		{
			if (!getEnabledWithParents())
				return ctArrow;
			return CBaseBlock::getCursor();
		}

		CEdit::STATE CEdit::getState()
		{
			if (m_pForm)
			{
				if (!m_bEnabled)
				{
					if (m_pForm->getHoveredControl() == this)
						return stDisabledHovered;
					return stDisabled;
				}
				if (m_pForm->getActiveControl() == this)
				{
					if (m_pForm->getHoveredControl() == this)
						return stActiveHovered;
					return stActive;
				}
				if (m_pForm->getHoveredControl() == this)
					return stNormalHovered;
				return stNormal;
			}
			if (!m_bEnabled)
				return stDisabled;
			return stNormal;
		}

		String CEdit::getText() const
		{
			return m_sText;
		}

		int CEdit::getScroll() const
		{
			return m_iScroll;
		}

		APP_POINT CEdit::getSelection() const
		{
			return m_sSelection;
		}

		int CEdit::getSelectionStart() const
		{
			return m_sSelection.X;
		}

		int CEdit::getSelectionEnd() const
		{
			return m_sSelection.Y;
		}

		bool CEdit::getIsReplacing() const
		{
			return m_bIsReplacing;
		}

		size_t CEdit::getMaxLength() const
		{
			return m_iMaxLength;
		}

		size_t CEdit::getCaretPosition() const
		{
			return m_iCaretPosition;
		}

		bool CEdit::getDeselectMovedSubstring() const
		{
			return m_bDeselectMovedSubstring;
		}

		size_t CEdit::getHistoryLimitCount() const
		{
			return m_cHistory.getLimitCount();
		}

		size_t CEdit::getHistoryLimitSize() const
		{
			return m_cHistory.getLimitSize();
		}

		bool CEdit::getReadOnly() const
		{
			return m_bReadOnly;
		}

		CPopupMenu *CEdit::getPopupMenu()
		{
			return m_pPopupMenu;
		}

		CEdit::FOnChange CEdit::getOnChange() const
		{
			return m_fOnChange;
		}
#pragma endregion

#pragma region Setters
		CEdit *CEdit::setText(String value)
		{
			size_t i{ 0 };
			while (i < value.length())
				if (!std::isprint(value[i], std::locale()))
					value.erase(i, 1);
				else
					i++;
			if (value != m_sText)
			{
				m_sText = value;
				if (m_iCaretPosition > m_sText.length())
					m_iCaretPosition = m_sText.length();
				m_cHistory.Store({ m_sText, m_iCaretPosition, m_iScroll }, m_sText.length() * sizeof(wchar_t) + sizeof(size_t) * 2 + sizeof(m_sSelection));
				UpdateScroll();
				UpdateCaret();
				if (m_pForm)
					m_pForm->LockRepaint();
				NotifyOnChange();
				Repaint(false);
				if (m_pForm)
					m_pForm->UnlockRepaint();
			}
			return this;
		}

		CEdit *CEdit::setScroll(int value)
		{
			if (value != m_iScroll)
			{
				m_iScroll = value;
				for (int i = 0; i <= stDisabledHovered; i++)
					m_sBlock[i].CaptionShift[0] = m_iScroll;
				UpdateCaret();
				Repaint(false);
			}
			return this;
		}

		CEdit *CEdit::setSelection(APP_POINT value)
		{
			if (value.X > (int)m_sText.length())
				value.X = m_sText.length();
			if (value.Y > (int)m_sText.length())
				value.Y = m_sText.length();
			if (value != m_sSelection)
			{
				m_sSelection = value;
				Repaint(false);
			}
			return this;
		}

		CEdit *CEdit::setSelectionStart(size_t value)
		{
			if (value > m_sText.length())
				value = m_sText.length();
			if (value != m_sSelection.X)
			{
				m_sSelection.X = value;
				Repaint(false);
			}
			return this;
		}

		CEdit *CEdit::setSelectionEnd(size_t value)
		{
			if (value > m_sText.length())
				value = m_sText.length();
			if (value != m_sSelection.Y)
			{
				m_sSelection.Y = value;
				Repaint(false);
			}
			return this;
		}

		CEdit *CEdit::setMaxLength(const size_t value)
		{
			m_iMaxLength = value;
			return this;
		}

		CEdit *CEdit::setCaretPosition(size_t value)
		{
			if (value > m_sText.length())
				if (m_sText.length() > 0)
					value = m_sText.length();
				else
					value = 0;
			if (value != m_iCaretPosition)
			{
				m_iCaretPosition = value;
				UpdateScroll();
				UpdateCaret();
				Repaint(false);
			}
			return this;
		}

		CEdit *CEdit::setDeselectMovedSubstring(const bool value)
		{
			m_bDeselectMovedSubstring = value;
			return this;
		}

		CEdit *CEdit::setHistoryLimitCount(const size_t value)
		{
			m_cHistory.setLimitCount(value);
			return this;
		}

		CEdit *CEdit::setHistoryLimitSize(const size_t value)
		{
			m_cHistory.setLimitSize(value);
			return this;
		}

		CEdit *CEdit::setReadOnly(const bool value)
		{
			m_bReadOnly = value;
			return this;
		}

		CEdit *CEdit::setPopupMenu(CPopupMenu *value)
		{
			if (value != m_pPopupMenu)
			{
				if (m_pPopupMenu && m_pPopupMenu->getVisible())
					m_pPopupMenu->Hide();
				m_pPopupMenu = value;
				if (m_pPopupMenu)
					m_pPopupMenu->Hide();
			}
			return this;
		}

		CEdit *CEdit::setOnChange(FOnChange value)
		{
			m_fOnChange = value;
			return this;
		}
#pragma endregion

#pragma region Block getters
		size_t CEdit::getBorderAntiAliazing(const STATE state)
		{
			return m_sBlock[state].BorderAntiAliazing;
		}

		APP_RECT CEdit::getBorderWidth()
		{
			STATE state{ getState() };
			return{ (int)m_sBlock[state].BorderWidth[0], (int)m_sBlock[state].BorderWidth[1], (int)m_sBlock[state].BorderWidth[2], (int)m_sBlock[state].BorderWidth[3] };
		}

		size_t CEdit::getLeftBorderWidth()
		{
			return m_sBlock[getState()].BorderWidth[0];
		}

		size_t CEdit::getTopBorderWidth()
		{
			return m_sBlock[getState()].BorderWidth[1];
		}

		size_t CEdit::getRightBorderWidth()
		{
			return m_sBlock[getState()].BorderWidth[2];
		}

		size_t CEdit::getBottomBorderWidth()
		{
			return m_sBlock[getState()].BorderWidth[3];
		}

		APP_RECT CEdit::getBorderRadius()
		{
			STATE state{ getState() };
			return{ (int)m_sBlock[state].BorderRadius[0], (int)m_sBlock[state].BorderRadius[1], (int)m_sBlock[state].BorderRadius[2], (int)m_sBlock[state].BorderRadius[3] };
		}

		size_t CEdit::getLeftTopRadius()
		{
			return m_sBlock[getState()].BorderRadius[0];
		}

		size_t CEdit::getRightTopRadius()
		{
			return m_sBlock[getState()].BorderRadius[1];
		}

		size_t CEdit::getRightBottomRadius()
		{
			return m_sBlock[getState()].BorderRadius[2];
		}

		size_t CEdit::getLeftBottomRadius()
		{
			return m_sBlock[getState()].BorderRadius[3];
		}

		APP_COLOR CEdit::getLeftBorderColor(const STATE state)
		{
			return m_sBlock[state].BorderColor[0];
		}

		APP_COLOR CEdit::getTopBorderColor(const STATE state)
		{
			return m_sBlock[state].BorderColor[1];
		}

		APP_COLOR CEdit::getRightBorderColor(const STATE state)
		{
			return m_sBlock[state].BorderColor[2];
		}

		APP_COLOR CEdit::getBottomBorderColor(const STATE state)
		{
			return m_sBlock[state].BorderColor[3];
		}

		APP_IMAGE *CEdit::getLeftBorderImage(const STATE state)
		{
			if (m_pForm)
				m_pForm->getImageManager()->FreeImage(&m_sBlock[state].BorderImage[0]);
			return &m_sBlock[state].BorderImage[0];
		}

		APP_IMAGE *CEdit::getTopBorderImage(const STATE state)
		{
			if (m_pForm)
				m_pForm->getImageManager()->FreeImage(&m_sBlock[state].BorderImage[1]);
			return &m_sBlock[state].BorderImage[1];
		}

		APP_IMAGE *CEdit::getRightBorderImage(const STATE state)
		{
			if (m_pForm)
				m_pForm->getImageManager()->FreeImage(&m_sBlock[state].BorderImage[2]);
			return &m_sBlock[state].BorderImage[2];
		}

		APP_IMAGE *CEdit::getBottomBorderImage(const STATE state)
		{
			if (m_pForm)
				m_pForm->getImageManager()->FreeImage(&m_sBlock[state].BorderImage[3]);
			return &m_sBlock[state].BorderImage[3];
		}

		bool CEdit::getLeftBorderInterpolate(const STATE state)
		{
			return m_sBlock[state].BorderInterpolate[0];
		}

		bool CEdit::getTopBorderInterpolate(const STATE state)
		{
			return m_sBlock[state].BorderInterpolate[1];
		}

		bool CEdit::getRightBorderInterpolate(const STATE state)
		{
			return m_sBlock[state].BorderInterpolate[2];
		}

		bool CEdit::getBottomBorderInterpolate(const STATE state)
		{
			return m_sBlock[state].BorderInterpolate[3];
		}

		APP_RECT CEdit::getPadding()
		{
			STATE state{ getState() };
			return{ (int)m_sBlock[state].Padding[0], (int)m_sBlock[state].Padding[1], (int)m_sBlock[state].Padding[2], (int)m_sBlock[state].Padding[3] };
		}

		size_t CEdit::getPaddingLeft()
		{
			return m_sBlock[getState()].Padding[0];
		}

		size_t CEdit::getPaddingTop()
		{
			return m_sBlock[getState()].Padding[1];
		}

		size_t CEdit::getPaddingRight()
		{
			return m_sBlock[getState()].Padding[2];
		}

		size_t CEdit::getPaddingBottom()
		{
			return m_sBlock[getState()].Padding[3];
		}

		TEXT_ALIGN CEdit::getCaptionHorizontalAlign()
		{
			return m_sBlock[getState()].CaptionHorizontalAlign;
		}

		bool CEdit::getCaptionText()
		{
			return m_sBlock[getState()].CaptionText;
		}

		bool CEdit::getCaptionShadow()
		{
			return m_sBlock[getState()].CaptionShadow;
		}

		APP_COLOR CEdit::getCaptionTextColor(const STATE state)
		{
			return m_sBlock[state].CaptionTextColor;
		}

		APP_COLOR CEdit::getCaptionShadowColor(const STATE state)
		{
			return m_sBlock[state].CaptionShadowColor;
		}

		size_t CEdit::getCaptionAntiAliazing(const STATE state)
		{
			return m_sBlock[state].CaptionAntiAliazing;
		}

		math::POINT<double> CEdit::getCaptionScale()
		{
			STATE state{ getState() };
			return{ m_sBlock[state].CaptionScale[0], m_sBlock[state].CaptionScale[1] };
		}

		double CEdit::getCaptionScaleX()
		{
			return m_sBlock[getState()].CaptionScale[0];
		}

		double CEdit::getCaptionScaleY()
		{
			return m_sBlock[getState()].CaptionScale[1];
		}

		APP_COLOR CEdit::getBackgrondColor(const STATE state)
		{
			return m_sBlock[state].BackgroundColor;
		}

		APP_IMAGE *CEdit::getBackgroundImage(const STATE state)
		{
			if (m_pForm)
				m_pForm->getImageManager()->FreeImage(&m_sBlock[state].BackgroundImage);
			return &m_sBlock[state].BackgroundImage;
		}

		bool CEdit::getBackgroundRepeatX(const STATE state)
		{
			return m_sBlock[state].BackgroundRepeat[0];
		}

		bool CEdit::getBackgroundRepeatY(const STATE state)
		{
			return m_sBlock[state].BackgroundRepeat[1];
		}

		APP_POINT CEdit::getBackgroundPosition(const STATE state)
		{
			return{ m_sBlock[state].BackgroundPosition[0], m_sBlock[state].BackgroundPosition[1] };
		}

		int CEdit::getBackgroundPositionX(const STATE state)
		{
			return m_sBlock[state].BackgroundPosition[0];
		}

		int CEdit::getBackgroundPositionY(const STATE state)
		{
			return m_sBlock[state].BackgroundPosition[1];
		}

		bool CEdit::getBackgroundPositionPercentageX(const STATE state)
		{
			return m_sBlock[state].BackgroundPositionPercentage[0];
		}

		bool CEdit::getBackgroundPositionPercentageY(const STATE state)
		{
			return m_sBlock[state].BackgroundPositionPercentage[1];
		}

		APP_POINT CEdit::getBackgroundSize(const STATE state)
		{
			return{ m_sBlock[state].BackgroundSize[0], m_sBlock[state].BackgroundSize[1] };
		}

		int CEdit::getBackgroundSizeX(const STATE state)
		{
			return m_sBlock[state].BackgroundSize[0];
		}

		int CEdit::getBackgroundSizeY(const STATE state)
		{
			return m_sBlock[state].BackgroundSize[1];
		}

		bool CEdit::getBackgroundInterpolate(const STATE state)
		{
			return m_sBlock[state].BackgroundInterpolate;
		}

		double CEdit::getBackgroundRotation(const STATE state)
		{
			return m_sBlock[state].BackgroundRotation;
		}

		APP_COLOR CEdit::getSelectionBackground(const STATE state)
		{
			return m_sBlock[state].SelectionBackground;
		}

		APP_COLOR CEdit::getSelectionTextColor(const STATE state)
		{
			return m_sBlock[state].SelectionTextColor;
		}

		APP_COLOR CEdit::getSelectionShadowColor(const STATE state)
		{
			return m_sBlock[state].SelectionShadowColor;
		}

		bool CEdit::getBoxShadow(const STATE state)
		{
			return m_sBlock[state].BoxShadow;
		}

		APP_COLOR CEdit::getBoxShadowColor(const STATE state)
		{
			return m_sBlock[state].BoxShadowColor;
		}

		APP_POINT CEdit::getBoxShadowShift(const STATE state)
		{
			return m_sBlock[state].BoxShadowShift;
		}

		size_t CEdit::getBoxShadowRadius(const STATE state)
		{
			return m_sBlock[state].BoxShadowRadius;
		}
#pragma endregion

#pragma region Block setters
		CEdit *CEdit::setBorderAntiAliazing(const STATE state, size_t value)
		{
			if (value != m_sBlock[state].BorderAntiAliazing)
			{
				m_sBlock[state].BorderAntiAliazing = value;
				if (getState() == state && (m_sBlock[state].BorderRadius[0] > 0 || m_sBlock[state].BorderRadius[1] > 0 || m_sBlock[state].BorderRadius[2] > 0 || m_sBlock[state].BorderRadius[3] > 0))
					Repaint(false);
			}
			return this;
		}

		CEdit *CEdit::setBorderWidth(const size_t value)
		{
			if (value != m_sBlock[stNormal].BorderWidth[0] || value != m_sBlock[stNormal].BorderWidth[1] || value != m_sBlock[stNormal].BorderWidth[2] || value != m_sBlock[stNormal].BorderWidth[3])
			{
				for (int i = 0; i <= stDisabledHovered; i++)
				{
					m_sBlock[i].BorderWidth[0] = value;
					m_sBlock[i].BorderWidth[1] = value;
					m_sBlock[i].BorderWidth[2] = value;
					m_sBlock[i].BorderWidth[3] = value;
				}
				UpdateCaret();
				Repaint(false);
			}
			return this;
		}

		CEdit *CEdit::setBorderWidth(const size_t left, const size_t top, const size_t right, const size_t bottom)
		{
			if (left != m_sBlock[stNormal].BorderWidth[0] || top != m_sBlock[stNormal].BorderWidth[1] || right != m_sBlock[stNormal].BorderWidth[2] || bottom != m_sBlock[stNormal].BorderWidth[3])
			{
				for (int i = 0; i <= stDisabledHovered; i++)
				{
					m_sBlock[i].BorderWidth[0] = left;
					m_sBlock[i].BorderWidth[1] = top;
					m_sBlock[i].BorderWidth[2] = right;
					m_sBlock[i].BorderWidth[3] = bottom;
				}
				UpdateCaret();
				Repaint(false);
			}
			return this;
		}

		CEdit *CEdit::setLeftBorderWidth(const size_t value)
		{
			if (value != m_sBlock[stNormal].BorderWidth[0])
			{
				for (int i = 0; i <= stDisabledHovered; i++)
					m_sBlock[i].BorderWidth[0] = value;
				UpdateCaret();
				Repaint(false);
			}
			return this;
		}

		CEdit *CEdit::setTopBorderWidth(const size_t value)
		{
			if (value != m_sBlock[stNormal].BorderWidth[1])
			{
				for (int i = 0; i <= stDisabledHovered; i++)
					m_sBlock[i].BorderWidth[1] = value;
				UpdateCaret();
				Repaint(false);
			}
			return this;
		}

		CEdit *CEdit::setRightBorderWidth(const size_t value)
		{
			if (value != m_sBlock[stNormal].BorderWidth[2])
			{
				for (int i = 0; i <= stDisabledHovered; i++)
					m_sBlock[i].BorderWidth[2] = value;
				UpdateCaret();
				Repaint(false);
			}
			return this;
		}

		CEdit *CEdit::setBottomBorderWidth(const size_t value)
		{
			if (value != m_sBlock[stNormal].BorderWidth[3])
			{
				for (int i = 0; i <= stDisabledHovered; i++)
					m_sBlock[i].BorderWidth[3] = value;
				UpdateCaret();
				Repaint(false);
			}
			return this;
		}

		CEdit *CEdit::setBorderRadius(const size_t value)
		{
			if (value != m_sBlock[stNormal].BorderRadius[0] || value != m_sBlock[stNormal].BorderRadius[1] || value != m_sBlock[stNormal].BorderRadius[2] || value != m_sBlock[stNormal].BorderRadius[3])
			{
				for (int i = 0; i <= stDisabledHovered; i++)
				{
					m_sBlock[i].BorderRadius[0] = value;
					m_sBlock[i].BorderRadius[1] = value;
					m_sBlock[i].BorderRadius[2] = value;
					m_sBlock[i].BorderRadius[3] = value;
				}
				UpdateCaret();
				Repaint(false);
			}
			return this;
		}

		CEdit *CEdit::setBorderRadius(const size_t left_top, const size_t right_top, const size_t right_bottom, const size_t left_bottom)
		{
			if (left_top != m_sBlock[stNormal].BorderRadius[0] || right_top != m_sBlock[stNormal].BorderRadius[1] || right_bottom != m_sBlock[stNormal].BorderRadius[2] || left_bottom != m_sBlock[stNormal].BorderRadius[3])
			{
				for (int i = 0; i <= stDisabledHovered; i++)
				{
					m_sBlock[i].BorderRadius[0] = left_top;
					m_sBlock[i].BorderRadius[1] = right_top;
					m_sBlock[i].BorderRadius[2] = right_bottom;
					m_sBlock[i].BorderRadius[3] = left_bottom;
				}
				UpdateCaret();
				Repaint(false);
			}
			return this;
		}

		CEdit *CEdit::setLeftTopRadius(const size_t value)
		{
			if (value != m_sBlock[stNormal].BorderRadius[0])
			{
				for (int i = 0; i <= stDisabledHovered; i++)
					m_sBlock[i].BorderRadius[0] = value;
				UpdateCaret();
				Repaint(false);
			}
			return this;
		}

		CEdit *CEdit::setRightTopRadius(const size_t value)
		{
			if (value != m_sBlock[stNormal].BorderRadius[1])
			{
				for (int i = 0; i <= stDisabledHovered; i++)
					m_sBlock[i].BorderRadius[1] = value;
				UpdateCaret();
				Repaint(false);
			}
			return this;
		}

		CEdit *CEdit::setRightBottomRadius(const size_t value)
		{
			if (value != m_sBlock[stNormal].BorderRadius[2])
			{
				for (int i = 0; i <= stDisabledHovered; i++)
					m_sBlock[i].BorderRadius[2] = value;
				UpdateCaret();
				Repaint(false);
			}
			return this;
		}

		CEdit *CEdit::setLeftBottomRadius(const size_t value)
		{
			if (value != m_sBlock[stNormal].BorderRadius[3])
			{
				for (int i = 0; i <= stDisabledHovered; i++)
					m_sBlock[i].BorderRadius[3] = value;
				UpdateCaret();
				Repaint(false);
			}
			return this;
		}

		CEdit *CEdit::setBorderColor(const STATE state, const APP_COLOR &value)
		{
			if (value != m_sBlock[state].BorderColor[0] || value != m_sBlock[state].BorderColor[1] || value != m_sBlock[state].BorderColor[2] || value != m_sBlock[state].BorderColor[3])
			{
				m_sBlock[state].BorderColor[0] = value;
				m_sBlock[state].BorderColor[1] = value;
				m_sBlock[state].BorderColor[2] = value;
				m_sBlock[state].BorderColor[3] = value;
				if (state == getState() && (m_sBlock[state].BorderWidth[0] > 0 || m_sBlock[state].BorderWidth[1] > 0 || m_sBlock[state].BorderWidth[2] > 0 || m_sBlock[state].BorderWidth[3] > 0))
					Repaint(false);
			}
			return this;
		}

		CEdit *CEdit::setBorderColor(const STATE state, const APP_COLOR &left, const APP_COLOR &top, const APP_COLOR &right, const APP_COLOR &bottom)
		{
			if (left != m_sBlock[state].BorderColor[0] || top != m_sBlock[state].BorderColor[1] || right != m_sBlock[state].BorderColor[2] || bottom != m_sBlock[state].BorderColor[3])
			{
				m_sBlock[state].BorderColor[0] = left;
				m_sBlock[state].BorderColor[1] = top;
				m_sBlock[state].BorderColor[2] = right;
				m_sBlock[state].BorderColor[3] = bottom;
				if (state == getState() && (m_sBlock[state].BorderWidth[0] > 0 || m_sBlock[state].BorderWidth[1] > 0 || m_sBlock[state].BorderWidth[2] > 0 || m_sBlock[state].BorderWidth[3] > 0))
					Repaint(false);
			}
			return this;
		}

		CEdit *CEdit::setLeftBorderColor(const STATE state, const APP_COLOR &value)
		{
			if (value != m_sBlock[state].BorderColor[0])
			{
				m_sBlock[state].BorderColor[0] = value;
				if (state == getState() && m_sBlock[state].BorderWidth[0] > 0)
					Repaint(false);
			}
			return this;
		}

		CEdit *CEdit::setTopBorderColor(const STATE state, const APP_COLOR &value)
		{
			if (value != m_sBlock[state].BorderColor[1])
			{
				m_sBlock[state].BorderColor[1] = value;
				if (state == getState() && m_sBlock[state].BorderWidth[1] > 0)
					Repaint(false);
			}
			return this;
		}

		CEdit *CEdit::setRightBorderColor(const STATE state, const APP_COLOR &value)
		{
			if (value != m_sBlock[state].BorderColor[2])
			{
				m_sBlock[state].BorderColor[2] = value;
				if (state == getState() && m_sBlock[state].BorderWidth[2] > 0)
					Repaint(false);
			}
			return this;
		}

		CEdit *CEdit::setBottomBorderColor(const STATE state, const APP_COLOR &value)
		{
			if (value != m_sBlock[state].BorderColor[3])
			{
				m_sBlock[state].BorderColor[3] = value;
				if (state == getState() && m_sBlock[state].BorderWidth[3] > 0)
					Repaint(false);
			}
			return this;
		}

		CEdit *CEdit::setBorderInterpolate(const STATE state, const bool value)
		{
			if (value != m_sBlock[state].BorderInterpolate[0] || value != m_sBlock[state].BorderInterpolate[1] || value != m_sBlock[state].BorderInterpolate[2] || value != m_sBlock[state].BorderInterpolate[3])
			{
				m_sBlock[state].BorderInterpolate[0] = value;
				m_sBlock[state].BorderInterpolate[1] = value;
				m_sBlock[state].BorderInterpolate[2] = value;
				m_sBlock[state].BorderInterpolate[3] = value;
				if (state == getState() && (m_sBlock[state].BorderWidth[0] > 0 || m_sBlock[state].BorderWidth[1] > 0 || m_sBlock[state].BorderWidth[2] > 0 || m_sBlock[state].BorderWidth[3] > 0))
					Repaint(false);
			}
			return this;
		}

		CEdit *CEdit::setBorderInterpolate(const STATE state, const bool left, const bool top, const bool right, const bool bottom)
		{
			if (left != m_sBlock[state].BorderInterpolate[0] || top != m_sBlock[state].BorderInterpolate[1] || right != m_sBlock[state].BorderInterpolate[2] || bottom != m_sBlock[state].BorderInterpolate[3])
			{
				m_sBlock[state].BorderInterpolate[0] = left;
				m_sBlock[state].BorderInterpolate[1] = top;
				m_sBlock[state].BorderInterpolate[2] = right;
				m_sBlock[state].BorderInterpolate[3] = bottom;
				if (state == getState() && (m_sBlock[state].BorderWidth[0] > 0 || m_sBlock[state].BorderWidth[1] > 0 || m_sBlock[state].BorderWidth[2] > 0 || m_sBlock[state].BorderWidth[3] > 0))
					Repaint(false);
			}
			return this;
		}

		CEdit *CEdit::setLeftBorderInterpolate(const STATE state, const bool value)
		{
			if (value != m_sBlock[state].BorderInterpolate[0])
			{
				m_sBlock[state].BorderInterpolate[0] = value;
				if (state == getState() && m_sBlock[state].BorderWidth[0] > 0)
					Repaint(false);
			}
			return this;
		}

		CEdit *CEdit::setTopBorderInterpolate(const STATE state, const bool value)
		{
			if (value != m_sBlock[state].BorderInterpolate[1])
			{
				m_sBlock[state].BorderInterpolate[1] = value;
				if (state == getState() && m_sBlock[state].BorderWidth[1] > 0)
					Repaint(false);
			}
			return this;
		}

		CEdit *CEdit::setRightBorderInterpolate(const STATE state, const bool value)
		{
			if (value != m_sBlock[state].BorderInterpolate[2])
			{
				m_sBlock[state].BorderInterpolate[2] = value;
				if (state == getState() && m_sBlock[state].BorderWidth[2] > 0)
					Repaint(false);
			}
			return this;
		}

		CEdit *CEdit::setBottomBorderInterpolate(const STATE state, const bool value)
		{
			if (value != m_sBlock[state].BorderInterpolate[3])
			{
				m_sBlock[state].BorderInterpolate[3] = value;
				if (state == getState() && m_sBlock[state].BorderWidth[3] > 0)
					Repaint(false);
			}
			return this;
		}

		CEdit *CEdit::setPadding(const math::RECTANGLE<size_t> &value)
		{
			if (value != m_sBlock[stNormal].Padding)
			{
				for (int i = 0; i <= stDisabledHovered; i++)
					m_sBlock[i].Padding = value;
				UpdateCaret();
				Repaint(false);
			}
			return this;
		}

		CEdit *CEdit::setPadding(const size_t value)
		{
			if (value != m_sBlock[stNormal].Padding[0] || value != m_sBlock[stNormal].Padding[1] || value != m_sBlock[stNormal].Padding[2] || value != m_sBlock[stNormal].Padding[3])
			{
				for (int i = 0; i <= stDisabledHovered; i++)
				{
					m_sBlock[i].Padding[0] = value;
					m_sBlock[i].Padding[1] = value;
					m_sBlock[i].Padding[2] = value;
					m_sBlock[i].Padding[3] = value;
				}
				UpdateCaret();
				Repaint(false);
			}
			return this;
		}

		CEdit *CEdit::setPaddingLeft(const size_t value)
		{
			if (value != m_sBlock[stNormal].Padding[0])
			{
				for (int i = 0; i <= stDisabledHovered; i++)
					m_sBlock[i].Padding[0] = value;
				UpdateCaret();
				Repaint(false);
			}
			return this;
		}

		CEdit *CEdit::setPaddingTop(const size_t value)
		{
			if (value != m_sBlock[stNormal].Padding[1])
			{
				for (int i = 0; i <= stDisabledHovered; i++)
					m_sBlock[i].Padding[1] = value;
				UpdateCaret();
				Repaint(false);
			}
			return this;
		}

		CEdit *CEdit::setPaddingRight(const size_t value)
		{
			if (value != m_sBlock[stNormal].Padding[2])
			{
				for (int i = 0; i <= stDisabledHovered; i++)
					m_sBlock[i].Padding[2] = value;
				UpdateCaret();
				Repaint(false);
			}
			return this;
		}

		CEdit *CEdit::setPaddingBottom(const size_t value)
		{
			if (value != m_sBlock[stNormal].Padding[3])
			{
				for (int i = 0; i <= stDisabledHovered; i++)
					m_sBlock[i].Padding[3] = value;
				UpdateCaret();
				Repaint(false);
			}
			return this;
		}

		CEdit *CEdit::setCaptionText(const bool value)
		{
			if (value != m_sBlock[stNormal].CaptionText)
			{
				for (int i = 0; i <= stDisabledHovered; i++)
					m_sBlock[i].CaptionText = value;
				if (!m_sText.empty())
					Repaint(false);
			}
			return this;
		}

		CEdit *CEdit::setCaptionShadow(const bool value)
		{
			if (value != m_sBlock[stNormal].CaptionShadow)
			{
				for (int i = 0; i <= stDisabledHovered; i++)
					m_sBlock[i].CaptionShadow = value;
				if (!m_sText.empty())
					Repaint(false);
			}
			return this;
		}

		CEdit *CEdit::setCaptionTextColor(const STATE state, const APP_COLOR &value)
		{
			if (value != m_sBlock[state].CaptionTextColor)
			{
				m_sBlock[state].CaptionTextColor = value;
				if (state == getState() && !m_sText.empty())
					Repaint(false);
			}
			return this;
		}

		CEdit *CEdit::setCaptionShadowColor(const STATE state, const APP_COLOR &value)
		{
			if (value != m_sBlock[state].CaptionShadowColor)
			{
				m_sBlock[state].CaptionShadowColor = value;
				if (state == getState() && !m_sText.empty())
					Repaint(false);
			}
			return this;
		}

		CEdit *CEdit::setCaptionHorizontalAlign(const TEXT_ALIGN value)
		{
			if (value != m_sBlock[stNormal].CaptionHorizontalAlign)
			{
				for (int i = 0; i <= stDisabledHovered; i++)
					m_sBlock[i].CaptionHorizontalAlign = value;
				UpdateScroll();
				UpdateCaret();
				Repaint(false);
			}
			return this;
		}

		CEdit *CEdit::setCaptionAntiAliazing(const STATE state, size_t value)
		{
			if (value != m_sBlock[state].CaptionAntiAliazing)
			{
				m_sBlock[state].CaptionAntiAliazing = value;
				if (state == getState() && !m_sText.empty())
					Repaint(false);
			}
			return this;
		}

		CEdit *CEdit::setCaptionScale(const math::POINT<double> &value)
		{
			if (value.X != m_sBlock[stNormal].CaptionScale[0] || value.Y != m_sBlock[stNormal].CaptionScale[1])
			{
				for (int i = 0; i <= stDisabledHovered; i++)
				{
					m_sBlock[i].CaptionScale[0] = value.X;
					m_sBlock[i].CaptionScale[1] = value.Y;
				}
				UpdateScroll();
				UpdateCaret();
				Repaint(false);
			}
			return this;
		}

		CEdit *CEdit::setCaptionScaleX(const double value)
		{
			if (value != m_sBlock[stNormal].CaptionScale[0])
			{
				for (int i = 0; i <= stDisabledHovered; i++)
					m_sBlock[i].CaptionScale[0] = value;
				UpdateScroll();
				UpdateCaret();
				Repaint(false);
			}
			return this;
		}

		CEdit *CEdit::setCaptionScaleY(const double value)
		{
			if (value != m_sBlock[stNormal].CaptionScale[1])
			{
				for (int i = 0; i <= stDisabledHovered; i++)
					m_sBlock[i].CaptionScale[1] = value;
				UpdateScroll();
				UpdateCaret();
				Repaint(false);
			}
			return this;
		}

		CEdit *CEdit::setBackgroundColor(const STATE state, const APP_COLOR &value)
		{
			if (value != m_sBlock[state].BackgroundColor)
			{
				m_sBlock[state].BackgroundColor = value;
				if (state == getState())
					Repaint(false);
			}
			return this;
		}

		CEdit *CEdit::setBackgroundRepeat(const STATE state, const bool value)
		{
			if (value != m_sBlock[state].BackgroundRepeat[0] || value != m_sBlock[state].BackgroundRepeat[1])
			{
				m_sBlock[state].BackgroundRepeat[0] = value;
				m_sBlock[state].BackgroundRepeat[1] = value;
				if (state == getState())
					Repaint(false);
			}
			return this;
		}

		CEdit *CEdit::setBackgroundRepeat(const STATE state, const bool x, const bool y)
		{
			if (x != m_sBlock[state].BackgroundRepeat[0] || y != m_sBlock[state].BackgroundRepeat[1])
			{
				m_sBlock[state].BackgroundRepeat[0] = x;
				m_sBlock[state].BackgroundRepeat[1] = y;
				if (state == getState())
					Repaint(false);
			}
			return this;
		}

		CEdit *CEdit::setBackgroundRepeatX(const STATE state, const bool value)
		{
			if (value != m_sBlock[state].BackgroundRepeat[0])
			{
				m_sBlock[state].BackgroundRepeat[0] = value;
				if (state == getState())
					Repaint(false);
			}
			return this;
		}

		CEdit *CEdit::setBackgroundRepeatY(const STATE state, const bool value)
		{
			if (value != m_sBlock[state].BackgroundRepeat[1])
			{
				m_sBlock[state].BackgroundRepeat[1] = value;
				if (state == getState())
					Repaint(false);
			}
			return this;
		}

		CEdit *CEdit::setBackgroundPosition(const STATE state, const APP_POINT &value)
		{
			if (value.X != m_sBlock[state].BackgroundPosition[0] || value.Y != m_sBlock[state].BackgroundPosition[1])
			{
				m_sBlock[state].BackgroundPosition[0] = value.X;
				m_sBlock[state].BackgroundPosition[1] = value.Y;
				if (state == getState())
					Repaint(false);
			}
			return this;
		}

		CEdit *CEdit::setBackgroundPositionX(const STATE state, const int value)
		{
			if (value != m_sBlock[state].BackgroundPosition[0])
			{
				m_sBlock[state].BackgroundPosition[0] = value;
				if (state == getState())
					Repaint(false);
			}
			return this;
		}

		CEdit *CEdit::setBackgroundPositionY(const STATE state, const int value)
		{
			if (value != m_sBlock[state].BackgroundPosition[1])
			{
				m_sBlock[state].BackgroundPosition[1] = value;
				if (state == getState())
					Repaint(false);
			}
			return this;
		}

		CEdit *CEdit::setBackgroundPositionPercentage(const STATE state, const bool value)
		{
			if (value != m_sBlock[state].BackgroundPositionPercentage[0] || value != m_sBlock[state].BackgroundPositionPercentage[1])
			{
				m_sBlock[state].BackgroundPositionPercentage[0] = value;
				m_sBlock[state].BackgroundPositionPercentage[1] = value;
				if (state == getState())
					Repaint(false);
			}
			return this;
		}

		CEdit *CEdit::setBackgroundPositionPercentage(const STATE state, const bool x, const bool y)
		{
			if (x != m_sBlock[state].BackgroundPositionPercentage[0] || y != m_sBlock[state].BackgroundPositionPercentage[1])
			{
				m_sBlock[state].BackgroundPositionPercentage[0] = x;
				m_sBlock[state].BackgroundPositionPercentage[1] = y;
				if (state == getState())
					Repaint(false);
			}
			return this;
		}

		CEdit *CEdit::setBackgroundPositionPercentageX(const STATE state, const bool value)
		{
			if (value != m_sBlock[state].BackgroundPositionPercentage[0])
			{
				m_sBlock[state].BackgroundPositionPercentage[0] = value;
				if (state == getState())
					Repaint(false);
			}
			return this;
		}

		CEdit *CEdit::setBackgroundPositionPercentageY(const STATE state, const bool value)
		{
			if (value != m_sBlock[state].BackgroundPositionPercentage[1])
			{
				m_sBlock[state].BackgroundPositionPercentage[1] = value;
				if (state == getState())
					Repaint(false);
			}
			return this;
		}

		CEdit *CEdit::setBackgroundSize(const STATE state, const APP_POINT &value)
		{
			if (value.X != m_sBlock[state].BackgroundSize[0] || value.Y != m_sBlock[state].BackgroundSize[1])
			{
				m_sBlock[state].BackgroundSize[0] = value.X;
				m_sBlock[state].BackgroundSize[1] = value.Y;
				if (state != getState())
					Repaint(false);
			}
			return this;
		}

		CEdit *CEdit::setBackgroundSizeX(const STATE state, const int value)
		{
			if (value != m_sBlock[state].BackgroundSize[0])
			{
				m_sBlock[state].BackgroundSize[0] = value;
				if (state != getState())
					Repaint(false);
			}
			return this;
		}

		CEdit *CEdit::setBackgroundSizeY(const STATE state, const int value)
		{
			if (value != m_sBlock[state].BackgroundSize[1])
			{
				m_sBlock[state].BackgroundSize[1] = value;
				if (state != getState())
					Repaint(false);
			}
			return this;
		}

		CEdit *CEdit::setBackgroundInterpolate(const STATE state, const bool value)
		{
			if (value != m_sBlock[state].BackgroundInterpolate)
			{
				m_sBlock[state].BackgroundInterpolate = value;
				if (state != getState())
					Repaint(false);
			}
			return this;
		}

		CEdit *CEdit::setBackgroundRotation(const STATE state, const double value)
		{
			if (value != m_sBlock[state].BackgroundRotation)
			{
				m_sBlock[state].BackgroundRotation = value;
				if (state != getState())
					Repaint(false);
			}
			return this;
		}

		CEdit *CEdit::setSelectionBackground(const STATE state, const APP_COLOR &value)
		{
			if (value != m_sBlock[state].SelectionBackground)
			{
				m_sBlock[state].SelectionBackground = value;
				if (state == getState() && m_sSelection.X != m_sSelection.Y)
					Repaint(false);
			}
			return this;
		}

		CEdit *CEdit::setSelectionTextColor(const STATE state, const APP_COLOR &value)
		{
			if (value != m_sBlock[state].SelectionTextColor)
			{
				m_sBlock[state].SelectionTextColor = value;
				if (state == getState() && m_sSelection.X != m_sSelection.Y)
					Repaint(false);
			}
			return this;
		}

		CEdit *CEdit::setSelectionShadowColor(const STATE state, const APP_COLOR &value)
		{
			if (value != m_sBlock[state].SelectionShadowColor)
			{
				m_sBlock[state].SelectionShadowColor = value;
				if (state == getState() && m_sSelection.X != m_sSelection.Y)
					Repaint(false);
			}
			return this;
		}

		CEdit *CEdit::setBoxShadow(const STATE state, const bool value)
		{
			if (value != m_sBlock[state].BoxShadow)
			{
				if (m_pForm)
					m_pForm->LockRepaint();
				if (state == getState())
					Repaint(false);
				m_sBlock[state].BoxShadow = value;
				if (state == getState())
					Repaint(false);
				if (m_pForm)
					m_pForm->UnlockRepaint();
			}
			return this;
		}

		CEdit *CEdit::setBoxShadowColor(const STATE state, const APP_COLOR &value)
		{
			if (value != m_sBlock[state].BoxShadowColor)
			{
				if (m_pForm)
					m_pForm->LockRepaint();
				if (state == getState() && m_sBlock[state].BoxShadow)
					Repaint(false);
				m_sBlock[state].BoxShadowColor = value;
				if (state == getState() && m_sBlock[state].BoxShadow)
					Repaint(false);
				if (m_pForm)
					m_pForm->UnlockRepaint();
			}
			return this;
		}

		CEdit *CEdit::setBoxShadowShift(const STATE state, const APP_POINT &value)
		{
			if (value != m_sBlock[state].BoxShadowShift)
			{
				if (m_pForm)
					m_pForm->LockRepaint();
				if (state == getState() && m_sBlock[state].BoxShadow && m_sBlock[state].BoxShadowColor.getAlpha() > 0)
					Repaint(false);
				m_sBlock[state].BoxShadowShift = value;
				if (state == getState() && m_sBlock[state].BoxShadow && m_sBlock[state].BoxShadowColor.getAlpha() > 0)
					Repaint(false);
				if (m_pForm)
					m_pForm->UnlockRepaint();
			}
			return this;
		}

		CEdit *CEdit::setBoxShadowRadius(const STATE state, const size_t value)
		{
			if (value != m_sBlock[state].BoxShadowRadius)
			{
				if (m_pForm)
					m_pForm->LockRepaint();
				if (state == getState() && m_sBlock[state].BoxShadow && m_sBlock[state].BoxShadowColor.getAlpha() > 0)
					Repaint(false);
				m_sBlock[state].BoxShadowRadius = value;
				if (state == getState() && m_sBlock[state].BoxShadow && m_sBlock[state].BoxShadowColor.getAlpha() > 0)
					Repaint(false);
				if (m_pForm)
					m_pForm->UnlockRepaint();
			}
			return this;
		}
#pragma endregion
	}
}