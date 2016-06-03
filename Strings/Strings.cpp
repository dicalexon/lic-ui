// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#include "Strings.h"
#include <codecvt>
#include <sstream>
#include <ctime>

namespace licui
{
#pragma region String type conversion functions
	AnsiString StringToAnsi(const String &str, const char replacer)
	{
		std::vector<char> buffer(str.size());
		std::use_facet<std::ctype<wchar_t>>(std::locale()).narrow(str.data(), str.data() + str.size(), replacer, buffer.data());
		return AnsiString(buffer.data(), buffer.size());
	}

	UTF8String StringToUTF8(const String &str)
	{
		std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
		return converter.to_bytes(str);
	}

	String AnsiToString(const AnsiString &str)
	{
		std::vector<wchar_t> buffer(str.size());
		std::use_facet<std::ctype<wchar_t>>(std::locale()).widen(str.data(), str.data() + str.size(), buffer.data());
		return String(buffer.data(), buffer.size());
	}

	String UTF8ToString(const UTF8String &str)
	{
		std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
		return converter.from_bytes(str);
	}
#pragma endregion

#pragma region Try convert strings to numerical values
	bool TryStringToInt(const String &str, int &out)
	{
		try
		{
			int r = std::stoi(str);
			out = r;
			return true;
		}
		catch (...)
		{
			return false;
		}
	}

	bool TryStringToUInt(const String &str, unsigned int &out)
	{
		try
		{
			unsigned int r = std::stoul(str);
			out = r;
			return true;
		}
		catch (...)
		{
			return false;
		}
	}

	bool TryStringToInt64(const String &str, __int64 &out)
	{
		try
		{
			__int64 r = std::stoll(str);
			out = r;
			return true;
		}
		catch (...)
		{
			return false;
		}
	}

	bool TryStringToUInt64(const String &str, unsigned __int64 &out)
	{
		try
		{
			unsigned __int64 r = std::stoull(str);
			out = r;
			return true;
		}
		catch (...)
		{
			return false;
		}
	}

	bool TryStringToFloat(const String &str, float &out)
	{
		try
		{
			float r = std::stof(str);
			out = r;
			return true;
		}
		catch (...)
		{
			return false;
		}
	}

	bool TryStringToDouble(const String &str, double &out)
	{
		try
		{
			double r = std::stod(str);
			out = r;
			return true;
		}
		catch (...)
		{
			return false;
		}
	}

	bool TryAnsiToInt(const AnsiString &str, int &out)
	{
		try
		{
			int r = std::stoi(str);
			out = r;
			return true;
		}
		catch (...)
		{
			return false;
		}
	}

	bool TryAnsiToUInt(const AnsiString &str, unsigned int &out)
	{
		try
		{
			unsigned int r = std::stoul(str);
			out = r;
			return true;
		}
		catch (...)
		{
			return false;
		}
	}

	bool TryAnsiToInt64(const AnsiString &str, __int64 &out)
	{
		try
		{
			__int64 r = std::stoll(str);
			out = r;
			return true;
		}
		catch (...)
		{
			return false;
		}
	}

	bool TryAnsiToUInt64(const AnsiString &str, unsigned __int64 &out)
	{
		try
		{
			unsigned __int64 r = std::stoull(str);
			out = r;
			return true;
		}
		catch (...)
		{
			return false;
		}
	}

	bool TryAnsiToFloat(const AnsiString &str, float &out)
	{
		try
		{
			float r = std::stof(str);
			out = r;
			return true;
		}
		catch (...)
		{
			return false;
		}
	}

	bool TryAnsiToDouble(const AnsiString &str, double &out)
	{
		try
		{
			double r = std::stod(str);
			out = r;
			return true;
		}
		catch (...)
		{
			return false;
		}
	}
#pragma endregion

#pragma region Formatting
	String Extend(const String &str, const size_t size, const wchar_t sym)
	{
		if (size == 0 || str.length() >= size)
			return str;
		String result(str);
		result.resize(size, sym);
		return result;
	}

	AnsiString Extend(const AnsiString &str, const size_t size, const char sym)
	{
		if (size == 0 || str.length() >= size)
			return str;
		AnsiString result(str);
		result.resize(size, sym);
		return result;
	}

	String Replace(const String &str, const String &search, const String &replace)
	{
		size_t pos = str.find(search, 0);
		if (pos == String::npos)
			return str;
		String result(str);
		result.replace(pos, search.length(), replace);
		return result;
	}

