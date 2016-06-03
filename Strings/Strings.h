// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#pragma once

#include <string>
#include <locale>
#include <vector>

namespace licui
{
#pragma region String declarations
	typedef std::wstring String;
	typedef std::string AnsiString;
	typedef std::string UTF8String;
#pragma endregion

#pragma region String type convertion functions
	/**
	Convert wide character string to ansi string
	@param str Wide character string
	@param replacer When unsupported by ansi string char is found, it will be replaced with this one. Default '?'
	@return Ansi string
	*/
	AnsiString StringToAnsi(const String &str, const char replacer = '?');

	/**
	Convert wide character string to utf-8 encoded string
	@param str Wide character string
	@return UTF-8 encoded string
	*/
	UTF8String StringToUTF8(const String &str);

	/**
	Convert ansi string to wide chcracter string
	@param str Ansi string
	@return Wide character string
	*/
	String AnsiToString(const AnsiString &str);

	/**
	Convert ansi string to utf-8 encoded string
	@param str Ansi string
	@return UTF8 encoded string
	*/
	inline UTF8String AnsiToUTF8(const AnsiString &str);

	/**
	Convert utf-8 encoded string to wide character string
	@param str UTF-8 encoded string
	@return Wide character string
	*/
	String UTF8ToString(const UTF8String &str);

	/**
	Convert utf-8 encoded string to ansi string
	@param str UTF-8 encoded string
	@return Ansi string
	*/
	inline AnsiString UTF8ToAnsi(const UTF8String &str);
#pragma endregion

#pragma region Conversions between strings and numerical values
	/**
	Convert string to int
	@param str Wide character string
	@return integer value or throw excpetion if convertion failed
	*/
	inline int StringToInt(const String &str);

	/**
	Convert ansi string to int
	@param str Ansi string
	@return integer value or throw exception if conversion failed
	*/
	inline int StringToInt(const AnsiString &str);

	/**
	Convert string to unsigned int
	@param str Wide character string
	@return unsigned int or throw exception if conversion failed
	*/
	inline unsigned int StringToUInt(const String &str);

	/**
	Convert ansi string to unsigned int
	@param str Ansi string
	@return unsigned int or throw exception if conversion failed
	*/
	inline unsigned int StringToUInt(const AnsiString &str);

	/**
	Convert string to Int64
	@param str Wide character string
	@returns 64-bit integer or throw exception if conversion failed
	*/
	inline __int64 StringToInt64(const String &str);

	/**
	Convert ansi string to Int64
	@param str Ansi string
	@return 64-bit integer or throw exception if conversion failed
	*/
	inline __int64 StringToInt64(const AnsiString &str);

	/**
	Convert string to unsigned Int64
	@param str Wide character string
	@return unsigned 64-bit integer or throw exception if conversion failed
	*/
	inline unsigned __int64 StringToUInt64(const String &str);

	/**
	Convert ansi string to unsigned Int64
	@param str Ansi string
	@return unsigned 64-bit integer or throw exception if conversion failed
	*/
	inline unsigned __int64 StringToUInt64(const AnsiString &str);

	/**
	Convert string to float
	@param str Wide character string
	@return float value or throw exception if conversion failed
	*/
	inline float StringToFloat(const String &str);

	/**
	Convert ansi string to float
	@param str Ansi string
	@return float value or throw exception if conversion failed
	*/
	inline float StringToFloat(const AnsiString &str);

	/**
	Convert string to double
	@param str Wide character string
	@return double value or throw exception if conversion failed
	*/
	inline double StringToDouble(const String &str);

	/**
	Convert ansi string to double
	@param str Ansi string
	@return double value or throw exception if conversion failed
	*/
	inline double StringToDouble(const AnsiString &str);

	/**
	Convert int to string
	@param value Integer value
	@return Wide character string
	*/
	inline String ToString(const int value);

	/**
	Convert unsigned int to string
	@param value Unsigned integer value
	@return Wide character string
	*/
	inline String ToString(const unsigned int value);

