// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#include "BaseText.h"
#include "..\..\Form.h"
#include "..\..\Presenter.h"
#include "..\..\Style.h"

namespace licui
{
	namespace application
	{
		const unsigned int TIMER_INTERVAL{ 250 };

	#pragma region Constructors
		CBaseText::CBaseText() :
			m_sRect{ 0, 0, 0, 0 },
			m_iVerticalScroll{ 0 },
			m_iHorizontalScroll{ 0 },
			m_sTextSize{ 0, 0 },
			m_iLineHeight{ 0 },
			m_sSelection{ 0, 0 },
			m_iCaretPosition{ 0 },
			m_bInserting{ true },
			m_bHovered{ false },
			m_hTimer{ 0 },
			m_eMouseMode{ mmNone },
			m_iSpaceWidth{ 0 },
			m_aTextColor{ {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {109, 109, 109, 255} },
			m_aShadowColor{ { 0, 0, 0, 0 },{ 0, 0, 0, 0 },{ 0, 0, 0, 0 },{ 0, 0, 0, 0 },{ 109, 109, 109, 255 } },
			m_aSelectionBackgroundColor{ { 0, 0, 255, 255 },{ 0, 0, 255, 255 },{ 0, 0, 255, 255 },{ 0, 0, 255, 255 },{ 0, 0, 255, 255 } },
			m_aSelectionTextColor{ { 255, 255, 255, 255 },{ 255, 255, 255, 255 },{ 255, 255, 255, 255 },{ 255, 255, 255, 255 },{ 109, 109, 109, 255 } },
			m_aSelectionShadowColor{ { 255, 255, 255, 255 },{ 255, 255, 255, 255 },{ 255, 255, 255, 255 },{ 255, 255, 255, 255 },{ 109, 109, 109, 255 } },
			m_iMaxWidth{ 0 },
			m_iMaxLength{ 0 },
			m_bReadOnly{ false },
			m_iDeltaWheelVertical{ 10 },
			m_iDeltaWheelHorizontal{ 10 },
			m_sLineMargin{ 0, 0 }
		{
			m_cHistory.setLimitCount(3);
			m_cHistory.setLimitSize(1024 * 1024);
			m_cHistory.Store({ m_sText, m_iCaretPosition, m_sSelection }, m_sText.length() * sizeof(wchar_t) + sizeof(HISTORY));
		}
	#pragma endregion

	#pragma region Process events
		bool CBaseText::ProcessMouseDown(const int x, const int y, const bool ctrl, const bool alt, const bool shift)
		{
			size_t caret = CursorToCaret(x, y, ClientToForm(m_sRect));
			if (!shift && m_sSelection[0] != m_sSelection[1] && caret >= std::min(m_sSelection[0], m_sSelection[1]) && caret < std::max(m_sSelection[0], m_sSelection[1]))
				if (ctrl)
					m_eMouseMode = mmCopy;
				else
					m_eMouseMode = mmMove;
			else
				m_eMouseMode = mmSelect;
			switch (m_eMouseMode)
			{
			case mmSelect:
				StartMouseModeSelect(caret, ctrl, shift);
				break;
			}
			setCaretPosition(caret);
			m_iMouseDownCaretPosition = caret;
			m_hTimer = getForm()->AddTimer(TimerCallback, this, TIMER_INTERVAL);
			return true;
		}

		bool CBaseText::ProcessMouseUp(const int x, const int y, const bool ctrl, const bool shift)
		{
			if (m_eMouseMode != mmNone || m_hTimer)
			{
				switch (m_eMouseMode)
				{
				case mmMove:
				case mmCopy:
					if (!shift)
					{
						size_t caret{ CursorToCaret(x, y, ClientToForm(m_sRect)) };
						if (caret == m_iMouseDownCaretPosition)
							m_sSelection[1] = m_sSelection[0];
						else
							ctrl ? ProcessCopyFinish(x, y) : ProcessMoveFinish(x, y);
					}
					break;
				}
				m_eMouseMode = mmNone;
				if (m_hTimer)
				{
					getForm()->DeleteTimer(m_hTimer);
					m_hTimer = 0;
				}
				return true;
			}
			return false;
		}

		bool CBaseText::ProcessMouseHover(const int x, const int y)
		{
			if (!m_bHovered)
			{
				m_bHovered = true;
				return true;
			}
			return false;
		}

		bool CBaseText::ProcessMouseLeave()
		{
			if (m_bHovered)
			{
				m_bHovered = false;
				return true;
			}
			return false;
		}

		bool CBaseText::ProcessMouseMove(const int x, const int y)
		{
			size_t caret = CursorToCaret(x, y, ClientToForm(m_sRect));
			bool changed{ false };
			switch (m_eMouseMode)
			{
			case mmSelect:
				if (m_sSelection[1] != caret)
				{
					m_sSelection[1] = caret;
					changed = true;
				}
				break;
			}
			if (m_eMouseMode != mmNone && setCaretPosition(caret))
				changed = true;
			return changed;
		}

		bool CBaseText::ProcessMouseVerticalWheel(const int x, const int y, const int delta)
		{
			if (m_sTextSize.Y > (size_t)m_sRect.Height())
			{
				size_t old{ m_iVerticalScroll };
				if (delta < 0)
					m_iVerticalScroll = std::min(m_sTextSize.Y - (size_t)m_sRect.Height(), m_iVerticalScroll + m_iDeltaWheelVertical);
				else
					m_iVerticalScroll = std::max(0, (int)m_iVerticalScroll - (int)m_iDeltaWheelVertical);
				return m_iVerticalScroll != old;
			}
			return false;
		}

		bool CBaseText::ProcessMouseHorizontalWheel(const int x, const int y, const int delta)
		{
			if (m_sTextSize.X > (size_t)m_sRect.Width())
			{
				size_t old{ m_iHorizontalScroll };
				if (delta < 0)
					m_iHorizontalScroll = std::min(m_sTextSize.X - (size_t)m_sRect.Width(), m_iHorizontalScroll + m_iDeltaWheelHorizontal);
				else
					m_iHorizontalScroll = std::max(0, (int)m_iHorizontalScroll - (int)m_iDeltaWheelHorizontal);
				return m_iHorizontalScroll != old;
			}
			return false;
		}

		bool CBaseText::ProcessMouseDoubleClick(const int x, const int y)
		{
			size_t caret = CursorToCaret(x, y, ClientToForm(m_sRect));
			if (m_sText.length() > 0 && caret <= m_sText.length() - 1 && std::isalnum(m_sText[caret], std::locale()))
			{
				size_t i{ caret }, j{ caret };
				while (i > 0 && std::isalnum(m_sText[i - 1], std::locale()))
					i--;
				while (j < m_sText.length() && std::isalnum(m_sText[j], std::locale()))
					j++;
				bool changed{ false };
				if (i != m_sSelection[0])
				{
					m_sSelection[0] = i;
					changed = true;
				}
				if (j != m_sSelection[1])
				{
					m_sSelection[1] = j;
					changed = true;
				}
				return changed;
			}
			return false;
		}

		bool CBaseText::ProcessKeyDown(const IWindow::KEY key, const bool ctrl, const bool alt, const bool shift, bool &text_changed, bool &caret_moved)
		{
			text_changed = caret_moved = false;
			switch (key)
			{
			case IWindow::keyUp:
			case IWindow::keyNumpad8:
				if (key == IWindow::keyUp || (key == IWindow::keyNumpad8 && !getForm()->getWindow()->getKeyIsToggled(IWindow::keyNumLock)))
				{
					if (ctrl)
						return ScrollLineUp();
					if (shift)
					{
						caret_moved = true;
						return MoveCaretLineUpAndSelect();
					}
					caret_moved = true;
					return MoveCaretLineUp();
				}
				break;

			case IWindow::keyDown:
			case IWindow::keyNumpad2:
				if (key == IWindow::keyDown || (key == IWindow::keyNumpad2 && !getForm()->getWindow()->getKeyIsToggled(IWindow::keyNumLock)))
				{
					if (ctrl)
						return ScrollLineDown();
					if (shift)
					{
						caret_moved = true;
						return MoveCaretLineDownAndSelect();
					}
					caret_moved = true;
					return MoveCaretLineDown();
				}
				break;

			case IWindow::keyLeft:
			case IWindow::keyNumpad4:
				if (key == IWindow::keyLeft || (key == IWindow::keyNumpad4 && !getForm()->getWindow()->getKeyIsToggled(IWindow::keyNumLock)))
				{
					caret_moved = true;
					if (ctrl)
					{
						if (shift)
							return MoveCaretWordStartAndSelect();
						return MoveCaretWordStart();
					}
					if (shift)
						return MoveCaretLeftAndSelect();
					return MoveCaretLeft();
				}
				break;

			case IWindow::keyRight:
			case IWindow::keyNumpad6:
				if (key == IWindow::keyRight || (key == IWindow::keyNumpad6 && !getForm()->getWindow()->getKeyIsToggled(IWindow::keyNumLock)))
				{
					caret_moved = true;
					if (ctrl)
					{
						if (shift)
							return MoveCaretWordEndAndSelect();
						return MoveCaretWordEnd();
					}
					if (shift)
						return MoveCaretRightAndSelect();
					return MoveCaretRight();
				}
				break;

			case IWindow::keyBack:
				text_changed = caret_moved = true;
				if (m_sSelection[0] != m_sSelection[1])
					return DeleteSelection();
				return DeleteLeft();

			case IWindow::keyDelete:
			case IWindow::keyDecimal:
				if (key == IWindow::keyDelete || (key == IWindow::keyDecimal && !getForm()->getWindow()->getKeyIsToggled(IWindow::keyNumLock)))
				{
					text_changed = caret_moved = true;
					if (m_sSelection[0] != m_sSelection[1])
						return DeleteSelection();
					return DeleteRight();
				}
				break;

			case IWindow::keyInsert:
			case IWindow::keyNumpad0:
				if (key == IWindow::keyInsert || (key == IWindow::keyNumpad0 && !getForm()->getWindow()->getKeyIsToggled(IWindow::keyNumLock)))
					return ProcessInsert();
				break;

			case IWindow::keyHome:
			case IWindow::keyNumpad7:
				if (key == IWindow::keyHome || (key == IWindow::keyNumpad7 && !getForm()->getWindow()->getKeyIsToggled(IWindow::keyNumLock)))
				{
					caret_moved = true;
					if (ctrl)
					{
						if (shift)
							return MoveCaretTextStartAndSelect();
						return MoveCaretTextStart();
					}
					if (shift)
						return MoveCaretLineStartAndSelect();
					return MoveCaretLineStart();
				}
				break;

			case IWindow::keyEnd:
			case IWindow::keyNumpad1:
				if (key == IWindow::keyEnd || (key == IWindow::keyNumpad1 && !getForm()->getWindow()->getKeyIsToggled(IWindow::keyNumLock)))
				{
					caret_moved = true;
					if (ctrl)
					{
						if (shift)
							return MoveCaretTextEndAndSelect();
						return MoveCaretTextEnd();
					}
					if (shift)
						return MoveCaretLineEndAndSelect();
					return MoveCaretLineEnd();
				}
				break;

			case IWindow::keyPrior:
			case IWindow::keyNumpad9:
				if (key == IWindow::keyPrior || (key == IWindow::keyNumpad9 && !getForm()->getWindow()->getKeyIsToggled(IWindow::keyNumLock)))
				{
					caret_moved = true;
					if (ctrl)
					{
						if (shift)
							return MoveCaretPageStartAndSelect();
						return MoveCaretPageStart();
					}
					if (shift)
						return MoveCaretPageUpAndSelect();
					return MoveCaretPageUp();
				}
				break;

			case IWindow::keyNext:
			case IWindow::keyNumpad3:
				if (key == IWindow::keyNext || (key == IWindow::keyNumpad3 && !getForm()->getWindow()->getKeyIsToggled(IWindow::keyNumLock)))
				{
					caret_moved = true;
					if (ctrl)
					{
						if (shift)
							return MoveCaretPageEndAndSelect();
						return MoveCaretPageEnd();
					}
					if (shift)
						return MoveCaretPageDownAndSelect();
					return MoveCaretPageDown();
				}
				break;

			case IWindow::keyA:
				if (ctrl && !shift && !alt)
					return SelectAll();
				break;

			case IWindow::keyV:
				if (ctrl && !shift && !alt)
				{
					text_changed = caret_moved = true;
					return Paste();
				}
				break;

			case IWindow::keyC:
				if (ctrl && !shift && !alt)
					return Copy();
				break;

			case IWindow::keyX:
				if (ctrl && !shift && !alt)
				{
					text_changed = caret_moved = true;
					return Cut();
				}
				break;

			case IWindow::keyZ:
				if (ctrl && !alt)
				{
					text_changed = caret_moved = true;
					return shift ? Redo() : Undo();
				}
				break;
			}
			return false;
		}

		bool CBaseText::ProcessChar(const wchar_t chr)
		{
			bool ctrl, alt, shift;
			getForm()->getWindow()->getControlKeys(ctrl, shift, alt);
			if (!ctrl && !alt && (std::isprint(chr, std::locale()) || std::isspace(chr, std::locale())))
				return m_bInserting ? ProcessInsertChar(chr) : ProcessReplaceChar(chr);
			return false;
		}

		bool CBaseText::ProcessSetFocus()
		{
			return true;
		}

		bool CBaseText::ProcessKillFocus()
		{
			if (getForm()->getWindow()->IsCaretVisible())
				getForm()->getWindow()->HideCaret();
			return true;
		}
	#pragma endregion

	#pragma region Helpers
		bool CBaseText::StartMouseModeSelect(const size_t caret, const bool ctrl, const bool shift)
		{
			bool changed{ false };
			// Shift is not hold. Set selection start to caret position
			if (!shift && m_sSelection[0] != caret)
			{
				m_sSelection[0] = caret;
				changed = true;
			}
			if (!shift)
			{
				// Shift is not hold and Ctrl is not hold. Set selection end to caret position
				if (!ctrl)
				{
					if (m_sSelection[1] != caret)
					{
						m_sSelection[1] = caret;
						return true;
					}
					return changed;
				}
				// Shift is not hold, Ctrl is hold. If caret is on a word, select the word
				if (m_sText.length() > 0 && caret <= m_sText.length() - 1 && std::isalnum(m_sText[caret], std::locale()))
				{
					size_t i{ caret }, j{ caret };
					while (i > 0 && std::isalnum(m_sText[i - 1], std::locale()))
						i--;
					while (j < m_sText.length() && std::isalnum(m_sText[j], std::locale()))
						j++;
					if (i != m_sSelection[0])
					{
						m_sSelection[0] = i;
						changed = true;
					}
					if (j != m_sSelection[1])
					{
						m_sSelection[1] = j;
						changed = true;
					}
					return changed;
				}
				return changed;
			}
			// Shift is hold, Ctrl is not hold. Set selection end to caret position
			if (!ctrl)
			{
				if (m_sSelection[1] != caret)
				{
					m_sSelection[1] = caret;
					return true;
				}
				return changed;
			}
			// Shift and Ctrl are hold. If caret is on a word, set selection end so the word became selected
			if (m_sText.length() > 0 && caret <= m_sText.length() - 1 && std::isalnum(m_sText[caret], std::locale()))
			{
				if (caret < m_sSelection[0])
				{
					size_t index{ caret };
					while (index > 0 && std::isalnum(m_sText[index - 1], std::locale()))
						index--;
					if (index != m_sSelection[1])
					{
						m_sSelection[1] = index;
						changed = true;
					}
				}
				else
				{
					size_t index{ caret };
					while (index < m_sText.length() && std::isalnum(m_sText[index], std::locale()))
						index++;
					if (index != m_sSelection[1])
					{
						m_sSelection[1] = index;
						changed = true;
					}
				}
				return changed;
			}
			return changed;
		}

		size_t CBaseText::CursorToCaret(const int x, const int y, const APP_RECT &rect)
		{
			size_t result{ 0 };
			if (m_iSpaceWidth == 0 || m_iLineHeight == 0 || m_sText.length() == 0)
				return result;
			size_t caret_y{ std::min(m_aLines.size() - 1, (size_t)std::max((int)0, (y - rect.Top + (int)m_iVerticalScroll) / (int)m_iLineHeight)) };
			int dx{ x - rect.Left + (int)m_iHorizontalScroll };
			IFont *font{ getFont() };
			int tx{ 0 }, w;
			result = m_aLines[caret_y].Start;
			if (m_sText.length() > 0)
				while (result <= m_aLines[caret_y].End && result <= m_sText.length() - 1 && !m_aLines[caret_y].Empty)
				{
					w = font->getChar(m_sText[result])->Width + font->getDistance();
					if (tx + w > dx)
					{
						if (dx > tx + w / 2)
							result++;
						break;
					}
					tx += w;
					result++;
				}
			return result;
		}

		void CBaseText::TimerCallback(void *param)
		{
			CBaseText *text{ (CBaseText*)param };
			int x, y;
			if (text->getForm()->getWindow()->getCursorPosition(x, y))
			{
				APP_RECT rect = text->ClientToForm(text->m_sRect);
				bool changed{ false };
				if (x < rect.Left)
				{
					if (text->m_iHorizontalScroll > 0)
						changed = text->setHorizontalScroll(std::max(0, (int)text->m_iHorizontalScroll - (rect.Left - x))) || changed;
					changed = text->ProcessMouseMove(rect.Left, y) || changed;
				}
				else if (x >= rect.Right)
				{
					if ((int)text->m_iHorizontalScroll < (int)text->m_sTextSize.X - rect.Width())
						changed = text->setHorizontalScroll(text->m_iHorizontalScroll + (x - rect.Right)) || changed;
					text->ProcessMouseMove(rect.Right, y) || changed;
				}
				if (y < rect.Top)
				{
					if (text->m_iVerticalScroll > 0)
						changed = text->setVerticalScroll(std::max(0, (int)text->m_iVerticalScroll - (rect.Top - y))) || changed;
					changed = text->ProcessMouseMove(x, rect.Top) || changed;
				}
				else if (y >= rect.Bottom)
				{
					if ((int)text->m_iVerticalScroll < (int)text->m_sTextSize.Y - rect.Height())
						changed = text->setVerticalScroll(text->m_iVerticalScroll + (y - rect.Top)) || changed;
					changed = text->ProcessMouseMove(x, rect.Bottom) || changed;
				}
				if (changed)
					text->NotifyOnChange();
			}
		}

		size_t CBaseText::getCaretLine(const size_t caret)
		{
			LINE line{ 0, caret, 0 };
			auto pos = std::lower_bound(m_aLines.begin(), m_aLines.end(), line, [](const LINE &a, const LINE &b) {
				return a.End < b.End ? true : false;
			});
			if (pos == m_aLines.end())
				return m_aLines.size() - 1;
			if (pos->Start > caret)
				return pos - m_aLines.begin() - 1;
			return pos - m_aLines.begin();
		}

		APP_POINT CBaseText::CaretToForm(const size_t caret)
		{
			APP_RECT rect = ClientToForm(m_sRect);
			size_t y{ getCaretLine(caret) };
			APP_POINT result{ rect.Left - (int)m_iHorizontalScroll, rect.Top + (int)y * (int)m_iLineHeight - (int)m_iVerticalScroll };
			size_t i{ m_aLines[y].Start };
			IFont *font{ getFont() };
			if (m_sText.length() > 0)
				while (caret > i && i <= m_aLines[y].End && i <= m_sText.length() - 1)
				{
					result.X += font->getChar(m_sText[i])->Width + font->getDistance();
					i++;
				}
			return result;
		}

		void CBaseText::UpdateCaret()
		{
			if (getFocused())
			{
				size_t line1{ m_iVerticalScroll / m_iLineHeight }, line2{ line1 + (size_t)(0.5 + (double)m_sRect.Height() / (double)m_iLineHeight) };
				size_t caret_y{ getCaretLine(m_iCaretPosition) };
				if (caret_y >= line1 && caret_y <= line2)
				{
					APP_RECT rect = ClientToForm(m_sRect);
					int y{ rect.Top + (int)caret_y * (int)m_iLineHeight - (int)m_iVerticalScroll };
					int x{ 0 }, w{ 0 };
					bool visible{ false };
					x = rect.Left - (int)m_iHorizontalScroll;
					size_t i{ m_aLines[caret_y].Start };
					IFont *font{ getFont() };
					if (m_sText.length() > 0)
						while (i <= m_aLines[caret_y].End && m_iCaretPosition > i && i <= m_sText.length() - 1)
						{
							x += font->getChar(m_sText[i])->Width + font->getDistance();
							i++;
						}
					if (m_iCaretPosition >= m_sText.length())
						w = m_iSpaceWidth;
					else
						w = font->getChar(m_sText[m_iCaretPosition])->Width + font->getDistance();
					visible = x >= rect.Left && x < rect.Right;
					if (visible)
					{
						if (m_bInserting)
							w = 1;
						int h{ (int)m_iLineHeight - (int)m_sLineMargin[0] - (int)m_sLineMargin[1] };
						y += (int)m_sLineMargin[0];
						if (y < rect.Top)
						{
							h -= rect.Top - y;
							y = rect.Top;
						}
						if (y + h >= rect.Bottom)
							h = rect.Bottom - y;
						if (x < rect.Left)
						{
							w -= rect.Left - x;
							x = rect.Left;
						}
						if (x + w >= rect.Right)
							w = rect.Right - x;
						if (h > 0 && w > 0 && getForm()->getWindow()->CreateCaret(w, h))
						{
							getForm()->getWindow()->SetCaretPosition(x, y);
							getForm()->getWindow()->ShowCaret();
						}
						else if (getForm()->getWindow()->IsCaretVisible())
							getForm()->getWindow()->HideCaret();
					}
					else if (getForm()->getWindow()->IsCaretVisible())
						getForm()->getWindow()->HideCaret();
				}
				else if (getForm()->getWindow()->IsCaretVisible())
					getForm()->getWindow()->HideCaret();
			}
		}

		bool CBaseText::ScrollToCaret()
		{
			APP_RECT rect = ClientToForm(m_sRect);
			APP_POINT pos = CaretToForm(m_iCaretPosition);
			bool changed{ false };
			int w{ (m_iCaretPosition >= m_sText.length() || std::isspace(m_sText[m_iCaretPosition], std::locale())) ? (int)m_iSpaceWidth : ((int)getFont()->getChar(m_sText[m_iCaretPosition])->Width + getFont()->getDistance()) };
			if (pos.X < rect.Left && setHorizontalScroll(std::max(0, (int)m_iHorizontalScroll - (rect.Left - pos.X))))
				changed = true;
			else if (pos.X >= rect.Right - w && setHorizontalScroll(std::min((int)m_sTextSize.X - m_sRect.Width(), (int)m_iHorizontalScroll + pos.X - (rect.Right - w))))
				changed = true;
			if (pos.Y < rect.Top && setVerticalScroll(std::max(0, (int)m_iVerticalScroll - (rect.Top - pos.Y))))
				changed = true;
			else if (pos.Y >= rect.Bottom - (int)m_iLineHeight && setVerticalScroll(std::min((int)m_sTextSize.Y - m_sRect.Height(), (int)m_iVerticalScroll + pos.Y - (rect.Bottom - (int)m_iLineHeight))))
				changed = true;
			return changed;
		}

		size_t CBaseText::CalculateLineHeight()
		{
			APP_POINT size = getFont()->getStringSize(L"Wy");
			return m_sLineMargin[0] + (size_t)size.Y + m_sLineMargin[1];
		}

		size_t CBaseText::CalculateSpaceWidth()
		{
			IFont *font{ getFont() };
			APP_POINT size = font->getStringSize(L" ");
			return size.X + font->getDistance();
		}

		void CBaseText::UpdateLines()
		{
			m_aLines.clear();
			size_t index{ 0 };
			IFont *font{ getFont() };
			LINE line{ index, index, 0, true };
			size_t w;
			while (index < m_sText.length())
			{
				w = font->getChar(m_sText[index])->Width + font->getDistance();
				if (m_sText[index] == L'\r')
				{
					if (line.Empty)
						line.Start = index;
					m_aLines.push_back(line);
					line.Start = line.End = ++index;
					line.Empty = true;
					line.Width = 0;
					continue;
				}
				if (m_iMaxWidth > 0 && line.Width + w > m_iMaxWidth && !line.Empty)
				{
					m_aLines.push_back(line);
					line.Start = line.End = index;
					line.Empty = true;
					line.Width = 0;
					continue;
				}
				line.End = index;
				line.Width += w;
				line.Empty = false;
				index++;
			}
			m_aLines.push_back(line);
		}

		void CBaseText::UpdateTextSize()
		{
			m_sTextSize.Y = m_iLineHeight * m_aLines.size();
			m_sTextSize.X = 0;
			for (auto pos = m_aLines.begin(); pos != m_aLines.end(); pos++)
				m_sTextSize.X = std::max(m_sTextSize.X, pos->Width);
			m_sTextSize.X += m_iSpaceWidth;
		}

		void CBaseText::UpdateScrolls()
		{
			if ((int)m_sTextSize.Y <= m_sRect.Height())
				m_iVerticalScroll = 0;
			else if ((int)m_iVerticalScroll > (int)m_sTextSize.Y - m_sRect.Height())
				m_iVerticalScroll = m_sTextSize.Y - m_sRect.Height();
			if ((int)m_sTextSize.X <= m_sRect.Width())
				m_iHorizontalScroll = 0;
			else if ((int)m_iHorizontalScroll > (int)m_sTextSize.X - m_sRect.Width())
				m_iHorizontalScroll = m_sTextSize.X - m_sRect.Width();
		}

		void CBaseText::Update()
		{
			m_iLineHeight = CalculateLineHeight();
			m_iSpaceWidth = CalculateSpaceWidth();
			UpdateLines();
			UpdateTextSize();
			UpdateScrolls();
		}

		void CBaseText::DeleteSelectionInternal()
		{
			math::POINT<size_t> selection{ std::min(m_sSelection[0], m_sSelection[1]), std::max(m_sSelection[0], m_sSelection[1]) };
			m_sText.erase(selection[0], selection[1] - selection[0]);
			if (m_iCaretPosition > selection[0])
				if (m_iCaretPosition < selection[1])
					m_iCaretPosition = selection[0];
				else
					m_iCaretPosition -= selection[1] - selection[0];
			m_sSelection[1] = m_sSelection[0] = m_iCaretPosition;
		}

		bool CBaseText::CanUndo()
		{
			return !m_bReadOnly && m_cHistory.getPosition() > 0;
		}

		bool CBaseText::CanRedo()
		{
			return !m_bReadOnly && m_cHistory.getCount() > 0 && m_cHistory.getPosition() < m_cHistory.getCount() - 1;
		}

		bool CBaseText::Undo()
		{
			if (!m_bReadOnly && m_cHistory.getPosition() > 0)
			{
				HISTORY h = m_cHistory.getItem(m_cHistory.getPosition() - 1);
				m_sText = h.Text;
				m_iCaretPosition = h.CaretPosition;
				m_sSelection = h.Selection;
				CutLength();
				m_cHistory.setPosition(m_cHistory.getPosition() - 1);
				UpdateLines();
				UpdateTextSize();
				UpdateScrolls();
				return true;
			}
			return false;
		}

		bool CBaseText::Redo()
		{
			if (!m_bReadOnly && m_cHistory.getPosition() < m_cHistory.getCount() - 1)
			{
				HISTORY h = m_cHistory.getItem(m_cHistory.getPosition() + 1);
				m_sText = h.Text;
				m_iCaretPosition = h.CaretPosition;
				m_sSelection = h.Selection;
				CutLength();
				m_cHistory.setPosition(m_cHistory.getPosition() + 1);
				UpdateLines();
				UpdateTextSize();
				UpdateScrolls();
				return true;
			}
			return false;
		}

		void CBaseText::CutLength()
		{
			if (m_iMaxLength > 0 && m_sText.length() > m_iMaxLength)
			{
				m_sText.erase(m_iMaxLength, m_sText.length() - m_iMaxLength);
				if (m_iCaretPosition > m_sText.length())
					m_iCaretPosition = m_sText.length();
				if (m_sSelection[0] > m_sText.length())
					m_sSelection[0] = m_sText.length();
				if (m_sSelection[1] > m_sText.length())
					m_sSelection[1] = m_sText.length();
			}
		}

		bool CBaseText::ScrollLineUp()
		{
			if (m_iVerticalScroll > 0)
			{
				m_iVerticalScroll = std::max(0, (int)m_iVerticalScroll - (int)m_iLineHeight);
				return true;
			}
			return false;
		}

		bool CBaseText::ScrollLineDown()
		{
			if (m_sTextSize.Y > (size_t)m_sRect.Height() && m_iVerticalScroll < m_sTextSize.Y - (size_t)m_sRect.Height())
			{
				m_iVerticalScroll = std::min((int)m_sTextSize.Y - m_sRect.Height(), (int)m_iVerticalScroll + (int)m_iLineHeight);
				return true;
			}
			return false;
		}

		bool CBaseText::MoveCaretLineUpAndSelect()
		{
			size_t y{ getCaretLine(m_iCaretPosition) };
			if (y > 0)
			{
				APP_POINT p = CaretToForm(m_iCaretPosition);
				p.Y -= (int)m_iLineHeight / 2;
				size_t caret{ CursorToCaret(p.X, p.Y, ClientToForm(m_sRect)) };
				if (caret != m_iCaretPosition)
				{
					m_sSelection[1] = caret;
					m_iCaretPosition = caret;
					return true;
				}
			}
			return false;
		}

		bool CBaseText::MoveCaretLineUp()
		{
			size_t y{ getCaretLine(m_iCaretPosition) };
			if (y > 0)
			{
				APP_POINT p = CaretToForm(m_iCaretPosition);
				p.Y -= (int)m_iLineHeight / 2;
				size_t caret{ CursorToCaret(p.X, p.Y, ClientToForm(m_sRect)) };
				if (caret != m_iCaretPosition || m_sSelection[1] != m_sSelection[0])
				{
					m_sSelection[1] = m_sSelection[0] = caret;
					m_iCaretPosition = caret;
					return true;
				}
			}
			if (m_sSelection[1] != m_sSelection[0])
			{
				m_sSelection[1] = m_sSelection[0] = m_iCaretPosition;
				return true;
			}
			return false;
		}

		bool CBaseText::MoveCaretLineDownAndSelect()
		{
			size_t y{ getCaretLine(m_iCaretPosition) };
			if (y < m_aLines.size() - 1)
			{
				APP_POINT p = CaretToForm(m_iCaretPosition);
				p.Y += 3 * (int)m_iLineHeight / 2;
				size_t caret{ CursorToCaret(p.X, p.Y, ClientToForm(m_sRect)) };
				if (caret != m_iCaretPosition)
				{
					m_sSelection[1] = caret;
					m_iCaretPosition = caret;
					return true;
				}
			}
			return false;
		}

		bool CBaseText::MoveCaretLineDown()
		{
			size_t y{ getCaretLine(m_iCaretPosition) };
			if (y < m_aLines.size() - 1)
			{
				APP_POINT p = CaretToForm(m_iCaretPosition);
				p.Y += 3 * (int)m_iLineHeight / 2;
				size_t caret{ CursorToCaret(p.X, p.Y, ClientToForm(m_sRect)) };
				if (caret != m_iCaretPosition || m_sSelection[1] != m_sSelection[0])
				{
					m_sSelection[1] = m_sSelection[0] = caret;
					m_iCaretPosition = caret;
					return true;
				}
			}
			if (m_sSelection[1] != m_sSelection[0])
			{
				m_sSelection[1] = m_sSelection[0] = m_iCaretPosition;
				return true;
			}
			return false;
		}

		bool CBaseText::MoveCaretWordStartAndSelect()
		{
			size_t caret{ SearchPrevWord(m_sText, m_iCaretPosition, false) };
			if (caret != m_iCaretPosition || caret != m_sSelection[1])
			{
				m_sSelection[1] = caret;
				m_iCaretPosition = caret;
				return true;
			}
			return false;
		}

		bool CBaseText::MoveCaretWordStart()
		{
			size_t caret{ SearchPrevWord(m_sText, m_iCaretPosition, false) };
			if (caret != m_iCaretPosition || m_sSelection[1] != m_sSelection[0])
			{
				m_sSelection[1] = m_sSelection[0] = caret;
				m_iCaretPosition = caret;
				return true;
			}
			return false;
		}

		bool CBaseText::MoveCaretLeftAndSelect()
		{
			if (m_iCaretPosition > 0)
			{
				m_iCaretPosition--;
				m_sSelection[1] = m_iCaretPosition;
				return true;
			}
			return false;
		}

		bool CBaseText::MoveCaretLeft()
		{
			if (m_iCaretPosition > 0 || m_sSelection[1] != m_sSelection[0])
			{
				if (m_iCaretPosition > 0)
					m_iCaretPosition--;
				m_sSelection[1] = m_sSelection[0] = m_iCaretPosition;
				return true;
			}
			return false;
		}

		bool CBaseText::MoveCaretWordEndAndSelect()
		{
			size_t caret{ SearchNextWord(m_sText, m_iCaretPosition, false) };
			if (caret != m_iCaretPosition || caret != m_sSelection[1])
			{
				m_sSelection[1] = caret;
				m_iCaretPosition = caret;
				return true;
			}
			return false;
		}

		bool CBaseText::MoveCaretWordEnd()
		{
			size_t caret{ SearchNextWord(m_sText, m_iCaretPosition, false) };
			if (caret != m_iCaretPosition || m_sSelection[1] != m_sSelection[0])
			{
				m_sSelection[1] = m_sSelection[0] = caret;
				m_iCaretPosition = caret;
				return true;
			}
			return false;
		}

		bool CBaseText::MoveCaretRightAndSelect()
		{
			if (m_iCaretPosition < m_sText.length())
			{
				m_iCaretPosition++;
				m_sSelection[1] = m_iCaretPosition;
				return true;
			}
			return false;
		}

		bool CBaseText::MoveCaretRight()
		{
			if (m_iCaretPosition < m_sText.length() || m_sSelection[1] != m_sSelection[0])
			{
				if (m_iCaretPosition < m_sText.length())
					m_iCaretPosition++;
				m_sSelection[1] = m_sSelection[0] = m_iCaretPosition;
				return true;
			}
			return false;
		}

		bool CBaseText::DeleteSelection()
		{
			if (!m_bReadOnly && m_sSelection[0] != m_sSelection[1])
			{
				DeleteSelectionInternal();
				m_cHistory.Store({ m_sText, m_iCaretPosition, m_sSelection }, m_sText.length() * sizeof(wchar_t) + sizeof(HISTORY));
				UpdateLines();
				UpdateTextSize();
				UpdateScrolls();
				return true;
			}
			return false;
		}

		bool CBaseText::DeleteLeft()
		{
			if (!m_bReadOnly && m_iCaretPosition > 0)
			{
				m_sText.erase(m_iCaretPosition - 1, 1);
				m_iCaretPosition--;
				m_sSelection[1] = m_sSelection[0] = m_iCaretPosition;
				m_cHistory.Store({ m_sText, m_iCaretPosition, m_sSelection }, m_sText.length() * sizeof(wchar_t) + sizeof(HISTORY));
				UpdateLines();
				UpdateTextSize();
				UpdateScrolls();
				return true;
			}
			return false;
		}

		bool CBaseText::DeleteRight()
		{
			if (!m_bReadOnly && m_iCaretPosition < m_sText.length())
			{
				m_sText.erase(m_iCaretPosition, 1);
				m_cHistory.Store({ m_sText, m_iCaretPosition, m_sSelection }, m_sText.length() * sizeof(wchar_t) + sizeof(HISTORY));
				UpdateLines();
				UpdateTextSize();
				UpdateScrolls();
				return true;
			}
			return false;
		}

		bool CBaseText::MoveCaretTextStartAndSelect()
		{
			if (m_iCaretPosition != 0 || m_sSelection[1] != 0)
			{
				m_iCaretPosition = 0;
				m_sSelection[1] = 0;
				return true;
			}
			return false;
		}

		bool CBaseText::MoveCaretTextStart()
		{
			if (m_iCaretPosition != 0 || m_sSelection[1] != m_sSelection[0])
			{
				m_iCaretPosition = 0;
				m_sSelection[1] = m_sSelection[0] = 0;
				return true;
			}
			return false;
		}

		bool CBaseText::MoveCaretLineStartAndSelect()
		{
			size_t y{ getCaretLine(m_iCaretPosition) };
			if (y < m_aLines.size() && !m_aLines[y].Empty && (m_iCaretPosition != m_aLines[y].Start || m_sSelection[1] != m_aLines[y].Start))
			{
				m_iCaretPosition = m_aLines[y].Start;
				m_sSelection[1] = m_iCaretPosition;
				return true;
			}
			return false;
		}

		bool CBaseText::MoveCaretLineStart()
		{
			size_t y{ getCaretLine(m_iCaretPosition) };
			if (y < m_aLines.size() && !m_aLines[y].Empty && (m_iCaretPosition != m_aLines[y].Start || m_sSelection[1] != m_sSelection[0]))
			{
				m_iCaretPosition = m_aLines[y].Start;
				m_sSelection[1] = m_sSelection[0] = m_iCaretPosition;
				return true;
			}
			return false;
		}

		bool CBaseText::MoveCaretTextEndAndSelect()
		{
			if (m_iCaretPosition < m_sText.length() || m_sSelection[1] != m_sText.length())
			{
				m_iCaretPosition = m_sText.length();
				m_sSelection[1] = m_iCaretPosition;
				return true;
			}
			return false;
		}

		bool CBaseText::MoveCaretTextEnd()
		{
			if (m_iCaretPosition < m_sText.length() || m_sSelection[1] != m_sSelection[0])
			{
				m_iCaretPosition = m_sText.length();
				m_sSelection[1] = m_sSelection[0] = m_iCaretPosition;
				return true;
			}
			return false;
		}

		bool CBaseText::MoveCaretLineEndAndSelect()
		{
			size_t y{ getCaretLine(m_iCaretPosition) };
			if (y < m_aLines.size() && !m_aLines[y].Empty && (m_iCaretPosition != m_aLines[y].End + 1 || m_sSelection[1] != m_aLines[y].End + 1))
			{
				m_iCaretPosition = m_aLines[y].End + 1;
				m_sSelection[1] = m_iCaretPosition;
				return true;
			}
			return false;
		}

		bool CBaseText::MoveCaretLineEnd()
		{
			size_t y{ getCaretLine(m_iCaretPosition) };
			if (y < m_aLines.size() && !m_aLines[y].Empty && (m_iCaretPosition != m_aLines[y].End + 1 || m_sSelection[1] != m_sSelection[0]))
			{
				m_iCaretPosition = m_aLines[y].End + 1;
				m_sSelection[1] = m_sSelection[0] = m_iCaretPosition;
				return true;
			}
			return false;
		}

		bool CBaseText::MoveCaretPageStartAndSelect()
		{
			size_t y{ getCaretLine(m_iCaretPosition) }, new_y{ m_iVerticalScroll / m_iLineHeight };
			if (m_iVerticalScroll % m_iLineHeight > 0)
				new_y++;
			new_y = std::min(new_y, m_aLines.size() - 1);
			if (new_y != y)
			{
				APP_POINT p = CaretToForm(m_iCaretPosition);
				p.Y += (int)m_iLineHeight / 2 - (int)m_iLineHeight * ((int)y - (int)new_y);
				size_t caret{ CursorToCaret(p.X, p.Y, ClientToForm(m_sRect)) };
				if (caret != m_iCaretPosition)
				{
					m_sSelection[1] = caret;
					m_iCaretPosition = caret;
					return true;
				}
			}
			return false;
		}

		bool CBaseText::MoveCaretPageStart()
		{
			size_t y{ getCaretLine(m_iCaretPosition) }, new_y{ m_iVerticalScroll / m_iLineHeight };
			if (m_iVerticalScroll % m_iLineHeight > 0)
				new_y++;
			new_y = std::min(new_y, m_aLines.size() - 1);
			if (new_y != y)
			{
				APP_POINT p = CaretToForm(m_iCaretPosition);
				p.Y += (int)m_iLineHeight / 2 - (int)m_iLineHeight * ((int)y - (int)new_y);
				size_t caret{ CursorToCaret(p.X, p.Y, ClientToForm(m_sRect)) };
				if (caret != m_iCaretPosition || m_sSelection[1] != m_sSelection[0])
				{
					m_iCaretPosition = caret;
					m_sSelection[1] = m_sSelection[0] = m_iCaretPosition;
					return true;
				}
			}
			return false;
		}

		bool CBaseText::MoveCaretPageUpAndSelect()
		{
			size_t y{ getCaretLine(m_iCaretPosition) }, page_size{ (size_t)std::max(1, (m_sRect.Height() - (int)m_iLineHeight) / (int)m_iLineHeight) }, new_y{ (size_t)std::max(0, (int)y - (int)page_size) };
			if (new_y != y)
			{
				APP_POINT p = CaretToForm(m_iCaretPosition);
				p.Y += (int)m_iLineHeight / 2 - (int)m_iLineHeight * ((int)y - (int)new_y);
				size_t caret{ CursorToCaret(p.X, p.Y, ClientToForm(m_sRect)) };
				if (caret != m_iCaretPosition)
				{
					m_sSelection[1] = caret;
					m_iCaretPosition = caret;
					return true;
				}
			}
			return false;
		}

		bool CBaseText::MoveCaretPageUp()
		{
			size_t y{ getCaretLine(m_iCaretPosition) }, page_size{ (size_t)std::max(1, (m_sRect.Height() - (int)m_iLineHeight) / (int)m_iLineHeight) }, new_y{ (size_t)std::max(0, (int)y - (int)page_size) };
			if (new_y != y)
			{
				APP_POINT p = CaretToForm(m_iCaretPosition);
				p.Y += (int)m_iLineHeight / 2 - (int)m_iLineHeight * ((int)y - (int)new_y);
				size_t caret{ CursorToCaret(p.X, p.Y, ClientToForm(m_sRect)) };
				if (caret != m_iCaretPosition || m_sSelection[1] != m_sSelection[0])
				{
					m_iCaretPosition = caret;
					m_sSelection[1] = m_sSelection[0] = m_iCaretPosition;
					return true;
				}
			}
			return false;
		}

		bool CBaseText::MoveCaretPageEndAndSelect()
		{
			size_t y{ getCaretLine(m_iCaretPosition) }, new_y{ (size_t)std::max(0, ((int)m_iVerticalScroll + m_sRect.Height() - (int)m_iLineHeight) / (int)m_iLineHeight) };
			new_y = std::min(new_y, m_aLines.size() - 1);
			if (new_y != y)
			{
				APP_POINT p = CaretToForm(m_iCaretPosition);
				p.Y += (int)m_iLineHeight / 2 + (int)m_iLineHeight * ((int)new_y - (int)y);
				size_t caret{ CursorToCaret(p.X, p.Y, ClientToForm(m_sRect)) };
				if (caret != m_iCaretPosition)
				{
					m_sSelection[1] = caret;
					m_iCaretPosition = caret;
					return true;
				}
			}
			return false;
		}

		bool CBaseText::MoveCaretPageEnd()
		{
			size_t y{ getCaretLine(m_iCaretPosition) }, new_y{ (size_t)std::max(0, ((int)m_iVerticalScroll + m_sRect.Height() - (int)m_iLineHeight) / (int)m_iLineHeight) };
			new_y = std::min(new_y, m_aLines.size() - 1);
			if (new_y != y)
			{
				APP_POINT p = CaretToForm(m_iCaretPosition);
				p.Y += (int)m_iLineHeight / 2 + (int)m_iLineHeight * ((int)new_y - (int)y);
				size_t caret{ CursorToCaret(p.X, p.Y, ClientToForm(m_sRect)) };
				if (caret != m_iCaretPosition || m_sSelection[1] != m_sSelection[0])
				{
					m_iCaretPosition = caret;
					m_sSelection[1] = m_sSelection[0] = m_iCaretPosition;
					return true;
				}
			}
			return false;
		}

		bool CBaseText::MoveCaretPageDownAndSelect()
		{
			size_t y{ getCaretLine(m_iCaretPosition) }, page_size{ (size_t)std::max(1, (m_sRect.Height() - (int)m_iLineHeight) / (int)m_iLineHeight) }, new_y{ std::min(m_aLines.size() - 1, y + page_size) };
			if (new_y != y)
			{
				APP_POINT p = CaretToForm(m_iCaretPosition);
				p.Y += (int)m_iLineHeight / 2 + (int)m_iLineHeight * ((int)new_y - (int)y);
				size_t caret{ CursorToCaret(p.X, p.Y, ClientToForm(m_sRect)) };
				if (caret != m_iCaretPosition)
				{
					m_sSelection[1] = caret;
					m_iCaretPosition = caret;
					return true;
				}
			}
			return false;
		}

		bool CBaseText::MoveCaretPageDown()
		{
			size_t y{ getCaretLine(m_iCaretPosition) }, page_size{ (size_t)std::max(1, (m_sRect.Height() - (int)m_iLineHeight) / (int)m_iLineHeight) }, new_y{ std::min(m_aLines.size() - 1, y + page_size) };
			if (new_y != y)
			{
				APP_POINT p = CaretToForm(m_iCaretPosition);
				p.Y += (int)m_iLineHeight / 2 + (int)m_iLineHeight * ((int)new_y - (int)y);
				size_t caret{ CursorToCaret(p.X, p.Y, ClientToForm(m_sRect)) };
				if (caret != m_iCaretPosition || m_sSelection[1] != m_sSelection[0])
				{
					m_iCaretPosition = caret;
					m_sSelection[1] = m_sSelection[0] = m_iCaretPosition;
					return true;
				}
			}
			return false;
		}

		bool CBaseText::SelectAll()
		{
			if (m_sSelection[0] != 0 || m_sSelection[1] != m_sText.length())
			{
				m_sSelection[0] = 0;
				m_sSelection[1] = m_sText.length();
				return true;
			}
			return false;
		}

		bool CBaseText::Paste()
		{
			if (!m_bReadOnly && getForm())
			{
				String s = getForm()->getWindow()->CopyStringFromClipboard();
				size_t i{ 0 };
				while (i < s.length())
					if (!std::isprint(s[i], std::locale()) && !std::isspace(s[i], std::locale()))
						s.erase(i, 1);
					else
						i++;
				if (s.length() > 0)
				{
					if (m_sSelection[1] != m_sSelection[0])
						DeleteSelectionInternal();
					m_sText.insert(m_iCaretPosition, s);
					m_iCaretPosition += s.length();
					m_sSelection[1] = m_sSelection[0] = m_iCaretPosition;
					CutLength();
					m_cHistory.Store({ m_sText, m_iCaretPosition, m_sSelection }, m_sText.length() * sizeof(wchar_t) + sizeof(HISTORY));
					UpdateLines();
					UpdateTextSize();
					UpdateScrolls();
					return true;
				}
			}
			return false;
		}

		bool CBaseText::Copy()
		{
			if (getForm() && m_sSelection[1] != m_sSelection[0])
				return getForm()->getWindow()->CopyStringToClipboard(m_sText.substr(std::min(m_sSelection[0], m_sSelection[1]), std::max(m_sSelection[0], m_sSelection[1]) - std::min(m_sSelection[0], m_sSelection[1])));
			return false;
		}

		bool CBaseText::Cut()
		{
			if (!m_bReadOnly && getForm() && m_sSelection[1] != m_sSelection[0])
			{
				math::POINT<size_t> selection{ std::min(m_sSelection[0], m_sSelection[1]) , std::max(m_sSelection[0], m_sSelection[1]) };
				getForm()->getWindow()->CopyStringToClipboard(m_sText.substr(selection[0], selection[1] - selection[0]));
				m_sText.erase(selection[0], selection[1] - selection[0]);
				m_iCaretPosition = selection[0];
				m_sSelection[1] = m_sSelection[0] = m_iCaretPosition;
				m_cHistory.Store({ m_sText, m_iCaretPosition, m_sSelection }, m_sText.length() * sizeof(wchar_t) + sizeof(HISTORY));
				UpdateLines();
				UpdateTextSize();
				UpdateScrolls();
				return true;
			}
			return false;
		}

		String CBaseText::getStateName(const STATE state)
		{
			switch (state)
			{
			case stNormal:
				return L".normal";
			case stHovered:
				return L".hovered";
			case stActive:
				return L".active";
			case stActiveHovered:
				return L".active.hovered";
			}
			return L".disabled";
		}

		bool CBaseText::UpdateFromStyle()
		{
			if (!getStyle())
				return false;
			m_iDeltaWheelVertical = getStyle()->getParameterByName(getClassName() + L".DeltaWheelVertical", m_iDeltaWheelVertical);
			m_iDeltaWheelHorizontal = getStyle()->getParameterByName(getClassName() + L".DeltaWheelHorizontal", m_iDeltaWheelHorizontal);
			m_sLineMargin = getStyle()->getParameterByName(getClassName() + L".LineMargin", m_sLineMargin);
			for (int i = 0; i <= stDisabled; i++)
			{
				String name{ getStateName((STATE)i) };
				m_aTextColor[i] = getStyle()->getParameterByName(getClassName() + L".TextColor" + name, m_aTextColor[i]);
				m_aShadowColor[i] = getStyle()->getParameterByName(getClassName() + L".ShadowColor" + name, m_aShadowColor[i]);
				m_aSelectionBackgroundColor[i] = getStyle()->getParameterByName(getClassName() + L".SelectionBackgroundColor" + name, m_aSelectionBackgroundColor[i]);
				m_aSelectionTextColor[i] = getStyle()->getParameterByName(getClassName() + L".SelectionTextColor" + name, m_aSelectionTextColor[i]);
				m_aSelectionShadowColor[i] = getStyle()->getParameterByName(getClassName() + L".SelectionShadowColor" + name, m_aSelectionShadowColor[i]);
			}
			return true;
		}

		bool CBaseText::ClearHistory()
		{
			if (m_cHistory.getCount() > 0)
			{
				m_cHistory.Clear();
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Getters
		size_t CBaseText::getVerticalScroll() const
		{
			return m_iVerticalScroll;
		}

		size_t CBaseText::getHorizontalScroll() const
		{
			return m_iHorizontalScroll;
		}

		APP_RECT CBaseText::getRect()
		{
			return m_sRect;
		}

		math::POINT<size_t> CBaseText::getTextSize()
		{
			return m_sTextSize;
		}

		size_t CBaseText::getLineHeight()
		{
			return m_iLineHeight;
		}

		CBaseText::STATE CBaseText::getState()
		{
			if (!getEnabled())
				return stDisabled;
			if (getFocused())
			{
				if (m_bHovered)
					return stActiveHovered;
				return stActive;
			}
			if (m_bHovered)
				return stHovered;
			return stNormal;
		}

		size_t CBaseText::getMaxWidth() const
		{
			return m_iMaxWidth;
		}

		math::POINT<size_t> CBaseText::getLineMargin() const
		{
			return m_sLineMargin;
		}

		size_t CBaseText::getLineMarginTop() const
		{
			return m_sLineMargin[0];
		}

		size_t CBaseText::getLineMarginBottom() const
		{
			return m_sLineMargin[1];
		}

		const String &CBaseText::getText() const
		{
			return m_sText;
		}

		APP_COLOR CBaseText::getTextColor(const STATE state) const
		{
			return m_aTextColor[state];
		}

		APP_COLOR CBaseText::getShadowColor(const STATE state) const
		{
			return m_aShadowColor[state];
		}

		APP_COLOR CBaseText::getSelectionBackgroundColor(const STATE state) const
		{
			return m_aSelectionBackgroundColor[state];
		}

		APP_COLOR CBaseText::getSelectionTextColor(const STATE state) const
		{
			return m_aSelectionTextColor[state];
		}

		APP_COLOR CBaseText::getSelectionShadowColor(const STATE state) const
		{
			return m_aSelectionShadowColor[state];
		}

		size_t CBaseText::getMaxLength() const
		{
			return m_iMaxLength;
		}

		bool CBaseText::getReadOnly() const
		{
			return m_bReadOnly;
		}

		bool CBaseText::getInserting() const
		{
			return m_bInserting;
		}

		math::POINT<size_t> CBaseText::getSelection() const
		{
			return m_sSelection;
		}

		size_t CBaseText::getCaretPosition() const
		{
			return m_iCaretPosition;
		}

		size_t CBaseText::getDeltaWheelVertical() const
		{
			return m_iDeltaWheelVertical;
		}

		size_t CBaseText::getDeltaWheelHorizontal() const
		{
			return m_iDeltaWheelHorizontal;
		}

		bool CBaseText::getVerticalScrollRequired(const size_t max_width, const size_t height)
		{
			size_t line_height{ CalculateLineHeight() };
			size_t space_width{ CalculateSpaceWidth() };
			size_t index{ 0 }, lines{ 1 }, max_lines{ (size_t)(0.5 + (double)height / (double)line_height) };
			IFont *font{ getFont() };
			LINE line{ index, index, space_width };
			size_t w;
			while (index < m_sText.length() && lines <= max_lines)
			{
				if (m_sText[index] == L'\r')
				{
					lines++;
					line.Start = line.End = ++index;
					line.Width = space_width;
					continue;
				}
				w = font->getChar(m_sText[index])->Width + font->getDistance();
				if (max_width > 0 && line.Width + w > max_width && line.End - line.Start > 0)
				{
					lines++;
					line.Start = line.End = index;
					line.Width = space_width;
					continue;
				}
				line.End = index;
				line.Width += w;
				index++;
			}
			return lines > max_lines;
		}

		bool CBaseText::getHorizontalScrollRequired(const size_t max_width)
		{
			size_t line_height{ CalculateLineHeight() };
			size_t space_width{ CalculateSpaceWidth() };
			size_t index{ 0 }, width{ 0 };
			IFont *font{ getFont() };
			LINE line{ index, index, space_width };
			size_t w;
			while (index < m_sText.length())
			{
				if (m_sText[index] == L'\r')
				{
					line.Width = space_width;
					index++;
					continue;
				}
				w = font->getChar(m_sText[index])->Width + font->getDistance();
				if (line.Width + w >= max_width)
					return true;
				line.Width += w;
				index++;
			}
			return false;
		}

		size_t CBaseText::getHistoryLimitCount() const
		{
			return m_cHistory.getLimitCount();
		}

		size_t CBaseText::getHistoryLimitSize() const
		{
			return m_cHistory.getLimitSize();
		}
	#pragma endregion

	#pragma region Setters
		bool CBaseText::setVerticalScroll(size_t value)
		{
			if ((size_t)m_sRect.Height() > m_sTextSize.Y)
				value = 0;
			else if (value > m_sTextSize.Y - m_sRect.Height())
				value = m_sTextSize.Y - m_sRect.Height();
			if (value != m_iVerticalScroll)
			{
				m_iVerticalScroll = value;
				return true;
			}
			return false;
		}

		bool CBaseText::setHorizontalScroll(size_t value)
		{
			if ((size_t)m_sRect.Width() > m_sTextSize.X)
				value = 0;
			else if (value > m_sTextSize.X - m_sRect.Width())
				value = m_sTextSize.X - m_sRect.Width();
			if (value != m_iHorizontalScroll)
			{
				m_iHorizontalScroll = value;
				return true;
			}
			return false;
		}

		bool CBaseText::setRect(APP_RECT &rect)
		{
			bool result{ rect.Width() != m_sRect.Width() || rect.Height() != m_sRect.Height() };
			m_sRect = rect;
			return result;
		}

		bool CBaseText::setMaxWidth(const size_t value)
		{
			if (value != m_iMaxWidth)
			{
				m_iMaxWidth = value;
				return true;
			}
			return false;
		}

		bool CBaseText::setLineMargin(const math::POINT<size_t> &value)
		{
			if (value != m_sLineMargin)
			{
				m_sLineMargin = value;
				return true;
			}
			return false;
		}

		bool CBaseText::setLineMarginTop(const size_t value)
		{
			return setLineMargin({ value, m_sLineMargin[1] });
		}

		bool CBaseText::setLineMarginBottom(const size_t value)
		{
			return setLineMargin({ m_sLineMargin[0], value });
		}

		bool CBaseText::setText(const String &value)
		{
			if (m_sText != value)
			{
				m_sText = value;
				CutLength();
				m_cHistory.Store({ m_sText, m_iCaretPosition, m_sSelection }, m_sText.length() * sizeof(wchar_t) + sizeof(HISTORY));
				UpdateLines();
				UpdateTextSize();
				UpdateScrolls();
				return true;
			}
			return false;
		}

		bool CBaseText::setTextColor(const STATE state, const APP_COLOR &value)
		{
			if (m_aTextColor[state] != value)
			{
				m_aTextColor[state] = value;
				if (state == getState())
					return true;
			}
			return false;
		}

		bool CBaseText::setShadowColor(const STATE state, const APP_COLOR &value)
		{
			if (m_aShadowColor[state] != value)
			{
				m_aShadowColor[state] = value;
				if (state == getState())
					return true;
			}
			return false;
		}

		bool CBaseText::setSelectionBackgroundColor(const STATE state, const APP_COLOR &value)
		{
			if (m_aSelectionBackgroundColor[state] != value)
			{
				m_aSelectionBackgroundColor[state] = value;
				if (state == getState())
					return true;
			}
			return false;
		}

		bool CBaseText::setSelectionTextColor(const STATE state, const APP_COLOR &value)
		{
			if (m_aSelectionTextColor[state] != value)
			{
				m_aSelectionTextColor[state] = value;
				if (state == getState())
					return true;
			}
			return false;
		}

		bool CBaseText::setSelectionShadowColor(const STATE state, const APP_COLOR &value)
		{
			if (m_aSelectionShadowColor[state] != value)
			{
				m_aSelectionShadowColor[state] = value;
				if (state == getState())
					return true;
			}
			return false;
		}

		bool CBaseText::setMaxLength(const size_t value)
		{
			if (value != m_iMaxLength)
			{
				m_iMaxLength = value;
				if (m_iMaxLength > 0 && m_sText.length() > m_iMaxLength)
				{
					CutLength();
					UpdateLines();
					UpdateTextSize();
					UpdateScrolls();
					return true;
				}
			}
			return false;
		}

		bool CBaseText::setReadOnly(const bool value)
		{
			if (value != m_bReadOnly)
			{
				m_bReadOnly = value;
				return true;
			}
			return false;
		}

		bool CBaseText::setInserting(const bool value)
		{
			if (value != m_bInserting)
			{
				m_bInserting = value;
				return true;
			}
			return false;
		}

		bool CBaseText::setSelection(math::POINT<size_t> value)
		{
			if (value[0] > m_sText.length())
				value[0] = m_sText.length();
			if (value[1] > m_sText.length())
				value[1] = m_sText.length();
			if (value != m_sSelection)
			{
				m_sSelection = value;
				return true;
			}
			return false;
		}

		bool CBaseText::setCaretPosition(size_t value)
		{
			if (value > m_sText.length())
				value = m_sText.length();
			if (value != m_iCaretPosition)
			{
				m_iCaretPosition = value;
				return true;
			}
			return false;
		}

		bool CBaseText::setDeltaWheelVertical(size_t value)
		{
			if (value == 0)
				value = 1;
			if (value != m_iDeltaWheelVertical)
			{
				m_iDeltaWheelVertical = value;
				return true;
			}
			return false;
		}

		bool CBaseText::setDeltaWheelHorizontal(size_t value)
		{
			if (value == 0)
				value = 1;
			if (value != m_iDeltaWheelHorizontal)
			{
				m_iDeltaWheelHorizontal = value;
				return true;
			}
			return false;
		}

		bool CBaseText::setHistoryLimitCount(const size_t value)
		{
			if (value != m_cHistory.getLimitCount())
			{
				m_cHistory.setLimitCount(value);
				return true;
			}
			return false;
		}

		bool CBaseText::setHistoryLimitSize(const size_t value)
		{
			if (value != m_cHistory.getLimitSize())
			{
				m_cHistory.setLimitSize(value);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Paint
		void CBaseText::Paint(APP_RECT clip)
		{
			APP_RECT rect = ClientToForm(m_sRect);
			// Paint text
			size_t l1{ m_iVerticalScroll / m_iLineHeight }, l2{ l1 + (size_t)(0.5 + (double)m_sRect.Height() / (double)m_iLineHeight) };
			STATE state{ getState() };
			APP_COLOR text{ getFont()->getColor() }, shadow{ getFont()->getShadowColor() };
			if (m_aTextColor[state].getAlpha() > 0)
				text = m_aTextColor[state];
			if (m_aShadowColor[state].getAlpha() > 0)
				shadow = m_aShadowColor[state];
			for (size_t l = l1; l <= l2 && l < m_aLines.size(); l++)
				if (!m_aLines[l].Empty)
					getForm()->getPresenter()->RenderString(
						m_sText.substr(m_aLines[l].Start, m_aLines[l].End - m_aLines[l].Start + 1), getFont(),
						rect.Left - (int)m_iHorizontalScroll, rect.Top + (int)l * (int)m_iLineHeight + (int)m_sLineMargin[0] - (int)m_iVerticalScroll, 0, 1, 1,
						clip, 0, rect, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, 0, graphics::bplInside, true, true, text, shadow, nullptr, nullptr, true);
			// Paint selection
			if (m_sSelection[0] != m_sSelection[1])
			{
				math::POINT<size_t> selection{ std::min(m_sSelection[0], m_sSelection[1]), std::max(m_sSelection[0], m_sSelection[1]) };
				selection[0] = getCaretLine(selection[0]);
				selection[1] = getCaretLine(selection[1]);
				size_t s1{ std::max(l1, selection[0]) };
				size_t s2{ std::min(l2, selection[1]) };
				if (s1 <= l2 && s2 >= l1)
				{
					// Background
					APP_POINT p1, p2;
					APP_RECT r;
					for (size_t l = s1; l <= s2; l++)
						if (!m_aLines[l].Empty)
						{
							if (l == selection[0])
							{
								p1 = CaretToForm(std::min(m_sSelection[0], m_sSelection[1]));
								if (l == selection[1])
									p2 = CaretToForm(std::max(m_sSelection[0], m_sSelection[1]));
								else
									p2 = CaretToForm(m_aLines[l].End + 1);

							}
							else if (l == selection[1])
							{
								p1 = CaretToForm(m_aLines[l].Start);
								p2 = CaretToForm(std::max(m_sSelection[0], m_sSelection[1]));
							}
							else
							{
								p1 = CaretToForm(m_aLines[l].Start);
								p2 = CaretToForm(m_aLines[l].End + 1);
							}
							r = { p1.X, p1.Y, p2.X, p2.Y + (int)m_iLineHeight };
							r *= rect;
							getForm()->getPresenter()->FillRect(m_aSelectionBackgroundColor[state], clip, r, r, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, 0, graphics::bplInside, nullptr, nullptr, true);
						}
					// Text
					for (size_t l = s1; l <= s2 && l < m_aLines.size(); l++)
						if (!m_aLines[l].Empty)
						{
							APP_POINT p1, p2;
							APP_RECT r;
							size_t offset, length;
							if (l == selection[0])
							{
								offset = std::min(m_sSelection[0], m_sSelection[1]) - m_aLines[l].Start;
								p1 = CaretToForm(std::min(m_sSelection[0], m_sSelection[1]));
								if (l == selection[1])
								{
									p2 = CaretToForm(std::max(m_sSelection[0], m_sSelection[1]));
									length = std::max(0, (int)std::max(m_sSelection[0], m_sSelection[1]) - (int)m_aLines[l].Start - (int)offset);
								}
								else
								{
									p2 = CaretToForm(m_aLines[l].End + 1);
									length = std::max(0, (int)m_aLines[l].End - (int)m_aLines[l].Start - (int)offset) + 1;
								}

							}
							else if (l == selection[1])
							{
								offset = 0;
								p1 = CaretToForm(m_aLines[l].Start);
								p2 = CaretToForm(std::max(m_sSelection[0], m_sSelection[1]));
								length = std::max(0, (int)std::max(m_sSelection[0], m_sSelection[1]) - (int)m_aLines[l].Start - (int)offset);
							}
							else
							{
								offset = 0;
								p1 = CaretToForm(m_aLines[l].Start);
								p2 = CaretToForm(m_aLines[l].End + 1);
								length = m_aLines[l].End - m_aLines[l].Start + 1;
							}
							r = { p1.X, p1.Y + (int)m_sLineMargin[0], p2.X, p2.Y + (int)m_iLineHeight - (int)m_sLineMargin[1] };
							String str{ m_sText.substr(m_aLines[l].Start + offset, length) };
							getForm()->getPresenter()->RenderString(str, getFont(), r.Left, r.Top, 0, 1, 1, clip * rect, 0, r, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, 0, graphics::bplInside,
								true, true, m_aSelectionTextColor[state], m_aSelectionShadowColor[state], nullptr, nullptr, true);
						}
				}
			}
		}
	#pragma endregion

	#pragma region Process keyboard events
		bool CBaseText::ProcessInsert()
		{
			m_bInserting = !m_bInserting;
			return true;
		}

		bool CBaseText::ProcessInsertChar(const wchar_t chr)
		{
			if (!m_bReadOnly)
			{
				if (m_sSelection[0] != m_sSelection[1])
					DeleteSelectionInternal();
				if (m_sText.length() > 0 && m_iCaretPosition <= m_sText.length() - 1) // Caret inside text
				{
					m_sText.insert(m_sText.begin() + m_iCaretPosition, chr);
					m_iCaretPosition++;
				}
				else // Caret out of text end
				{
					m_sText += chr;
					m_iCaretPosition = m_sText.length();
				}
				m_sSelection[1] = m_sSelection[0] = m_iCaretPosition;
				CutLength();
				m_cHistory.Store({ m_sText, m_iCaretPosition, m_sSelection }, m_sText.length() * sizeof(wchar_t) + sizeof(HISTORY));
				UpdateLines();
				UpdateTextSize();
				UpdateScrolls();
				return true;
			}
			return false;
		}

		bool CBaseText::ProcessReplaceChar(const wchar_t chr)
		{
			if (!m_bReadOnly)
			{
				if (m_sSelection[0] != m_sSelection[1])
					DeleteSelectionInternal();
				if (m_sText.length() > 0 && m_iCaretPosition <= m_sText.length() - 1) // Caret inside text
				{
					String str{ chr };
					m_sText.replace(m_iCaretPosition, 1, str);
					m_iCaretPosition++;
				}
				else // Caret out of text end
				{
					m_sText += chr;
					m_iCaretPosition = m_sText.length();
				}
				m_sSelection[1] = m_sSelection[0] = m_iCaretPosition;
				m_cHistory.Store({ m_sText, m_iCaretPosition, m_sSelection }, m_sText.length() * sizeof(wchar_t) + sizeof(HISTORY));
				UpdateLines();
				UpdateTextSize();
				UpdateScrolls();
				return true;
			}
			return false;
		}

		bool CBaseText::ProcessMoveFinish(const int x, const int y)
		{
			if (!m_bReadOnly)
			{
				size_t caret{ CursorToCaret(x, y, ClientToForm(m_sRect)) };
				math::POINT<size_t> selection{ std::min(m_sSelection[0], m_sSelection[1]) , std::max(m_sSelection[0], m_sSelection[1]) };
				if (m_sSelection[0] != m_sSelection[1] && (caret < selection[0] || caret > selection[1]))
				{

					String str{ m_sText.substr(selection[0], selection[1] - selection[0]) };
					m_sText.erase(selection[0], selection[1] - selection[0]);
					if (caret > selection[1])
						caret -= selection[1] - selection[0];
					m_sText.insert(caret, str);
					m_iCaretPosition = caret + selection[1] - selection[0];
					m_sSelection[0] = caret;
					m_sSelection[1] = m_iCaretPosition;
					m_cHistory.Store({ m_sText, m_iCaretPosition, m_sSelection }, m_sText.length() * sizeof(wchar_t) + sizeof(HISTORY));
					UpdateLines();
					UpdateTextSize();
					UpdateScrolls();
					return true;
				}
			}
			return false;
		}

		bool CBaseText::ProcessCopyFinish(const int x, const int y)
		{
			if (!m_bReadOnly)
			{
				size_t caret{ CursorToCaret(x, y, ClientToForm(m_sRect)) };
				math::POINT<size_t> selection{ std::min(m_sSelection[0], m_sSelection[1]) , std::max(m_sSelection[0], m_sSelection[1]) };
				if (m_sSelection[0] != m_sSelection[1] && (caret < selection[0] || caret > selection[1]))
				{

					String str{ m_sText.substr(selection[0], selection[1] - selection[0]) };
					m_sText.insert(caret, str);
					m_iCaretPosition = caret + selection[1] - selection[0];
					m_sSelection[0] = caret;
					m_sSelection[1] = m_iCaretPosition;
					CutLength();
					m_cHistory.Store({ m_sText, m_iCaretPosition, m_sSelection }, m_sText.length() * sizeof(wchar_t) + sizeof(HISTORY));
					UpdateLines();
					UpdateTextSize();
					UpdateScrolls();
					return true;
				}
			}
			return false;
		}
	#pragma endregion
	}
}