	AnsiString Replace(const AnsiString &str, const AnsiString &search, const AnsiString &replace)
	{
		size_t pos = str.find(search, 0);
		if (pos == AnsiString::npos)
			return str;
		AnsiString result(str);
		result.replace(pos, search.length(), replace);
		return result;
	}

	void ReplaceDirect(String &str, const String &search, const String &replace)
	{
		size_t pos = str.find(search, 0);
		if (pos == String::npos)
			return;
		str.replace(pos, search.length(), replace);
	}

	void ReplaceDirect(AnsiString &str, const AnsiString &search, const AnsiString &replace)
	{
		size_t pos = str.find(search, 0);
		if (pos == String::npos)
			return;
		str.replace(pos, search.length(), replace);
	}

	String ReplaceAll(const String &str, const String &search, const String &replace)
	{
		size_t pos = str.find(search, 0);
		if (pos == String::npos)
			return str;
		String result(str);
		do
		{
			result.replace(pos, search.length(), replace);
			pos = str.find(search, pos + replace.length() + 1);
		} while (pos != String::npos);
		return result;
	}

	AnsiString ReplaceAll(const AnsiString &str, const AnsiString &search, const AnsiString &replace)
	{
		size_t pos = str.find(search, 0);
		if (pos == AnsiString::npos)
			return str;
		AnsiString result(str);
		do
		{
			result.replace(pos, search.length(), replace);
			pos = str.find(search, pos + replace.length() + 1);
		} while (pos != AnsiString::npos);
		return result;
	}

	void ReplaceAllDirect(String &str, const String &search, const String &replace)
	{
		size_t pos = str.find(search, 0);
		if (pos == String::npos)
			return;
		do
		{
			str.replace(pos, search.length(), replace);
			pos = str.find(search, pos + replace.length() + 1);
		} while (pos != String::npos);
	}

	void ReplaceAllDirect(AnsiString &str, const AnsiString &search, const AnsiString &replace)
	{
		size_t pos = str.find(search, 0);
		if (pos == AnsiString::npos)
			return;
		do
		{
			str.replace(pos, search.length(), replace);
			pos = str.find(search, pos + replace.length() + 1);
		} while (pos != AnsiString::npos);
	}

	String TrimRight(const String &str, const std::locale &locale)
	{
		if (str.length() == 0)
			return str;
		size_t last;
		for (last = str.length() - 1; last >= 0; last--)
			if (!std::isspace(str[last], locale))
				break;
		if (last == str.length() - 1)
			return str;
		return str.substr(0, last + 1);
	}

	AnsiString TrimRight(const AnsiString &str, const std::locale &locale)
	{
		if (str.length() == 0)
			return str;
		size_t last;
		for (last = str.length() - 1; last >= 0; last--)
			if (!std::isspace(str[last], locale))
				break;
		if (last == str.length() - 1)
			return str;
		return str.substr(0, last + 1);
	}

	void TrimRightDirect(String &str, const std::locale &locale)
	{
		if (str.length() == 0)
			return;
		size_t last;
		for (last = str.length() - 1; last >= 0; last--)
			if (!std::isspace(str[last], locale))
				break;
		if (last == str.length() - 1)
			return;
		str.erase(last + 1, str.length() - last + 1);
	}

	void TrimRightDirect(AnsiString &str, const std::locale &locale)
	{
		if (str.length() == 0)
			return;
		size_t last;
		for (last = str.length() - 1; last >= 0; last--)
			if (!std::isspace(str[last], locale))
				break;
		if (last == str.length() - 1)
			return;
		str.erase(last + 1, str.length() - last + 1);
	}

	String TrimLeft(const String &str, const std::locale &locale)
	{
		if (str.length() == 0)
			return str;
		size_t first;
		for (first = 0; first < str.length(); first++)
			if (!std::isspace(str[first], locale))
				break;
		if (first == 0)
			return str;
		return str.substr(first);
	}

	AnsiString TrimLeft(const AnsiString &str, const std::locale &locale)
	{
		if (str.length() == 0)
			return str;
		size_t first;
		for (first = 0; first < str.length(); first++)
			if (!std::isspace(str[first], locale))
				break;
		if (first == 0)
			return str;
		return str.substr(first);
	}

	void TrimLeftDirect(String &str, const std::locale &locale)
	{
		if (str.length() == 0)
			return;
		size_t first;
		for (first = 0; first < str.length(); first++)
			if (!std::isspace(str[first], locale))
				break;
		if (first == 0)
			return;
		str.erase(0, first);
	}