	/**
	Convert Int64 to string
	@param value 64-bit integer
	@return Wide character string
	*/
	inline String ToString(const __int64 value);

	/**
	Convert unsigned Int64 to string
	@param value Unsigned 64-bit integer
	@return Wide character string
	*/
	inline String ToString(const unsigned __int64 value);

	/**
	Convert float to string
	@param value Float value
	@return Wide character string
	*/
	inline String ToString(const float value);

	/**
	Convert double to string
	@param value Double value
	@return Wide character string
	*/
	inline String ToString(const double value);

	/**
	Convert int to ansi string
	@param value Integer value
	@return Ansi string
	*/
	inline AnsiString ToAnsi(const int value);

	/**
	Convert unsigned int to ansi string
	@param value Unsigned integer value
	@return Ansi string
	*/
	inline AnsiString ToAnsi(const unsigned int value);

	/**
	Convert Int64 to ansi string
	@param value 64-bit integer value
	@return Ansi string
	*/
	inline AnsiString ToAnsi(const __int64 value);

	/**
	Convert unsigned Int64 to ansi string
	@param value Unsigned 64-bit value
	@return Ansi string
	*/
	inline AnsiString ToAnsi(const unsigned __int64 value);

	/**
	Convert float to ansi string
	@param value Float value
	@return Ansi string
	*/
	inline AnsiString ToAnsi(const float value);

	/**
	Convert double to ansi string
	@param value Double value
	@return Ansi string
	*/
	inline AnsiString ToAnsi(const double value);

	/**
	Try convert string to int
	@param str Wide character string
	@param[out] out Reference to integer where to store result of conversion
	@return True if conversion succeeded, otherwise - false
	*/
	bool TryStringToInt(const String &str, int &out);

	/**
	Try convert string to unsigned int
	@param str Wide character string
	@param[out] out Reference to unsigned integer where to store result of conversion
	@return True if conversion succeeded, otherwise - false
	*/
	bool TryStringToUInt(const String &str, unsigned int &out);

	/**
	Try convert string to Int64
	@param str Wide character string
	@param[out] out Reference to 64-bit integer where to store result of conversion
	@return True if conversion succeeded, otherwise - false
	*/
	bool TryStringToInt64(const String &str, __int64 &out);

	/**
	Try convert string to unsigned Int64
	@param str Wide character string
	@param[out] out Reference to unsigned 64-bit integer where to store result of conversion
	@return True if conversion succeeded, otherwise - false
	*/
	bool TryStringToUInt64(const String &str, unsigned __int64 &out);

	/**
	Try convert string to float
	@param str Wide character string
	@param[out] out Reference to float where to store result of conversion
	@return True if conversion succeeded, otherwise - false
	*/
	bool TryStringToFloat(const String &str, float &out);

	/**
	Try convert string to double
	@param str Wide character string
	@param[out] out Reference to double where to store result of conversion
	@return True if conversion succeeded, otherwise - false
	*/
	bool TryStringToDouble(const String &str, double &out);

	/**
	Try convert ansi string to int
	@param str Ansi string
	@param[out] out Reference to integer where to store result of conversion
	@return True if conversion succeeded, otherwise - false
	*/
	bool TryAnsiToInt(const AnsiString &str, int &out);

	/**
	Try convert ansi string to unsigned int
	@param str Ansi string
	@param[out] out Reference to unsigned integer where to store result of conversion
	@return True if conversion succeeded, otherwise - false
	*/
	bool TryAnsiToUInt(const AnsiString &str, unsigned int &out);

	/**
	Try convert ansi string to Int64
	@param str Ansi string
	@param[out] out Reference to 64-bit integer where to store result of conversion
	@return True if conversion succeeded, otherwise - false
	*/
	bool TryAnsiToInt64(const AnsiString &str, __int64 &out);

	/**
	Try convert ansi string to unsigned Int64
	@param str Ansi string
	@param[out] out Reference to unsigned 64-bit integer where to store result of conversion
	@return True if conversion succeeded, otherwise - false
	*/
	bool TryAnsiToUInt64(const AnsiString &str, unsigned __int64 &out);

	/**
	Try convert ansi string to float
	@param str Ansi string
	@param[out] out Reference to float where to store result of conversion
	@return True if conversion succeeded, otherwise - false
	*/
	bool TryAnsiToFloat(const AnsiString &str, float &out);

	/**
	Try convert ansi string to double
	@param str Ansi string
	@param[out] out Reference to double where to store result of conversion
	@return True if conversion succeeded, otherwise - false
	*/
	bool TryAnsiToDouble(const AnsiString &str, double &out);
#pragma endregion

#pragma region Formatting
	/**
	Extend string to specified length with specified character
	@param str Wide character string
	@param size Required string size
	@param sym Character used to extend string
	@return Wide character string with length size or greater(if str size was greater than size)
	*/
	String Extend(const String &str, const size_t size, const wchar_t sym);

	/**
	Extend ansi string to specified length with specified character
	@param str Ansi string
	@param size Required string size
	@param sym Character used to extend string
	@return Ansi string with length size or greater(if str size was greater than size)
	*/
	AnsiString Extend(const AnsiString &str, const size_t size, const char sym);

	/**
	Replace first occurance of substring "search" in string "str" on substring "replace" and return new string
	@param str String where to search
	@param search Searching string
	@param replace String to replace with
	@return String where first occurance of "search" is replaced with "replace"
	*/
	String Replace(const String &str, const String &search, const String &replace);

	/**
	Replace first occurance of substring "search" in ansi string "str" on substring "replace" and return new ansi string
	@param str String where to search
	@param search Searching string
	@param replace String to replace with
	@return String where first occurance of "search" is replaced with "replace"
	*/
	AnsiString Replace(const AnsiString &str, const AnsiString &search, const AnsiString &replace);

	/**
	Replace first occurance of substring "search" in string "str" on substring "replace"
	@param[in, out] str String where to search and replace
	@param search Searching string
	@param replace String to replace with
	*/
	void ReplaceDirect(String &str, const String &search, const String &replace);

	/**
	Replace first occurance of substring "search" in ansi string "str" on substring "replace"
	@param[in, out] str String where to search and replace
	@param search Searching string
	@param replace String to replace with
	*/
	void ReplaceDirect(AnsiString &str, const AnsiString &search, const AnsiString &replace);

	/**
	Replace all occurances of substring "search" in string "str" on substring "replace" and return new string
	@param str String where to search
	@param search Searching string
	@param replace String to replace with
	@return String where all occurances of "search" is replaced with "replace"
	*/
	String ReplaceAll(const String &str, const String &search, const String &replace);

	/**
	Replace all occurances of substring "search" in ansi string "str" on substring "replace" and return new ansi string
	@param str String where to search
	@param search Searching string
	@param replace String to replace with
	@return String where all occurances of "search" is replaced with "replace"
	*/
	AnsiString ReplaceAll(const AnsiString &str, const AnsiString &search, const AnsiString &replace);

	/**
	Replace all occurances of substring "search" in string "str" on substring "replace"
	@param[in, out] str String where to search and replace
	@param search Searching string
	@param replace String to replace with
	*/
	void ReplaceAllDirect(String &str, const String &search, const String &replace);

	/**
	Replace all occurances of substring "search" in ansi string "str" on substring "replace"
	@param[in, out] str String where to search and replace
	@param search Searching string
	@param replace String to replace with
	*/
	void ReplaceAllDirect(AnsiString &str, const AnsiString &search, const AnsiString &replace);

	/**
	Remove spaces at the end of string and return new one
	@param str String where to search spaces
	@param local Locale used for search. Default is current locale
	@return String with removed spaces from end
	*/
	String TrimRight(const String &str, const std::locale &locale = std::locale());

	/**
	Remove spaces at the end of ansi string and return new one
	@param str String where to search spaces
	@param local Locale used for search. Default is current locale
	@return String with removed spaces from end
	*/
	AnsiString TrimRight(const AnsiString &str, const std::locale &locale = std::locale());