	void TrimLeftDirect(AnsiString &str, const std::locale &locale)
	{
		if (str.length() == 0)
			return;
		size_t first;
		for (first = 0; first < str.length(); first++)
			if (!std::isspace(str[first], locale))
				break;
		if (first == 0)
			return;
		str.erase(0, first);
	}

	String Trim(const String &str, const std::locale &locale)
	{
		if (str.length() == 0)
			return str;
		size_t first;
		for (first = 0; first < str.length(); first++)
			if (!std::isspace(str[first], locale))
				break;
		size_t last;
		for (last = str.length() - 1; last >= 0; last--)
			if (!std::isspace(str[last], locale))
				break;
		if (last < first)
			return L"";
		return str.substr(first, last - first + 1);
	}

	AnsiString Trim(const AnsiString &str, const std::locale &locale)
	{
		if (str.length() == 0)
			return str;
		size_t first;
		for (first = 0; first < str.length(); first++)
			if (!std::isspace(str[first], locale))
				break;
		size_t last;
		for (last = str.length() - 1; last >= 0; last--)
			if (!std::isspace(str[last], locale))
				break;
		if (last < first)
			return "";
		return str.substr(first, last - first + 1);
	}

	void TrimDirect(String &str, const std::locale &locale)
	{
		if (str.length() == 0)
			return;
		size_t first;
		for (first = 0; first < str.length(); first++)
			if (!std::isspace(str[first], locale))
				break;
		size_t last;
		for (last = str.length() - 1; last >= 0; last--)
			if (!std::isspace(str[last], locale))
				break;
		if (last < first)
		{
			str.clear();
			return;
		}
		str = str.substr(first, last - first + 1);
	}

	void TrimDirect(AnsiString &str, const std::locale &locale)
	{
		if (str.length() == 0)
			return;
		size_t first;
		for (first = 0; first < str.length(); first++)
			if (!std::isspace(str[first], locale))
				break;
		size_t last;
		for (last = str.length() - 1; last >= 0; last--)
			if (!std::isspace(str[last], locale))
				break;
		if (last < first)
		{
			str.clear();
			return;
		}
		str = str.substr(first, last - first + 1);
	}

	String FormatDateTime(const String &format, const tm datetime, const std::locale &locale)
	{
		std::basic_stringstream<wchar_t> stream;
		std::use_facet<std::time_put<wchar_t>>(locale).put(std::basic_ostream<wchar_t>::_Iter(stream.rdbuf()), stream, L' ', &datetime, format.data(), format.data() + format.length());
		return stream.rdbuf()->str();
	}

	AnsiString FormatDateTime(const AnsiString &format, const tm datetime, const std::locale &locale)
	{
		std::basic_stringstream<char> stream;
		std::use_facet<std::time_put<char>>(locale).put(std::basic_ostream<char>::_Iter(stream.rdbuf()), stream, ' ', &datetime, format.data(), format.data() + format.length());
		return stream.rdbuf()->str();
	}

	bool ParseDateTime(const String &str, tm &out, const String &format, const std::locale &locale)
	{
		std::basic_stringstream<wchar_t> stream(str);
		std::ios_base::iostate state = std::ios_base::goodbit;
		std::use_facet<std::time_get<wchar_t>>(locale).get(std::basic_istream<wchar_t>::_Iter(stream.rdbuf()), std::istreambuf_iterator<wchar_t>(), stream, state, &out, format.data(), format.data() + format.length());
		return state == std::ios_base::goodbit || state == std::ios_base::eofbit;
	}

	bool ParseDateTime(const AnsiString &str, tm &out, const AnsiString &format, const std::locale &locale)
	{
		std::basic_stringstream<char> stream(str);
		std::ios_base::iostate state = std::ios_base::goodbit;
		std::use_facet<std::time_get<char>>(locale).get(std::basic_istream<char>::_Iter(stream.rdbuf()), std::istreambuf_iterator<char>(), stream, state, &out, format.data(), format.data() + format.length());
		return state == std::ios_base::goodbit || state == std::ios_base::eofbit;
	}