	/**
	Remove spaces at the end of string
	@param[in, out] str String where to search and remove spaces
	@param local Locale used for search. Default is current locale
	*/
	void TrimRightDirect(String &str, const std::locale &locale = std::locale());

	/**
	Remove spaces at the end of ansi string
	@param[in, out] str String where to and remove search spaces
	@param local Locale used for search. Default is current locale
	*/
	void TrimRightDirect(AnsiString &str, const std::locale &locale = std::locale());

	/**
	Remove spaces at the beggining of string and return new one
	@param str String where to search spaces
	@param local Locale used for search. Default is current locale
	@return String with removed spaces from beginning
	*/
	String TrimLeft(const String &str, const std::locale &locale = std::locale());

	/**
	Remove spaces at the beggining of ansi string and return new one
	@param str String where to search spaces
	@param local Locale used for search. Default is current locale
	@return String with removed spaces from beginning
	*/
	AnsiString TrimLeft(const AnsiString &str, const std::locale &locale = std::locale());

	/**
	Remove spaces at the beggining of string
	@param[in, out] str String where to search and remove spaces
	@param local Locale used for search. Default is current locale
	*/
	void TrimLeftDirect(String &str, const std::locale &locale = std::locale());

	/**
	Remove spaces at the beggining of ansi string
	@param[in, out] str String where to search and remove spaces
	@param local Locale used for search. Default is current locale
	*/
	void TrimLeftDirect(AnsiString &str, const std::locale &locale = std::locale());

	/**
	Remove spaces both at the beggining and at the end of string and return new one
	@param str String where to search spaces
	@param local Locale used for search. Default is current locale
	@return String with removed spaces from beginning and end
	*/
	String Trim(const String &str, const std::locale &locale = std::locale());

	/**
	Remove spaces both at the beggining and at the end of ansi string and return new one
	@param str String where to search spaces
	@param local Locale used for search. Default is current locale
	@return String with removed spaces from beginning and end
	*/
	AnsiString Trim(const AnsiString &str, const std::locale &locale = std::locale());

	/**
	Remove spaces both at the beggining and at the end of string
	@param[in, out] str String where to search and remove spaces
	@param local Locale used for search. Default is current locale
	*/
	void TrimDirect(String &str, const std::locale &locale = std::locale());

	/**
	Remove spaces both at the beggining and at the end of ansi string
	@param[in, out] str String where to search and remove spaces
	@param local Locale used for search. Default is current locale
	*/
	void TrimDirect(AnsiString &str, const std::locale &locale = std::locale());

	/**
	Format datetime to specified format and return as string
	@param format Format in which datetime should be output
	@param  datetime Datetime structure
	@param locale Locale used for formatting. Default is current one
	@return Formatted string datetime reprecentation

	@para Possible formats:
		- \%a Abbreviated weekday name
		- \%A Full weekday name
		- \%b Abbreviated month name
		- \%B Full month name
		- \%c Date and time representation appropriate for locale
		- \%d Day of month as decimal number (01 - 31)
		- \%H Hour in 24-hour format (00 - 23)
		- \%I Hour in 12-hour format (01 - 12)
		- \%j Day of year as decimal number (001 - 366)
		- \%m Month as decimal number (01 - 12)
		- \%M Minute as decimal number (00 - 59)
		- \%p Current locale's A.M./P.M. indicator for 12-hour clock
		- \%S Second as decimal number (00 - 59)
		- \%U Week of year as decimal number, with Sunday as first day of week (00 - 53)
		- \%w Weekday as decimal number (0 - 6; Sunday is 0)
		- \%W Week of year as decimal number, with Monday as first day of week (00 - 53)
		- \%x Date representation for current locale
		- \%X Time representation for current locale
		- \%y Year without century, as decimal number (00 - 99)
		- \%Y Year with century, as decimal number
		- \%z, %Z Either the time-zone name or time zone abbreviation, depending on registry settings; no characters if time zone is unknown
		- \%\% Percent sign
	*/
	String FormatDateTime(const String &format, const tm datetime, const std::locale &locale = std::locale());

	/**
	Format datetime to specified format and return as ansi string
	@param format Format in which datetime should be output
	@param  datetime Datetime structure
	@param locale Locale used for formatting. Default is current one
	@return Formatted string datetime reprecentation

	@para Possible formats:
	- \%a Abbreviated weekday name
	- \%A Full weekday name
	- \%b Abbreviated month name
	- \%B Full month name
	- \%c Date and time representation appropriate for locale
	- \%d Day of month as decimal number (01 - 31)
	- \%H Hour in 24-hour format (00 - 23)
	- \%I Hour in 12-hour format (01 - 12)
	- \%j Day of year as decimal number (001 - 366)
	- \%m Month as decimal number (01 - 12)
	- \%M Minute as decimal number (00 - 59)
	- \%p Current locale's A.M./P.M. indicator for 12-hour clock
	- \%S Second as decimal number (00 - 59)
	- \%U Week of year as decimal number, with Sunday as first day of week (00 - 53)
	- \%w Weekday as decimal number (0 - 6; Sunday is 0)
	- \%W Week of year as decimal number, with Monday as first day of week (00 - 53)
	- \%x Date representation for current locale
	- \%X Time representation for current locale
	- \%y Year without century, as decimal number (00 - 99)
	- \%Y Year with century, as decimal number
	- \%z, %Z Either the time-zone name or time zone abbreviation, depending on registry settings; no characters if time zone is unknown
	- \%\% Percent sign
	*/
	AnsiString FormatDateTime(const AnsiString &format, const tm datetime, const std::locale &locale = std::locale());

	/**
	Parse string for specified datetime format and return true if successfully parsed or false otherwise
	@param str String for parsing
	@param[out] out Datetime structure where to store result
	@param format Expected format. Default is "%Y-%m-%d %H:%M:%S"
	@param locale Locale used for parsing. Default is current one
	@return True is successfully parsed, otherwise - false

	@para Possible formats:
	- \%a Abbreviated weekday name
	- \%A Full weekday name
	- \%b Abbreviated month name
	- \%B Full month name
	- \%c Date and time representation appropriate for locale
	- \%d Day of month as decimal number (01 - 31)
	- \%H Hour in 24-hour format (00 - 23)
	- \%I Hour in 12-hour format (01 - 12)
	- \%j Day of year as decimal number (001 - 366)
	- \%m Month as decimal number (01 - 12)
	- \%M Minute as decimal number (00 - 59)
	- \%p Current locale's A.M./P.M. indicator for 12-hour clock
	- \%S Second as decimal number (00 - 59)
	- \%U Week of year as decimal number, with Sunday as first day of week (00 - 53)
	- \%w Weekday as decimal number (0 - 6; Sunday is 0)
	- \%W Week of year as decimal number, with Monday as first day of week (00 - 53)
	- \%x Date representation for current locale
	- \%X Time representation for current locale
	- \%y Year without century, as decimal number (00 - 99)
	- \%Y Year with century, as decimal number
	- \%z, %Z Either the time-zone name or time zone abbreviation, depending on registry settings; no characters if time zone is unknown
	- \%\% Percent sign
	*/
	bool ParseDateTime(const String &str, tm &out, const String &format = L"%Y-%m-%d %H:%M:%S", const std::locale &locale = std::locale());