	void Explode(const String &str, const String &delimiter, std::vector<String> &out, const bool remove_empty)
	{
		out.clear();
		if (str.empty())
		{
			if (!remove_empty)
				out.push_back(str);
			return;
		}
		if (delimiter.empty())
		{
			out.push_back(str);
			return;
		}
		size_t first = 0, last;
		do
		{
			last = str.find(delimiter, first);
			if (last == String::npos)
				last = str.length();
			last--;
			if (last >= first || (last == first - 1 && !remove_empty))
				out.push_back(str.substr(first, last - first + 1));
			first = last + delimiter.length() + 1;
		} while (last < str.length() - 1);
	}

	void Explode(const AnsiString &str, const AnsiString &delimiter, std::vector<AnsiString> &out, const bool remove_empty)
	{
		out.clear();
		if (str.empty())
		{
			if (!remove_empty)
				out.push_back(str);
			return;
		}
		if (delimiter.empty())
		{
			out.push_back(str);
			return;
		}
		size_t first = 0, last;
		do
		{
			last = str.find(delimiter, first);
			if (last == AnsiString::npos)
				last = str.length();
			last--;
			if (last >= first || (last == first - 1 && !remove_empty))
				out.push_back(str.substr(first, last - first + 1));
			first = last + delimiter.length() + 1;
		} while (last < str.length() - 1);
	}

	String ToUpper(const String &str, const std::locale &locale)
	{
		String result = str;
		for (wchar_t &c : result)
			c = std::use_facet<std::ctype<wchar_t>>(locale).toupper(c);
		return result;
	}

	AnsiString ToUpper(const AnsiString &str, const std::locale &locale)
	{
		AnsiString result = str;
		for (char &c : result)
			c = std::use_facet<std::ctype<char>>(locale).toupper(c);
		return result;
	}

	void ToUpperDirect(String &str, const std::locale &locale)
	{
		for (wchar_t &c : str)
			c = std::use_facet<std::ctype<wchar_t>>(locale).toupper(c);
	}

	void ToUpperDirect(AnsiString &str, const std::locale &locale)
	{
		for (char &c : str)
			c = std::use_facet<std::ctype<char>>(locale).toupper(c);
	}

	String ToLower(const String &str, const std::locale &locale)
	{
		String result = str;
		for (wchar_t &c : result)
			c = std::use_facet<std::ctype<wchar_t>>(locale).tolower(c);
		return result;
	}

	AnsiString ToLower(const AnsiString &str, const std::locale &locale)
	{
		AnsiString result = str;
		for (char &c : result)
			c = std::use_facet<std::ctype<char>>(locale).tolower(c);
		return result;
	}

	void ToLowerDirect(String &str, const std::locale &locale)
	{
		for (wchar_t &c : str)
			c = std::use_facet<std::ctype<wchar_t>>(locale).tolower(c);
	}

	void ToLowerDirect(AnsiString &str, const std::locale &locale)
	{
		for (char &c : str)
			c = std::use_facet<std::ctype<char>>(locale).tolower(c);
	}

	std::vector<String> Explode(const String &str, const String &delimiter, const bool remove_empty)
	{
		std::vector<String> result;
		Explode(str, delimiter, result, remove_empty);
		return result;
	}

	std::vector<AnsiString> Explode(const AnsiString &str, const AnsiString &delimiter, const bool remove_empty)
	{
		std::vector<AnsiString> result;
		Explode(str, delimiter, result, remove_empty);
		return result;
	}
#pragma endregion

#pragma region Searching
	size_t SearchNextWord(const String &str, const size_t start, const bool with_punct, const std::locale &locale)
	{
		if (start >= str.length())
			return str.length();
		auto test{ with_punct ? std::isgraph<wchar_t> : std::isalnum<wchar_t> };
		size_t result{ start + 1 };
		if (test(str[result], locale)) // If current position is inside word, find first position outside word
			while (result < str.length() && test(str[result], locale))
				result++;
		while (result < str.length() && (!test(str[result], locale) || std::isspace(str[result], locale))) // Find first word char
			result++;
		return result;
	}

	size_t SearchPrevWord(const String &str, const size_t start, const bool with_punct, const std::locale &locale)
	{
		if (str.length() == 0)
			return 0;
		size_t result{ start };
		if (start > str.length())
			result = str.length();
		if (result > 0)
			result--;
		auto test{ with_punct ? std::isgraph<wchar_t> : std::isalnum<wchar_t> };
		if (!test(str[result], locale)) // If current position is outside word, find first position inside word
			while (result > 0 && (!test(str[result], locale) || std::isspace(str[result], locale)))
				result--;
		while (result > 0 && test(str[result - 1], locale)) // Find first word char
			result--;
		return result;
	}
#pragma endregion
}