	/**
	Parse ansi string for specified datetime format and return true if successfully parsed or false otherwise
	@param str String for parsing
	@param[out] out Datetime structure where to store result
	@param format Expected format. Default is "%Y-%m-%d %H:%M:%S"
	@param locale Locale used for parsing. Default is current one
	@return True is successfully parsed, otherwise - false

	@para Possible formats:
	- \%a Abbreviated weekday name
	- \%A Full weekday name
	- \%b Abbreviated month name
	- \%B Full month name
	- \%c Date and time representation appropriate for locale
	- \%d Day of month as decimal number (01 - 31)
	- \%H Hour in 24-hour format (00 - 23)
	- \%I Hour in 12-hour format (01 - 12)
	- \%j Day of year as decimal number (001 - 366)
	- \%m Month as decimal number (01 - 12)
	- \%M Minute as decimal number (00 - 59)
	- \%p Current locale's A.M./P.M. indicator for 12-hour clock
	- \%S Second as decimal number (00 - 59)
	- \%U Week of year as decimal number, with Sunday as first day of week (00 - 53)
	- \%w Weekday as decimal number (0 - 6; Sunday is 0)
	- \%W Week of year as decimal number, with Monday as first day of week (00 - 53)
	- \%x Date representation for current locale
	- \%X Time representation for current locale
	- \%y Year without century, as decimal number (00 - 99)
	- \%Y Year with century, as decimal number
	- \%z, %Z Either the time-zone name or time zone abbreviation, depending on registry settings; no characters if time zone is unknown
	- \%\% Percent sign
	*/
	bool ParseDateTime(const AnsiString &str, tm &out, const AnsiString &format = "%Y-%m-%d %H:%M:%S", const std::locale &locale = std::locale());

	/**
	Explode string by specified delimiter and put parts into specified output
	@param str String to exploding
	@param delimiter Exploding delimiter
	@param[out] out Vector of string parts
	@param remove_empty Indicates if empty parts should be removed. Default is true
	*/
	void Explode(const String &str, const String &delimiter, std::vector<String> &out, const bool remove_empty = true);

	/**
	Explode ansi string by specified delimiter and put parts into specified output
	@param str String to exploding
	@param delimiter Exploding delimiter
	@param[out] out Vector of string parts
	@param remove_empty Indicates if empty parts should be removed. Default is true
	*/
	void Explode(const AnsiString &str, const AnsiString &delimiter, std::vector<AnsiString> &out, const bool remove_empty = true);

	/**
	Explode string by specified delimiter and return result(less efficient than version without result due to twice copying)
	@param str String to exploding
	@param delimiter Exploding delimiter
	@param remove_empty Indicates if empty parts should be removed. Default is true
	@return Vector of string parts
	*/
	std::vector<String> Explode(const String &str, const String &delimiter, const bool remove_empty = true);

	/**
	Explode ansi string by specified delimiter and return result(less efficient than version without result due to twice copying)
	@param str String to exploding
	@param delimiter Exploding delimiter
	@param remove_empty Indicates if empty parts should be removed. Default is true
	@return Vector of string parts
	*/
	std::vector<AnsiString> Explode(const AnsiString &str, const AnsiString &delimiter, const bool remove_empty = true);

	/**
	Convert string to upper case and return result
	@param str Source string
	@param locale Locale used for conversion. Default is current one
	@return Uppercase representation of source string
	*/
	String ToUpper(const String &str, const std::locale &locale = std::locale());

	/**
	Convert ansi string to upper case and return result
	@param str Source string
	@param locale Locale used for conversion. Default is current one
	@return Uppercase representation of source string
	*/
	AnsiString ToUpper(const AnsiString &str, const std::locale &locale = std::locale());

	/**
	Direct convert string to upper case
	@param[in, out] str String to be converted
	@param locale Locale used for conversion. Default is current one
	*/
	void ToUpperDirect(String &str, const std::locale &locale = std::locale());

	/**
	Direct convert ansi string to upper case
	@param[in, out] str String to be converted
	@param locale Locale used for conversion. Default is current one
	*/
	void ToUpperDirect(AnsiString &str, const std::locale &locale = std::locale());

	/**
	Convert string to lower case and return result
	@param str Source string
	@param locale Locale used for conversion. Default is current one
	@return Lowercase representation of source string
	*/
	String ToLower(const String &str, const std::locale &locale = std::locale());

	/**
	Convert ansi string to lower case and return result
	@param str Source string
	@param locale Locale used for conversion. Default is current one
	@return Lowercase representation of source string
	*/
	AnsiString ToLower(const AnsiString &str, const std::locale &locale = std::locale());

	/**
	Direct convert string to lower case
	@param[in, out] str String to be converted
	@param locale Locale used for conversion. Default is current one
	*/
	void ToLowerDirect(String &str, const std::locale &locale = std::locale());

	/**
	Direct convert ansi string to lower case
	@param[in, out] str String to be converted
	@param locale Locale used for conversion. Default is current one
	*/
	void ToLowerDirect(AnsiString &str, const std::locale &locale = std::locale());
#pragma endregion

#pragma region Searching
	/**
	Return index of starting word characted next after start position
	@param str String where to search
	@param start Index from where start to search
	@param with_punch If true, punctuation characters are interpreted as words as well
	@param locale Used locale
	@return Word start position or str length
	*/
	size_t SearchNextWord(const String &str, const size_t start, const bool with_punct = false, const std::locale &locale = std::locale());

	/**
	Return index of starting word characted prev to start position
	@param str String where to search
	@param start Index from where start to search
	@param with_punch If true, punctuation characters are interpreted as words as well
	@param locale Used locale
	@return Word start position or 0
	*/
	size_t SearchPrevWord(const String &str, const size_t start, const bool with_punct = false, const std::locale &locale = std::locale());
#pragma endregion

#pragma region Inline functions
#pragma region Strings conversions
	UTF8String AnsiToUTF8(const AnsiString &str)
	{
		return StringToUTF8(AnsiToString(str));
	}

	AnsiString UTF8ToAnsi(const UTF8String &str)
	{
		return StringToAnsi(UTF8ToString(str));
	}
#pragma endregion

#pragma region Convert strings to numerical values
	int StringToInt(const String &str)
	{
		return std::stoi(str);
	}

	int StringToInt(const AnsiString &str)
	{
		return std::stoi(str);
	}

	unsigned int StringToUInt(const String &str)
	{
		return std::stoul(str);
	}

	unsigned int StringToUInt(const AnsiString &str)
	{
		return std::stoul(str);
	}

	__int64 StringToInt64(const String &str)
	{
		return std::stoll(str);
	}

	__int64 StringToInt64(const AnsiString &str)
	{
		return std::stoll(str);
	}

	unsigned __int64 StringToUInt64(const String &str)
	{
		return std::stoull(str);
	}

	unsigned __int64 StringToUInt64(const AnsiString &str)
	{
		return std::stoull(str);
	}

	float StringToFloat(const String &str)
	{
		return std::stof(str);
	}

	float StringToFloat(const AnsiString &str)
	{
		return std::stof(str);
	}

	double StringToDouble(const String &str)
	{
		return std::stod(str);
	}

	double StringToDouble(const AnsiString &str)
	{
		return std::stod(str);
	}
#pragma endregion

#pragma region Convert numerical values to strings
	String ToString(const int value)
	{
		return std::to_wstring(value);
	}

	String ToString(const unsigned int value)
	{
		return std::to_wstring(value);
	}

	String ToString(const __int64 value)
	{
		return std::to_wstring(value);
	}

	String ToString(const unsigned __int64 value)
	{
		return std::to_wstring(value);
	}

	String ToString(const float value)
	{
		return std::to_wstring(value);
	}

	String ToString(const double value)
	{
		return std::to_wstring(value);
	}

	AnsiString ToAnsi(const int value)
	{
		return std::to_string(value);
	}

	AnsiString ToAnsi(const unsigned int value)
	{
		return std::to_string(value);
	}

	AnsiString ToAnsi(const __int64 value)
	{
		return std::to_string(value);
	}

	AnsiString ToAnsi(const unsigned __int64 value)
	{
		return std::to_string(value);
	}

	AnsiString ToAnsi(const float value)
	{
		return std::to_string(value);
	}

	AnsiString ToAnsi(const double value)
	{
		return std::to_string(value);
	}
#pragma endregion
#pragma endregion
}